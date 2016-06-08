/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2008 Orestis Malaspinas, Andrea Parmigiani
 *  Address: EPFL-STI-LIN Station 9, 1015 Lausanne
 *  E-mail: orestis.malaspinas@epfl.ch
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
#ifndef ADVECTION_DIFFUSION_BOUNDARY_CONDITION_2D_H
#define ADVECTION_DIFFUSION_BOUNDARY_CONDITION_2D_H

#include "core/momentaOnBoundaries2D.h"
// #include "core/dynamics.h"
#include "advectionDiffusionDynamics.h"

#include <vector>
#include <list>

namespace olb {

template<typename T, template<typename U> class Lattice>
class OnLatticeAdvectionDiffusionBoundaryCondition2D {
public:
  virtual ~OnLatticeAdvectionDiffusionBoundaryCondition2D() { }

  virtual void addTemperatureBoundary0N(int x0, int x1, int y0, int y1,T omega) =0;
  virtual void addTemperatureBoundary0P(int x0, int x1, int y0, int y1,T omega) =0;
  virtual void addTemperatureBoundary1N(int x0, int x1, int y0, int y1,T omega) =0;
  virtual void addTemperatureBoundary1P(int x0, int x1, int y0, int y1,T omega) =0;

  virtual void addTemperatureCornerNN(int x, int y, T omega) =0;
  virtual void addTemperatureCornerNP(int x, int y, T omega) =0;
  virtual void addTemperatureCornerPN(int x, int y, T omega) =0;
  virtual void addTemperatureCornerPP(int x, int y, T omega) =0;

  BlockStructure2D<T,Lattice>& getBlock();
  BlockStructure2D<T,Lattice> const& getBlock() const;
};

//////  Factory function for Regularized Thermal BC

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
OnLatticeAdvectionDiffusionBoundaryCondition2D<T,Lattice>*
createAdvectionDiffusionBoundaryCondition2D(BlockStructure2D<T,Lattice>& block);

template<typename T, template<typename U> class Lattice>
OnLatticeAdvectionDiffusionBoundaryCondition2D<T,Lattice>*
createAdvectionDiffusionBoundaryCondition2D(BlockStructure2D<T,Lattice>& block)
{
  return createAdvectionDiffusionBoundaryCondition2D<T,Lattice,
         AdvectionDiffusionRLBdynamics<T,Lattice> >(block);
}


} //namespace olb


#endif
