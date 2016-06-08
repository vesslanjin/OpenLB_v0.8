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

#ifndef SUPER_LATTICE_LOCAL_F_3D_H
#define SUPER_LATTICE_LOCAL_F_3D_H

#include<vector>    // for generic i/o
#include<string>

#include "superLatticeBaseF3D.h"
#include "complexGrids/cuboidStructure/superLattice3D.h"

/** Note: Throughout the whole source code directory genericFunctions, the
 *  template parameters for i/o dimensions are:
 *           F: S^m -> T^n  (S=source, T=target)
 */

namespace olb {


/// functor to get pointwise dissipation density on local lattices, if globIC is not on
/// the local processor, the returned vector is empty
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticeDissipation3D : public SuperLatticeF3D<T,DESCRIPTOR> {
protected:
  const LBconverter<T>& converter;
public:
  SuperLatticeDissipation3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, const LBconverter<T>& _converter);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() { return "dissipation"; }
};


/// functor to get pointwise density rho on local lattices, if globIC is not on
/// the local processor, the returned vector is empty
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticeDensity3D : public SuperLatticeF3D<T,DESCRIPTOR> {
public:
  SuperLatticeDensity3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() { return "density"; }
};


/// functor to get pointwise velocity on local lattice, if globIC is not on
/// the local processor, the returned vector is empty
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticeVelocity3D : public SuperLatticeF3D<T,DESCRIPTOR> {
public:
  SuperLatticeVelocity3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() { return "velocity"; }
};


/// functor to get pointwise the material no. presenting the geometry on local lattice, if globIC is not on
/// the local processor, the returned vector is empty
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticeGeometry3D : public SuperLatticeF3D<T,DESCRIPTOR> {
  SuperGeometry3D& superGeometry;
public:
  SuperLatticeGeometry3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, SuperGeometry3D& _superGeometry);
    std::vector<T> operator() (std::vector<int> input);
  std::string name() { return "geometry"; }
};


/// functor to get pointwise the rank no. + 1 on local lattice, if globIC is not on
/// the local processor, the returned vector is empty
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticeRank3D : public SuperLatticeF3D<T,DESCRIPTOR> {
public:
  SuperLatticeRank3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() { return "rank"; }
};


/// functor to get pointwise the cuboid no. + 1 on local lattice, if globIC is not on
/// the local processor, the returned vector is empty
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticeCuboid3D : public SuperLatticeF3D<T,DESCRIPTOR> {
public:
  SuperLatticeCuboid3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() { return "cuboid"; }
};


/// functor to get pointwise phys pressure from rho on local lattices, if globIC is not on
/// the local processor, the returned vector is empty
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticePhysPressure3D : public SuperLatticePhysF3D<T,DESCRIPTOR> {
public:
  SuperLatticePhysPressure3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, const LBconverter<T>& _converter);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() { return "physPressure"; }
};


/// functor to get pointwise phys velocity on local lattice, if globIC is not on
/// the local processor, the returned vector is empty
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticePhysVelocity3D : public SuperLatticePhysF3D<T,DESCRIPTOR> {
public:
  SuperLatticePhysVelocity3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, const LBconverter<T>& _converter);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() { return "physVelocity"; }
};


/// functor to get pointwise phys force acting on a boundary with a given 
/// material on local lattice, if globIC is not on
/// the local processor, the returned vector is empty
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticePhysBoundaryForce3D : public SuperLatticePhysF3D<T,DESCRIPTOR> {
private: 
  SuperGeometry3D& superGeometry;
  int material;

public:
  SuperLatticePhysBoundaryForce3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, SuperGeometry3D& _superGeometry, int _material, const LBconverter<T>& _converter);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() { return "physBoundaryForce"; }
};


/// functor to get pointwise phys force acting on a boundary with a given 
/// material on local lattice, if globIC is not on
/// the local processor, the returned vector is empty
/// see: Caiazzo, Junk: Boundary Forces in lattice Boltzmann: Analysis of MEA
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticePhysCorrBoundaryForce3D : public SuperLatticePhysF3D<T,DESCRIPTOR> {
private: 
  SuperGeometry3D& superGeometry;
  int material;

public:
  SuperLatticePhysCorrBoundaryForce3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, SuperGeometry3D& _superGeometry, int _material, const LBconverter<T>& _converter);

  std::vector<T> operator() (std::vector<int> input);
  std::string name() { return "physCorrBoundaryForce"; }
};


/// functor to get pointwise, lattice-dependent porosity values in [0,1]
/// in combination with (Extended)PorousBGKdynamics: 0->solid, 1->fluid
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticePorosity3D : public SuperLatticePhysF3D<T,DESCRIPTOR> {
private:
  SuperGeometry3D& superGeometry;
  int material;
public:
  SuperLatticePorosity3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice,
                       SuperGeometry3D& _superGeometry,
                       int _material,
                       const LBconverter<T>& _converter);
  std::vector<T> operator()(std::vector<int> input);

  std::string name() { return "porosity"; }
};


/// functor to get pointwise mesh-independent permeability values in (0,inf)
/// in combination with (Extended)PorousBGKdynamics
/// note: result is cropped to 999999
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticePhysPermeability3D : public SuperLatticePhysF3D<T,DESCRIPTOR> {
private:
  SuperGeometry3D& superGeometry;
  int material;
public:
  SuperLatticePhysPermeability3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice,
                                 SuperGeometry3D& _superGeometry,
                                 int _material,
                                 const LBconverter<T>& _converter);
  std::vector<T> operator()(std::vector<int> input);
  std::string name() { return "permeability"; }
};


/// computes pointwise -nu/K*u on the lattice, can be used with SuperSum3D as objective
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticePhysDarcyForce3D : public SuperLatticePhysF3D<T,DESCRIPTOR> {
private:
  SuperGeometry3D& superGeometry;
  int material;
public:
  SuperLatticePhysDarcyForce3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice,
                               SuperGeometry3D& _superGeometry,
                               int _material,
                               const LBconverter<T>& _converter);
  std::vector<T> operator()(std::vector<int> input);
  std::string name() { return "alphaU"; }
};


/// functor to get a pointwise local average of a passed functor with a given
/// material and radius on local lattice, if globIC is not on
/// the local processor, the returned vector is empty
/// the output data must be of the same size and dimension like f
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticeAverage3D : public SuperLatticeF3D<T,DESCRIPTOR> {
private:
  SuperLatticeF3D<T,DESCRIPTOR>& f;
  SuperGeometry3D& superGeometry;
  int material;
  T radius;

public:
  SuperLatticeAverage3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperGeometry3D& _superGeometry, int _material, T _radius);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() {std::string tmp = "Average("+f.name()+")"; return tmp; }
};


/// functor that returns pointwise the l2-norm, e.g. of a velocity
template <typename T, template <typename U> class DESCRIPTOR>
class SuperL2Norm3D : public SuperLatticeF3D<T,DESCRIPTOR> {
protected:
  SuperLatticeF3D<T,DESCRIPTOR>& f;
public:
  SuperL2Norm3D(SuperLatticeF3D<T,DESCRIPTOR>& _f);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() {std::string tmp = "l2("+f.name()+")"; return tmp; }
};



} // end namespace olb

#endif
