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
 * Serializer for 2D multi data -- header file.
 */

#ifndef MULTI_SERIALIZER_2D_H
#define MULTI_SERIALIZER_2D_H

#include "core/serializer.h"
#include "multiDataGeometry2D.h"

namespace olb {

template<typename T>
struct MultiSerializerPolicy2D {
  virtual ~MultiSerializerPolicy2D() { }
  virtual int getElementSize() const =0;
  virtual void serializeElement(int block, int localX, int localY, T* buffer) const =0;
  virtual MultiDataDistribution2D const& getMultiData() const =0;
  virtual bool isAllocated(int block) const =0;
};

template<typename T>
struct MultiUnSerializerPolicy2D {
  virtual ~MultiUnSerializerPolicy2D() { }
  virtual int getElementSize() const =0;
  virtual void unSerializeElement(int block, int localX, int localY, T const* buffer) =0;
  virtual MultiDataDistribution2D const& getMultiData() const =0;
  virtual bool isAllocated(int block) const =0;
};

template<typename T>
class MultiSerializer2D : public DataSerializer<T> {
public:
  MultiSerializer2D(MultiSerializerPolicy2D<T> const& policy_,
                    IndexOrdering::OrderingT ordering_);
  MultiSerializer2D(MultiSerializerPolicy2D<T> const& policy_,
                    int x0_, int x1_, int y0_, int y1_,
                    IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual const T* getNextDataBuffer(size_t& bufferSize) const;
  virtual bool isEmpty() const;
private:
  void computeBufferAlongX(int nextLattice, int nextChunkSize) const;
  void computeBufferAlongY(int nextLattice, int nextChunkSize) const;
  void communicateBuffer(int bufferSize, int fromProc, bool isAllocated) const;
  void fillBufferWithZeros(int nextChunkSize) const;
private:
  MultiSerializerPolicy2D<T> const& policy;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1;
  mutable int iX, iY;
  mutable std::vector<T> buffer;
};

template<typename T>
class MultiUnSerializer2D : public DataUnSerializer<T> {
public:
  MultiUnSerializer2D(MultiUnSerializerPolicy2D<T>& policy_,
                      IndexOrdering::OrderingT ordering_);
  MultiUnSerializer2D(MultiUnSerializerPolicy2D<T>& policy_,
                      int x0_, int x1_, int y0_, int y1_,
                      IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual T* getNextDataBuffer(size_t& bufferSize);
  virtual void commitData();
  virtual bool isFull() const;
private:
  void fillBufferAlongX(int nextLattice, int nextChunkSize);
  void fillBufferAlongY(int nextLattice, int nextChunkSize);
  void communicateBuffer(int bufferSize, int toBlock, bool isAllocated) const;
private:
  MultiUnSerializerPolicy2D<T>& policy;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1;
  mutable int iX, iY;
  mutable std::vector<T> buffer;
};

}

#endif // defined MULTI_SERIALIZER_2D_H
