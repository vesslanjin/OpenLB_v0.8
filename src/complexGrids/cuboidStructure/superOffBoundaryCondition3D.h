/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Jonas Kratzke, Mathias J. Krause
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
 * A helper for initialising 3D boundaries -- header file.
 */


#ifndef SUPER_OFF_BOUNDARY_CONDITION_3D_H
#define SUPER_OFF_BOUNDARY_CONDITION_3D_H

#include <vector>
#include <list>
#include "core/offBoundaryCondition3D.h"
#include "superGeometry3D.h"
#include "superLattice3D.h"
#include "io/ostreamManager.h"
#include "functors/analyticalF.h"


/// All OpenLB code is contained in this namespace.
namespace olb {

/// A helper for initialising 3D boundaries for super lattices.
/** Here we have methods that initializes for a given global
 * point or global range the local postprocessors and the
 * communicator (_commBC in SuperLattice) for boundary conditions.
 *
 * This class is not intended to be derived from.
 */

template<typename T, template<typename U> class Lattice>
class sOffLatticeBoundaryCondition3D {

public:
  /// Constructor
  sOffLatticeBoundaryCondition3D(SuperLattice3D<T,Lattice>& sLattice, T epsFraction_ = 0.0001);
  /// Copy construction
  sOffLatticeBoundaryCondition3D(sOffLatticeBoundaryCondition3D<T,Lattice> const& rhs);
  /// Copy assignment
  sOffLatticeBoundaryCondition3D operator=(sOffLatticeBoundaryCondition3D<T,Lattice> rhs);
  /// Destructor
  ~sOffLatticeBoundaryCondition3D();

  /// Using Bouzidi BC OnePoint corresponds to Bounce Back and TwoPoint to linear interpolation
  void addOnePointZeroVelocityBoundary(int x, int y, int z, int iPop, T dist);
  void addTwoPointZeroVelocityBoundary(int x, int y, int z, int iPop, T dist);
  void addOnePointVelocityBoundary(int x, int y, int z, int iPop, T dist);
  void addTwoPointVelocityBoundary(int x, int y, int z, int iPop, T dist);

  /// Calls offDynamics(x,y,z) vor every cell with the material number
  void addOffDynamics(SuperGeometry3D& superGeometry, int material);
  /// Adds default offDynamics to (x,y,z).
  /// Note: Set boundary links manually with SuperLattice3D<T,Lattice>::setBoundaryIntersection
  void addOffDynamics(int x, int y, int z, T location[Lattice<T>::d]);
  /// Add offDynamics with initialisation of the boundary links
  void addOffDynamics(int x, int y, int z, T location[Lattice<T>::d], T distances[Lattice<T>::q]);

  void addZeroVelocityBoundary(SuperGeometry3D& superGeometry, int material, STLreader<T>& stlreader, std::list<int> bulkMaterials = std::list<int>(1,1));
  void addZeroVelocityBoundary(SuperGeometry3D& superGeometry, int x, int y, int z, int iPop, T dist);

  /// Automatically sets offDynamics with boundary links and post processors using an stl-file and material number
  void addVelocityBoundary(SuperGeometry3D& superGeometry, int material, STLreader<T>& stlreader);
  void addVelocityBoundary(SuperGeometry3D& superGeometry, int x, int y, int z, STLreader<T>& stlreader);
  /// Add offDynamics with initialisation of boundary links and the corresponding post processors
  /// Note: Uses information of the second neighbours of the cell (x,y,z)
  void addVelocityBoundary(SuperGeometry3D& superGeometry, int x, int y, int z, T distances[Lattice<T>::q]);
  /// Add post processors. Ensure that offDynamics are defined!
  void addVelocityBoundary(SuperGeometry3D& superGeometry, int x, int y, int z, int iPop, T dist);

  void setBoundaryIntersection(int x, int y, int z, int iPop, T distance);
  bool getBoundaryIntersection(int x, int y, int z, int iPop, T point[Lattice<T>::d]);
  void defineU(int x, int y, int z, int iPop, const T u[Lattice<T>::d]);

  void defineU(SuperGeometry3D& superGeometry, int material, AnalyticalF3D<T,T>& u, std::list<int> bulkMaterials = std::list<int>(1,1) );

  /// Adds needed Cells to the Communicator _commBC in SuperLattice
  void addPoints2CommBC(int x0, int x1, int y0, int y1, int z0, int z1, int iCglob);

  SuperLattice3D<T,Lattice>& get_sLattice() {return _sLattice; };
  std::vector<OffLatticeBoundaryCondition3D<T,Lattice>* >& get_blockBCs() {return _blockBCs; };
  int get_overlap() {return _overlap; };
  void set_overlap(int overlap) {_overlap = overlap; };

  void outputOn();
  void outputOff();

private:
  mutable OstreamManager clout;
  SuperLattice3D<T,Lattice>& _sLattice;
  std::vector<OffLatticeBoundaryCondition3D<T,Lattice>* > _blockBCs;
  T _epsFraction;
  int _overlap;
  bool _output;
};

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
void createBouzidiBoundaryCondition3D(sOffLatticeBoundaryCondition3D<T,Lattice>& sBC);

template<typename T, template<typename U> class Lattice>
void createBouzidiBoundaryCondition3D(sOffLatticeBoundaryCondition3D<T,Lattice>& sBC) {
  createBouzidiBoundaryCondition3D<T,Lattice,BGKdynamics<T,Lattice> > (sBC);
}

}  // namespace olb

#endif
