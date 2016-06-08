/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006, 2007 Jonas Latt, Bernd Stahl
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
 * Serial implementation of scalar, vector and tensor fields for 2D data analysis.
 * -- header file
 */

#ifndef DATA_FIELDS_2D_H
#define DATA_FIELDS_2D_H

#include "olbDebug.h"
#include "dataFieldBase2D.h"

namespace olb {

template<typename T> class SequentialScalarFieldSerializer2D;
template<typename T> class SequentialScalarFieldUnSerializer2D;

template<typename T>
class ScalarField2D : public ScalarFieldBase2D<T> {
public:
  ScalarField2D(int nx_, int ny_);
  ~ScalarField2D();
  ScalarField2D(ScalarField2D<T> const& rhs);
  ScalarField2D<T>& operator=(ScalarField2D<T> const& rhs);
  void swap(ScalarField2D<T>& rhs);
public:
  virtual bool isConstructed() const;
  virtual void construct();
  virtual void deConstruct();
  virtual void reset();
  virtual int getNx() const { return nx; }
  virtual int getNy() const { return ny; }
  virtual size_t getSize() const { return (size_t)nx*(size_t)ny; }
  virtual T& get(int iX, int iY) {
    OLB_PRECONDITION(iX>=0 && iX<nx);
    OLB_PRECONDITION(iY>=0 && iY<ny);
    OLB_PRECONDITION(isConstructed());
    return field[iX][iY];
  }
  virtual T const& get(int iX, int iY) const {
    OLB_PRECONDITION(iX>=0 && iX<nx);
    OLB_PRECONDITION(iY>=0 && iY<ny);
    OLB_PRECONDITION(isConstructed());
    return field[iX][iY];
  }
  T& operator[] (int ind) {
    OLB_PRECONDITION(ind>=0 && ind<nx*ny);
    OLB_PRECONDITION(isConstructed());
    return rawData[ind];
  }
  T const& operator[] (int ind) const {
    OLB_PRECONDITION(ind>=0 && ind<nx*ny);
    OLB_PRECONDITION(isConstructed());
    return rawData[ind];
  }
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
private:
  void allocateMemory();
  void releaseMemory();
private:
  int nx;
  int ny;
  T   *rawData;
  T   **field;
  mutable SequentialScalarFieldSerializer2D<T>* serializer;
  mutable SequentialScalarFieldUnSerializer2D<T>* unSerializer;
};


template<typename T, int nDim> class SequentialTensorFieldSerializer2D;
template<typename T, int nDim> class SequentialTensorFieldUnSerializer2D;

template<typename T, int nDim>
class TensorField2D : public TensorFieldBase2D<T,nDim> {
public:
  typedef T Tensor[nDim];
public:
  TensorField2D(int nx_, int ny_);
  ~TensorField2D();
  TensorField2D(TensorField2D<T,nDim> const& rhs);
  TensorField2D<T,nDim>& operator=(TensorField2D<T,nDim> const& rhs);
  void swap(TensorField2D<T,nDim>& rhs);
public:
  virtual bool isConstructed() const;
  virtual void construct();
  virtual void deConstruct();
  virtual void reset();
  virtual int getNx() const { return nx; }
  virtual int getNy() const { return ny; }
  virtual Tensor& get(int iX, int iY) {
    OLB_PRECONDITION(iX>=0 && iX<nx);
    OLB_PRECONDITION(iY>=0 && iY<ny);
    OLB_PRECONDITION(isConstructed());
    return field[iX][iY];
  }
  virtual Tensor const& get(int iX, int iY) const {
    OLB_PRECONDITION(iX>=0 && iX<nx);
    OLB_PRECONDITION(iY>=0 && iY<ny);
    OLB_PRECONDITION(isConstructed());
    return field[iX][iY];
  }
  Tensor& operator[] (int ind) {
    OLB_PRECONDITION(ind>=0 && ind<nx*ny);
    OLB_PRECONDITION(isConstructed());
    return rawData[ind];
  }
  Tensor const& operator[] (int ind) const {
    OLB_PRECONDITION(ind>=0 && ind<nx*ny);
    OLB_PRECONDITION(isConstructed());
    return rawData[ind];
  }
  virtual ScalarField2D<T> const& extractComponent(int whichDim) const;
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
private:
  void allocateMemory();
  void releaseMemory();
private:
  int nx;
  int ny;
  Tensor *rawData;
  Tensor **field;
  mutable ScalarField2D<T> *components[nDim];
  mutable SequentialTensorFieldSerializer2D<T,nDim>* serializer;
  mutable SequentialTensorFieldUnSerializer2D<T,nDim>* unSerializer;
};



template<typename T>
class SequentialScalarFieldSerializer2D : public DataSerializer<T> {
public:
  SequentialScalarFieldSerializer2D(ScalarField2D<T> const& scalarField_,
                                    IndexOrdering::OrderingT ordering_);
  SequentialScalarFieldSerializer2D(ScalarField2D<T> const& scalarField_,
                                    int x0_, int x1_, int y0_, int y1_,
                                    IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual const T* getNextDataBuffer(size_t& bufferSize) const;
  virtual bool isEmpty() const;
private:
  ScalarField2D<T> const& scalarField;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1;
  mutable std::vector<T> buffer;
  mutable int iX, iY;
};

template<typename T>
class SequentialScalarFieldUnSerializer2D : public DataUnSerializer<T> {
public:
  SequentialScalarFieldUnSerializer2D(ScalarField2D<T>& scalarField_,
                                      IndexOrdering::OrderingT ordering_);
  SequentialScalarFieldUnSerializer2D(ScalarField2D<T>& scalarField_,
                                      int x0_, int x1_, int y0_, int y1_,
                                      IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual T* getNextDataBuffer(size_t& bufferSize);
  virtual void commitData();
  virtual bool isFull() const;
private:
  ScalarField2D<T>& scalarField;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1;
  mutable std::vector<T> buffer;
  mutable int iX, iY;
};

template<typename T, int nDim>
class SequentialTensorFieldSerializer2D : public DataSerializer<T> {
public:
  SequentialTensorFieldSerializer2D(TensorField2D<T,nDim> const& tensorField_,
                                    IndexOrdering::OrderingT ordering_);
  SequentialTensorFieldSerializer2D(TensorField2D<T,nDim> const& tensorField_,
                                    int x0_, int x1_, int y0_, int y1_,
                                    IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual const T* getNextDataBuffer(size_t& bufferSize) const;
  virtual bool isEmpty() const;
private:
  TensorField2D<T,nDim> const& tensorField;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1;
  mutable std::vector<T> buffer;
  mutable int iX, iY;
};

template<typename T, int nDim>
class SequentialTensorFieldUnSerializer2D : public DataUnSerializer<T> {
public:
  SequentialTensorFieldUnSerializer2D(TensorField2D<T,nDim>& tensorField_,
                                      IndexOrdering::OrderingT ordering_);
  SequentialTensorFieldUnSerializer2D(TensorField2D<T,nDim>& tensorField_,
                                      int x0_, int x1_, int y0_, int y1_,
                                      IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual T* getNextDataBuffer(size_t& bufferSize);
  virtual void commitData();
  virtual bool isFull() const;
private:
  TensorField2D<T,nDim>& tensorField;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1;
  mutable std::vector<T> buffer;
  mutable int iX, iY;
};

}


#endif
