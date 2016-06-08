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

#ifndef SUPER_LATTICE_CALC_F_3D_H
#define SUPER_LATTICE_CALC_F_3D_H

#include<vector>    // for generic i/o
#include<string>     // for lpnorm

#include "genericF.h"
#include "superLatticeBaseF3D.h"

/** Note: Throughout the whole source code directory genericFunctions, the
 *  template parameters for i/o dimensions are:
 *           F: S^m -> T^n  (S=source, T=target)
 */

namespace olb {


/// arithmetic helper class for SuperLatticeF3D functors
/** Warning: Allocation error possible in functors that have multiple functor evaluation like SuperSum3D */
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticeCalc3D : public SuperLatticeF3D< T, DESCRIPTOR > {
protected:
  SuperLatticeF3D<T,DESCRIPTOR>& f;
  SuperLatticeF3D<T,DESCRIPTOR>& g;
public:
  
  // set dimensions as well
  SuperLatticeCalc3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperLatticeF3D<T,DESCRIPTOR>& _g);
  std::string name() { return "SuperLatticeCalcF3D"; }
  virtual void myErase(GenericF<T,int>* ptr);
};


/// addition functor
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticePlus3D : public SuperLatticeCalc3D<T,DESCRIPTOR> {
public:
  SuperLatticePlus3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperLatticeF3D<T,DESCRIPTOR>& _g);
  std::vector<T> operator()(std::vector<int> input);
};


/// subtraction functor
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticeMinus3D : public SuperLatticeCalc3D<T,DESCRIPTOR> {
public:
  SuperLatticeMinus3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperLatticeF3D<T,DESCRIPTOR>& _g);
  std::vector<T> operator()(std::vector<int> input);
};


/// multiplication functor
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticeMultiplication3D : public SuperLatticeCalc3D<T,DESCRIPTOR> {
public:
  SuperLatticeMultiplication3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperLatticeF3D<T,DESCRIPTOR>& _g);
  std::vector<T> operator()(std::vector<int> input);
};


/// division functor
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticeDivision3D : public SuperLatticeCalc3D<T,DESCRIPTOR> {
public:
  SuperLatticeDivision3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperLatticeF3D<T,DESCRIPTOR>& _g);
  std::vector<T> operator()(std::vector<int> input);
};



} // end namespace olb

#endif
