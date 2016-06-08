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
 * BGK Dynamics with adjusted omega -- header file.
 */
#ifndef SMAGORINSKY_BGK_DYNAMICS_H
#define SMAGORINSKY_BGK_DYNAMICS_H

#include "core/dynamics.h"
#include "core/cell.h"
#include "core/units.h"
#include "core/units.hh"

namespace olb {

/// Implementation of the BGK collision step
template<typename T, template<typename U> class Lattice>
class SmagorinskyBGKdynamics : public BGKdynamics<T,Lattice> {
public:
  /// Constructor
  SmagorinskyBGKdynamics(T omega_, Momenta<T,Lattice>& momenta_, T smagoConst_, T dx_, T dt_);

  /// Collision step
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_);
  /// Collide with fixed velocity
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics_);

  /// Set local relaxation parameter of the dynamics
  virtual void setOmega(T omega_);

  /// Get local smagorinsky relaxation parameter of the dynamics
  virtual T getSmagorinskyOmega(Cell<T,Lattice>& cell_);

private:
  /// Computes a constant prefactor in order to speed up the computation
  T computePreFactor(T omega_, T smagoConst_, T dx_, T dt_);

  /// Computes the local smagorinsky relaxation parameter
  T computeOmega(T omega0_, T preFactor_, T rho_, T pi_[util::TensorVal<Lattice<T> >::n] );

private:
  /// effective collision time based upon Smagorisnky approach
  T tau_eff;
  /// Smagorinsky constant
  T smagoConst;
  /// Precomputed constant which speeeds up the computation
  T preFactor; 
  T dx;
  T dt;
};


/// Implementation of the ForcedBGK collision step
template<typename T, template<typename U> class Lattice>
class SmagorinskyForcedBGKdynamics : public ForcedBGKdynamics<T,Lattice> {
public:
  /// Constructor
  SmagorinskyForcedBGKdynamics(T omega_, Momenta<T,Lattice>& momenta_, T smagoConst_, T dx_, T dt_);

  /// Collision step
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_);
  /// Collide with fixed velocity
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics_);

  /// Set local relaxation parameter of the dynamics
  virtual void setOmega(T omega_);

  /// Get local smagorinsky relaxation parameter of the dynamics
  virtual T getSmagorinskyOmega(Cell<T,Lattice>& cell_);

private:
  /// Computes a constant prefactor in order to speed up the computation
  T computePreFactor(T omega_, T smagoConst_, T dx_, T dt_);

  /// Computes the local smagorinsky relaxation parameter
  T computeOmega(T omega0_, T preFactor_, T rho_, T pi_[util::TensorVal<Lattice<T> >::n] );

private:
  /// effective collision time based upon Smagorisnky approach
  T tau_eff;
  /// Smagorinsky constant
  T smagoConst;
  /// Precomputed constant which speeeds up the computation
  T preFactor; 
  T dx;
  T dt;
};
}

#endif
