/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007, 2008 Jonas Latt and Bernd Stahl
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
 * Handler for 3D multiblock structure -- generic implementation.
 */

#ifndef MULTI_BLOCK_HANDLER_3D_HH
#define MULTI_BLOCK_HANDLER_3D_HH

#include "complexGrids/mpiManager/mpiManager.h"
#include "multiBlockHandler3D.h"
#include "parallelDynamics.h"
#include "core/util.h"
#include <algorithm>
#include <numeric>


namespace olb {

////////////////////// Class SerialMultiBlockHandler3D /////////////////////

template<typename T, template<typename U> class Lattice>
SerialMultiBlockHandler3D<T,Lattice>::SerialMultiBlockHandler3D (
  MultiDataDistribution3D const& dataDistribution_ )
  : dataDistribution(dataDistribution_),
    relevantIndexes(dataDistribution.getNumBlocks(), dataDistribution.getNumNormalOverlaps(),
                    dataDistribution.getNumPeriodicOverlaps(), dataDistribution.getNx(),
                    dataDistribution.getNy(), dataDistribution.getNz() )
{ }

template<typename T, template<typename U> class Lattice>
int SerialMultiBlockHandler3D<T,Lattice>::getNx() const {
  return dataDistribution.getNx();
}

template<typename T, template<typename U> class Lattice>
int SerialMultiBlockHandler3D<T,Lattice>::getNy() const {
  return dataDistribution.getNy();
}

template<typename T, template<typename U> class Lattice>
int SerialMultiBlockHandler3D<T,Lattice>::getNz() const {
  return dataDistribution.getNz();
}

template<typename T, template<typename U> class Lattice>
MultiDataDistribution3D const& SerialMultiBlockHandler3D<T,Lattice>::getMultiDataDistribution() const {
  return dataDistribution;
}

template<typename T, template<typename U> class Lattice>
RelevantIndexes3D const& SerialMultiBlockHandler3D<T,Lattice>::getRelevantIndexes() const {
  return relevantIndexes;
}

template<typename T, template<typename U> class Lattice>
bool SerialMultiBlockHandler3D<T,Lattice>::getLocalEnvelope(int iBlock, int& lx, int& ly, int& lz) const {
  BlockParameters3D const& parameters = dataDistribution.getBlockParameters(iBlock);
  lx = parameters.getEnvelopeLx();
  ly = parameters.getEnvelopeLy();
  lz = parameters.getEnvelopeLz();
  return true;
}

template<typename T, template<typename U> class Lattice>
T SerialMultiBlockHandler3D<T,Lattice>::reduceSum (T localSum) const {
  return localSum;
}

template<typename T, template<typename U> class Lattice>
T SerialMultiBlockHandler3D<T,Lattice>::reduceAverage (T localAverage, T localWeight) const {
  return localAverage;
}

template<typename T, template<typename U> class Lattice>
T SerialMultiBlockHandler3D<T,Lattice>::reduceMin (T localMin) const {
  return localMin;
}

template<typename T, template<typename U> class Lattice>
T SerialMultiBlockHandler3D<T,Lattice>::reduceMax (T localMax) const {
  return localMax;
}

template<typename T, template<typename U> class Lattice>
void SerialMultiBlockHandler3D<T,Lattice>::broadCastCell(Cell<T,Lattice>& cell, int fromBlock) const {
  // Nothing to do in the serial case
}

template<typename T, template<typename U> class Lattice>
void SerialMultiBlockHandler3D<T,Lattice>::broadCastScalar(T& scalar, int fromBlock) const {
  // Nothing to do in the serial case
}

template<typename T, template<typename U> class Lattice>
void SerialMultiBlockHandler3D<T,Lattice>::broadCastVector(T vect[Lattice<T>::d], int fromBlock) const {
  // Nothing to do in the serial case
}

template<typename T, template<typename U> class Lattice>
void SerialMultiBlockHandler3D<T,Lattice>::copyOverlap (
  Overlap3D const& overlap, BlockVector3D& lattices ) const
{
  int originalId = overlap.getOriginalId();
  int overlapId  = overlap.getOverlapId();
  BlockParameters3D const& originalParameters = dataDistribution.getBlockParameters(originalId);
  BlockParameters3D const& overlapParameters  = dataDistribution.getBlockParameters(overlapId);

  BlockCoordinates3D originalCoords(originalParameters.toLocal(overlap.getOriginalCoordinates()));
  BlockCoordinates3D overlapCoords(overlapParameters.toLocal(overlap.getOverlapCoordinates()));

  assert(originalCoords.x1-originalCoords.x0 == overlapCoords.x1-overlapCoords.x0);
  assert(originalCoords.y1-originalCoords.y0 == overlapCoords.y1-overlapCoords.y0);
  assert(originalCoords.z1-originalCoords.z0 == overlapCoords.z1-overlapCoords.z0);

  int origX = originalCoords.x0;
  int overlapX = overlapCoords.x0;
  for (; origX<=originalCoords.x1; ++origX, ++overlapX) {
    int origY = originalCoords.y0;
    int overlapY = overlapCoords.y0;
    for (; origY<=originalCoords.y1; ++origY, ++overlapY) {
      int origZ = originalCoords.z0;
      int overlapZ = overlapCoords.z0;
      for (; origZ<=originalCoords.z1; ++origZ, ++overlapZ) {
        lattices[overlapId] -> get(overlapX, overlapY, overlapZ).attributeValues (
          lattices[originalId] -> get(origX, origY, origZ) );
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void SerialMultiBlockHandler3D<T,Lattice>::connectBoundaries (
  BlockVector3D& lattices, bool periodicCommunication ) const
{
  for (int iOverlap=0; iOverlap<dataDistribution.getNumNormalOverlaps(); ++iOverlap) {
    copyOverlap(dataDistribution.getNormalOverlap(iOverlap), lattices);
  }
  if (periodicCommunication) {
    for (int iOverlap=0; iOverlap<dataDistribution.getNumPeriodicOverlaps(); ++iOverlap) {
      copyOverlap(dataDistribution.getPeriodicOverlap(iOverlap), lattices);
    }
  }
}

template<typename T, template<typename U> class Lattice>
Cell<T,Lattice>& SerialMultiBlockHandler3D<T,Lattice>::
getDistributedCell(std::vector<Cell<T,Lattice>*>& baseCell, bool hasBulkCell) const
{
  OLB_PRECONDITION( baseCell.size()>0 && baseCell[0] );
  return *baseCell[0];
}

template<typename T, template<typename U> class Lattice>
Cell<T,Lattice> const& SerialMultiBlockHandler3D<T,Lattice>::
getDistributedCell(std::vector<Cell<T,Lattice> const*>& baseCell, bool hasBulkCell) const
{
  OLB_PRECONDITION( baseCell.size()>0 && baseCell[0] );
  return *baseCell[0];
}

template<typename T, template<typename U> class Lattice>
int SerialMultiBlockHandler3D<T,Lattice>::locateLocally(int iX, int iY, int iZ,
    std::vector<int>& foundId,
    std::vector<int>& foundX,
    std::vector<int>& foundY,
    std::vector<int>& foundZ,
    bool& hasBulkCell, int guess) const
{
  // In serial there's only one processor, we're therefore sure
  //   the bulk cell with coordinates (iX,iY,iZ) can be found locally.
  hasBulkCell = true;
  // In serial, it is sufficient to find the bulk-cell representation
  //   of cell (iX,iY,iZ). Although it might also be present in envelopes,
  //   these envelope representations are properly treated because all
  //   of them have a pointer to the same dynamics object.
  int bulkId = dataDistribution.locate(iX,iY,iZ, guess);
  foundId.push_back(bulkId);
  BlockParameters3D const& parameters = dataDistribution.getBlockParameters(bulkId);
  foundX.push_back(parameters.toLocalX(iX));
  foundY.push_back(parameters.toLocalY(iY));
  foundZ.push_back(parameters.toLocalZ(iZ));
  return bulkId;
}


#ifdef PARALLEL_MODE_MPI

////////////////////// Class DataTransmittor3D /////////////////////

template<typename T, template<typename U> class Lattice>
BlockingDataTransmittor3D<T,Lattice>::BlockingDataTransmittor3D (
  Overlap3D const& overlap, MultiDataDistribution3D const& dataDistribution )
{
  originalId = overlap.getOriginalId();
  overlapId  = overlap.getOverlapId();

  BlockParameters3D const& originalParameters = dataDistribution.getBlockParameters(originalId);
  BlockParameters3D const& overlapParameters  = dataDistribution.getBlockParameters(overlapId);

  originalProc = originalParameters.getProcId();
  overlapProc  = overlapParameters.getProcId();
  int myProc   = singleton::mpi().getRank();

  originalCoords = originalParameters.toLocal(overlap.getOriginalCoordinates());
  overlapCoords  = overlapParameters.toLocal(overlap.getOverlapCoordinates());

  int lx = originalCoords.x1-originalCoords.x0+1;
  int ly = originalCoords.y1-originalCoords.y0+1;
  int lz = originalCoords.z1-originalCoords.z0+1;
  OLB_PRECONDITION(lx == overlapCoords.x1-overlapCoords.x0+1);
  OLB_PRECONDITION(ly == overlapCoords.y1-overlapCoords.y0+1);
  OLB_PRECONDITION(lz == overlapCoords.z1-overlapCoords.z0+1);

  sizeOfCell = Lattice<T>::q + Lattice<T>::ExternalField::numScalars;
  bufferSize = lx*ly*lz*sizeOfCell;

  buffer.resize(bufferSize);

  if (originalProc==myProc && overlapProc==myProc) {
    myRole = senderAndReceiver;
  }
  else if (originalProc==myProc) {
    myRole = sender;
  }
  else if (overlapProc==myProc) {
    myRole = receiver;
  }
  else {
    myRole = nothing;
  }
}

template<typename T, template<typename U> class Lattice>
void BlockingDataTransmittor3D<T,Lattice>::prepareTransmission(BlockVector3D& lattices) {
  if (myRole==sender) {
    T* bufferP = &buffer[0];
    BlockLattice3D<T,Lattice>* lattice = lattices[originalId];
    int iData=0;
    for (int iX=originalCoords.x0; iX<=originalCoords.x1; ++iX) {
      for (int iY=originalCoords.y0; iY<=originalCoords.y1; ++iY) {
        for (int iZ=originalCoords.z0; iZ<=originalCoords.z1; ++iZ) {
          lattice -> get(iX,iY,iZ).serialize(bufferP+iData);
          iData += sizeOfCell;
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void BlockingDataTransmittor3D<T,Lattice>::executeTransmission(BlockVector3D& lattices) {
  switch(myRole) {
  case senderAndReceiver:
  {
    int origX = originalCoords.x0;
    int overlapX = overlapCoords.x0;
    for (; origX<=originalCoords.x1; ++origX, ++overlapX) {
      int origY = originalCoords.y0;
      int overlapY = overlapCoords.y0;
      for (; origY<=originalCoords.y1; ++origY, ++overlapY) {
        int origZ = originalCoords.z0;
        int overlapZ = overlapCoords.z0;
        for (; origZ<=originalCoords.z1; ++origZ, ++overlapZ) {
          lattices[overlapId] -> get(overlapX, overlapY, overlapZ).attributeValues (
            lattices[originalId] -> get(origX, origY, origZ) );
        }
      }
    }
    break;
  }
  case sender:
    singleton::mpi().send(&buffer[0], bufferSize, overlapProc);
    break;
  case receiver:
    singleton::mpi().receive(&buffer[0], bufferSize, originalProc);
    break;
  case nothing:
    break;
  }
}

template<typename T, template<typename U> class Lattice>
void BlockingDataTransmittor3D<T,Lattice>::finalizeTransmission(BlockVector3D& lattices) {
  if (myRole==receiver) {
    T* bufferP = &buffer[0];
    BlockLattice3D<T,Lattice>* lattice = lattices[overlapId];
    int iData=0;
    for (int iX=overlapCoords.x0; iX<=overlapCoords.x1; ++iX) {
      for (int iY=overlapCoords.y0; iY<=overlapCoords.y1; ++iY) {
        for (int iZ=overlapCoords.z0; iZ<=overlapCoords.z1; ++iZ) {
          lattice -> get(iX,iY,iZ).unSerialize(bufferP+iData);
          iData += sizeOfCell;
        }
      }
    }
  }
}


template<typename T, template<typename U> class Lattice>
NonBlockingDataTransmittor3D<T,Lattice>::NonBlockingDataTransmittor3D (
  Overlap3D const& overlap, MultiDataDistribution3D const& dataDistribution )
{
  originalId = overlap.getOriginalId();
  overlapId  = overlap.getOverlapId();

  BlockParameters3D const& originalParameters = dataDistribution.getBlockParameters(originalId);
  BlockParameters3D const& overlapParameters  = dataDistribution.getBlockParameters(overlapId);

  originalProc = originalParameters.getProcId();
  overlapProc  = overlapParameters.getProcId();
  int myProc   = singleton::mpi().getRank();

  originalCoords = originalParameters.toLocal(overlap.getOriginalCoordinates());
  overlapCoords  = overlapParameters.toLocal(overlap.getOverlapCoordinates());

  int lx = originalCoords.x1-originalCoords.x0+1;
  int ly = originalCoords.y1-originalCoords.y0+1;
  int lz = originalCoords.z1-originalCoords.z0+1;
  OLB_PRECONDITION(lx == overlapCoords.x1-overlapCoords.x0+1);
  OLB_PRECONDITION(ly == overlapCoords.y1-overlapCoords.y0+1);
  OLB_PRECONDITION(lz == overlapCoords.z1-overlapCoords.z0+1);

  sizeOfCell = Lattice<T>::q + Lattice<T>::ExternalField::numScalars;
  bufferSize = lx*ly*lz*sizeOfCell;

  buffer.resize(bufferSize);

  if (originalProc==myProc && overlapProc==myProc) {
    myRole = senderAndReceiver;
  }
  else if (originalProc==myProc) {
    myRole = sender;
  }
  else if (overlapProc==myProc) {
    myRole = receiver;
  }
  else {
    myRole = nothing;
  }
}

template<typename T, template<typename U> class Lattice>
void NonBlockingDataTransmittor3D<T,Lattice>::prepareTransmission(BlockVector3D& lattices) {
  switch(myRole) {
  case senderAndReceiver:
    break;
  case sender:
    break;
  case receiver:
  {
    singleton::mpi().iRecv(&buffer[0], bufferSize, originalProc, &request);
    break;
  }
  case nothing:
    break;
  }
}

template<typename T, template<typename U> class Lattice>
void NonBlockingDataTransmittor3D<T,Lattice>::executeTransmission(BlockVector3D& lattices) {
  switch(myRole) {
  case senderAndReceiver:
  {
    int origX = originalCoords.x0;
    int overlapX = overlapCoords.x0;
    for (; origX<=originalCoords.x1; ++origX, ++overlapX) {
      int origY = originalCoords.y0;
      int overlapY = overlapCoords.y0;
      for (; origY<=originalCoords.y1; ++origY, ++overlapY) {
        int origZ = originalCoords.z0;
        int overlapZ = overlapCoords.z0;
        for (; origZ<=originalCoords.z1; ++origZ, ++overlapZ) {
          lattices[overlapId] -> get(overlapX, overlapY, overlapZ).attributeValues (
            lattices[originalId] -> get(origX, origY, origZ) );
        }
      }
    }
    break;
  }
  case sender:
  {
    T* bufferP = &buffer[0];
    BlockLattice3D<T,Lattice>* lattice = lattices[originalId];
    int iData=0;
    for (int iX=originalCoords.x0; iX<=originalCoords.x1; ++iX) {
      for (int iY=originalCoords.y0; iY<=originalCoords.y1; ++iY) {
        for (int iZ=originalCoords.z0; iZ<=originalCoords.z1; ++iZ) {
          lattice -> get(iX,iY,iZ).serialize(bufferP+iData);
          iData += sizeOfCell;
        }
      }
    }
    singleton::mpi().iSend(&buffer[0], bufferSize, overlapProc, &request);
    break;
  }
  case receiver:
    break;
  case nothing:
    break;
  }
}

template<typename T, template<typename U> class Lattice>
void NonBlockingDataTransmittor3D<T,Lattice>::finalizeTransmission(BlockVector3D& lattices) {
  switch(myRole) {
  case senderAndReceiver:
    break;
  case sender:
  {
    singleton::mpi().wait(&request, &status);
    break;
  }
  case receiver:
  {
    singleton::mpi().wait(&request, &status);
    T* bufferP = &buffer[0];
    BlockLattice3D<T,Lattice>* lattice = lattices[overlapId];
    int iData=0;
    for (int iX=overlapCoords.x0; iX<=overlapCoords.x1; ++iX) {
      for (int iY=overlapCoords.y0; iY<=overlapCoords.y1; ++iY) {
        for (int iZ=overlapCoords.z0; iZ<=overlapCoords.z1; ++iZ) {
          lattice -> get(iX,iY,iZ).unSerialize(bufferP+iData);
          iData += sizeOfCell;
        }
      }
    }
    break;
  }
  case nothing:
    break;
  }
}


////////////////////// Class ParallelMultiBlockHandler3D /////////////////////

template<typename T, template<typename U> class Lattice>
ParallelMultiBlockHandler3D<T,Lattice>::ParallelMultiBlockHandler3D (
  MultiDataDistribution3D const& dataDistribution_ )
  : dataDistribution(dataDistribution_),
    relevantIndexes(dataDistribution, singleton::mpi().getRank()),
    parallelDynamics( 0 )
{
  normalTransmittors.resize(relevantIndexes.getNormalOverlaps().size());
  for (unsigned iRelevant=0; iRelevant<relevantIndexes.getNormalOverlaps().size(); ++iRelevant) {
    int iOverlap = relevantIndexes.getNormalOverlaps()[iRelevant];
    normalTransmittors[iRelevant] =
      new NonBlockingDataTransmittor3D<T,Lattice>(dataDistribution.getNormalOverlap(iOverlap),
          dataDistribution);
  }
  periodicTransmittors.resize(relevantIndexes.getPeriodicOverlaps().size());
  for (unsigned iRelevant=0; iRelevant<relevantIndexes.getPeriodicOverlaps().size(); ++iRelevant) {
    int iOverlap = relevantIndexes.getPeriodicOverlaps()[iRelevant];
    periodicTransmittors[iRelevant] =
      new NonBlockingDataTransmittor3D<T,Lattice>(dataDistribution.getPeriodicOverlap(iOverlap),
          dataDistribution);
  }
}

template<typename T, template<typename U> class Lattice>
ParallelMultiBlockHandler3D<T,Lattice>::~ParallelMultiBlockHandler3D() {
  for (unsigned iRelevant=0; iRelevant<relevantIndexes.getNormalOverlaps().size(); ++iRelevant) {
    delete normalTransmittors[iRelevant];
  }
  for (unsigned iRelevant=0; iRelevant<relevantIndexes.getPeriodicOverlaps().size(); ++iRelevant) {
    delete periodicTransmittors[iRelevant];
  }
}

template<typename T, template<typename U> class Lattice>
int ParallelMultiBlockHandler3D<T,Lattice>::getNx() const {
  return dataDistribution.getNx();
}

template<typename T, template<typename U> class Lattice>
int ParallelMultiBlockHandler3D<T,Lattice>::getNy() const {
  return dataDistribution.getNy();
}

template<typename T, template<typename U> class Lattice>
int ParallelMultiBlockHandler3D<T,Lattice>::getNz() const {
  return dataDistribution.getNz();
}

template<typename T, template<typename U> class Lattice>
MultiDataDistribution3D const& ParallelMultiBlockHandler3D<T,Lattice>::getMultiDataDistribution() const {
  return dataDistribution;
}

template<typename T, template<typename U> class Lattice>
RelevantIndexes3D const& ParallelMultiBlockHandler3D<T,Lattice>::getRelevantIndexes() const {
  return relevantIndexes;
}

template<typename T, template<typename U> class Lattice>
bool ParallelMultiBlockHandler3D<T,Lattice>::getLocalEnvelope(int iBlock, int& lx, int& ly, int& lz) const {
  BlockParameters3D const& parameters = dataDistribution.getBlockParameters(iBlock);
  lx = parameters.getEnvelopeLx();
  ly = parameters.getEnvelopeLy();
  lz = parameters.getEnvelopeLz();
  if ( parameters.getProcId() == singleton::mpi().getRank() ) {
    return true;
  }
  else {
    return false;
  }
}

template<typename T, template<typename U> class Lattice>
T ParallelMultiBlockHandler3D<T,Lattice>::reduceSum(T localSum) const {
  T globalSum;
  singleton::mpi().reduce(localSum, globalSum, MPI_SUM);
  singleton::mpi().bCast(&globalSum, 1);
  return globalSum;
}

template<typename T, template<typename U> class Lattice>
T ParallelMultiBlockHandler3D<T,Lattice>::reduceAverage(T localAverage, T localWeight) const {
  T sumAverage, sumWeights;
  singleton::mpi().reduce(localAverage*localWeight, sumAverage, MPI_SUM);
  singleton::mpi().reduce(localWeight, sumWeights, MPI_SUM);
  if (singleton::mpi().isMainProcessor() && sumWeights>1.e-12) {
    sumAverage /= sumWeights;
  }
  singleton::mpi().bCast(&sumAverage, 1);
  return sumAverage;
}

template<typename T, template<typename U> class Lattice>
T ParallelMultiBlockHandler3D<T,Lattice>::reduceMin(T localMin) const {
  T globalMin;
  singleton::mpi().reduce(localMin, globalMin, MPI_MIN);
  singleton::mpi().bCast(&globalMin, 1);
  return globalMin;
}

template<typename T, template<typename U> class Lattice>
T ParallelMultiBlockHandler3D<T,Lattice>::reduceMax(T localMax) const {
  T globalMax;
  singleton::mpi().reduce(localMax, globalMax, MPI_MAX);
  singleton::mpi().bCast(&globalMax, 1);
  return globalMax;
}

template<typename T, template<typename U> class Lattice>
void ParallelMultiBlockHandler3D<T,Lattice>::broadCastCell(Cell<T,Lattice>& cell, int fromBlock) const {
  const int sizeOfCell = Lattice<T>::q + Lattice<T>::ExternalField::numScalars;
  T* cellData = new T[sizeOfCell];
  int fromProc = dataDistribution.getBlockParameters(fromBlock).getProcId();
  if (singleton::mpi().getRank()==fromProc) {
    cell.serialize(cellData);
  }
  singleton::mpi().bCast(cellData, sizeOfCell, fromProc);
  cell.unSerialize(cellData);
  delete [] cellData;
}

template<typename T, template<typename U> class Lattice>
void ParallelMultiBlockHandler3D<T,Lattice>::broadCastScalar(T& scalar, int fromBlock) const {
  int fromProc = dataDistribution.getBlockParameters(fromBlock).getProcId();
  singleton::mpi().bCast(&scalar, 1, fromProc);
}

template<typename T, template<typename U> class Lattice>
void ParallelMultiBlockHandler3D<T,Lattice>::broadCastVector(T vect[Lattice<T>::d], int fromBlock) const {
  int fromProc = dataDistribution.getBlockParameters(fromBlock).getProcId();
  singleton::mpi().bCast(vect, Lattice<T>::d, fromProc);
}

template<typename T, template<typename U> class Lattice>
void ParallelMultiBlockHandler3D<T,Lattice>::connectBoundaries (
  BlockVector3D& lattices, bool periodicCommunication ) const
{
  for (unsigned iRelevant=0; iRelevant<relevantIndexes.getNormalOverlaps().size(); ++iRelevant) {
    normalTransmittors[iRelevant]->prepareTransmission(lattices);
  }
  if (periodicCommunication) {
    for (unsigned iRelevant=0; iRelevant<relevantIndexes.getPeriodicOverlaps().size(); ++iRelevant) {
      periodicTransmittors[iRelevant]->prepareTransmission(lattices);
    }
  }
  for (unsigned iRelevant=0; iRelevant<relevantIndexes.getNormalOverlaps().size(); ++iRelevant) {
    normalTransmittors[iRelevant]->executeTransmission(lattices);
  }
  if (periodicCommunication) {
    for (unsigned iRelevant=0; iRelevant<relevantIndexes.getPeriodicOverlaps().size(); ++iRelevant) {
      periodicTransmittors[iRelevant]->executeTransmission(lattices);
    }
  }
  for (unsigned iRelevant=0; iRelevant<relevantIndexes.getNormalOverlaps().size(); ++iRelevant) {
    normalTransmittors[iRelevant]->finalizeTransmission(lattices);
  }
  if (periodicCommunication) {
    for (unsigned iRelevant=0; iRelevant<relevantIndexes.getPeriodicOverlaps().size(); ++iRelevant) {
      periodicTransmittors[iRelevant]->finalizeTransmission(lattices);
    }
  }
}

template<typename T, template<typename U> class Lattice>
Cell<T,Lattice>& ParallelMultiBlockHandler3D<T,Lattice>::
getDistributedCell(std::vector<Cell<T,Lattice>*>& baseCell, bool hasBulkCell) const
{
  delete parallelDynamics;
  parallelDynamics = new ParallelDynamics<T,Lattice>(baseCell, hasBulkCell);
  distributedCell.defineDynamics(parallelDynamics);
  return distributedCell;
}

template<typename T, template<typename U> class Lattice>
Cell<T,Lattice> const& ParallelMultiBlockHandler3D<T,Lattice>::
getDistributedCell(std::vector<Cell<T,Lattice> const*>& baseCell, bool hasBulkCell) const
{
  delete parallelDynamics;
  parallelDynamics = new ConstParallelDynamics<T,Lattice>(baseCell, hasBulkCell);
  distributedCell.defineDynamics(parallelDynamics);
  return distributedCell;
}

template<typename T, template<typename U> class Lattice>
int ParallelMultiBlockHandler3D<T,Lattice>::locateLocally(int iX, int iY, int iZ,
    std::vector<int>& foundId,
    std::vector<int>& foundX,
    std::vector<int>& foundY,
    std::vector<int>& foundZ,
    bool& hasBulkCell, int guess) const
{
  hasBulkCell = false;
  // First, search in all blocks which are local to the current processor, including in the envelopes.
  //   These blocks are confined within the relevantIndexes.getBoundingBox(),
  //   so checking for inclusion in the relevantIndexes.getBoundingBox()
  //   eliminates most queries and thus enhances efficiency.
  if (util::contained(iX,iY,iZ, relevantIndexes.getBoundingBox())) {
    for (unsigned iBlock=0; iBlock < relevantIndexes.getBlocks().size(); ++iBlock) {
      BlockParameters3D const& parameters = dataDistribution.getBlockParameters(relevantIndexes.getBlocks()[iBlock]);
      BlockCoordinates3D const& envelope = parameters.getEnvelope();
      if (util::contained(iX,iY,iZ, envelope)) {
        BlockCoordinates3D const& bulk = parameters.getBulk();
        if (util::contained(iX,iY,iZ, bulk)) {
          hasBulkCell = true;
          foundId.insert(foundId.begin(), relevantIndexes.getBlocks()[iBlock]);
          foundX.insert(foundX.begin(), iX-envelope.x0);
          foundY.insert(foundY.begin(), iY-envelope.y0);
          foundZ.insert(foundZ.begin(), iZ-envelope.z0);
        }
        else {
          foundId.push_back(relevantIndexes.getBlocks()[iBlock]);
          foundX.push_back(iX-envelope.x0);
          foundY.push_back(iY-envelope.y0);
          foundZ.push_back(iZ-envelope.z0);
        }
      }
    }
  }
  // Here's a subtlety: with periodic boundary conditions, one may need to take into account
  //   a cell which is not inside the relevantIndexes.getBoundingBox(), because it's at the opposite boundary.
  //   Therefore, this loop checks all blocks which overlap with the current one by periodicity.
  for (unsigned iRelevant=0; iRelevant<relevantIndexes.getPeriodicOverlapWithMe().size(); ++iRelevant) {
    int iOverlap = relevantIndexes.getPeriodicOverlapWithMe()[iRelevant];
    Overlap3D const& overlap = dataDistribution.getPeriodicOverlap(iOverlap);
    if (util::contained(iX,iY,iZ, overlap.getOriginalCoordinates())) {
      int overlapId = overlap.getOverlapId();
      foundId.push_back(overlapId);
      BlockParameters3D const& parameters = dataDistribution.getBlockParameters(overlapId);
      foundX.push_back(parameters.toLocalX(iX-overlap.getShiftX()));
      foundY.push_back(parameters.toLocalY(iY-overlap.getShiftY()));
      foundZ.push_back(parameters.toLocalZ(iZ-overlap.getShiftZ()));
    }
  }
  return -1;
}

#endif  // PARALLEL_MODE_MPI

}  // namespace olb

#endif
