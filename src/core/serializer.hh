/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Jonas Latt
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


#ifndef SERIALIZER_HH
#define SERIALIZER_HH

#include "complexGrids/mpiManager/mpiManager.h"
#include "serializer.h"
#include "olbDebug.h"
#include <algorithm>

namespace olb {

////////// class ScalingSerializer ////////////////////////////

template<typename T>
ScalingSerializer<T>::ScalingSerializer(DataSerializer<T> const& baseSerializer_, T scalingFactor_)
  : baseSerializer(baseSerializer_),
    scalingFactor(scalingFactor_)
{ }

template<typename T>
size_t ScalingSerializer<T>::getSize() const {
  return baseSerializer.getSize();
}

template<typename T>
const T* ScalingSerializer<T>::getNextDataBuffer(size_t& bufferSize) const {
  const T* unscaledBuffer = baseSerializer.getNextDataBuffer(bufferSize);
  scaledBuffer.resize(bufferSize);
  for (size_t iBuffer=0; iBuffer<bufferSize; ++iBuffer) {
    scaledBuffer[iBuffer] = unscaledBuffer[iBuffer] * scalingFactor;
  }
  return &scaledBuffer[0];
}

template<typename T>
bool ScalingSerializer<T>::isEmpty() const {
  return baseSerializer.isEmpty();
}

////////// class TypeConversionSerializer ////////////////////////////

template<typename T, typename TConv>
TypeConversionSerializer<T,TConv>::TypeConversionSerializer (
  DataSerializer<T> const& baseSerializer_)
  : baseSerializer(baseSerializer_)
{ }

template<typename T, typename TConv>
size_t TypeConversionSerializer<T,TConv>::getSize() const {
  return baseSerializer.getSize();
}

template<typename T, typename TConv>
const TConv* TypeConversionSerializer<T,TConv>::getNextDataBuffer(size_t& bufferSize) const {
  const T* originalBuffer = baseSerializer.getNextDataBuffer(bufferSize);
  convBuffer.resize(bufferSize);
  for (size_t iBuffer=0; iBuffer<bufferSize; ++iBuffer) {
    convBuffer[iBuffer] = static_cast<TConv>( originalBuffer[iBuffer] );
  }
  return &convBuffer[0];
}

template<typename T, typename TConv>
bool TypeConversionSerializer<T,TConv>::isEmpty() const {
  return baseSerializer.isEmpty();
}

/// Specialization of TypeConversionSerializer in case T==TConv, for efficiency reasons
template<typename T>
class TypeConversionSerializer<T,T> : public DataSerializer<T> {
public:
  TypeConversionSerializer(DataSerializer<T> const& baseSerializer_);
  virtual size_t getSize() const;
  virtual const T* getNextDataBuffer(size_t& bufferSize) const;
  virtual bool isEmpty() const;
private:
  DataSerializer<T> const& baseSerializer;
};

template<typename T>
TypeConversionSerializer<T,T>::TypeConversionSerializer (
  DataSerializer<T> const& baseSerializer_)
  : baseSerializer(baseSerializer_)
{ }

template<typename T>
size_t TypeConversionSerializer<T,T>::getSize() const {
  return baseSerializer.getSize();
}

template<typename T>
const T* TypeConversionSerializer<T,T>::getNextDataBuffer(size_t& bufferSize) const {
  return baseSerializer.getNextDataBuffer(bufferSize);
}

template<typename T>
bool TypeConversionSerializer<T,T>::isEmpty() const {
  return baseSerializer.isEmpty();
}


////////// Free functions ////////////////////////////

template<typename T>
void copySerializedData(DataSerializer<T> const& serializer, DataUnSerializer<T>& unSerializer) {
  OLB_PRECONDITION( serializer.getSize() == unSerializer.getSize() );
  size_t writePos = 0, readPos = 0;
  size_t serializerBufferSize =0, unSerializerBufferSize =0;
  const T* serializerBuffer =0;
  T* unSerializerBuffer =0;
  while (!unSerializer.isFull()) {
    if (readPos==serializerBufferSize) {
      serializerBuffer = serializer.getNextDataBuffer(serializerBufferSize);
      readPos = 0;
    }
    if (writePos==unSerializerBufferSize) {
      unSerializerBuffer = unSerializer.getNextDataBuffer(unSerializerBufferSize);
      writePos = 0;
    }

    size_t remainToRead = (std::ptrdiff_t)serializerBufferSize - (std::ptrdiff_t)readPos;
    size_t remainToWrite = (std::ptrdiff_t)unSerializerBufferSize - (std::ptrdiff_t)writePos;
    size_t nextChunk = std::min(remainToRead, remainToWrite);
    for (size_t iChunk=0; iChunk<nextChunk; ++iChunk, ++readPos, ++writePos) {
      if (singleton::mpi().isMainProcessor()) {
        unSerializerBuffer[writePos] = serializerBuffer[readPos];
      }
    }
    if (writePos==unSerializerBufferSize) {
      unSerializer.commitData();
    }
  }
}

template<typename T>
void copyDataBlock(Serializable<T> const& from, Serializable<T>& to, IndexOrdering::OrderingT ordering) {
  copySerializedData(from.getSerializer(ordering), to.getUnSerializer(ordering));
}

}  // namespace olb

#endif


