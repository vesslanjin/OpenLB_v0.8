/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Jonas Latt
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

#ifndef BOUNDARY_CONDITION_2D_H
#define BOUNDARY_CONDITION_2D_H

#include "blockStructure2D.h"
#include "momentaOnBoundaries2D.h"
#include "boundaryPostProcessors2D.h"
#include "dynamics.h"
#include "blockGeometryStatistics2D.h"
namespace olb {

template<typename T, template<typename U> class Lattice>
class OnLatticeBoundaryCondition2D {
public:
  virtual ~OnLatticeBoundaryCondition2D() { }

  virtual void addVelocityBoundary0N(int x0, int x1, int y0, int y1, T omega) =0;
  virtual void addVelocityBoundary0P(int x0, int x1, int y0, int y1, T omega) =0;
  virtual void addVelocityBoundary1N(int x0, int x1, int y0, int y1, T omega) =0;
  virtual void addVelocityBoundary1P(int x0, int x1, int y0, int y1, T omega) =0;

  virtual void addPressureBoundary0N(int x0, int x1, int y0, int y1, T omega) =0;
  virtual void addPressureBoundary0P(int x0, int x1, int y0, int y1, T omega) =0;
  virtual void addPressureBoundary1N(int x0, int x1, int y0, int y1, T omega) =0;
  virtual void addPressureBoundary1P(int x0, int x1, int y0, int y1, T omega) =0;

  virtual void addExternalVelocityCornerNN(int x, int y, T omega) =0;
  virtual void addExternalVelocityCornerNP(int x, int y, T omega) =0;
  virtual void addExternalVelocityCornerPN(int x, int y, T omega) =0;
  virtual void addExternalVelocityCornerPP(int x, int y, T omega) =0;

  virtual void addInternalVelocityCornerNN(int x, int y, T omega) =0;
  virtual void addInternalVelocityCornerNP(int x, int y, T omega) =0;
  virtual void addInternalVelocityCornerPN(int x, int y, T omega) =0;
  virtual void addInternalVelocityCornerPP(int x, int y, T omega) =0;

  /// adds a pressure or velocity boundary for one material and a range (x0-x1, y0-y1, z0-z1) or the whole geometry
  virtual void addVelocityBoundary(BlockGeometryStatistics2D* blockGeoSta, int x0, int x1, int y0, int y1, T omega, int material) =0;
  virtual void addVelocityBoundary(BlockGeometryStatistics2D* blockGeoSta, T omega, int material) =0;
  virtual void addPressureBoundary(BlockGeometryStatistics2D* blockGeoSta, int x0, int x1, int y0, int y1, T omega, int material) =0;
  virtual void addPressureBoundary(BlockGeometryStatistics2D* blockGeoSta, T omega, int material) =0;

  virtual BlockStructure2D<T,Lattice>& getBlock() =0;
  virtual BlockStructure2D<T,Lattice> const& getBlock() const =0;

  virtual void outputOn() =0;
  virtual void outputOff() =0;
};

////////// Factory functions //////////////////////////////////////////////////

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
OnLatticeBoundaryCondition2D<T,Lattice>*
createLocalBoundaryCondition2D(BlockStructure2D<T,Lattice>& block);

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
OnLatticeBoundaryCondition2D<T,Lattice>*
createInterpBoundaryCondition2D(BlockStructure2D<T,Lattice>& block);

template<typename T, template<typename U> class Lattice>
OnLatticeBoundaryCondition2D<T,Lattice>*
createLocalBoundaryCondition2D(BlockStructure2D<T,Lattice>& block) {
  return createLocalBoundaryCondition2D<T,Lattice,RLBdynamics<T,Lattice> >(block);
}

template<typename T, template<typename U> class Lattice>
OnLatticeBoundaryCondition2D<T,Lattice>*
createInterpBoundaryCondition2D(BlockStructure2D<T,Lattice>& block) {
  return createInterpBoundaryCondition2D<T,Lattice,BGKdynamics<T,Lattice> >(block);
}

}

#endif
