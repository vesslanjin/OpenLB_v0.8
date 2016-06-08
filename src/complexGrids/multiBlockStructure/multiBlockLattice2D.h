/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007, 2008 Jonas Latt
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
 * A 2D multiblock lattice -- header file.
 */
#ifndef MULTI_BLOCK_LATTICE_2D_H
#define MULTI_BLOCK_LATTICE_2D_H

#include "core/blockLattice2D.h"
#include "core/cell.h"
#include "core/dynamics.h"
#include "multiBlockStatistics.h"
#include "multiBlockHandler2D.h"
#include "multiSerializer2D.h"
#include "core/dataAnalysisBase2D.h"
#include <vector>


namespace olb {

template<typename T, template<typename U> class Lattice> class MultiDataAnalysis2D;

template<typename T, template<typename U> class Lattice> class MultiBlockSerializerPolicy2D;
template<typename T, template<typename U> class Lattice> class MultiBlockUnSerializerPolicy2D;

/// A complex BlockStructure, itself decomposed into smaller components.
/** This extensible class can be used for example for cache-optimized
 * lattices, irregular domains (no memory allocation in areas exterior to
 * the domain) and parallel lattices. The actual behavior of the lattice
 * is parametrizable by a multiBlockHandler instance, which is given to
 * the constructor.
 *
 * The MultiBlockLattice does not itself possess PostProcessors. The Post-
 * Processors are delegated to the respective BlockStructures.
 */
template<typename T, template<typename U> class Lattice>
class MultiBlockLattice2D : public BlockStructure2D<T,Lattice> {
public:
  MultiBlockLattice2D(MultiDataDistribution2D const& dataDistribution_);
  ~MultiBlockLattice2D();
  MultiBlockLattice2D(MultiBlockLattice2D const& rhs);
  MultiBlockLattice2D<T,Lattice>& operator=(MultiBlockLattice2D<T,Lattice> const& rhs);
  void swap(MultiBlockLattice2D<T,Lattice>& rhs);

  virtual int getNx() const { return multiBlockHandler->getNx(); }
  virtual int getNy() const { return multiBlockHandler->getNy(); }
  virtual Cell<T,Lattice>& get(int iX, int iY);
  virtual Cell<T,Lattice> const& get(int iX, int iY) const;
  virtual void initialize();
  virtual void defineDynamics(int x0_, int x1_, int y0_, int y1_, Dynamics<T,Lattice>* dynamics);
  virtual void defineDynamics(int iX, int iY, Dynamics<T,Lattice>* dynamics);
  virtual void defineDynamics(BlockGeometryStatistics2D* blockGeoSta,
                              int x0_, int x1_, int y0_, int y1_, Dynamics<T,Lattice>* dynamics, int material);
  virtual void defineDynamics(BlockGeometryStatistics2D* blockGeoSta,
                              Dynamics<T, Lattice>* dynamics, int material);

  virtual void specifyStatisticsStatus(int x0_, int x1_, int y0_, int y1_, bool status);
  virtual void collide(int x0_, int x1_, int y0_, int y1_);
  virtual void collide();
  virtual void staticCollide (int x0, int x1, int y0, int y1, TensorFieldBase2D<T,2> const& u);
  virtual void staticCollide (TensorFieldBase2D<T,2> const& u);
  virtual void stream(int x0_, int x1_, int y0_, int y1_);
  virtual void stream(bool periodic=false);
  virtual void collideAndStream(int x0_, int x1_, int y0_, int y1_);
  virtual void collideAndStream(bool periodic=false);
  virtual T computeAverageDensity(int x0_, int x1_, int y0_, int y1_) const;
  virtual T computeAverageDensity() const;
  virtual void stripeOffDensityOffset (
    int x0_, int x1_, int y0_, int y1_, T offset );
  virtual void stripeOffDensityOffset(T offset);
  virtual void forAll(int x0_, int x1_, int y0_, int y1_,
                      WriteCellFunctional<T,Lattice> const& application);
  virtual void forAll(WriteCellFunctional<T,Lattice> const& application);
  virtual void addPostProcessor (
    PostProcessorGenerator2D<T,Lattice> const& ppGen );
  virtual void resetPostProcessors();
  virtual void postProcess(int x0_, int x1_, int y0_, int y1_);
  virtual void postProcess();
  virtual void addLatticeCoupling (
    LatticeCouplingGenerator2D<T,Lattice> const& lcGen,
    std::vector<SpatiallyExtendedObject2D*> partners );
  virtual void executeCoupling(int x0_, int x1_, int y0_, int y1_);
  virtual void executeCoupling();
  virtual void subscribeReductions(Reductor<T>& reductor);
  virtual LatticeStatistics<T>& getStatistics();
  virtual LatticeStatistics<T> const& getStatistics() const;
  virtual DataAnalysisBase2D<T,Lattice> const& getDataAnalysis() const;
  virtual DataSerializer<T> const& getSerializer(IndexOrdering::OrderingT ordering) const;
  virtual DataUnSerializer<T>& getUnSerializer(IndexOrdering::OrderingT ordering);
  virtual DataSerializer<T> const& getSubSerializer (
    int x0_, int x1_, int y0_, int y1_,
    IndexOrdering::OrderingT ordering ) const;
  virtual DataUnSerializer<T>& getSubUnSerializer (
    int x0_, int x1_, int y0_, int y1_,
    IndexOrdering::OrderingT ordering );
  virtual MultiDataDistribution2D getDataDistribution() const;
  virtual SpatiallyExtendedObject2D* getComponent(int iBlock);
  virtual SpatiallyExtendedObject2D const* getComponent(int iBlock) const;
  virtual multiPhysics::MultiPhysicsId getMultiPhysicsId() const;
private:
  std::vector<int> const& getRelevantBlocks() const;
public:
  void toggleInternalStatistics(bool statisticsOn_);
  void togglePeriodicCommunication(bool periodicCommunicationOn_);
  bool isInternalStatisticsOn() const;
  bool isPeriodicCommunicationOn() const;
public:
  MultiDataDistribution2D const& getMultiData() const;
  std::vector<BlockLattice2D<T,Lattice>*> getBlockLattices();
  const std::vector<BlockLattice2D<T,Lattice>*> getBlockLattices() const;
private:
  void allocateBlocks();
  void postProcessMultiBlock();
  void reduceStatistics();
  void eliminateStatisticsInEnvelope();
private:
  BlockParameters2D const& getParameters(int iParam) const;
  Overlap2D const& getNormalOverlap(int iOverlap) const;
  Overlap2D const& getPeriodicOverlap(int iOverlap) const;
  int getNumRelevantBlocks() const;
private:
  mutable int locatedBlock; ///< for optimization, keep the last index found
  MultiBlockHandler2D<T,Lattice>* multiBlockHandler;
  std::vector<BlockLattice2D<T,Lattice>*> blockLattices;
  LatticeStatistics<T>* statistics;
  bool statisticsOn;
  bool periodicCommunicationOn;
  MultiBlockReductor<T> reductor;
  NoDynamics<T,Lattice> dummyDynamics;
  mutable std::vector<Cell<T,Lattice>*> returnCells;
  mutable std::vector<Cell<T,Lattice> const*> constReturnCells;
  mutable MultiSerializer2D<T>* serializer;
  mutable MultiUnSerializer2D<T>* unSerializer;
  MultiBlockSerializerPolicy2D<T,Lattice> serializerPolicy;
  MultiBlockUnSerializerPolicy2D<T,Lattice> unSerializerPolicy;
  MultiDataAnalysis2D<T,Lattice> *dataAnalysis;
};

template<typename T, template<typename U> class Lattice>
class MultiBlockSerializerPolicy2D : public MultiSerializerPolicy2D<T> {
public:
  MultiBlockSerializerPolicy2D(MultiBlockLattice2D<T,Lattice> const& lattice_);
  virtual int getElementSize() const;
  virtual void serializeElement(int block, int localX, int localY, T* buffer) const;
  virtual MultiDataDistribution2D const& getMultiData() const;
  virtual bool isAllocated(int block) const;
private:
  MultiBlockLattice2D<T,Lattice> const& lattice;
};

template<typename T, template<typename U> class Lattice>
class MultiBlockUnSerializerPolicy2D : public MultiUnSerializerPolicy2D<T> {
public:
  MultiBlockUnSerializerPolicy2D(MultiBlockLattice2D<T,Lattice>& lattice_);
  virtual int getElementSize() const;
  virtual void unSerializeElement(int block, int localX, int localY, T const* buffer);
  virtual MultiDataDistribution2D const& getMultiData() const;
  virtual bool isAllocated(int block) const;
private:
  MultiBlockLattice2D<T,Lattice>& lattice;
};

}  // namespace olb

#endif
