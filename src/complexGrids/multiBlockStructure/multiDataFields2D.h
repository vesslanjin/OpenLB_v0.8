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
 * Scalar, vector and tensor fields for 2D data analysis -- header file.
 */

#ifndef MULTI_DATA_FIELDS_2D_H
#define MULTI_DATA_FIELDS_2D_H

#include <vector>
#include "core/olbDebug.h"
#include "core/dataFieldBase2D.h"
#include "core/dataFields2D.h"
#include "multiDataFieldHandler2D.h"
#include "complexGrids/multiBlockStructure/multiSerializer2D.h"

namespace olb {

template<typename T> class ParallelScalarFieldSerializerPolicy2D;
template<typename T> class ParallelScalarFieldUnSerializerPolicy2D;

/// Multi-block parallel implementation of scalar, vector and tensor fields for 2D data analysis
template<typename T>
class MultiScalarField2D : public ScalarFieldBase2D<T> {
public:
  MultiScalarField2D(MultiDataDistribution2D const& dataDistribution_);
  ~MultiScalarField2D();
  MultiScalarField2D(MultiScalarField2D<T> const& rhs);
  MultiScalarField2D<T>& operator=(MultiScalarField2D<T> const& rhs);
  void swap(MultiScalarField2D<T>& rhs);
public:
  virtual bool isConstructed() const;
  virtual void construct();
  virtual void deConstruct();
  virtual void reset();
  virtual int getNx() const { return multiDataFieldHandler->getNx(); }
  virtual int getNy() const { return multiDataFieldHandler->getNy(); }
  virtual size_t getSize() const { return (size_t)getNx()*(size_t)getNy(); }
  virtual T& get(int iX, int iY);
  virtual T const& get(int iX, int iY) const;
public:
  virtual DataSerializer<T> const& getSerializer(IndexOrdering::OrderingT ordering) const;
  virtual DataUnSerializer<T>& getUnSerializer(IndexOrdering::OrderingT ordering);
  virtual DataSerializer<T> const& getSubSerializer (
    int x0_, int x1_, int y0_, int y1_,
    IndexOrdering::OrderingT ordering ) const;
  virtual DataUnSerializer<T>& getSubUnSerializer (
    int x0_, int x1_, int y0_, int y1_,
    IndexOrdering::OrderingT ordering );
  virtual T computeReduction(DataReduction<T>& reduction) const;
  virtual MultiDataDistribution2D getDataDistribution() const;
  virtual SpatiallyExtendedObject2D* getComponent(int iBlock);
  virtual SpatiallyExtendedObject2D const* getComponent(int iBlock) const;
  virtual multiPhysics::MultiPhysicsId getMultiPhysicsId() const;
public:
  MultiDataDistribution2D const& getMultiData() const;
  std::vector<ScalarField2D<T>*> getScalarFields() { return fields; }
  const std::vector<ScalarField2D<T>*> getScalarFields() const  { return fields; }
private:
  void allocateFields();
  void deAllocateFields();
  BlockParameters2D const& getParameters(int iParam) const;
  int getNumBlocks() const;
private:
  MultiDataFieldHandler2D<T>* multiDataFieldHandler;
  std::vector<ScalarField2D<T>*> fields;
  mutable int locatedBlock; ///< for optimization, keep the last index found
  mutable T dummyScalar;
  bool constructed;
  mutable MultiSerializer2D<T>* serializer;
  mutable MultiUnSerializer2D<T>* unSerializer;
  ParallelScalarFieldSerializerPolicy2D<T> serializerPolicy;
  ParallelScalarFieldUnSerializerPolicy2D<T> unSerializerPolicy;
};


template<typename T, int nDim> class ParallelTensorFieldSerializerPolicy2D;
template<typename T, int nDim> class ParallelTensorFieldUnSerializerPolicy2D;

template<typename T, int nDim>
class MultiTensorField2D : public TensorFieldBase2D<T,nDim> {
public:
  typedef T Tensor[nDim];
public:
  MultiTensorField2D(MultiDataDistribution2D const& dataDistribution_);
  ~MultiTensorField2D();
  MultiTensorField2D(MultiTensorField2D<T,nDim> const& rhs);
  MultiTensorField2D<T,nDim>& operator=(MultiTensorField2D<T,nDim> const& rhs);
  void swap(MultiTensorField2D<T,nDim>& rhs);
public:
  virtual bool isConstructed() const;
  virtual void construct();
  virtual void deConstruct();
  virtual void reset();
  virtual int getNx() const { return multiDataFieldHandler->getNx(); }
  virtual int getNy() const { return multiDataFieldHandler->getNy(); }
  virtual Tensor& get(int iX, int iY);
  virtual Tensor const& get(int iX, int iY) const;
  MultiScalarField2D<T> const& extractComponent(int whichDim) const;
public:
  virtual DataSerializer<T> const& getSerializer(IndexOrdering::OrderingT ordering) const;
  virtual DataUnSerializer<T>& getUnSerializer(IndexOrdering::OrderingT ordering);
  virtual DataSerializer<T> const& getSubSerializer (
    int x0_, int x1_, int y0_, int y1_,
    IndexOrdering::OrderingT ordering ) const;
  virtual DataUnSerializer<T>& getSubUnSerializer (
    int x0_, int x1_, int y0_, int y1_,
    IndexOrdering::OrderingT ordering );
  virtual MultiDataDistribution2D getDataDistribution() const;
  virtual SpatiallyExtendedObject2D* getComponent(int iBlock);
  virtual SpatiallyExtendedObject2D const* getComponent(int iBlock) const;
  virtual multiPhysics::MultiPhysicsId getMultiPhysicsId() const;
public:
  MultiDataDistribution2D const& getMultiData() const;
  std::vector<TensorField2D<T,nDim>*> getTensorFields() { return fields; }
  const std::vector<TensorField2D<T,nDim>*> getTensorFields() const { return fields; }
private:
  void allocateFields();
  void deAllocateFields();
  void allocateComponents();
  void deAllocateComponents();
  BlockParameters2D const& getParameters(int iParam) const;
  int getNumBlocks() const;
private:
  MultiDataFieldHandler2D<T>* multiDataFieldHandler;
  std::vector<TensorField2D<T,nDim>*> fields;
  mutable int locatedBlock; ///< for optimization, keep the last index found
  mutable Tensor dummyTensor;
  bool constructed;
  mutable MultiScalarField2D<T> *components[nDim];
  mutable MultiSerializer2D<T>* serializer;
  mutable MultiUnSerializer2D<T>* unSerializer;
  ParallelTensorFieldSerializerPolicy2D<T,nDim> serializerPolicy;
  ParallelTensorFieldUnSerializerPolicy2D<T,nDim> unSerializerPolicy;
};

template<typename T>
class ParallelScalarFieldSerializerPolicy2D : public MultiSerializerPolicy2D<T> {
public:
  ParallelScalarFieldSerializerPolicy2D(MultiScalarField2D<T> const& field_);
  virtual int getElementSize() const;
  virtual void serializeElement(int block, int localX, int localY, T* buffer) const;
  virtual MultiDataDistribution2D const& getMultiData() const;
  virtual bool isAllocated(int block) const;
private:
  MultiScalarField2D<T> const& field;
};

template<typename T>
class ParallelScalarFieldUnSerializerPolicy2D : public MultiUnSerializerPolicy2D<T> {
public:
  ParallelScalarFieldUnSerializerPolicy2D(MultiScalarField2D<T>& field_);
  virtual int getElementSize() const;
  virtual void unSerializeElement(int block, int localX, int localY, T const* buffer);
  virtual MultiDataDistribution2D const& getMultiData() const;
  virtual bool isAllocated(int block) const;
private:
  MultiScalarField2D<T>& field;
};

template<typename T, int nDim>
class ParallelTensorFieldSerializerPolicy2D : public MultiSerializerPolicy2D<T> {
public:
  ParallelTensorFieldSerializerPolicy2D(MultiTensorField2D<T,nDim> const& field_);
  virtual int getElementSize() const;
  virtual void serializeElement(int block, int localX, int localY, T* buffer) const;
  virtual MultiDataDistribution2D const& getMultiData() const;
  virtual bool isAllocated(int block) const;
private:
  MultiTensorField2D<T,nDim> const& field;
};

template<typename T, int nDim>
class ParallelTensorFieldUnSerializerPolicy2D : public MultiUnSerializerPolicy2D<T> {
public:
  ParallelTensorFieldUnSerializerPolicy2D(MultiTensorField2D<T,nDim>& field_);
  virtual int getElementSize() const;
  virtual void unSerializeElement(int block, int localX, int localY, T const* buffer);
  virtual MultiDataDistribution2D const& getMultiData() const;
  virtual bool isAllocated(int block) const;
private:
  MultiTensorField2D<T,nDim>& field;
};

}

#endif
