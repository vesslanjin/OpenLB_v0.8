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
 * Implementation of boundary cell dynamics -- generic implementation.
 */
#ifndef MOMENTA_ON_BOUNDARIES_HH
#define MOMENTA_ON_BOUNDARIES_HH

#include <limits>
#include "momentaOnBoundaries.h"
#include "lbHelpers.h"
#include "firstOrderLbHelpers.h"

namespace olb {

////////////////////// Class EquilibriumBM //////////////////////

template<typename T, template<typename U> class Lattice>
EquilibriumBM<T,Lattice>::EquilibriumBM()
{
  rho = (T)1;
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u[iD] = T();
  }
}

template<typename T, template<typename U> class Lattice>
EquilibriumBM<T,Lattice>::EquilibriumBM(T rho_, const T u_[Lattice<T>::d]) {
  rho = rho_;
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u[iD] = u_[iD];
  }
}

template<typename T, template<typename U> class Lattice>
T EquilibriumBM<T,Lattice>::computeRho (
  Cell<T,Lattice> const& cell ) const
{
  return rho;
}

template<typename T, template<typename U> class Lattice>
void EquilibriumBM<T,Lattice>::computeU (
  Cell<T,Lattice> const& cell,
  T u_[Lattice<T>::d]) const
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u_[iD] = u[iD];
  }
}

template<typename T, template<typename U> class Lattice>
void EquilibriumBM<T,Lattice>::computeJ (
  Cell<T,Lattice> const& cell,
  T j_[Lattice<T>::d]) const
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    j_[iD] = u[iD]*rho;
  }
}

template<typename T, template<typename U> class Lattice>
void EquilibriumBM<T,Lattice>::computeStress (
  Cell<T,Lattice> const& cell,
  T rho, const T u[Lattice<T>::d],
  T pi_[util::TensorVal<Lattice<T> >::n] ) const
{
  for (int iPi=0; iPi<util::TensorVal<Lattice<T> >::n; ++iPi) {
    pi_[iPi] = T();
  }
}


template<typename T, template<typename U> class Lattice>
void EquilibriumBM<T,Lattice>::defineRho (
  Cell<T,Lattice>& cell, T rho_ )
{
  rho = rho_;
}

template<typename T, template<typename U> class Lattice>
void EquilibriumBM<T,Lattice>::defineU (
  Cell<T,Lattice>& cell,
  const T u_[Lattice<T>::d])
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u[iD] = u_[iD];
  }
}

template<typename T, template<typename U> class Lattice>
void EquilibriumBM<T,Lattice>::defineAllMomenta (
  Cell<T,Lattice>& cell,
  T rho_, const T u_[Lattice<T>::d],
  const T pi_[util::TensorVal<Lattice<T> >::n] )
{
  defineRho(cell, rho_);
  defineU(cell, u_);
}



////////////////////// Class VelocityBM //////////////////////

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
VelocityBM<T,Lattice,direction,orientation>::VelocityBM()
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u[iD] = T();
  }
}

/** It takes as argument the value of the velocity to be imposed on the
 * boundary.
 */
template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
VelocityBM<T,Lattice,direction,orientation>::
VelocityBM(const T u_[Lattice<T>::d])
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u[iD] = u_[iD];
  }
}

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
T VelocityBM<T,Lattice,direction,orientation>::computeRho (
  Cell<T,Lattice> const& cell ) const
{
  std::vector<int> const& onWallIndices
  = util::subIndex<Lattice<T>, direction, 0>();

  std::vector<int> const& normalIndices
  = util::subIndex<Lattice<T>, direction, orientation>();

  T rhoOnWall = T();
  for (unsigned fIndex=0; fIndex<onWallIndices.size(); ++fIndex) {
    rhoOnWall += cell[onWallIndices[fIndex]];
  }

  T rhoNormal = T();
  for (unsigned fIndex=0; fIndex<normalIndices.size(); ++fIndex) {
    rhoNormal += cell[normalIndices[fIndex]];
  }

  T rho =((T)2*rhoNormal+rhoOnWall+(T)1) /
         ((T)1+(T)orientation*this->u[direction]);

  return rho;
}

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
void VelocityBM<T,Lattice,direction,orientation>::computeU (
  Cell<T,Lattice> const& cell,
  T u_[Lattice<T>::d]) const
{
  computeU(u_);
}

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
void VelocityBM<T,Lattice,direction,orientation>::computeJ (
  Cell<T,Lattice> const& cell,
  T j_[Lattice<T>::d]) const
{
  T rho = computeRho(cell);
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    j_[iD] = u[iD]*rho;
  }
}

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
void VelocityBM<T,Lattice,direction,orientation>::computeU (
  T u_[Lattice<T>::d]) const
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u_[iD] = u[iD];
  }
}

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
void VelocityBM<T,Lattice,direction,orientation>::defineRho (
  Cell<T,Lattice>& cell, T rho_ )
{ }

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
void VelocityBM<T,Lattice,direction,orientation>::defineU (
  Cell<T,Lattice>& cell,
  const T u_[Lattice<T>::d])
{
  defineU(u_);
}

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
void VelocityBM<T,Lattice,direction,orientation>::defineU (
  const T u_[Lattice<T>::d])
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u[iD] = u_[iD];
  }
}

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
void VelocityBM<T,Lattice,direction,orientation>::defineAllMomenta (
  Cell<T,Lattice>& cell,
  T rho_, const T u_[Lattice<T>::d],
  const T pi_[util::TensorVal<Lattice<T> >::n] )
{
  this->defineRhoU(cell, rho_, u_);
}


////////////////////// Class PressureBM //////////////////////

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
PressureBM<T,Lattice,direction,orientation>::PressureBM()
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    values[iD] = T();
  }
  values[direction] = 1.;
}

/** It takes as argument the value of the tangential velocity
 * components, and the pressure, to be imposed on the boundary.
 */
template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
PressureBM<T,Lattice,direction,orientation>::
PressureBM(const T values_[Lattice<T>::d])
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    values[iD] = values_[iD];
  }
}

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
T PressureBM<T,Lattice,direction,orientation>::computeRho (
  Cell<T,Lattice> const& cell ) const
{
  return computeRho();
}

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
T PressureBM<T,Lattice,direction,orientation>::computeRho() const {
  return values[direction];
}

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
void PressureBM<T,Lattice,direction,orientation>::computeU (
  Cell<T,Lattice> const& cell,
  T u_[Lattice<T>::d]) const
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u_[iD] = values[iD];
  }
  T rho = values[direction];

  std::vector<int> const& onWallIndices
  = util::subIndex<Lattice<T>, direction, 0>();

  std::vector<int> const& normalIndices
  = util::subIndex<Lattice<T>, direction, orientation>();

  T rhoOnWall = T();
  for (unsigned fIndex=0; fIndex<onWallIndices.size(); ++fIndex) {
    rhoOnWall += cell[onWallIndices[fIndex]];
  }

  T rhoNormal = T();
  for (unsigned fIndex=0; fIndex<normalIndices.size(); ++fIndex) {
    rhoNormal += cell[normalIndices[fIndex]];
  }

  u_[direction] = (T)orientation*(
                    ((T)2*rhoNormal+rhoOnWall+(T)1)/rho-(T)1 );
}

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
void PressureBM<T,Lattice,direction,orientation>::computeJ (
  Cell<T,Lattice> const& cell,
  T j_[Lattice<T>::d]) const
{
  computeU(cell, j_);
  T rho = computeRho(cell);
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    j_[iD] *= rho;
  }
}

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
void PressureBM<T,Lattice,direction,orientation>::defineRho (
  Cell<T,Lattice>& cell, T rho_)
{
  defineRho(rho_);
}

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
void PressureBM<T,Lattice,direction,orientation>::defineRho(T rho_ ) {
  values[direction] = rho_;
}

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
void PressureBM<T,Lattice,direction,orientation>::defineU (
  Cell<T,Lattice>& cell,
  const T u_[Lattice<T>::d])
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    if (iD != direction) {
      values[iD] = u_[iD];
    }
  }
}

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
void PressureBM<T,Lattice,direction,orientation>::defineAllMomenta (
  Cell<T,Lattice>& cell,
  T rho_, const T u_[Lattice<T>::d],
  const T pi_[util::TensorVal<Lattice<T> >::n] )
{
  this->defineRhoU(cell, rho_, u_);
}

////////  FreeStressBM //////////////////////////////////////////////

template<typename T, template<typename U> class Lattice>
void FreeStressBM<T,Lattice>::computeStress (
  Cell<T,Lattice> const& cell,
  T rho, const T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  lbHelpers<T,Lattice>::computeStress(cell, rho, u, pi);
}



////////////////////// Class RegularizedBM //////////////////////

template<typename T, template<typename U> class Lattice,
         int direction, int orientation>
void RegularizedBM<T,Lattice,direction,orientation>::computeStress (
  Cell<T,Lattice> const& cell,
  T rho, const T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  BoundaryHelpers<T,Lattice,direction,orientation>::computeStress(cell, rho, u, pi);
}

////////////////////// Class FixedVelocityBM //////////////////////////

template<typename T, template<typename U> class Lattice>
T FixedVelocityBM<T,Lattice>::computeRho(Cell<T,Lattice> const& cell) const {
  return basicMomenta.computeRho(cell);
}

template<typename T, template<typename U> class Lattice>
void FixedVelocityBM<T,Lattice>::computeU(Cell<T,Lattice> const& cell, T u[Lattice<T>::d]) const
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    u[iD] = fixU[iD];
  }
}

template<typename T, template<typename U> class Lattice>
void FixedVelocityBM<T,Lattice>::computeJ(Cell<T,Lattice> const& cell, T j[Lattice<T>::d]) const
{
  T rho = computeRho(cell);
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    j[iD] = fixU[iD]*rho;
  }
}

template<typename T, template<typename U> class Lattice>
void FixedVelocityBM<T,Lattice>::computeStress (
  Cell<T,Lattice> const& cell,
  T rho, const T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  basicMomenta.computeStress(cell, rho, u, pi);
}

template<typename T, template<typename U> class Lattice>
void FixedVelocityBM<T,Lattice>::computeRhoU (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d] ) const
{
  rho = computeRho(cell);
  computeU(cell,u);
}

template<typename T, template<typename U> class Lattice>
void FixedVelocityBM<T,Lattice>::computeAllMomenta (
  Cell<T,Lattice> const& cell,
  T& rho, T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  basicMomenta.computeAllMomenta(cell, rho, u, pi);
  computeU(cell, u);
}

template<typename T, template<typename U> class Lattice>
void FixedVelocityBM<T,Lattice>::defineRho(Cell<T,Lattice>& cell, T rho) {
  basicMomenta.defineRho(cell, rho);
}

template<typename T, template<typename U> class Lattice>
void FixedVelocityBM<T,Lattice>::defineU (
  Cell<T,Lattice>& cell,
  const T u[Lattice<T>::d])
{
  for (int iD=0; iD<Lattice<T>::d; ++iD) {
    fixU[iD] = u[iD];
  }
}

template<typename T, template<typename U> class Lattice>
void FixedVelocityBM<T,Lattice>::defineRhoU (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d])
{
  defineRho(cell,rho);
  defineU(cell,u);
}

template<typename T, template<typename U> class Lattice>
void FixedVelocityBM<T,Lattice>::defineAllMomenta (
  Cell<T,Lattice>& cell,
  T rho, const T u[Lattice<T>::d],
  const T pi[util::TensorVal<Lattice<T> >::n] )
{
  basicMomenta.defineAllMomenta(cell, rho, u, pi);
  defineU(cell,u);
}



}  // namespace olb

#endif
