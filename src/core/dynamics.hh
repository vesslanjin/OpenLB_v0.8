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
 * A collection of dynamics classes (e.g. BGK) with which a Cell object
 * can be instantiated -- generic implementation.
 */
#ifndef LB_DYNAMICS_HH
#define LB_DYNAMICS_HH

#include <algorithm>
#include <limits>
#include "dynamics.h"
#include "cell.h"
#include "lbHelpers.h"
#include "firstOrderLbHelpers.h"
#include "d3q13Helpers.h"

namespace olb {

////////////////////// Class Dynamics ////////////////////////

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::computePopulations(Cell<T,Lattice> const& cell, T* f) const {
  for (int iPop=0; iPop<Lattice<T>::q; ++iPop) {
    f[iPop] = cell[iPop];
  }
}

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::iniEquilibrium(Cell<T,Lattice>& cell, T rho, const T u[Lattice<T>::d]) {
  T uSqr = util::normSqr<T,Lattice<T>::d>(u);
  for (int iPop=0; iPop<Lattice<T>::q; ++iPop) {
    cell[iPop] = computeEquilibrium(iPop, rho, u, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::computeExternalField (
  Cell<T,Lattice> const& cell, int pos, int size, T* ext) const {
  OLB_PRECONDITION(pos+size <= Lattice<T>::ExternalField::numScalars);
  T const* externalData = cell.getExternal(pos);
  for (int iExt=0; iExt<size; ++iExt) {
    ext[iExt] = externalData[iExt];
  }
}

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::definePopulations(Cell<T,Lattice>& cell, const T* f)
{
  for (int iPop=0; iPop<Lattice<T>::q; ++iPop) {
    cell[iPop] = f[iPop];
  }
}

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::defineExternalField (
  Cell<T,Lattice>& cell, int pos, int size, const T* ext)
{
  OLB_PRECONDITION(pos+size <= Lattice<T>::ExternalField::numScalars);
  T* externalData = cell.getExternal(pos);
  for (int iExt=0; iExt<size; ++iExt) {
    externalData[iExt] = ext[iExt];
  }
}

template<typename T, template<typename U> class Lattice>
T Dynamics<T,Lattice>::getParameter(int whichParameter) const {
  if (whichParameter == dynamicParams::omega_shear) {
    return getOmega();
  }
  return 0.;
}

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::setParameter(int whichParameter, T value) {
  if (whichParameter == dynamicParams::omega_shear) {
    setOmega(value);
  }
}

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::setBoundaryIntersection(int iPop, T distance)
{ }

template<typename T, template<typename U> class Lattice>
bool Dynamics<T,Lattice>::getBoundaryIntersection(int iPop, T point[Lattice<T>::d])
{ return 0; }

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::defineU(const T u[Lattice<T>::d])
{ }

template<typename T, template<typename U> class Lattice>
void Dynamics<T,Lattice>::defineU(int iPop, const T u[Lattice<T>::d])
{ }

template<typename T, template<typename U> class Lattice>
T Dynamics<T,Lattice>::getVelocityCoefficient(int iPop)
{ return 0; }

////////////////////// Class BasicDynamics ////////////////////////

template<typename T, template<typename U> class Lattice>
BasicDynamics<T,Lattice>::BasicDynamics(Momenta<T,Lattice>& momenta_)
  : momenta(momenta_)
{ }

template<typename T, template<typename U> class Lattice>
T BasicDynamics<T,Lattice>::computeRho(Cell<T,Lattice> const& cell) const
{
  return momenta.computeRho(cell);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::computeU (
  Cell<T,Lattice> const& cell,
  T u[Lattice<T>::d]) const
{
  momenta.computeU(cell, u);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::computeJ (
  Cell<T,Lattice> const& cell,
  T j[Lattice<T>::d]) const
{
  momenta.computeJ(cell, j);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::computeStress (
  Cell<T,Lattice> const& cell,
  T rho, const T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  momenta.computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::computeRhoU (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d]) const
{
  momenta.computeRhoU(cell, rho, u);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::computeAllMomenta (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  this->computeRhoU(cell, rho, u);
  this->computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::defineRho(Cell<T,Lattice>& cell, T rho) {
  momenta.defineRho(cell, rho);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::defineU (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d])
{
  momenta.defineU(cell, u);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::defineRhoU (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d])
{
  momenta.defineRhoU(cell, rho, u);
}

template<typename T, template<typename U> class Lattice>
void BasicDynamics<T,Lattice>::defineAllMomenta (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d],
  const T pi[util::TensorVal<Lattice<T> >::n] )
{
  momenta.defineAllMomenta(cell, rho, u, pi);
}


////////////////////// Class BGKdynamics //////////////////////////

/** \param omega_ relaxation parameter, related to the dynamic viscosity
 *  \param momenta_ a Momenta object to know how to compute velocity momenta
 */
template<typename T, template<typename U> class Lattice>
BGKdynamics<T,Lattice>::BGKdynamics (
  T omega_, Momenta<T,Lattice>& momenta_ )
  : BasicDynamics<T,Lattice>(momenta_),
    omega(omega_)
{ }

template<typename T, template<typename U> class Lattice>
BGKdynamics<T,Lattice>* BGKdynamics<T,Lattice>::clone() const {
  return new BGKdynamics<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
T BGKdynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr);
}

template<typename T, template<typename U> class Lattice>
void BGKdynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho, u[Lattice<T>::d];
  this->momenta.computeRhoU(cell, rho, u);
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void BGKdynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  T rho;
  rho = this->momenta.computeRho(cell);
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
T BGKdynamics<T,Lattice>::getOmega() const {
  return omega;
}

template<typename T, template<typename U> class Lattice>
void BGKdynamics<T,Lattice>::setOmega(T omega_) {
  omega = omega_;
}


////////////////////// Class ConstRhoBGKdynamics //////////////////////////

/** \param omega_ relaxation parameter, related to the dynamic viscosity
 *  \param momenta_ a Momenta object to know how to compute velocity momenta
 */
template<typename T, template<typename U> class Lattice>
ConstRhoBGKdynamics<T,Lattice>::ConstRhoBGKdynamics (
  T omega_, Momenta<T,Lattice>& momenta_ )
  : BasicDynamics<T,Lattice>(momenta_),
    omega(omega_)
{ }

template<typename T, template<typename U> class Lattice>
ConstRhoBGKdynamics<T,Lattice>* ConstRhoBGKdynamics<T,Lattice>::clone()
const
{
  return new ConstRhoBGKdynamics<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
T ConstRhoBGKdynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr);
}

template<typename T, template<typename U> class Lattice>
void ConstRhoBGKdynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho, u[Lattice<T>::d];
  this->momenta.computeRhoU(cell, rho, u);

  T deltaRho = (T)1 - (statistics).getAverageRho();
  T ratioRho = (T)1 + deltaRho/rho;
  //T rho_ = (T)1/rho;
  //T ratioRho = deltaRho*rho_ + (T)1;

  T uSqr = lbHelpers<T,Lattice>::constRhoBgkCollision (
             cell, rho, u, ratioRho, omega );
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho+deltaRho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void ConstRhoBGKdynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  T rho = this->momenta.computeRho(cell);
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
T ConstRhoBGKdynamics<T,Lattice>::getOmega() const {
  return omega;
}

template<typename T, template<typename U> class Lattice>
void ConstRhoBGKdynamics<T,Lattice>::setOmega(T omega_) {
  omega = omega_;
}

////////////////////// Class IncBGKdynamics //////////////////////////

/** \param omega_ relaxation parameter, related to the dynamic viscosity
 *  \param momenta_ a Momenta object to know how to compute velocity momenta
 */
template<typename T, template<typename U> class Lattice>
IncBGKdynamics<T,Lattice>::IncBGKdynamics (
  T omega_, Momenta<T,Lattice>& momenta_ )
  : BasicDynamics<T,Lattice>(momenta_),
    omega(omega_)
{ }

template<typename T, template<typename U> class Lattice>
IncBGKdynamics<T,Lattice>* IncBGKdynamics<T,Lattice>::clone() const {
  return new IncBGKdynamics<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
T IncBGKdynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr);
}

template<typename T, template<typename U> class Lattice>
void IncBGKdynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho = this->momenta.computeRho(cell);
  T p = rho / Lattice<T>::invCs2;
  T j[Lattice<T>::d];
  this->momenta.computeJ(cell, j);
  T uSqr = lbHelpers<T,Lattice>::incBgkCollision(cell, p, j, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void IncBGKdynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T j[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  T rho = this->momenta.computeRho(cell);
  T p = rho / Lattice<T>::invCs2;
  T uSqr = lbHelpers<T,Lattice>::incBgkCollision(cell, p, j, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
T IncBGKdynamics<T,Lattice>::getOmega() const {
  return omega;
}

template<typename T, template<typename U> class Lattice>
void IncBGKdynamics<T,Lattice>::setOmega(T omega_) {
  omega = omega_;
}



////////////////////// Class RLBdynamics /////////////////////////

/** \param omega_ relaxation parameter, related to the dynamic viscosity
 *  \param momenta_ a Momenta object to know how to compute velocity momenta
 */
template<typename T, template<typename U> class Lattice>
RLBdynamics<T,Lattice>::RLBdynamics (
  T omega_, Momenta<T,Lattice>& momenta_ )
  : BasicDynamics<T,Lattice>(momenta_),
    omega(omega_)
{ }

template<typename T, template<typename U> class Lattice>
RLBdynamics<T,Lattice>* RLBdynamics<T,Lattice>::clone() const {
  return new RLBdynamics<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
T RLBdynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr);
}

template<typename T, template<typename U> class Lattice>
void RLBdynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho, u[Lattice<T>::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell, rho, u, pi);
  T uSqr = rlbHelpers<T,Lattice>::rlbCollision(cell, rho, u, pi, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void RLBdynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  T rho, uDummy[Lattice<T>::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell, rho, uDummy, pi);
  T uSqr = rlbHelpers<T,Lattice>::rlbCollision(cell, rho, u, pi, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
T RLBdynamics<T,Lattice>::getOmega() const {
  return omega;
}

template<typename T, template<typename U> class Lattice>
void RLBdynamics<T,Lattice>::setOmega(T omega_) {
  omega = omega_;
}


////////////////////// Class CombinedRLBdynamics /////////////////////////

template<typename T, template<typename U> class Lattice, typename Dynamics>
CombinedRLBdynamics<T,Lattice,Dynamics>::CombinedRLBdynamics (
  T omega_, Momenta<T,Lattice>& momenta_ )
  : BasicDynamics<T,Lattice>(momenta_),
    boundaryDynamics(omega_, momenta_)
{ }

template<typename T, template<typename U> class Lattice, typename Dynamics>
CombinedRLBdynamics<T,Lattice,Dynamics>*
CombinedRLBdynamics<T,Lattice, Dynamics>::clone() const
{
  return new CombinedRLBdynamics<T,Lattice,Dynamics>(*this);
}

template<typename T, template<typename U> class Lattice, typename Dynamics>
T CombinedRLBdynamics<T,Lattice,Dynamics>::
computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return boundaryDynamics.computeEquilibrium(iPop, rho, u, uSqr);
}

template<typename T, template<typename U> class Lattice, typename Dynamics>
void CombinedRLBdynamics<T,Lattice,Dynamics>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  typedef Lattice<T> L;

  T rho, u[L::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell,rho,u,pi);

  T uSqr = util::normSqr<T,L::d>(u);

  for (int iPop = 0; iPop < L::q; ++iPop)
  {
    cell[iPop] = computeEquilibrium(iPop,rho,u,uSqr) +
                 firstOrderLbHelpers<T,Lattice>::fromPiToFneq(iPop, pi);
  }

  boundaryDynamics.collide(cell, statistics);
}

template<typename T, template<typename U> class Lattice, typename Dynamics>
void CombinedRLBdynamics<T,Lattice,Dynamics>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  typedef Lattice<T> L;

  T rho, falseU[L::d], pi[util::TensorVal<Lattice<T> >::n];
  this->momenta.computeAllMomenta(cell, rho, falseU, pi);

  T uSqr = util::normSqr<T,L::d>(u);

  for (int iPop = 0; iPop < L::q; ++iPop)
  {
    cell[iPop] = computeEquilibrium(iPop,rho,u,uSqr) +
                 firstOrderLbHelpers<T,Lattice>::fromPiToFneq(iPop, pi);
  }

  boundaryDynamics.staticCollide(cell, u, statistics);
}

template<typename T, template<typename U> class Lattice, typename Dynamics>
T CombinedRLBdynamics<T,Lattice,Dynamics>::getOmega() const
{
  return boundaryDynamics.getOmega();
}

template<typename T, template<typename U> class Lattice, typename Dynamics>
void CombinedRLBdynamics<T,Lattice,Dynamics>::setOmega(T omega_)
{
  boundaryDynamics.setOmega(omega_);
}

template<typename T, template<typename U> class Lattice, typename Dynamics>
T CombinedRLBdynamics<T,Lattice,Dynamics>::getParameter(int whichParameter) const {
  return boundaryDynamics.getParameter(whichParameter);
}

template<typename T, template<typename U> class Lattice, typename Dynamics>
void CombinedRLBdynamics<T,Lattice,Dynamics>::setParameter(int whichParameter, T value) {
  boundaryDynamics.setParameter(whichParameter, value);
}


////////////////////// Class ForcedBGKdynamics /////////////////////////

/** \param omega_ relaxation parameter, related to the dynamic viscosity
 *  \param momenta_ a Momenta object to know how to compute velocity momenta
 */
template<typename T, template<typename U> class Lattice>
ForcedBGKdynamics<T,Lattice>::ForcedBGKdynamics (
  T omega_, Momenta<T,Lattice>& momenta_ )
  : BasicDynamics<T,Lattice>(momenta_),
    omega(omega_)
{
  // This ensures both that the constant sizeOfForce is defined in
  // ExternalField and that it has the proper size
  OLB_PRECONDITION( Lattice<T>::d == Lattice<T>::ExternalField::sizeOfForce );
}

template<typename T, template<typename U> class Lattice>
ForcedBGKdynamics<T,Lattice>* ForcedBGKdynamics<T,Lattice>::clone() const {
  return new ForcedBGKdynamics<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
T ForcedBGKdynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr);
}

template<typename T, template<typename U> class Lattice>
void ForcedBGKdynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho, u[Lattice<T>::d];
  this->momenta.computeRhoU(cell, rho, u);
  T* force = cell.getExternal(forceBeginsAt);
  for (int iVel=0; iVel<Lattice<T>::d; ++iVel) {
    u[iVel] += force[iVel] / (T)2.;
  }
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, omega);
  lbHelpers<T,Lattice>::addExternalForce(cell, u, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void ForcedBGKdynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  T rho, uDummy[Lattice<T>::d];
  this->momenta.computeRhoU(cell, rho, uDummy);
  T uSqr = lbHelpers<T,Lattice>::bgkCollision(cell, rho, u, omega);
  lbHelpers<T,Lattice>::addExternalForce(cell, u, omega);
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
T ForcedBGKdynamics<T,Lattice>::getOmega() const {
  return omega;
}

template<typename T, template<typename U> class Lattice>
void ForcedBGKdynamics<T,Lattice>::setOmega(T omega_) {
  omega = omega_;
}



////////////////////// Class D3Q13dynamics /////////////////////////

/** \param omega_ relaxation parameter, related to the dynamic viscosity
 *  \param momenta_ a Momenta object to know how to compute velocity momenta
 */
template<typename T, template<typename U> class Lattice>
D3Q13dynamics<T,Lattice>::D3Q13dynamics (
  T omega_, Momenta<T,Lattice>& momenta_ )
  : BasicDynamics<T,Lattice>(momenta_)
{
  setOmega(omega_);
}

template<typename T, template<typename U> class Lattice>
D3Q13dynamics<T,Lattice>* D3Q13dynamics<T,Lattice>::clone() const {
  return new D3Q13dynamics<T,Lattice>(*this);
}

template<typename T, template<typename U> class Lattice>
T D3Q13dynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  // To get at the equilibrium, execute collision with relaxation parameters 1
  Cell<T,Lattice> tmp;
  for (int pop=0; pop<Lattice<T>::q; ++pop) {
    tmp[pop] = Lattice<T>::t[pop];
  }
  d3q13Helpers<T>::collision(tmp, rho, u, (T)1, (T)1);
  return tmp[iPop];
}


template<typename T, template<typename U> class Lattice>
void D3Q13dynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  T rho, u[Lattice<T>::d];
  this->momenta.computeRhoU(cell, rho, u);
  T uSqr = d3q13Helpers<T>::collision (
             cell, rho, u, lambda_nu, lambda_nu_prime );
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
void D3Q13dynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  T rho = this->momenta.computeRho(cell);
  T uSqr = d3q13Helpers<T>::collision (
             cell, rho, u, lambda_nu, lambda_nu_prime );
  if (cell.takesStatistics()) {
    statistics.incrementStats(rho, uSqr);
  }
}

template<typename T, template<typename U> class Lattice>
T D3Q13dynamics<T,Lattice>::getOmega() const {
  return (T)4 / ( (T)3/lambda_nu + (T)1/(T)2 );
}

template<typename T, template<typename U> class Lattice>
void D3Q13dynamics<T,Lattice>::setOmega(T omega_) {
  lambda_nu = (T)3 / ( (T)4/omega_ - (T)1/(T)2 );
  lambda_nu_prime = (T)3 / ( (T)2/omega_ + (T)1/(T)2 );
}

////////////////////// Class Momenta //////////////////////////////

template<typename T, template<typename U> class Lattice>
void Momenta<T,Lattice>::computeRhoU (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d]) const
{
  rho = this->computeRho(cell);
  this->computeU(cell, u);

}

template<typename T, template<typename U> class Lattice>
void Momenta<T,Lattice>::computeAllMomenta (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  this->computeRhoU(cell, rho, u);
  this->computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void Momenta<T,Lattice>::defineRhoU (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d])
{
  this->defineRho(cell, rho);
  this->defineU(cell, u);

}

////////////////////// Class BulkMomenta //////////////////////////

template<typename T, template<typename U> class Lattice>
T BulkMomenta<T,Lattice>::computeRho(Cell<T,Lattice> const& cell) const {
  return lbHelpers<T,Lattice>::computeRho(cell);
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::computeU(Cell<T,Lattice> const& cell, T u[Lattice<T>::d]) const
{
  T dummyRho;
  lbHelpers<T,Lattice>::computeRhoU(cell, dummyRho, u);
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::computeJ(Cell<T,Lattice> const& cell, T j[Lattice<T>::d]) const
{
  lbHelpers<T,Lattice>::computeJ(cell, j);
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::computeStress (
  Cell<T,Lattice> const& cell,
  T rho, const T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  lbHelpers<T,Lattice>::computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::computeRhoU (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d] ) const
{
  lbHelpers<T,Lattice>::computeRhoU(cell, rho,u);
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::computeAllMomenta (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  this->computeRhoU(cell, rho, u);
  this->computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::defineRho(Cell<T,Lattice>& cell, T rho) {
  T oldRho, u[Lattice<T>::d];
  computeRhoU(cell, oldRho, u);
  T uSqr = util::normSqr<T,Lattice<T>::d>(u);
  T fNeq[Lattice<T>::q];
  lbHelpers<T,Lattice>::computeFneq(cell, fNeq, oldRho, u);
  for (int iPop=0; iPop < Lattice<T>::q; ++iPop) {
    cell[iPop] = lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr) +
                 fNeq[iPop];
  }
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::defineU (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d])
{
  T rho, oldU[Lattice<T>::d];
  computeRhoU(cell, rho, oldU);
  T uSqr = util::normSqr<T,Lattice<T>::d>(u);
  T fNeq[Lattice<T>::q];
  lbHelpers<T,Lattice>::computeFneq(cell, fNeq, rho, oldU);
  for (int iPop=0; iPop < Lattice<T>::q; ++iPop) {
    cell[iPop] = lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr) +
                 fNeq[iPop];
  }

}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::defineRhoU (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d])
{
  T oldRho, oldU[Lattice<T>::d];
  computeRhoU(cell, oldRho, oldU);
  T uSqr = util::normSqr<T,Lattice<T>::d>(u);
  T fNeq[Lattice<T>::q];
  lbHelpers<T,Lattice>::computeFneq(cell, fNeq, oldRho, oldU);
  for (int iPop=0; iPop < Lattice<T>::q; ++iPop) {
    cell[iPop] = lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr) +
                 fNeq[iPop];
  }
}

template<typename T, template<typename U> class Lattice>
void BulkMomenta<T,Lattice>::defineAllMomenta (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d],
  const T pi[util::TensorVal<Lattice<T> >::n] )
{
  T uSqr = util::normSqr<T,Lattice<T>::d>(u);
  for (int iPop=0; iPop < Lattice<T>::q; ++iPop) {
    cell[iPop] = lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr) +
                 firstOrderLbHelpers<T,Lattice>::fromPiToFneq(iPop, pi);
  }
}

////////////////////// Class ExternalVelocityMomenta //////////////////////////

template<typename T, template<typename U> class Lattice>
T ExternalVelocityMomenta<T,Lattice>::computeRho(Cell<T,Lattice> const& cell) const {
  return lbHelpers<T,Lattice>::computeRho(cell);
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::computeU(Cell<T,Lattice> const& cell, T u[Lattice<T>::d]) const
{
  T const* uExt = cell.getExternal(Lattice<T>::ExternalField::velocityBeginsAt);
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u[iD] = uExt[iD];
  }
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::computeJ(Cell<T,Lattice> const& cell, T j[Lattice<T>::d]) const
{
  T rho = computeRho(cell);
  T const* uExt = cell.getExternal(Lattice<T>::ExternalField::velocityBeginsAt);
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    j[iD] = uExt[iD]*rho;
  }
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::computeStress (
  Cell<T,Lattice> const& cell,
  T rho, const T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  lbHelpers<T,Lattice>::computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::computeRhoU (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d] ) const
{
  rho = computeRho(cell);
  computeU(cell,u);
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::computeAllMomenta (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  computeRhoU(cell, rho,u);
  computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::defineRho(Cell<T,Lattice>& cell, T rho) {
  T oldRho, u[Lattice<T>::d];
  computeRhoU(cell, oldRho, u);
  T uSqr = util::normSqr<T,Lattice<T>::d>(u);
  T fNeq[Lattice<T>::q];
  lbHelpers<T,Lattice>::computeFneq(cell, fNeq, oldRho, u);
  for (int iPop=0; iPop < Lattice<T>::q; ++iPop) {
    cell[iPop] = lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr) +
                 fNeq[iPop];
  }
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::defineU (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d])
{
  T* uExt = cell.getExternal(Lattice<T>::ExternalField::velocityBeginsAt);
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    uExt[iD] = u[iD];
  }
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::defineRhoU (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d])
{
  defineRho(cell, rho);
  defineU(cell, u);
}

template<typename T, template<typename U> class Lattice>
void ExternalVelocityMomenta<T,Lattice>::defineAllMomenta (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d],
  const T pi[util::TensorVal<Lattice<T> >::n] )
{
  defineU(cell, u);
  T uSqr = util::normSqr<T,Lattice<T>::d>(u);
  for (int iPop=0; iPop < Lattice<T>::q; ++iPop) {
    cell[iPop] = lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr) +
                 firstOrderLbHelpers<T,Lattice>::fromPiToFneq(iPop, pi);
  }
}


////////////////////// Class BounceBack ///////////////////////////

template<typename T, template<typename U> class Lattice>
BounceBack<T,Lattice>::BounceBack()
{ 
  rhoFixed=false;
}

template<typename T, template<typename U> class Lattice>
BounceBack<T,Lattice>::BounceBack(T rho_)
  :rho(rho_)
{ 
  rhoFixed=true;
}

template<typename T, template<typename U> class Lattice>
BounceBack<T,Lattice>* BounceBack<T,Lattice>::clone() const {
  return new BounceBack<T,Lattice>();
}

template<typename T, template<typename U> class Lattice>
T BounceBack<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return T();
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{
  for (int iPop=1; iPop <= Lattice<T>::q/2; ++iPop) {
    std::swap(cell[iPop], cell[iPop+Lattice<T>::q/2]);
  }
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{
  this->collide(cell, statistics);
}

template<typename T, template<typename U> class Lattice>
T BounceBack<T,Lattice>::computeRho(Cell<T,Lattice> const& cell) const {
 
  if (rhoFixed)
    return rho;
  return lbHelpers<T,Lattice>::computeRho(cell);
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::computeU (
  Cell<T,Lattice> const& cell,
  T u[Lattice<T>::d]) const
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u[iD] = T();
  }
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::computeJ (
  Cell<T,Lattice> const& cell,
  T j[Lattice<T>::d]) const
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    j[iD] = T();
  }
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::computeStress (
  Cell<T,Lattice> const& cell,
  T rho, const T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  for (int iPi=0; iPi<util::TensorVal<Lattice<T> >::n; ++iPi) {
    pi[iPi] = T();//std::numeric_limits<T>::signaling_NaN();
  }
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::computeRhoU (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d]) const
{
  rho = computeRho(cell);
  computeU(cell, u);
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::computeAllMomenta (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  computeRhoU(cell, rho, u);
  computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::defineRho(Cell<T,Lattice>& cell, T rho)
{ }

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::defineU (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d])
{ }

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::defineRhoU (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d])
{ }

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::defineAllMomenta (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d],
  const T pi[util::TensorVal<Lattice<T> >::n] )
{ }

template<typename T, template<typename U> class Lattice>
T BounceBack<T,Lattice>::getOmega() const {
  return T();//std::numeric_limits<T>::signaling_NaN();
}

template<typename T, template<typename U> class Lattice>
void BounceBack<T,Lattice>::setOmega(T omega_)
{ }

////////////////////// Class NoDynamics ///////////////////////////

template<typename T, template<typename U> class Lattice>
NoDynamics<T,Lattice>* NoDynamics<T,Lattice>::clone() const {
  return new NoDynamics<T,Lattice>();
}

template<typename T, template<typename U> class Lattice>
T NoDynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  return T();
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::collide (
  Cell<T,Lattice>& cell,
  LatticeStatistics<T>& statistics )
{ }

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics )
{ }

template<typename T, template<typename U> class Lattice>
T NoDynamics<T,Lattice>::computeRho(Cell<T,Lattice> const& cell) const
{
  return (T)0;
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::computeU (
  Cell<T,Lattice> const& cell,
  T u[Lattice<T>::d]) const
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u[iD] = T();
  }
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::computeJ (
  Cell<T,Lattice> const& cell,
  T j[Lattice<T>::d]) const
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    j[iD] = T();
  }
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::computeStress (
  Cell<T,Lattice> const& cell,
  T rho, const T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  for (int iPi=0; iPi<util::TensorVal<Lattice<T> >::n; ++iPi) {
    pi[iPi] = T();//std::numeric_limits<T>::signaling_NaN();
  }
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::computeRhoU (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d]) const
{
  rho = computeRho(cell);
  computeU(cell, u);
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::computeAllMomenta (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  computeRhoU(cell, rho, u);
  computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::defineRho(Cell<T,Lattice>& cell, T rho)
{ }

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::defineU (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d])
{ }

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::defineRhoU (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d])
{ }

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::defineAllMomenta (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d],
  const T pi[util::TensorVal<Lattice<T> >::n] )
{ }

template<typename T, template<typename U> class Lattice>
T NoDynamics<T,Lattice>::getOmega() const {
  return T();//std::numeric_limits<T>::signaling_NaN();
}

template<typename T, template<typename U> class Lattice>
void NoDynamics<T,Lattice>::setOmega(T omega_)
{ }

////////////////////// Class offDynamics ///////////////////////////
template<typename T, template<typename U> class Lattice>
OffDynamics<T,Lattice>::OffDynamics(
  const T _location[Lattice<T>::d])
{
  typedef Lattice<T> L;
  for (int iD = 0; iD < L::d; iD++)
    location[iD] = _location[iD];
  for (int iPop = 0; iPop < L::q; iPop++){
    distances[iPop] = -1;
    velocityCoefficient[iPop] = 0;
    for (int iD = 0; iD < L::d; iD++)
      boundaryIntersection[iPop][iD] = _location[iD];
  }
}

template<typename T, template<typename U> class Lattice>
OffDynamics<T,Lattice>::OffDynamics(
  const T _location[Lattice<T>::d], T _distances[Lattice<T>::q])
{
  typedef Lattice<T> L;
  for (int iD = 0; iD < L::d; iD++)
    location[iD] = _location[iD];
  for (int iPop = 0; iPop < L::q; iPop++){
    distances[iPop] = _distances[iPop];
    velocityCoefficient[iPop] = 0;
    const int* c = L::c[iPop];
    for (int iD = 0; iD < L::d; iD++)
      boundaryIntersection[iPop][iD] = _location[iD] - _distances[iPop]*c[iD];
  }
}

template<typename T, template<typename U> class Lattice>
void OffDynamics<T,Lattice>::setBoundaryIntersection(int iPop, T distance)
{
  /// direction points from the fluid node into the solid domain
  /// distance is the distance from the fluid node to the solid wall
  typedef Lattice<T> L;
  distances[iPop] = distance;
  const int* c = L::c[iPop];
  for (int iD = 0; iD < L::d; iD++)
    boundaryIntersection[iPop][iD] = location[iD] - distance*c[iD];
}

template<typename T, template<typename U> class Lattice>
bool OffDynamics<T,Lattice>::getBoundaryIntersection(int iPop, T intersection[Lattice<T>::d])
{
  typedef Lattice<T> L;
  if (distances[iPop] != -1){
    for (int iD = 0; iD < L::d; iD++){
      intersection[iD] = boundaryIntersection[iPop][iD];
    }
    return true;
  }
  return false;
}

template<typename T, template<typename U> class Lattice>
void OffDynamics<T,Lattice>::defineU (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d])
{
  defineU(u);
}

template<typename T, template<typename U> class Lattice>
void OffDynamics<T,Lattice>::defineU(const T u[Lattice<T>::d])
{
  typedef Lattice<T> L;
  for (int iPop = 0; iPop < L::q; iPop++){
    if (distances[iPop] != -1){
      defineU(iPop, u);
    }
  }
}

/// Bouzidi velocity boundary condition formulas for the Coefficients:
/** 2*     invCs2*weight*(c,u)  for dist < 1/2
 *  1/dist*invCs2*weight*(c,u)  for dist >= 1/2
 */

template<typename T, template<typename U> class Lattice>
void OffDynamics<T,Lattice>::defineU(
  int iPop, const T u[Lattice<T>::d])
{
  OLB_PRECONDITION(distances[iPop] != -1)
  typedef Lattice<T> L;
  const int* c = L::c[iPop];
  velocityCoefficient[iPop] = 0;
  // scalar product of c(iPop) and u
  for (int sum = 0; sum < L::d; sum++)  // +/- problem because of first stream than postprocess 
    velocityCoefficient[iPop] -= c[sum]*u[sum];
  // compute summand for boundary condition
  velocityCoefficient[iPop] *= 2*L::invCs2 * L::t[iPop];

}

template<typename T, template<typename U> class Lattice>
T OffDynamics<T,Lattice>::getVelocityCoefficient(int iPop)
{
  return velocityCoefficient[iPop];
}

/////////////// Singletons //////////////////////////////////

namespace instances {

template<typename T, template<typename U> class Lattice>
BulkMomenta<T,Lattice>& getBulkMomenta() {
  static BulkMomenta<T,Lattice> bulkMomentaSingleton;
  return bulkMomentaSingleton;
}

template<typename T, template<typename U> class Lattice>
ExternalVelocityMomenta<T,Lattice>& getExternalVelocityMomenta() {
  static ExternalVelocityMomenta<T,Lattice> externalVelocityMomentaSingleton;
  return externalVelocityMomentaSingleton;
}

template<typename T, template<typename U> class Lattice>
BounceBack<T,Lattice>& getBounceBack() {
  static BounceBack<T,Lattice> bounceBackSingleton;
  return bounceBackSingleton;
}

template<typename T, template<typename U> class Lattice>
NoDynamics<T,Lattice>& getNoDynamics() {
  static NoDynamics<T,Lattice> noDynamicsSingleton;
  return noDynamicsSingleton;
}

}

}

#endif
