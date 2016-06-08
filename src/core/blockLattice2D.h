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
 * The dynamics of a 2D block lattice -- header file.
 */
#ifndef BLOCK_LATTICE_2D_H
#define BLOCK_LATTICE_2D_H

#include <vector>
#include "olbDebug.h"
#include "postProcessing.h"
#include "dataFields2D.h"
#include "blockStructure2D.h"
#include "dataAnalysisBase2D.h"
#include "multiPhysics.h"
#include "blockGeometryStatistics2D.h"
#include "latticeStatistics.h"



/// All OpenLB code is contained in this namespace.
namespace olb {

template<typename T, template<typename U> class Lattice> struct Dynamics;
template<typename T, template<typename U> class Lattice> class Cell;

template<typename T, template<typename U> class Lattice> class DataAnalysis2D;

template<typename T, template<typename U> class Lattice> class BlockLatticeSerializer2D;
template<typename T, template<typename U> class Lattice> class BlockLatticeUnSerializer2D;

/// A regular lattice for highly efficient 2D LB dynamics.
/** A block lattice contains a regular array of Cell objects and
 * some useful methods to execute the LB dynamics on the lattice.
 *
 * This class is not intended to be derived from.
 */
template<typename T, template<typename U> class Lattice>
class BlockLattice2D : public BlockStructure2D<T,Lattice> {
public:
  typedef std::vector<PostProcessor2D<T,Lattice>*> PostProcVector;
public:
  /// Construction of an nx_ by ny_ lattice
  BlockLattice2D(int nx_, int ny_);
  /// Destruction of the lattice
  ~BlockLattice2D();
  /// Copy construction
  BlockLattice2D(BlockLattice2D<T,Lattice> const& rhs);
  /// Copy assignment
  BlockLattice2D& operator=(BlockLattice2D<T,Lattice> const& rhs);
  /// Swap the content of two BlockLattices
  void swap(BlockLattice2D& rhs);
public:
  /// Read access to lattice width
  virtual int getNx() const { return nx; }
  /// Read access to lattice height
  virtual int getNy() const { return ny; }
  /// Read/write access to lattice cells
  virtual Cell<T,Lattice>& get(int iX, int iY) {
    OLB_PRECONDITION(iX<nx);
    OLB_PRECONDITION(iY<ny);
    return grid[iX][iY];
  }
  /// Read only access to lattice cells
  virtual Cell<T,Lattice> const& get(int iX, int iY) const {
    OLB_PRECONDITION(iX<nx);
    OLB_PRECONDITION(iY<ny);
    return grid[iX][iY];
  }
  /// Initialize the lattice cells to become ready for simulation
  virtual void initialize();
  /// Define the dynamics on a rectangular domain
  virtual void defineDynamics (int x0, int x1, int y0, int y1,
                               Dynamics<T,Lattice>* dynamics );
  /// Define the dynamics on a lattice site
  virtual void defineDynamics(int iX, int iY, Dynamics<T,Lattice>* dynamics);
  /// Define the dynamics by material
  virtual void defineDynamics(BlockGeometryStatistics2D* blockGeoSta, Dynamics<T,Lattice>* dynamics, int material);
  /// Define the dynamics by material on a 2D sub-box
  virtual void defineDynamics(BlockGeometryStatistics2D* blockGeoSta, int x0_, int x1_, int y0_, int y1_, Dynamics<T,Lattice>* dynamics, int material);
  /// Specify whether statistics measurements are done on given rect. domain
  virtual void specifyStatisticsStatus (int x0, int x1, int y0, int y1,
                                        bool status );
  /// Apply collision step to a rectangular domain
  virtual void collide(int x0, int x1, int y0, int y1);
  /// Apply collision step to the whole domain
  virtual void collide();
  /// Apply collision step to a rectangular domain, with fixed velocity
  virtual void staticCollide (int x0, int x1, int y0, int y1,
                              TensorFieldBase2D<T,2> const& u);
  /// Apply collision step to the whole domain, with fixed velocity
  virtual void staticCollide(TensorFieldBase2D<T,2> const& u);
  /// Apply streaming step to a rectangular domain
  virtual void stream(int x0, int x1, int y0, int y1);
  /// Apply streaming step to the whole domain
  virtual void stream(bool periodic=false);
  /// Apply first collision, then streaming step to a rectangular domain
  virtual void collideAndStream(int x0, int x1, int y0, int y1);
  /// Apply first collision, then streaming step to the whole domain
  virtual void collideAndStream(bool periodic=false);
  /// Compute the average density within a rectangular domain
  virtual T computeAverageDensity(int x0, int x1, int y0, int y1) const;
  /// Compute the average density within the whole domain
  virtual T computeAverageDensity() const;
  /// Subtract a constant offset from the density within the whole domain
  virtual void stripeOffDensityOffset (
    int x0, int x1, int y0, int y1, T offset );
  /// Subtract a constant offset from the density within a rect. domain
  virtual void stripeOffDensityOffset(T offset);
  /// Apply an operation to all cells of a sub-domain
  virtual void forAll(int x0_, int x1_, int y0_, int y1_,
                      WriteCellFunctional<T,Lattice> const& application);
  /// Apply an operation to all cells
  virtual void forAll(WriteCellFunctional<T,Lattice> const& application);
  /// Add a non-local post-processing step
  virtual void addPostProcessor (
    PostProcessorGenerator2D<T,Lattice> const& ppGen );
  /// Clean up all non-local post-processing steps
  virtual void resetPostProcessors();
  /// Execute post-processing on a sub-lattice
  virtual void postProcess(int x0_, int x1_, int y0_, int y1_);
  /// Execute post-processing steps
  virtual void postProcess();
  /// Add a non-local post-processing step which couples together lattices
  virtual void addLatticeCoupling (
    LatticeCouplingGenerator2D<T,Lattice> const& lcGen,
    std::vector<SpatiallyExtendedObject2D*> partners );
  /// Execute couplings on a sub-lattice
  virtual void executeCoupling(int x0_, int x1_, int y0_, int y1_);
  /// Execute couplings
  virtual void executeCoupling();
  /// Subscribe postProcessors for reduction operations
  virtual void subscribeReductions(Reductor<T>& reductor);
  /// Return a handle to the LatticeStatistics object
  virtual LatticeStatistics<T>& getStatistics();
  /// Return a constant handle to the LatticeStatistics object
  virtual LatticeStatistics<T> const& getStatistics() const;
  /// Return a class for analysis of the numerical data
  virtual DataAnalysisBase2D<T,Lattice> const& getDataAnalysis() const;
  /// Get a serializer to flush the full lattice content
  virtual DataSerializer<T> const& getSerializer(IndexOrdering::OrderingT ordering) const;
  /// Get an UnSerializer to read the full lattice content
  virtual DataUnSerializer<T>& getUnSerializer(IndexOrdering::OrderingT ordering);
  /// Get a serializer to flush a sub-domain of the lattice
  virtual DataSerializer<T> const& getSubSerializer (
    int x0_, int x1_, int y0_, int y1_,
    IndexOrdering::OrderingT ordering ) const;
  /// Get a serializer to read a sub-domain of the lattice
  virtual DataUnSerializer<T>& getSubUnSerializer (
    int x0_, int x1_, int y0_, int y1_,
    IndexOrdering::OrderingT ordering );
  virtual MultiDataDistribution2D getDataDistribution() const;
  virtual SpatiallyExtendedObject2D* getComponent(int iBlock);
  virtual SpatiallyExtendedObject2D const* getComponent(int iBlock) const;
  virtual multiPhysics::MultiPhysicsId getMultiPhysicsId() const;
public:
  /// Apply streaming step to bulk (non-boundary) cells
  void bulkStream(int x0, int x1, int y0, int y1);
  /// Apply streaming step to boundary cells
  void boundaryStream (
    int lim_x0, int lim_x1, int lim_y0, int lim_y1,
    int x0, int x1, int y0, int y1 );
  /// Apply collision and streaming step to bulk (non-boundary) cells
  void bulkCollideAndStream(int x0, int x1, int y0, int y1);
private:
  /// Helper method for memory allocation
  void allocateMemory();
  /// Helper method for memory de-allocation
  void releaseMemory();
  /// Release memory for post processors
  void clearPostProcessors();
  /// Release memory for lattice couplings
  void clearLatticeCouplings();
  void periodicEdge(int x0, int x1, int y0, int y1);
  void makePeriodic();
private:
  int                  nx, ny;
  Cell<T,Lattice>      *rawData;
  Cell<T,Lattice>      **grid;
  PostProcVector       postProcessors, latticeCouplings;
#ifdef PARALLEL_MODE_OMP
  LatticeStatistics<T> **statistics;
#else
  LatticeStatistics<T> *statistics;
#endif
  mutable BlockLatticeSerializer2D<T,Lattice>* serializer;
  mutable BlockLatticeUnSerializer2D<T,Lattice>* unSerializer;
  DataAnalysis2D<T,Lattice> *dataAnalysis;
};


template<typename T, template<typename U> class Lattice>
class BlockLatticeSerializer2D : public DataSerializer<T> {
public:
  BlockLatticeSerializer2D(BlockLattice2D<T,Lattice> const& blockLattice_,
                           IndexOrdering::OrderingT ordering_);
  BlockLatticeSerializer2D(BlockLattice2D<T,Lattice> const& blockLattice_,
                           int x0_, int x1_, int y0_, int y1_,
                           IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual const T* getNextDataBuffer(size_t& bufferSize) const;
  virtual bool isEmpty() const;
private:
  BlockLattice2D<T,Lattice> const& blockLattice;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1;
  mutable std::vector<T> buffer;
  mutable int iX, iY;
  int sizeOfCell;
};

template<typename T, template<typename U> class Lattice>
class BlockLatticeUnSerializer2D : public DataUnSerializer<T> {
public:
  BlockLatticeUnSerializer2D(BlockLattice2D<T,Lattice>& blockLattice_,
                             IndexOrdering::OrderingT ordering_);
  BlockLatticeUnSerializer2D(BlockLattice2D<T,Lattice>& blockLattice_,
                             int x0_, int x1_, int y0_, int y1_,
                             IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual T* getNextDataBuffer(size_t& bufferSize);
  virtual void commitData();
  virtual bool isFull() const;
private:
  BlockLattice2D<T,Lattice>& blockLattice;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1;
  mutable std::vector<T> buffer;
  mutable int iX, iY;
  int sizeOfCell;
};

}  // namespace olb

#endif
