/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006-2008 Jonas Latt
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
 * The dynamics of a 3D block lattice -- header file.
 */
#ifndef BLOCK_LATTICE_3D_H
#define BLOCK_LATTICE_3D_H

#include <vector>
#include "olbDebug.h"
#include "postProcessing.h"
#include "dataFields3D.h"
#include "blockStructure3D.h"
#include "dataAnalysisBase3D.h"
#include "blockGeometry3D.h"
#include "multiPhysics.h"
#include "latticeStatistics.h"


/// All OpenLB code is contained in this namespace.
namespace olb {

template<typename T, template<typename U> class Lattice> struct Dynamics;
template<typename T, template<typename U> class Lattice> class Cell;

template<typename T, template<typename U> class Lattice> class DataAnalysis3D;

template<typename T, template<typename U> class Lattice> class BlockLatticeSerializer3D;
template<typename T, template<typename U> class Lattice> class BlockLatticeUnSerializer3D;

/// A regular lattice for highly efficient 3D LB dynamics.
/** A block lattice contains a regular array of Cell objects and
 * some useful methods to execute the LB dynamics on the lattice.
 *
 * This class is not intended to be derived from.
 */
template<typename T, template<typename U> class Lattice>
class BlockLattice3D : public BlockStructure3D<T,Lattice> {
public:
  typedef std::vector<PostProcessor3D<T,Lattice>*> PostProcVector;
public:
  /// Construction of an nx_ by ny_ by nz_ lattice
  BlockLattice3D(int nx_, int ny_, int nz_);
  /// Destruction of the lattice
  ~BlockLattice3D();
  /// Copy construction
  BlockLattice3D(BlockLattice3D<T,Lattice> const& rhs);
  /// Copy assignment
  BlockLattice3D& operator=(BlockLattice3D<T,Lattice> const& rhs);
  /// Swap the content of two BlockLattices
  void swap(BlockLattice3D& rhs);
public:
  /// Read access to lattice width
  virtual int getNx() const { return nx; }
  /// Read access to lattice height
  virtual int getNy() const { return ny; }
  /// Read access to lattice depth
  virtual int getNz() const { return nz; }
  /// Read/write access to lattice cells
  virtual Cell<T,Lattice>& get(int iX, int iY, int iZ) {
    OLB_PRECONDITION(iX<nx);
    OLB_PRECONDITION(iY<ny);
    OLB_PRECONDITION(iZ<nz);
    return grid[iX][iY][iZ];
  }
  /// Read only access to lattice cells
  virtual Cell<T,Lattice> const& get(int iX, int iY, int iZ) const {
    OLB_PRECONDITION(iX<nx);
    OLB_PRECONDITION(iY<ny);
    OLB_PRECONDITION(iZ<nz);
    return grid[iX][iY][iZ];
  }
  /// Initialize the lattice cells to become ready for simulation
  virtual void initialize();
  /// Define the dynamics on a 3D sub-box
  virtual void defineDynamics (
    int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
    Dynamics<T,Lattice>* dynamics );
  /// Define the dynamics on a lattice site
  virtual void defineDynamics(int iX, int iY, int iZ, Dynamics<T,Lattice>* dynamics);
  /// Define the dynamics by material
  virtual void defineDynamics(BlockGeometry3D& blockGeometry, int material, Dynamics<T,Lattice>* dynamics);
  /// Define the dynamics by material on a 3D sub-box
  virtual void defineDynamics(BlockGeometry3D& blockGeometry, int material, int x0_, int x1_, int y0_, int y1_, int z0_, int z1_, Dynamics<T,Lattice>* dynamics);
  /// Specify whether statistics measurements are done on a rect. domain
  virtual void specifyStatisticsStatus (
    int x0_, int x1_, int y0_, int y1_, int z0_, int z1_, bool status );
  /// Apply collision step to a 3D sub-box
  virtual void collide(int x0_, int x1_, int y0_, int y1_,
                       int z0_, int z1_);
  /// Apply collision step to the whole domain
  virtual void collide();
  /// Apply collision step to a rectangular domain, with fixed velocity
  virtual void staticCollide(int x0_, int x1_, int y0_, int y1_,
                             int z0_, int z1_, TensorFieldBase3D<T,3> const& u);
  /// Apply collision step to the whole domain, with fixed velocity
  virtual void staticCollide(TensorFieldBase3D<T,3> const& u);
  /// Apply streaming step to a 3D sub-box
  virtual void stream(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_);
  /// Apply streaming step to the whole domain
  virtual void stream(bool periodic=false);
  /// Apply first collision, then streaming step to a 3D sub-box
  virtual void collideAndStream(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_);
  /// Apply first collision, then streaming step to the whole domain
  virtual void collideAndStream(bool periodic=false);
  /// Compute the average density within a rectangular domain
  virtual T computeAverageDensity(int x0_, int x1_, int y0_, int y1_,
                                  int z0_, int z1_ ) const;
  /// Compute the average density within the whole domain
  virtual T computeAverageDensity() const;
  /// Subtract a constant offset from the density within the whole domain
  virtual void stripeOffDensityOffset (
    int x0_, int x1_, int y0_, int y1_, int z0_, int z1_, T offset );
  /// Subtract a constant offset from the density within a rect. domain
  virtual void stripeOffDensityOffset(T offset);
  /// Apply an operation to all cells of a sub-domain
  virtual void forAll(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
                      WriteCellFunctional<T,Lattice> const& application);
  /// Apply an operation to all cells
  virtual void forAll(WriteCellFunctional<T,Lattice> const& application);
  /// Add a non-local post-processing step
  virtual void addPostProcessor (
    PostProcessorGenerator3D<T,Lattice> const& ppGen );
  /// Clean up all non-local post-processing steps
  virtual void resetPostProcessors();
  /// Execute post-processing on a sub-lattice
  virtual void postProcess(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_);
  /// Execute post-processing steps
  virtual void postProcess();
  /// Add a non-local post-processing step
  virtual void addLatticeCoupling (
    LatticeCouplingGenerator3D<T,Lattice> const& lcGen,
    std::vector<SpatiallyExtendedObject3D*> partners );
  /// Execute couplings on a sub-lattice
  virtual void executeCoupling(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_);
  /// Execute couplings steps
  virtual void executeCoupling();
  /// Subscribe postProcessors for reduction operations
  virtual void subscribeReductions(Reductor<T>& reductor);
  /// Return a handle to the LatticeStatistics object
  virtual LatticeStatistics<T>& getStatistics();
  /// Return a constant handle to the LatticeStatistics object
  virtual LatticeStatistics<T> const& getStatistics() const;
  /// Return a class for analysis of the numerical data
  virtual DataAnalysisBase3D<T,Lattice> const& getDataAnalysis() const;
  /// Get a serializer to flush the full lattice content
  virtual DataSerializer<T> const& getSerializer(IndexOrdering::OrderingT ordering) const;
  /// Get an UnSerializer to read the full lattice content
  virtual DataUnSerializer<T>& getUnSerializer(IndexOrdering::OrderingT ordering);
  /// Get a serializer to flush a sub-domain of the lattice
  virtual DataSerializer<T> const& getSubSerializer (
    int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
    IndexOrdering::OrderingT ordering ) const;
  /// Get a serializer to read a sub-domain of the lattice
  virtual DataUnSerializer<T>& getSubUnSerializer (
    int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
    IndexOrdering::OrderingT ordering );
  virtual MultiDataDistribution3D getDataDistribution() const;
  virtual SpatiallyExtendedObject3D* getComponent(int iBlock);
  virtual SpatiallyExtendedObject3D const* getComponent(int iBlock) const;
  virtual multiPhysics::MultiPhysicsId getMultiPhysicsId() const;
public:
  /// Apply streaming step to bulk (non-boundary) cells
  void bulkStream(int x0, int x1, int y0, int y1, int z0, int z1);
  /// Apply streaming step to boundary cells
  void boundaryStream (
    int lim_x0, int lim_x1, int lim_y0, int lim_y1,
    int lim_z0, int lim_z1,
    int x0, int x1, int y0, int y1, int z0, int z1 );
  /// Apply collision and streaming step to bulk (non-boundary) cells
  void bulkCollideAndStream(int x0, int x1, int y0, int y1, int z0, int z1);
private:
  /// Helper method for memory allocation
  void allocateMemory();
  /// Helper method for memory de-allocation
  void releaseMemory();
  /// Release memory for post processors
  void clearPostProcessors();
  /// Release memory for post processors
  void clearLatticeCouplings();
  /// Make the lattice periodic in all directions
  void makePeriodic();
private:
  void periodicSurface(int x0, int x1, int y0, int y1, int z0, int z1);
private:
  int                  nx, ny, nz;
  Cell<T,Lattice>      *rawData;
  Cell<T,Lattice>      ***grid;
  PostProcVector       postProcessors, latticeCouplings;
///*
#ifdef PARALLEL_MODE_OMP
  LatticeStatistics<T> **statistics;
#else
  LatticeStatistics<T> *statistics;
#endif
//*/
//  LatticeStatistics<T> *statistics;
  mutable BlockLatticeSerializer3D<T,Lattice>* serializer;
  mutable BlockLatticeUnSerializer3D<T,Lattice>* unSerializer;
  DataAnalysis3D<T,Lattice> *dataAnalysis;
};

template<typename T, template<typename U> class Lattice>
class BlockLatticeSerializer3D : public DataSerializer<T> {
public:
  BlockLatticeSerializer3D(BlockLattice3D<T,Lattice> const& blockLattice_,
                           IndexOrdering::OrderingT ordering_);
  BlockLatticeSerializer3D(BlockLattice3D<T,Lattice> const& blockLattice_,
                           int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
                           IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual const T* getNextDataBuffer(size_t& bufferSize) const;
  virtual bool isEmpty() const;
private:
  BlockLattice3D<T,Lattice> const& blockLattice;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1, z0, z1;
  mutable std::vector<T> buffer;
  mutable int iX, iY, iZ;
  int sizeOfCell;
};

template<typename T, template<typename U> class Lattice>
class BlockLatticeUnSerializer3D : public DataUnSerializer<T> {
public:
  BlockLatticeUnSerializer3D(BlockLattice3D<T,Lattice>& blockLattice_,
                             IndexOrdering::OrderingT ordering_);
  BlockLatticeUnSerializer3D(BlockLattice3D<T,Lattice>& blockLattice_,
                             int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
                             IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual T* getNextDataBuffer(size_t& bufferSize);
  virtual void commitData();
  virtual bool isFull() const;
private:
  BlockLattice3D<T,Lattice>& blockLattice;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1, z0, z1;
  mutable std::vector<T> buffer;
  mutable int iX, iY, iZ;
  int sizeOfCell;
};

}  // namespace olb

#endif
