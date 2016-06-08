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
 * A helper for initialising 2D boundaries -- header file.
 */


#ifndef SUPER_BOUNDARY_CONDITION_2D_H
#define SUPER_BOUNDARY_CONDITION_2D_H

#include <vector>
#include "core/boundaryCondition2D.h"
#include "core/blockGeometryStatistics2D.h"
#include "superLattice2D.h"
#include "io/ostreamManager.h"


/// All OpenLB code is contained in this namespace.
namespace olb {

/// A helper for initialising 2D boundaries for super lattices.
/** Here we have methods that initializes for a given global
 * point or global range the local postprocessors and the
 * communicator (_commBC in SuperLattice) for boundary conditions.
 *
 * This class is not intended to be derived from.
 */



template<typename T, template<typename U> class Lattice>
class sOnLatticeBoundaryCondition2D {

public:
  /// Constructor
  sOnLatticeBoundaryCondition2D(SuperLattice2D<T,Lattice>& sLattice);
  /// Copy construction
  sOnLatticeBoundaryCondition2D(sOnLatticeBoundaryCondition2D<T,Lattice> const& rhs);
  /// Copy assignment
  sOnLatticeBoundaryCondition2D operator=(sOnLatticeBoundaryCondition2D<T,Lattice> rhs);
  /// Destructor
  ~sOnLatticeBoundaryCondition2D();

  void addVelocityBoundary0N(T x0, T x1, T y0, T y1, T omega);
  void addVelocityBoundary0P(T x0, T x1, T y0, T y1, T omega);
  void addVelocityBoundary1N(T x0, T x1, T y0, T y1, T omega);
  void addVelocityBoundary1P(T x0, T x1, T y0, T y1, T omega);
  void addPressureBoundary0N(T x0, T x1, T y0, T y1, T omega);
  void addPressureBoundary0P(T x0, T x1, T y0, T y1, T omega);
  void addPressureBoundary1N(T x0, T x1, T y0, T y1, T omega);
  void addPressureBoundary1P(T x0, T x1, T y0, T y1, T omega);

  void addExternalVelocityCornerNN(T x, T y, T omega);
  void addExternalVelocityCornerNP(T x, T y, T omega);
  void addExternalVelocityCornerPN(T x, T y, T omega);
  void addExternalVelocityCornerPP(T x, T y, T omega);

  void addInternalVelocityCornerNN(T x, T y, T omega);
  void addInternalVelocityCornerNP(T x, T y, T omega);
  void addInternalVelocityCornerPN(T x, T y, T omega);
  void addInternalVelocityCornerPP(T x, T y, T omega);

  void addVelocityBoundary(BlockGeometryStatistics2D* blockGeoSta, int x0,
                           int x1, int y0, int y1, T omega, int material);
  void addVelocityBoundary(BlockGeometryStatistics2D* blockGeoSta, T omega,
                           int material);
  void addPressureBoundary(BlockGeometryStatistics2D* blockGeoSta, int x0,
                           int x1, int y0, int y1, T omega, int material);
  void addPressureBoundary(BlockGeometryStatistics2D* blockGeoSta, T omega,
                           int material);

  /// Adds needed Cells to the Communicator _commBC in SuperLattice
  void addPoints2CommBC(int x0, int x1, int y0, int y1, int iCglob);

  SuperLattice2D<T,Lattice>& get_sLattice() {return _sLattice; };
  std::vector<OnLatticeBoundaryCondition2D<T,Lattice>* >& get_blockBCs() {return _blockBCs; };
  int get_overlap() {return _overlap; };
  void set_overlap(int overlap) {_overlap = overlap; };

  void outputOn();
  void outputOff();

private:
  mutable OstreamManager clout;
  SuperLattice2D<T,Lattice>& _sLattice;
  std::vector<OnLatticeBoundaryCondition2D<T,Lattice>* > _blockBCs;
  int _overlap;
  bool _output;
};


template<typename T, template<typename U> class Lattice, typename MixinDynamics>
void createLocalBoundaryCondition2D(sOnLatticeBoundaryCondition2D<T,Lattice>& sBC);

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
void createInterpBoundaryCondition2D(sOnLatticeBoundaryCondition2D<T,Lattice>& sBC);

template<typename T, template<typename U> class Lattice>
void createLocalBoundaryCondition2D(sOnLatticeBoundaryCondition2D<T,Lattice>& sBC) {
  createLocalBoundaryCondition2D<T,Lattice,RLBdynamics<T,Lattice> > (sBC);
}
template<typename T, template<typename U> class Lattice>
void createInterpBoundaryCondition2D(sOnLatticeBoundaryCondition2D<T,Lattice>& sBC) {
  createInterpBoundaryCondition2D<T,Lattice,BGKdynamics<T,Lattice> > (sBC);
}

}  // namespace olb

#endif
