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
 * The dynamics of a 3D block lattice -- generic implementation.
 */
#ifndef BLOCK_LATTICE_3D_HH
#define BLOCK_LATTICE_3D_HH

#include <algorithm>
#include "blockLattice3D.h"
#include "dynamics.h"
#include "cell.h"
#include "lbHelpers.h"
#include "util.h"
#include "ompManager.h"
#include "loadBalancer.h"
#include "dataAnalysis3D.h"


namespace olb {

////////////////////// Class BlockLattice3D /////////////////////////

/** \param nx_ lattice width (first index)
 *  \param ny_ lattice height (second index)
 *  \param nz_ lattice depth (third index)
 */
template<typename T, template<typename U> class Lattice>
BlockLattice3D<T,Lattice>::BlockLattice3D(int nx_, int ny_, int nz_)
  : nx(nx_), ny(ny_), nz(nz_),
    serializer(0), unSerializer(0),
    dataAnalysis(new DataAnalysis3D<T,Lattice>(*this) )
{
  allocateMemory();
  resetPostProcessors();
///*
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
//*/
 // statistics = new LatticeStatistics<T>;
}

/** During destruction, the memory for the lattice and the contained
 * cells is released. However, the dynamics objects pointed to by
 * the cells must be deleted manually by the user.
 */
template<typename T, template<typename U> class Lattice>
BlockLattice3D<T,Lattice>::~BlockLattice3D()
{
  releaseMemory();
  clearPostProcessors();
  clearLatticeCouplings();
///*
#ifdef PARALLEL_MODE_OMP
  #pragma omp parallel
  {
    delete statistics[omp.get_rank()];
  }
  delete statistics;
#else
  delete statistics;
#endif
//*/
 // delete statistics;
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
BlockLattice3D<T,Lattice>::BlockLattice3D(BlockLattice3D<T,Lattice> const& rhs)
  :  serializer(0), unSerializer(0),
     dataAnalysis(new DataAnalysis3D<T,Lattice>(*this) )
{
  nx = rhs.nx;
  ny = rhs.ny;
  nz = rhs.nz;
  allocateMemory();
  resetPostProcessors();
  for (int iX=0; iX<nx; ++iX) {
    for (int iY=0; iY<ny; ++iY) {
      for (int iZ=0; iZ<nz; ++iZ) {
        grid[iX][iY][iZ] = rhs.grid[iX][iY][iZ];
      }
    }
  }
///*
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
//*/
//  statistics = new LatticeStatistics<T> (*rhs.statistics);
}

/** The current lattice is deallocated, then the lattice from the rhs
 * is duplicated. This includes both particle distribution function
 * and external fields.
 * \warning The dynamics objects and postProcessors are not copied
 * \param rhs the lattice to be duplicated
 */
template<typename T, template<typename U> class Lattice>
BlockLattice3D<T,Lattice>& BlockLattice3D<T,Lattice>::operator= (
  BlockLattice3D<T,Lattice> const& rhs )
{
  BlockLattice3D<T,Lattice> tmp(rhs);
  swap(tmp);
  return *this;
}

/** The swap is efficient, in the sense that only pointers to the
 * lattice are copied, and not the lattice itself.
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::swap(BlockLattice3D& rhs) {
  std::swap(nx, rhs.nx);
  std::swap(ny, rhs.ny);
  std::swap(nz, rhs.nz);
  std::swap(rawData, rhs.rawData);
  std::swap(grid, rhs.grid);
  postProcessors.swap(rhs.postProcessors);
  std::swap(statistics, rhs.statistics);
  std::swap(serializer, rhs.serializer);
  std::swap(unSerializer, rhs.unSerializer);
  std::swap(dataAnalysis, rhs.dataAnalysis);
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::initialize() {
  postProcess();
}

/** The dynamics object is not duplicated: all cells of the rectangular
 * domain point to the same dynamics.
 *
 * The dynamics object is not owned by the BlockLattice3D object, its
 * memory management must be taken care of by the user.
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::defineDynamics (
  int x0, int x1, int y0, int y1, int z0, int z1,
  Dynamics<T,Lattice>* dynamics )
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);
  OLB_PRECONDITION(z0>=0 && z1<nz);
  OLB_PRECONDITION(z1>=z0);

  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iZ=z0; iZ<=z1; ++iZ) {
        grid[iX][iY][iZ].defineDynamics(dynamics);
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::defineDynamics (
  int iX, int iY, int iZ, Dynamics<T,Lattice>* dynamics )
{
  OLB_PRECONDITION(iX>=0 && iX<nx);
  OLB_PRECONDITION(iY>=0 && iY<ny);
  OLB_PRECONDITION(iZ>=0 && iZ<nz);

  grid[iX][iY][iZ].defineDynamics(dynamics);
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::defineDynamics (
  BlockGeometry3D& blockGeometry, int material, Dynamics<T,Lattice>* dynamics)
{
  defineDynamics (
    blockGeometry, material,
    0, blockGeometry.getNx()-1, 0, blockGeometry.getNy()-1, 0, blockGeometry.getNz()-1,
    dynamics);
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::defineDynamics (
  BlockGeometry3D& blockGeometry, int material,
  int x0, int x1, int y0, int y1, int z0, int z1,
  Dynamics<T,Lattice>* dynamics)
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);
  OLB_PRECONDITION(z0>=0 && z1<nz);
  OLB_PRECONDITION(z1>=z0);
  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iZ=z0; iZ<=z1; ++iZ) {

        if(blockGeometry.getMaterial(iX, iY, iZ)==material) {

          grid[iX][iY][iZ].defineDynamics(dynamics);
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::specifyStatisticsStatus (
  int x0, int x1, int y0, int y1, int z0, int z1, bool status)
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);
  OLB_PRECONDITION(z0>=0 && z1<nz);
  OLB_PRECONDITION(z1>=z0);

  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iZ=z0; iZ<=z1; ++iZ) {
        grid[iX][iY][iZ].specifyStatisticsStatus(status);
      }
    }
  }
}

/**
 * This method is automatically parallelized if your compiler understands
 * OpenMP
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::collide (
  int x0, int x1, int y0, int y1, int z0, int z1)
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);
  OLB_PRECONDITION(z0>=0 && z1<nz);
  OLB_PRECONDITION(z1>=z0);

  int iX;
#ifdef PARALLEL_MODE_OMP
  //#pragma omp parallel for schedule(dynamic,1) collapse(2)
  #pragma omp for schedule(dynamic,1) collapse(2)
#endif
  for (iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iZ=z0; iZ<=z1; ++iZ) {
        grid[iX][iY][iZ].collide(getStatistics());
        grid[iX][iY][iZ].revert();
      }
    }
  }
}

/** \sa collide(int,int,int,int) */
template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::collide() {
  collide(0, nx-1, 0, ny-1, 0, nz-1);
}

/**
 * A useful method for initializing the flow field to a given velocity
 * profile.
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::staticCollide (
  int x0, int x1, int y0, int y1, int z0, int z1,
  TensorFieldBase3D<T,3> const& u )
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);
  OLB_PRECONDITION(z0>=0 && z1<nz);
  OLB_PRECONDITION(z1>=z0);

  int iX;
#ifdef PARALLEL_MODE_OMP
  #pragma omp parallel for schedule(dynamic,1)
#endif
  for (iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iZ=z0; iZ<=z1; ++iZ) {
        grid[iX][iY][iZ].staticCollide(u.get(iX,iY,iZ), getStatistics());
        grid[iX][iY][iZ].revert();
      }
    }
  }
}

/** \sa collide(int,int,int,int) */
template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::staticCollide(TensorFieldBase3D<T,3> const& u) {
  staticCollide(0, nx-1, 0, ny-1, 0, nz-1, u);
}

/** The distribution function never leave the rectangular domain. On the
 * domain boundaries, the (outgoing) distribution functions that should
 * be streamed outside are simply left untouched.
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::stream(int x0, int x1, int y0, int y1, int z0, int z1) {
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);
  OLB_PRECONDITION(z0>=0 && z1<nz);
  OLB_PRECONDITION(z1>=z0);

  static const int vicinity = Lattice<T>::vicinity;

  bulkStream(x0+vicinity,x1-vicinity, y0+vicinity,y1-vicinity, z0+vicinity,z1-vicinity);

  boundaryStream(x0,x1,y0,y1,z0,z1, x0,x0+vicinity-1, y0,y1, z0,z1);
  boundaryStream(x0,x1,y0,y1,z0,z1, x1-vicinity+1,x1, y0,y1, z0,z1);
  boundaryStream(x0,x1,y0,y1,z0,z1, x0+vicinity,x1-vicinity, y0,y0+vicinity-1, z0,z1);
  boundaryStream(x0,x1,y0,y1,z0,z1, x0+vicinity,x1-vicinity, y1-vicinity+1,y1, z0,z1);
  boundaryStream(x0,x1,y0,y1,z0,z1, x0+vicinity,x1-vicinity, y0+vicinity,y1-vicinity, z0,z0+vicinity-1);
  boundaryStream(x0,x1,y0,y1,z0,z1, x0+vicinity,x1-vicinity, y0+vicinity,y1-vicinity, z1-vicinity+1,z1);
}

/** Post-processing steps are called at the end of this method.
 * \sa stream(int,int,int,int,int,int) */
template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::stream(bool periodic) {
  stream(0, nx-1, 0, ny-1, 0, nz-1);

  if (periodic) {
    makePeriodic();
  }

  postProcess();
  getStatistics().incrementTime();
}

/** This operation is more efficient than a successive application of
 * collide(int,int,int,int,int,int) and stream(int,int,int,int,int,int),
 * because memory is traversed only once instead of twice.
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::collideAndStream(int x0, int x1, int y0, int y1, int z0, int z1) {
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);
  OLB_PRECONDITION(z0>=0 && z1<nz);
  OLB_PRECONDITION(z1>=z0);

  static const int vicinity = Lattice<T>::vicinity;

#ifdef PARALLEL_MODE_OMP
  #pragma omp parallel
#endif
 {
  collide(x0,x0+vicinity-1, y0,y1, z0,z1);
  collide(x1-vicinity+1,x1, y0,y1, z0,z1);
  collide(x0+vicinity,x1-vicinity, y0,y0+vicinity-1, z0,z1);
  collide(x0+vicinity,x1-vicinity, y1-vicinity+1,y1, z0,z1);
  collide(x0+vicinity,x1-vicinity, y0+vicinity,y1-vicinity, z0,z0+vicinity-1);
  collide(x0+vicinity,x1-vicinity, y0+vicinity,y1-vicinity, z1-vicinity+1,z1);
 //}
  bulkCollideAndStream(x0+vicinity,x1-vicinity, y0+vicinity,y1-vicinity, z0+vicinity,z1-vicinity);

//#ifdef PARALLEL_MODE_OMP
//  #pragma omp parallel
//#endif
// {
  boundaryStream(x0,x1,y0,y1,z0,z1, x0,x0+vicinity-1, y0,y1, z0,z1);
  boundaryStream(x0,x1,y0,y1,z0,z1, x1-vicinity+1,x1, y0,y1, z0,z1);
  boundaryStream(x0,x1,y0,y1,z0,z1, x0+vicinity,x1-vicinity, y0,y0+vicinity-1, z0,z1);
  boundaryStream(x0,x1,y0,y1,z0,z1, x0+vicinity,x1-vicinity, y1-vicinity+1,y1, z0,z1);
  boundaryStream(x0,x1,y0,y1,z0,z1, x0+vicinity,x1-vicinity, y0+vicinity,y1-vicinity, z0,z0+vicinity-1);
  boundaryStream(x0,x1,y0,y1,z0,z1, x0+vicinity,x1-vicinity, y0+vicinity,y1-vicinity, z1-vicinity+1,z1);
 }
}

/** Post-processing steps are called at the end of this method.
 * \sa collideAndStream(int,int,int,int,int,int) */
template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::collideAndStream(bool periodic) {
  collideAndStream(0, nx-1, 0, ny-1, 0, nz-1);

  if (periodic) {
    makePeriodic();
  }

  postProcess();
  getStatistics().incrementTime();
}

template<typename T, template<typename U> class Lattice>
T BlockLattice3D<T,Lattice>::computeAverageDensity (
  int x0, int x1, int y0, int y1, int z0, int z1) const
{
  T sumRho = T();
  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iZ=z0; iZ<=z1; ++iZ) {
        T rho, u[Lattice<T>::d];
        get(iX,iY,iZ).computeRhoU(rho, u);
        sumRho += rho;
      }
    }
  }
  return sumRho / (T)(x1-x0+1) / (T)(y1-y0+1) / (T)(z1-z0+1);
}

template<typename T, template<typename U> class Lattice>
T BlockLattice3D<T,Lattice>::computeAverageDensity() const {
  return computeAverageDensity(0, nx-1, 0, ny-1, 0, nz-1);
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::stripeOffDensityOffset (
  int x0, int x1, int y0, int y1, int z0, int z1, T offset )
{
  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iZ=z0; iZ<=z1; ++iZ) {
        for (int iPop=0; iPop<Lattice<T>::q; ++iPop) {
          get(iX,iY,iZ)[iPop] -= Lattice<T>::t[iPop] * offset;
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::stripeOffDensityOffset(T offset) {
  stripeOffDensityOffset(0, nx-1, 0, ny-1, 0, nz-1, offset);
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::forAll (
  int x0, int x1, int y0, int y1, int z0, int z1,
  WriteCellFunctional<T,Lattice> const& application )
{
  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iZ=z0; iZ<=z1; ++iZ) {
        application.apply( get(iX,iY,iZ) );
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::forAll(WriteCellFunctional<T,Lattice> const& application) {
  forAll(0, nx-1, 0, ny-1, 0, nz-1, application);
}


template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::addPostProcessor (
  PostProcessorGenerator3D<T,Lattice> const& ppGen )
{
  postProcessors.push_back(ppGen.generate());
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::resetPostProcessors() {
  clearPostProcessors();
  StatPPGenerator3D<T,Lattice> statPPGenerator;
  addPostProcessor(statPPGenerator);
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::clearPostProcessors() {
  typename std::vector<PostProcessor3D<T,Lattice>*>::iterator ppIt = postProcessors.begin();
  for (; ppIt != postProcessors.end(); ++ppIt) {
    delete *ppIt;
  }
  postProcessors.clear();
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::postProcess() {
  for (unsigned iPr=0; iPr<postProcessors.size(); ++iPr) {
    postProcessors[iPr] -> process(*this);
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::postProcess (
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_)
{
  for (unsigned iPr=0; iPr<postProcessors.size(); ++iPr) {
    postProcessors[iPr] -> processSubDomain(*this, x0_, x1_, y0_, y1_, z0_, z1_);
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::addLatticeCoupling (
  LatticeCouplingGenerator3D<T,Lattice> const& lcGen,
  std::vector<SpatiallyExtendedObject3D*> partners )
{
  latticeCouplings.push_back(lcGen.generate(partners));
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::executeCoupling() {
  for (unsigned iPr=0; iPr<latticeCouplings.size(); ++iPr) {
    latticeCouplings[iPr] -> process(*this);
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::executeCoupling (
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_)
{
  for (unsigned iPr=0; iPr<latticeCouplings.size(); ++iPr) {
    latticeCouplings[iPr] -> processSubDomain(*this, x0_, x1_, y0_, y1_, z0_, z1_);
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::clearLatticeCouplings() {
  typename std::vector<PostProcessor3D<T,Lattice>*>::iterator ppIt = latticeCouplings.begin();
  for (; ppIt != latticeCouplings.end(); ++ppIt) {
    delete *ppIt;
  }
  latticeCouplings.clear();
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::subscribeReductions(Reductor<T>& reductor) {
  for (unsigned iPr=0; iPr<postProcessors.size(); ++iPr) {
    postProcessors[iPr] -> subscribeReductions(*this, &reductor);
  }
}

template<typename T, template<typename U> class Lattice>
LatticeStatistics<T>& BlockLattice3D<T,Lattice>::getStatistics() {
///*
#ifdef PARALLEL_MODE_OMP
  return *statistics[omp.get_rank()];
#else
  return *statistics;
#endif
//*/
//  return *statistics;
}

template<typename T, template<typename U> class Lattice>
LatticeStatistics<T> const&
BlockLattice3D<T,Lattice>::getStatistics() const
{
///*
#ifdef PARALLEL_MODE_OMP
  return *statistics[omp.get_rank()];
#else
  return *statistics;
#endif
//*/
 // return *statistics;
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::allocateMemory() {
  // The conversions to size_t ensure 64-bit compatibility. Note that
  //   nx, ny and nz are of type int, which might by 32-bit types, even on
  //   64-bit platforms. Therefore, nx*ny*nz may lead to a type overflow.
  rawData = new Cell<T,Lattice> [(size_t)nx*(size_t)ny*(size_t)nz];
  grid    = new Cell<T,Lattice>** [(size_t)nx];
  for (int iX=0; iX<nx; ++iX) {
    grid[iX] = new Cell<T,Lattice>* [(size_t)ny];
    for (int iY=0; iY<ny; ++iY) {
      grid[iX][iY] = rawData + (size_t)nz*((size_t)iY+(size_t)ny*(size_t)iX);
    }
  }
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::releaseMemory() {
  delete [] rawData;
  for (int iX=0; iX<nx; ++iX) {
    delete [] grid[iX];
  }
  delete [] grid;
}

/** This method is slower than bulkStream(int,int,int,int), because it must
 * be verified which distribution functions are to be kept from leaving
 * the domain.
 * \sa stream(int,int,int,int)
 * \sa stream()
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::boundaryStream (
  int lim_x0, int lim_x1, int lim_y0, int lim_y1, int lim_z0, int lim_z1,
  int x0, int x1, int y0, int y1, int z0, int z1 )
{
  OLB_PRECONDITION(lim_x0>=0 && lim_x1<nx);
  OLB_PRECONDITION(lim_x1>=lim_x0);
  OLB_PRECONDITION(lim_y0>=0 && lim_y1<ny);
  OLB_PRECONDITION(lim_y1>=lim_y0);
  OLB_PRECONDITION(lim_z0>=0 && lim_z1<nz);
  OLB_PRECONDITION(lim_z1>=lim_z0);

  OLB_PRECONDITION(x0>=lim_x0 && x1<=lim_x1);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=lim_y0 && y1<=lim_y1);
  OLB_PRECONDITION(y1>=y0);
  OLB_PRECONDITION(z0>=lim_z0 && z1<=lim_z1);
  OLB_PRECONDITION(z1>=z0);

  int iX;

#ifdef PARALLEL_MODE_OMP
  //#pragma omp parallel for schedule(dynamic,1) collapse(2)
  #pragma omp for schedule(dynamic,1) collapse(2)
#endif
  for (iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iZ=z0; iZ<=z1; ++iZ) {
        for (int iPop=1; iPop<=Lattice<T>::q/2; ++iPop) {
          int nextX = iX + Lattice<T>::c[iPop][0];
          int nextY = iY + Lattice<T>::c[iPop][1];
          int nextZ = iZ + Lattice<T>::c[iPop][2];
          if ( nextX>=lim_x0 && nextX<=lim_x1 &&
               nextY>=lim_y0 && nextY<=lim_y1 &&
               nextZ>=lim_z0 && nextZ<=lim_z1 )
          {
            std::swap(grid[iX][iY][iZ][iPop+Lattice<T>::q/2],
                      grid[nextX][nextY][nextZ][iPop]);
          }
        }
      }
    }
  }
}

/** This method is faster than boundaryStream(int,int,int,int,int,int), but it
 * is erroneous when applied to boundary cells.
 * \sa stream(int,int,int,int,int,int)
 * \sa stream()
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::bulkStream (
  int x0, int x1, int y0, int y1, int z0, int z1 )
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);
  OLB_PRECONDITION(z0>=0 && z1<nz);
  OLB_PRECONDITION(z1>=z0);

  int iX;
#ifdef PARALLEL_MODE_OMP
  #pragma omp parallel for
#endif
  for (iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iZ=z0; iZ<=z1; ++iZ) {
        for (int iPop=1; iPop<=Lattice<T>::q/2; ++iPop) {
          int nextX = iX + Lattice<T>::c[iPop][0];
          int nextY = iY + Lattice<T>::c[iPop][1];
          int nextZ = iZ + Lattice<T>::c[iPop][2];
          std::swap(grid[iX][iY][iZ][iPop+Lattice<T>::q/2],
                    grid[nextX][nextY][nextZ][iPop]);
        }
      }
    }
  }
}

#ifndef PARALLEL_MODE_OMP // OpenMP parallel version is at the end
// of this file
/** This method is fast, but it is erroneous when applied to boundary
 * cells.
 * \sa collideAndStream(int,int,int,int,int,int)
 * \sa collideAndStream()
 */
template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::bulkCollideAndStream (
  int x0, int x1, int y0, int y1, int z0, int z1 )
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);
  OLB_PRECONDITION(z0>=0 && z1<nz);
  OLB_PRECONDITION(z1>=z0);
#if 0 //no cache block
  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iZ=z0; iZ<=z1; ++iZ) {
        grid[iX][iY][iZ].collide(getStatistics());
        lbHelpers<T,Lattice>::swapAndStream3D(grid, iX, iY, iZ);
      }
    }
  }
#else
int BSX=32;
//int BSX=x1-x0;
int BSY=y1-y0;
//int BSZ=z1-z0;
 for (int iX=x0; iX<=x1; iX+=BSX) {
//    for (int iY=y0; iY<=y1; iY+=BSY) {
//      for (int iZ=z0; iZ<=z1; iZ+=BSZ) {
      //if((iX+BSX>x1+1) || (iY+BSY>y1+1))
      if(iX+BSX>x1+1)
      {
	  for (int iX_=iX; iX_<x1+1; ++iX_)
          //for (int iY_=iY; iY_<y1+1; ++iY_) {
          for (int iY_=y0; iY_<y1+1; ++iY_) {
          for (int iZ_=z0; iZ_<z1+1; ++iZ_) {
             grid[iX_][iY_][iZ_].collide(getStatistics());
             lbHelpers<T,Lattice>::swapAndStream3D(grid, iX_, iY_,iZ_);
          }
        }
      }
       else
       {
	  for (int iX_=iX; iX_<iX+BSX; ++iX_)
	  //for (int iX_=x0; iX_<iX+BSX; ++iX_)
          //for (int iY_=iY; iY_<iY+BSY; ++iY_) {
          for (int iY_=y0; iY_<y1+1; ++iY_) {
           for (int iZ_=z0; iZ_<z1+1; ++iZ_) {
             grid[iX_][iY_][iZ_].collide(getStatistics());
             lbHelpers<T,Lattice>::swapAndStream3D(grid, iX_, iY_,iZ_);
	   }
         }
         }
     //  }
 //     }
     }

#endif
}
#endif  // not defined PARALLEL_MODE_OMP

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::makePeriodic() {
  static const int vicinity = Lattice<T>::vicinity;
  int maxX = getNx()-1;
  int maxY = getNy()-1;
  int maxZ = getNz()-1;
  periodicSurface(0,             vicinity-1,    0,    maxY,              0,       maxZ);
  periodicSurface(maxX-vicinity+1,     maxX,    0,    maxY,              0,       maxZ);
  periodicSurface(vicinity,      maxX-vicinity, 0,    vicinity-1,        0,       maxZ);
  periodicSurface(vicinity,      maxX-vicinity, maxY-vicinity+1, maxY,   0,       maxZ);
  periodicSurface(vicinity,      maxX-vicinity, vicinity, maxY-vicinity, 0, vicinity-1);
  periodicSurface(vicinity,      maxX-vicinity, vicinity, maxY-vicinity, maxZ-vicinity+1, maxZ);
}

template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::periodicSurface (
  int x0, int x1, int y0, int y1, int z0, int z1)
{
  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iZ=z0; iZ<=z1; ++iZ) {
        for (int iPop=1; iPop<=Lattice<T>::q/2; ++iPop) {
          int nextX = iX + Lattice<T>::c[iPop][0];
          int nextY = iY + Lattice<T>::c[iPop][1];
          int nextZ = iZ + Lattice<T>::c[iPop][2];
          if ( nextX<0 || nextX>=getNx() ||
               nextY<0 || nextY>=getNy() ||
               nextZ<0 || nextZ>=getNz() )
          {
            nextX = (nextX+getNx())%getNx();
            nextY = (nextY+getNy())%getNy();
            nextZ = (nextZ+getNz())%getNz();
            std::swap (
              grid[iX][iY][iZ]         [iPop+Lattice<T>::q/2],
              grid[nextX][nextY][nextZ][iPop] );
          }
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
DataAnalysisBase3D<T,Lattice> const& BlockLattice3D<T,Lattice>::getDataAnalysis() const {
  dataAnalysis -> reset();
  return *dataAnalysis;
}

template<typename T, template<typename U> class Lattice>
DataSerializer<T> const& BlockLattice3D<T,Lattice>::getSerializer(IndexOrdering::OrderingT ordering) const {
  delete serializer;
  serializer = new BlockLatticeSerializer3D<T,Lattice>(*this, ordering);
  return *serializer;
}

template<typename T, template<typename U> class Lattice>
DataUnSerializer<T>& BlockLattice3D<T,Lattice>::getUnSerializer(IndexOrdering::OrderingT ordering) {
  delete unSerializer;
  unSerializer = new BlockLatticeUnSerializer3D<T,Lattice>(*this, ordering);
  return *unSerializer;
}

template<typename T, template<typename U> class Lattice>
DataSerializer<T> const& BlockLattice3D<T,Lattice>::getSubSerializer (
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering ) const
{
  delete serializer;
  serializer = new BlockLatticeSerializer3D<T,Lattice> (
    *this, x0_, x1_, y0_, y1_, z0_, z1_, ordering );
  return *serializer;
}

template<typename T, template<typename U> class Lattice>
DataUnSerializer<T>& BlockLattice3D<T,Lattice>::getSubUnSerializer (
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering )
{
  delete unSerializer;
  unSerializer = new BlockLatticeUnSerializer3D<T,Lattice> (
    *this, x0_, x1_, y0_, y1_, z0_, z1_, ordering );
  return *unSerializer;
}

template<typename T, template<typename U> class Lattice>
MultiDataDistribution3D BlockLattice3D<T,Lattice>::getDataDistribution() const {
  return MultiDataDistribution3D(getNx(), getNy(), getNz());
}

template<typename T, template<typename U> class Lattice>
SpatiallyExtendedObject3D* BlockLattice3D<T,Lattice>::getComponent(int iBlock) {
  OLB_PRECONDITION( iBlock==0 );
  return this;
}

template<typename T, template<typename U> class Lattice>
SpatiallyExtendedObject3D const* BlockLattice3D<T,Lattice>::getComponent(int iBlock) const {
  OLB_PRECONDITION( iBlock==0 );
  return this;
}

template<typename T, template<typename U> class Lattice>
multiPhysics::MultiPhysicsId BlockLattice3D<T,Lattice>::getMultiPhysicsId() const {
  return multiPhysics::getMultiPhysicsBlockId<T,Lattice>();
}



////////// class BlockLatticeSerializer3D ////////////////////////////

template<typename T, template<typename U> class Lattice>
BlockLatticeSerializer3D<T,Lattice>::BlockLatticeSerializer3D (
  BlockLattice3D<T,Lattice> const& blockLattice_, IndexOrdering::OrderingT ordering_ )
  : blockLattice(blockLattice_), ordering(ordering_),
    x0(0), x1(blockLattice.getNx()-1), y0(0), y1(blockLattice.getNy()-1), z0(0), z1(blockLattice.getNz()-1),
    iX(x0), iY(y0), iZ(z0),
    sizeOfCell(Lattice<T>::q + Lattice<T>::ExternalField::numScalars)
{ }

template<typename T, template<typename U> class Lattice>
BlockLatticeSerializer3D<T,Lattice>::BlockLatticeSerializer3D (
  BlockLattice3D<T,Lattice> const& blockLattice_,
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering_ )
  : blockLattice(blockLattice_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_), z0(z0_), z1(z1_),
    iX(x0), iY(y0), iZ(z0),
    sizeOfCell(Lattice<T>::q + Lattice<T>::ExternalField::numScalars)
{ }

template<typename T, template<typename U> class Lattice>
size_t BlockLatticeSerializer3D<T,Lattice>::getSize() const {
  return (size_t)(x1-x0+1) * (size_t)(y1-y0+1) * (size_t)(z1-z0+1) * (size_t)sizeOfCell;
}

template<typename T, template<typename U> class Lattice>
const T* BlockLatticeSerializer3D<T,Lattice>::getNextDataBuffer(size_t& bufferSize) const {
  OLB_PRECONDITION( !isEmpty() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    bufferSize = (size_t)(z1-z0+1)*(size_t)sizeOfCell;
    buffer.resize(bufferSize);
    for (iZ=z0; iZ<=z1; ++iZ) {
      blockLattice.get(iX,iY,iZ).serialize(&buffer[(size_t)(iZ-z0)*(size_t)sizeOfCell]);
    }
    ++iY;
    if (iY > y1) {
      iY = 0;
      ++iX;
    }
  }
  else {
    bufferSize = (size_t)(x1-x0+1)*(size_t)sizeOfCell;
    buffer.resize(bufferSize);
    for (iX=x0; iX<=x1; ++iX) {
      blockLattice.get(iX,iY,iZ).serialize(&buffer[(size_t)(iX-x0)*(size_t)sizeOfCell]);
    }
    ++iY;
    if (iY > y1) {
      iY = 0;
      ++iZ;
    }
  }
  return &buffer[0];
}

template<typename T, template<typename U> class Lattice>
bool BlockLatticeSerializer3D<T,Lattice>::isEmpty() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iZ > z1;
  }
}



////////// class BlockLatticeUnSerializer3D ////////////////////////////

template<typename T, template<typename U> class Lattice>
BlockLatticeUnSerializer3D<T,Lattice>::BlockLatticeUnSerializer3D (
  BlockLattice3D<T,Lattice>& blockLattice_, IndexOrdering::OrderingT ordering_ )
  : blockLattice(blockLattice_), ordering(ordering_),
    x0(0), x1(blockLattice.getNx()-1), y0(0), y1(blockLattice.getNy()-1), z0(0), z1(blockLattice.getNz()-1),
    iX(x0), iY(y0), iZ(z0),
    sizeOfCell(Lattice<T>::q + Lattice<T>::ExternalField::numScalars)
{ }

template<typename T, template<typename U> class Lattice>
BlockLatticeUnSerializer3D<T,Lattice>::BlockLatticeUnSerializer3D (
  BlockLattice3D<T,Lattice>& blockLattice_,
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering_ )
  : blockLattice(blockLattice_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_), z0(z0_), z1(z1_),
    iX(x0), iY(y0), iZ(z0),
    sizeOfCell(Lattice<T>::q + Lattice<T>::ExternalField::numScalars)
{ }

template<typename T, template<typename U> class Lattice>
size_t BlockLatticeUnSerializer3D<T,Lattice>::getSize() const {
  return (size_t)(x1-x0+1) * (size_t)(y1-y0+1) * (size_t)(z1-z0+1) * (size_t)sizeOfCell;
}

template<typename T, template<typename U> class Lattice>
T* BlockLatticeUnSerializer3D<T,Lattice>::getNextDataBuffer(size_t& bufferSize) {
  OLB_PRECONDITION( !isFull() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    bufferSize = (size_t)(z1-z0+1)*(size_t)sizeOfCell;
  }
  else {
    bufferSize = (size_t)(x1-x0+1)*(size_t)sizeOfCell;
  }
  buffer.resize(bufferSize);
  return &buffer[0];
}

template<typename T, template<typename U> class Lattice>
void BlockLatticeUnSerializer3D<T,Lattice>::commitData() {
  OLB_PRECONDITION( !isFull() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    for (iZ=z0; iZ<=z1; ++iZ) {
      blockLattice.get(iX,iY,iZ).unSerialize(&buffer[(iZ-z0)*sizeOfCell]);
    }
    ++iY;
    if (iY > y1) {
      iY = 0;
      ++iX;
    }
  }
  else {
    for (iX=x0; iX<=x1; ++iX) {
      blockLattice.get(iX,iY,iZ).unSerialize(&buffer[(iX-x0)*sizeOfCell]);
    }
    ++iY;
    if (iY > y1) {
      iY = 0;
      ++iZ;
    }
  }
}

template<typename T, template<typename U> class Lattice>
bool BlockLatticeUnSerializer3D<T,Lattice>::isFull() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iZ > z1;
  }
}



//// OpenMP implementation of the method bulkCollideAndStream,
//   by Mathias Krause                                         ////
#ifdef PARALLEL_MODE_OMP
template<typename T, template<typename U> class Lattice>
void BlockLattice3D<T,Lattice>::bulkCollideAndStream (
  int x0, int x1, int y0, int y1, int z0, int z1 )
{
  OLB_PRECONDITION(x0>=0 && x1<nx);
  OLB_PRECONDITION(x1>=x0);
  OLB_PRECONDITION(y0>=0 && y1<ny);
  OLB_PRECONDITION(y1>=y0);
  OLB_PRECONDITION(z0>=0 && z1<nz);
  OLB_PRECONDITION(z1>=z0);

  if (omp.get_size() <= x1-x0+1) {
//    #pragma omp parallel 
    {
      loadBalancer loadbalance(omp.get_rank(), omp.get_size(), x1-x0+1, x0);
      int iX, iY, iZ, iPop;

      iX=loadbalance.get_firstGlobNum();
      
      for (int iY=y0; iY<=y1; ++iY) {
        for (int iZ=z0; iZ<=z1; ++iZ) {
          
          grid[iX][iY][iZ].collide(getStatistics());
          grid[iX][iY][iZ].revert();
        }
      }

      for (iX=loadbalance.get_firstGlobNum()+1; iX<=loadbalance.get_lastGlobNum(); ++iX) {
        for (iY=y0; iY<=y1; ++iY) {
          for (iZ=z0; iZ<=z1; ++iZ) {
            grid[iX][iY][iZ].collide(getStatistics());
            /** The method beneath doesnt work with Intel
             *  compiler 9.1044 and 9.1046 for Itanium prozessors
             *    lbHelpers<T,Lattice>::swapAndStream3D(grid, iX, iY, iZ);
             *  Therefore we use:
             */
            int half = Lattice<T>::q/2;
            for (int iPop=1; iPop<=half; ++iPop) {
              int nextX = iX + Lattice<T>::c[iPop][0];
              int nextY = iY + Lattice<T>::c[iPop][1];
              int nextZ = iZ + Lattice<T>::c[iPop][2];
              T fTmp                          = grid[iX][iY][iZ][iPop];
              grid[iX][iY][iZ][iPop]          = grid[iX][iY][iZ][iPop+half];
              grid[iX][iY][iZ][iPop+half]     = grid[nextX][nextY][nextZ][iPop];
              grid[nextX][nextY][nextZ][iPop] = fTmp;
            }
          }
        }
      }

      #pragma omp barrier
      iX=loadbalance.get_firstGlobNum();
      for (iY=y0; iY<=y1; ++iY) {
        for (iZ=z0; iZ<=z1; ++iZ) {
          for (iPop=1; iPop<=Lattice<T>::q/2; ++iPop) {
            int nextX = iX + Lattice<T>::c[iPop][0];
            int nextY = iY + Lattice<T>::c[iPop][1];
            int nextZ = iZ + Lattice<T>::c[iPop][2];
            std::swap(grid[iX][iY][iZ][iPop+Lattice<T>::q/2],
                      grid[nextX][nextY][nextZ][iPop]);
          }
        }
      }
    }
  }
  else {
    for (int iX=x0; iX<=x1; ++iX) {
      for (int iY=y0; iY<=y1; ++iY) {
        for (int iZ=z0; iZ<=z1; ++iZ) {
          grid[iX][iY][iZ].collide(getStatistics());
          lbHelpers<T,Lattice>::swapAndStream3D(grid, iX, iY, iZ);
        }
      }
    }
  }
}

#endif // defined PARALLEL_MODE_OMP

}  // namespace olb

#endif
