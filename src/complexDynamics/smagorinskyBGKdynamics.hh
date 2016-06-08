/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Mathias J. Krause, Jonas Latt, Patrick Nathen
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
 * BGK Dynamics with adjusted omega -- generic implementation.
 */
#ifndef SMAGORINSKY_BGK_DYNAMICS_HH
#define SMAGORINSKY_BGK_DYNAMICS_HH

#include "smagorinskyBGKdynamics.h"
#include "core/cell.h"
#include "core/util.h"
#include "core/lbHelpers.h"
#include "core/units.h"
#include "core/units.hh"
#include "math.h"

namespace olb {

////////////////////// Class SmagorinskyBGKdynamics //////////////////////////

/** \param vs2_ speed of sound
 *  \param momenta_ a Momenta object to know how to compute velocity momenta
 *  \param momenta_ a Momenta object to know how to compute velocity momenta
 */
template<typename T, template<typename U> class Lattice>
SmagorinskyBGKdynamics<T,Lattice>::SmagorinskyBGKdynamics (
  T omega_, Momenta<T,Lattice>& momenta_, T smagoConst_, T dx_, T dt_ )
  : BGKdynamics<T,Lattice>(omega_,momenta_),
    smagoConst(smagoConst_),
    preFactor(computePreFactor(omega_,smagoConst_, dx_, dt_) )
{ }

template<typename T, template<typename U> class Lattice>
void SmagorinskyBGKdynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho, u[Lattice<T>::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell, rho, u, pi);
  T newOmega = computeOmega(this->getOmega(), preFactor, rho, pi);
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, newOmega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void SmagorinskyBGKdynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  T rho, uTemp[Lattice<T>::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell, rho, uTemp, pi);
  T newOmega = computeOmega(this->getOmega(), preFactor, rho, pi);
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, newOmega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void SmagorinskyBGKdynamics<T,Lattice>::setOmega(T omega) {
  this->setOmega(omega);
  preFactor = computePreFactor(omega, smagoConst, dx, dt);
}

template<typename T, template<typename U> class Lattice>
T SmagorinskyBGKdynamics<T,Lattice>::getSmagorinskyOmega(Cell<T,Lattice>& cell ) {
  T rho, uTemp[Lattice<T>::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell, rho, uTemp, pi);
  T newOmega = computeOmega(this->getOmega(), preFactor, rho, pi);
  return newOmega;
}

template<typename T, template<typename U> class Lattice>
T SmagorinskyBGKdynamics<T,Lattice>::computePreFactor(T omega, T smagoConst, T dx, T dt) {
  return (T)(smagoConst*smagoConst*dx*dx)*Lattice<T>::invCs2/dt*4*sqrt(2);
}



template<typename T, template<typename U> class Lattice>
T SmagorinskyBGKdynamics<T,Lattice>::computeOmega(T omega0, T preFactor, T rho, T pi[util::TensorVal<Lattice<T> >::n] ) {


  T PiNeqNormSqr = pi[0]*pi[0] + 2.0*pi[1]*pi[1] + pi[2]*pi[2];
  if (util::TensorVal<Lattice<T> >::n == 6)
    PiNeqNormSqr += pi[2]*pi[2] + pi[3]*pi[3] + 2*pi[4]*pi[4] +pi[5]*pi[5];
  T PiNeqNorm    = sqrt(PiNeqNormSqr);
  /// Molecular realaxation time
  T tau_mol = 1. /omega0;
  /// Turbulent realaxation time
  T tau_turb = 0.5*(sqrt(tau_mol*tau_mol+(preFactor*tau_eff*PiNeqNorm))-tau_mol);
  /// Effective realaxation time
  tau_eff = tau_mol+tau_turb;
  T omega_new= 1./tau_eff;
  return omega_new;
    
}

template<typename T, template<typename U> class Lattice>
SmagorinskyForcedBGKdynamics<T,Lattice>::SmagorinskyForcedBGKdynamics (
  T omega_, Momenta<T,Lattice>& momenta_, T smagoConst_, T dx_, T dt_ )
  : ForcedBGKdynamics<T,Lattice>(omega_,momenta_),
    smagoConst(smagoConst_),
    preFactor(computePreFactor(omega_,smagoConst_, dx_, dt_) )
{ }

template<typename T, template<typename U> class Lattice>
void SmagorinskyForcedBGKdynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho, u[Lattice<T>::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell, rho, u, pi);
  T newOmega = computeOmega(this->getOmega(), preFactor, rho, pi);
  T* force = cell.getExternal(this->forceBeginsAt);
  for (int iVel=0; iVel<Lattice<T>::d; ++iVel) {
    u[iVel] += force[iVel] / (T)2.;
  }
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, newOmega);
  lbHelpers<T,Lattice>::addExternalForce(cell, u, newOmega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void SmagorinskyForcedBGKdynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  T rho, uTemp[Lattice<T>::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell, rho, uTemp, pi);
  T newOmega = computeOmega(this->getOmega(), preFactor, rho, pi);
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, newOmega);
  lbHelpers<T,Lattice>::addExternalForce(cell, u, newOmega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void SmagorinskyForcedBGKdynamics<T,Lattice>::setOmega(T omega) {
  this->setOmega(omega);
  preFactor = computePreFactor(omega, smagoConst, dx, dt);
}

template<typename T, template<typename U> class Lattice>
T SmagorinskyForcedBGKdynamics<T,Lattice>::getSmagorinskyOmega(Cell<T,Lattice>& cell ) {
  T rho, uTemp[Lattice<T>::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell, rho, uTemp, pi);
  T newOmega = computeOmega(this->getOmega(), preFactor, rho, pi);
  return newOmega;
}

template<typename T, template<typename U> class Lattice>
T SmagorinskyForcedBGKdynamics<T,Lattice>::computePreFactor(T omega, T smagoConst, T dx, T dt) {
  return (T)(smagoConst*smagoConst*dx*dx)*Lattice<T>::invCs2/dt*4*sqrt(2);
}



template<typename T, template<typename U> class Lattice>
T SmagorinskyForcedBGKdynamics<T,Lattice>::computeOmega(T omega0, T preFactor, T rho, T pi[util::TensorVal<Lattice<T> >::n] ) {


  T PiNeqNormSqr = pi[0]*pi[0] + 2.0*pi[1]*pi[1] + pi[2]*pi[2];
  if (util::TensorVal<Lattice<T> >::n == 6)
    PiNeqNormSqr += pi[2]*pi[2] + pi[3]*pi[3] + 2*pi[4]*pi[4] +pi[5]*pi[5];
  T PiNeqNorm    = sqrt(PiNeqNormSqr);
  /// Molecular realaxation time
  T tau_mol = 1. /omega0;
  /// Turbulent realaxation time
  T tau_turb = 0.5*(sqrt(tau_mol*tau_mol+(preFactor*tau_eff*PiNeqNorm))-tau_mol);
  /// Effective realaxation time
  tau_eff = tau_mol+tau_turb;
  T omega_new= 1./tau_eff;
  return omega_new;
    
}
}

#endif
