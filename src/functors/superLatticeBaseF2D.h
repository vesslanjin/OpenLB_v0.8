/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Lukas Baron, Tim Dornieden, Mathias J. Krause,
 *  Albert Mink
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

#ifndef SUPER_LATTICE_BASE_F_2D_H
#define SUPER_LATTICE_BASE_F_2D_H

#include<vector>    // for generic i/o
#include<string>     // for lpnorm

#include "genericF.h"
#include "complexGrids/cuboidStructure/superLattice2D.h"
#include "core/units.h"

/** Note: Throughout the whole source code directory genericFunctions, the
 *  template parameters for i/o dimensions are:
 *           F: S^m -> T^n  (S=source, T=target)
 */

namespace olb {

template<typename T, template<typename U> class Lattice> class SuperLattice2D;
template<typename T, template<typename U> class Lattice> class SuperLatticeF2D;


/// represents all functors that operate on a Lattice in general,
/// e.g. getVelocity(), getForce(), getPressure()
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticeF2D : public GenericF<T,int> {
protected:
  SuperLattice2D<T,DESCRIPTOR>& sLattice;
public:
  SuperLatticeF2D(SuperLattice2D<T,DESCRIPTOR>& _sLattice, int targetDim);

  SuperLatticeF2D<T,DESCRIPTOR>& operator-(SuperLatticeF2D<T,DESCRIPTOR>& rhs);
  SuperLatticeF2D<T,DESCRIPTOR>& operator+(SuperLatticeF2D<T,DESCRIPTOR>& rhs);
  SuperLatticeF2D<T,DESCRIPTOR>& operator*(SuperLatticeF2D<T,DESCRIPTOR>& rhs);
  SuperLatticeF2D<T,DESCRIPTOR>& operator/(SuperLatticeF2D<T,DESCRIPTOR>& rhs);

  virtual std::string name() = 0;
  SuperLattice2D<T,DESCRIPTOR>& getSuperLattice2D() { return sLattice; }
};


/// represents all functors that operate on a Lattice with output in Phys,
/// e.g. physVelocity(), physForce(), physPressure()
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticePhysF2D : public SuperLatticeF2D<T,DESCRIPTOR> {
protected:
  const LBconverter<T>&      converter;
public:
  SuperLatticePhysF2D(SuperLattice2D<T,DESCRIPTOR>& _sLattice, const LBconverter<T>& _converter, int targetDim); 
  virtual std::string name() = 0;
};



} // end namespace olb

#endif
