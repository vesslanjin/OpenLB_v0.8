/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2013 Patrick Nathen, Mathias J. Krause
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

#ifndef TURBULENT_F_3D_H
#define TURBULENT_F_3D_H

#include<vector>
#include<cmath>  
#include<string> 

#include "functors/genericF.h"
#include "functors/analyticalF.h"
#include "functors/superLatticeBaseF3D.h"
#include "complexGrids/cuboidStructure/superLattice3D.h"
#include "core/lbHelpers.h"  // for computation of lattice rho and velocity
#include "io/stlReader.h"

/** To enable simulations in a rotating frame, the axis is set in the
  * constructor with axisPoint and axisDirection. The axisPoint can be the
  * coordinate of any point where the axis pass. The axisDirection has to,
  * be a normal. The pulse w is in rad/s. It determines the pulse speed by
  * its norm while the trigonometric or clockwise direction is determined by
  * its sign: when the axisDirection is pointing "toward you", a
  * positive pulse make it turn in the trigonometric way. It has to be noted
  * that putting both axisDirection into -axisDirection and w into -w yields 
  * an exactly identical situation.
  */

namespace olb {

/**
  * This functor gives a linar profile for a given point x as it computes
  * the distance between x and the axis.

  * To simulate the rotation, the axis is set in the input with axisPoint and axisDirection. The axisPoint can be the coordinate of any point yhere the axis pass. axisDirection has to be normed to 1.
  * The pulse is in rad/s. It determines the pulse speed by its norm while the trigonometric or clockwise direction is determined by its sign: when the axisDirection is pointing "toward you", a positive pulse make it turn in the trigonometric way. It has to be noticed that putting both axisDirection into -axisDirection and w into -w brings to an exactly identical situation.

  * The field in outcome is the velocity field of q rotqting solid 
  */

/// functor to get pointwise yPlus from rho, shear stress and local density on local lattices, if globIC is not on
/// the local processor, the returned vector is empty


template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticeYplus3D : public SuperLatticePhysF3D<T,DESCRIPTOR> {
// class SuperLatticeQCrit3D : public SuperLatticePhysInterpF3D<T,DESCRIPTOR> {
private:
  SuperGeometry3D& superGeometry;
  STLreader<T>& stlReader;
  int material;
public:
  SuperLatticeYplus3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, const LBconverter<T>& _converter,
                      SuperGeometry3D& _superGeometry, STLreader<T>& _stlReader, int _material );
  std::vector<T> operator() (std::vector<int> input);
  std::string name() {return "yPlus";}
};


template <typename T, template <typename U> class DESCRIPTOR>
class SuperLatticeQCrit3D : public SuperLatticePhysF3D<T,DESCRIPTOR> {
private:
  SuperGeometry3D& superGeometry;
public:
  SuperLatticeQCrit3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, LBconverter<T>& _converter, SuperGeometry3D& sg);
  std::vector<T> operator() (std::vector<int> input);
  std::string name() {return "qCrit"; }
};



} // end namespace olb

#endif


