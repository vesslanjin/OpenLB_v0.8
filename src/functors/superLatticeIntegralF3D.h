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

#ifndef SUPER_LATTICE_INTEGRAL_F_3D_H
#define SUPER_LATTICE_INTEGRAL_F_3D_H

#include<vector>    // for generic i/o
#include<cmath>     // for lpnorm
#include<string>     // for lpnorm

#include "functors/genericF.h"
#include "functors/analyticalF.h"
#include "functors/indicatorF.h"
#include "functors/superLatticeBaseF3D.h"
#include "functors/superLatticeLocalF3D.h"
#include "complexGrids/cuboidStructure/superLattice3D.h"
#include "core/lbHelpers.h"  // for computation of lattice rho and velocity
//#include "io/stlReader.h"

/** Note: Throughout the whole source code directory genericFunctions, the
 *  template parameters for i/o dimensions are:
 *           F: S^m -> T^n  (S=source, T=target)
 */

namespace olb {



/// functor that returns the max in each component of all points of a certain material
template <typename T, template <typename U> class DESCRIPTOR>
class SuperMax : public SuperLatticeF3D<T,DESCRIPTOR> {
protected:
  SuperLatticeF3D<T,DESCRIPTOR>& f;
  SuperGeometry3D& superGeometry;
  int material;

public:
  SuperMax(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperGeometry3D& _superGeometry, int _material);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() {std::string tmp = "max("+f.name()+")"; return tmp; }
};


/// sums over all cells of a certain material number
template <typename T, template <typename U> class DESCRIPTOR>
class SuperSum3D : public SuperLatticeF3D<T,DESCRIPTOR> {
protected:
  SuperLatticeF3D<T,DESCRIPTOR>& f;
  SuperGeometry3D& superGeometry;
  int material;
public:
  SuperSum3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperGeometry3D& _superGeometry, int _material);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() {std::string tmp = "Sum("+f.name()+")"; return tmp; }
};


template <typename T, template <typename U> class DESCRIPTOR>
class SuperIntegral3D : public SuperLatticeF3D<T,DESCRIPTOR> {
protected:
  SuperLatticeF3D<T,DESCRIPTOR>& f;
  SuperGeometry3D& superGeometry;
  int material;
public:
  SuperIntegral3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperGeometry3D& _superGeometry, int _material);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() {std::string tmp = "Integral("+f.name()+")"; return tmp; }
};


/// functor that returns componentwise the l1 norm
template <typename T, template <typename U> class DESCRIPTOR>
class SuperL1Norm3D : public SuperLatticeF3D<T,DESCRIPTOR> {
protected:
  SuperLatticeF3D<T,DESCRIPTOR>& f;
  SuperGeometry3D& superGeometry;
  int material;
public:
  SuperL1Norm3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperGeometry3D& _superGeometry, int _material);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() {std::string tmp = "L1("+f.name()+")"; return tmp; }
};


/// functor that returns componentwise the squared l2-norm
template <typename T, template <typename U> class DESCRIPTOR>
class SuperL223D : public SuperLatticeF3D<T,DESCRIPTOR> {
protected:
  SuperLatticeF3D<T,DESCRIPTOR>& f;
  SuperGeometry3D& superGeometry;
  int material;
public:
  SuperL223D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperGeometry3D& _superGeometry, int _material);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() {std::string tmp = "L22("+f.name()+")"; return tmp; }
};


/// functor counts to get the discrete surface for a material no. in direction (1,0,0), (0,1,0), (0,0,1), (-1,0,0), (0,-1,0), (0,0,-1) and total surface, then it converts it into phys units
template <typename T>
class SuperGeometryFaces3D : public GenericF<T,int> {
  SuperGeometry3D& superGeometry;
  int material;
  const LBconverter<T>& converter;
public:
  SuperGeometryFaces3D(SuperGeometry3D& _superGeometry, int _material, const LBconverter<T>& _converter);
  std::vector<T> operator() (std::vector<int> input);
    std::string name() { return "superGeometryFaces"; }
};


///functor to get pointwise phys force acting on a boundary with a given 
/// material on local lattice, if globIC is not on
/// the local processor, the returned vector is empty
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticePhysDrag3D : public SuperLatticePhysF3D<T,DESCRIPTOR> {
private: 
  SuperGeometry3D& superGeometry;
  int material;

public:
  SuperLatticePhysDrag3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, SuperGeometry3D& _superGeometry, int _material, const LBconverter<T>& _converter);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() { return "physDrag"; }
};


/// functor to get pointwise phys force acting on a boundary with a given 
/// material on local lattice, if globIC is not on
/// the local processor, the returned vector is empty
/// see: Caiazzo, Junk: Boundary Forces in lattice Boltzmann: Analysis of MEA
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticePhysCorrDrag3D : public SuperLatticePhysF3D<T,DESCRIPTOR> {
private: 
  SuperGeometry3D& superGeometry;
  int material;

public:
  SuperLatticePhysCorrDrag3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, SuperGeometry3D& _superGeometry, int _material, const LBconverter<T>& _converter);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() { return "physCorrDrag"; }
};




} // end namespace olb

#endif
