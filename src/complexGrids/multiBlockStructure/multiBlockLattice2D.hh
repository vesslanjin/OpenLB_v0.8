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
 * A 2D multiblock lattice -- generic implementation.
 */
#ifndef MULTI_BLOCK_LATTICE_2D_HH
#define MULTI_BLOCK_LATTICE_2D_HH

#include "multiBlockLattice2D.h"
#include "multiDataAnalysis2D.h"
#include <limits>


namespace olb {

////////////////////// Class MultiBlockLattice2D /////////////////////////

template<typename T, template<typename U> class Lattice>
MultiBlockLattice2D<T,Lattice>::MultiBlockLattice2D(MultiDataDistribution2D const& dataDistribution_)
  : locatedBlock(0),
    statisticsOn(true),
    periodicCommunicationOn(true),
    serializer(0), unSerializer(0),
    serializerPolicy(*this), unSerializerPolicy(*this),
    dataAnalysis(0)
{
#ifdef PARALLEL_MODE_MPI
  multiBlockHandler = new ParallelMultiBlockHandler2D<T,Lattice>(dataDistribution_);
#else
  multiBlockHandler = new SerialMultiBlockHandler2D<T,Lattice>(dataDistribution_);
#endif
  statistics = new LatticeStatistics<T>;
  allocateBlocks();
  eliminateStatisticsInEnvelope();
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock<getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    reductor.startNewSubscription();
    blockLattices[iBlock] -> subscribeReductions(reductor);
  }
  dataAnalysis = new MultiDataAnalysis2D<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
MultiBlockLattice2D<T,Lattice>::~MultiBlockLattice2D() {
  delete serializer;
  delete unSerializer;
  delete statistics;
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock<getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    delete blockLattices[iBlock];
  }
  delete multiBlockHandler;
  delete dataAnalysis;
}

template<typename T, template<typename U> class Lattice>
MultiBlockLattice2D<T,Lattice>::MultiBlockLattice2D(MultiBlockLattice2D<T,Lattice> const& rhs)
  : locatedBlock(rhs.locatedBlock),
    statisticsOn(rhs.statisticsOn),
    periodicCommunicationOn(rhs.periodicCommunicationOn),
    serializer(0), unSerializer(0),
    serializerPolicy(*this), unSerializerPolicy(*this),
    dataAnalysis(0)
{
  statistics = new LatticeStatistics<T>;
#ifdef PARALLEL_MODE_MPI
  multiBlockHandler = new ParallelMultiBlockHandler2D<T,Lattice> (
    rhs.multiBlockHandler->getMultiDataDistribution() );
#else
  multiBlockHandler = new SerialMultiBlockHandler2D<T,Lattice> (
    rhs.multiBlockHandler->getMultiDataDistribution() );
#endif
  allocateBlocks();
  eliminateStatisticsInEnvelope();
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock<getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    *(blockLattices[iBlock]) = *(rhs.blockLattices[iBlock]);
  }
  for (int rBlock=0; rBlock<getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    reductor.startNewSubscription();
    blockLattices[iBlock] -> subscribeReductions(reductor);
  }
  dataAnalysis = new MultiDataAnalysis2D<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
MultiBlockLattice2D<T,Lattice>& MultiBlockLattice2D<T,Lattice>::operator= (
  MultiBlockLattice2D<T,Lattice> const& rhs )
{
  MultiBlockLattice2D<T,Lattice>(rhs).swap(*this);
  return *this;
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::swap(MultiBlockLattice2D<T,Lattice>& rhs) {
  std::swap(locatedBlock, rhs.locatedBlock);
  std::swap(multiBlockHandler, rhs.multiBlockHandler);
  blockLattices.swap(rhs.blockLattices);
  std::swap(statistics, rhs.statistics);
  std::swap(statisticsOn, rhs.statisticsOn);
  std::swap(periodicCommunicationOn, rhs.periodicCommunicationOn);
  std::swap(reductor, rhs.reductor);
  std::swap(serializer, rhs.serializer);
  std::swap(unSerializer, rhs.unSerializer);
  std::swap(dataAnalysis, rhs.dataAnalysis);
}

template<typename T, template<typename U> class Lattice>
Cell<T,Lattice>& MultiBlockLattice2D<T,Lattice>::get(int iX, int iY) {
  std::vector<int> foundId;
  std::vector<int> foundX, foundY;
  bool hasBulkCell;
  locatedBlock = multiBlockHandler -> locateLocally(iX, iY, foundId, foundX, foundY, hasBulkCell, locatedBlock);
  returnCells.clear();
  for (unsigned iBlock=0; iBlock<foundId.size(); ++iBlock) {
    int foundBlock = foundId[iBlock];
    returnCells.push_back ( &blockLattices[foundBlock] -> get ( foundX[iBlock], foundY[iBlock] ) );
  }
  return multiBlockHandler -> getDistributedCell(returnCells, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
Cell<T,Lattice> const& MultiBlockLattice2D<T,Lattice>::get(int iX, int iY) const {
  std::vector<int> foundId;
  std::vector<int> foundX, foundY;
  bool hasBulkCell;
  locatedBlock = multiBlockHandler -> locateLocally(iX, iY, foundId, foundX, foundY, hasBulkCell, locatedBlock);
  constReturnCells.clear();
  for (unsigned iBlock=0; iBlock<foundId.size(); ++iBlock) {
    int foundBlock = foundId[iBlock];
    constReturnCells.push_back ( &blockLattices[foundBlock] -> get ( foundX[iBlock], foundY[iBlock] ) );
  }
  return multiBlockHandler -> getDistributedCell(constReturnCells, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::initialize() {
  // Invoke postProcessMultiBlock(), which fills the envelope of
  //   each sub-block. This needs to be done in the first place,
  //   because the method initialize() of each sub-block may want
  //   to access the envelope. An additional postProcessMultiBlock()
  //   is invoked in the end to copy the result of initialize() to
  //   all processors
  postProcessMultiBlock();
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    blockLattices[iBlock] -> initialize();
  }
  postProcessMultiBlock();
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::defineDynamics (
  int x0_, int x1_, int y0_, int y1_, Dynamics<T,Lattice>* dynamics )
{
  BlockCoordinates2D domain(x0_, x1_, y0_, y1_), inters;
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    BlockParameters2D const& params = getParameters(iBlock);
    if (util::intersect(domain, params.getNonPeriodicEnvelope(), inters ) ) {
      inters = params.toLocal(inters);
      blockLattices[iBlock] -> defineDynamics (
        inters.x0, inters.x1, inters.y0, inters.y1, dynamics );
    }
  }
  std::vector<int> const& periodicOverlapWithMe
  = multiBlockHandler->getRelevantIndexes().getPeriodicOverlapWithMe();
  for (unsigned rOverlap=0; rOverlap < periodicOverlapWithMe.size(); ++rOverlap) {
    int iOverlap = periodicOverlapWithMe[rOverlap];
    Overlap2D const& overlap = getPeriodicOverlap(iOverlap);
    int overlapId = overlap.getOverlapId();
    if (util::intersect(domain, overlap.getOriginalCoordinates(), inters ) ) {
      inters = inters.shift( -overlap.getShiftX(), -overlap.getShiftY() );
      inters = getParameters(overlapId).toLocal(inters);
      blockLattices[overlapId] -> defineDynamics (
        inters.x0, inters.x1, inters.y0, inters.y1, dynamics );
    }
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::defineDynamics (
  int iX, int iY, Dynamics<T,Lattice>* dynamics )
{
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    BlockParameters2D const& params = getParameters(iBlock);
    if (util::contained(iX, iY, params.getNonPeriodicEnvelope()) ) {
      int localX = params.toLocalX(iX);
      int localY = params.toLocalY(iY);
      blockLattices[iBlock] -> defineDynamics (localX,localY, dynamics );
    }
  }
  std::vector<int> const& periodicOverlapWithMe
  = multiBlockHandler->getRelevantIndexes().getPeriodicOverlapWithMe();
  for (unsigned rOverlap=0; rOverlap < periodicOverlapWithMe.size(); ++rOverlap) {
    int iOverlap = periodicOverlapWithMe[rOverlap];
    Overlap2D const& overlap = getPeriodicOverlap(iOverlap);
    int overlapId = overlap.getOverlapId();
    BlockParameters2D const& params = getParameters(overlapId);
    if (util::contained(iX,iY, overlap.getOriginalCoordinates()) ) {
      int localX = params.toLocalX(iX-overlap.getShiftX());
      int localY = params.toLocalY(iY-overlap.getShiftY());
      blockLattices[overlapId] -> defineDynamics (localX, localY, dynamics);
    }
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T, Lattice>::defineDynamics(
  BlockGeometryStatistics2D* blockGeoSta, int x0_, int x1_, int y0_,
  int y1_, Dynamics<T, Lattice>* dynamics, int material) {

  for (int iX = x0_; iX <= x1_; ++iX) {
    for (int iY = y0_; iY <= y1_; ++iY) {

      if (blockGeoSta->getBlockGeometry()->getMaterial(iX, iY)
          == material) {
        BlockCoordinates2D domain(iX, iX, iY, iY), inters;
        std::vector<int> const& relevantBlocks = getRelevantBlocks();
        for (int rBlock = 0; rBlock < getNumRelevantBlocks(); ++rBlock) {
          int iBlock = relevantBlocks[rBlock];
          BlockParameters2D const& params = getParameters(iBlock);
          if (util::intersect(domain,
                              params.getNonPeriodicEnvelope(), inters)) {
            inters = params.toLocal(inters);
            blockLattices[iBlock] -> defineDynamics(inters.x0,
                                                    inters.x1, inters.y0, inters.y1, dynamics);
          }
        }

        std::vector<int> const
        & periodicOverlapWithMe =
          multiBlockHandler->getRelevantIndexes().getPeriodicOverlapWithMe();
        for (unsigned rOverlap = 0; rOverlap
             < periodicOverlapWithMe.size(); ++rOverlap) {
          int iOverlap = periodicOverlapWithMe[rOverlap];
          Overlap2D const& overlap = getPeriodicOverlap(iOverlap);
          int overlapId = overlap.getOverlapId();
          if (util::intersect(domain,
                              overlap.getOriginalCoordinates(), inters)) {
            inters = inters.shift(-overlap.getShiftX(),
                                  -overlap.getShiftY());
            inters = getParameters(overlapId).toLocal(inters);
            blockLattices[overlapId] -> defineDynamics(inters.x0,
                inters.x1, inters.y0, inters.y1, dynamics);
          }
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T, Lattice>::defineDynamics(
  BlockGeometryStatistics2D* blockGeoSta, Dynamics<T, Lattice>* dynamics,
  int material) {
  defineDynamics(blockGeoSta,
                 0, blockGeoSta->getBlockGeometry()->getNx() - 1,
                 0, blockGeoSta->getBlockGeometry()->getNy() - 1, dynamics, material);
}


template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::specifyStatisticsStatus (
  int x0_, int x1_, int y0_, int y1_, bool status )
{
  BlockCoordinates2D domain(x0_, x1_, y0_, y1_), inters;
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    BlockParameters2D const& params = getParameters(iBlock);
    if (util::intersect(domain, params.getBulk(), inters ) ) {
      inters = params.toLocal(inters);
      blockLattices[iBlock] -> specifyStatisticsStatus (
        inters.x0, inters.x1, inters.y0, inters.y1, status );
    }
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::collide(int x0_, int x1_, int y0_, int y1_)
{
  BlockCoordinates2D domain(x0_, x1_, y0_, y1_), inters;
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    BlockParameters2D const& params = getParameters(iBlock);
    if (util::intersect(domain, params.getEnvelope(), inters ) ) {
      inters = params.toLocal(inters);
      blockLattices[iBlock] -> collide(inters.x0, inters.x1, inters.y0, inters.y1);
    }
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::collide() {
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    blockLattices[iBlock] -> collide();
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::staticCollide (
  int x0_, int x1_, int y0_, int y1_,
  TensorFieldBase2D<T,2> const& u)
{
  OLB_ASSERT(false, "Method not yet implemented");
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::staticCollide(TensorFieldBase2D<T,2> const& u)
{
  OLB_ASSERT(false, "Method not yet implemented");
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::stream(int x0_, int x1_, int y0_, int y1_)
{
  BlockCoordinates2D domain(x0_, x1_, y0_, y1_), inters;
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    BlockParameters2D const& params = getParameters(iBlock);
    if (util::intersect(domain, params.getNonPeriodicEnvelope(), inters ) ) {
      inters = params.toLocal(inters);
      blockLattices[iBlock] -> stream(inters.x0, inters.x1, inters.y0, inters.y1);
    }
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::stream(bool periodic) {
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  if (periodic) {
    for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
      int iBlock = relevantBlocks[rBlock];
      blockLattices[iBlock] -> stream();
    }
  }
  else {
    for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
      int iBlock = relevantBlocks[rBlock];
      BlockParameters2D const& params = getParameters(iBlock);
      BlockCoordinates2D npEnv = params.toLocal(params.getNonPeriodicEnvelope());
      blockLattices[iBlock] -> stream(npEnv.x0, npEnv.x1, npEnv.y0, npEnv.y1);
      blockLattices[iBlock] -> postProcess();
    }
  }
  postProcessMultiBlock();
  getStatistics().incrementTime();
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::collideAndStream(int x0_, int x1_, int y0_, int y1_) {
  BlockCoordinates2D domain(x0_, x1_, y0_, y1_), inters;
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    BlockParameters2D const& params = getParameters(iBlock);
    if (util::intersect(domain, params.getNonPeriodicEnvelope(), inters ) ) {
      inters = params.toLocal(inters);
      blockLattices[iBlock] -> stream(inters.x0, inters.x1, inters.y0, inters.y1);
    }
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::collideAndStream(bool periodic) {
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  if (periodic) {
    for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
      int iBlock = relevantBlocks[rBlock];
      blockLattices[iBlock] -> collideAndStream();
    }
  }
  else {
    for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
      int iBlock = relevantBlocks[rBlock];
      BlockParameters2D const& params = getParameters(iBlock);
      BlockCoordinates2D npEnv = params.toLocal(params.getNonPeriodicEnvelope());
      blockLattices[iBlock] -> collideAndStream(npEnv.x0, npEnv.x1, npEnv.y0, npEnv.y1);
      blockLattices[iBlock] -> postProcess();
    }
  }
  postProcessMultiBlock();
  getStatistics().incrementTime();
}

template<typename T, template<typename U> class Lattice>
T MultiBlockLattice2D<T,Lattice>::computeAverageDensity(int x0_, int x1_, int y0_, int y1_) const {
  BlockCoordinates2D domain(x0_, x1_, y0_, y1_), inters;
  T sumWeights = T(), sumDensities = T();
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    BlockParameters2D const& params = getParameters(iBlock);
    if (util::intersect(domain, params.getBulk(), inters ) ) {
      inters = params.toLocal(inters);
      T weight = (T) ( (inters.x1-inters.x0+1) * (inters.y1-inters.y0+1) ) /
                 (T) std::numeric_limits<int>::max();
      sumWeights += weight;
      T newDensity = blockLattices[iBlock] -> computeAverageDensity (
                       inters.x0, inters.x1, inters.y0, inters.y1 );
      sumDensities += newDensity * weight;
    }
  }
  if (sumWeights > 1.e-12) {
    sumDensities /= sumWeights;
  }
  multiBlockHandler->reduceAverage(sumDensities, sumWeights);
  return sumDensities;
}

template<typename T, template<typename U> class Lattice>
T MultiBlockLattice2D<T,Lattice>::computeAverageDensity() const {
  return computeAverageDensity(0, getNx()-1, 0, getNy()-1);
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::stripeOffDensityOffset(int x0_, int x1_, int y0_, int y1_, T offset) {
  BlockCoordinates2D domain(x0_, x1_, y0_, y1_), inters;
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    BlockParameters2D const& params = getParameters(iBlock);
    if (util::intersect(domain, params.getEnvelope(), inters ) ) {
      inters = params.toLocal(inters);
      blockLattices[iBlock] -> stripeOffDensityOffset (
        inters.x0, inters.x1, inters.y0, inters.y1, offset );
    }
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::stripeOffDensityOffset(T offset) {
  stripeOffDensityOffset(0, getNx()-1, 0,getNy()-1, offset);
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::forAll(int x0_, int x1_, int y0_, int y1_,
    WriteCellFunctional<T,Lattice> const& application)
{
  BlockCoordinates2D domain(x0_, x1_, y0_, y1_), inters;
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    BlockParameters2D const& params = getParameters(iBlock);
    if (util::intersect(domain, params.getEnvelope(), inters ) ) {
      inters = params.toLocal(inters);
      blockLattices[iBlock] -> forAll (
        inters.x0, inters.x1, inters.y0, inters.y1, application );
    }
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::forAll(WriteCellFunctional<T,Lattice> const& application)
{
  forAll(0, getNx()-1, 0,getNy()-1, application);
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::addPostProcessor(PostProcessorGenerator2D<T,Lattice> const& ppGen)
{
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    BlockParameters2D const& params = getParameters(iBlock);
    BlockCoordinates2D const& bulk = params.getBulk();
    PostProcessorGenerator2D<T,Lattice> *extractedPpGen = ppGen.clone();
    if (extractedPpGen->extract( bulk.x0, bulk.x1, bulk.y0, bulk.y1 ) ) {
      BlockCoordinates2D const& envelope = params.getEnvelope();
      extractedPpGen->shift(-envelope.x0, -envelope.y0);
      blockLattices[iBlock] -> addPostProcessor(*extractedPpGen);
    }
    delete extractedPpGen;
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::addLatticeCoupling (
  LatticeCouplingGenerator2D<T,Lattice> const& lcGen,
  std::vector<SpatiallyExtendedObject2D*> partners )
{
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    std::vector<SpatiallyExtendedObject2D*> extractedPartners(partners.size());
    for (unsigned iP=0; iP<extractedPartners.size(); ++iP) {
      extractedPartners[iP] = partners[iP]->getComponent(iBlock);
    }
    BlockParameters2D const& params = getParameters(iBlock);
    BlockCoordinates2D const& bulk = params.getBulk();
    LatticeCouplingGenerator2D<T,Lattice> *extractedLcGen = lcGen.clone();
    if (extractedLcGen->extract( bulk.x0, bulk.x1, bulk.y0, bulk.y1 ) ) {
      BlockCoordinates2D const& envelope = params.getEnvelope();
      extractedLcGen->shift(-envelope.x0, -envelope.y0);
      blockLattices[iBlock] -> addLatticeCoupling (*extractedLcGen, extractedPartners);
    }
    delete extractedLcGen;
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::resetPostProcessors() {
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    blockLattices[iBlock] -> resetPostProcessors();
  }
}

template<typename T, template<typename U> class Lattice>
LatticeStatistics<T>& MultiBlockLattice2D<T,Lattice>::getStatistics()
{
  return *statistics;
}

template<typename T, template<typename U> class Lattice>
LatticeStatistics<T> const&
MultiBlockLattice2D<T,Lattice>::getStatistics() const
{
  return *statistics;
}

template<typename T, template<typename U> class Lattice>
DataAnalysisBase2D<T,Lattice> const& MultiBlockLattice2D<T,Lattice>::getDataAnalysis() const {
  dataAnalysis -> reset();
  return *dataAnalysis;
}

template<typename T, template<typename U> class Lattice>
DataSerializer<T> const& MultiBlockLattice2D<T,Lattice>::getSerializer(IndexOrdering::OrderingT ordering) const {
  delete serializer;
  serializer = new MultiSerializer2D<T>(serializerPolicy, ordering);
  return *serializer;
}

template<typename T, template<typename U> class Lattice>
DataUnSerializer<T>& MultiBlockLattice2D<T,Lattice>::getUnSerializer(IndexOrdering::OrderingT ordering) {
  delete unSerializer;
  unSerializer = new MultiUnSerializer2D<T>(unSerializerPolicy, ordering);
  return *unSerializer;
}

template<typename T, template<typename U> class Lattice>
DataSerializer<T> const& MultiBlockLattice2D<T,Lattice>::getSubSerializer (
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering ) const
{
  delete serializer;
  serializer = new MultiSerializer2D<T> (
    serializerPolicy, x0_, x1_, y0_, y1_, ordering );
  return *serializer;
}

template<typename T, template<typename U> class Lattice>
DataUnSerializer<T>& MultiBlockLattice2D<T,Lattice>::getSubUnSerializer (
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering )
{
  delete unSerializer;
  unSerializer = new MultiUnSerializer2D<T> (
    unSerializerPolicy, x0_, x1_, y0_, y1_, ordering );
  return *unSerializer;
}



template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::postProcess(int x0_, int x1_, int y0_, int y1_) {
  BlockCoordinates2D domain(x0_, x1_, y0_, y1_), inters;
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    BlockParameters2D const& params = getParameters(iBlock);
    if ( util::intersect(domain, params.getBulk(), inters) ) {
      inters = params.toLocal(inters);
      blockLattices[iBlock] -> postProcess(inters.x0, inters.x1, inters.y0, inters.y1);
    }
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::postProcess() {
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    blockLattices[iBlock] -> postProcess();
  }
  postProcessMultiBlock();
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::executeCoupling(int x0_, int x1_, int y0_, int y1_) {
  BlockCoordinates2D domain(x0_, x1_, y0_, y1_), inters;
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    BlockParameters2D const& params = getParameters(iBlock);
    if ( util::intersect(domain, params.getBulk(), inters) ) {
      inters = params.toLocal(inters);
      blockLattices[iBlock] -> executeCoupling(inters.x0, inters.x1, inters.y0, inters.y1);
    }
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::executeCoupling() {
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock < getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    blockLattices[iBlock] -> executeCoupling();
  }
  multiBlockHandler -> connectBoundaries(blockLattices, periodicCommunicationOn);
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::subscribeReductions(Reductor<T>& reductor)
{
  std::vector<T>& averageVect = statistics->getAverageVect();
  for (size_t iVect=0; iVect<averageVect.size(); ++iVect) {
    reductor.subscribeAverage(statistics->getNumCells(), averageVect[iVect]);
  }
  std::vector<T>& sumVect = statistics->getSumVect();
  for (size_t iVect=0; iVect<sumVect.size(); ++iVect) {
    reductor.subscribeSum(sumVect[iVect]);
  }
  std::vector<T>& minVect = statistics->getMinVect();
  for (size_t iVect=0; iVect<minVect.size(); ++iVect) {
    reductor.subscribeMin(minVect[iVect]);
  }
  std::vector<T>& maxVect = statistics->getMaxVect();
  for (size_t iVect=0; iVect<maxVect.size(); ++iVect) {
    reductor.subscribeMax(maxVect[iVect]);
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::allocateBlocks() {
  for (int iBlock=0; iBlock<getMultiData().getNumBlocks(); ++iBlock) {
    int lx=0, ly=0;
    if (multiBlockHandler->getLocalEnvelope(iBlock, lx, ly)) {
      blockLattices.push_back(new BlockLattice2D<T,Lattice>(lx,ly));
    }
    else {
      blockLattices.push_back( 0 );
    }
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::postProcessMultiBlock() {
  if (statisticsOn) {
    reduceStatistics();
  }
  multiBlockHandler -> connectBoundaries(blockLattices, periodicCommunicationOn);
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::reduceStatistics() {
  std::vector<T> averageElements, averageWeights, sumElements, minElements, maxElements;
  // Reduce averages
  reductor.getAverages(averageElements, averageWeights);
  for (unsigned iEl=0; iEl<averageElements.size(); ++iEl) {
    averageElements[iEl] =
      multiBlockHandler -> reduceAverage(averageElements[iEl], averageWeights[iEl]);
  }
  // Reduce sums
  reductor.getSums(sumElements);
  for (unsigned iEl=0; iEl<sumElements.size(); ++iEl) {
    sumElements[iEl] = multiBlockHandler -> reduceSum(sumElements[iEl]);
  }
  // Reduce minima
  reductor.getMins(minElements);
  for (unsigned iEl=0; iEl<minElements.size(); ++iEl) {
    minElements[iEl] = multiBlockHandler -> reduceMin(minElements[iEl]);
  }
  // Reduce maxima
  reductor.getMaxs(maxElements);
  for (unsigned iEl=0; iEl<maxElements.size(); ++iEl) {
    maxElements[iEl] = multiBlockHandler -> reduceMax(maxElements[iEl]);
  }
  // Write reductions back to the individual lattices
  reductor.saveGlobalReductions(averageElements, sumElements, minElements, maxElements);
  // Write reductions back to the MultiBlockLattice
  MultiBlockReductor<T> myReductor;
  myReductor.startNewSubscription();
  this -> subscribeReductions(myReductor);
  myReductor.saveGlobalReductions(averageElements, sumElements, minElements, maxElements);
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::eliminateStatisticsInEnvelope() {
  std::vector<int> const& relevantBlocks = getRelevantBlocks();
  for (int rBlock=0; rBlock<getNumRelevantBlocks(); ++rBlock) {
    int iBlock = relevantBlocks[rBlock];
    int envelopeWidth = getParameters(iBlock).getEnvelopeWidth();
    BlockLattice2D<T,Lattice>& block = *blockLattices[iBlock];
    int maxX = block.getNx()-1;
    int maxY = block.getNy()-1;

    block.specifyStatisticsStatus(0, maxX, 0, envelopeWidth-1, false);
    block.specifyStatisticsStatus(0, maxX, maxY-envelopeWidth+1, maxY, false);
    block.specifyStatisticsStatus(0, envelopeWidth-1,         0, maxY, false);
    block.specifyStatisticsStatus(maxX-envelopeWidth+1, maxX, 0, maxY, false);
  }
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::toggleInternalStatistics(bool statisticsOn_) {
  statisticsOn = statisticsOn_;
}

template<typename T, template<typename U> class Lattice>
void MultiBlockLattice2D<T,Lattice>::togglePeriodicCommunication(bool periodicCommunicationOn_) {
  periodicCommunicationOn = periodicCommunicationOn_;
}

template<typename T, template<typename U> class Lattice>
bool MultiBlockLattice2D<T,Lattice>::isInternalStatisticsOn() const {
  return statisticsOn;
}

template<typename T, template<typename U> class Lattice>
bool MultiBlockLattice2D<T,Lattice>::isPeriodicCommunicationOn() const {
  return periodicCommunicationOn;
}

template<typename T, template<typename U> class Lattice>
std::vector<BlockLattice2D<T,Lattice>*> MultiBlockLattice2D<T,Lattice>::getBlockLattices() {
  return blockLattices;
}

template<typename T, template<typename U> class Lattice>
const std::vector<BlockLattice2D<T,Lattice>*> MultiBlockLattice2D<T,Lattice>::getBlockLattices() const {
  return blockLattices;
}

template<typename T, template<typename U> class Lattice>
MultiDataDistribution2D const& MultiBlockLattice2D<T,Lattice>::getMultiData() const {
  return multiBlockHandler -> getMultiDataDistribution();
}

template<typename T, template<typename U> class Lattice>
BlockParameters2D const& MultiBlockLattice2D<T,Lattice>::getParameters(int iParam) const {
  return getMultiData().getBlockParameters(iParam);
}

template<typename T, template<typename U> class Lattice>
Overlap2D const& MultiBlockLattice2D<T,Lattice>::getNormalOverlap(int iOverlap) const {
  return getMultiData().getNormalOverlap(iOverlap);
}

template<typename T, template<typename U> class Lattice>
Overlap2D const& MultiBlockLattice2D<T,Lattice>::getPeriodicOverlap(int iOverlap) const {
  return getMultiData().getPeriodicOverlap(iOverlap);
}

template<typename T, template<typename U> class Lattice>
int MultiBlockLattice2D<T,Lattice>::getNumRelevantBlocks() const {
  return getRelevantBlocks().size();
}

template<typename T, template<typename U> class Lattice>
MultiDataDistribution2D MultiBlockLattice2D<T,Lattice>::getDataDistribution() const {
  return getMultiData();
}

template<typename T, template<typename U> class Lattice>
std::vector<int> const& MultiBlockLattice2D<T,Lattice>::getRelevantBlocks() const {
  return multiBlockHandler->getRelevantIndexes().getBlocks();
}


template<typename T, template<typename U> class Lattice>
SpatiallyExtendedObject2D* MultiBlockLattice2D<T,Lattice>::getComponent(int iBlock) {
  OLB_PRECONDITION( iBlock<getBlockLattices().size() );
  return getBlockLattices()[iBlock];
}

template<typename T, template<typename U> class Lattice>
SpatiallyExtendedObject2D const* MultiBlockLattice2D<T,Lattice>::getComponent(int iBlock) const {
  OLB_PRECONDITION( iBlock<getBlockLattices().size() );
  return getBlockLattices()[iBlock];
}

template<typename T, template<typename U> class Lattice>
multiPhysics::MultiPhysicsId MultiBlockLattice2D<T,Lattice>::getMultiPhysicsId() const {
  return multiPhysics::getMultiPhysicsBlockId<T,Lattice>();
}



////////// class MultiBlockSerializerPolicy2D ////////////////////////////

template<typename T, template<typename U> class Lattice>
MultiBlockSerializerPolicy2D<T,Lattice>::MultiBlockSerializerPolicy2D (
  MultiBlockLattice2D<T,Lattice> const& lattice_ )
  : lattice(lattice_)
{ }

template<typename T, template<typename U> class Lattice>
int MultiBlockSerializerPolicy2D<T,Lattice>::getElementSize() const {
  return Lattice<T>::q + Lattice<T>::ExternalField::numScalars;
}

template<typename T, template<typename U> class Lattice>
void MultiBlockSerializerPolicy2D<T,Lattice>::serializeElement (
  int block, int localX, int localY, T* buffer) const
{
  lattice.getBlockLattices()[block] -> get(localX, localY).serialize(buffer);
}

template<typename T, template<typename U> class Lattice>
MultiDataDistribution2D const& MultiBlockSerializerPolicy2D<T,Lattice>::getMultiData() const
{
  return lattice.getMultiData();
}

template<typename T, template<typename U> class Lattice>
bool MultiBlockSerializerPolicy2D<T,Lattice>::isAllocated(int block) const
{
  return lattice.getBlockLattices()[block];
}


////////// class MultiBlockUnSerializerPolicy2D ////////////////////////////

template<typename T, template<typename U> class Lattice>
MultiBlockUnSerializerPolicy2D<T,Lattice>::MultiBlockUnSerializerPolicy2D (
  MultiBlockLattice2D<T,Lattice>& lattice_ )
  : lattice(lattice_)
{ }

template<typename T, template<typename U> class Lattice>
int MultiBlockUnSerializerPolicy2D<T,Lattice>::getElementSize() const {
  return Lattice<T>::q + Lattice<T>::ExternalField::numScalars;
}

template<typename T, template<typename U> class Lattice>
void MultiBlockUnSerializerPolicy2D<T,Lattice>::unSerializeElement (
  int block, int localX, int localY, T const* buffer)
{
  lattice.getBlockLattices()[block] -> get(localX, localY).unSerialize(buffer);
}

template<typename T, template<typename U> class Lattice>
MultiDataDistribution2D const& MultiBlockUnSerializerPolicy2D<T,Lattice>::getMultiData() const
{
  return lattice.getMultiData();
}

template<typename T, template<typename U> class Lattice>
bool MultiBlockUnSerializerPolicy2D<T,Lattice>::isAllocated(int block) const
{
  return lattice.getBlockLattices()[block];
}


}  // namespace olb

#endif
