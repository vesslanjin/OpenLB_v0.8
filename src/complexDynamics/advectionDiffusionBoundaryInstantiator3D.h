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
#ifndef ADVECTION_DIFFUSION_BOUNDARY_INSTANTIATOR_3D_H
#define ADVECTION_DIFFUSION_BOUNDARY_INSTANTIATOR_3D_H

#include "advectionDiffusionBoundaryCondition3D.h"
#include "advectionDiffusionBoundaryCondition3D.hh"

namespace olb {

template<typename T, template<typename U> class Lattice, class BoundaryManager>
class AdvectionDiffusionBoundaryConditionInstantiator3D : public OnLatticeAdvectionDiffusionBoundaryCondition3D<T,Lattice> {
public:
  AdvectionDiffusionBoundaryConditionInstantiator3D( BlockStructure3D<T,Lattice>& block_ );
  ~AdvectionDiffusionBoundaryConditionInstantiator3D();

  void addTemperatureBoundary0N(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundary0P(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundary1N(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundary1P(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundary2N(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundary2P(int x0, int x1, int y0, int y1, int z0, int z1, T omega);

  // Temperature Boundary Conditions for edges ...
  void addTemperatureBoundaryEdge0NN(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundaryEdge0NP(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundaryEdge0PN(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundaryEdge0PP(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundaryEdge1NN(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundaryEdge1NP(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundaryEdge1PN(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundaryEdge1PP(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundaryEdge2NN(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundaryEdge2NP(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundaryEdge2PN(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  void addTemperatureBoundaryEdge2PP(int x0, int x1, int y0, int y1, int z0, int z1, T omega);

  // Temperature Boundary Conditions for Corners ...
  void addTemperatureBoundaryCornerNNN(int x, int y, int z, T omega);
  void addTemperatureBoundaryCornerNNP(int x, int y, int z, T omega);
  void addTemperatureBoundaryCornerNPN(int x, int y, int z, T omega);
  void addTemperatureBoundaryCornerNPP(int x, int y, int z, T omega);
  void addTemperatureBoundaryCornerPNN(int x, int y, int z, T omega);
  void addTemperatureBoundaryCornerPNP(int x, int y, int z, T omega);
  void addTemperatureBoundaryCornerPPN(int x, int y, int z, T omega);
  void addTemperatureBoundaryCornerPPP(int x, int y, int z, T omega);


  virtual BlockStructure3D<T,Lattice>& getBlock();
  virtual BlockStructure3D<T,Lattice> const& getBlock() const;
private:
  template<int direction, int orientation>
  void addTemperatureBoundary(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  template<int plane, int normal1, int normal2>
  void addTemperatureBoundaryEdge(int x0, int x1, int y0, int y1, int z0, int z1, T omega);
  template<int normalX, int normalY, int normalZ>
  void addTemperatureBoundaryCorner(int x, int y, int z, T omega);

private:
  BlockStructure3D<T,Lattice>& block;
  std::vector<Momenta<T,Lattice>*>  momentaVector;
  std::vector<Dynamics<T,Lattice>*> dynamicsVector;
};

///////// class AdvectionDiffusionBoundaryConditionInstantiator3D ////////////////////////

template<typename T, template<typename U> class Lattice, class BoundaryManager>
AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::AdvectionDiffusionBoundaryConditionInstantiator3D (
  BlockStructure3D<T,Lattice>& block_)
  : block(block_)
{ }

template<typename T, template<typename U> class Lattice, class BoundaryManager>
AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::~AdvectionDiffusionBoundaryConditionInstantiator3D() {
  for (unsigned iDynamics=0; iDynamics<dynamicsVector.size(); ++iDynamics) {
    delete dynamicsVector[iDynamics];
  }
  for (unsigned iMomenta=0; iMomenta<dynamicsVector.size(); ++iMomenta) {
    delete momentaVector[iMomenta];
  }
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
template<int direction, int orientation>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundary(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  OLB_PRECONDITION(x0==x1 || y0==y1 || z0==z1);

  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iZ=z0; iZ<=z1; ++iZ) {
        Momenta<T,Lattice>* momenta
        = BoundaryManager::template getTemperatureBoundaryMomenta<direction,orientation>();
        Dynamics<T,Lattice>* dynamics
        = BoundaryManager::template getTemperatureBoundaryDynamics<direction,orientation>(omega, *momenta);
        this->getBlock().defineDynamics(iX,iX,iY,iY,iZ,iZ, dynamics);
        momentaVector.push_back(momenta);
        dynamicsVector.push_back(dynamics);
      }
    }
  }
  PostProcessorGenerator3D<T,Lattice>* postProcessor
  = BoundaryManager::template getTemperatureBoundaryProcessor<direction,orientation>(x0,x1, y0,y1, z0,z1);
  if (postProcessor) {
    this->getBlock().addPostProcessor(*postProcessor);
  }
}

// ----  Edges -------------
template<typename T, template<typename U> class Lattice, class BoundaryManager>
template<int plane, int normal1, int normal2>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryEdge(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  OLB_PRECONDITION(
    ( x0==x1 && y0==y1 ) ||
    ( x0==x1 && z0==z1 ) ||
    ( y0==y1 && z0==z1 ) );

  for (int iX=x0; iX<=x1; ++iX) {
    for (int iY=y0; iY<=y1; ++iY) {
      for (int iZ=z0; iZ<=z1; ++iZ) {
        Momenta<T,Lattice>* momenta
        = BoundaryManager::template getTemperatureBoundaryEdgeMomenta<plane,normal1,normal2>();
        Dynamics<T,Lattice>* dynamics
        = BoundaryManager::template getTemperatureBoundaryEdgeDynamics<plane,normal1,normal2>(omega, *momenta);
        this->getBlock().defineDynamics(iX,iX,iY,iY,iZ,iZ, dynamics);
        momentaVector.push_back(momenta);
        dynamicsVector.push_back(dynamics);
      }
    }
  }

  PostProcessorGenerator3D<T,Lattice>* postProcessor
  = BoundaryManager::template getTemperatureBoundaryEdgeProcessor<plane,normal1,normal2>(x0,x1, y0,y1, z0,z1);
  if (postProcessor) {
    this->getBlock().addPostProcessor(*postProcessor);
  }
}


// Boundary Conditions for corners ......
template<typename T, template<typename U> class Lattice, class BoundaryManager>
template<int xNormal, int yNormal, int zNormal>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryCorner(int x, int y, int z, T omega)
{
  Momenta<T,Lattice>* momenta
  = BoundaryManager::template getTemperatureBoundaryCornerMomenta<xNormal,yNormal,zNormal>();
  Dynamics<T,Lattice>* dynamics
  = BoundaryManager::template getTemperatureBoundaryCornerDynamics<xNormal,yNormal,zNormal>(omega, *momenta);

  this->getBlock().defineDynamics(x,x,y,y,z,z, dynamics);

  PostProcessorGenerator3D<T,Lattice>* postProcessor
  = BoundaryManager::template getTemperatureBoundaryCornerProcessor<xNormal,yNormal,zNormal>(x, y, z);
  if (postProcessor) {
    this->getBlock().addPostProcessor(*postProcessor);
  }
}

// --------------------------------  Specification for different position---------------
template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundary0N(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundary<0,-1>(x0,x1,y0,y1,z0,z1,  omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundary0P(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundary<0,1>(x0,x1,y0,y1,z0,z1, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundary1N(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundary<1,-1>(x0,x1,y0,y1,z0,z1, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundary1P(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundary<1,1>(x0,x1,y0,y1,z0,z1, omega);
}


template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundary2N(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundary<2,-1>(x0,x1,y0,y1,z0,z1, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundary2P(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundary<2,1>(x0,x1,y0,y1,z0,z1, omega);
}

// Edges ------------------------------------
template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryEdge0NN(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundaryEdge<0,-1,-1>(x0,x1,y0,y1,z0,z1, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryEdge0NP(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundaryEdge<0,-1, 1>(x0,x1,y0,y1,z0,z1, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryEdge0PN(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundaryEdge<0, 1,-1>(x0,x1,y0,y1,z0,z1, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryEdge0PP(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundaryEdge<0, 1, 1>(x0,x1,y0,y1,z0,z1, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryEdge1NN(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundaryEdge<1,-1,-1>(x0,x1,y0,y1,z0,z1, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryEdge1NP(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundaryEdge<1,-1, 1>(x0,x1,y0,y1,z0,z1, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryEdge1PN(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundaryEdge<1, 1,-1>(x0,x1,y0,y1,z0,z1, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryEdge1PP(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundaryEdge<1, 1, 1>(x0,x1,y0,y1,z0,z1, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryEdge2NN(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundaryEdge<2,-1,-1>(x0,x1,y0,y1,z0,z1, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryEdge2NP(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundaryEdge<2,-1, 1>(x0,x1,y0,y1,z0,z1, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryEdge2PN(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundaryEdge<2, 1,-1>(x0,x1,y0,y1,z0,z1, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryEdge2PP(int x0, int x1, int y0, int y1, int z0, int z1, T omega)
{
  addTemperatureBoundaryEdge<2, 1, 1>(x0,x1,y0,y1,z0,z1, omega);
}

// Corners ------------------------------------

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryCornerNNN(int x, int y, int z, T omega)
{
  addTemperatureBoundaryCorner<-1,-1,-1>(x,y,z, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryCornerNNP(int x, int y, int z, T omega)
{
  addTemperatureBoundaryCorner<-1,-1, 1>(x,y,z, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryCornerNPN(int x, int y, int z, T omega)
{
  addTemperatureBoundaryCorner<-1, 1,-1>(x,y,z, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryCornerNPP(int x, int y, int z, T omega)
{
  addTemperatureBoundaryCorner<-1, 1, 1>(x,y,z, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryCornerPNN(int x, int y, int z, T omega)
{
  addTemperatureBoundaryCorner< 1,-1,-1>(x,y,z, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryCornerPNP(int x, int y, int z, T omega)
{
  addTemperatureBoundaryCorner< 1,-1, 1>(x,y,z, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryCornerPPN(int x, int y, int z, T omega)
{
  addTemperatureBoundaryCorner< 1, 1,-1>(x,y,z, omega);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::
addTemperatureBoundaryCornerPPP(int x, int y, int z, T omega)
{
  addTemperatureBoundaryCorner< 1, 1, 1>(x,y,z, omega);
}


//---------------------------------
template<typename T, template<typename U> class Lattice, class BoundaryManager>
BlockStructure3D<T,Lattice>& AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::getBlock()
{
  return block;
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
BlockStructure3D<T,Lattice> const& AdvectionDiffusionBoundaryConditionInstantiator3D<T,Lattice,BoundaryManager>::getBlock() const
{
  return block;
}

}


#endif
