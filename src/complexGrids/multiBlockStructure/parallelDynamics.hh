/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007, 2008 Jonas Latt
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
 * Parallel dynamics object -- generic template code
 */
#ifndef PARALLEL_DYNAMICS_HH
#define PARALLEL_DYNAMICS_HH

#include "complexGrids/mpiManager/mpiManager.h"
#include "parallelDynamics.h"

namespace olb {


#ifdef PARALLEL_MODE_MPI


////////////////////// Class ParallelDynamics /////////////////////////////

template<typename T, template<typename U> class Lattice>
ParallelDynamics<T,Lattice>::ParallelDynamics(std::vector<Cell<T,Lattice>*>& baseCells_, bool hasBulkCell_)
  : baseCells(baseCells_), hasBulkCell(hasBulkCell_)
{ }

template<typename T, template<typename U> class Lattice>
Dynamics<T,Lattice>* ParallelDynamics<T,Lattice>::clone() const {
  return new ParallelDynamics(baseCells, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
T ParallelDynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  T eq = T();
  if (hasBulkCell) {
    eq = baseCells[0] -> computeEquilibrium(iPop, rho, u, uSqr);
  }
  singleton::mpi().bCastThroughMaster(&eq, 1, hasBulkCell);
  return eq;
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::iniEquilibrium(Cell<T,Lattice>& cell, T rho, const T u[Lattice<T>::d]) {
  for (unsigned iCell=0; iCell<baseCells.size(); ++iCell) {
    baseCells[iCell] -> getDynamics() -> iniEquilibrium(*baseCells[iCell], rho, u);
  }
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::collide(Cell<T,Lattice>& cell, LatticeStatistics<T>& statistics_) {
  for (unsigned iCell=0; iCell<baseCells.size(); ++iCell) {
    baseCells[iCell] -> collide(statistics_);
  }
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell, const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics_ )
{
  for (unsigned iCell=0; iCell<baseCells.size(); ++iCell) {
    baseCells[iCell] -> staticCollide(u, statistics_);
  }
}

template<typename T, template<typename U> class Lattice>
T ParallelDynamics<T,Lattice>::computeRho(Cell<T,Lattice> const& cell) const {
  T rho = T();
  if (hasBulkCell) {
    rho = baseCells[0] -> computeRho();
  }
  singleton::mpi().bCastThroughMaster(&rho, 1, hasBulkCell);
  return rho;
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::computeU(Cell<T,Lattice> const& cell, T u[Lattice<T>::d] ) const
{
  if (hasBulkCell) {
    baseCells[0] -> computeU(u);
  }
  singleton::mpi().bCastThroughMaster(u, Lattice<T>::d, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::computeJ(Cell<T,Lattice> const& cell, T j[Lattice<T>::d] ) const
{
  if (hasBulkCell) {
    baseCells[0] -> getDynamics() -> computeJ(*baseCells[0], j);
  }
  singleton::mpi().bCastThroughMaster(j, Lattice<T>::d, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::computeStress (
  Cell<T,Lattice> const& cell, T rho, const T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  if (hasBulkCell) {
    baseCells[0] -> getDynamics() -> computeStress(*baseCells[0], rho, u, pi);
  }
  singleton::mpi().bCastThroughMaster(pi, util::TensorVal<Lattice<T> >::n, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::computeRhoU (
  Cell<T,Lattice> const& cell, T& rho, T u[Lattice<T>::d] ) const
{
  if (hasBulkCell) {
    baseCells[0] -> computeRhoU(rho, u);
  }
  singleton::mpi().bCastThroughMaster(&rho, 1, hasBulkCell);
  singleton::mpi().bCastThroughMaster(u, Lattice<T>::d, hasBulkCell);
}


template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::computeAllMomenta (
  Cell<T,Lattice> const& cell, T& rho, T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  if (hasBulkCell) {
    baseCells[0] -> computeAllMomenta(rho, u, pi);
  }
  singleton::mpi().bCastThroughMaster(&rho, 1, hasBulkCell);
  singleton::mpi().bCastThroughMaster(u, Lattice<T>::d, hasBulkCell);
  singleton::mpi().bCastThroughMaster(pi, util::TensorVal<Lattice<T> >::n, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::computePopulations(Cell<T,Lattice> const& cell, T* f) const
{
  if (hasBulkCell) {
    baseCells[0] -> computePopulations(f);
  }
  singleton::mpi().bCastThroughMaster(f, Lattice<T>::q, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::computeExternalField (
  Cell<T,Lattice> const& cell, int pos, int size, T* ext ) const
{
  if (hasBulkCell) {
    baseCells[0] -> computeExternalField(pos, size, ext);
  }
  singleton::mpi().bCastThroughMaster(ext, Lattice<T>::ExternalField::numScalars, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::defineRho(Cell<T,Lattice>& cell, T rho) {
  for (unsigned iCell=0; iCell<baseCells.size(); ++iCell) {
    baseCells[iCell] -> defineRho(rho);
  }
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::defineU(Cell<T,Lattice>& cell, const T u[Lattice<T>::d]) {
  for (unsigned iCell=0; iCell<baseCells.size(); ++iCell) {
    baseCells[iCell] -> defineU(u);
  }
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::defineRhoU(Cell<T,Lattice>& cell, T rho, const T u[Lattice<T>::d]) {
  for (unsigned iCell=0; iCell<baseCells.size(); ++iCell) {
    baseCells[iCell] -> defineRhoU(rho, u);
  }
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::defineAllMomenta (
  Cell<T,Lattice>& cell, T rho, const T u[Lattice<T>::d],
  const T pi[util::TensorVal<Lattice<T> >::n] )
{
  for (unsigned iCell=0; iCell<baseCells.size(); ++iCell) {
    baseCells[iCell] -> defineAllMomenta(rho, u, pi);
  }
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::definePopulations(Cell<T,Lattice>& cell, const T* f)
{
  for (unsigned iCell=0; iCell<baseCells.size(); ++iCell) {
    baseCells[iCell] -> definePopulations(f);
  }
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::defineExternalField (
  Cell<T,Lattice>& cell, int pos, int size, const T* ext )
{
  for (unsigned iCell=0; iCell<baseCells.size(); ++iCell) {
    baseCells[iCell] -> defineExternalField(pos, size, ext);
  }
}

template<typename T, template<typename U> class Lattice>
T ParallelDynamics<T,Lattice>::getParameter(int whichParameter) const {
  T parameter = T();
  if (hasBulkCell) {
    parameter = baseCells[0] -> getDynamics() -> getParameter(whichParameter);
  }
  singleton::mpi().bCastThroughMaster(&parameter, 1, hasBulkCell);
  return parameter;
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::setParameter(int whichParameter, T value) {
  for (unsigned iCell=0; iCell<baseCells.size(); ++iCell) {
    baseCells[iCell] -> getDynamics() -> setParameter(whichParameter, value);
  }
}

template<typename T, template<typename U> class Lattice>
T ParallelDynamics<T,Lattice>::getOmega() const {
  T omega = T();
  if (hasBulkCell) {
    omega = baseCells[0] -> getDynamics() -> getOmega();
  }
  singleton::mpi().bCastThroughMaster(&omega, 1, hasBulkCell);
  return omega;
}

template<typename T, template<typename U> class Lattice>
void ParallelDynamics<T,Lattice>::setOmega(T omega_) {
  for (unsigned iCell=0; iCell<baseCells.size(); ++iCell) {
    baseCells[iCell] -> getDynamics() -> setOmega(omega_);
  }
}

////////////////// Class ConstParallelDynamics /////////////////////////

template<typename T, template<typename U> class Lattice>
ConstParallelDynamics<T,Lattice>::ConstParallelDynamics(std::vector<Cell<T,Lattice> const*>& baseCells_,
    bool hasBulkCell_)
  : baseCells(baseCells_), hasBulkCell(hasBulkCell_)
{ }

template<typename T, template<typename U> class Lattice>
Dynamics<T,Lattice>* ConstParallelDynamics<T,Lattice>::clone() const {
  return new ConstParallelDynamics(baseCells, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
T ConstParallelDynamics<T,Lattice>::computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const
{
  T eq = T();
  if (hasBulkCell) {
    eq = baseCells[0] -> computeEquilibrium(iPop, rho, u, uSqr);
  }
  singleton::mpi().bCastThroughMaster(&eq, 1, hasBulkCell);
  return eq;
}

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::iniEquilibrium(Cell<T,Lattice>& cell, T rho, const T u[Lattice<T>::d])
{ }

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::collide(Cell<T,Lattice>& cell,
    LatticeStatistics<T>& statistics_)
{ }

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::staticCollide (
  Cell<T,Lattice>& cell, const T u[Lattice<T>::d],
  LatticeStatistics<T>& statistics_ )
{ }

template<typename T, template<typename U> class Lattice>
T ConstParallelDynamics<T,Lattice>::computeRho(Cell<T,Lattice> const& cell) const {
  T rho = T();
  if (hasBulkCell) {
    rho = baseCells[0] -> computeRho();
  }
  singleton::mpi().bCastThroughMaster(&rho, 1, hasBulkCell);
  return rho;
}

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::computeU(Cell<T,Lattice> const& cell, T u[Lattice<T>::d] ) const
{
  if (hasBulkCell) {
    baseCells[0] -> computeU(u);
  }
  singleton::mpi().bCastThroughMaster(u, Lattice<T>::d, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::computeJ(Cell<T,Lattice> const& cell, T j[Lattice<T>::d] ) const
{
  if (hasBulkCell) {
    baseCells[0] -> getDynamics() -> computeJ(*baseCells[0], j);
  }
  singleton::mpi().bCastThroughMaster(j, Lattice<T>::d, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::computeStress (
  Cell<T,Lattice> const& cell, T rho, const T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  if (hasBulkCell) {
    baseCells[0] -> getDynamics() -> computeStress(*baseCells[0], rho, u, pi);
  }
  singleton::mpi().bCastThroughMaster(pi, util::TensorVal<Lattice<T> >::n, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::computeRhoU (
  Cell<T,Lattice> const& cell, T& rho, T u[Lattice<T>::d] ) const
{
  if (hasBulkCell) {
    baseCells[0] -> computeRhoU(rho, u);
  }
  singleton::mpi().bCastThroughMaster(&rho, 1, hasBulkCell);
  singleton::mpi().bCastThroughMaster(u, Lattice<T>::d, hasBulkCell);
}


template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::computeAllMomenta (
  Cell<T,Lattice> const& cell, T& rho, T u[Lattice<T>::d],
  T pi[util::TensorVal<Lattice<T> >::n] ) const
{
  if (hasBulkCell) {
    baseCells[0] -> computeAllMomenta(rho, u, pi);
  }
  singleton::mpi().bCastThroughMaster(&rho, 1, hasBulkCell);
  singleton::mpi().bCastThroughMaster(u, Lattice<T>::d, hasBulkCell);
  singleton::mpi().bCastThroughMaster(pi, util::TensorVal<Lattice<T> >::n, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::computePopulations(Cell<T,Lattice> const& cell, T* f) const
{
  if (hasBulkCell) {
    baseCells[0] -> computePopulations(f);
  }
  singleton::mpi().bCastThroughMaster(f, Lattice<T>::q, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::computeExternalField (
  Cell<T,Lattice> const& cell, int pos, int size, T* ext ) const
{
  if (hasBulkCell) {
    baseCells[0] -> computeExternalField(pos, size, ext);
  }
  singleton::mpi().bCastThroughMaster(ext, Lattice<T>::ExternalField::numScalars, hasBulkCell);
}

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::defineRho(Cell<T,Lattice>& cell, T rho)
{ }

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::defineU(Cell<T,Lattice>& cell, const T u[Lattice<T>::d])
{ }

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::defineRhoU(Cell<T,Lattice>& cell, T rho, const T u[Lattice<T>::d])
{ }

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::defineAllMomenta (
  Cell<T,Lattice>& cell, T rho, const T u[Lattice<T>::d],
  const T pi[util::TensorVal<Lattice<T> >::n] )
{ }

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::definePopulations (
  Cell<T,Lattice>& cell, const T* f)
{ }

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::defineExternalField (
  Cell<T,Lattice>& cell, int pos, int size, const T* ext )
{ }

template<typename T, template<typename U> class Lattice>
T ConstParallelDynamics<T,Lattice>::getParameter(int whichParameter) const {
  T parameter = T();
  if (hasBulkCell) {
    parameter = baseCells[0] -> getDynamics() -> getParameter(whichParameter);
  }
  singleton::mpi().bCastThroughMaster(&parameter, 1, hasBulkCell);
  return parameter;
}

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::setParameter(int whichParameter, T value)
{ }

template<typename T, template<typename U> class Lattice>
T ConstParallelDynamics<T,Lattice>::getOmega() const {
  T omega = T();
  if (hasBulkCell) {
    omega = baseCells[0] -> getDynamics() -> getOmega();
  }
  singleton::mpi().bCastThroughMaster(&omega, 1, hasBulkCell);
  return omega;
}

template<typename T, template<typename U> class Lattice>
void ConstParallelDynamics<T,Lattice>::setOmega(T omega_)
{ }

#endif


}

#endif // defined MULTIBLOCK_DYNAMICS_H
