/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006, 2007 Jonas Latt
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
 * Scalar, vector and tensor fields for 2D data analysis -- generic implementation.
 */

#ifndef DATA_FIELDS_2D_HH
#define DATA_FIELDS_2D_HH

#include <algorithm>
#include "dataFields2D.h"

namespace olb {

/////// Class ScalarField2D //////////////////////////////////

template<typename T>
ScalarField2D<T>::ScalarField2D(int nx_, int ny_)
  : nx(nx_), ny(ny_), rawData(0), field(0),
    serializer(0), unSerializer(0)
{ }

template<typename T>
ScalarField2D<T>::~ScalarField2D() {
  delete serializer;
  delete unSerializer;
  deConstruct();
}

template<typename T>
ScalarField2D<T>::ScalarField2D(ScalarField2D<T> const& rhs)
  : serializer(0), unSerializer(0)
{
  nx = rhs.nx;
  ny = rhs.ny;
  rawData = 0;
  field   = 0;
  if (rhs.isConstructed()) {
    construct();
    for (size_t iData=0; iData<getSize(); ++iData) {
      (*this)[iData] = rhs[iData];
    }
  }
}

template<typename T>
ScalarField2D<T>& ScalarField2D<T>::operator=(ScalarField2D<T> const& rhs) {
  ScalarField2D<T> tmp(rhs);
  swap(tmp);
  return *this;
}

template<typename T>
bool ScalarField2D<T>::isConstructed() const {
  return rawData;
}

template<typename T>
void ScalarField2D<T>::construct() {
  if (!isConstructed()) {
    allocateMemory();
  }
}

template<typename T>
void ScalarField2D<T>::deConstruct() {
  if (isConstructed()) {
    releaseMemory();
  }
}

template<typename T>
void ScalarField2D<T>::reset() {
  OLB_PRECONDITION(isConstructed());
  for (int index=0; index<nx*ny; ++index) {
    (*this)[index] = T();
  }
}


template<typename T>
void ScalarField2D<T>::swap(ScalarField2D<T>& rhs) {
  std::swap(nx, rhs.nx);
  std::swap(ny, rhs.ny);
  std::swap(rawData, rhs.rawData);
  std::swap(field, rhs.field);
  std::swap(serializer, rhs.serializer);
  std::swap(unSerializer, rhs.unSerializer);
}

template<typename T>
DataSerializer<T> const& ScalarField2D<T>::getSerializer(IndexOrdering::OrderingT ordering) const
{
  delete serializer;
  serializer = new SequentialScalarFieldSerializer2D<T>(*this, ordering);
  return *serializer;
}

template<typename T>
DataUnSerializer<T>& ScalarField2D<T>::getUnSerializer(IndexOrdering::OrderingT ordering)
{
  delete unSerializer;
  unSerializer = new SequentialScalarFieldUnSerializer2D<T>(*this, ordering);
  return *unSerializer;
}

template<typename T>
DataSerializer<T> const& ScalarField2D<T>::getSubSerializer (
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering ) const
{
  delete serializer;
  serializer = new SequentialScalarFieldSerializer2D<T> (
    *this, x0_, x1_, y0_, y1_, ordering );
  return *serializer;
}

template<typename T>
DataUnSerializer<T>& ScalarField2D<T>::getSubUnSerializer (
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering )
{
  delete unSerializer;
  unSerializer = new SequentialScalarFieldUnSerializer2D<T> (
    *this, x0_, x1_, y0_, y1_, ordering );
  return *unSerializer;
}

template<typename T>
MultiDataDistribution2D ScalarField2D<T>::getDataDistribution() const {
  return MultiDataDistribution2D(getNx(), getNy());
}

template<typename T>
SpatiallyExtendedObject2D* ScalarField2D<T>::getComponent(int iBlock) {
  OLB_PRECONDITION( iBlock==0 );
  return this;
}

template<typename T>
SpatiallyExtendedObject2D const* ScalarField2D<T>::getComponent(int iBlock) const {
  OLB_PRECONDITION( iBlock==0 );
  return this;
}

template<typename T>
multiPhysics::MultiPhysicsId ScalarField2D<T>::getMultiPhysicsId() const {
  return multiPhysics::getMultiPhysicsScalarId<T>();
}

template<typename T>
T ScalarField2D<T>::computeReduction(DataReduction<T>& reduction) const
{
  OLB_PRECONDITION(isConstructed());
  reduction.reset();
  for (size_t iEl=0; iEl<getSize(); iEl++) {
    reduction.takeElement( this->operator[](iEl) );
  }
  return reduction.getResult();
}

template<typename T>
void ScalarField2D<T>::allocateMemory() {
  rawData = new T[(size_t)nx*(size_t)ny];
  field   = new T* [(size_t)nx];
  for (int iX=0; iX<nx; ++iX) {
    field[iX] = rawData + (size_t)iX*(size_t)ny;
  }
}

template<typename T>
void ScalarField2D<T>::releaseMemory() {
  delete [] rawData;
  rawData = 0;
  delete [] field;
}

//////// Class SequentialScalarFieldSerializer2D //////////////////////////////////

template<typename T>
SequentialScalarFieldSerializer2D<T>::SequentialScalarFieldSerializer2D (
  ScalarField2D<T> const& scalarField_, IndexOrdering::OrderingT ordering_ )
  : scalarField(scalarField_), ordering(ordering_),
    x0(0), x1(scalarField.getNx()-1), y0(0), y1(scalarField.getNy()-1),
    iX(x0), iY(y0)
{ }

template<typename T>
SequentialScalarFieldSerializer2D<T>::SequentialScalarFieldSerializer2D (
  ScalarField2D<T> const& scalarField_,
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering_ )
  : scalarField(scalarField_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_),
    iX(x0), iY(y0)
{ }

template<typename T>
size_t SequentialScalarFieldSerializer2D<T>::getSize() const {
  return (size_t)(x1-x0+1) * (size_t)(y1-y0+1);
}

template<typename T>
const T* SequentialScalarFieldSerializer2D<T>::getNextDataBuffer(size_t& bufferSize) const {
  OLB_PRECONDITION( !isEmpty() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    bufferSize = y1-y0+1;
    buffer.resize(bufferSize);
    for (iY=y0; iY<=y1; ++iY) {
      buffer[iY-y0] = scalarField.get(iX, iY);
    }
    ++iX;
  }
  else {
    bufferSize = x1-x0+1;
    buffer.resize(bufferSize);
    for (iX=x0; iX<=x1; ++iX) {
      buffer[iX-x0] = scalarField.get(iX, iY);
    }
    ++iY;
  }
  return &buffer[0];
}

template<typename T>
bool SequentialScalarFieldSerializer2D<T>::isEmpty() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iY > y1;
  }
}

//////// Class SequentialScalarFieldUnSerializer2D //////////////////////////////////

template<typename T>
SequentialScalarFieldUnSerializer2D<T>::SequentialScalarFieldUnSerializer2D (
  ScalarField2D<T>& scalarField_, IndexOrdering::OrderingT ordering_ )
  : scalarField(scalarField_), ordering(ordering_),
    x0(0), x1(scalarField.getNx()-1), y0(0), y1(scalarField.getNy()-1),
    iX(x0), iY(y0)
{ }

template<typename T>
SequentialScalarFieldUnSerializer2D<T>::SequentialScalarFieldUnSerializer2D (
  ScalarField2D<T>& scalarField_,
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering_ )
  : scalarField(scalarField_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_),
    iX(x0), iY(y0)
{ }

template<typename T>
size_t SequentialScalarFieldUnSerializer2D<T>::getSize() const {
  return (size_t)(x1-x0+1) * (size_t)(y1-y0+1);
}

template<typename T>
T* SequentialScalarFieldUnSerializer2D<T>::getNextDataBuffer(size_t& bufferSize) {
  OLB_PRECONDITION( !isFull() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    bufferSize = y1-y0+1;
  }
  else {
    bufferSize = x1-x0+1;
  }
  buffer.resize(bufferSize);
  return &buffer[0];
}

template<typename T>
void SequentialScalarFieldUnSerializer2D<T>::commitData() {
  OLB_PRECONDITION( !isFull() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    for (iY=y0; iY<=y1; ++iY) {
      scalarField.get(iX, iY) = buffer[iY-y0];
    }
    ++iX;
  }
  else {
    for (iX=x0; iX<=x1; ++iX) {
      scalarField.get(iX, iY) = buffer[iX-x0];
    }
    ++iY;
  }
}

template<typename T>
bool SequentialScalarFieldUnSerializer2D<T>::isFull() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iY > y1;
  }
}


//////// Class TensorField2D //////////////////////////////////

template<typename T, int nDim>
TensorField2D<T,nDim>::TensorField2D(int nx_, int ny_)
  : nx(nx_), ny(ny_),
    rawData(0), field(0),
    serializer(0), unSerializer(0)
{
  for (int iDim=0; iDim<nDim; ++iDim) {
    components[iDim] = new ScalarField2D<T>(nx, ny);
  }
}

template<typename T, int nDim>
TensorField2D<T,nDim>::~TensorField2D() {
  delete serializer;
  delete unSerializer;
  deConstruct();
  for (int iDim=0; iDim<nDim; ++iDim) {
    delete components[iDim];
  }
}

template<typename T, int nDim>
TensorField2D<T,nDim>::TensorField2D(TensorField2D<T,nDim> const& rhs)
  : serializer(0), unSerializer(0)
{
  nx = rhs.nx;
  ny = rhs.ny;
  rawData = 0;
  field   = 0;
  for (int iDim=0; iDim<nDim; ++iDim) {
    components[iDim] = new ScalarField2D<T>(nx, ny);
  }
  if (rhs.isConstructed()) {
    construct();
    for (int iData=0; iData<nx*ny; ++iData) {
      for (int iDim=0; iDim<nDim; ++iDim) {
        (*this)[iData][iDim] = rhs[iData][iDim];
      }
    }
  }
}

template<typename T, int nDim>
TensorField2D<T,nDim>& TensorField2D<T,nDim>::operator=(TensorField2D<T,nDim> const& rhs) {
  TensorField2D<T,nDim> tmp(rhs);
  swap(tmp);
  return *this;
}

template<typename T, int nDim>
bool TensorField2D<T,nDim>::isConstructed() const {
  return rawData;
}

template<typename T, int nDim>
void TensorField2D<T,nDim>::construct() {
  if (!isConstructed()) {
    allocateMemory();
  }
}

template<typename T, int nDim>
void TensorField2D<T,nDim>::deConstruct() {
  if (isConstructed()) {
    releaseMemory();
  }
}

template<typename T, int nDim>
void TensorField2D<T,nDim>::reset() {
  OLB_PRECONDITION(isConstructed());
  for (int index=0; index<nx*ny; ++index) {
    for (int iDim=0; iDim<nDim; ++iDim) {
      (*this)[index][iDim] = T();
    }
  }
}

template<typename T, int nDim>
void TensorField2D<T,nDim>::swap(TensorField2D<T,nDim>& rhs) {
  std::swap(nx, rhs.nx);
  std::swap(ny, rhs.ny);
  std::swap(rawData, rhs.rawData);
  std::swap(field, rhs.field);
  std::swap(serializer, rhs.serializer);
  std::swap(unSerializer, rhs.unSerializer);
  for (int iDim=0; iDim<nDim; ++iDim) {
    std::swap(components[iDim], rhs.components[iDim]);
  }
}

template<typename T, int nDim>
DataSerializer<T> const& TensorField2D<T,nDim>::getSerializer(IndexOrdering::OrderingT ordering) const
{
  delete serializer;
  serializer = new SequentialTensorFieldSerializer2D<T,nDim>(*this,ordering);
  return *serializer;
}

template<typename T, int nDim>
DataUnSerializer<T>& TensorField2D<T,nDim>::getUnSerializer(IndexOrdering::OrderingT ordering)
{
  delete unSerializer;
  unSerializer = new SequentialTensorFieldUnSerializer2D<T,nDim>(*this,ordering);
  return *unSerializer;
}

template<typename T, int nDim>
DataSerializer<T> const& TensorField2D<T,nDim>::getSubSerializer (
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering ) const
{
  delete serializer;
  serializer = new SequentialTensorFieldSerializer2D<T, nDim> (
    *this, x0_, x1_, y0_, y1_, ordering );
  return *serializer;
}

template<typename T, int nDim>
DataUnSerializer<T>& TensorField2D<T,nDim>::getSubUnSerializer (
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering )
{
  delete unSerializer;
  unSerializer = new SequentialTensorFieldUnSerializer2D<T, nDim> (
    *this, x0_, x1_, y0_, y1_, ordering );
  return *unSerializer;
}

template<typename T, int nDim>
MultiDataDistribution2D TensorField2D<T,nDim>::getDataDistribution() const {
  return MultiDataDistribution2D(getNx(), getNy());
}

template<typename T, int nDim>
SpatiallyExtendedObject2D* TensorField2D<T,nDim>::getComponent(int iBlock) {
  OLB_PRECONDITION( iBlock==0 );
  return this;
}

template<typename T, int nDim>
SpatiallyExtendedObject2D const* TensorField2D<T,nDim>::getComponent(int iBlock) const {
  OLB_PRECONDITION( iBlock==0 );
  return this;
}

template<typename T, int nDim>
multiPhysics::MultiPhysicsId TensorField2D<T,nDim>::getMultiPhysicsId() const {
  return multiPhysics::getMultiPhysicsTensorId<T,nDim>();
}

template<typename T, int nDim>
void TensorField2D<T,nDim>::allocateMemory() {
  rawData = new Tensor[(size_t)nx*(size_t)ny];
  field   = new Tensor* [(size_t)nx];
  for (int iX=0; iX<nx; ++iX) {
    field[iX] = rawData + (size_t)iX*(size_t)ny;
  }
}

template<typename T, int nDim>
void TensorField2D<T,nDim>::releaseMemory() {
  delete [] rawData;
  rawData = 0;
  delete [] field;
}

template<typename T, int nDim>
ScalarField2D<T> const& TensorField2D<T,nDim>::extractComponent(int whichDim)
const
{
  components[whichDim]->construct();
  for (int iEl=0; iEl<nx*ny; ++iEl) {
    (*components[whichDim])[iEl] = (*this)[iEl][whichDim];
  };
  return *components[whichDim];
}

////////// class SequentialTensorFieldSerializer2D ////////////////////////////

template<typename T, int nDim>
SequentialTensorFieldSerializer2D<T,nDim>::SequentialTensorFieldSerializer2D (
  TensorField2D<T,nDim> const& tensorField_, IndexOrdering::OrderingT ordering_ )
  : tensorField(tensorField_), ordering(ordering_),
    x0(0), x1(tensorField.getNx()-1), y0(0), y1(tensorField.getNy()-1),
    iX(x0), iY(y0)
{ }

template<typename T, int nDim>
SequentialTensorFieldSerializer2D<T,nDim>::SequentialTensorFieldSerializer2D (
  TensorField2D<T,nDim> const& tensorField_,
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering_ )
  : tensorField(tensorField_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_),
    iX(x0), iY(y0)
{ }

template<typename T, int nDim>
size_t SequentialTensorFieldSerializer2D<T, nDim>::getSize() const {
  return (size_t)(x1-x0+1) * (size_t)(y1-y0+1) * nDim;
}

template<typename T, int nDim>
const T* SequentialTensorFieldSerializer2D<T, nDim>::getNextDataBuffer(size_t& bufferSize) const {
  OLB_PRECONDITION( !isEmpty() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    bufferSize = (size_t)(y1-y0+1)*(size_t)nDim;
    buffer.resize(bufferSize);
    for (iY=y0; iY<=y1; ++iY) {
      for (int iDim=0; iDim<nDim; ++iDim) {
        buffer[nDim*(iY-y0)+iDim] = tensorField.get(iX, iY)[iDim];
      }
    }
    ++iX;
  }
  else {
    bufferSize = (size_t)(x1-x0+1)*(size_t)nDim;
    buffer.resize(bufferSize);
    for (iX=x0; iX<=x1; ++iX) {
      for (int iDim=0; iDim<nDim; ++iDim) {
        buffer[nDim*(iX-x0)+iDim] = tensorField.get(iX, iY)[iDim];
      }
    }
    ++iY;
  }
  return &buffer[0];
}

template<typename T, int nDim>
bool SequentialTensorFieldSerializer2D<T, nDim>::isEmpty() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iY > y1;
  }
}


////////// class SequentialTensorFieldUnSerializer2D ////////////////////////////

template<typename T, int nDim>
SequentialTensorFieldUnSerializer2D<T,nDim>::SequentialTensorFieldUnSerializer2D (
  TensorField2D<T,nDim>& tensorField_, IndexOrdering::OrderingT ordering_ )
  : tensorField(tensorField_), ordering(ordering_),
    x0(0), x1(tensorField.getNx()-1), y0(0), y1(tensorField.getNy()-1),
    iX(x0), iY(y0)
{ }

template<typename T, int nDim>
SequentialTensorFieldUnSerializer2D<T,nDim>::SequentialTensorFieldUnSerializer2D (
  TensorField2D<T,nDim>& tensorField_,
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering_ )
  : tensorField(tensorField_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_),
    iX(x0), iY(y0)
{ }

template<typename T, int nDim>
size_t SequentialTensorFieldUnSerializer2D<T, nDim>::getSize() const {
  return (size_t)(x1-x0+1) * (size_t)(y1-y0+1) * (size_t)nDim;
}

template<typename T, int nDim>
T* SequentialTensorFieldUnSerializer2D<T, nDim>::getNextDataBuffer(size_t& bufferSize) {
  OLB_PRECONDITION( !isFull() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    bufferSize = (size_t)(y1-y0+1)*(size_t)nDim;
  }
  else {
    bufferSize = (size_t)(x1-x0+1)*(size_t)nDim;
  }
  buffer.resize(bufferSize);
  return &buffer[0];
}

template<typename T, int nDim>
void SequentialTensorFieldUnSerializer2D<T, nDim>::commitData() {
  OLB_PRECONDITION( !isFull() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    for (iY=y0; iY<=y1; ++iY) {
      for (int iDim=0; iDim<nDim; ++iDim) {
        tensorField.get(iX, iY)[iDim] = buffer[nDim*(iY-y0)+iDim];
      }
    }
    ++iX;
  }
  else {
    for (iX=x0; iX<=x1; ++iX) {
      for (int iDim=0; iDim<nDim; ++iDim) {
        tensorField.get(iX, iY)[iDim] = buffer[nDim*(iX-x0)+iDim];
      }
    }
    ++iY;
  }
}

template<typename T, int nDim>
bool SequentialTensorFieldUnSerializer2D<T, nDim>::isFull() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iY > y1;
  }
}

}  // namespace olb

#endif
