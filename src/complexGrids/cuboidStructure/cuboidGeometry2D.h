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
 * The description of a vector of 2D cuboid -- header file.
 */


#ifndef CUBOID_GEOMETRY_2D_H
#define CUBOID_GEOMETRY_2D_H

#include <vector>
#include "cuboid2D.h"
#include "core/dataFields2D.h"
#include "io/ostreamManager.h"


/// All OpenLB code is contained in this namespace.
namespace olb {

/// A cuboid structure represents the grid of a considered domain
/** A cuboid structure is given by a number of cuboids. To represent
 * a connected domain it is required that the distance between two
 * neighbooring cuboids is less than the smallest delta of them.
 *
 * WARNING:
 * At the moment there are only cuboids with a constant delta possible
 * and the distance between two neighbooring cuboids must be delta
 * since an interpolation operator in time and space is missing in
 * cuboidNeigbourhood and superLattice.
 *
 * This class is not intended to be derived from.
 */


template<typename T>
class CuboidGeometry2D {
private:
  /// class specific ostream
  mutable OstreamManager clout;
  /// Vector of the cuboids
  std::vector<Cuboid2D<T> > _cuboids;
  /// Cuboid which contains all other cuboids
  Cuboid2D<T> _motherCuboid;
public:
  /// Constructor
  CuboidGeometry2D();
  /// Constructs a cuboid structure with a cubic shape
  /// of size nX times nY that consits of nC cuboids
  CuboidGeometry2D(T globPosX, T globPosY, T delta, int nX, int nY, int nC=1);

  /// Re init
  void reInit(T globPosX, T globPosY,
                   T delta, int nX, int nY, int nC=1);
  /// Read and write access to the cuboids
  Cuboid2D<T>& get_cuboid(int i);
  /// Read access to the cuboids
  Cuboid2D<T> const& get_cuboid(int i) const;

  /// Returns the number of cuboids in the structure
  int get_nC() const;
  /// Returns the maximum/minimum of the ratio nX/NY in the structure
  T get_minRatio() const;
  T get_maxRatio() const;
  /// Returns the maximum/minimum volume in the structure
  T get_minVolume() const;
  T get_maxVolume() const;
  /// Returns the maximum/minimum number of nodes in the structure
  int get_minNodes() const;
  int get_maxNodes() const;
  /// Returns the maximum/minimum delata in the structure
  T get_minDelta() const;
  T get_maxDelta() const;
  /// Returns the smallest cuboid that includes all cuboids of
  /// the structure
  Cuboid2D<T> get_motherC() const;
  /// Prints cuboid structure details
  void printStatistics() const;

  /// for a given point (globX/globY), returns the related cuboidID
  /// and _p if the point is not in any of the cuboid _childrenQ
  int get_iC(T globX, T globY, int offset = 0) const;
  /// This function checks if the points (globX/globY) and
  /// (globX + orientationX/delta /globY + orientationY/delta) is in
  /// a cuboid. It gives the related cuboidID and _p if the points are
  /// not in any of the cuboids.
  /// abs(orientationX) = abs(orientationY) = 1 must be satisfied
  int get_iC(T globX, T globY, int orientationX, int orientationY) const;

  /// Adds a cuboid
  void add(Cuboid2D<T> cuboid);
  /// Removes the cuboid iC
  void remove(int iC);
  /// Removes all cuboids where geometryData = 0
  void remove(olb::ScalarField2D<int>* geometryData);
  /// Splits cuboid iC, removes it and add p cuboids
  void split(int iC, int p);

  /// stores the neighbouring cuboids in array neighbours;
  void get_cuboidNeighbourhood(int cuboid, std::vector<int> neighbours, int offset = 0);
  
  void refineArea(T x0, T x1, T y0, T y1, int coarse_level);
};

}  // namespace olb

#endif
