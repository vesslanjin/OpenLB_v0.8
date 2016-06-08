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
 * can be instantiated -- header file.
 */
#ifndef ADVECTION_DIFFUSION_DYNAMICS_H
#define ADVECTION_DIFFUSION_DYNAMICS_H

#include "advectionDiffusionLatticeDescriptors.h"
#include "core/dynamics.h"

namespace olb {

// ========= the RLB advection diffusion dynamics ========//
// it uses the regularized approximation that can be found in
// the thesis of J. Latt (2007).

template<typename T, template<typename U> class Lattice>
class AdvectionDiffusionRLBdynamics : public BasicDynamics<T,Lattice> {
public:
  /// Constructor
  AdvectionDiffusionRLBdynamics(T omega_, Momenta<T,Lattice>& momenta_);
  /// Clone the object on its dynamic type.
  virtual AdvectionDiffusionRLBdynamics<T,Lattice>* clone() const;
  /// Compute equilibrium distribution function
  virtual T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const;
  /// Collision step
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics );
  /// Collide with fixed velocity
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics );
  /// Get local relaxation parameter of the dynamics
  virtual T getOmega() const;
  /// Set local relaxation parameter of the dynamics
  virtual void setOmega(T omega_);
private:
  T omega;  ///< relaxation parameter
};

// ========= the BGK advection diffusion dynamics ========//
// This approach contains a slight error in the diffusion
// term.

template<typename T, template<typename U> class Lattice>
class AdvectionDiffusionBGKdynamics : public BasicDynamics<T,Lattice> {
public:
  /// Constructor
  AdvectionDiffusionBGKdynamics(T omega_, Momenta<T,Lattice>& momenta_);
  /// Clone the object on its dynamic type.
  virtual AdvectionDiffusionBGKdynamics<T,Lattice>* clone() const;
  /// Compute equilibrium distribution function
  virtual T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const;
  /// Collision step
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics );
  /// Collide with fixed velocity
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics );
  /// Get local relaxation parameter of the dynamics
  virtual T getOmega() const;
  /// Set local relaxation parameter of the dynamics
  virtual void setOmega(T omega_);
private:
  T omega;  ///< relaxation parameter
};





} // namespace olb

#endif

