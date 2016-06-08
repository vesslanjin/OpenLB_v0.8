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
 * Scalar, vector and tensor fields for 2D data analysis -- generic implementation.
 */

#ifndef MULTI_DATA_FIELDS_2D_HH
#define MULTI_DATA_FIELDS_2D_HH

#include <algorithm>
#include <limits>
#include "multiDataFields2D.h"
#include "complexGrids/multiBlockStructure/multiDataGeometry2D.h"

namespace olb {

/////// Class MultiScalarField2D //////////////////////////////////

template<typename T>
MultiScalarField2D<T>::MultiScalarField2D(MultiDataDistribution2D const& dataDistribution_)
  : locatedBlock(0), constructed(false),
    serializer(0), unSerializer(0),
    serializerPolicy(*this), unSerializerPolicy(*this)
{
#ifdef PARALLEL_MODE_MPI
  multiDataFieldHandler = new ParallelMultiDataFieldHandler2D<T>(dataDistribution_);
#else
  multiDataFieldHandler = new SerialMultiDataFieldHandler2D<T>(dataDistribution_);
#endif
  allocateFields();
}

template<typename T>
MultiScalarField2D<T>::~MultiScalarField2D() {
  deConstruct();
  deAllocateFields();
  delete multiDataFieldHandler;
  delete serializer;
  delete unSerializer;
}

template<typename T>
MultiScalarField2D<T>::MultiScalarField2D(MultiScalarField2D<T> const& rhs)
  : locatedBlock(rhs.locatedBlock),
    constructed(false), // must equal false to run this.construct(), below
    serializer(0), unSerializer(0),
    serializerPolicy(*this), unSerializerPolicy(*this)
{
#ifdef PARALLEL_MODE_MPI
  multiDataFieldHandler = new ParallelMultiDataFieldHandler2D<T>(
    rhs.multiDataFieldHandler->getMultiDataDistribution() );
#else
  multiDataFieldHandler = new SerialMultiDataFieldHandler2D<T>(
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
MultiScalarField2D<T>& MultiScalarField2D<T>::operator=(MultiScalarField2D<T> const& rhs) {
  MultiScalarField2D<T> tmp(rhs);
  swap(tmp);
  return *this;
}

template<typename T>
void MultiScalarField2D<T>::swap(MultiScalarField2D<T>& rhs) {
  std::swap(multiDataFieldHandler, rhs.multiDataFieldHandler);
  fields.swap(rhs.fields);
  std::swap(locatedBlock, rhs.locatedBlock);
  std::swap(constructed, rhs.constructed);
}

template<typename T>
bool MultiScalarField2D<T>::isConstructed() const {
  return constructed;
}

template<typename T>
void MultiScalarField2D<T>::construct() {
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
void MultiScalarField2D<T>::deConstruct() {
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
void MultiScalarField2D<T>::reset() {
  OLB_PRECONDITION(isConstructed());
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    if (fields[iBlock]) {
      fields[iBlock] -> reset();
    }
  }
}

template<typename T>
void MultiScalarField2D<T>::allocateFields()
{
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    int lx=0, ly=0;
    if (multiDataFieldHandler->getLocalEnvelope(iBlock, lx, ly)) {
      fields.push_back(new ScalarField2D<T>(lx,ly));
    }
    else {
      fields.push_back( 0 );
    }
  }
}

template<typename T>
void MultiScalarField2D<T>::deAllocateFields()
{
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    delete fields[iBlock];
  }
}
template<typename T>
inline T& MultiScalarField2D<T>::get(int iX, int iY) {
  OLB_PRECONDITION(iX>=0 && iX<getNx());
  OLB_PRECONDITION(iY>=0 && iY<getNy());
  OLB_PRECONDITION(isConstructed());

  locatedBlock = getMultiData().locate(iX, iY, locatedBlock);
  if (locatedBlock == -1) {
    locatedBlock = 0;
    dummyScalar = std::numeric_limits<T>::signaling_NaN();
    return dummyScalar;
  }
  T* returnScalar = &dummyScalar;
  if (fields[locatedBlock]) {
    returnScalar = &(fields[locatedBlock] -> get( getParameters(locatedBlock).toLocalX(iX),
                     getParameters(locatedBlock).toLocalY(iY) ));
  }
  multiDataFieldHandler -> broadCastScalar(*returnScalar, locatedBlock);
  return *returnScalar;
}

template<typename T>
inline T const& MultiScalarField2D<T>::get(int iX, int iY) const {
  OLB_PRECONDITION(iX>=0 && iX<getNx());
  OLB_PRECONDITION(iY>=0 && iY<getNy());
  OLB_PRECONDITION(isConstructed());

  locatedBlock = getMultiData().locate(iX, iY, locatedBlock);
  if (locatedBlock == -1) {
    locatedBlock = 0;
    dummyScalar = std::numeric_limits<T>::signaling_NaN();
    return dummyScalar;
  }
  T* returnScalar = &dummyScalar;
  if (fields[locatedBlock]) {
    returnScalar = &(fields[locatedBlock] -> get( getParameters(locatedBlock).toLocalX(iX),
                     getParameters(locatedBlock).toLocalY(iY) ));
  }
  multiDataFieldHandler -> broadCastScalar(*returnScalar, locatedBlock);
  return *returnScalar;
}

template<typename T>
DataSerializer<T> const& MultiScalarField2D<T>::getSerializer(IndexOrdering::OrderingT ordering) const
{
  delete serializer;
  serializer = new MultiSerializer2D<T>(serializerPolicy, ordering);
  return *serializer;
}

template<typename T>
DataUnSerializer<T>& MultiScalarField2D<T>::getUnSerializer(IndexOrdering::OrderingT ordering)
{
  delete unSerializer;
  unSerializer = new MultiUnSerializer2D<T>(unSerializerPolicy, ordering);
  return *unSerializer;
}

template<typename T>
DataSerializer<T> const& MultiScalarField2D<T>::getSubSerializer (
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering ) const
{
  delete serializer;
  serializer = new MultiSerializer2D<T> (
    serializerPolicy, x0_, x1_, y0_, y1_, ordering );
  return *serializer;
}

template<typename T>
DataUnSerializer<T>& MultiScalarField2D<T>::getSubUnSerializer (
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering )
{
  delete unSerializer;
  unSerializer = new MultiUnSerializer2D<T> (
    unSerializerPolicy, x0_, x1_, y0_, y1_, ordering );
  return *unSerializer;
}


template<typename T>
T MultiScalarField2D<T>::computeReduction(DataReduction<T>& reduction) const
{
  OLB_PRECONDITION(isConstructed());
  reduction.reset();
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    if (fields[iBlock]) {
      // data must be taken on the bulk only, not on the envelope
      BlockParameters2D blockParameters = getMultiData().getBlockParameters(iBlock);
      BlockCoordinates2D bulkLocal = blockParameters.toLocal( blockParameters.getBulk() );
      for (int iX=bulkLocal.x0; iX<=bulkLocal.x1; iX++) {
        for (int iY=bulkLocal.y0; iY<=bulkLocal.y1; iY++) {
          reduction.takeElement( fields[iBlock]->get(iX,iY) );
        }
      }
    }
  }
  reduction.reduceParallel();
  return reduction.getResult();
}

template<typename T>
MultiDataDistribution2D const& MultiScalarField2D<T>::getMultiData() const {
  return multiDataFieldHandler -> getMultiDataDistribution();
}

template<typename T>
BlockParameters2D const& MultiScalarField2D<T>::getParameters(int iParam) const {
  return getMultiData().getBlockParameters(iParam);
}

template<typename T>
int MultiScalarField2D<T>::getNumBlocks() const {
  return getMultiData().getNumBlocks();
}

template<typename T>
MultiDataDistribution2D MultiScalarField2D<T>::getDataDistribution() const {
  return getMultiData();
}

template<typename T>
SpatiallyExtendedObject2D* MultiScalarField2D<T>::getComponent(int iBlock) {
  OLB_PRECONDITION( iBlock<getScalarFields().size() );
  return getScalarFields()[iBlock];
}

template<typename T>
SpatiallyExtendedObject2D const* MultiScalarField2D<T>::getComponent(int iBlock) const {
  OLB_PRECONDITION( iBlock<getScalarFields().size() );
  return getScalarFields()[iBlock];
}

template<typename T>
multiPhysics::MultiPhysicsId MultiScalarField2D<T>::getMultiPhysicsId() const {
  return multiPhysics::getMultiPhysicsScalarId<T>();
}


//////// Class MultiTensorField2D //////////////////////////////////

template<typename T, int nDim>
MultiTensorField2D<T,nDim>::MultiTensorField2D(MultiDataDistribution2D const& dataDistribution_)
  : locatedBlock(0), constructed(false),
    serializer(0), unSerializer(0),
    serializerPolicy(*this), unSerializerPolicy(*this)
{
#ifdef PARALLEL_MODE_MPI
  multiDataFieldHandler = new ParallelMultiDataFieldHandler2D<T>(dataDistribution_);
#else
  multiDataFieldHandler = new SerialMultiDataFieldHandler2D<T>(dataDistribution_);
#endif
  allocateFields();
  allocateComponents();
}

template<typename T, int nDim>
MultiTensorField2D<T,nDim>::~MultiTensorField2D() {
  deAllocateComponents();
  deConstruct();
  deAllocateFields();
  delete multiDataFieldHandler;
  delete serializer;
  delete unSerializer;
}

template<typename T, int nDim>
MultiTensorField2D<T,nDim>::MultiTensorField2D(MultiTensorField2D<T,nDim> const& rhs)
  : locatedBlock(rhs.locatedBlock),
    constructed(false), // must equal false to  run this.construct(), below
    serializer(0), unSerializer(0),
    serializerPolicy(*this), unSerializerPolicy(*this)
{
#ifdef PARALLEL_MODE_MPI
  multiDataFieldHandler = new ParallelMultiDataFieldHandler2D<T>(
    rhs.multiDataFieldHandler->getMultiDataDistribution() );
#else
  multiDataFieldHandler = new SerialMultiDataFieldHandler2D<T>(
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
MultiTensorField2D<T,nDim>& MultiTensorField2D<T,nDim>::operator=(MultiTensorField2D<T,nDim> const& rhs) {
  MultiTensorField2D<T,nDim> tmp(rhs);
  swap(tmp);
  return *this;
}

template<typename T, int nDim>
void MultiTensorField2D<T,nDim>::swap(MultiTensorField2D<T,nDim>& rhs) {
  std::swap(multiDataFieldHandler, rhs.multiDataFieldHandler);
  fields.swap(rhs.fields);
  std::swap(locatedBlock, rhs.locatedBlock);
  std::swap(constructed, rhs.constructed);
  for (int iDim=0; iDim<nDim; ++iDim) {
    std::swap(components[iDim], rhs.components[iDim]);
  }
}

template<typename T, int nDim>
bool MultiTensorField2D<T,nDim>::isConstructed() const {
  return constructed;
}

template<typename T, int nDim>
void MultiTensorField2D<T,nDim>::construct() {
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
void MultiTensorField2D<T,nDim>::deConstruct() {
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
void MultiTensorField2D<T,nDim>::reset() {
  OLB_PRECONDITION(isConstructed());
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    if (fields[iBlock]) {
      fields[iBlock] -> reset();
    }
  }
}

template<typename T, int nDim>
void MultiTensorField2D<T,nDim>::allocateFields()
{
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    int lx=0, ly=0;
    if (multiDataFieldHandler->getLocalEnvelope(iBlock, lx, ly)) {
      fields.push_back(new TensorField2D<T,nDim>(lx,ly));
    }
    else {
      fields.push_back( 0 );
    }
  }
}

template<typename T, int nDim>
void MultiTensorField2D<T,nDim>::deAllocateFields()
{
  for (int iBlock=0; iBlock<getNumBlocks(); ++iBlock) {
    delete fields[iBlock];
  }
}

template<typename T, int nDim>
void MultiTensorField2D<T,nDim>::allocateComponents()
{
  for (int iDim=0; iDim<nDim; ++iDim) {
    components[iDim] = new MultiScalarField2D<T>( getMultiData() );
  }
}

template<typename T, int nDim>
void MultiTensorField2D<T,nDim>::deAllocateComponents()
{
  for (int iDim=0; iDim<nDim; ++iDim) {
    delete components[iDim];
  }
}

template<typename T, int nDim>
inline typename MultiTensorField2D<T,nDim>::Tensor&
MultiTensorField2D<T,nDim>::get(int iX, int iY) {
  OLB_PRECONDITION(iX>=0 && iX<getNx());
  OLB_PRECONDITION(iY>=0 && iY<getNy());
  OLB_PRECONDITION(isConstructed());

  locatedBlock = getMultiData().locate(iX, iY, locatedBlock);
  if (locatedBlock == -1) {
    locatedBlock = 0;
    for (int iDim=0; iDim<nDim; iDim++) {
      dummyTensor[iDim] = std::numeric_limits<T>::signaling_NaN();
    }
    return dummyTensor;
  }
  Tensor* returnTensor = &dummyTensor;
  if (fields[locatedBlock]) {
    returnTensor = &(fields[locatedBlock] -> get( getParameters(locatedBlock).toLocalX(iX),
                     getParameters(locatedBlock).toLocalY(iY) ));
  }
  multiDataFieldHandler -> broadCastVector(*returnTensor, nDim, locatedBlock);
  return *returnTensor;
}

template<typename T, int nDim>
inline typename MultiTensorField2D<T,nDim>::Tensor const&
MultiTensorField2D<T,nDim>::get(int iX, int iY) const {
  OLB_PRECONDITION(iX>=0 && iX<getNx());
  OLB_PRECONDITION(iY>=0 && iY<getNy());
  OLB_PRECONDITION(isConstructed());

  locatedBlock = getMultiData().locate(iX, iY, locatedBlock);
  if (locatedBlock == -1) {
    locatedBlock = 0;
    for (int iDim=0; iDim<nDim; iDim++) {
      dummyTensor[iDim] = std::numeric_limits<T>::signaling_NaN();
    }
    return dummyTensor;
  }
  Tensor* returnTensor = &dummyTensor;
  if (fields[locatedBlock]) {
    returnTensor = &(fields[locatedBlock] -> get( getParameters(locatedBlock).toLocalX(iX),
                     getParameters(locatedBlock).toLocalY(iY) ));
  }
  multiDataFieldHandler -> broadCastVector(*returnTensor, nDim, locatedBlock);
  return *returnTensor;
}

template<typename T, int nDim>
DataSerializer<T> const& MultiTensorField2D<T,nDim>::getSerializer(IndexOrdering::OrderingT ordering) const
{
  delete serializer;
  serializer = new MultiSerializer2D<T>(serializerPolicy, ordering);
  return *serializer;
}

template<typename T, int nDim>
DataUnSerializer<T>& MultiTensorField2D<T,nDim>::getUnSerializer(IndexOrdering::OrderingT ordering)
{
  delete unSerializer;
  unSerializer = new MultiUnSerializer2D<T>(unSerializerPolicy, ordering);
  return *unSerializer;
}

template<typename T, int nDim>
DataSerializer<T> const& MultiTensorField2D<T,nDim>::getSubSerializer (
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering ) const
{
  delete serializer;
  serializer = new MultiSerializer2D<T> (
    serializerPolicy, x0_, x1_, y0_, y1_, ordering );
  return *serializer;
}

template<typename T, int nDim>
DataUnSerializer<T>& MultiTensorField2D<T,nDim>::getSubUnSerializer (
  int x0_, int x1_, int y0_, int y1_,
  IndexOrdering::OrderingT ordering )
{
  delete unSerializer;
  unSerializer = new MultiUnSerializer2D<T> (
    unSerializerPolicy, x0_, x1_, y0_, y1_, ordering );
  return *unSerializer;
}


template<typename T, int nDim>
MultiDataDistribution2D const& MultiTensorField2D<T,nDim>::getMultiData() const {
  return multiDataFieldHandler -> getMultiDataDistribution();
}

template<typename T, int nDim>
BlockParameters2D const& MultiTensorField2D<T,nDim>::getParameters(int iParam) const {
  return getMultiData().getBlockParameters(iParam);
}

template<typename T, int nDim>
int MultiTensorField2D<T,nDim>::getNumBlocks() const {
  return getMultiData().getNumBlocks();
}

template<typename T, int nDim>
MultiScalarField2D<T> const& MultiTensorField2D<T,nDim>::extractComponent(int whichDim)
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
MultiDataDistribution2D MultiTensorField2D<T,nDim>::getDataDistribution() const {
  return getMultiData();
}

template<typename T, int nDim>
SpatiallyExtendedObject2D* MultiTensorField2D<T,nDim>::getComponent(int iBlock) {
  OLB_PRECONDITION( iBlock<getTensorFields().size() );
  return getTensorFields()[iBlock];
}

template<typename T, int nDim>
SpatiallyExtendedObject2D const* MultiTensorField2D<T,nDim>::getComponent(int iBlock) const {
  OLB_PRECONDITION( iBlock<getTensorFields().size() );
  return getTensorFields()[iBlock];
}

template<typename T, int nDim>
multiPhysics::MultiPhysicsId MultiTensorField2D<T,nDim>::getMultiPhysicsId() const {
  return multiPhysics::getMultiPhysicsTensorId<T,nDim>();
}


////////// class ParallelScalarFieldSerializerPolicy2D ////////////////////////////

template<typename T>
ParallelScalarFieldSerializerPolicy2D<T>::ParallelScalarFieldSerializerPolicy2D (
  MultiScalarField2D<T> const& field_ )
  : field(field_)
{ }

template<typename T>
int ParallelScalarFieldSerializerPolicy2D<T>::getElementSize() const {
  return 1;
}

template<typename T>
void ParallelScalarFieldSerializerPolicy2D<T>::serializeElement (
  int block, int localX, int localY, T* buffer) const
{
  *buffer = field.getScalarFields()[block] -> get(localX, localY);
}

template<typename T>
MultiDataDistribution2D const& ParallelScalarFieldSerializerPolicy2D<T>::getMultiData() const
{
  return field.getMultiData();
}

template<typename T>
bool ParallelScalarFieldSerializerPolicy2D<T>::isAllocated(int block) const
{
  return field.getScalarFields()[block];
}


////////// class ParallelScalarFieldUnSerializerPolicy2D ////////////////////////////

template<typename T>
ParallelScalarFieldUnSerializerPolicy2D<T>::ParallelScalarFieldUnSerializerPolicy2D (
  MultiScalarField2D<T>& field_ )
  : field(field_)
{ }

template<typename T>
int ParallelScalarFieldUnSerializerPolicy2D<T>::getElementSize() const {
  return 1;
}

template<typename T>
void ParallelScalarFieldUnSerializerPolicy2D<T>::unSerializeElement (
  int block, int localX, int localY, T const* buffer)
{
  field.getScalarFields()[block] -> get(localX, localY) = *buffer;
}

template<typename T>
MultiDataDistribution2D const& ParallelScalarFieldUnSerializerPolicy2D<T>::getMultiData() const
{
  return field.getMultiData();
}

template<typename T>
bool ParallelScalarFieldUnSerializerPolicy2D<T>::isAllocated(int block) const
{
  return field.getScalarFields()[block];
}


////////// class ParallelTensorFieldSerializerPolicy2D ////////////////////////////

template<typename T, int nDim>
ParallelTensorFieldSerializerPolicy2D<T,nDim>::ParallelTensorFieldSerializerPolicy2D (
  MultiTensorField2D<T,nDim> const& field_ )
  : field(field_)
{ }

template<typename T, int nDim>
int ParallelTensorFieldSerializerPolicy2D<T,nDim>::getElementSize() const {
  return nDim;
}

template<typename T, int nDim>
void ParallelTensorFieldSerializerPolicy2D<T,nDim>::serializeElement (
  int block, int localX, int localY, T* buffer) const
{
  for (int iDim=0; iDim<nDim; ++iDim) {
    buffer[iDim] = field.getTensorFields()[block] -> get(localX, localY)[iDim];
  }
}

template<typename T, int nDim>
MultiDataDistribution2D const& ParallelTensorFieldSerializerPolicy2D<T,nDim>::getMultiData() const
{
  return field.getMultiData();
}

template<typename T, int nDim>
bool ParallelTensorFieldSerializerPolicy2D<T,nDim>::isAllocated(int block) const
{
  return field.getTensorFields()[block];
}


////////// class ParallelTensorFieldUnSerializerPolicy2D ////////////////////////////

template<typename T, int nDim>
ParallelTensorFieldUnSerializerPolicy2D<T,nDim>::ParallelTensorFieldUnSerializerPolicy2D (
  MultiTensorField2D<T,nDim>& field_ )
  : field(field_)
{ }

template<typename T, int nDim>
int ParallelTensorFieldUnSerializerPolicy2D<T,nDim>::getElementSize() const {
  return nDim;
}

template<typename T, int nDim>
void ParallelTensorFieldUnSerializerPolicy2D<T,nDim>::unSerializeElement (
  int block, int localX, int localY, T const* buffer)
{
  for (int iDim=0; iDim<nDim; ++iDim) {
    field.getTensorFields()[block] -> get(localX, localY)[iDim] = buffer[iDim];
  }
}

template<typename T, int nDim>
MultiDataDistribution2D const& ParallelTensorFieldUnSerializerPolicy2D<T,nDim>::getMultiData() const
{
  return field.getMultiData();
}

template<typename T, int nDim>
bool ParallelTensorFieldUnSerializerPolicy2D<T,nDim>::isAllocated(int block) const
{
  return field.getTensorFields()[block];
}

}  // namespace olb

#endif
