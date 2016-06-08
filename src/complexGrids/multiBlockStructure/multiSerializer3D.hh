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
 * Serializer for 3D multi data -- generic template code.
 */

#ifndef MULTI_SERIALIZER_3D_HH
#define MULTI_SERIALIZER_3D_HH

#include "complexGrids/mpiManager/mpiManager.h"
#include "multiSerializer3D.h"
#include "core/olbDebug.h"

namespace olb {

////////// class MultiSerializer3D ////////////////////////////

template<typename T>
MultiSerializer3D<T>::MultiSerializer3D (
  MultiSerializerPolicy3D<T> const& policy_, IndexOrdering::OrderingT ordering_ )
  : policy(policy_), ordering(ordering_),
    x0(0), x1(policy.getMultiData().getNx()-1), y0(0), y1(policy.getMultiData().getNy()-1),
    z0(0), z1(policy.getMultiData().getNz()-1),
    iX(x0), iY(y0), iZ(z0),
    buffer(1) // this avoids buffer of size 0 which one cannot point to
{ }

template<typename T>
MultiSerializer3D<T>::MultiSerializer3D (
  MultiSerializerPolicy3D<T> const& policy_,
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering_ )
  : policy(policy_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_), z0(z0_), z1(z1_),
    iX(x0), iY(y0), iZ(z0),
    buffer(1) // this avoids buffer of size 0 which one cannot point to
{ }

template<typename T>
size_t MultiSerializer3D<T>::getSize() const {
  if (ordering==IndexOrdering::memorySaving) {
    return policy.getMultiData().getNumAllocatedBulkCells() * (size_t)policy.getElementSize();
  }
  else {
    return (size_t)(x1-x0+1) * (size_t)(y1-y0+1) * (size_t)(z1-z0+1) * (size_t)policy.getElementSize();
  }
}

template<typename T>
void MultiSerializer3D<T>::computeBufferAlongZ(int nextLattice, int nextChunkSize) const {
  int bufferSize = nextChunkSize*policy.getElementSize();
  BlockParameters3D const& param = policy.getMultiData().getBlockParameters(nextLattice);
  if (policy.isAllocated(nextLattice)) {
    // The +1 avoids having a buffer of size 0 which one cannot point to
    buffer.resize(bufferSize+1);
    int localX = param.toLocalX(iX);
    int localY = param.toLocalY(iY);
    int localZ = param.toLocalZ(iZ);
    for (int iChunk=0; iChunk<nextChunkSize; ++localZ, ++iChunk) {
      policy.serializeElement(nextLattice, localX, localY, localZ, &buffer[policy.getElementSize()*iChunk]);
    }
  }
  communicateBuffer(bufferSize, param.getProcId(), policy.isAllocated(nextLattice));
}

template<typename T>
void MultiSerializer3D<T>::computeBufferAlongX(int nextLattice, int nextChunkSize) const {
  int bufferSize = nextChunkSize*policy.getElementSize();
  BlockParameters3D const& param = policy.getMultiData().getBlockParameters(nextLattice);
  if (policy.isAllocated(nextLattice)) {
    // The +1 avoids having a buffer of size 0 which one cannot point to
    buffer.resize(bufferSize+1);
    int localX = param.toLocalX(iX);
    int localY = param.toLocalY(iY);
    int localZ = param.toLocalZ(iZ);
    for (int iChunk=0; iChunk<nextChunkSize; ++localX, ++iChunk) {
      policy.serializeElement(nextLattice, localX, localY, localZ, &buffer[policy.getElementSize()*iChunk]);
    }
  }
  communicateBuffer(bufferSize, param.getProcId(), policy.isAllocated(nextLattice));
}

template<typename T>
void MultiSerializer3D<T>::communicateBuffer (
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
void MultiSerializer3D<T>::fillBufferWithZeros(int nextChunkSize) const {
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
const T* MultiSerializer3D<T>::getNextDataBuffer(size_t& bufferSize) const {
  OLB_PRECONDITION( !isEmpty() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    int nextLattice, nextChunkSize;
    bool hasData = policy.getMultiData().getNextChunkZ(iX,iY,iZ, nextLattice, nextChunkSize);
    if (iZ+nextChunkSize>z1+1) {
      nextChunkSize = z1-iZ+1;
    }
    if (hasData) {
      computeBufferAlongZ(nextLattice, nextChunkSize);
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
    iZ += nextChunkSize;
    if (iZ > z1) {
      iZ = z0;
      ++iY;
      if (iY > y1) {
        iY = y0;
        ++iX;
      }
    }
  }
  else {
    int nextLattice, nextChunkSize;
    bool hasData = policy.getMultiData().getNextChunkX(iX,iY,iZ, nextLattice, nextChunkSize);
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
      if (iY > y1) {
        iY = y0;
        ++iZ;
      }
    }
  }
  return &buffer[0];
}

template<typename T>
bool MultiSerializer3D<T>::isEmpty() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iZ > z1;
  }
}


////////// class MultiUnSerializer3D ////////////////////////////

template<typename T>
MultiUnSerializer3D<T>::MultiUnSerializer3D (
  MultiUnSerializerPolicy3D<T>& policy_,
  IndexOrdering::OrderingT ordering_ )
  : policy(policy_), ordering(ordering_),
    x0(0), x1(policy.getMultiData().getNx()-1), y0(0), y1(policy.getMultiData().getNy()-1),
    z0(0), z1(policy.getMultiData().getNz()-1),
    iX(x0), iY(y0), iZ(z0),
    buffer(1) // this avoids buffer of size 0 which one cannot point to
{ }

template<typename T>
MultiUnSerializer3D<T>::MultiUnSerializer3D (
  MultiUnSerializerPolicy3D<T>& policy_,
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering_ )
  : policy(policy_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_), z0(z0_), z1(z1_),
    iX(x0), iY(y0), iZ(z0),
    buffer(1) // this avoids buffer of size 0 which one cannot point to
{ }

template<typename T>
size_t MultiUnSerializer3D<T>::getSize() const {
  if (ordering==IndexOrdering::memorySaving) {
    return policy.getMultiData().getNumAllocatedBulkCells() * (size_t)policy.getElementSize();
  }
  else {
    return (size_t)(x1-x0+1) * (size_t)(y1-y0+1) * (size_t)(z1-z0+1) * (size_t)policy.getElementSize();
  }
}

template<typename T>
T* MultiUnSerializer3D<T>::getNextDataBuffer(size_t& bufferSize) {
  OLB_PRECONDITION( !isFull() );
  int nextLattice, nextChunkSize;
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    bool hasData = policy.getMultiData().getNextChunkZ(iX,iY,iZ, nextLattice, nextChunkSize);
    if (iZ+nextChunkSize>z1+1) {
      nextChunkSize = z1-iZ+1;
    }
    bufferSize = nextChunkSize * policy.getElementSize();
    if (ordering==IndexOrdering::memorySaving && !hasData) {
      bufferSize = 0;
    }
  }
  else {
    policy.getMultiData().getNextChunkX(iX,iY,iZ, nextLattice, nextChunkSize);
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
void MultiUnSerializer3D<T>::fillBufferAlongZ(int nextLattice, int nextChunkSize) {
  int bufferSize = nextChunkSize*policy.getElementSize();
  BlockParameters3D const& param = policy.getMultiData().getBlockParameters(nextLattice);
  communicateBuffer(bufferSize, param.getProcId(), policy.isAllocated(nextLattice));
  if (policy.isAllocated(nextLattice)) {
    int localX = param.toLocalX(iX);
    int localY = param.toLocalY(iY);
    int localZ = param.toLocalZ(iZ);
    for (int iChunk=0; iChunk<nextChunkSize; ++localZ, ++iChunk) {
      policy.unSerializeElement(nextLattice, localX, localY, localZ,
                                &buffer[policy.getElementSize()*iChunk]);
    }
  }
}

template<typename T>
void MultiUnSerializer3D<T>::fillBufferAlongX(int nextLattice, int nextChunkSize) {
  int bufferSize = nextChunkSize*policy.getElementSize();
  BlockParameters3D const& param = policy.getMultiData().getBlockParameters(nextLattice);
  communicateBuffer(bufferSize, param.getProcId(), policy.isAllocated(nextLattice));
  if (policy.isAllocated(nextLattice)) {
    // The +1 avoids having a buffer of size 0 which one cannot point to
    buffer.resize(bufferSize+1);
    int localX = param.toLocalX(iX);
    int localY = param.toLocalY(iY);
    int localZ = param.toLocalZ(iZ);
    for (int iChunk=0; iChunk<nextChunkSize; ++localX, ++iChunk) {
      policy.unSerializeElement(nextLattice, localX, localY, localZ, &buffer[policy.getElementSize()*iChunk]);
    }
  }
}

template<typename T>
void MultiUnSerializer3D<T>::communicateBuffer (
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
void MultiUnSerializer3D<T>::commitData() {
  OLB_PRECONDITION( !isFull() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    int nextLattice, nextChunkSize;
    bool hasData = policy.getMultiData().getNextChunkZ(iX,iY,iZ, nextLattice, nextChunkSize);
    if (iZ+nextChunkSize>z1+1) {
      nextChunkSize = z1-iZ+1;
    }
    if (hasData) {
      fillBufferAlongZ(nextLattice, nextChunkSize);
    }
    iZ += nextChunkSize;
    if (iZ > z1) {
      iZ = z0;
      ++iY;
      if (iY > y1) {
        iY = y0;
        ++iX;
      }
    }
  }
  else {
    int nextLattice, nextChunkSize;
    bool hasData = policy.getMultiData().getNextChunkX(iX,iY,iZ, nextLattice, nextChunkSize);
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
      if (iY > y1) {
        iY = y0;
        ++iZ;
      }
    }
  }
}

template<typename T>
bool MultiUnSerializer3D<T>::isFull() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iZ > z1;
  }
}

}

#endif // defined MULTI_SERIALIZER_3D_HH

