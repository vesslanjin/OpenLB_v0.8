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
 * Serializer for 2D multi data -- generic template code.
 */

#ifndef MULTI_SERIALIZER_2D_HH
#define MULTI_SERIALIZER_2D_HH

#include "complexGrids/mpiManager/mpiManager.h"
#include "multiSerializer2D.h"
#include "core/olbDebug.h"

namespace olb {

////////// class MultiSerializer2D ////////////////////////////

template<typename T>
MultiSerializer2D<T>::MultiSerializer2D (
  MultiSerializerPolicy2D<T> const& policy_, IndexOrdering::OrderingT ordering_ )
  : policy(policy_), ordering(ordering_),
    x0(0), x1(policy.getMultiData().getNx()-1), y0(0), y1(policy.getMultiData().getNy()-1),
    iX(x0), iY(y0),
    buffer(1) // this avoids buffer of size 0 which one cannot point to
{ }

template<typename T>
MultiSerializer2D<T>::MultiSerializer2D (
  MultiSerializerPolicy2D<T> const& policy_,
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering_ )
  : policy(policy_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_),
    iX(x0), iY(y0),
    buffer(1) // this avoids buffer of size 0 which one cannot point to
{ }

template<typename T>
size_t MultiSerializer2D<T>::getSize() const {
  if (ordering==IndexOrdering::memorySaving) {
    return policy.getMultiData().getNumAllocatedBulkCells() * (size_t)policy.getElementSize();
  }
  else {
    return (size_t)(x1-x0+1) * (size_t)(y1-y0+1) * (size_t)policy.getElementSize();
  }
}

template<typename T>
void MultiSerializer2D<T>::computeBufferAlongY(int nextLattice, int nextChunkSize) const {
  int bufferSize = nextChunkSize*policy.getElementSize();
  BlockParameters2D const& param = policy.getMultiData().getBlockParameters(nextLattice);
  if (policy.isAllocated(nextLattice)) {
    // The +1 avoids having a buffer of size 0 which one cannot point to
    buffer.resize(bufferSize+1);
    int localX = param.toLocalX(iX);
    int localY = param.toLocalY(iY);
    for (int iChunk=0; iChunk<nextChunkSize; ++localY, ++iChunk) {
      policy.serializeElement(nextLattice, localX, localY, &buffer[policy.getElementSize()*iChunk]);
    }
  }
  communicateBuffer(bufferSize, param.getProcId(), policy.isAllocated(nextLattice));
}

template<typename T>
void MultiSerializer2D<T>::computeBufferAlongX(int nextLattice, int nextChunkSize) const {
  int bufferSize = nextChunkSize*policy.getElementSize();
  BlockParameters2D const& param = policy.getMultiData().getBlockParameters(nextLattice);
  if (policy.isAllocated(nextLattice)) {
    // The +1 avoids having a buffer of size 0 which one cannot point to
    buffer.resize(bufferSize+1);
    int localX = param.toLocalX(iX);
    int localY = param.toLocalY(iY);
    for (int iChunk=0; iChunk<nextChunkSize; ++localX, ++iChunk) {
      policy.serializeElement(nextLattice, localX, localY, &buffer[policy.getElementSize()*iChunk]);
    }
  }
  communicateBuffer(bufferSize, param.getProcId(), policy.isAllocated(nextLattice));
}

template<typename T>
void MultiSerializer2D<T>::communicateBuffer (
  int bufferSize, int fromProc, bool isAllocated) const
{
#ifdef PARALLEL_MODE_MPI
  int dummyMessage;
  if (isAllocated && !singleton::mpi().isMainProcessor()) {
    singleton::mpi().receive(&dummyMessage, 1, 0);
    singleton::mpi().send(&buffer[0], bufferSize, 0);
  }
  if (!isAllocated && singleton::mpi().isMainProcessor()) {
    // The +1 avoids having a buffer of size 0 which one cannot point to
    buffer.resize(bufferSize+1);
    singleton::mpi().send(&dummyMessage, 1, fromProc);
    singleton::mpi().receive(&buffer[0], bufferSize, fromProc);
  }
#endif
}

template<typename T>
void MultiSerializer2D<T>::fillBufferWithZeros(int nextChunkSize) const {
  int bufferSize = nextChunkSize*policy.getElementSize();
#ifdef PARALLEL_MODE_MPI
  if (singleton::mpi().isMainProcessor()) {
#endif
    // The +1 avoids having a buffer of size 0 which one cannot point to
    buffer.resize(bufferSize+1);
    for (int iChunk=0; iChunk<nextChunkSize; ++iChunk) {
      for (int iCell=0; iCell<policy.getElementSize(); ++iCell) {
        buffer[iCell + policy.getElementSize()*iChunk] = T();
      }
    }
#ifdef PARALLEL_MODE_MPI
  }
#endif
}

template<typename T>
const T* MultiSerializer2D<T>::getNextDataBuffer(size_t& bufferSize) const {
  OLB_PRECONDITION( !isEmpty() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    int nextLattice, nextChunkSize;
    bool hasData = policy.getMultiData().getNextChunkY(iX,iY, nextLattice, nextChunkSize);
    if (iY+nextChunkSize>y1+1) {
      nextChunkSize = y1-iY+1;
    }
    if (hasData) {
      computeBufferAlongY(nextLattice, nextChunkSize);
      bufferSize = nextChunkSize*policy.getElementSize();
    }
    else {
      if (ordering==IndexOrdering::forward) {
        fillBufferWithZeros(nextChunkSize);
        bufferSize = nextChunkSize*policy.getElementSize();
      }
      else {
        bufferSize = 0;
      }
    }
    iY += nextChunkSize;
    if (iY > y1) {
      iY = y0;
      ++iX;
    }
  }
  else {
    int nextLattice, nextChunkSize;
    bool hasData = policy.getMultiData().getNextChunkX(iX,iY, nextLattice, nextChunkSize);
    if (iX+nextChunkSize>x1+1) {
      nextChunkSize = x1-iX+1;
    }
    if (hasData) {
      computeBufferAlongX(nextLattice, nextChunkSize);
      bufferSize = nextChunkSize*policy.getElementSize();
    }
    else {
      fillBufferWithZeros(nextChunkSize);
    }
    iX += nextChunkSize;
    if (iX > x1) {
      iX = x0;
      ++iY;
    }
  }
  return &buffer[0];
}

template<typename T>
bool MultiSerializer2D<T>::isEmpty() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iY > y1;
  }
}


////////// class MultiUnSerializer2D ////////////////////////////

template<typename T>
MultiUnSerializer2D<T>::MultiUnSerializer2D (
  MultiUnSerializerPolicy2D<T>& policy_,
  IndexOrdering::OrderingT ordering_ )
  : policy(policy_), ordering(ordering_),
    x0(0), x1(policy.getMultiData().getNx()-1), y0(0), y1(policy.getMultiData().getNy()-1),
    iX(x0), iY(y0),
    buffer(1) // this avoids buffer of size 0 which one cannot point to
{ }

template<typename T>
MultiUnSerializer2D<T>::MultiUnSerializer2D (
  MultiUnSerializerPolicy2D<T>& policy_,
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering_ )
  : policy(policy_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_),
    iX(x0), iY(y0),
    buffer(1) // this avoids buffer of size 0 which one cannot point to
{ }

template<typename T>
size_t MultiUnSerializer2D<T>::getSize() const {
  if (ordering==IndexOrdering::memorySaving) {
    return policy.getMultiData().getNumAllocatedBulkCells() * (size_t)policy.getElementSize();
  }
  else {
    return (size_t)(x1-x0+1) * (size_t)(y1-y0+1) * (size_t)policy.getElementSize();
  }
}

template<typename T>
T* MultiUnSerializer2D<T>::getNextDataBuffer(size_t& bufferSize) {
  OLB_PRECONDITION( !isFull() );
  int nextLattice, nextChunkSize;
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    bool hasData = policy.getMultiData().getNextChunkY(iX,iY, nextLattice, nextChunkSize);
    if (iY+nextChunkSize>y1+1) {
      nextChunkSize = y1-iY+1;
    }
    bufferSize = nextChunkSize * policy.getElementSize();
    if (ordering==IndexOrdering::memorySaving && !hasData) {
      bufferSize = 0;
    }
  }
  else {
    policy.getMultiData().getNextChunkX(iX,iY, nextLattice, nextChunkSize);
    if (iX+nextChunkSize>x1+1) {
      nextChunkSize = x1-iX+1;
    }
    bufferSize = nextChunkSize * policy.getElementSize();
  }
#ifdef PARALLEL_MODE_MPI
  if (singleton::mpi().isMainProcessor()) {
#endif
    // The +1 avoids having a buffer of size 0 which one cannot point to
    buffer.resize(bufferSize+1);
#ifdef PARALLEL_MODE_MPI
  }
#endif
  return &buffer[0];
}

template<typename T>
void MultiUnSerializer2D<T>::fillBufferAlongY(int nextLattice, int nextChunkSize) {
  int bufferSize = nextChunkSize*policy.getElementSize();
  BlockParameters2D const& param = policy.getMultiData().getBlockParameters(nextLattice);
  communicateBuffer(bufferSize, param.getProcId(), policy.isAllocated(nextLattice));
  if (policy.isAllocated(nextLattice)) {
    int localX = param.toLocalX(iX);
    int localY = param.toLocalY(iY);
    for (int iChunk=0; iChunk<nextChunkSize; ++localY, ++iChunk) {
      policy.unSerializeElement(nextLattice, localX, localY, &buffer[policy.getElementSize()*iChunk]);
    }
  }
}

template<typename T>
void MultiUnSerializer2D<T>::fillBufferAlongX(int nextLattice, int nextChunkSize) {
  int bufferSize = nextChunkSize*policy.getElementSize();
  BlockParameters2D const& param = policy.getMultiData().getBlockParameters(nextLattice);
  communicateBuffer(bufferSize, param.getProcId(), policy.isAllocated(nextLattice));
  if (policy.isAllocated(nextLattice)) {
    // The +1 avoids having a buffer of size 0 which one cannot point to
    buffer.resize(bufferSize+1);
    int localX = param.toLocalX(iX);
    int localY = param.toLocalY(iY);
    for (int iChunk=0; iChunk<nextChunkSize; ++localX, ++iChunk) {
      policy.unSerializeElement(nextLattice, localX, localY, &buffer[policy.getElementSize()*iChunk]);
    }
  }
}

template<typename T>
void MultiUnSerializer2D<T>::communicateBuffer (
  int bufferSize, int toProc, bool isAllocated ) const
{
#ifdef PARALLEL_MODE_MPI
  if (isAllocated && !singleton::mpi().isMainProcessor()) {
    // The +1 avoids having a buffer of size 0 which one cannot point to
    buffer.resize(bufferSize+1);
    singleton::mpi().receive(&buffer[0], bufferSize, 0);
  }
  if (!isAllocated && singleton::mpi().isMainProcessor()) {
    singleton::mpi().send(&buffer[0], bufferSize, toProc);
  }
#endif
}

template<typename T>
void MultiUnSerializer2D<T>::commitData() {
  OLB_PRECONDITION( !isFull() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    int nextLattice, nextChunkSize;
    bool hasData = policy.getMultiData().getNextChunkY(iX,iY, nextLattice, nextChunkSize);
    if (iY+nextChunkSize>y1+1) {
      nextChunkSize = y1-iY+1;
    }
    if (hasData) {
      fillBufferAlongY(nextLattice, nextChunkSize);
    }
    iY += nextChunkSize;
    if (iY > y1) {
      iY = y0;
      ++iX;
    }
  }
  else {
    int nextLattice, nextChunkSize;
    bool hasData = policy.getMultiData().getNextChunkX(iX,iY, nextLattice, nextChunkSize);
    if (iX+nextChunkSize>x1+1) {
      nextChunkSize = x1-iX+1;
    }
    if (hasData) {
      fillBufferAlongX(nextLattice, nextChunkSize);
    }
    iX += nextChunkSize;
    if (iX > x1) {
      iX = x0;
      ++iY;
    }
  }
}

template<typename T>
bool MultiUnSerializer2D<T>::isFull() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iY > y1;
  }
}

}

#endif // defined MULTI_SERIALIZER_2D_HH

