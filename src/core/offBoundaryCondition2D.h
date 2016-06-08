/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Jonas Kratzke, Mathias J. Krause
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

/** \file A helper for initialising 2D boundaries -- header file.  */

#ifndef OFF_BOUNDARY_CONDITION_2D_H
#define OFF_BOUNDARY_CONDITION_2D_H

#include "blockStructure2D.h"
#include "offBoundaryPostProcessors2D.h"
#include "dynamics.h"
#include "blockGeometryStatistics2D.h"
namespace olb {

/**
* This class provides a general off lattice boundary condition
*/

template<typename T, template<typename U> class Lattice>
class OffLatticeBoundaryCondition2D {
public:
  virtual ~OffLatticeBoundaryCondition2D() { }

  virtual void addOnePointFixedBoundary(int x, int y, int dir, T dist) =0;
  virtual void addTwoPointFixedBoundary(int x, int y, int dir, T dist) =0;
  virtual void addThreePointFixedBoundary(int x, int y, int dir, T dist) =0;

  virtual void addOnePointVelocityBoundary(int x, int y, int dir, T dist, T uX, T uY) =0;
  virtual void addTwoPointVelocityBoundary(int x, int y, int dir, T dist, T uX, T uY) =0;
  virtual void addThreePointVelocityBoundary(int x, int y, int dir, T dist, T uX, T uY) =0;

  virtual void addFixedBoundary(BlockGeometryStatistics2D* blockGeoSta, int x, int y, int dir, T dist) =0;
  virtual void addVelocityBoundary(BlockGeometryStatistics2D* blockGeoSta, int x, int y, int dir, T dist, T uX, T uY) =0;

  virtual BlockStructure2D<T,Lattice>& getBlock() =0;
  virtual BlockStructure2D<T,Lattice> const& getBlock() const =0;

  virtual void outputOn() =0;
  virtual void outputOff() =0;
};

////////// Factory functions //////////////////////////////////////////////////

/**
* Create specific off lattice boundary conditions
*/

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
OffLatticeBoundaryCondition2D<T,Lattice>*
createBouzidiBoundaryCondition2D(BlockStructure2D<T,Lattice>& block);

template<typename T, template<typename U> class Lattice>
OffLatticeBoundaryCondition2D<T,Lattice>*
createBouzidiBoundaryCondition2D(BlockStructure2D<T,Lattice>& block) {
  return createBouzidiBoundaryCondition2D<T,Lattice,BGKdynamics<T,Lattice> >(block);
}

}

#endif
