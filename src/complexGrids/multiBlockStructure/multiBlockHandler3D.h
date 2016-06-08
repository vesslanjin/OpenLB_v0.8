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
 * Handler for 3D multiblock structure -- header file.
 */
#ifndef MULTI_BLOCK_HANDLER_3D_H
#define MULTI_BLOCK_HANDLER_3D_H

#include "complexGrids/mpiManager/mpiManager.h"
#include "core/blockLattice3D.h"
#include "core/cell.h"
#include "multiDataGeometry3D.h"
#include <vector>


namespace olb {

template<typename T, template<typename U> class Lattice>
struct MultiBlockHandler3D {
  typedef std::vector<BlockLattice3D<T,Lattice>*> BlockVector3D;

  virtual ~MultiBlockHandler3D() { }
  virtual int getNx() const =0;
  virtual int getNy() const =0;
  virtual int getNz() const =0;
  virtual MultiDataDistribution3D const& getMultiDataDistribution() const =0;
  virtual RelevantIndexes3D const& getRelevantIndexes() const =0;
  virtual bool getLocalEnvelope(int iBlock, int& lx, int& ly, int& lz) const =0;
  virtual T reduceSum(T localSum) const =0;
  virtual T reduceAverage(T localAverage, T localWeight) const =0;
  virtual T reduceMin(T localMin) const =0;
  virtual T reduceMax(T localMax) const =0;
  virtual void broadCastCell(Cell<T,Lattice>& cell, int fromBlock) const =0;
  virtual void broadCastScalar(T& scalar, int fromBlock) const =0;
  virtual void broadCastVector(T vect[Lattice<T>::d], int fromBlock) const =0;
  virtual void connectBoundaries(BlockVector3D& lattices, bool periodicCommunication) const =0;
  virtual Cell<T,Lattice>& getDistributedCell(std::vector<Cell<T,Lattice>*>& baseCell,
      bool hasBulkCell) const =0;
  virtual Cell<T,Lattice> const& getDistributedCell(std::vector<Cell<T,Lattice> const*>& baseCell,
      bool hasBulkCell) const =0;
  virtual int locateLocally(int iX, int iY, int iZ, std::vector<int>& foundId,
                            std::vector<int>& foundX, std::vector<int>& foundY,
                            std::vector<int>& foundZ, bool& hasBulkCell, int guess=0) const =0;
};

template<typename T, template<typename U> class Lattice>
class SerialMultiBlockHandler3D : public MultiBlockHandler3D<T,Lattice> {
public:
  typedef std::vector<BlockLattice3D<T,Lattice>*> BlockVector3D;
public:
  SerialMultiBlockHandler3D(MultiDataDistribution3D const& dataDistribution_);
  virtual int getNx() const;
  virtual int getNy() const;
  virtual int getNz() const;
  virtual MultiDataDistribution3D const& getMultiDataDistribution() const;
  virtual RelevantIndexes3D const& getRelevantIndexes() const;
  virtual bool getLocalEnvelope(int iBlock, int& lx, int& ly, int& lz) const;
  virtual T reduceSum(T localSum) const;
  virtual T reduceAverage(T localAverage, T localWeight) const;
  virtual T reduceMin(T localMin) const;
  virtual T reduceMax(T localMax) const;
  virtual void broadCastCell(Cell<T,Lattice>& cell, int fromBlock) const;
  virtual void broadCastScalar(T& scalar, int fromBlock) const;
  virtual void broadCastVector(T vect[Lattice<T>::d], int fromBlock) const;
  virtual void connectBoundaries(BlockVector3D& lattices, bool periodicCommunication) const;
  virtual Cell<T,Lattice>& getDistributedCell(std::vector<Cell<T,Lattice>*>& baseCell,
      bool hasBulkCell) const;
  virtual Cell<T,Lattice> const& getDistributedCell(std::vector<Cell<T,Lattice> const*>& baseCell,
      bool hasBulkCell) const;
  virtual int locateLocally(int iX, int iY, int iZ, std::vector<int>& foundId,
                            std::vector<int>& foundX, std::vector<int>& foundY,
                            std::vector<int>& foundZ, bool& hasBulkCell, int guess=0) const;
private:
  void copyOverlap(Overlap3D const& overlap, BlockVector3D& lattices) const;
private:
  MultiDataDistribution3D dataDistribution;
  RelevantIndexes3D       relevantIndexes;
};


#ifdef PARALLEL_MODE_MPI

template<typename T, template<typename U> class Lattice>
class DataTransmittor3D {
public:
  typedef std::vector<BlockLattice3D<T,Lattice>*> BlockVector3D;
public:
  virtual ~DataTransmittor3D() { }
  virtual void prepareTransmission(BlockVector3D& lattices) =0;
  virtual void executeTransmission(BlockVector3D& lattices) =0;
  virtual void finalizeTransmission(BlockVector3D& lattices) =0;
};

template<typename T, template<typename U> class Lattice>
class BlockingDataTransmittor3D : public DataTransmittor3D<T,Lattice> {
public:
  typedef std::vector<BlockLattice3D<T,Lattice>*> BlockVector3D;
public:
  BlockingDataTransmittor3D(Overlap3D const& overlap, MultiDataDistribution3D const& dataDistribution);
  virtual void prepareTransmission(BlockVector3D& lattices);
  virtual void executeTransmission(BlockVector3D& lattices);
  virtual void finalizeTransmission(BlockVector3D& lattices);
private:
  std::vector<T> buffer;
  int originalId, overlapId;
  int originalProc, overlapProc;
  BlockCoordinates3D originalCoords, overlapCoords;
  int sizeOfCell;
  int bufferSize;
  enum {sender, receiver, senderAndReceiver, nothing} myRole;
};

template<typename T, template<typename U> class Lattice>
class NonBlockingDataTransmittor3D : public DataTransmittor3D<T,Lattice> {
public:
  typedef std::vector<BlockLattice3D<T,Lattice>*> BlockVector3D;
public:
  NonBlockingDataTransmittor3D(Overlap3D const& overlap, MultiDataDistribution3D const& dataDistribution);
  virtual void prepareTransmission(BlockVector3D& lattices);
  virtual void executeTransmission(BlockVector3D& lattices);
  virtual void finalizeTransmission(BlockVector3D& lattices);
private:
  std::vector<T> buffer;
  int originalId, overlapId;
  int originalProc, overlapProc;
  BlockCoordinates3D originalCoords, overlapCoords;
  int sizeOfCell;
  int bufferSize;
  enum {sender, receiver, senderAndReceiver, nothing} myRole;
  MPI_Request request;
  MPI_Status  status;
};

template<typename T, template<typename U> class Lattice>
class ParallelMultiBlockHandler3D : public MultiBlockHandler3D<T,Lattice> {
public:
  typedef std::vector<BlockLattice3D<T,Lattice>*> BlockVector3D;
public:
  ParallelMultiBlockHandler3D(MultiDataDistribution3D const& dataDistribution_);
  ~ParallelMultiBlockHandler3D();
  virtual int getNx() const;
  virtual int getNy() const;
  virtual int getNz() const;
  virtual MultiDataDistribution3D const& getMultiDataDistribution() const;
  virtual RelevantIndexes3D const& getRelevantIndexes() const;
  virtual bool getLocalEnvelope(int iBlock, int& lx, int& ly, int& lz) const;
  virtual T reduceSum(T localSum) const;
  virtual T reduceAverage(T localAverage, T localWeight) const;
  virtual T reduceMin(T localMin) const;
  virtual T reduceMax(T localMax) const;
  virtual void broadCastCell(Cell<T,Lattice>& cell, int fromBlock) const;
  virtual void broadCastScalar(T& scalar, int fromBlock) const;
  virtual void broadCastVector(T vect[Lattice<T>::d], int fromBlock) const;
  virtual void connectBoundaries(BlockVector3D& lattices, bool periodicCommunication) const;
  virtual Cell<T,Lattice>& getDistributedCell(std::vector<Cell<T,Lattice>*>& baseCell,
      bool hasBulkCell) const;
  virtual Cell<T,Lattice> const& getDistributedCell(std::vector<Cell<T,Lattice> const*>& baseCell,
      bool hasBulkCell) const;
  virtual int locateLocally(int iX, int iY, int iZ, std::vector<int>& foundId,
                            std::vector<int>& foundX, std::vector<int>& foundY,
                            std::vector<int>& foundZ, bool& hasBulkCell, int guess=0) const;
private:
  MultiDataDistribution3D dataDistribution;
  RelevantIndexes3D       relevantIndexes;
  std::vector<DataTransmittor3D<T,Lattice>*> normalTransmittors;
  std::vector<DataTransmittor3D<T,Lattice>*> periodicTransmittors;
  mutable Cell<T,Lattice> distributedCell;
  mutable Dynamics<T,Lattice>* parallelDynamics;
};
#endif

}  // namespace olb

#endif
