/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Bernd Stahl and Jonas Latt
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
 * Base class for scalar, vector and tensor fields for 2D data analysis -- header file.
 */

#ifndef DATA_FIELD_BASE_2D_H
#define DATA_FIELD_BASE_2D_H

#include "serializer.h"
#include "dataReductions.h"
#include "spatiallyExtendedObject2D.h"

namespace olb {

/// Interface for the variants of 2D scalar, vector and tensor fields.
template<typename T>
class ScalarFieldBase2D : public Serializable<T>, public SpatiallyExtendedObject2D {
public:
  virtual ~ScalarFieldBase2D() { }
public:
  virtual bool isConstructed() const =0;
  virtual void construct() =0;
  virtual void deConstruct() =0;
  virtual void reset() =0;
  virtual int getNx() const =0;
  virtual int getNy() const =0;
  virtual size_t getSize() const =0;
  virtual T& get(int iX, int iY) =0;
  virtual T const& get(int iX, int iY) const =0;
  virtual T computeReduction(DataReduction<T>& reduction) const =0;
  virtual DataSerializer<T> const& getSubSerializer (
    int x0_, int x1_, int y0_, int y1_,
    IndexOrdering::OrderingT ordering ) const =0;
  virtual DataUnSerializer<T>& getSubUnSerializer (
    int x0_, int x1_, int y0_, int y1_,
    IndexOrdering::OrderingT ordering ) =0;
};

template<typename T, int nDim>
class TensorFieldBase2D : public Serializable<T>, public SpatiallyExtendedObject2D {
public:
  typedef T Tensor[nDim];
public:
  virtual ~TensorFieldBase2D() { }
public:
  virtual bool isConstructed() const =0;
  virtual void construct() =0;
  virtual void deConstruct() =0;
  virtual void reset() =0;
  virtual int getNx() const =0;
  virtual int getNy() const =0;
  virtual Tensor& get(int iX, int iY) =0;
  virtual Tensor const& get(int iX, int iY) const =0;
  virtual ScalarFieldBase2D<T> const& extractComponent(int whichDim) const =0;
  virtual DataSerializer<T> const& getSubSerializer (
    int x0_, int x1_, int y0_, int y1_,
    IndexOrdering::OrderingT ordering ) const =0;
  virtual DataUnSerializer<T>& getSubUnSerializer (
    int x0_, int x1_, int y0_, int y1_,
    IndexOrdering::OrderingT ordering ) =0;
};

} // end namespace olb

#endif
