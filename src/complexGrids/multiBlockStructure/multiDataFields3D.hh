/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007, 2008 Bernd Stahl and Jonas Latt
 *  Address: Battelle Batiment A, Route de Drize 7, 1227 Carouge, Switzerland
 *  E-mail: bernd.stahl@cui.unige.ch
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

#ifndef MULTI_DATA_FIELDS_3D_HH
#define MULTI_DATA_FIELDS_3D_HH

#include "multiDataFields3D.h"
#include "complexGrids/multiBlockStructure/multiDataGeometry3D.h"
#include <algorithm>
#include <limits>

namespace olb {

/////// Class MultiScalarField3D //////////////////////////////////

template<typename T>
MultiScalarField3D<T>::MultiScalarField3D(MultiDataDistribution3D const& dataDistribution_)
  : locatedBlock(0), constructed(false),
    serializer(0), unSerializer(0),
    serializerPolicy(*this), unSerializerPolicy(*this),
    xSlice(dataDistribution_.getNy(), dataDistribution_.getNz() ),
    ySlice(dataDistribution_.getNx(), dataDistribution_.getNz() ),
    zSlice(dataDistribution_.getNx(), dataDistribution_.getNy() )
{
#ifdef PARALLEL_MODE_MPI
  multiDataFieldHandler = new ParallelMultiDataFieldHandler3D<T>(dataDistribution_);
#else
  multiDataFieldHandler = new SerialMultiDataFieldHandler3D<T>(dataDistribution_);
#endif
  allocateFields();
}

template<typename T>
MultiScalarField3D<T>::~MultiScalarField3D() {
  deConstruct();
  deAllocateFields();
  delete multiDataFieldHandler;
  delete serializer;
  delete unSerializer;
}

template<typename T>
MultiScalarField3D<T>::MultiScalarField3D(MultiScalarField3D<T> const& rhs)
  : locatedBlock(rhs.locatedBlock),
    constructed(false), // must equal false to run this.construct(), below
    serializer(0), unSerializer(0),
    serializerPolicy(*this), unSerializerPolicy(*this),
    xSlice(rhs.getMultiData().getNy(), rhs.getMultiData().getNz() ),
    ySlice(rhs.getMultiData().getNx(), rhs.getMultiData().getNz() ),
    zSlice(rhs.getMultiData().getNx(), rhs.getMultiData().getNy() )
{
#ifdef PARALLEL_MODE_MPI
  multiDataFieldHandler = new ParallelMultiDataFieldHandler3D<T>(
    rhs.multiDataFieldHandler->getMultiDataDistribution() );
#else
  multiDataFieldHandler = new SerialMultiDataFieldHandler3D<T>(
    rhs.multiDataFieldHandler->getMultiDataDistribution() );
#endif
  allocateFields();
  if (rhs.isConstructed()) {
    construct();
  }
  if (isConstructed()) {
    for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
      if (fields[iBlock]) {
        *(fields[iBlock]) = *(rhs.fields[iBlock]);
      }
    }
  }
}

template<typename T>
MultiScalarField3D<T>& MultiScalarField3D<T>::operator=(MultiScalarField3D<T> const& rhs) {
  MultiScalarField3D<T> tmp(rhs);
  swap(tmp);
  return *this;
}

template<typename T>
void MultiScalarField3D<T>::swap(MultiScalarField3D<T>& rhs) {
  std::swap(multiDataFieldHandler, rhs.multiDataFieldHandler);
  fields.swap(rhs.fields);
  std::swap(locatedBlock, rhs.locatedBlock);
  std::swap(constructed, rhs.constructed);
}

template<typename T>
bool MultiScalarField3D<T>::isConstructed() const {
  return constructed;
}

template<typename T>
void MultiScalarField3D<T>::construct() {
  if (!isConstructed()) {
    for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
      if (fields[iBlock]) {
        fields[iBlock] -> construct();
      }
    }
    constructed = true;
  }
}

template<typename T>
void MultiScalarField3D<T>::deConstruct() {
  if (isConstructed()) {
    for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
      if (fields[iBlock]) {
        fields[iBlock] -> deConstruct();
      }
    }
    constructed = false;
  }
}

template<typename T>
void MultiScalarField3D<T>::reset() {
  OLB_PRECONDITION(isConstructed());
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    if (fields[iBlock]) {
      fields[iBlock] -> reset();
    }
  }
}

template<typename T>
void MultiScalarField3D<T>::allocateFields()
{
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    int lx=0, ly=0, lz=0;
    if (multiDataFieldHandler->getLocalEnvelope(iBlock, lx, ly, lz)) {
      fields.push_back(new ScalarField3D<T>(lx,ly,lz));
    }
    else {
      fields.push_back( 0 );
    }
  }
}

template<typename T>
void MultiScalarField3D<T>::deAllocateFields()
{
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    delete fields[iBlock];
  }
}
template<typename T>
inline T& MultiScalarField3D<T>::get(int iX, int iY, int iZ) {
  OLB_PRECONDITION(iX>=0 && iX<getNx());
  OLB_PRECONDITION(iY>=0 && iY<getNy());
  OLB_PRECONDITION(iZ>=0 && iZ<getNz());
  OLB_PRECONDITION(isConstructed());

  locatedBlock = getMultiData().locate(iX, iY, iZ, locatedBlock);
  if (locatedBlock == -1) {
    locatedBlock = 0;
    dummyScalar = std::numeric_limits<T>::signaling_NaN();
    return dummyScalar;
  }
  T* returnScalar = &dummyScalar;
  if (fields[locatedBlock]) {
    returnScalar = &(fields[locatedBlock] -> get(
                       getParameters(locatedBlock).toLocalX(iX),
                       getParameters(locatedBlock).toLocalY(iY),
                       getParameters(locatedBlock).toLocalZ(iZ) ));
  }
  multiDataFieldHandler -> broadCastScalar(*returnScalar, locatedBlock);
  return *returnScalar;
}

template<typename T>
inline T const& MultiScalarField3D<T>::get(int iX, int iY, int iZ) const {
  OLB_PRECONDITION(iX>=0 && iX<getNx());
  OLB_PRECONDITION(iY>=0 && iY<getNy());
  OLB_PRECONDITION(iZ>=0 && iZ<getNz());
  OLB_PRECONDITION(isConstructed());

  locatedBlock = getMultiData().locate(iX, iY, iZ, locatedBlock);
  if (locatedBlock == -1) {
    locatedBlock = 0;
    dummyScalar = std::numeric_limits<T>::signaling_NaN();
    return dummyScalar;
  }
  T* returnScalar = &dummyScalar;
  if (fields[locatedBlock]) {
    returnScalar = &(fields[locatedBlock] -> get(
                       getParameters(locatedBlock).toLocalX(iX),
                       getParameters(locatedBlock).toLocalY(iY),
                       getParameters(locatedBlock).toLocalZ(iZ) ));
  }
  multiDataFieldHandler -> broadCastScalar(*returnScalar, locatedBlock);
  return *returnScalar;
}

template<typename T>
ScalarField2D<T> const& MultiScalarField3D<T>::sliceX(int xVal) const {
  xSlice.construct();
  copySerializedData (
    this->getSubSerializer(xVal, xVal, 0, getNy()-1, 0, getNz()-1, IndexOrdering::forward),
    xSlice.getUnSerializer(IndexOrdering::forward) );
  return xSlice;
}

template<typename T>
ScalarField2D<T> const& MultiScalarField3D<T>::sliceY(int yVal) const {
  ySlice.construct();
  copySerializedData (
    this->getSubSerializer(0, getNx()-1, yVal, yVal, 0, getNz()-1, IndexOrdering::forward),
    ySlice.getUnSerializer(IndexOrdering::forward) );
  return ySlice;
}

template<typename T>
ScalarField2D<T> const& MultiScalarField3D<T>::sliceZ(int zVal) const {
  zSlice.construct();
  copySerializedData (
    this->getSubSerializer(0, getNx()-1, 0, getNy()-1, zVal, zVal, IndexOrdering::backward),
    zSlice.getUnSerializer(IndexOrdering::backward) );
  return zSlice;
}

template<typename T>
DataSerializer<T> const& MultiScalarField3D<T>::getSerializer(IndexOrdering::OrderingT ordering) const
{
  delete serializer;
  serializer = new MultiSerializer3D<T>(serializerPolicy, ordering);
  return *serializer;
}

template<typename T>
DataUnSerializer<T>& MultiScalarField3D<T>::getUnSerializer(IndexOrdering::OrderingT ordering)
{
  delete unSerializer;
  unSerializer = new MultiUnSerializer3D<T>(unSerializerPolicy, ordering);
  return *unSerializer;
}

template<typename T>
DataSerializer<T> const& MultiScalarField3D<T>::getSubSerializer (
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering ) const
{
  delete serializer;
  serializer = new MultiSerializer3D<T> (
    serializerPolicy, x0_, x1_, y0_, y1_, z0_, z1_, ordering );
  return *serializer;
}

template<typename T>
DataUnSerializer<T>& MultiScalarField3D<T>::getSubUnSerializer (
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering )
{
  delete unSerializer;
  unSerializer = new MultiUnSerializer3D<T> (
    unSerializerPolicy, x0_, x1_, y0_, y1_, z0_, z1_, ordering );
  return *unSerializer;
}


template<typename T>
T MultiScalarField3D<T>::computeReduction(DataReduction<T>& reduction) const
{
  OLB_PRECONDITION(isConstructed());
  reduction.reset();
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    if (fields[iBlock]) {
      // data must be taken on the bulk only, not on the envelope
      BlockParameters3D blockParameters = getMultiData().getBlockParameters(iBlock);
      BlockCoordinates3D bulkLocal = blockParameters.toLocal( blockParameters.getBulk() );
      for (int iX=bulkLocal.x0; iX<=bulkLocal.x1; iX++) {
        for (int iY=bulkLocal.y0; iY<=bulkLocal.y1; iY++) {
          for (int iZ=bulkLocal.z0; iZ<=bulkLocal.z1; iZ++) {
            reduction.takeElement( fields[iBlock]->get(iX,iY,iZ) );
          }
        }
      }
    }
  }
  reduction.reduceParallel();
  return reduction.getResult();
}

template<typename T>
MultiDataDistribution3D const& MultiScalarField3D<T>::getMultiData() const {
  return multiDataFieldHandler -> getMultiDataDistribution();
}

template<typename T>
BlockParameters3D const& MultiScalarField3D<T>::getParameters(int iParam) const {
  return getMultiData().getBlockParameters(iParam);
}

template<typename T>
int MultiScalarField3D<T>::getNumBlocks() const {
  return getMultiData().getNumBlocks();
}

template<typename T>
MultiDataDistribution3D MultiScalarField3D<T>::getDataDistribution() const {
  return getMultiData();
}

template<typename T>
SpatiallyExtendedObject3D* MultiScalarField3D<T>::getComponent(int iBlock) {
  OLB_PRECONDITION( iBlock<getScalarFields().size() );
  return getScalarFields()[iBlock];
}

template<typename T>
SpatiallyExtendedObject3D const* MultiScalarField3D<T>::getComponent(int iBlock) const {
  OLB_PRECONDITION( iBlock<getScalarFields().size() );
  return getScalarFields()[iBlock];
}

template<typename T>
multiPhysics::MultiPhysicsId MultiScalarField3D<T>::getMultiPhysicsId() const {
  return multiPhysics::getMultiPhysicsScalarId<T>();
}


//////// Class MultiTensorField3D //////////////////////////////////

template<typename T, int nDim>
MultiTensorField3D<T,nDim>::MultiTensorField3D(MultiDataDistribution3D const& dataDistribution_)
  : locatedBlock(0), constructed(false),
    serializer(0), unSerializer(0),
    serializerPolicy(*this), unSerializerPolicy(*this),
    xSlice(dataDistribution_.getNy(), dataDistribution_.getNz() ),
    ySlice(dataDistribution_.getNx(), dataDistribution_.getNz() ),
    zSlice(dataDistribution_.getNx(), dataDistribution_.getNy() )
{
#ifdef PARALLEL_MODE_MPI
  multiDataFieldHandler = new ParallelMultiDataFieldHandler3D<T>(dataDistribution_);
#else
  multiDataFieldHandler = new SerialMultiDataFieldHandler3D<T>(dataDistribution_);
#endif
  allocateFields();
  allocateComponents();
}

template<typename T, int nDim>
MultiTensorField3D<T,nDim>::~MultiTensorField3D() {
  deAllocateComponents();
  deConstruct();
  deAllocateFields();
  delete multiDataFieldHandler;
  delete serializer;
  delete unSerializer;
}

template<typename T, int nDim>
MultiTensorField3D<T,nDim>::MultiTensorField3D(MultiTensorField3D<T,nDim> const& rhs)
  : locatedBlock(rhs.locatedBlock), constructed(false), // must equal false to  run this.construct(), below
    serializer(0), unSerializer(0),
    serializerPolicy(*this), unSerializerPolicy(*this),
    xSlice(rhs.getMultiData().getNy(), rhs.getMultiData().getNz() ),
    ySlice(rhs.getMultiData().getNx(), rhs.getMultiData().getNz() ),
    zSlice(rhs.getMultiData().getNx(), rhs.getMultiData().getNy() )
{
#ifdef PARALLEL_MODE_MPI
  multiDataFieldHandler = new ParallelMultiDataFieldHandler3D<T>(
    rhs.multiDataFieldHandler->getMultiDataDistribution() );
#else
  multiDataFieldHandler = new SerialMultiDataFieldHandler3D<T>(
    rhs.multiDataFieldHandler->getMultiDataDistribution() );
#endif
  allocateFields();
  allocateComponents();
  if (rhs.isConstructed()) {
    construct();
  }
  if (isConstructed()) {
    for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
      if (fields[iBlock]) {
        *(fields[iBlock]) = *(rhs.fields[iBlock]);
      }
    }
  }
}

template<typename T, int nDim>
MultiTensorField3D<T,nDim>& MultiTensorField3D<T,nDim>::operator=(MultiTensorField3D<T,nDim> const& rhs) {
  MultiTensorField3D<T,nDim> tmp(rhs);
  swap(tmp);
  return *this;
}

template<typename T, int nDim>
void MultiTensorField3D<T,nDim>::swap(MultiTensorField3D<T,nDim>& rhs) {
  std::swap(multiDataFieldHandler, rhs.multiDataFieldHandler);
  fields.swap(rhs.fields);
  std::swap(locatedBlock, rhs.locatedBlock);
  std::swap(constructed, rhs.constructed);
  for (int iDim=0; iDim<nDim; ++iDim) {
    std::swap(components[iDim], rhs.components[iDim]);
  }
}

template<typename T, int nDim>
bool MultiTensorField3D<T,nDim>::isConstructed() const {
  return constructed;
}

template<typename T, int nDim>
void MultiTensorField3D<T,nDim>::construct() {
  if (!isConstructed()) {
    for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
      if (fields[iBlock]) {
        fields[iBlock] -> construct();
      }
    }
    constructed = true;
  }
}

template<typename T, int nDim>
void MultiTensorField3D<T,nDim>::deConstruct() {
  if (isConstructed()) {
    for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
      if (fields[iBlock]) {
        fields[iBlock] -> deConstruct();
      }
    }
    constructed = false;
  }
}

template<typename T, int nDim>
void MultiTensorField3D<T,nDim>::reset() {
  OLB_PRECONDITION(isConstructed());
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    if (fields[iBlock]) {
      fields[iBlock] -> reset();
    }
  }
}

template<typename T, int nDim>
void MultiTensorField3D<T,nDim>::allocateFields()
{
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    int lx=0, ly=0, lz=0;
    if (multiDataFieldHandler->getLocalEnvelope(iBlock, lx, ly, lz)) {
      fields.push_back(new TensorField3D<T,nDim>(lx,ly,lz));
    }
    else {
      fields.push_back( 0 );
    }
  }
}

template<typename T, int nDim>
void MultiTensorField3D<T,nDim>::deAllocateFields()
{
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    delete fields[iBlock];
  }
}

template<typename T, int nDim>
void MultiTensorField3D<T,nDim>::allocateComponents()
{
  for (int iDim=0; iDim<nDim; ++iDim) {
    components[iDim] = new MultiScalarField3D<T>( getMultiData() );
  }
}

template<typename T, int nDim>
void MultiTensorField3D<T,nDim>::deAllocateComponents()
{
  for (int iDim=0; iDim<nDim; ++iDim) {
    delete components[iDim];
  }
}

template<typename T, int nDim>
inline typename MultiTensorField3D<T,nDim>::Tensor&
MultiTensorField3D<T,nDim>::get(int iX, int iY, int iZ) {
  OLB_PRECONDITION(iX>=0 && iX<getNx());
  OLB_PRECONDITION(iY>=0 && iY<getNy());
  OLB_PRECONDITION(iZ>=0 && iZ<getNz());
  OLB_PRECONDITION(isConstructed());

  locatedBlock = getMultiData().locate(iX, iY, iZ, locatedBlock);
  if (locatedBlock == -1) {
    locatedBlock = 0;
    for (int iDim=0; iDim<nDim; iDim++) {
      dummyTensor[iDim] = std::numeric_limits<T>::signaling_NaN();
    }
    return dummyTensor;
  }
  Tensor* returnTensor = &dummyTensor;
  if (fields[locatedBlock]) {
    returnTensor = &(fields[locatedBlock] -> get(
                       getParameters(locatedBlock).toLocalX(iX),
                       getParameters(locatedBlock).toLocalY(iY),
                       getParameters(locatedBlock).toLocalZ(iZ) ));
  }
  multiDataFieldHandler -> broadCastVector(*returnTensor, nDim, locatedBlock);
  return *returnTensor;
}

template<typename T, int nDim>
inline typename MultiTensorField3D<T,nDim>::Tensor const&
MultiTensorField3D<T,nDim>::get(int iX, int iY, int iZ) const {
  OLB_PRECONDITION(iX>=0 && iX<getNx());
  OLB_PRECONDITION(iY>=0 && iY<getNy());
  OLB_PRECONDITION(iZ>=0 && iZ<getNz());
  OLB_PRECONDITION(isConstructed());

  locatedBlock = getMultiData().locate(iX, iY, iZ, locatedBlock);
  if (locatedBlock == -1) {
    locatedBlock = 0;
    for (int iDim=0; iDim<nDim; iDim++) {
      dummyTensor[iDim] = std::numeric_limits<T>::signaling_NaN();
    }
    return dummyTensor;
  }
  Tensor* returnTensor = &dummyTensor;
  if (fields[locatedBlock]) {
    returnTensor = &(fields[locatedBlock] -> get(
                       getParameters(locatedBlock).toLocalX(iX),
                       getParameters(locatedBlock).toLocalY(iY),
                       getParameters(locatedBlock).toLocalZ(iZ) ));
  }
  multiDataFieldHandler -> broadCastVector(*returnTensor, nDim, locatedBlock);
  return *returnTensor;
}
template<typename T, int nDim>
TensorField2D<T,nDim> const& MultiTensorField3D<T,nDim>::sliceX(int xVal) const {
  xSlice.construct();
  copySerializedData (
    this->getSubSerializer(xVal, xVal, 0, getNy()-1, 0, getNz()-1, IndexOrdering::forward),
    xSlice.getUnSerializer(IndexOrdering::forward) );
  return xSlice;
}

template<typename T, int nDim>
TensorField2D<T,nDim> const& MultiTensorField3D<T,nDim>::sliceY(int yVal) const {
  ySlice.construct();
  copySerializedData (
    this->getSubSerializer(0, getNx()-1, yVal, yVal, 0, getNz()-1, IndexOrdering::forward),
    ySlice.getUnSerializer(IndexOrdering::forward) );
  return ySlice;
}

template<typename T, int nDim>
TensorField2D<T,nDim> const& MultiTensorField3D<T,nDim>::sliceZ(int zVal) const {
  zSlice.construct();
  copySerializedData (
    this->getSubSerializer(0, getNx()-1, 0, getNy()-1, zVal, zVal, IndexOrdering::backward),
    zSlice.getUnSerializer(IndexOrdering::backward) );
  return zSlice;
}

template<typename T, int nDim>
DataSerializer<T> const& MultiTensorField3D<T,nDim>::getSerializer(IndexOrdering::OrderingT ordering) const
{
  delete serializer;
  serializer = new MultiSerializer3D<T>(serializerPolicy, ordering);
  return *serializer;
}

template<typename T, int nDim>
DataUnSerializer<T>& MultiTensorField3D<T,nDim>::getUnSerializer(IndexOrdering::OrderingT ordering)
{
  delete unSerializer;
  unSerializer = new MultiUnSerializer3D<T>(unSerializerPolicy, ordering);
  return *unSerializer;
}

template<typename T, int nDim>
DataSerializer<T> const& MultiTensorField3D<T,nDim>::getSubSerializer (
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering ) const
{
  delete serializer;
  serializer = new MultiSerializer3D<T> (
    serializerPolicy, x0_, x1_, y0_, y1_, z0_, z1_, ordering );
  return *serializer;
}

template<typename T, int nDim>
DataUnSerializer<T>& MultiTensorField3D<T,nDim>::getSubUnSerializer (
  int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
  IndexOrdering::OrderingT ordering )
{
  delete unSerializer;
  unSerializer = new MultiUnSerializer3D<T> (
    unSerializerPolicy, x0_, x1_, y0_, y1_, z0_, z1_, ordering );
  return *unSerializer;
}


template<typename T, int nDim>
MultiDataDistribution3D const& MultiTensorField3D<T,nDim>::getMultiData() const {
  return multiDataFieldHandler -> getMultiDataDistribution();
}

template<typename T, int nDim>
BlockParameters3D const& MultiTensorField3D<T,nDim>::getParameters(int iParam) const {
  return getMultiData().getBlockParameters(iParam);
}

template<typename T, int nDim>
int MultiTensorField3D<T,nDim>::getNumBlocks() const {
  return getMultiData().getNumBlocks();
}

template<typename T, int nDim>
MultiScalarField3D<T> const& MultiTensorField3D<T,nDim>::extractComponent(int whichDim)
const
{
  OLB_PRECONDITION(isConstructed());
  components[whichDim] -> construct();

  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    if (fields[iBlock]) {
      *(components[whichDim]->getScalarFields()[iBlock]) =
        this -> getTensorFields()[iBlock] -> extractComponent(whichDim);
    }
  }
  return *components[whichDim];
}

template<typename T, int nDim>
MultiDataDistribution3D MultiTensorField3D<T,nDim>::getDataDistribution() const {
  return getMultiData();
}

template<typename T, int nDim>
SpatiallyExtendedObject3D* MultiTensorField3D<T,nDim>::getComponent(int iBlock) {
  OLB_PRECONDITION( iBlock<getTensorFields().size() );
  return getTensorFields()[iBlock];
}

template<typename T, int nDim>
SpatiallyExtendedObject3D const* MultiTensorField3D<T,nDim>::getComponent(int iBlock) const {
  OLB_PRECONDITION( iBlock<getTensorFields().size() );
  return getTensorFields()[iBlock];
}

template<typename T, int nDim>
multiPhysics::MultiPhysicsId MultiTensorField3D<T,nDim>::getMultiPhysicsId() const {
  return multiPhysics::getMultiPhysicsTensorId<T,nDim>();
}


////////// class ParallelScalarFieldSerializerPolicy3D ////////////////////////////

template<typename T>
ParallelScalarFieldSerializerPolicy3D<T>::ParallelScalarFieldSerializerPolicy3D (
  MultiScalarField3D<T> const& field_ )
  : field(field_)
{ }

template<typename T>
int ParallelScalarFieldSerializerPolicy3D<T>::getElementSize() const {
  return 1;
}

template<typename T>
void ParallelScalarFieldSerializerPolicy3D<T>::serializeElement (
  int block, int localX, int localY, int localZ, T* buffer) const
{
  *buffer = field.getScalarFields()[block] -> get(localX, localY, localZ);
}

template<typename T>
MultiDataDistribution3D const& ParallelScalarFieldSerializerPolicy3D<T>::getMultiData() const
{
  return field.getMultiData();
}

template<typename T>
bool ParallelScalarFieldSerializerPolicy3D<T>::isAllocated(int block) const
{
  return field.getScalarFields()[block];
}


////////// class ParallelScalarFieldUnSerializerPolicy3D ////////////////////////////

template<typename T>
ParallelScalarFieldUnSerializerPolicy3D<T>::ParallelScalarFieldUnSerializerPolicy3D (
  MultiScalarField3D<T>& field_ )
  : field(field_)
{ }

template<typename T>
int ParallelScalarFieldUnSerializerPolicy3D<T>::getElementSize() const {
  return 1;
}

template<typename T>
void ParallelScalarFieldUnSerializerPolicy3D<T>::unSerializeElement (
  int block, int localX, int localY, int localZ, T const* buffer)
{
  field.getScalarFields()[block] -> get(localX, localY, localZ) = *buffer;
}

template<typename T>
MultiDataDistribution3D const& ParallelScalarFieldUnSerializerPolicy3D<T>::getMultiData() const
{
  return field.getMultiData();
}

template<typename T>
bool ParallelScalarFieldUnSerializerPolicy3D<T>::isAllocated(int block) const
{
  return field.getScalarFields()[block];
}


////////// class ParallelTensorFieldSerializerPolicy3D ////////////////////////////

template<typename T, int nDim>
ParallelTensorFieldSerializerPolicy3D<T,nDim>::ParallelTensorFieldSerializerPolicy3D (
  MultiTensorField3D<T,nDim> const& field_ )
  : field(field_)
{ }

template<typename T, int nDim>
int ParallelTensorFieldSerializerPolicy3D<T,nDim>::getElementSize() const {
  return nDim;
}

template<typename T, int nDim>
void ParallelTensorFieldSerializerPolicy3D<T,nDim>::serializeElement (
  int block, int localX, int localY, int localZ, T* buffer) const
{
  for (int iDim=0; iDim<nDim; ++iDim) {
    buffer[iDim] = field.getTensorFields()[block] -> get(localX, localY, localZ)[iDim];
  }
}

template<typename T, int nDim>
MultiDataDistribution3D const& ParallelTensorFieldSerializerPolicy3D<T,nDim>::getMultiData() const
{
  return field.getMultiData();
}

template<typename T, int nDim>
bool ParallelTensorFieldSerializerPolicy3D<T,nDim>::isAllocated(int block) const
{
  return field.getTensorFields()[block];
}


////////// class ParallelTensorFieldUnSerializerPolicy3D ////////////////////////////

template<typename T, int nDim>
ParallelTensorFieldUnSerializerPolicy3D<T,nDim>::ParallelTensorFieldUnSerializerPolicy3D (
  MultiTensorField3D<T,nDim>& field_ )
  : field(field_)
{ }

template<typename T, int nDim>
int ParallelTensorFieldUnSerializerPolicy3D<T,nDim>::getElementSize() const {
  return nDim;
}

template<typename T, int nDim>
void ParallelTensorFieldUnSerializerPolicy3D<T,nDim>::unSerializeElement (
  int block, int localX, int localY, int localZ, T const* buffer)
{
  for (int iDim=0; iDim<nDim; ++iDim) {
    field.getTensorFields()[block] -> get(localX, localY, localZ)[iDim] = buffer[iDim];
  }
}

template<typename T, int nDim>
MultiDataDistribution3D const& ParallelTensorFieldUnSerializerPolicy3D<T,nDim>::getMultiData() const
{
  return field.getMultiData();
}

template<typename T, int nDim>
bool ParallelTensorFieldUnSerializerPolicy3D<T,nDim>::isAllocated(int block) const
{
  return field.getTensorFields()[block];
}


}  // namespace olb

#endif
