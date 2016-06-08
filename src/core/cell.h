/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006, 2007 Jonas Latt
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
 * Definition of a LB cell -- header file.
 */
#ifndef CELL_H
#define CELL_H

#include "olbDebug.h"
#include "latticeDescriptors.h"
#include "dynamics.h"

namespace olb {

/// A LB lattice cell.
/** A cell contains the q values of the distribution functions f on
 * one lattice point, as well as a pointer to the dynamics of the
 * cell. Thanks to this pointer, one can have a space dependend de-
 * finition of the dynamics. This mechanism is useful e.g. for the
 * implementation of boundary conditions, or an inhomogeneous body
 * force.
 *
 * The dynamics object is not owned by the class, it is not
 * destructed in the Cell destructor.
 *
 * This class is not intended to be derived from.
 */
template<typename T, template<typename U> class Lattice>
class Cell {
public:
  /// The lattice populations are defined as a q-element C-array.
  typedef T fPop[Lattice<T>::q];
  /// Additional per-cell scalars for external fields, e.g. forces
  typedef descriptors::ExternalFieldArray <
  T, typename Lattice<T>::ExternalField > External;
public:
  /// Default constructor.
  Cell();
  /// Constructor, to be used whenever possible.
  Cell(Dynamics<T,Lattice>* dynamics_);
public:
  /// Read-write access to distribution functions.
  /** \param iPop index of the accessed distribution function */
  T& operator[](int iPop) {
    OLB_PRECONDITION( iPop < Lattice<T>::q );
    return f[iPop];
  }
  /// Read-only access to distribution functions.
  /** \param iPop index of the accessed distribution function */
  T const& operator[](int iPop) const {
    OLB_PRECONDITION( iPop < Lattice<T>::q );
    return f[iPop];
  }
  /// Attribute all f-values from another cell to the present one.
  /** \return a reference to *this
   */
  Cell<T,Lattice>& attributeF(Cell<T,Lattice> const& rhs) {
    for (unsigned iPop=0; iPop < Lattice<T>::q; ++iPop) {
      f[iPop] = rhs.f[iPop];
    }
    return *this;
  };
  /// Attribute all f-values and external scalars from another cell to the present one.
  /** \return a reference to *this
   * This is similar to the assignment operator operator= (which is
   * created by default and copies all the f's, as well as the dynamics
   * object), except that the dynamics object is not copied.
   */
  Cell<T,Lattice>& attributeValues(Cell<T,Lattice> const& rhs) {
    attributeF(rhs);
    for (int iExt=0; iExt < Lattice<T>::ExternalField::numScalars; ++iExt) {
      *external.get(iExt) = *rhs.external.get(iExt);
    }
    return *this;
  };
  /// Get a pointer to an external field
  T* getExternal(int offset) {
    OLB_PRECONDITION( offset < Lattice<T>::ExternalField::numScalars );
    return external.get(offset);
  }
  /// Get a const pointer to an external field
  T const* getExternal(int offset) const {
    OLB_PRECONDITION( offset < Lattice<T>::ExternalField::numScalars );
    return external.get(offset);
  }
  /// Define or re-define dynamics of the cell.
  /** \param dynamics_ a pointer to the dynamics object, whos
    *    memory management falls under the responsibility of the
    *    user */
  void defineDynamics(Dynamics<T,Lattice>* dynamics_);
  /// Get a non-modifiable pointer to the dynamics
  Dynamics<T,Lattice> const* getDynamics() const;
  /// Get a non-modifiable pointer to the dynamics
  Dynamics<T,Lattice>* getDynamics();
  /// Request whether this cell does statistics measurements
  bool takesStatistics() const {
    return takesStat;
  }
  /// Specify whether this cell does statistics measurements
  void specifyStatisticsStatus(bool status) {
    takesStat = status;
  }

  // The following helper functions forward the function call
  // to the Dynamics object
public:
  /// Apply LB collision to the cell according to local dynamics.
  void collide(LatticeStatistics<T>& statistics) {
    OLB_PRECONDITION( dynamics );
    dynamics->collide(*this, statistics);
  }
  /// Apply LB collision with fixed velocity to the cell.
  void staticCollide(const T u[Lattice<T>::d], LatticeStatistics<T>& statistics)
  {
    OLB_PRECONDITION( dynamics );
    dynamics->staticCollide(*this, u, statistics);
  }

  /// Compute equilibrium distribution function
  T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
  {
    OLB_PRECONDITION( dynamics );
    return dynamics->computeEquilibrium(iPop, rho, u, uSqr);
  }

  /// Compute particle density on the cell.
  /** \return particle density
   */
  T computeRho() const {
    OLB_PRECONDITION( dynamics );
    return dynamics->computeRho(*this);
  }
  /// Compute fluid velocity on the cell.
  /** \param u fluid velocity
   */
  void computeU(T u[Lattice<T>::d]) const {
    OLB_PRECONDITION( dynamics );
    dynamics->computeU(*this, u);
  }
  /// Compute components of the stress tensor on the cell.
  /** \param pi stress tensor */
  void computeStress (
    T pi[util::TensorVal<Lattice<T> >::n]) const
  {
    OLB_PRECONDITION( dynamics );
    T rho, u[Lattice<T>::d];
    dynamics->computeRhoU(*this, rho, u);
    dynamics->computeStress(*this, rho, u, pi);
  }
  /// Compute fluid velocity and particle density on the cell.
  /** \param rho particle density
   *  \param u fluid velocity
   */
  void computeRhoU(T& rho, T u[Lattice<T>::d]) const {
    OLB_PRECONDITION( dynamics );
    dynamics->computeRhoU(*this, rho, u);
  }
  /// Compute all momenta on the celll, up to second order.
  /** \param rho particle density
   *  \param u fluid velocity
   *  \param pi stress tensor
   */
  void computeAllMomenta (
    T& rho, T u[Lattice<T>::d],
    T pi[util::TensorVal<Lattice<T> >::n] ) const
  {
    OLB_PRECONDITION( dynamics );
    dynamics->computeAllMomenta(*this, rho, u, pi);
  }
  /// Access particle populations through the dynamics object.
  /** This method is similar to operator[]: it delivers the
   * value of the particle populations. This time, those values
   * are however computed through a virtual call to the dynamics
   * object.
   */
  void computePopulations(T* f) const {
    OLB_PRECONDITION( dynamics );
    dynamics->computePopulations(*this, f);
  }
  /// Access external fields through the dynamics object.
  /** This method is similar to getExternal(): it delivers the
   * value of the external fields. This time, those values
   * are however computed through a virtual call to the dynamics
   * object.
   */
  void computeExternalField(int pos, int size, T* ext) const {
    OLB_PRECONDITION( dynamics );
    dynamics->computeExternalField(*this, pos, size, ext);
  }
  /// Set particle density on the cell.
  /** \param rho particle density
   */
  void defineRho(T rho) {
    OLB_PRECONDITION( dynamics );
    dynamics->defineRho(*this, rho);
  }
  /// Set fluid velocity on the cell.
  /** \param u fluid velocity
   */
  void defineU(const T u[Lattice<T>::d]) {
    OLB_PRECONDITION( dynamics );
    dynamics->defineU(*this, u);
  }
  /// Set components of the stress tensor on the cell.
  /** \param pi stress tensor */
  void defineStress (
    const T pi[util::TensorVal<Lattice<T> >::n])
  {
    OLB_PRECONDITION( dynamics );
    T rho, u[Lattice<T>::d];
    dynamics->computeRhoU(*this, rho, u);
    dynamics->defineAllMomenta(*this, rho, u, pi);
  }
  /// Define fluid velocity and particle density on the cell.
  /** \param rho particle density
   *  \param u fluid velocity
   */
  void defineRhoU(T rho, const T u[Lattice<T>::d]) {
    OLB_PRECONDITION( dynamics );
    dynamics->defineRhoU(*this, rho, u);
  }
  /// Define all momenta on the celll, up to second order.
  /** \param rho particle density
   *  \param u fluid velocity
   *  \param pi stress tensor
   */
  void defineAllMomenta (
    T rho, const T u[Lattice<T>::d],
    const T pi[util::TensorVal<Lattice<T> >::n] )
  {
    OLB_PRECONDITION( dynamics );
    dynamics->defineAllMomenta(*this, rho, u, pi);
  }
  /// Define particle populations through the dynamics object.
  /** This method is similar to operator[]: it modifies the
   * value of the particle populations. This time, those values
   * are however accessed through a virtual call to the dynamics
   * object.
   */
  void definePopulations(const T* f) {
    OLB_PRECONDITION( dynamics );
    dynamics->definePopulations(*this, f);
  }
  /// Define external fields through the dynamics object.
  /** This method is similar to getExternal(): it accesses the
   * value of the external fields. This time, those values
   * are however accessed through a virtual call to the dynamics
   * object.
   */
  void defineExternalField(int pos, int size, const T* ext) {
    OLB_PRECONDITION( dynamics );
    dynamics->defineExternalField(*this, pos, size, ext);
  }
  /// Initialize all f values to their local equilibrium
  void iniEquilibrium(T rho, const T u[Lattice<T>::d]) {
    OLB_PRECONDITION( dynamics );
    dynamics->iniEquilibrium(*this, rho, u);
  }
  /// Revert ("bounce-back") the distribution functions.
  void revert();
  void serialize(T* data) const;
  void unSerialize(T const* data);
private:
  void iniPop();
  void iniExternal();
private:
  fPop                 f;         ///< distribution functions
  External             external;  ///< external scalars
  bool                 takesStat; ///< is statistics taken?
  Dynamics<T,Lattice>* dynamics;  ///< local LB dynamics
};

template<typename T, template<typename U> class Lattice>
struct WriteCellFunctional {
  virtual ~WriteCellFunctional() { };
  virtual void apply(Cell<T,Lattice>& cell) const =0;
};

}  // namespace olb

#endif
