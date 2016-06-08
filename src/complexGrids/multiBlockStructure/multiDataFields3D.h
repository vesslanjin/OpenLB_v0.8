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
 * Scalar, vector and tensor fields for 3D data analysis -- header file.
 */

#ifndef MULTI_DATA_FIELDS_3D_H
#define MULTI_DATA_FIELDS_3D_H

#include <vector>
#include "core/olbDebug.h"
#include "core/dataFieldBase2D.h"
#include "core/dataFieldBase3D.h"
#include "core/dataFields2D.h"
#include "core/dataFields3D.h"
#include "multiDataFieldHandler3D.h"
#include "complexGrids/multiBlockStructure/multiSerializer3D.h"

namespace olb {

template<typename T> class ScalarField2D;
template<typename T> class ParallelScalarFieldSerializerPolicy3D;
template<typename T> class ParallelScalarFieldUnSerializerPolicy3D;

/// Multi-block parallel implementation of scalar, vector and tensor fields for 3D data analysis
template<typename T>
class MultiScalarField3D : public ScalarFieldBase3D<T> {
public:
  MultiScalarField3D(MultiDataDistribution3D const& dataDistribution_);
  ~MultiScalarField3D();
  MultiScalarField3D(MultiScalarField3D<T> const& rhs);
  MultiScalarField3D<T>& operator=(MultiScalarField3D<T> const& rhs);
  void swap(MultiScalarField3D<T>& rhs);
public:
  virtual bool isConstructed() const;
  virtual void construct();
  virtual void deConstruct();
  virtual void reset();
  virtual int getNx() const { return multiDataFieldHandler->getNx(); }
  virtual int getNy() const { return multiDataFieldHandler->getNy(); }
  virtual int getNz() const { return multiDataFieldHandler->getNz(); }
  virtual size_t getSize() const { return (size_t)getNx()*(size_t)getNy()*(size_t)getNz(); }
  virtual T& get(int iX, int iY, int iZ);
  virtual T const& get(int iX, int iY, int iZ) const;
  virtual ScalarField2D<T> const& sliceX(int xVal) const;
  virtual ScalarField2D<T> const& sliceY(int yVal) const;
  virtual ScalarField2D<T> const& sliceZ(int zVal) const;
public:
  virtual DataSerializer<T> const& getSerializer(IndexOrdering::OrderingT ordering) const;
  virtual DataUnSerializer<T>& getUnSerializer(IndexOrdering::OrderingT ordering);
  virtual DataSerializer<T> const& getSubSerializer (
    int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
    IndexOrdering::OrderingT ordering ) const;
  virtual DataUnSerializer<T>& getSubUnSerializer (
    int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
    IndexOrdering::OrderingT ordering );
  virtual T computeReduction(DataReduction<T>& reduction) const;
  virtual MultiDataDistribution3D getDataDistribution() const;
  virtual SpatiallyExtendedObject3D* getComponent(int iBlock);
  virtual SpatiallyExtendedObject3D const* getComponent(int iBlock) const;
  virtual multiPhysics::MultiPhysicsId getMultiPhysicsId() const;
public:
  MultiDataDistribution3D const& getMultiData() const;
  std::vector<ScalarField3D<T>*> getScalarFields() { return fields; }
  const std::vector<ScalarField3D<T>*> getScalarFields() const { return fields; }
private:
  void allocateFields();
  void deAllocateFields();
  BlockParameters3D const& getParameters(int iParam) const;
  int getNumBlocks() const;
private:
  MultiDataFieldHandler3D<T>* multiDataFieldHandler;
  std::vector<ScalarField3D<T>*> fields;
  mutable int locatedBlock; ///< for optimization, keep the last index found
  mutable T dummyScalar;
  bool constructed;
  mutable MultiSerializer3D<T>* serializer;
  mutable MultiUnSerializer3D<T>* unSerializer;
  ParallelScalarFieldSerializerPolicy3D<T> serializerPolicy;
  ParallelScalarFieldUnSerializerPolicy3D<T> unSerializerPolicy;
  mutable ScalarField2D<T> xSlice;
  mutable ScalarField2D<T> ySlice;
  mutable ScalarField2D<T> zSlice;
};


template<typename T, int nDim> class ParallelTensorFieldSerializerPolicy3D;
template<typename T, int nDim> class ParallelTensorFieldUnSerializerPolicy3D;

template<typename T, int nDim>
class MultiTensorField3D : public TensorFieldBase3D<T,nDim> {
public:
  typedef T Tensor[nDim];
public:
  MultiTensorField3D(MultiDataDistribution3D const& dataDistribution_);
  ~MultiTensorField3D();
  MultiTensorField3D(MultiTensorField3D<T,nDim> const& rhs);
  MultiTensorField3D<T,nDim>& operator=(MultiTensorField3D<T,nDim> const& rhs);
  void swap(MultiTensorField3D<T,nDim>& rhs);
public:
  virtual bool isConstructed() const;
  virtual void construct();
  virtual void deConstruct();
  virtual void reset();
  virtual int getNx() const { return multiDataFieldHandler->getNx(); }
  virtual int getNy() const { return multiDataFieldHandler->getNy(); }
  virtual int getNz() const { return multiDataFieldHandler->getNz(); }
  virtual Tensor& get(int iX, int iY, int iZ);
  virtual Tensor const& get(int iX, int iY, int iZ) const;
  MultiScalarField3D<T> const& extractComponent(int whichDim) const;
  virtual TensorField2D<T,nDim> const& sliceX(int xVal) const;
  virtual TensorField2D<T,nDim> const& sliceY(int yVal) const;
  virtual TensorField2D<T,nDim> const& sliceZ(int zVal) const;
public:
  virtual DataSerializer<T> const& getSerializer(IndexOrdering::OrderingT ordering) const;
  virtual DataUnSerializer<T>& getUnSerializer(IndexOrdering::OrderingT ordering);
  virtual DataSerializer<T> const& getSubSerializer (
    int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
    IndexOrdering::OrderingT ordering ) const;
  virtual DataUnSerializer<T>& getSubUnSerializer (
    int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
    IndexOrdering::OrderingT ordering );
  virtual MultiDataDistribution3D getDataDistribution() const;
  virtual SpatiallyExtendedObject3D* getComponent(int iBlock);
  virtual SpatiallyExtendedObject3D const* getComponent(int iBlock) const;
  virtual multiPhysics::MultiPhysicsId getMultiPhysicsId() const;
public:
  MultiDataDistribution3D const& getMultiData() const;
  std::vector<TensorField3D<T,nDim>*> getTensorFields() { return fields; }
  const std::vector<TensorField3D<T,nDim>*> getTensorFields() const { return fields; }
private:
  void allocateFields();
  void deAllocateFields();
  void allocateComponents();
  void deAllocateComponents();
  BlockParameters3D const& getParameters(int iParam) const;
  int getNumBlocks() const;
private:
  MultiDataFieldHandler3D<T>* multiDataFieldHandler;
  std::vector<TensorField3D<T,nDim>*> fields;
  mutable int locatedBlock; ///< for optimization, keep the last index found
  mutable Tensor dummyTensor;
  bool constructed;
  mutable MultiScalarField3D<T> *components[nDim];
  mutable MultiSerializer3D<T>* serializer;
  mutable MultiUnSerializer3D<T>* unSerializer;
  ParallelTensorFieldSerializerPolicy3D<T,nDim> serializerPolicy;
  ParallelTensorFieldUnSerializerPolicy3D<T,nDim> unSerializerPolicy;
  mutable TensorField2D<T,nDim> xSlice;
  mutable TensorField2D<T,nDim> ySlice;
  mutable TensorField2D<T,nDim> zSlice;
};


template<typename T>
class ParallelScalarFieldSerializerPolicy3D : public MultiSerializerPolicy3D<T> {
public:
  ParallelScalarFieldSerializerPolicy3D(MultiScalarField3D<T> const& field_);
  virtual int getElementSize() const;
  virtual void serializeElement(int block, int localX, int localY, int localZ, T* buffer) const;
  virtual MultiDataDistribution3D const& getMultiData() const;
  virtual bool isAllocated(int block) const;
private:
  MultiScalarField3D<T> const& field;
};

template<typename T>
class ParallelScalarFieldUnSerializerPolicy3D : public MultiUnSerializerPolicy3D<T> {
public:
  ParallelScalarFieldUnSerializerPolicy3D(MultiScalarField3D<T>& field_);
  virtual int getElementSize() const;
  virtual void unSerializeElement(int block, int localX, int localY, int localZ, T const* buffer);
  virtual MultiDataDistribution3D const& getMultiData() const;
  virtual bool isAllocated(int block) const;
private:
  MultiScalarField3D<T>& field;
};

template<typename T, int nDim>
class ParallelTensorFieldSerializerPolicy3D : public MultiSerializerPolicy3D<T> {
public:
  ParallelTensorFieldSerializerPolicy3D(MultiTensorField3D<T,nDim> const& field_);
  virtual int getElementSize() const;
  virtual void serializeElement(int block, int localX, int localY, int localZ, T* buffer) const;
  virtual MultiDataDistribution3D const& getMultiData() const;
  virtual bool isAllocated(int block) const;
private:
  MultiTensorField3D<T,nDim> const& field;
};

template<typename T, int nDim>
class ParallelTensorFieldUnSerializerPolicy3D : public MultiUnSerializerPolicy3D<T> {
public:
  ParallelTensorFieldUnSerializerPolicy3D(MultiTensorField3D<T,nDim>& field_);
  virtual int getElementSize() const;
  virtual void unSerializeElement(int block, int localX, int localY, int localZ, T const* buffer);
  virtual MultiDataDistribution3D const& getMultiData() const;
  virtual bool isAllocated(int block) const;
private:
  MultiTensorField3D<T,nDim>& field;
};

}

#endif
