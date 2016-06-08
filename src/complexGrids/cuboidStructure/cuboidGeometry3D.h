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
 * The description of a vector of 3D cuboid -- header file.
 */


#ifndef CUBOID_GEOMETRY_3D_H
#define CUBOID_GEOMETRY_3D_H

#include <vector>
#include "cuboid3D.h"
#include "core/blockGeometry3D.h"
#include "superGeometry3D.h"
#include "io/ostreamManager.h"


/// All OpenLB code is contained in this namespace.
namespace olb {

/// A cuboid structure represents the grid of a considered domain
/** A cuboid structure is given by a number of cuboids. To represent
 * a connected domain it is required that the distance between two
 * neighbooring cuboids is less than the smallest delta of them.
 *
 * WARNING:
 * At the moment only cuboids with a constant delta are possible
 * and the distance between two neighbooring cuboids must be delta
 * since an interpolation operator in time and space is missing in
 * cuboidNeigbourhood and superLattice.
 *
 * This class is not intended to be derived from.
 */


template<typename T>
class CuboidGeometry3D {
private:
  /// class specific ostream
  mutable OstreamManager clout;
  /// Vector of the cuboids
  std::vector<Cuboid3D<T> > _cuboids;
  /// Cuboid which contains all other cuboids
  Cuboid3D<T> _motherCuboid;

public:
  /// Constructor
  CuboidGeometry3D() : clout(std::cout,"CuboidGeometry3D") {};
  /// Constructs a cuboid structure with a cubic shape
  /// of size nX times nY times nZ that consits of nC cuboids
  CuboidGeometry3D(T globPosX, T globPosY, T globPosZ,
                   T delta, int nX, int nY, int nZ, int nC=1);


  /// Re init
  void reInit(T globPosX, T globPosY, T globPosZ,
                   T delta, int nX, int nY, int nZ, int nC=1);
  /// Read and write access to the cuboids
  Cuboid3D<T>& get_cuboid(int i);
  /// Read access to the cuboids
  Cuboid3D<T> const& get_cuboid(int i) const;

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
  /// Returns the maximum/minimum delta in the structure
  T get_minDelta() const;
  T get_maxDelta() const;
  /// Returns the smallest cuboid that includes all cuboids of
  /// the structure
  Cuboid3D<T> get_motherC() const;
  void set_motherC(T globPosX, T globPosY, T globPosZ,
                   T delta, int nX, int nY, int nZ);
  /// Prints cuboid structure details
  void printStatistics() const;

  /// Gives for a given point (globX/globY/globZ) the related cuboidID
  /// and _p if the point is not in any of the cuboid _childrenQ
  int get_iC(T globX, T globY, T globZ, int offset = 0) const;
  /// This function checks if the points (globX/globY/globZ) and
  /// (globX + orientationX/delta/globY + orientationY/delta/
  /// globZ + orientationZ/delta) is in a cuboid.
  /// It gives the related cuboidID and _p if the points are
  /// not in any of the cuboids.
  /// abs(orientationX) = abs(orientationY) = abs(orientationY) = 1
  /// must be satisfied
  int get_iC(T globX, T globY, T globZ,
             int orientationX, int orientationY, int orientationZ) const;

  /// Adds a cuboid
  void add(Cuboid3D<T> cuboid);
  /// Removes the cuboid iC
  void remove(int iC);
  /// Removes all cuboids where geometryData = 0
  void remove(olb::BlockGeometry3D& blockGeometry);
  /// Shrink all cuboids so that no empty planes are left
  void shrink(olb::BlockGeometry3D& blockGeometry);
  /// Splits cuboid iC, removes it and adds p cuboids
  void remove(olb::SuperGeometry3D& superGeometry);
  /// Shrink all cuboids so that no empty planes are left
  void shrink(olb::SuperGeometry3D& superGeometry);
  /// Splits cuboid iC, removes it and adds p cuboids
  void split(int iC, int p);

  /// stores the neighbouring cuboids in array neighbours;
  void get_cuboidNeighbourhood(int cuboid, std::vector<int>& neighbours, int offset = 0);
};

}  // namespace olb

#endif
