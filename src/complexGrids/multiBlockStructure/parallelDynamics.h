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
 * Parallel dynamics object -- header file.
 */

#ifndef PARALLEL_DYNAMICS_H
#define PARALLEL_DYNAMICS_H

#include "core/postProcessing.h"
#include "core/dynamics.h"
#include "core/cell.h"


namespace olb {

#ifdef PARALLEL_MODE_MPI

template<typename T, template<typename U> class Lattice>
class ParallelDynamics : public Dynamics<T,Lattice> {
public:
  ParallelDynamics(std::vector<Cell<T,Lattice>*>& baseCells_, bool hasBulkCell_);
  virtual Dynamics<T,Lattice>* clone() const;
  virtual T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const;
  virtual void iniEquilibrium(Cell<T,Lattice>& cell, T rho, const T u[Lattice<T>::d]);
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_);
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics_);
  virtual T computeRho(Cell<T,Lattice> const& cell) const;
  virtual void computeU( Cell<T,Lattice> const& cell,
                         T u[Lattice<T>::d] ) const;
  virtual void computeJ( Cell<T,Lattice> const& cell,
                         T j[Lattice<T>::d] ) const;
  virtual void computeStress( Cell<T,Lattice> const& cell,
                              T rho, const T u[Lattice<T>::d],
                              T pi[util::TensorVal<Lattice<T> >::n] ) const;
  virtual void computeRhoU( Cell<T,Lattice> const& cell,
                            T& rho, T u[Lattice<T>::d] ) const;
  virtual void computeAllMomenta( Cell<T,Lattice> const& cell,
                                  T& rho, T u[Lattice<T>::d],
                                  T pi[util::TensorVal<Lattice<T> >::n] ) const;
  virtual void computePopulations(Cell<T,Lattice> const& cell, T* f) const;
  virtual void computeExternalField (
    Cell<T,Lattice> const& cell, int pos, int size, T* ext ) const;
  virtual void defineRho(Cell<T,Lattice>& cell, T rho);
  virtual void defineU(Cell<T,Lattice>& cell,
                       const T u[Lattice<T>::d]);
  virtual void defineRhoU( Cell<T,Lattice>& cell,
                           T rho, const T u[Lattice<T>::d]);
  virtual void defineAllMomenta( Cell<T,Lattice>& cell,
                                 T rho, const T u[Lattice<T>::d],
                                 const T pi[util::TensorVal<Lattice<T> >::n] );
  virtual void definePopulations(Cell<T,Lattice>& cell, const T* f);
  virtual void defineExternalField(Cell<T,Lattice>& cell, int pos, int size, const T* ext);
  virtual T getOmega() const;
  virtual void setOmega(T omega_);
  virtual T getParameter(int whichParameter) const;
  virtual void setParameter(int whichParameter, T value);
private:
  std::vector<Cell<T,Lattice>*>& baseCells;
  bool hasBulkCell;
};

template<typename T, template<typename U> class Lattice>
class ConstParallelDynamics : public Dynamics<T,Lattice> {
public:
  ConstParallelDynamics(std::vector<Cell<T,Lattice> const*>& baseCells_, bool hasBulkCell_);
  virtual Dynamics<T,Lattice>* clone() const;
  virtual T computeEquilibrium(int iPop, T rho, const T u[Lattice<T>::d], T uSqr) const;
  virtual void iniEquilibrium(Cell<T,Lattice>& cell, T rho, const T u[Lattice<T>::d]);
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_);
  virtual void staticCollide(Cell<T,Lattice>& cell,
                             const T u[Lattice<T>::d],
                             LatticeStatistics<T>& statistics_);
  virtual T computeRho(Cell<T,Lattice> const& cell) const;
  virtual void computeU( Cell<T,Lattice> const& cell,
                         T u[Lattice<T>::d] ) const;
  virtual void computeJ( Cell<T,Lattice> const& cell,
                         T j[Lattice<T>::d] ) const;
  virtual void computeStress( Cell<T,Lattice> const& cell,
                              T rho, const T u[Lattice<T>::d],
                              T pi[util::TensorVal<Lattice<T> >::n] ) const;
  virtual void computeRhoU( Cell<T,Lattice> const& cell,
                            T& rho, T u[Lattice<T>::d] ) const;
  virtual void computeAllMomenta( Cell<T,Lattice> const& cell,
                                  T& rho, T u[Lattice<T>::d],
                                  T pi[util::TensorVal<Lattice<T> >::n] ) const;
  virtual void computePopulations(Cell<T,Lattice> const& cell, T* f) const;
  virtual void computeExternalField (
    Cell<T,Lattice> const& cell, int pos, int size, T* ext ) const;
  virtual void defineRho(Cell<T,Lattice>& cell, T rho);
  virtual void defineU(Cell<T,Lattice>& cell,
                       const T u[Lattice<T>::d]);
  virtual void defineRhoU( Cell<T,Lattice>& cell,
                           T rho, const T u[Lattice<T>::d]);
  virtual void defineAllMomenta( Cell<T,Lattice>& cell,
                                 T rho, const T u[Lattice<T>::d],
                                 const T pi[util::TensorVal<Lattice<T> >::n] );
  virtual void definePopulations(Cell<T,Lattice>& cell, const T* f);
  virtual void defineExternalField (
    Cell<T,Lattice>& cell, int pos, int size, const T* ext);
  virtual T getOmega() const;
  virtual void setOmega(T omega_);
  virtual T getParameter(int whichParameter) const;
  virtual void setParameter(int whichParameter, T value);
private:
  std::vector<Cell<T,Lattice> const*>& baseCells;
  bool hasBulkCell;
};

#endif // PARALLEL_MODE_MPI

}

#endif // defined PARALLEL_DYNAMICS_H
