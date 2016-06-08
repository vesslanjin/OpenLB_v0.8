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
 * A helper for initialising 3D boundaries -- header file.
 */

#ifndef SUPER_BOUNDARY_CONDITION_3D_H
#define SUPER_BOUNDARY_CONDITION_3D_H

#include <vector>
#include "core/boundaryCondition3D.h"
#include "superGeometryStatistics3D.h"
#include "superLattice3D.h"
#include "io/ostreamManager.h"

/// All OpenLB code is contained in this namespace.
namespace olb {

/// A helper for initialising 3D boundaries for super lattices.
/** Here we have methods that initializes the local postprocessors and the
 * communicator (_commBC in SuperLattice) for boundary conditions
 * for a given global point or global range.
 *
 * This class is not intended to be derived from.
 */

template<typename T, template<typename U> class Lattice>
class sOnLatticeBoundaryCondition3D {

public:
  /// Constructor
  sOnLatticeBoundaryCondition3D(SuperLattice3D<T, Lattice>& sLattice);
  /// Copy construction
  sOnLatticeBoundaryCondition3D(
    sOnLatticeBoundaryCondition3D<T, Lattice> const& rhs);
  /// Copy assignment
  sOnLatticeBoundaryCondition3D operator=(sOnLatticeBoundaryCondition3D<T,
                                          Lattice> rhs);
  /// Destructor
  ~sOnLatticeBoundaryCondition3D();

  void addVelocityBoundary0N(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addVelocityBoundary0P(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addVelocityBoundary1N(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addVelocityBoundary1P(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addVelocityBoundary2N(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addVelocityBoundary2P(T x0, T x1, T y0, T y1, T z0, T z1, T omega);

  void addPressureBoundary0N(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addPressureBoundary0P(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addPressureBoundary1N(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addPressureBoundary1P(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addPressureBoundary2N(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addPressureBoundary2P(T x0, T x1, T y0, T y1, T z0, T z1, T omega);

  void addExternalVelocityEdge0NN(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addExternalVelocityEdge0NP(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addExternalVelocityEdge0PN(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addExternalVelocityEdge0PP(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addExternalVelocityEdge1NN(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addExternalVelocityEdge1NP(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addExternalVelocityEdge1PN(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addExternalVelocityEdge1PP(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addExternalVelocityEdge2NN(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addExternalVelocityEdge2NP(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addExternalVelocityEdge2PN(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addExternalVelocityEdge2PP(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addInternalVelocityEdge0NN(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addInternalVelocityEdge0NP(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addInternalVelocityEdge0PN(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addInternalVelocityEdge0PP(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addInternalVelocityEdge1NN(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addInternalVelocityEdge1NP(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addInternalVelocityEdge1PN(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addInternalVelocityEdge1PP(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addInternalVelocityEdge2NN(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addInternalVelocityEdge2NP(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addInternalVelocityEdge2PN(T x0, T x1, T y0, T y1, T z0, T z1, T omega);
  void addInternalVelocityEdge2PP(T x0, T x1, T y0, T y1, T z0, T z1, T omega);

  void addExternalVelocityCornerNNN(T x, T y, T z, T omega);
  void addExternalVelocityCornerNNP(T x, T y, T z, T omega);
  void addExternalVelocityCornerNPN(T x, T y, T z, T omega);
  void addExternalVelocityCornerNPP(T x, T y, T z, T omega);
  void addExternalVelocityCornerPNN(T x, T y, T z, T omega);
  void addExternalVelocityCornerPNP(T x, T y, T z, T omega);
  void addExternalVelocityCornerPPN(T x, T y, T z, T omega);
  void addExternalVelocityCornerPPP(T x, T y, T z, T omega);

  void addInternalVelocityCornerNNN(T x, T y, T z, T omega);
  void addInternalVelocityCornerNNP(T x, T y, T z, T omega);
  void addInternalVelocityCornerNPN(T x, T y, T z, T omega);
  void addInternalVelocityCornerNPP(T x, T y, T z, T omega);
  void addInternalVelocityCornerPNN(T x, T y, T z, T omega);
  void addInternalVelocityCornerPNP(T x, T y, T z, T omega);
  void addInternalVelocityCornerPPN(T x, T y, T z, T omega);
  void addInternalVelocityCornerPPP(T x, T y, T z, T omega);

  void addVelocityBoundary(SuperGeometry3D& superGeometry, int material, int x0,
                           int x1, int y0, int y1, int z0, int z1, T omega);
  void addVelocityBoundary(SuperGeometry3D& superGeometry, int material, T omega);
  void addPressureBoundary(SuperGeometry3D& superGeometry, int material, int x0,
                           int x1, int y0, int y1, int z0, int z1, T omega);
  void addPressureBoundary(SuperGeometry3D& superGeometry, int material, T omega);

  /// Adds needed Cells to the Communicator _commBC in SuperLattice
  void addPoints2CommBC(int x0, int x1, int y0, int y1, int z0, int z1,
                        int iCglob);

  SuperLattice3D<T, Lattice>& get_sLattice() {
    return _sLattice;
  };

  std::vector<OnLatticeBoundaryCondition3D<T, Lattice>*>& get_blockBCs() {
    return _blockBCs;
  };

  int get_overlap() {
    return _overlap;
  };

  void set_overlap(int overlap) {
    _overlap = overlap;
  };

  void outputOn();
  void outputOff();


private:
  mutable OstreamManager clout;
  SuperLattice3D<T, Lattice>& _sLattice;
  std::vector<OnLatticeBoundaryCondition3D<T, Lattice>*> _blockBCs;
  int _overlap;
  bool _output;
};

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
void createLocalBoundaryCondition3D(
  sOnLatticeBoundaryCondition3D<T, Lattice>& sBC);

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
void createInterpBoundaryCondition3D(
  sOnLatticeBoundaryCondition3D<T, Lattice>& sBC);

template<typename T, template<typename U> class Lattice>
void createLocalBoundaryCondition3D(
  sOnLatticeBoundaryCondition3D<T, Lattice>& sBC) {
  createLocalBoundaryCondition3D<T, Lattice, RLBdynamics<T, Lattice> > (sBC);
}
template<typename T, template<typename U> class Lattice>
void createInterpBoundaryCondition3D(
  sOnLatticeBoundaryCondition3D<T, Lattice>& sBC) {
  createInterpBoundaryCondition3D<T, Lattice, BGKdynamics<T, Lattice> > (sBC);
}

} // namespace olb

#endif
