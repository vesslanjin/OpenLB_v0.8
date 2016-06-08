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
 * A communincator provides a cuboids with cells of other
 * cuboids -- header file.
 */


#ifndef COMMUNICATOR_2D_H
#define COMMUNICATOR_2D_H

#include <vector>
#include "cuboidNeighbourhood2D.h"
#include "superLattice2D.h"


/// All OpenLB code is contained in this namespace.
namespace olb {

/// A communincator provides a cuboids with data of other
/// cuboids.
/** For each cuboid is a cuboid neighbourhood defined. A communicator
 * coordinates the communication of the single cuboids where the data
 * is stored locally.
 *
 * There are methods to add needed cells, send, receive and write
 * data of the cell.
 *
 * This class is not intended to be derived from.
 */


template<typename T, template<typename U> class Lattice> class SuperLattice2D;

template<typename T, template<typename U> class Lattice> class CuboidNeighbourhood2D;

template<typename T, template<typename U> class Lattice>
class Communicator2D {

private:
  /// Stores the single cuboid neighbourhoods information
  std::vector<CuboidNeighbourhood2D<T,Lattice> > _nh;
  /// Reference to the super strucrture
  SuperLattice2D<T,Lattice>& _sLattice;
  /// Number of coboids in the structure
  int _nC;
  /// Indicates if there was an initialization done
  bool _initDone;
public:
  /// Constructor
  Communicator2D(SuperLattice2D<T,Lattice>& sLattice);
  /// Initializes the cuboid neighbourhoods
  void init_nh();

  /// Adds a cell (globX/globY) to the cuboid neigbourhood iC
  /// that is then able to get data of the cell
  void add_cell(int iC, T globX, T globY);
  /// Adds all cells of the overlaps to its accociated cuboid
  /// neigbourhood
  void add_cells(int overlap);
  /// Initializes the communicator
  void init();
  /// Resets all cuboids neighbourhoods
  void reset();

  /// Sends the needed data
  void send();
  /// Receives the needed data
  void receive();
  /// Writes all data to the block lattices of the super structure
  void write();
};

}  // namespace olb

#endif
