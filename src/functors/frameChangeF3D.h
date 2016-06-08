/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2013 Gilles Zahnd, Mathias J. Krause
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

#ifndef FRAME_CHANGE_F_3D_H
#define FRAME_CHANGE_F_3D_H

#include<vector>
#include<cmath>
#include<string>
#include"math.h"

#include "functors/genericF.h"
#include "functors/analyticalF.h"
#include "functors/superLatticeBaseF3D.h"
#include "functors/superLatticeLocalF3D.h"
#include "complexGrids/cuboidStructure/superLattice3D.h"

/** \file
  This file contains two different classes of functors, in the FIRST part
  - for simulations in a rotating frame
  - different functors for
      velocity (3d, RotatingLinear3D),
      pressure (1d, RotatingQuadratic1D) and
      force    (3d, RotatingForceField3D)
  The functors return the displacement of a point x in a fixed amount of time.

  The ones in the SECOND part are useful to set Poiseuille velocity profiles on
  - pipes with round cross-section and
  - pipes with square-shaped cross-section.
*/

/** To enable simulations in a rotating frame, the axis is set in the
  * constructor with axisPoint and axisDirection. The axisPoint can be the
  * coordinate of any point on the axis. The axisDirection has to be a normed to
  * 1. The pulse w is in rad/s. It determines the pulse speed by its norm while
  * the trigonometric or clockwise direction is determined by its sign: When the
  * axisDirection is pointing "towards you", a positive pulse makes it turn in
  * the trigonometric way. It has to be noticed that putting both axisDirection
  * into -axisDirection and w into -w yields an exactly identical situation.
  */


namespace olb {


// PART 1: /////////////////////////////////////////////////////////////////////
// Functors for rotating the coordinate system (velocity, pressure, force,...)

/**
  * This functor gives a linar profile for a given point x as it computes
  * the distance between x and the axis.
  *
  * The field in outcome is the velocity field of q rotating solid
  */

/// Functor with a linear profile e.g. for rotating velocity fields.
template <typename T>
class RotatingLinear3D : public AnalyticalF3D<T,T> {
protected:
  std::vector<T> axisPoint;
  std::vector<T> axisDirection;
  T w;
  T scale;
public:
  RotatingLinear3D(std::vector<T> axisPoint_, std::vector<T> axisDirection_, T w_, T scale_=1);
  std::vector<T> operator()(std::vector<T> x);
};



/**
  * This functor gives a parabolic profile for a given point x as it computes
  * the distance between x and the axis.
  *
  * This field is a scalar field, a vector with one component will be used
  */

/// Functor with a parabolic profile e.g. for rotating pressure fields.
template <typename T>
class RotatingQuadratic1D : public AnalyticalF3D<T,T> {
protected:
  std::vector<T> axisPoint;
  std::vector<T> axisDirection;
  T w;
  T scale;
  T additive;
public:
  RotatingQuadratic1D(std::vector<T> axisPoint_, std::vector<T> axisDirection_,
                      T w_, T scale_=1, T additive_=0);
  std::vector<T> operator()(std::vector<T> x);
};



/**
  * This functor gives a parabolic profile for a given point x as it computes
  * the distance between x and the axis.

    The forces set are the fake forces caused by a non-Galilean frame, here rotating around an axis with a pulse w.
    There are:
          - The centrifuge force F = rho * w * w * (x-hx, y-hy, z-hz)         | where (hx, hy, hz) is the projection of the point on the axis.
          - The coriolis force F = -2 * rho * w * (vx, vy, vz)°(Dx, Dy, Dz)   | where ° is the vector product and (Dx, Dy, Dz) is the direction vector of the axis normed to 1 (named axisDirection in the code)

     The boolean terms enable to choose having centrifugue or coriolis forces too or not.
*/
/// Functor for the rotation of forces.
template <typename T, template <typename U> class DESCRIPTOR>
class RotatingForceField3D : public SuperLatticeF3D<T,DESCRIPTOR> {
protected:
  SuperGeometry3D sg;
  const LBconverter<T>& converter;
  std::vector<T> axisPoint;
  std::vector<T> axisDirection;
  T w;
  bool centrifugeForceOn;
  bool coriolisForceOn;
  SuperLatticePhysVelocity3D<T, DESCRIPTOR>* velocity;
  SuperLatticeDensity3D<T, DESCRIPTOR>* rho;

public:
  RotatingForceField3D(SuperLattice3D<T,DESCRIPTOR>& sLattice_,
                       SuperGeometry3D& superGeometry_,
                       const LBconverter<T>& converter_,
                       std::vector<T> axisPoint_,
                       std::vector<T> axisDirection_,
                       T w_,
                       bool centrifugeForceOn_ = true,
                       bool coriolisForceOn_ = true);

  ~RotatingForceField3D();
  std::vector<T> operator()(std::vector<int> x);
  std::string name() { return "rotatingForce"; }
};



// PART 2: /////////////////////////////////////////////////////////////////////
// Functors for setting velocities on a velocity boundary of a pipe

/**
  * This functor returns a quadratic Poiseuille profile for use with a pipe with
  * round cross-section. It uses cylinder coordinates and is valid for the
  * entire length of the pipe.
  *
  * This functor gives a parabolic velocity profile for a given point x as it
  * computes the distance between x and the axis.
  *
  * The axis is set in the input with axisPoint and axisDirection. The axisPoint
  * can be the coordinate of any point where the axis passes.
  * axisDirection has to be normed to 1.
  * Once the axis is set in the middle of the pipe, the radius of the
  * pipe "radius" and the velocity in the middle of the pipe "maxVelocity"
  * determine the Poisseuille profile entierly.
  */
/// Velocity profile for round pipes.
template <typename T>
class CirclePoiseuille3D : public AnalyticalF3D<T,T> {
protected:
  std::vector<T> axisPoint;
  std::vector<T> axisDirection;
  T maxVelocity;
  T radius;
  T scale;

public:
  CirclePoiseuille3D(std::vector<T> axisPoint_, std::vector<T> axisDirection_,  T maxVelocity_, T radius_, T scale_=1);
  /// construct from material number, note: untested
  CirclePoiseuille3D(SuperGeometry3D& superGeometry_, int material_, T maxVelocity_, T scale_=1);
  std::vector<T> operator()(std::vector<T> x);
};

/**
  This functor returns a Poiseuille profile for use with a pipe with square shaped cross-section.
*/
/// velocity profile for pipes with rectangular cross-section.
template <typename T>
class RectanglePoiseuille3D : public AnalyticalF3D<T,T> {
protected:
  OstreamManager clout;
  std::vector<T> x0;
  std::vector<T> x1;
  std::vector<T> x2;
  std::vector<T> maxVelocity;

  /*
  /// cross product, only valid in 3d
  std::vector<T> crossProduct3D(std::vector<T> a, std::vector<T> b) {
    std::vector<T> v;
    v.push_back(a[2]*b[3]-a[3]*b[2]);
    v.push_back(a[3]*b[1]-a[1]*b[3]);
    v.push_back(a[1]*b[2]-a[2]*b[1]);
    return v;
  }
  */

  /// normalizes an arbitrary vector
  std::vector<T> normalize(std::vector<T> vec);

public:
  RectanglePoiseuille3D(std::vector<T>& x0_, std::vector<T>& x1_, std::vector<T>& x2_, std::vector<T>& maxVelocity_);
  /// constructor from material numbers
  /** offsetX,Y,Z is a positive number denoting the distance from border
    * voxels of material_ to the zerovelocity boundary (warning: input is
    * currently ignored, uses spacing instead) */
  RectanglePoiseuille3D(SuperGeometry3D& superGeometry_, int material_, std::vector<T>& maxVelocity_, T offsetX=1, T offsetY=1, T offsetZ=1);
  std::vector<T> operator()(std::vector<T> x);
};


/**
  * This functor returns a quadratic Poiseuille profile for use with a pipe with
  * elliptic cross-section.
  *
  * Ellpise is orthogonal to z-direction.
  * a is in x-direction
  * b is in y-direction
  *
  */
/// Velocity profile for round pipes.
template <typename T>
class EllipticPoiseuille3D : public AnalyticalF3D<T,T> {
protected:
  OstreamManager clout;
  std::vector<T> _center;
  T _a2, _b2;
  T _maxVel;

public:
  EllipticPoiseuille3D(std::vector<T> center, T a, T b, T maxVel);
  std::vector<T> operator()(std::vector<T> x);
};

} // end namespace olb
#endif
