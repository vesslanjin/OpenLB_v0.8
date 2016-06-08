/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007, 2008 Jonas Latt
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
 * Handler for 2D multi data field structure -- header file.
 */

#ifndef MULTI_DATA_FIELD_HANDLER_2D_H
#define MULTI_DATA_FIELD_HANDLER_2D_H

#include <vector>
#include "complexGrids/multiBlockStructure/multiDataGeometry2D.h"

namespace olb {

template<typename T>
struct MultiDataFieldHandler2D {
  virtual ~MultiDataFieldHandler2D() { }
  virtual int getNx() const =0;
  virtual int getNy() const =0;
  virtual MultiDataDistribution2D const& getMultiDataDistribution() const =0;
  virtual bool getLocalEnvelope(int iBlock, int& lx, int& ly) const =0;
  virtual T reduceSum(T localSum) const =0;
  virtual T reduceAverage(T localAverage, T localWeight) const =0;
  virtual T reduceMin(T localMin) const =0;
  virtual T reduceMax(T localMax) const =0;
  virtual void broadCastScalar(T& scalar, int fromBlock) const =0;
  virtual void broadCastVector(T* vect, int size, int fromBlock) const =0;
};

template<typename T>
class SerialMultiDataFieldHandler2D : public MultiDataFieldHandler2D<T> {
public:
  SerialMultiDataFieldHandler2D(MultiDataDistribution2D const& dataDistribution_);
  virtual int getNx() const;
  virtual int getNy() const;
  virtual MultiDataDistribution2D const& getMultiDataDistribution() const;
  virtual bool getLocalEnvelope(int iBlock, int& lx, int& ly) const;
  virtual T reduceSum(T localSum) const;
  virtual T reduceAverage(T localAverage, T localWeight) const;
  virtual T reduceMin(T localMin) const;
  virtual T reduceMax(T localMax) const;
  virtual void broadCastScalar(T& scalar, int fromBlock) const;
  virtual void broadCastVector(T* vect, int size, int fromBlock) const;
private:
  MultiDataDistribution2D dataDistribution;
};


#ifdef PARALLEL_MODE_MPI
template<typename T>
class ParallelMultiDataFieldHandler2D : public MultiDataFieldHandler2D<T> {
public:
  ParallelMultiDataFieldHandler2D(MultiDataDistribution2D const& dataDistribution_);
  virtual int getNx() const;
  virtual int getNy() const;
  virtual MultiDataDistribution2D const& getMultiDataDistribution() const;
  virtual bool getLocalEnvelope(int iBlock, int& lx, int& ly) const;
  virtual T reduceSum(T localSum) const;
  virtual T reduceAverage(T localAverage, T localWeight) const;
  virtual T reduceMin(T localMin) const;
  virtual T reduceMax(T localMax) const;
  virtual void broadCastScalar(T& scalar, int fromBlock) const;
  virtual void broadCastVector(T* vect, int size, int fromBlock) const;
private:
  MultiDataDistribution2D dataDistribution;
};
#endif

}  // namespace olb

#endif
