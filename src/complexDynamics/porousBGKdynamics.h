/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Lukas Baron, Mathias J. Krause, Jonas Latt
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
 * BGK Dynamics for porous media -- header file.
 */
#ifndef POROUS_BGK_DYNAMICS_H
#define POROUS_BGK_DYNAMICS_H

#include "core/dynamics.h"
#include "core/cell.h"

namespace olb {

/// Implementation of the BGK collision step for a porosity model
template<typename T, template<typename U> class Lattice>
class PorousBGKdynamics : public BGKdynamics<T,Lattice> {
public:
  /// Constructor
  PorousBGKdynamics(T omega_, Momenta<T,Lattice>& momenta_);

  /// Collision step
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_);

/// get relaxation parameter
T    getOmega() const;
/// set relaxation parameter
void setOmega(T omega_);


private:
  T omega;      ///< relaxation parameter
  static const int porosityIsAt = Lattice<T>::ExternalField::porosityIsAt;
};


/// Implementation of the BGK collision step for a porosity model enabling
/// drag computation
template<typename T, template<typename U> class Lattice>
class ExtendedPorousBGKdynamics : public BGKdynamics<T,Lattice> {
public:
  /// Constructor
  ExtendedPorousBGKdynamics(T omega_, Momenta<T,Lattice>& momenta_);
  /// extended Collision step, computes local drag in a given direction
  virtual void collide(Cell<T,Lattice>& cell,
                       LatticeStatistics<T>& statistics_);
/// get relaxation parameter
T    getOmega() const;
/// set relaxation parameter
void setOmega(T omega_);


private:
  T omega;      ///< relaxation parameter
  static const int porosityIsAt      = Lattice<T>::ExternalField::
                                         porosityIsAt;
  static const int localDragBeginsAt = Lattice<T>::ExternalField::
                                         localDragBeginsAt;
  static const int sizeOfLocalDrag   = Lattice<T>::ExternalField::
                                         sizeOfLocalDrag;
};

} // olb

#endif
