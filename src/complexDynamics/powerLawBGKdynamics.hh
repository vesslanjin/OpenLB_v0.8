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
 * BGK Dynamics with adjusted omega -- generic implementation.
 */
#ifndef POWER_LAW_BGK_DYNAMICS_HH
#define POWER_LAW_BGK_DYNAMICS_HH

#include "powerLawBGKdynamics.h"
#include "core/cell.h"
#include "core/util.h"
#include "core/lbHelpers.h"
#include "math.h"

namespace olb {

////////////////////// Class PowerLawBGKdynamics //////////////////////////

/** \param vs2_ speed of sound
 *  \param momenta_ a Momenta object to know how to compute velocity momenta
 *  \param momenta_ a Momenta object to know how to compute velocity momenta
 */
template<typename T, template<typename U> class Lattice>
PowerLawBGKdynamics<T,Lattice>::PowerLawBGKdynamics (
  T omega_, Momenta<T,Lattice>& momenta_, T m_, T n_ )
  : BGKdynamics<T,Lattice>(omega_,momenta_),
    m(m_),
    n(n_)
    //preFactor(computePreFactor(omega_,smagoConst_) )
{ }

template<typename T, template<typename U> class Lattice>
void PowerLawBGKdynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho, u[Lattice<T>::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell, rho, u, pi);
  T newOmega = computeOmega(
this->getOmega(), preFactor, rho, pi);
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, newOmega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void PowerLawBGKdynamics<T,Lattice>::staticCollide (
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
void PowerLawBGKdynamics<T,Lattice>::setOmega(T omega) {
  this->setOmega(omega);
  preFactor = computePreFactor(omega, smagoConst);
}

template<typename T, template<typename U> class Lattice>
T PowerLawBGKdynamics<T,Lattice>::getPowerLawOmega(Cell<T,Lattice>& cell ) {
  T rho, uTemp[Lattice<T>::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell, rho, uTemp, pi);
  T newOmega = computeOmega(this->getOmega(), preFactor, rho, pi);
  return newOmega;
}

template<typename T, template<typename U> class Lattice>
T PowerLawBGKdynamics<T,Lattice>::computePreFactor(T omega, T smagoConst) {
  return (T)0.5 * util::sqr(smagoConst*omega*Lattice<T>::invCs2);
}

template<typename T, template<typename U> class Lattice>
T PowerLawBGKdynamics<T,Lattice>::computeOmega(T omega0, T preFactor, T rho, T pi[util::TensorVal<Lattice<T> >::n] ) {

  T PiNeqNormSqr = (pi[0]+1./Lattice<T>::invCs2*(rho-(T)1))*(pi[0]+1./Lattice<T>::invCs2*(rho-(T)1)) + 2.0*pi[1]*pi[1] + (pi[2]+1./Lattice<T>::invCs2*(rho-(T)1))*(pi[2]+1./Lattice<T>::invCs2*(rho-(T)1));
  if (util::TensorVal<Lattice<T> >::n == 6)
    PiNeqNormSqr += + 2*pi[2]*pi[2] - (pi[2]+1./Lattice<T>::invCs2*(rho-(T)1))*(pi[2]+1./Lattice<T>::invCs2*(rho-(T)1)) + (pi[3]+1./Lattice<T>::invCs2*(rho-(T)1))*(pi[3]+1./Lattice<T>::invCs2*(rho-(T)1)) + 2*pi[4]*pi[4] + (pi[5]+1./Lattice<T>::invCs2*(rho-(T)1))*(pi[5]+1./Lattice<T>::invCs2*(rho-(T)1));
  T PiNeqNorm    = sqrt(PiNeqNormSqr)/rho; // TODO "*rho" or "/rho"?

  // Compute new omega0 by solving with newton's scheme
  T tau = 1./omega0;
  for (int i=0; i<10 ; i++) {
    T fTau = m*pow(3,n)*pow(tau,1-n)*pow(PiNeqNorm,n-1)+0.5-tau;
    T dfTau = m*pow(3,n)*(1.-n)*pow(tau,-n)*pow(PiNeqNorm,n-1)-1; 
    tau=tau-fTau/dfTau;
    //std::cout << "Newton step=" << i << "; tau=" << tau << std::endl;
  }  
  omega0=1./tau;
  return omega0;
}

}

#endif
