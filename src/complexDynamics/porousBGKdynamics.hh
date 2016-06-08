/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Mathias J. Krause, Jonas Latt
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
 * BGK Dynamics for porous -- generic implementation.
 */
#ifndef POROUS_BGK_DYNAMICS_HH
#define POROUS_BGK_DYNAMICS_HH

#include "porousBGKdynamics.h"
#include "core/cell.h"
#include "core/dynamics.h"
#include "core/util.h"
#include "core/lbHelpers.h"
#include "math.h"

namespace olb {

////////////////////// Class PorousBGKdynamics //////////////////////////

template<typename T, template<typename U> class Lattice>
PorousBGKdynamics<T,Lattice>::PorousBGKdynamics (
  T omega_, Momenta<T,Lattice>& momenta_)
  : BGKdynamics<T,Lattice>(omega_,momenta_),
    omega(omega_)
{ }

template<typename T, template<typename U> class Lattice>
void PorousBGKdynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho, u[Lattice<T>::d];
  this->momenta.computeRhoU(cell, rho, u);
  T* porosity = cell.getExternal(porosityIsAt);
  for (int i=0; i<Lattice<T>::d; i++)  {
    u[i] *= porosity[0];
  }
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
T PorousBGKdynamics<T,Lattice>::getOmega() const {
  return omega;
}

template<typename T, template<typename U> class Lattice>
void PorousBGKdynamics<T,Lattice>::setOmega(T omega_) {
  omega = omega_;
}


//////////////////// Class ExtendedPorousBGKdynamics ////////////////////

template<typename T, template<typename U> class Lattice>
ExtendedPorousBGKdynamics<T,Lattice>::ExtendedPorousBGKdynamics (
  T omega_, Momenta<T,Lattice>& momenta_)
  : BGKdynamics<T,Lattice>(omega_,momenta_),
    omega(omega_)
{ }

template<typename T, template<typename U> class Lattice>
void ExtendedPorousBGKdynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  // compute uPre
  T rhoPre, rhoPost, uPre[Lattice<T>::d], uPost[Lattice<T>::d];
  this->momenta.computeRhoU(cell, rhoPre, uPre);

  T rho, u[Lattice<T>::d];
  this->momenta.computeRhoU(cell, rho, u);
  T* porosity = cell.getExternal(porosityIsAt);
  for (int i=0; i<Lattice<T>::d; i++)  {
    u[i] *= porosity[0];
  }
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }

  //compute uPost
  this->momenta.computeRhoU(cell, rhoPost, uPost);
  // compute localDrag
  T* localDrag = cell.getExternal(localDragBeginsAt);
  for (int i=0; i<Lattice<T>::d; i++)  {
    localDrag[i] = rhoPre  *  uPre[i]
                 - rhoPost * uPost[i];
  }
}

template<typename T, template<typename U> class Lattice>
T ExtendedPorousBGKdynamics<T,Lattice>::getOmega() const {
  return omega;
}

template<typename T, template<typename U> class Lattice>
void ExtendedPorousBGKdynamics<T,Lattice>::setOmega(T omega_) {
  omega = omega_;
}


} // olb

#endif
