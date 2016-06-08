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

#ifndef INTERPOLATION_F_3D_H
#define INTERPOLATION_F_3D_H


#include<vector>    // for generic i/o
#include<string>     // for lpnorm

#include "analyticalF.h"
#include "complexGrids/cuboidStructure/superLattice3D.h"
#include "complexGrids/cuboidStructure/superGeometry3D.h"
#include "complexGrids/cuboidStructure/cuboidGeometry3D.h"
#include "core/lbHelpers.h"  // for computation of lattice rho and velocity

namespace olb {


/// a class used to convert lattice functions to analytical functions
template <typename T, template <typename U> class DESCRIPTOR>
class AnalyticalFfromSuperLatticeF3D : public AnalyticalF3D<T,T> {
protected:
  SuperLatticeF3D<T,DESCRIPTOR>&  f;
  SuperGeometry3D&                sg;
  CuboidGeometry3D<T>&            cg;
  bool                            communicateToAll;
  int                             overlap;
public:
  AnalyticalFfromSuperLatticeF3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperGeometry3D& _sg, bool _communicateToAll=false, int _overlap=2);

  std::vector<T> operator() (std::vector<T> physC);
  std::string name() { return "fromSuperLatticeF"; }
};


/// a class used to convert analytical functions to lattice functions
/// input functions are interpreted as SI->SI units, the resulting lattice
/// function will map lattice->lattice units
template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticeFfromAnalyticalF3D : public SuperLatticeF3D<T,DESCRIPTOR> {
protected:
  AnalyticalF3D<T,T>&  f;
  SuperGeometry3D& sg;
  CuboidGeometry3D<T>& cg;
  //const LBconverter<T>&      converter;
public:
  SuperLatticeFfromAnalyticalF3D(AnalyticalF3D<T,T>& _f, SuperLattice3D<T,DESCRIPTOR>& _sLattice, SuperGeometry3D& _sg, CuboidGeometry3D<T>& _cg);

  std::vector<T> operator() (std::vector<int> input);
  std::string name() { return "fromAnalyticalF";}
};



} // end namespace olb

#endif
