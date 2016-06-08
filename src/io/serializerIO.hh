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

#ifndef SERIALIZER_IO_HH
#define SERIALIZER_IO_HH

#include "complexGrids/mpiManager/mpiManager.h"
#include "serializerIO.h"
#include "base64.h"
#include "core/olbDebug.h"
#include <limits>
#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>

namespace olb {

template<typename T>
void serializer2ostr(DataSerializer<T> const& serializer, std::ostream* ostr, bool enforceUint) {
  size_t fullSize = 0;
  if (singleton::mpi().isMainProcessor()) {
    fullSize = serializer.getSize();
    size_t binarySize = (size_t) (fullSize * sizeof(T));
    if (enforceUint) {
      Base64Encoder<unsigned int> sizeEncoder(*ostr, 1);
      OLB_PRECONDITION(binarySize <= std::numeric_limits<unsigned int>::max());
      unsigned int uintBinarySize = (unsigned int)binarySize;
      sizeEncoder.encode(&uintBinarySize, 1);
    }
    else {
      Base64Encoder<size_t> sizeEncoder(*ostr, 1);
      sizeEncoder.encode(&binarySize, 1);
    }
  }
  Base64Encoder<T>* dataEncoder = 0;
  if (singleton::mpi().isMainProcessor()) {
    dataEncoder = new Base64Encoder<T>(*ostr, fullSize);
  }
  while (!serializer.isEmpty()) {
    size_t bufferSize;
    const T* dataBuffer = serializer.getNextDataBuffer(bufferSize);
    if (singleton::mpi().isMainProcessor()) {
      dataEncoder->encode(dataBuffer, bufferSize);
    }
  }
  delete dataEncoder;
}

template<typename T>
void saveData(Serializable<T> const& object, std::string fName, bool enforceUint) {
  std::ofstream* ostr = 0;
  if (singleton::mpi().isMainProcessor()) {
    ostr = new std::ofstream(fName.c_str());
    OLB_PRECONDITION( *ostr );
  }
  serializer2ostr<T>(object.getSerializer(IndexOrdering::memorySaving), ostr, enforceUint);
  delete ostr;
}

template<typename T>
void istr2unSerializer(DataUnSerializer<T>& unSerializer, std::istream* istr, bool enforceUint) {
  size_t fullSize = 0;
  if (singleton::mpi().isMainProcessor()) {
    size_t binarySize;
    if (enforceUint) {
      unsigned int uintBinarySize;
      Base64Decoder<unsigned int> sizeDecoder(*istr, 1);
      sizeDecoder.decode(&uintBinarySize, 1);
      binarySize = uintBinarySize;
    }
    else {
      Base64Decoder<size_t> sizeDecoder(*istr, 1);
      sizeDecoder.decode(&binarySize, 1);
    }
    fullSize = binarySize / sizeof(T);
    OLB_PRECONDITION(fullSize == unSerializer.getSize());
  }
  Base64Decoder<T>* dataDecoder = 0;
  if (singleton::mpi().isMainProcessor()) {
    dataDecoder = new Base64Decoder<T>(*istr, unSerializer.getSize());
  }
  while (!unSerializer.isFull()) {
    size_t bufferSize = 0;
    T* dataBuffer = unSerializer.getNextDataBuffer(bufferSize);
    if (singleton::mpi().isMainProcessor()) {
      dataDecoder->decode(dataBuffer, bufferSize);
    }
    unSerializer.commitData();
  }
  delete dataDecoder;
}

template<typename T>
void loadData(Serializable<T>& object, std::string fName, bool enforceUint) {
  std::ifstream* istr = 0;
  if (singleton::mpi().isMainProcessor()) {
    istr = new std::ifstream(fName.c_str());
    OLB_PRECONDITION( *istr );
  }
  istr2unSerializer<T>(object.getUnSerializer(IndexOrdering::memorySaving), istr, enforceUint);
  delete istr;
}

template<typename T>
void saveAsciiData(Serializable<T> const& object, std::string fName) {
  std::ofstream* ostr = 0;
  if (singleton::mpi().isMainProcessor()) {
    ostr = new std::ofstream(fName.c_str());
    OLB_PRECONDITION( *ostr );
  }
  DataSerializer<T> const& serializer = object.getSerializer(IndexOrdering::memorySaving);
  while (!serializer.isEmpty()) {
    size_t bufferSize;
    const T* dataBuffer = serializer.getNextDataBuffer(bufferSize);
    if (singleton::mpi().isMainProcessor()) {
      for (size_t iData=0; iData<bufferSize; ++iData) {
        *ostr << dataBuffer[iData] << " ";
      }
    }
  }
  delete ostr;
}

} // namespace olb

#endif
