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
 * Serial implementation of scalar, vector and tensor fields for 3D data analysis.
 * -- header file
 */

#ifndef DATA_FIELDS_3D_H
#define DATA_FIELDS_3D_H

#include "olbDebug.h"
#include "dataFields2D.h"
#include "dataFieldBase2D.h"
#include "dataFieldBase3D.h"

namespace olb {

template<typename T> class SequentialScalarFieldSerializer3D;
template<typename T> class SequentialScalarFieldUnSerializer3D;

template<typename T>
class ScalarField3D : public ScalarFieldBase3D<T> {
public:
  ScalarField3D(int nx_, int ny_, int nz_);
  ~ScalarField3D();
  ScalarField3D(ScalarField3D<T> const& rhs);
  ScalarField3D<T>& operator=(ScalarField3D<T> const& rhs);
  void swap(ScalarField3D<T>& rhs);
public:
  virtual bool isConstructed() const;
  virtual void construct();
  virtual void deConstruct();
  virtual void reset();
  virtual int getNx() const { return nx; }
  virtual int getNy() const { return ny; }
  virtual int getNz() const { return nz; }
  virtual size_t getSize() const { return (size_t)nx*(size_t)ny*(size_t)nz; }
  virtual T& get(int iX, int iY, int iZ) {
    OLB_PRECONDITION(iX>=0 && iX<nx);
    OLB_PRECONDITION(iY>=0 && iY<ny);
    OLB_PRECONDITION(iZ>=0 && iZ<nz);
    OLB_PRECONDITION(isConstructed());
    return field[iX][iY][iZ];
  }
  virtual T const& get(int iX, int iY, int iZ) const {
    OLB_PRECONDITION(iX>=0 && iX<nx);
    OLB_PRECONDITION(iY>=0 && iY<ny);
    OLB_PRECONDITION(iZ>=0 && iZ<nz);
    OLB_PRECONDITION(isConstructed());
    return field[iX][iY][iZ];
  }
  T& operator[] (int ind) {
    OLB_PRECONDITION(ind>=0 && ind<nx*ny*nz);
    OLB_PRECONDITION(isConstructed());
    return rawData[ind];
  }
  T const& operator[] (int ind) const {
    OLB_PRECONDITION(ind>=0 && ind<nx*ny*nz);
    OLB_PRECONDITION(isConstructed());
    return rawData[ind];
  }
  virtual ScalarField2D<T> const& sliceX(int xVal) const;
  virtual ScalarField2D<T> const& sliceY(int yVal) const;
  virtual ScalarField2D<T> const& sliceZ(int zVal) const;
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
private:
  void allocateMemory();
  void releaseMemory();
private:
  int nx;
  int ny;
  int nz;
  T   *rawData;
  T   ***field;
  mutable ScalarField2D<T> xSlice;
  mutable ScalarField2D<T> ySlice;
  mutable ScalarField2D<T> zSlice;
  mutable SequentialScalarFieldSerializer3D<T>* serializer;
  mutable SequentialScalarFieldUnSerializer3D<T>* unSerializer;
};


template<typename T, int nDim> class SequentialTensorFieldSerializer3D;
template<typename T, int nDim> class SequentialTensorFieldUnSerializer3D;

template<typename T, int nDim>
class TensorField3D : public TensorFieldBase3D<T,nDim> {
public:
  typedef T Tensor[nDim];
public:
  TensorField3D(int nx_, int ny_, int nz_);
  ~TensorField3D();
  TensorField3D(TensorField3D<T,nDim> const& rhs);
  TensorField3D<T,nDim>& operator=(TensorField3D<T,nDim> const& rhs);
  void swap(TensorField3D<T,nDim>& rhs);
public:
  virtual bool isConstructed() const;
  virtual void construct();
  virtual void deConstruct();
  virtual void reset();
  virtual int getNx() const { return nx; }
  virtual int getNy() const { return ny; }
  virtual int getNz() const { return nz; }
  virtual Tensor& get(int iX, int iY, int iZ) {
    OLB_PRECONDITION(iX>=0 && iX<nx);
    OLB_PRECONDITION(iY>=0 && iY<ny);
    OLB_PRECONDITION(iZ>=0 && iZ<nz);
    OLB_PRECONDITION(isConstructed());
    return field[iX][iY][iZ];
  }
  virtual Tensor const& get(int iX, int iY, int iZ) const {
    OLB_PRECONDITION(iX>=0 && iX<nx);
    OLB_PRECONDITION(iY>=0 && iY<ny);
    OLB_PRECONDITION(iZ>=0 && iZ<nz);
    OLB_PRECONDITION(isConstructed());
    return field[iX][iY][iZ];
  }
  virtual Tensor& operator[] (int ind) {
    OLB_PRECONDITION(ind>=0 && ind<nx*ny*nz);
    OLB_PRECONDITION(isConstructed());
    return rawData[ind];
  }
  virtual Tensor const& operator[] (int ind) const {
    OLB_PRECONDITION(ind>=0 && ind<nx*ny*nz);
    OLB_PRECONDITION(isConstructed());
    return rawData[ind];
  }
  virtual TensorField2D<T,nDim> const& sliceX(int xVal) const;
  virtual TensorField2D<T,nDim> const& sliceY(int yVal) const;
  virtual TensorField2D<T,nDim> const& sliceZ(int zVal) const;
  virtual ScalarField3D<T> const& extractComponent(int iDim) const;
  virtual DataSerializer<T> const& getSerializer(IndexOrdering::OrderingT ordering) const;
  virtual DataUnSerializer<T>& getUnSerializer(IndexOrdering::OrderingT ordering);
  virtual DataSerializer<T> const& getSubSerializer (
    int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
    IndexOrdering::OrderingT ordering ) const;
  virtual DataUnSerializer<T>& getSubUnSerializer (
    int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
    IndexOrdering::OrderingT ordering );
//     virtual T computeReduction(DataReduction<T>& reduction) const;
  virtual MultiDataDistribution3D getDataDistribution() const;
  virtual SpatiallyExtendedObject3D* getComponent(int iBlock);
  virtual SpatiallyExtendedObject3D const* getComponent(int iBlock) const;
  virtual multiPhysics::MultiPhysicsId getMultiPhysicsId() const;
private:
  void allocateMemory();
  void releaseMemory();
private:
  int nx;
  int ny;
  int nz;
  Tensor *rawData;
  Tensor ***field;
  mutable TensorField2D<T,nDim> xSlice;
  mutable TensorField2D<T,nDim> ySlice;
  mutable TensorField2D<T,nDim> zSlice;
  mutable ScalarField3D<T> *components[nDim];

  mutable SequentialTensorFieldSerializer3D<T,nDim>* serializer;
  mutable SequentialTensorFieldUnSerializer3D<T,nDim>* unSerializer;
};

template<typename T>
class SequentialScalarFieldSerializer3D : public DataSerializer<T> {
public:
  SequentialScalarFieldSerializer3D(ScalarField3D<T> const& scalarField_,
                                    IndexOrdering::OrderingT ordering_);
  SequentialScalarFieldSerializer3D(ScalarField3D<T> const& scalarField_,
                                    int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
                                    IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual const T* getNextDataBuffer(size_t& bufferSize) const;
  virtual bool isEmpty() const;
private:
  ScalarField3D<T> const& scalarField;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1, z0, z1;
  mutable std::vector<T> buffer;
  mutable int iX, iY, iZ;
};

template<typename T>
class SequentialScalarFieldUnSerializer3D : public DataUnSerializer<T> {
public:
  SequentialScalarFieldUnSerializer3D(ScalarField3D<T>& scalarField_,
                                      IndexOrdering::OrderingT ordering_);
  SequentialScalarFieldUnSerializer3D(ScalarField3D<T>& scalarField_,
                                      int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
                                      IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual T* getNextDataBuffer(size_t& bufferSize);
  virtual void commitData();
  virtual bool isFull() const;
private:
  ScalarField3D<T>& scalarField;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1, z0, z1;
  mutable std::vector<T> buffer;
  mutable int iX, iY, iZ;
};

template<typename T, int nDim>
class SequentialTensorFieldSerializer3D : public DataSerializer<T> {
public:
  SequentialTensorFieldSerializer3D(TensorField3D<T,nDim> const& tensorField_,
                                    IndexOrdering::OrderingT ordering_);
  SequentialTensorFieldSerializer3D(TensorField3D<T,nDim> const& tensorField_,
                                    int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
                                    IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual const T* getNextDataBuffer(size_t& bufferSize) const;
  virtual bool isEmpty() const;
private:
  TensorField3D<T,nDim> const& tensorField;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1, z0, z1;
  mutable std::vector<T> buffer;
  mutable int iX, iY, iZ;
};

template<typename T, int nDim>
class SequentialTensorFieldUnSerializer3D : public DataUnSerializer<T> {
public:
  SequentialTensorFieldUnSerializer3D(TensorField3D<T,nDim>& tensorField_,
                                      IndexOrdering::OrderingT ordering_);
  SequentialTensorFieldUnSerializer3D(TensorField3D<T,nDim>& tensorField_,
                                      int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
                                      IndexOrdering::OrderingT ordering_);
  virtual size_t getSize() const;
  virtual T* getNextDataBuffer(size_t& bufferSize);
  virtual void commitData();
  virtual bool isFull() const;
private:
  TensorField3D<T,nDim>& tensorField;
  IndexOrdering::OrderingT ordering;
  int x0, x1, y0, y1, z0, z1;
  mutable std::vector<T> buffer;
  mutable int iX, iY, iZ;
};

}  // namespace olb


#endif
