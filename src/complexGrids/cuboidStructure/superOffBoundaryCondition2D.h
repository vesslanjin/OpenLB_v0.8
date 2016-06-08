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
 * A helper for initialising 2D boundaries -- header file.
 */


#ifndef SUPER_OFF_BOUNDARY_CONDITION_2D_H
#define SUPER_OFF_BOUNDARY_CONDITION_2D_H

#include <vector>
#include "core/offBoundaryCondition2D.h"
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
class sOffLatticeBoundaryCondition2D {

public:
  /// Constructor
  sOffLatticeBoundaryCondition2D(SuperLattice2D<T,Lattice>& sLattice);
  /// Copy construction
  sOffLatticeBoundaryCondition2D(sOffLatticeBoundaryCondition2D<T,Lattice> const& rhs);
  /// Copy assignment
  sOffLatticeBoundaryCondition2D operator=(sOffLatticeBoundaryCondition2D<T,Lattice> rhs);
  /// Destructor
  ~sOffLatticeBoundaryCondition2D();

  void addOnePointFixedBoundary(int x, int y, int dir, T dist);
  void addTwoPointFixedBoundary(int x, int y, int dir, T dist);
  void addThreePointFixedBoundary(int x, int y, int dir, T dist);
  void addOnePointVelocityBoundary(int x, int y, int dir, T dist, T uX, T uY);
  void addTwoPointVelocityBoundary(int x, int y, int dir, T dist, T uX, T uY);
  void addThreePointVelocityBoundary(int x, int y, int dir, T dist, T uX, T uY);

  void addFixedBoundary(BlockGeometryStatistics2D* blockGeoSta, int x, int y, int dir, T dist);
  void addVelocityBoundary(BlockGeometryStatistics2D* blockGeoSta, int x, int y, int dir, T dist, T uX, T uY);

  /// Adds needed Cells to the Communicator _commBC in SuperLattice
  void addPoints2CommBC(int x0, int x1, int y0, int y1, int iCglob);

  SuperLattice2D<T,Lattice>& get_sLattice() {return _sLattice; };
  std::vector<OffLatticeBoundaryCondition2D<T,Lattice>* >& get_blockBCs() {return _blockBCs; };
  int get_overlap() {return _overlap; };
  void set_overlap(int overlap) {_overlap = overlap; };

  void outputOn();
  void outputOff();

private:
  mutable OstreamManager clout;
  SuperLattice2D<T,Lattice>& _sLattice;
  std::vector<OffLatticeBoundaryCondition2D<T,Lattice>* > _blockBCs;
  int _overlap;
  bool _output;
};

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
void createBouzidiBoundaryCondition2D(sOffLatticeBoundaryCondition2D<T,Lattice>& sBC);

template<typename T, template<typename U> class Lattice>
void createBouzidiBoundaryCondition2D(sOffLatticeBoundaryCondition2D<T,Lattice>& sBC) {
  createBouzidiBoundaryCondition2D<T,Lattice,BGKdynamics<T,Lattice> > (sBC);
}

}  // namespace olb

#endif
