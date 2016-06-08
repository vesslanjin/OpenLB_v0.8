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
 * Scalar, vector and tensor fields for 3D data analysis -- generic implementation.
 */
#ifndef DATA_FIELDS_3D_HH
#define DATA_FIELDS_3D_HH

#include <algorithm>
#include "dataFields3D.h"

namespace olb {

/////// Class ScalarField3D //////////////////////////////////

template<typename T>
ScalarField3D<T>::ScalarField3D(int nx_, int ny_, int nz_)
  : nx(nx_), ny(ny_), nz(nz_), rawData(0), field(0),
    xSlice(ny,nz), ySlice(nx,nz), zSlice(nx,ny),
    serializer(0), unSerializer(0)
{ }

template<typename T>
ScalarField3D<T>::~ScalarField3D() {
  delete serializer;
  delete unSerializer;
  deConstruct();
}

template<typename T>
ScalarField3D<T>::ScalarField3D(ScalarField3D<T> const& rhs)
  : nx(rhs.nx), ny(rhs.ny), nz(rhs.nz), rawData(0), field(0),
    xSlice(ny,nz), ySlice(nx,nz), zSlice(nx,ny),
    serializer(0), unSerializer(0)
{
  if (rhs.isConstructed()) {
    construct();
    for (size_t iData=0; iData<getSize(); ++iData) {
      (*this)[iData] = rhs[iData];
    }
  }
}

template<typename T>
ScalarField3D<T>& ScalarField3D<T>::operator=(ScalarField3D<T> const& rhs) {
  ScalarField3D<T> tmp(rhs);
  swap(tmp);
  return *this;
}

template<typename T>
bool ScalarField3D<T>::isConstructed() const {
  return rawData;
}

template<typename T>
void ScalarField3D<T>::construct() {
  if (!isConstructed()) {
    allocateMemory();
  }
}

template<typename T>
void ScalarField3D<T>::deConstruct() {
  if (isConstructed()) {
    releaseMemory();
  }
}

template<typename T>
void ScalarField3D<T>::reset() {
  OLB_PRECONDITION(isConstructed());
  for (int index=0; index<nx*ny*nz; ++index) {
    (*this)[index] = T();
  }
}

template<typename T>
ScalarField2D<T> const& ScalarField3D<T>::sliceX(int xVal) const {
  xSlice.construct();
  for (int iY=0; iY<ny; ++iY) {
    for (int iZ=0; iZ<nz; ++iZ) {
      xSlice.get(iY,iZ) = this->get(xVal,iY,iZ);
    }
  }
  return xSlice;
}

template<typename T>
ScalarField2D<T> const& ScalarField3D<T>::sliceY(int yVal) const {
  ySlice.construct();
  for (int iX=0; iX<nx; ++iX) {
    for (int iZ=0; iZ<nz; ++iZ) {
      ySlice.get(iX,iZ) = this->get(iX,yVal,iZ);
    }
  }
  return ySlice;
}

template<typename T>
ScalarField2D<T> const& ScalarField3D<T>::sliceZ(int zVal) const {
  zSlice.construct();
  for (int iX=0; iX<nx; ++iX) {
    for (int iY=0; iY<ny; ++iY) {
      zSlice.get(iX,iY) = this->get(iX,iY,zVal);
    }
  }
  return zSlice;
}

template<typename T>
void ScalarField3D<T>::swap(ScalarField3D<T>& rhs) {
  std::swap(nx, rhs.nx);
  std::swap(ny, rhs.ny);
  std::swap(nz, rhs.nz);
  std::swap(rawData, rhs.rawData);
  std::swap(field, rhs.field);
}

template<typename T>
DataSerializer<T> const& ScalarField3D<T>::getSerializer(IndexOrdering::OrderingT ordering) const
{
  delete serializer;
  serializer = new SequentialScalarFieldSerializer3D<T>(*this, ordering);
  return *serializer;
}

template<typename T>
DataUnSerializer<T>& ScalarField3D<T>::getUnSerializer(IndexOrdering::OrderingT ordering)
{
  delete unSerializer;
  unSerializer = new SequentialScalarFieldUnSerializer3D<T>(*this, ordering);
  return *unSerializer;
}

template<typename T>
DataSerializer<T> const& ScalarField3D<T>::getSubSerializer (
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering ) const
{
  delete serializer;
  serializer = new SequentialScalarFieldSerializer3D<T> (
    *this, x0_, x1_, y0_, y1_, z0_, z1_, ordering );
  return *serializer;
}

template<typename T>
DataUnSerializer<T>& ScalarField3D<T>::getSubUnSerializer (
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering )
{
  delete unSerializer;
  unSerializer = new SequentialScalarFieldUnSerializer3D<T> (
    *this, x0_, x1_, y0_, y1_, z0_, z1_, ordering );
  return *unSerializer;
}


template<typename T>
T ScalarField3D<T>::computeReduction(DataReduction<T>& reduction) const
{
  OLB_PRECONDITION(isConstructed());
  reduction.reset();
  for (size_t iEl=0; iEl<getSize(); iEl++) {
    reduction.takeElement( this->operator[](iEl) );
  }
  return reduction.getResult();
}

template<typename T>
MultiDataDistribution3D ScalarField3D<T>::getDataDistribution() const {
  return MultiDataDistribution3D(getNx(), getNy(), getNz());
}

template<typename T>
SpatiallyExtendedObject3D* ScalarField3D<T>::getComponent(int iBlock) {
  OLB_PRECONDITION( iBlock==0 );
  return this;
}

template<typename T>
SpatiallyExtendedObject3D const* ScalarField3D<T>::getComponent(int iBlock) const {
  OLB_PRECONDITION( iBlock==0 );
  return this;
}

template<typename T>
multiPhysics::MultiPhysicsId ScalarField3D<T>::getMultiPhysicsId() const {
  return multiPhysics::getMultiPhysicsScalarId<T>();
}


template<typename T>
void ScalarField3D<T>::allocateMemory() {
  rawData = new T [(size_t)nx*(size_t)ny*(size_t)nz];
  field   = new T** [(size_t)nx];
  for (int iX=0; iX<nx; ++iX) {
    field[iX] = new T* [(size_t)ny];
    for (int iY=0; iY<ny; ++iY) {
      field[iX][iY] = rawData + (size_t)nz*((size_t)iY+(size_t)ny*(size_t)iX);
    }
  }
}

template<typename T>
void ScalarField3D<T>::releaseMemory() {
  delete [] rawData;
  rawData = 0;
  for (int iX=0; iX<nx; ++iX) {
    delete [] field[iX];
  }
  delete [] field;
}


////////// class SequentialScalarFieldSerializer3D ////////////////////////////

template<typename T>
SequentialScalarFieldSerializer3D<T>::SequentialScalarFieldSerializer3D (
  ScalarField3D<T> const& scalarField_, IndexOrdering::OrderingT ordering_ )
  : scalarField(scalarField_), ordering(ordering_),
    x0(0), x1(scalarField.getNx()-1), y0(0), y1(scalarField.getNy()-1),
    z0(0), z1(scalarField.getNz()-1),
    iX(x0), iY(y0), iZ(z0)
{ }

template<typename T>
SequentialScalarFieldSerializer3D<T>::SequentialScalarFieldSerializer3D (
  ScalarField3D<T> const& scalarField_,
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering_ )
  : scalarField(scalarField_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_), z0(z0_), z1(z1_),
    iX(x0), iY(y0), iZ(z0)
{ }

template<typename T>
size_t SequentialScalarFieldSerializer3D<T>::getSize() const {
  return (size_t)(x1-x0+1) * (size_t)(y1-y0+1) * (size_t)(z1-z0+1);
}

template<typename T>
const T* SequentialScalarFieldSerializer3D<T>::getNextDataBuffer(size_t& bufferSize) const {
  OLB_PRECONDITION( !isEmpty() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    bufferSize = (z1-z0+1);
    buffer.resize(bufferSize);
    for (iZ=z0; iZ<=z1; ++iZ) {
      buffer[iZ-z0] = scalarField.get(iX, iY, iZ);
    }
    ++iY;
    if (iY > y1) {
      iY = y0;
      ++iX;
    }
  }
  else {
    bufferSize = scalarField.getNx();
    buffer.resize(bufferSize);
    for (iX=x0; iX<=x1; ++iX) {
      buffer[iX-x0] = scalarField.get(iX, iY, iZ);
    }
    ++iY;
    if (iY > y1) {
      iY = y0;
      ++iZ;
    }
  }
  return &buffer[0];
}

template<typename T>
bool SequentialScalarFieldSerializer3D<T>::isEmpty() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iZ > z1;
  }
}

////////// class SequentialScalarFieldUnSerializer3D ////////////////////////////

template<typename T>
SequentialScalarFieldUnSerializer3D<T>::SequentialScalarFieldUnSerializer3D (
  ScalarField3D<T>& scalarField_, IndexOrdering::OrderingT ordering_ )
  : scalarField(scalarField_), ordering(ordering_),
    x0(0), x1(scalarField.getNx()-1), y0(0), y1(scalarField.getNy()-1),
    z0(0), z1(scalarField.getNz()-1),
    iX(x0), iY(y0), iZ(z0)
{ }

template<typename T>
SequentialScalarFieldUnSerializer3D<T>::SequentialScalarFieldUnSerializer3D (
  ScalarField3D<T>& scalarField_,
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering_ )
  : scalarField(scalarField_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_), z0(z0_), z1(z1_),
    iX(x0), iY(y0), iZ(z0)
{ }

template<typename T>
size_t SequentialScalarFieldUnSerializer3D<T>::getSize() const {
  return (size_t)(x1-x0+1) * (size_t)(y1-y0+1) * (size_t)(z1-z0+1);
}

template<typename T>
T* SequentialScalarFieldUnSerializer3D<T>::getNextDataBuffer(size_t& bufferSize) {
  OLB_PRECONDITION( !isFull() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    bufferSize = (z1-z0+1);
  }
  else {
    bufferSize = (x1-x0+1);
  }
  buffer.resize(bufferSize);
  return &buffer[0];
}

template<typename T>
void SequentialScalarFieldUnSerializer3D<T>::commitData() {
  OLB_PRECONDITION( !isFull() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    for (iZ=z0; iZ<=z1; ++iZ) {
      scalarField.get(iX, iY, iZ) = buffer[iZ-z0];
    }
    ++iY;
    if (iY > y1) {
      iY = y0;
      ++iX;
    }
  }
  else {
    for (iX=x0; iX<=x1; ++iX) {
      scalarField.get(iX, iY, iZ) = buffer[iX-x0];
    }
    ++iY;
    if (iY > y1) {
      iY = y0;
      ++iZ;
    }
  }
}

template<typename T>
bool SequentialScalarFieldUnSerializer3D<T>::isFull() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iZ > z1;
  }
}


//////// Class TensorField3D //////////////////////////////////

template<typename T, int nDim>
TensorField3D<T,nDim>::TensorField3D(int nx_, int ny_, int nz_)
  : nx(nx_), ny(ny_), nz(nz_), rawData(0), field(0),
    xSlice(ny,nz), ySlice(nx,nz), zSlice(nx,ny),
    serializer(0), unSerializer(0)
{
  for (int iDim=0; iDim<nDim; ++iDim) {
    components[iDim] = new ScalarField3D<T>(nx, ny, nz);
  }
}

template<typename T, int nDim>
TensorField3D<T,nDim>::~TensorField3D() {
  delete serializer;
  delete unSerializer;
  deConstruct();
  for (int iDim=0; iDim<nDim; ++iDim) {
    delete components[iDim];
  }
}

template<typename T, int nDim>
TensorField3D<T,nDim>::TensorField3D(TensorField3D<T,nDim> const& rhs)
  : nx(rhs.nx), ny(rhs.ny), nz(rhs.nz), rawData(0), field(0),
    xSlice(ny,nz), ySlice(nx,nz), zSlice(nx,ny),
    serializer(0), unSerializer(0)
{
  for (int iDim=0; iDim<nDim; ++iDim) {
    components[iDim] = new ScalarField3D<T>(nx, ny, nz);
  }
  if (rhs.isConstructed()) {
    construct();
    for (int iData=0; iData<nx*ny*nz; ++iData) {
      for (int iDim=0; iDim<nDim; ++iDim) {
        (*this)[iData][iDim] = rhs[iData][iDim];
      }
    }
  }
}

template<typename T, int nDim>
TensorField3D<T,nDim>& TensorField3D<T,nDim>::operator=(TensorField3D<T,nDim> const& rhs) {
  TensorField3D<T,nDim> tmp(rhs);
  swap(tmp);
  return *this;
}


template<typename T, int nDim>
bool TensorField3D<T,nDim>::isConstructed() const {
  return rawData;
}

template<typename T, int nDim>
void TensorField3D<T,nDim>::construct() {
  if (!isConstructed()) {
    allocateMemory();
  }
}

template<typename T, int nDim>
void TensorField3D<T,nDim>::deConstruct() {
  if (isConstructed()) {
    releaseMemory();
  }
}

template<typename T, int nDim>
void TensorField3D<T,nDim>::reset() {
  OLB_PRECONDITION(isConstructed());
  for (int index=0; index<nx*ny; ++index) {
    for (int iDim=0; iDim<nDim; ++iDim) {
      (*this)[index][iDim] = T();
    }
  }
}

template<typename T, int nDim>
TensorField2D<T,nDim> const& TensorField3D<T,nDim>::sliceX(int xVal) const {
  xSlice.construct();
  for (int iY=0; iY<ny; ++iY) {
    for (int iZ=0; iZ<nz; ++iZ) {
      for (int iDim=0; iDim<nDim; ++iDim) {
        xSlice.get(iY,iZ)[iDim] = this->get(xVal,iY,iZ)[iDim];
      }
    }
  }
  return xSlice;
}

template<typename T, int nDim>
TensorField2D<T,nDim> const& TensorField3D<T,nDim>::sliceY(int yVal) const {
  ySlice.construct();
  for (int iX=0; iX<nx; ++iX) {
    for (int iZ=0; iZ<nz; ++iZ) {
      for (int iDim=0; iDim<nDim; ++iDim) {
        ySlice.get(iX,iZ)[iDim] = this->get(iX,yVal,iZ)[iDim];
      }
    }
  }
  return ySlice;
}

template<typename T, int nDim>
TensorField2D<T,nDim> const& TensorField3D<T,nDim>::sliceZ(int zVal) const {
  zSlice.construct();
  for (int iX=0; iX<nx; ++iX) {
    for (int iY=0; iY<ny; ++iY) {
      for (int iDim=0; iDim<nDim; ++iDim) {
        zSlice.get(iX,iY)[iDim] = this->get(iX,iY,zVal)[iDim];
      }
    }
  }
  return zSlice;
}

template<typename T, int nDim>
void TensorField3D<T,nDim>::swap(TensorField3D<T,nDim>& rhs) {
  std::swap(nx, rhs.nx);
  std::swap(ny, rhs.ny);
  std::swap(nz, rhs.nz);
  std::swap(rawData, rhs.rawData);
  std::swap(field, rhs.field);
  std::swap(serializer, rhs.serializer);
  std::swap(unSerializer, rhs.unSerializer);
  for (int iDim=0; iDim<nDim; ++iDim) {
    std::swap(components[iDim], rhs.components[iDim]);
  }
}

template<typename T, int nDim>
DataSerializer<T> const& TensorField3D<T,nDim>::getSerializer(IndexOrdering::OrderingT ordering) const
{
  delete serializer;
  serializer = new SequentialTensorFieldSerializer3D<T,nDim>(*this,ordering);
  return *serializer;
}

template<typename T, int nDim>
DataUnSerializer<T>& TensorField3D<T,nDim>::getUnSerializer(IndexOrdering::OrderingT ordering)
{
  delete unSerializer;
  unSerializer = new SequentialTensorFieldUnSerializer3D<T,nDim>(*this,ordering);
  return *unSerializer;
}

template<typename T, int nDim>
DataSerializer<T> const& TensorField3D<T,nDim>::getSubSerializer (
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering ) const
{
  delete serializer;
  serializer = new SequentialTensorFieldSerializer3D<T, nDim> (
    *this, x0_, x1_, y0_, y1_, z0_, z1_, ordering );
  return *serializer;
}

template<typename T, int nDim>
DataUnSerializer<T>& TensorField3D<T,nDim>::getSubUnSerializer (
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering )
{
  delete unSerializer;
  unSerializer = new SequentialTensorFieldUnSerializer3D<T, nDim> (
    *this, x0_, x1_, y0_, y1_, z0_, z1_, ordering );
  return *unSerializer;
}

template<typename T, int nDim>
MultiDataDistribution3D TensorField3D<T,nDim>::getDataDistribution() const {
  return MultiDataDistribution3D(getNx(), getNy(), getNz());
}

template<typename T, int nDim>
SpatiallyExtendedObject3D* TensorField3D<T,nDim>::getComponent(int iBlock) {
  OLB_PRECONDITION( iBlock==0 );
  return this;
}

template<typename T, int nDim>
SpatiallyExtendedObject3D const* TensorField3D<T,nDim>::getComponent(int iBlock) const {
  OLB_PRECONDITION( iBlock==0 );
  return this;
}

template<typename T, int nDim>
multiPhysics::MultiPhysicsId TensorField3D<T,nDim>::getMultiPhysicsId() const {
  return multiPhysics::getMultiPhysicsTensorId<T,nDim>();
}

template<typename T, int nDim>
void TensorField3D<T,nDim>::allocateMemory() {
  rawData = new Tensor   [(size_t)nx*(size_t)ny*(size_t)nz];
  field   = new Tensor** [(size_t)nx];
  for (int iX=0; iX<nx; ++iX) {
    field[iX] = new Tensor* [(size_t)ny];
    for (int iY=0; iY<ny; ++iY) {
      field[iX][iY] = rawData + (size_t)nz*((size_t)iY+(size_t)ny*(size_t)iX);
    }
  }
}

template<typename T, int nDim>
void TensorField3D<T,nDim>::releaseMemory() {
  delete [] rawData;
  rawData = 0;
  for (int iX=0; iX<nx; ++iX) {
    delete [] field[iX];
  }
  delete [] field;
}
template<typename T, int nDim>
ScalarField3D<T> const& TensorField3D<T,nDim>::extractComponent(int iDim)
const
{
  components[iDim]->construct();
  for (int iEl=0; iEl<nx*ny*nz; ++iEl) {
    (*components[iDim])[iEl] = (*this)[iEl][iDim];
  };
  return *components[iDim];
}


////////// class SequentialTensorFieldSerializer3D ////////////////////////////

template<typename T, int nDim>
SequentialTensorFieldSerializer3D<T,nDim>::SequentialTensorFieldSerializer3D (
  TensorField3D<T,nDim> const& tensorField_, IndexOrdering::OrderingT ordering_ )
  : tensorField(tensorField_), ordering(ordering_),
    x0(0), x1(tensorField.getNx()-1), y0(0), y1(tensorField.getNy()-1),
    z0(0), z1(tensorField.getNz()-1),
    iX(x0), iY(y0), iZ(z0)
{ }

template<typename T, int nDim>
SequentialTensorFieldSerializer3D<T,nDim>::SequentialTensorFieldSerializer3D (
  TensorField3D<T,nDim> const& tensorField_,
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering_ )
  : tensorField(tensorField_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_), z0(z0_), z1(z1_),
    iX(x0), iY(y0), iZ(z0)
{ }

template<typename T, int nDim>
size_t SequentialTensorFieldSerializer3D<T, nDim>::getSize() const {
  return (size_t)(x1-x0+1) * (size_t)(y1-y0+1) * (size_t)(z1-z0+1) * (size_t)nDim;
}

template<typename T, int nDim>
const T* SequentialTensorFieldSerializer3D<T, nDim>::getNextDataBuffer(size_t& bufferSize) const {
  OLB_PRECONDITION( !isEmpty() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    bufferSize = (size_t)(z1-z0+1)*(size_t)nDim;
    buffer.resize(bufferSize);
    for (iZ=z0; iZ<=z1; ++iZ) {
      for (int iDim=0; iDim<nDim; ++iDim) {
        buffer[nDim*(iZ-z0)+iDim] = tensorField.get(iX, iY, iZ)[iDim];
      }
    }
    ++iY;
    if (iY > y1) {
      iY = y0;
      ++iX;
    }
  }
  else {
    bufferSize = (size_t)(x1-x0+1)*(size_t)nDim;
    buffer.resize(bufferSize);
    for (iX=x0; iX<=x1; ++iX) {
      for (int iDim=0; iDim<nDim; ++iDim) {
        buffer[nDim*(iX-x0)+iDim] = tensorField.get(iX, iY, iZ)[iDim];
      }
    }
    ++iY;
    if (iY > y1) {
      iY = y0;
      ++iZ;
    }
  }
  return &buffer[0];
}

template<typename T, int nDim>
bool SequentialTensorFieldSerializer3D<T, nDim>::isEmpty() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iZ > z1;
  }
}

////////// class SequentialTensorFieldUnSerializer3D ////////////////////////////

template<typename T, int nDim>
SequentialTensorFieldUnSerializer3D<T,nDim>::SequentialTensorFieldUnSerializer3D (
  TensorField3D<T,nDim>& tensorField_, IndexOrdering::OrderingT ordering_ )
  : tensorField(tensorField_), ordering(ordering_),
    x0(0), x1(tensorField.getNx()-1), y0(0), y1(tensorField.getNy()-1),
    z0(0), z1(tensorField.getNz()-1),
    iX(x0), iY(y0), iZ(z0)
{ }

template<typename T, int nDim>
SequentialTensorFieldUnSerializer3D<T,nDim>::SequentialTensorFieldUnSerializer3D (
  TensorField3D<T,nDim>& tensorField_,
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering_ )
  : tensorField(tensorField_), ordering(ordering_),
    x0(x0_), x1(x1_), y0(y0_), y1(y1_), z0(z0_), z1(z1_),
    iX(x0), iY(y0), iZ(z0)
{ }

template<typename T, int nDim>
size_t SequentialTensorFieldUnSerializer3D<T, nDim>::getSize() const {
  return (size_t)(x1-x0+1) * (size_t)(y1-y0+1) * (size_t)(z1-z0+1) * (size_t)nDim;
}

template<typename T, int nDim>
T* SequentialTensorFieldUnSerializer3D<T, nDim>::getNextDataBuffer(size_t& bufferSize) {
  OLB_PRECONDITION( !isFull() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    bufferSize = (size_t)(z1-z0+1)*(size_t)nDim;
  }
  else {
    bufferSize = (size_t)(x1-x0+1)*(size_t)nDim;
  }
  buffer.resize(bufferSize);
  return &buffer[0];
}

template<typename T, int nDim>
void SequentialTensorFieldUnSerializer3D<T, nDim>::commitData() {
  OLB_PRECONDITION( !isFull() );
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    for (iZ=z0; iZ<=z1; ++iZ) {
      for (int iDim=0; iDim<nDim; ++iDim) {
        tensorField.get(iX, iY, iZ)[iDim] = buffer[nDim*(iZ-z0)+iDim];
      }
    }
    ++iY;
    if (iY > y1) {
      iY = y0;
      ++iX;
    }
  }
  else {
    for (iX=x0; iX<=x1; ++iX) {
      for (int iDim=0; iDim<nDim; ++iDim) {
        tensorField.get(iX, iY, iZ)[iDim] = buffer[nDim*(iX-x0)+iDim];
      }
    }
    ++iY;
    if (iY > y1) {
      iY = y0;
      ++iZ;
    }
  }
}

template<typename T, int nDim>
bool SequentialTensorFieldUnSerializer3D<T, nDim>::isFull() const {
  if (ordering==IndexOrdering::forward || ordering==IndexOrdering::memorySaving) {
    return iX > x1;
  }
  else {
    return iZ > z1;
  }
}

}  // namespace olb

#endif
