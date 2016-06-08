/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2013 Lukas Baron, Mathias J. Krause
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

#ifndef INDICATOR_F_H
#define INDICATOR_F_H

#include<vector>    // for generic i/o
#include<cmath>     // for lpnorm
#include "analyticalF.h"
#include "io/stlReader.h"

/** \file
 * This file contains analytical indicator functions. These return 1 if the given coordinates are inside, and 0 if they are outside of the defined set. Implemented are:
 - Sphere
 - Cylinder (not yet)
 - Pipe (not yet)
 - Cube (not yet)
 - Cuboid (not yet)
 Boolean operators allow to create unions and intersections. They can be used for example for initialization of a SuperGeometry.
*/

namespace olb {

/// Indicator function for a 1d-sphere, returns 1 if ||x-center||_2<=radius, else 0
template <typename T, typename S>
class SphereAnalyticalF1D : public AnalyticalF3D<T,S> {
private:
  std::vector<S> _center;
  S _radius2;
public:
  SphereAnalyticalF1D(std::vector<S> center, S radius);
  std::vector<T> operator()(std::vector<S> x);
};

/// indicator function for a circle orthogonal to the z-axis
template <typename T, typename S>
class SphereAnalyticalF2D : public AnalyticalF3D<T,S> {
private:
  std::vector<S> _center;
  S _radius2;
public:
  SphereAnalyticalF2D(std::vector<S> center, S radius);
  std::vector<T> operator()(std::vector<S> x);
};

/// indicator function for a 3d-sphere
template <typename T, typename S>
class SphereAnalyticalF3D : public AnalyticalF3D<T,S> {
private:
  std::vector<S> _center;
  S _radius2;
public:
  SphereAnalyticalF3D(std::vector<S> center, S radius);
  std::vector<T> operator()(std::vector<S> x);
};


/// indicator function for a ellipse orthogonal to the z-axis
template <typename T, typename S>
class EllipseAnalyticalF2D : public AnalyticalF3D<T,S> {
private:
  std::vector<S> _center;
  S _a2, _b2;
public:
  EllipseAnalyticalF2D(std::vector<S> center, S a, S b);
  std::vector<T> operator()(std::vector<S> input);
};


/// indicator function for a 3d-cylinder
/** parameters are center of the base circle, normal of the circle plane, radius of the circle and the thickness in both directions (i.e. the cylinder actually has twice the thickness)
*/
template <typename T, typename S>
class CylinderAnalyticalF3D : public AnalyticalF3D<T,S> {
private:
  std::vector<S> _center;
  std::vector<S> _normal;
  S _radius;
  S _thickness;
public:
  CylinderAnalyticalF3D(std::vector<S> center, std::vector<S> normal, S radius, S thickness);
  /// normalizes an arbitrary vector
  std::vector<S> normalize(std::vector<S> vec);
  /// cross product, only valid in 3d
  std::vector<S> crossProduct3D(std::vector<S> a, std::vector<S> b);
  /// l2 norm of a vector
  std::vector<S> vectorNorm(std::vector<S> a);
  /// Access operator
  std::vector<T> operator()(std::vector<S> x);
};

/// indicator function for an object given by an stl file
template <typename T, typename S>
class StlIndicatorF3D : public AnalyticalF3D<T,S> {
private:
  STLreader<S>& stlReader;
  S eps;
public:
  StlIndicatorF3D(STLreader<S>& _stlReader, S _eps);
  std::vector<T> operator()(std::vector<S> x);
};

}

#endif
