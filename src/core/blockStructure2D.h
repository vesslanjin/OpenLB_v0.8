/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006-2008 Jonas Latt
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
 * Dynamics for a generic 2D block structure -- header file.
 */
#ifndef BLOCK_STRUCTURE_2D_H
#define BLOCK_STRUCTURE_2D_H

#include <vector>
#include "postProcessing.h"
#include "dataFields2D.h"
#include "serializer.h"
#include "dataAnalysisBase2D.h"
#include "spatiallyExtendedObject2D.h"
#include "blockGeometryStatistics2D.h"
#include "latticeStatistics.h"


namespace olb {

template<typename T, template<typename U> class Lattice> struct Dynamics;
template<typename T, template<typename U> class Lattice> class Cell;
template<typename T, template<typename U> class Lattice> struct WriteCellFunctional;

/// An interface to all the variants of (more or less) regular lattices.
template<typename T, template<typename U> class Lattice>
class BlockStructure2D : public Serializable<T>, public SpatiallyExtendedObject2D {
public:
  virtual ~BlockStructure2D() { }
public:
  virtual int getNx() const =0;
  virtual int getNy() const =0;
  virtual Cell<T,Lattice>& get(int iX, int iY) =0;
  virtual Cell<T,Lattice> const& get(int iX, int iY) const =0;
  virtual void initialize() =0;
  virtual void defineDynamics (
    int x0_, int x1_, int y0_, int y1_,
    Dynamics<T,Lattice>* dynamics ) =0;
  virtual void defineDynamics(int iX, int iY, Dynamics<T,Lattice>* dynamics ) =0;
  virtual void defineDynamics(BlockGeometryStatistics2D* blockGeoSta,
                              Dynamics<T,Lattice>* dynamics, int material)=0;
  virtual void defineDynamics(BlockGeometryStatistics2D* blockGeoSta,
                              int x0_, int x1_, int y0_, int y1_,
                              Dynamics<T,Lattice>* dynamics, int material)=0;
  virtual void specifyStatisticsStatus (
    int x0_, int x1_, int y0_, int y1_, bool status ) =0;
  virtual void collide(int x0_, int x1_, int y0_, int y1_) =0;
  virtual void collide() =0;
  virtual void staticCollide (int x0, int x1, int y0, int y1,
                              TensorFieldBase2D<T,2> const& u) =0;
  virtual void staticCollide (TensorFieldBase2D<T,2> const& u) =0;
  virtual void stream(int x0_, int x1_, int y0_, int y1_) =0;
  virtual void stream(bool periodic=false) =0;
  virtual void collideAndStream(int x0_, int x1_, int y0_, int y1_) =0;
  virtual void collideAndStream(bool periodic=false) =0;
  virtual T computeAverageDensity( int x0_, int x1_, int y0_, int y1_) const =0;
  virtual T computeAverageDensity() const =0;
  virtual void stripeOffDensityOffset (
    int x0_, int x1_, int y0_, int y1_, T offset ) =0;
  virtual void stripeOffDensityOffset(T offset) =0;
  virtual void forAll(int x0_, int x1_, int y0_, int y1_,
                      WriteCellFunctional<T,Lattice> const& application) =0;
  virtual void forAll(WriteCellFunctional<T,Lattice> const& application) =0;
  virtual void addPostProcessor (
    PostProcessorGenerator2D<T,Lattice> const& ppGen) =0;
  virtual void resetPostProcessors() =0;
  virtual void postProcess(int x0_, int x1_, int y0_, int y1_) =0;
  virtual void postProcess() =0;
  virtual void addLatticeCoupling (
    LatticeCouplingGenerator2D<T,Lattice> const& lcGen,
    std::vector<SpatiallyExtendedObject2D*> partners ) =0;
  virtual void executeCoupling(int x0_, int x1_, int y0_, int y1_) =0;
  virtual void executeCoupling() =0;
  virtual void subscribeReductions(Reductor<T>& reductor) =0;
  virtual LatticeStatistics<T>& getStatistics() =0;
  virtual LatticeStatistics<T> const& getStatistics() const =0;
  virtual DataAnalysisBase2D<T,Lattice> const& getDataAnalysis() const =0;
  virtual DataSerializer<T> const& getSubSerializer (
    int x0_, int x1_, int y0_, int y1_,
    IndexOrdering::OrderingT ordering ) const =0;
  virtual DataUnSerializer<T>& getSubUnSerializer (
    int x0_, int x1_, int y0_, int y1_,
    IndexOrdering::OrderingT ordering) =0;
};

}  // namespace olb

#endif
