/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Mathias J. Krause
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
 * The description of a single 3D cuboid -- header file.
 */

#ifndef CUBOID_3D_H
#define CUBOID_3D_H

#include <vector>
#include "io/ostreamManager.h"


/// All OpenLB code is contained in this namespace.
namespace olb {

/// A regular single 3D cuboid is the basic component of a 3D cuboid
/// structure which defines the grid.
/** A cuboid is given with its left lower corner, the number of nodes
 * in the direction x, y and z and the distance between two nodes.
 * Among after useful methods a cuboid can divide itself in a given
 * number of disjoint subcuboids. The number of nodes at the boundary
 * is minimized.
 *
 * This class is not intended to be derived from.
 */


template<typename T>
class Cuboid3D {
private:
  /// Global position of the left lower corner of the cuboid
  T   _globPosX, _globPosY, _globPosZ;
  /// Distance to the next node
  T   _delta;
  /// Number of nodes in the direction x and y
  int _nX, _nY, _nZ;
  /// Specific ostream for the classname in each line
  mutable OstreamManager clout;
public:
  /// Constructor
  Cuboid3D();
  /// Construction of a cuboid
  Cuboid3D(T globPosX, T globPosY, T globPosZ, T delta, int nX, int nY, int nZ);
  /// Initializes the cuboid
  void init(T globPosX, T globPosY, T globPosZ, T delta, int nX, int nY, int nZ);

  /// Read access to left lower corner coordinates
  T get_globPosX() const;
  T get_globPosY() const;
  T get_globPosZ() const;
  /// Read access to the distance of cuboid nodes
  T get_delta() const;
  /// Read access to cuboid width
  int get_nX() const;
  /// Read access to cuboid height
  int get_nY() const;
  /// Read access to cuboid depth
  int get_nZ() const;
  /// Returns the volume of the cuboid
  T get_volume() const;
  /// Returns the number of Nodes in the volume
  int get_nNodesVolume() const;
  /// Returns the perimeter of the cuboid
  T get_perimeter() const;
  /// Returns the number of Nodes at the perimeter
  int get_nNodesPerimeter() const;
  /// Prints cuboid details
  void print() const;

  /// Checks whether a point (globX/gloxY/globZ) is contained in the cuboid
  /// extended with an layer of size overlap*delta
  bool checkPoint(T globX, T globY, T globZ, int overlap = 0) const;
  /// Checks whether a point (globX/gloxY/globZ) is contained and is a node
  /// in the cuboid extended with an layer of size overlap*delta and
  /// returns the local active node
  bool checkPoint(T globX, T globY, T globZ, int &locX, int &locY, int &locZ, int overlap = 0) const;
  /// Checks whether there is an intersection with the cuboid extended
  /// with an layer of size overlap*delta
  bool checkInters(T globX0, T globX1, T globY0, T globY1, T globZ0, T globZ1, int overlap = 0) const;
  /// Checks whether there is an intersection and returns the local
  /// active node range which can be empty by means of locX0=1, locX1=0,
  /// locY0=1, locY1=0, locZ0=1; locZ1=0 of the cuboid extended with an
  /// layer of size overlap*delta
  bool checkInters(T globX0, T globX1, T globY0, T globY1, T globZ0, T globZ1,
                   int &locX0, int &locX1, int &locY0, int &locY1, int &locZ0, int &locZ1,
                   int overlap = 0) const;

  /// Divides the cuboid in p*q*r cuboids and add the to the given vector
  void divide(int p, int q, int r, std::vector<Cuboid3D<T> > &childrenC) const;
  /// Divides the cuboid in p cuboids and add them to the given vector
  void divide(int p, std::vector<Cuboid3D<T> > &childrenC) const;

  /// resize the cuboid to the passed size
  void resize(int X, int Y, int Z, int nX, int nY, int nZ);
};

}  // namespace olb

#endif
