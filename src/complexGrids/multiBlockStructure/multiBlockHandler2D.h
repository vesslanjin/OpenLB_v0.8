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
 * Handler for 2D multiblock structure -- header file.
 */
#ifndef MULTI_BLOCK_HANDLER_2D_H
#define MULTI_BLOCK_HANDLER_2D_H

#include "complexGrids/mpiManager/mpiManager.h"
#include "core/blockLattice2D.h"
#include "core/cell.h"
#include "multiDataGeometry2D.h"
#include <vector>


namespace olb {

template<typename T, template<typename U> class Lattice>
struct MultiBlockHandler2D {
  typedef std::vector<BlockLattice2D<T,Lattice>*> BlockVector2D;

  virtual ~MultiBlockHandler2D() { }
  virtual int getNx() const =0;
  virtual int getNy() const =0;
  virtual MultiDataDistribution2D const& getMultiDataDistribution() const =0;
  virtual RelevantIndexes2D const& getRelevantIndexes() const =0;
  virtual bool getLocalEnvelope(int iBlock, int& lx, int& ly) const =0;
  virtual T reduceSum(T localSum) const =0;
  virtual T reduceAverage(T localAverage, T localWeight) const =0;
  virtual T reduceMin(T localMin) const =0;
  virtual T reduceMax(T localMax) const =0;
  virtual void broadCastCell(Cell<T,Lattice>& cell, int fromBlock) const =0;
  virtual void broadCastScalar(T& scalar, int fromBlock) const =0;
  virtual void broadCastVector(T vect[Lattice<T>::d], int fromBlock) const =0;
  virtual void connectBoundaries(BlockVector2D& lattices, bool periodicCommunication) const =0;
  virtual Cell<T,Lattice>& getDistributedCell(std::vector<Cell<T,Lattice>*>& baseCell,
      bool hasBulkCell) const =0;
  virtual Cell<T,Lattice> const& getDistributedCell(std::vector<Cell<T,Lattice> const*>& baseCell,
      bool hasBulkCell) const =0;
  virtual int locateLocally(int iX, int iY, std::vector<int>& foundId, std::vector<int>& foundX,
                            std::vector<int>& foundY, bool& hasBulkCell, int guess=0) const =0;
};

template<typename T, template<typename U> class Lattice>
class SerialMultiBlockHandler2D : public MultiBlockHandler2D<T,Lattice> {
public:
  typedef std::vector<BlockLattice2D<T,Lattice>*> BlockVector2D;
public:
  SerialMultiBlockHandler2D(MultiDataDistribution2D const& dataDistribution_);
  virtual int getNx() const;
  virtual int getNy() const;
  virtual MultiDataDistribution2D const& getMultiDataDistribution() const;
  virtual RelevantIndexes2D const& getRelevantIndexes() const;
  virtual bool getLocalEnvelope(int iBlock, int& lx, int& ly) const;
  virtual T reduceSum(T localSum) const;
  virtual T reduceAverage(T localAverage, T localWeight) const;
  virtual T reduceMin(T localMin) const;
  virtual T reduceMax(T localMax) const;
  virtual void broadCastCell(Cell<T,Lattice>& cell, int fromBlock) const;
  virtual void broadCastScalar(T& scalar, int fromBlock) const;
  virtual void broadCastVector(T vect[Lattice<T>::d], int fromBlock) const;
  virtual void connectBoundaries(BlockVector2D& lattices, bool periodicCommunication) const;
  virtual Cell<T,Lattice>& getDistributedCell(std::vector<Cell<T,Lattice>*>& baseCell,
      bool hasBulkCell) const;
  virtual Cell<T,Lattice> const& getDistributedCell(std::vector<Cell<T,Lattice> const*>& baseCell,
      bool hasBulkCell) const;
  virtual int locateLocally(int iX, int iY, std::vector<int>& foundId, std::vector<int>& foundX,
                            std::vector<int>& foundY, bool& hasBulkCell, int guess=0) const;
private:
  void copyOverlap(Overlap2D const& overlap, BlockVector2D& lattices) const;
private:
  MultiDataDistribution2D dataDistribution;
  RelevantIndexes2D       relevantIndexes;
};


#ifdef PARALLEL_MODE_MPI

template<typename T, template<typename U> class Lattice>
class DataTransmittor2D {
public:
  typedef std::vector<BlockLattice2D<T,Lattice>*> BlockVector2D;
public:
  virtual ~DataTransmittor2D() { }
  virtual void prepareTransmission(BlockVector2D& lattices) =0;
  virtual void executeTransmission(BlockVector2D& lattices) =0;
  virtual void finalizeTransmission(BlockVector2D& lattices) =0;
};

template<typename T, template<typename U> class Lattice>
class BlockingDataTransmittor2D : public DataTransmittor2D<T,Lattice> {
public:
  typedef std::vector<BlockLattice2D<T,Lattice>*> BlockVector2D;
public:
  BlockingDataTransmittor2D(Overlap2D const& overlap, MultiDataDistribution2D const& dataDistribution);
  virtual void prepareTransmission(BlockVector2D& lattices);
  virtual void executeTransmission(BlockVector2D& lattices);
  virtual void finalizeTransmission(BlockVector2D& lattices);
private:
  std::vector<char> buffer;
  int originalId, overlapId;
  int originalProc, overlapProc;
  BlockCoordinates2D originalCoords, overlapCoords;
  int sizeOfCell;
  int bufferSize;
  enum {sender, receiver, senderAndReceiver, nothing} myRole;
};

template<typename T, template<typename U> class Lattice>
class NonBlockingDataTransmittor2D : public DataTransmittor2D<T,Lattice> {
public:
  typedef std::vector<BlockLattice2D<T,Lattice>*> BlockVector2D;
public:
  NonBlockingDataTransmittor2D(Overlap2D const& overlap, MultiDataDistribution2D const& dataDistribution);
  virtual void prepareTransmission(BlockVector2D& lattices);
  virtual void executeTransmission(BlockVector2D& lattices);
  virtual void finalizeTransmission(BlockVector2D& lattices);
private:
  std::vector<T> buffer;
  int originalId, overlapId;
  int originalProc, overlapProc;
  BlockCoordinates2D originalCoords, overlapCoords;
  int sizeOfCell;
  int bufferSize;
  enum {sender, receiver, senderAndReceiver, nothing} myRole;
  MPI_Request request;
  MPI_Status  status;
};

template<typename T, template<typename U> class Lattice>
class ParallelMultiBlockHandler2D : public MultiBlockHandler2D<T,Lattice> {
public:
  typedef std::vector<BlockLattice2D<T,Lattice>*> BlockVector2D;
public:
  ParallelMultiBlockHandler2D(MultiDataDistribution2D const& dataDistribution_);
  ~ParallelMultiBlockHandler2D();
  virtual int getNx() const;
  virtual int getNy() const;
  virtual MultiDataDistribution2D const& getMultiDataDistribution() const;
  virtual RelevantIndexes2D const& getRelevantIndexes() const;
  virtual bool getLocalEnvelope(int iBlock, int& lx, int& ly) const;
  virtual T reduceSum(T localSum) const;
  virtual T reduceAverage(T localAverage, T localWeight) const;
  virtual T reduceMin(T localMin) const;
  virtual T reduceMax(T localMax) const;
  virtual void broadCastCell(Cell<T,Lattice>& cell, int fromBlock) const;
  virtual void broadCastScalar(T& scalar, int fromBlock) const;
  virtual void broadCastVector(T vect[Lattice<T>::d], int fromBlock) const;
  virtual void connectBoundaries(BlockVector2D& lattices, bool periodicCommunication) const;
  virtual Cell<T,Lattice>& getDistributedCell(std::vector<Cell<T,Lattice>*>& baseCell, bool hasBulkCell) const;
  virtual Cell<T,Lattice> const& getDistributedCell(std::vector<Cell<T,Lattice> const*>& baseCell,
      bool hasBulkCell) const;
  virtual int locateLocally(int iX, int iY, std::vector<int>& foundId, std::vector<int>& foundX,
                            std::vector<int>& foundY, bool& hasBulkCell, int guess=0) const;
private:
  MultiDataDistribution2D dataDistribution;
  RelevantIndexes2D       relevantIndexes;
  std::vector<DataTransmittor2D<T,Lattice>*> normalTransmittors;
  std::vector<DataTransmittor2D<T,Lattice>*> periodicTransmittors;
  mutable Cell<T,Lattice> distributedCell;
  mutable Dynamics<T,Lattice>* parallelDynamics;
};
#endif

}  // namespace olb

#endif
