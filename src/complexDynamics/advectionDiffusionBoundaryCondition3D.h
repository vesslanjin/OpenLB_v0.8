/*
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

/** \file A helper for initialising 3D boundaries -- header file.  */
#ifndef ADVECTION_DIFFUSION_BOUNDARY_CONDITION_3D_H
#define ADVECTION_DIFFUSION_BOUNDARY_CONDITION_3D_H

#include "core/momentaOnBoundaries3D.h"
#include "core/dynamics.h"
#include "advectionDiffusionDynamics.h"

#include <vector>
#include <list>

namespace olb {

template<typename T, template<typename U> class Lattice>
class OnLatticeAdvectionDiffusionBoundaryCondition3D {
public:
  virtual ~OnLatticeAdvectionDiffusionBoundaryCondition3D() { }

  // 3D boundary condition for temperature:
  virtual void addTemperatureBoundary0N(int x0, int x1,int y0, int y1,int z0, int z1,T omega) =0;
  virtual void addTemperatureBoundary0P(int x0, int x1,int y0, int y1,int z0, int z1,T omega) =0;
  virtual void addTemperatureBoundary1N(int x0, int x1,int y0, int y1,int z0, int z1,T omega) =0;
  virtual void addTemperatureBoundary1P(int x0, int x1,int y0, int y1,int z0, int z1,T omega) =0;
  virtual void addTemperatureBoundary2N(int x0, int x1,int y0, int y1,int z0, int z1,T omega) =0;
  virtual void addTemperatureBoundary2P(int x0, int x1,int y0, int y1,int z0, int z1,T omega) =0;

  virtual void addTemperatureBoundaryEdge0NN(int x0, int x1, int y0, int y1, int z0, int z1, T omega) =0;
  virtual void addTemperatureBoundaryEdge0NP(int x0, int x1, int y0, int y1, int z0, int z1, T omega) =0;
  virtual void addTemperatureBoundaryEdge0PN(int x0, int x1, int y0, int y1, int z0, int z1, T omega) =0;
  virtual void addTemperatureBoundaryEdge0PP(int x0, int x1, int y0, int y1, int z0, int z1, T omega) =0;
  virtual void addTemperatureBoundaryEdge1NN(int x0, int x1, int y0, int y1, int z0, int z1, T omega) =0;
  virtual void addTemperatureBoundaryEdge1NP(int x0, int x1, int y0, int y1, int z0, int z1, T omega) =0;
  virtual void addTemperatureBoundaryEdge1PN(int x0, int x1, int y0, int y1, int z0, int z1, T omega) =0;
  virtual void addTemperatureBoundaryEdge1PP(int x0, int x1, int y0, int y1, int z0, int z1, T omega) =0;
  virtual void addTemperatureBoundaryEdge2NN(int x0, int x1, int y0, int y1, int z0, int z1, T omega) =0;
  virtual void addTemperatureBoundaryEdge2NP(int x0, int x1, int y0, int y1, int z0, int z1, T omega) =0;
  virtual void addTemperatureBoundaryEdge2PN(int x0, int x1, int y0, int y1, int z0, int z1, T omega) =0;
  virtual void addTemperatureBoundaryEdge2PP(int x0, int x1, int y0, int y1, int z0, int z1, T omega) =0;

  virtual void addTemperatureBoundaryCornerNNN(int x, int y, int z, T omega) =0;
  virtual void addTemperatureBoundaryCornerNNP(int x, int y, int z, T omega) =0;
  virtual void addTemperatureBoundaryCornerNPN(int x, int y, int z, T omega) =0;
  virtual void addTemperatureBoundaryCornerNPP(int x, int y, int z, T omega) =0;
  virtual void addTemperatureBoundaryCornerPNN(int x, int y, int z, T omega) =0;
  virtual void addTemperatureBoundaryCornerPNP(int x, int y, int z, T omega) =0;
  virtual void addTemperatureBoundaryCornerPPN(int x, int y, int z, T omega) =0;
  virtual void addTemperatureBoundaryCornerPPP(int x, int y, int z, T omega) =0;


  BlockStructure3D<T,Lattice>& getBlock();
  BlockStructure3D<T,Lattice> const& getBlock() const;
};

//////  Factory function for Regularized Thermal BC

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
OnLatticeAdvectionDiffusionBoundaryCondition3D<T,Lattice>*
createAdvectionDiffusionBoundaryCondition3D(
  BlockStructure3D<T,Lattice>& block);

template<typename T, template<typename U> class Lattice>
OnLatticeAdvectionDiffusionBoundaryCondition3D<T,Lattice>*
createAdvectionDiffusionBoundaryCondition3D(
  BlockStructure3D<T,Lattice>& block)
{
  return createAdvectionDiffusionBoundaryCondition3D<T,Lattice,
         AdvectionDiffusionRLBdynamics<T,Lattice> >(block);
}



} //namespace olb


#endif
