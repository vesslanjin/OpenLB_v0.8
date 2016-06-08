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

/** \file
 * A collection of dynamics classes (e.g. BGK) with which a Cell object
 * can be instantiated -- generic implementation.
 */
#ifndef ADVECTION_DIFFUSION_DYNAMICS_HH
#define ADVECTION_DIFFUSION_DYNAMICS_HH

#include <algorithm>
#include <limits>
#include "advectionDiffusionDynamics.h"
#include "advectionDiffusionLbHelpers.h"

namespace olb {


////////////////////// Class AdvectionDiffusionRLBdynamics //////////////////////////

/** \param omega_ relaxation parameter, related to the dynamic viscosity
 *  \param momenta_ a Momenta object to know how to compute velocity momenta
 */
//==================================================================//
//============= Regularized Model for Advection diffusion===========//
//==================================================================//

template<typename T, template<typename U> class Lattice>
AdvectionDiffusionRLBdynamics<T,Lattice>::AdvectionDiffusionRLBdynamics (
  T omega_, Momenta<T,Lattice>& momenta_)
  : BasicDynamics<T,Lattice>(momenta_),
    omega(omega_)
{ }

template<typename T, template<typename U> class Lattice>
AdvectionDiffusionRLBdynamics<T,Lattice>* AdvectionDiffusionRLBdynamics<T,Lattice>::clone() const {
  return new AdvectionDiffusionRLBdynamics<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
T AdvectionDiffusionRLBdynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return advectionDiffusionLbHelpers<T,Lattice>::equilibrium(iPop, rho, u);
}


template<typename T, template<typename U> class Lattice>
void AdvectionDiffusionRLBdynamics<T,Lattice>::collide(Cell<T,Lattice>& cell, LatticeStatistics<T>& statistics )
{
  T temperature = this->momenta.computeRho(cell);

  const T* u = cell.getExternal(Lattice<T>::ExternalField::velocityBeginsAt);

  T uSqr = advectionDiffusionLbHelpers<T,Lattice>::
           rlbCollision(cell, temperature, u, omega);

  if (cell.takesStatistics()) {
    statistics.incrementStats(temperature, uSqr);
  }
}


template<typename T, template<typename U> class Lattice>
void AdvectionDiffusionRLBdynamics<T,Lattice>::staticCollide(Cell<T,Lattice>& cell,
    const T u[Lattice<T>::d] ,
    LatticeStatistics<T>& statistics )
{
  assert(false);
}

template<typename T, template<typename U> class Lattice>
T AdvectionDiffusionRLBdynamics<T,Lattice>::getOmega() const {
  return omega;
}

template<typename T, template<typename U> class Lattice>
void AdvectionDiffusionRLBdynamics<T,Lattice>::setOmega(T omega_) {
  omega = omega_;
}

//==================================================================//
//============= BGK Model for Advection diffusion===========//
//==================================================================//

template<typename T, template<typename U> class Lattice>
AdvectionDiffusionBGKdynamics<T,Lattice>::AdvectionDiffusionBGKdynamics (
  T omega_, Momenta<T,Lattice>& momenta_)
  : BasicDynamics<T,Lattice>(momenta_),
    omega(omega_)
{ }

template<typename T, template<typename U> class Lattice>
AdvectionDiffusionBGKdynamics<T,Lattice>* AdvectionDiffusionBGKdynamics<T,Lattice>::clone() const {
  return new AdvectionDiffusionBGKdynamics<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
T AdvectionDiffusionBGKdynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return advectionDiffusionLbHelpers<T,Lattice>::equilibrium(iPop, rho, u);
}


template<typename T, template<typename U> class Lattice>
void AdvectionDiffusionBGKdynamics<T,Lattice>::collide(Cell<T,Lattice>& cell, LatticeStatistics<T>& statistics )
{
  T temperature = this->momenta.computeRho(cell);

  const T* u = cell.getExternal(Lattice<T>::ExternalField::velocityBeginsAt);

  T uSqr = advectionDiffusionLbHelpers<T,Lattice>::
           bgkCollision(cell, temperature, u, omega);

  if (cell.takesStatistics()) {
    statistics.incrementStats(temperature, uSqr);
  }
}


template<typename T, template<typename U> class Lattice>
void AdvectionDiffusionBGKdynamics<T,Lattice>::staticCollide(Cell<T,Lattice>& cell,
    const T u[Lattice<T>::d] ,
    LatticeStatistics<T>& statistics )
{
  assert(false);
}

template<typename T, template<typename U> class Lattice>
T AdvectionDiffusionBGKdynamics<T,Lattice>::getOmega() const {
  return omega;
}

template<typename T, template<typename U> class Lattice>
void AdvectionDiffusionBGKdynamics<T,Lattice>::setOmega(T omega_) {
  omega = omega_;
}


} // namespace olb













#endif
