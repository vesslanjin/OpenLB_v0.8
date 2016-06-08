/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2008 Orestis Malaspinas, Andrea Parmigiani, Jonas Latt
 *  Address: EPFL-STI-LIN Station 9, 1015 Lausanne
 *  E-mail: orestis.malaspinas@epfl.ch
 *
 *  This program is free software you can redistribute it and/or
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

#ifndef NAVIER_STOKES_INTO_ADVECTION_DIFFUSION_COUPLING_POST_PROCESSOR_3D_HH
#define NAVIER_STOKES_INTO_ADVECTION_DIFFUSION_COUPLING_POST_PROCESSOR_3D_HH

#include "core/latticeDescriptors.h"
#include "advectionDiffusionLatticeDescriptors.h"
#include "navierStokesAdvectionDiffusionCouplingPostProcessor3D.h"
#include "core/blockLattice3D.h"
#include "core/util.h"
#include "core/finiteDifference3D.h"

namespace olb {

//=====================================================================================
//==============  NavierStokesAdvectionDiffusionCouplingPostProcessor3D ===========
//=====================================================================================

template<typename T, template<typename U> class Lattice>
NavierStokesAdvectionDiffusionCouplingPostProcessor3D<T,Lattice>::
NavierStokesAdvectionDiffusionCouplingPostProcessor3D(int x0_, int x1_, int y0_, int y1_, int z0_, int z1_,
    T gravity_, T T0_, T deltaTemp_, std::vector<T> dir_,
    std::vector<SpatiallyExtendedObject3D* > partners_)
  :  x0(x0_), x1(x1_), y0(y0_), y1(y1_), z0(z0_), z1(z1_),
     gravity(gravity_), T0(T0_), deltaTemp(deltaTemp_),
     dir(dir_), partners(partners_)
{
  // we normalize the direction of force vector
  T normDir = T();
  for (unsigned iD = 0; iD < dir.size(); ++iD)
  {
    normDir += dir[iD]*dir[iD];
  }
  normDir = sqrt(normDir);
  for (unsigned iD = 0; iD < dir.size(); ++iD)
  {
    dir[iD] /= normDir;
  }
}

template<typename T, template<typename U> class Lattice>
void NavierStokesAdvectionDiffusionCouplingPostProcessor3D<T,Lattice>::
processSubDomain(BlockLattice3D<T,Lattice>& blockLattice,
                 int x0_, int x1_, int y0_, int y1_, int z0_, int z1_)
{
  typedef Lattice<T> L;
  enum {x,y,z};
  enum {
    velOffset = AdvectionDiffusionD3Q7Descriptor<T>::ExternalField::velocityBeginsAt,
    forceOffset = Lattice<T>::ExternalField::forceBeginsAt
  };

  BlockLattice3D<T,AdvectionDiffusionD3Q7Descriptor> *tPartner =
    dynamic_cast<BlockLattice3D<T,AdvectionDiffusionD3Q7Descriptor> *>(partners[0]);

  int newX0, newX1, newY0, newY1, newZ0, newZ1;
  if ( util::intersect (
         x0, x1, y0, y1, z0, z1,
         x0_, x1_, y0_, y1_, z0_, z1_,
         newX0, newX1, newY0, newY1, newZ0, newZ1 ) )
  {

    for (int iX=newX0; iX<=newX1; ++iX)
    {
      for (int iY=newY0; iY<=newY1; ++iY)
      {
        for (int iZ=newZ0; iZ<=newZ1; ++iZ)
        {
//                  Velocity coupling
          T *u = tPartner->get(iX,iY,iZ).getExternal(velOffset);
          blockLattice.get(iX,iY,iZ).computeU(u);

          //coupling between the temperature and navier stokes.

          T *force = blockLattice.get(iX,iY,iZ).getExternal(forceOffset);
          T temperature = tPartner->get(iX,iY,iZ).computeRho();
          T rho = blockLattice.get(iX,iY,iZ).computeRho();
          for (unsigned iD = 0; iD < L::d; ++iD)
          {
            force[iD] = gravity * rho * (temperature - T0) / deltaTemp * dir[iD];
          }
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void NavierStokesAdvectionDiffusionCouplingPostProcessor3D<T,Lattice>::
process(BlockLattice3D<T,Lattice>& blockLattice)
{
  processSubDomain(blockLattice, x0, x1, y0, y1, z0, z1);
}

// LatticeCouplingGenerator for advectionDiffusion coupling

template<typename T, template<typename U> class Lattice>
NavierStokesAdvectionDiffusionCouplingGenerator3D<T,Lattice>::
NavierStokesAdvectionDiffusionCouplingGenerator3D(int x0_, int x1_, int y0_, int y1_,int z0_, int z1_,
    T gravity_, T T0_, T deltaTemp_, std::vector<T> dir_)
  : LatticeCouplingGenerator3D<T,Lattice>(x0_, x1_, y0_, y1_, z0_, z1_),
    gravity(gravity_), T0(T0_), deltaTemp(deltaTemp_), dir(dir_)
{ }

template<typename T, template<typename U> class Lattice>
PostProcessor3D<T,Lattice>* NavierStokesAdvectionDiffusionCouplingGenerator3D<T,Lattice>::generate (
  std::vector<SpatiallyExtendedObject3D* > partners) const
{
  return new NavierStokesAdvectionDiffusionCouplingPostProcessor3D<T,Lattice>(
           this->x0,this->x1,this->y0,this->y1,this->z0,this->z1, gravity, T0, deltaTemp, dir,partners);
}

template<typename T, template<typename U> class Lattice>
LatticeCouplingGenerator3D<T,Lattice>* NavierStokesAdvectionDiffusionCouplingGenerator3D<T,Lattice>::clone() const {
  return new NavierStokesAdvectionDiffusionCouplingGenerator3D<T,Lattice>(*this);
}




}  // namespace olb

#endif
