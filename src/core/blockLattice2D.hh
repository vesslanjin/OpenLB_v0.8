/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006-2008 Jonas Latt
 *  OMP parallel code by Mathias Krause, Copyright (C) 2007
 *  E-mail contact: info@openlb.net
 *  The most recent release of OpenLB can be downloaded at
 *  <http://www.openlb.net/>
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License
 *  as published by the Free Software Foundation; either version 2
 *  of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public
 *  License along with this program; if not, write to the Free
 *  Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA  02110-1301, USA.
*/

/** \file
 * The dynamics of a 2D block lattice -- generic implementation.
 */
#ifndef BLOCK_LATTICE_2D_HH
#define BLOCK_LATTICE_2D_HH

#include <algorithm>
#include "blockLattice2D.h"
#include "dynamics.h"
#include "cell.h"
#include "lbHelpers.h"
#include "util.h"
#include "ompManager.h"
#include "loadBalancer.h"
#include "dataAnalysis2D.h"

namespace olb {

////////////////////// Class BlockLattice2D /////////////////////////

/** \param nx_ lattice width (first index)
 *  \param ny_ lattice height (second index)
 */
template<typename T, template<typename U> class Lattice>
BlockLattice2D<T,Lattice>::BlockLattice2D(int nx_, int ny_)
  : nx(nx_), ny(ny_),
    serializer(0), unSerializer(0),
    dataAnalysis( new DataAnalysis2D<T,Lattice>(*this) )
{
  allocateMemory();
  resetPostProcessors();
#ifdef PARALLEL_MODE_OMP
  statistics = new LatticeStatistics<T>* [3*omp.get_size()];
  #pragma omp parallel
  { statistics[omp.get_rank() + omp.get_size()]
    = new LatticeStatistics<T>;
    statistics[omp.get_rank()] = new LatticeStatistics<T>;
    statistics[omp.get_rank() + 2*omp.get_size()]
    = new LatticeStatistics<T>;
  }
#else
  statistics = new LatticeStatistics<T>;
#endif
}

/** During destruction, the memory for the lattice and the contained
 * cells is released. However, the dynamics objects pointed to by
 * the cells must be deleted manually by the user.
 */
template<typename T, template<typename U> class Lattice>
BlockLattice2D<T,Lattice>::~BlockLattice2D()
{
  releaseMemory();
  clearPostProcessors();
  clearLatticeCouplings();
#ifdef PARALLEL_MODE_OMP
  #pragma omp parallel
  {
    delete statistics[omp.get_rank()];
  }
  delete statistics;
#else
  delete statistics;
#endif
  delete serializer;
  delete unSerializer;
  delete dataAnalysis;
}

/** The whole data of the lattice is duplicated. This includes
 * both particle distribution function and external fields.
 * \warning The dynamics objects and postProcessors are not copied
 * \param rhs the lattice to be duplicated
 */
template<typename T, template<typename U> class Lattice>
BlockLattice2D<T,Lattice>::BlockLattice2D(BlockLattice2D<T,Lattice> const& rhs)
  : serializer(0), unSerializer(0),
    dataAnalysis( new DataAnalysis2D<T,Lattice>(*this) )
{
  nx = rhs.nx;
  ny = rhs.ny;
  allocateMemory();
  resetPostProcessors();
  for (int iX=0; iX<nx; ++iX) {
    for (int iY=0; iY<ny; ++iY) {
      grid[iX][iY] = rhs.grid[iX][iY];
    }
  }
#ifdef PARALLEL_MODE_OMP
  statistics = new LatticeStatistics<T>* [3*omp.get_size()];
  #pragma omp parallel
  { statistics[omp.get_rank() + omp.get_size()]
    = new LatticeStatistics<T>;
    statistics[omp.get_rank()] = new LatticeStatistics<T> (**rhs.statistics);
    statistics[omp.get_rank() + 2*omp.get_size()]
    = new LatticeStatistics<T>;
  }
#else
  statistics = new LatticeStatistics<T> (*rhs.statistics);
#endif
}

/** The current lattice is deallocated, then the lattice from the rhs
 * is duplicated. This includes both particle distribution function
 * and external fields.
 * \warning The dynamics objects and postProcessors are not copied
 * \param rhs the lattice to be duplicated
 */
template<typename T, template<typename U> class Lattice>
BlockLattice2D<T,Lattice>& BlockLattice2D<T,Lattice>::operator= (
  BlockLattice2D<T,Lattice> const& rhs )
{
  BlockLattice2D<T,Lattice> tmp(rhs);
  swap(tmp);
  return *this;
}

/** The swap is efficient, in the sense that only pointers to the
 * lattice are copied, and not the lattice itself.
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::swap(BlockLattice2D& rhs) {
  std::swap(nx, rhs.nx);
  std::swap(ny, rhs.ny);
  std::swap(rawData, rhs.rawData);
  std::swap(grid, rhs.grid);
  postProcessors.swap(rhs.postProcessors);
  std::swap(statistics, rhs.statistics);
  std::swap(serializer, rhs.serializer);
  std::swap(unSerializer, rhs.unSerializer);
  std::swap(dataAnalysis, rhs.dataAnalysis);
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::initialize() {
  postProcess();
}

/** The dynamics object is not duplicated: all cells of the rectangular
 * domain point to the same dynamics.
 *
 * The dynamics object is not owned by the BlockLattice2D object, its
 * memory management is in charge of the user.
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::defineDynamics (
  int x0, int x1, int y0, int y1, Dynamics<T,Lattice>* dynamics )
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);

  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      grid[iX][iY].defineDynamics(dynamics);
    }
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::defineDynamics (
  int iX, int iY, Dynamics<T,Lattice>* dynamics )
{
  OLB_PRECONDITION(iX>=0 && iX<nx);
  OLB_PRECONDITION(iY>=0 && iY<ny);

  grid[iX][iY].defineDynamics(dynamics);
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::defineDynamics (
  BlockGeometryStatistics2D* blockGeoSta, Dynamics<T,Lattice>* dynamics, int material )
{
  defineDynamics (
    blockGeoSta,
    0, blockGeoSta->getBlockGeometry()->getNx()-1, 0, blockGeoSta->getBlockGeometry()->getNy()-1,
    dynamics, material );
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::defineDynamics (
  BlockGeometryStatistics2D* blockGeoSta,
  int x0, int x1, int y0, int y1,
  Dynamics<T,Lattice>* dynamics, int material )
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);
  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      if(blockGeoSta->getBlockGeometry()->getMaterial(iX, iY)==material) {
        grid[iX][iY].defineDynamics(dynamics);

      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::specifyStatisticsStatus (
  int x0, int x1, int y0, int y1, bool status )
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);

  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      grid[iX][iY].specifyStatisticsStatus(status);
    }
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::collide(int x0, int x1, int y0, int y1) {
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);

  int iX;
#ifdef PARALLEL_MODE_OMP
  #pragma omp parallel for schedule(dynamic,1)
#endif
  for (iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      grid[iX][iY].collide(getStatistics());
      grid[iX][iY].revert();
    }
  }
}

/** \sa collide(int,int,int,int) */
template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::collide() {
  collide(0, nx-1, 0, ny-1);
}

/**
 * A useful method for initializing the flow field to a given velocity
 * profile.
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::staticCollide(int x0, int x1, int y0, int y1,
    TensorFieldBase2D<T,2> const& u)
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);

  int iX;

#ifdef PARALLEL_MODE_OMP
  #pragma omp parallel for schedule(dynamic,1)
#endif
  for (iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      grid[iX][iY].staticCollide(u.get(iX,iY), getStatistics());
      grid[iX][iY].revert();
    }
  }
}

/** \sa collide(int,int,int,int) */
template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::staticCollide(TensorFieldBase2D<T,2> const& u) {
  staticCollide(0, nx-1, 0, ny-1, u);
}

/** The distribution functions never leave the rectangular domain. On the
 * domain boundaries, the (outgoing) distribution functions that should
 * be streamed outside are simply left untouched.
 * The post-processing steps are not automatically invoked by this method,
 * as they are in the method stream(). If you want them to be executed, you
 * must explicitly call the method postProcess().
 * \sa stream()
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::stream(int x0, int x1, int y0, int y1) {
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);

  static const int vicinity = Lattice<T>::vicinity;

  bulkStream(x0+vicinity,x1-vicinity,y0+vicinity,y1-vicinity);

  boundaryStream(x0,x1,y0,y1, x0,x0+vicinity-1, y0,y1);
  boundaryStream(x0,x1,y0,y1, x1-vicinity+1,x1, y0,y1);
  boundaryStream(x0,x1,y0,y1, x0+vicinity,x1-vicinity, y0,y0+vicinity-1);
  boundaryStream(x0,x1,y0,y1, x0+vicinity,x1-vicinity, y1-vicinity+1,y1);
}

/** At the end of this method, the post-processing steps are automatically
 * invoked.
 * \sa stream(int,int,int,int)
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::stream(bool periodic) {
  stream(0, nx-1, 0, ny-1);

  if (periodic) {
    makePeriodic();
  }

  postProcess();
  getStatistics().incrementTime();
}

/** This operation is more efficient than a successive application of
 * collide(int,int,int,int) and stream(int,int,int,int), because memory
 * is traversed only once instead of twice.
 * The post-processing steps are not automatically invoked by this method,
 * as they are in the method stream(). If you want them to be executed, you
 * must explicitly call the method postProcess().
 * \sa collideAndStream()
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::collideAndStream(int x0, int x1, int y0, int y1)
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);

  static const int vicinity = Lattice<T>::vicinity;

  // First, do the collision on cells within a boundary envelope of width
  // equal to the range of the lattice vectors (e.g. 1 for D2Q9)
  collide(x0,x0+vicinity-1, y0,y1);
  collide(x1-vicinity+1,x1, y0,y1);
  collide(x0+vicinity,x1-vicinity, y0,y0+vicinity-1);
  collide(x0+vicinity,x1-vicinity, y1-vicinity+1,y1);

  // Then, do the efficient collideAndStream algorithm in the bulk,
  // excluding the envelope (this is efficient because there is no
  // if-then-else statement within the loop, given that the boundary
  // region is excluded)
  bulkCollideAndStream(x0+vicinity,x1-vicinity,y0+vicinity,y1-vicinity);

  // Finally, do streaming in the boundary envelope to conclude the
  // collision-stream cycle
  boundaryStream(x0,x1,y0,y1, x0,x0+vicinity-1,y0,y1);
  boundaryStream(x0,x1,y0,y1, x1-vicinity+1,x1,y0,y1);
  boundaryStream(x0,x1,y0,y1, x0+vicinity,x1-vicinity, y0,y0+vicinity-1);
  boundaryStream(x0,x1,y0,y1, x0+vicinity,x1-vicinity, y1-vicinity+1,y1);
}

/** At the end of this method, the post-processing steps are automatically
 * invoked.
 * \sa collideAndStream(int,int,int,int) */
template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::collideAndStream(bool periodic) {
  collideAndStream(0, nx-1, 0, ny-1);

  if (periodic) {
    makePeriodic();
  }

  postProcess();
  getStatistics().incrementTime();
}

template<typename T, template<typename U> class Lattice>
T BlockLattice2D<T,Lattice>::computeAverageDensity (
  int x0, int x1, int y0, int y1) const
{
  T sumRho = T();
  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      T rho, u[Lattice<T>::d];
      get(iX,iY).computeRhoU(rho, u);
      sumRho += rho;
    }
  }
  return sumRho / (T)(x1-x0+1) / (T)(y1-y0+1);
}

template<typename T, template<typename U> class Lattice>
T BlockLattice2D<T,Lattice>::computeAverageDensity() const {
  return computeAverageDensity(0, nx-1, 0, ny-1);
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::stripeOffDensityOffset (
  int x0, int x1, int y0, int y1, T offset )
{
  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iPop=0; iPop<Lattice<T>::q; ++iPop) {
        get(iX,iY)[iPop] -= Lattice<T>::t[iPop] * offset;
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::stripeOffDensityOffset(T offset) {
  stripeOffDensityOffset(0, nx-1, 0, ny-1, offset);
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::forAll (
  int x0, int x1, int y0, int y1, WriteCellFunctional<T,Lattice> const& application )
{
  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      application.apply( get(iX,iY) );
    }
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::forAll(WriteCellFunctional<T,Lattice> const& application) {
  forAll(0, nx-1, 0, ny-1, application);
}


template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::addPostProcessor (
  PostProcessorGenerator2D<T,Lattice> const& ppGen )
{
  postProcessors.push_back(ppGen.generate());
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::resetPostProcessors() {
  clearPostProcessors();
  StatPPGenerator2D<T,Lattice> statPPGenerator;
  addPostProcessor(statPPGenerator);
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::clearPostProcessors() {
  typename PostProcVector::iterator ppIt = postProcessors.begin();
  for (; ppIt != postProcessors.end(); ++ppIt) {
    delete *ppIt;
  }
  postProcessors.clear();
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::postProcess() {
  for (unsigned iPr=0; iPr<postProcessors.size(); ++iPr) {
    postProcessors[iPr] -> process(*this);
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::postProcess(int x0_, int x1_, int y0_, int y1_)
{
  for (unsigned iPr=0; iPr<postProcessors.size(); ++iPr) {
    postProcessors[iPr] -> processSubDomain(*this, x0_, x1_, y0_, y1_);
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::addLatticeCoupling (
  LatticeCouplingGenerator2D<T,Lattice> const& lcGen,
  std::vector<SpatiallyExtendedObject2D*> partners )
{
  latticeCouplings.push_back(lcGen.generate(partners));
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::executeCoupling() {
  for (unsigned iPr=0; iPr<latticeCouplings.size(); ++iPr) {
    latticeCouplings[iPr] -> process(*this);
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::executeCoupling(int x0_, int x1_, int y0_, int y1_) {
  for (unsigned iPr=0; iPr<latticeCouplings.size(); ++iPr) {
    latticeCouplings[iPr] -> processSubDomain(*this, x0_, x1_, y0_, y1_);
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::clearLatticeCouplings() {
  typename PostProcVector::iterator ppIt = latticeCouplings.begin();
  for (; ppIt != latticeCouplings.end(); ++ppIt) {
    delete *ppIt;
  }
  latticeCouplings.clear();
}


template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::subscribeReductions(Reductor<T>& reductor) {
  for (unsigned iPr=0; iPr<postProcessors.size(); ++iPr) {
    postProcessors[iPr] -> subscribeReductions(*this, &reductor);
  }
}

template<typename T, template<typename U> class Lattice>
LatticeStatistics<T>& BlockLattice2D<T,Lattice>::getStatistics() {
#ifdef PARALLEL_MODE_OMP
  return *statistics[omp.get_rank()];
#else
  return *statistics;
#endif
}

template<typename T, template<typename U> class Lattice>
LatticeStatistics<T> const& BlockLattice2D<T,Lattice>::getStatistics() const {
#ifdef PARALLEL_MODE_OMP
  return *statistics[omp.get_rank()];
#else
  return *statistics;
#endif
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::allocateMemory() {
  // The conversions to size_t ensure 64-bit compatibility. Note that
  //   nx and ny are of type int, which might by 32-bit types, even on
  //   64-bit platforms. Therefore, nx*ny may lead to a type overflow.
  rawData = new Cell<T,Lattice> [(size_t)nx*(size_t)ny];
  grid    = new Cell<T,Lattice>* [(size_t)nx];
  for (int iX=0; iX<nx; ++iX) {
    grid[iX] = rawData + (size_t)iX*(size_t)ny;
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::releaseMemory() {
  delete [] rawData;
  delete [] grid;
}

/** This method is slower than bulkStream(int,int,int,int), because it must
 * be verified which distribution functions are to be kept from leaving
 * the domain.
 * \sa stream(int,int,int,int)
 * \sa stream()
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::boundaryStream (
  int lim_x0, int lim_x1, int lim_y0, int lim_y1,
  int x0, int x1, int y0, int y1 )
{
  OLB_PRECONDITION(lim_x0>=0 && lim_x1<nx);
  OLB_PRECONDITION(lim_x1>=lim_x0);
  OLB_PRECONDITION(lim_y0>=0 && lim_y1<ny);
  OLB_PRECONDITION(lim_y1>=lim_y0);

  OLB_PRECONDITION(x0>=lim_x0 && x1<=lim_x1);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=lim_y0 && y1<=lim_y1);
  OLB_PRECONDITION(y1>=y0);

  int iX;

#ifdef PARALLEL_MODE_OMP
  #pragma omp parallel for
#endif
  for (iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iPop=1; iPop<=Lattice<T>::q/2; ++iPop) {
        int nextX = iX + Lattice<T>::c[iPop][0];
        int nextY = iY + Lattice<T>::c[iPop][1];
        if (nextX>=lim_x0 && nextX<=lim_x1 && nextY>=lim_y0 && nextY<=lim_y1) {
          std::swap(grid[iX][iY][iPop+Lattice<T>::q/2],
                    grid[nextX][nextY][iPop]);
        }
      }
    }
  }
}

/** This method is faster than boundaryStream(int,int,int,int), but it
 * is erroneous when applied to boundary cells.
 * \sa stream(int,int,int,int)
 * \sa stream()
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::bulkStream (
  int x0, int x1, int y0, int y1 )
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);

  int iX;
#ifdef PARALLEL_MODE_OMP
  #pragma omp parallel for
#endif
  for (iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iPop=1; iPop<=Lattice<T>::q/2; ++iPop) {
        int nextX = iX + Lattice<T>::c[iPop][0];
        int nextY = iY + Lattice<T>::c[iPop][1];
        std::swap(grid[iX][iY][iPop+Lattice<T>::q/2],
                  grid[nextX][nextY][iPop]);
      }
    }
  }
}

#ifndef PARALLEL_MODE_OMP  // OpenMP parallel version is at the
// end of this file
/** This method is fast, but it is erroneous when applied to boundary
 * cells.
 * \sa collideAndStream(int,int,int,int)
 * \sa collideAndStream()
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::bulkCollideAndStream (
  int x0, int x1, int y0, int y1 )
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);

  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      grid[iX][iY].collide(getStatistics());
      lbHelpers<T,Lattice>::swapAndStream2D(grid, iX, iY);
    }
  }
  #if  0 //check the result
 for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
    // if(iX%10==0 && iY%10==0){
	if(iX%100==0 && iY%10==0){
     std::cout<<" X "<<iX<<" Y "<<iY<<" 0 "<<grid[iX][iY][0]<<std::endl;
     std::cout<<" X "<<iX<<" Y "<<iY<<" 1 "<<grid[iX][iY][1]<<std::endl;
     std::cout<<" X "<<iX<<" Y "<<iY<<" 2 "<<grid[iX][iY][2]<<std::endl;
     std::cout<<" X "<<iX<<" Y "<<iY<<" 3 "<<grid[iX][iY][3]<<std::endl;
     std::cout<<" X "<<iX<<" Y "<<iY<<" 4 "<<grid[iX][iY][4]<<std::endl;
     std::cout<<" X "<<iX<<" Y "<<iY<<" 5 "<<grid[iX][iY][5]<<std::endl;
     std::cout<<" X "<<iX<<" Y "<<iY<<" 6 "<<grid[iX][iY][6]<<std::endl;
     std::cout<<" X "<<iX<<" Y "<<iY<<" 7 "<<grid[iX][iY][7]<<std::endl;
     std::cout<<" X "<<iX<<" Y "<<iY<<" 8 "<<grid[iX][iY][8]<<std::endl;
  }
  }
  }
#endif

}
#endif // not defined PARALLEL_MODE_OMP

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::periodicEdge(int x0, int x1, int y0, int y1)
{
  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iPop=1; iPop<=Lattice<T>::q/2; ++iPop) {
        int nextX = iX + Lattice<T>::c[iPop][0];
        int nextY = iY + Lattice<T>::c[iPop][1];
        if ( nextX<0 || nextX>=getNx() ||
             nextY<0 || nextY>=getNy() )
        {
          nextX = (nextX+getNx())%getNx();
          nextY = (nextY+getNy())%getNy();
          std::swap (
            grid[iX][iY]        [iPop+Lattice<T>::q/2],
            grid[nextX][nextY][iPop] );
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::makePeriodic() {
  static const int vicinity = Lattice<T>::vicinity;
  int maxX = getNx()-1;
  int maxY = getNy()-1;
  periodicEdge(0,vicinity-1, 0,maxY);
  periodicEdge(maxX-vicinity+1,maxX, 0,maxY);
  periodicEdge(vicinity,maxX-vicinity, 0,vicinity-1);
  periodicEdge(vicinity,maxX-vicinity, maxY-vicinity+1,maxY);
}

template<typename T, template<typename U> class Lattice>
DataAnalysisBase2D<T,Lattice> const& BlockLattice2D<T,Lattice>::getDataAnalysis() const {
  dataAnalysis -> reset();
  return *dataAnalysis;
}

template<typename T, template<typename U> class Lattice>
DataSerializer<T> const& BlockLattice2D<T,Lattice>::getSerializer(IndexOrdering::OrderingT ordering) const {
  delete serializer;
  serializer = new BlockLatticeSerializer2D<T,Lattice>(*this, ordering);
  return *serializer;
}

template<typename T, template<typename U> class Lattice>
DataUnSerializer<T>& BlockLattice2D<T,Lattice>::getUnSerializer(IndexOrdering::OrderingT ordering) {
  delete unSerializer;
  unSerializer = new BlockLatticeUnSerializer2D<T,Lattice>(*this, ordering);
  return *unSerializer;
}

template<typename T, template<typename U> class Lattice>
DataSerializer<T> const& BlockLattice2D<T,Lattice>::getSubSerializer (
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering ) const
{
  delete serializer;
  serializer = new BlockLatticeSerializer2D<T,Lattice> (
    *this, x0_, x1_, y0_, y1_, ordering );
  return *serializer;
}

template<typename T, template<typename U> class Lattice>
DataUnSerializer<T>& BlockLattice2D<T,Lattice>::getSubUnSerializer (
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering )
{
  delete unSerializer;
  unSerializer = new BlockLatticeUnSerializer2D<T,Lattice> (
    *this, x0_, x1_, y0_, y1_, ordering );
  return *unSerializer;
}

template<typename T, template<typename U> class Lattice>
MultiDataDistribution2D BlockLattice2D<T,Lattice>::getDataDistribution() const {
  return MultiDataDistribution2D(getNx(), getNy());
}

template<typename T, template<typename U> class Lattice>
SpatiallyExtendedObject2D* BlockLattice2D<T,Lattice>::getComponent(int iBlock) {
  OLB_PRECONDITION( iBlock==0 );
  return this;
}

template<typename T, template<typename U> class Lattice>
SpatiallyExtendedObject2D const* BlockLattice2D<T,Lattice>::getComponent(int iBlock) const {
  OLB_PRECONDITION( iBlock==0 );
  return this;
}

template<typename T, template<typename U> class Lattice>
multiPhysics::MultiPhysicsId BlockLattice2D<T,Lattice>::getMultiPhysicsId() const {
  return multiPhysics::getMultiPhysicsBlockId<T,Lattice>();
}



////////// class BlockLatticeSerializer2D ////////////////////////////

template<typename T, template<typename U> class Lattice>
BlockLatticeSerializer2D<T,Lattice>::BlockLatticeSerializer2D (
  BlockLattice2D<T,Lattice> const& blockLattice_, IndexOrdering::OrderingT ordering_ )
  : blockLattice(blockLattice_), ordering(ordering_),
    x0(0), x1(blockLattice.getNx()-1), y0(0), y1(blockLattice.getNy()-1),
    iX(x0), iY(y0),
    sizeOfCell(Lattice<T>::q + Lattice<T>::ExternalField::numScalars)
{ }

template<typename T, template<typename U> class Lattice>
BlockLatticeSerializer2D<T,Lattice>::BlockLatticeSerializer2D (
  BlockLattice2D<T,Lattice> const& blockLattice_,
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering_ )
  : blockLattice(blockLattice_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_),
    iX(x0), iY(y0),
    sizeOfCell(Lattice<T>::q + Lattice<T>::ExternalField::numScalars)
{ }

template<typename T, template<typename U> class Lattice>
size_t BlockLatticeSerializer2D<T,Lattice>::getSize() const {
  return (size_t)(x1-x0+1) * (size_t)(y1-y0+1) * (size_t)sizeOfCell;
}

template<typename T, template<typename U> class Lattice>
const T* BlockLatticeSerializer2D<T,Lattice>::getNextDataBuffer(size_t& bufferSize) const {
  OLB_PRECONDITION( !isEmpty() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    bufferSize = (size_t)(y1-y0+1)*(size_t)sizeOfCell;
    buffer.resize(bufferSize);
    for (iY=y0; iY<=y1; ++iY) {
      blockLattice.get(iX,iY).serialize(&buffer[(size_t)sizeOfCell*(size_t)(iY-y0)]);
    }
    ++iX;
  }
  else {
    bufferSize = (size_t)(x1-x0+1)*(size_t)sizeOfCell;
    buffer.resize(bufferSize);
    for (iX=x0; iX<=x1; ++iX) {
      blockLattice.get(iX,iY).serialize(&buffer[(size_t)sizeOfCell*(size_t)(iX-x0)]);
    }
    ++iY;
  }
  return &buffer[0];
}

template<typename T, template<typename U> class Lattice>
bool BlockLatticeSerializer2D<T,Lattice>::isEmpty() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iY > y1;
  }
}


////////// class BlockLatticeUnSerializer2D ////////////////////////////

template<typename T, template<typename U> class Lattice>
BlockLatticeUnSerializer2D<T,Lattice>::BlockLatticeUnSerializer2D (
  BlockLattice2D<T,Lattice>& blockLattice_, IndexOrdering::OrderingT ordering_ )
  : blockLattice(blockLattice_), ordering(ordering_),
    x0(0), x1(blockLattice.getNx()-1), y0(0), y1(blockLattice.getNy()-1),
    iX(x0), iY(y0),
    sizeOfCell(Lattice<T>::q + Lattice<T>::ExternalField::numScalars)
{ }

template<typename T, template<typename U> class Lattice>
BlockLatticeUnSerializer2D<T,Lattice>::BlockLatticeUnSerializer2D (
  BlockLattice2D<T,Lattice>& blockLattice_,
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering_ )
  : blockLattice(blockLattice_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_),
    iX(x0), iY(y0),
    sizeOfCell(Lattice<T>::q + Lattice<T>::ExternalField::numScalars)
{ }

template<typename T, template<typename U> class Lattice>
size_t BlockLatticeUnSerializer2D<T,Lattice>::getSize() const {
  return (size_t)(x1-x0+1) * (size_t)(y1-y0+1) * (size_t)sizeOfCell;
}

template<typename T, template<typename U> class Lattice>
T* BlockLatticeUnSerializer2D<T,Lattice>::getNextDataBuffer(size_t& bufferSize) {
  OLB_PRECONDITION( !isFull() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    bufferSize = (size_t)(y1-y0+1)*(size_t)sizeOfCell;
  }
  else {
    bufferSize = (size_t)(x1-x0+1)*(size_t)sizeOfCell;
  }
  buffer.resize(bufferSize);
  return &buffer[0];
}

template<typename T, template<typename U> class Lattice>
void BlockLatticeUnSerializer2D<T,Lattice>::commitData() {
  OLB_PRECONDITION( !isFull() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    for (iY=y0; iY<=y1; ++iY) {
      blockLattice.get(iX,iY).unSerialize(&buffer[(size_t)(iY-y0)*(size_t)sizeOfCell]);
    }
    ++iX;
  }
  else {
    for (iX=x0; iX<=x1; ++iX) {
      blockLattice.get(iX,iY).unSerialize(&buffer[(size_t)(iX-x0)*(size_t)sizeOfCell]);
    }
    ++iY;
  }
}

template<typename T, template<typename U> class Lattice>
bool BlockLatticeUnSerializer2D<T,Lattice>::isFull() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iY > y1;
  }
}


//// OpenMP implementation of the method bulkCollideAndStream,
//   by Mathias Krause                                         ////

#ifdef PARALLEL_MODE_OMP
template<typename T, template<typename U> class Lattice>
void BlockLattice2D<T,Lattice>::bulkCollideAndStream (
  int x0, int x1, int y0, int y1 )
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);

  if (omp.get_size() <= x1-x0+1) {
    #pragma omp parallel
    {
      loadBalancer loadbalance(omp.get_rank(), omp.get_size(), x1-x0+1, x0);
      int iX, iY, iPop;

      iX=loadbalance.get_firstGlobNum();
      for (int iY=y0; iY<=y1; ++iY) {
        grid[iX][iY].collide(getStatistics());
        grid[iX][iY].revert();
      }

      for (iX=loadbalance.get_firstGlobNum()+1; iX<=loadbalance.get_lastGlobNum(); ++iX) {
        for (iY=y0; iY<=y1; ++iY) {
          grid[iX][iY].collide(getStatistics());
          /** The method beneath doesnt work with Intel compiler 9.1044 and 9.1046 for Itanium prozessors
           *    lbHelpers<T,Lattice>::swapAndStream2D(grid, iX, iY);
           *  Therefore we use:
           */
          int half = Lattice<T>::q/2;
          for (int iPop=1; iPop<=half; ++iPop) {
            int nextX = iX + Lattice<T>::c[iPop][0];
            int nextY = iY + Lattice<T>::c[iPop][1];
            T fTmp                   = grid[iX][iY][iPop];
            grid[iX][iY][iPop]       = grid[iX][iY][iPop+half];
            grid[iX][iY][iPop+half]  = grid[nextX][nextY][iPop];
            grid[nextX][nextY][iPop] = fTmp;
          }
        }
      }

      #pragma omp barrier

      iX=loadbalance.get_firstGlobNum();
      for (iY=y0; iY<=y1; ++iY) {
        for (iPop=1; iPop<=Lattice<T>::q/2; ++iPop) {
          int nextX = iX + Lattice<T>::c[iPop][0];
          int nextY = iY + Lattice<T>::c[iPop][1];
          std::swap(grid[iX][iY][iPop+Lattice<T>::q/2],
                    grid[nextX][nextY][iPop]);
        }
      }
    }
  }
  else {
    for (int iX=x0; iX<=x1; ++iX) {
      for (int iY=y0; iY<=y1; ++iY) {
        grid[iX][iY].collide(getStatistics());
        lbHelpers<T,Lattice>::swapAndStream2D(grid, iX, iY);
      }
    }
  }
}
#endif // defined PARALLEL_MODE_OMP


}  // namespace olb

#endif
