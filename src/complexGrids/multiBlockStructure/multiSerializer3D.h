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
 * Serializer for 3D multi data -- header file.
 */

#ifndef MULTI_SERIALIZER_3D_H
#define MULTI_SERIALIZER_3D_H

#include "core/serializer.h"
#include "multiDataGeometry3D.h"

namespace olb {

template<typename T>
struct MultiSerializerPolicy3D {
  virtual ~MultiSerializerPolicy3D() { }
  virtual int getElementSize() const =0;
  virtual void serializeElement(int block, int localX, int localY, int localZ, T* buffer) const =0;
  virtual MultiDataDistribution3D const& getMultiData() const =0;
  virtual bool isAllocated(int block) const =0;
};

template<typename T>
struct MultiUnSerializerPolicy3D {
  virtual ~MultiUnSerializerPolicy3D() { }
  virtual int getElementSize() const =0;
  virtual void unSerializeElement(int block, int localX, int localY, int localZ, T const* buffer) =0;
  virtual MultiDataDistribution3D const& getMultiData() const =0;
  virtual bool isAllocated(int block) const =0;
};

template<typename T>
class MultiSerializer3D : public DataSerializer<T> {
public:
  MultiSerializer3D(MultiSerializerPolicy3D<T> const& policy_,
                    IndexOrdering::OrderingT ordering_);
  MultiSerializer3D(MultiSerializerPolicy3D<T> const& policy_,
                    int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
                    IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual const T* getNextDataBuffer(size_t& bufferSize) const;
  virtual bool isEmpty() const;
private:
  void computeBufferAlongX(int nextLattice, int nextChunkSize) const;
  void computeBufferAlongZ(int nextLattice, int nextChunkSize) const;
  void communicateBuffer(int bufferSize, int fromProc, bool isAllocated) const;
  void fillBufferWithZeros(int nextChunkSize) const;
private:
  MultiSerializerPolicy3D<T> const& policy;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1, z0, z1;
  mutable int iX, iY, iZ;
  mutable std::vector<T> buffer;
};

template<typename T>
class MultiUnSerializer3D : public DataUnSerializer<T> {
public:
  MultiUnSerializer3D(MultiUnSerializerPolicy3D<T>& policy_,
                      IndexOrdering::OrderingT ordering_);
  MultiUnSerializer3D(MultiUnSerializerPolicy3D<T>& policy_,
                      int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
                      IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual T* getNextDataBuffer(size_t& bufferSize);
  virtual void commitData();
  virtual bool isFull() const;
private:
  void fillBufferAlongX(int nextLattice, int nextChunkSize);
  void fillBufferAlongZ(int nextLattice, int nextChunkSize);
  void communicateBuffer(int bufferSize, int toBlock, bool isAllocated) const;
private:
  MultiUnSerializerPolicy3D<T>& policy;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1, z0, z1;
  mutable int iX, iY, iZ;
  mutable std::vector<T> buffer;
};

}

#endif // defined MULTI_SERIALIZER_3D_H
