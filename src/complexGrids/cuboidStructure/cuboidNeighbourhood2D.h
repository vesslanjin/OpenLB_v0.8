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
 * The description of a 2D cuboid neighbourhood -- header file.
 */


#ifndef CUBOID_NEIGHBOURHOOD_2D_H
#define CUBOID_NEIGHBOURHOOD_2D_H

#include "complexGrids/mpiManager/mpiManager.h"
#include <vector>
#include "superLattice2D.h"


/// All OpenLB code is contained in this namespace.
namespace olb {

/// Single 2D cuboid neighbourhoods are the basic component of a
/// 2D communicator
/** For each cuboid is a cuboid neighbourhood devined. It stores the
 * needed cell coordinates (Cell2D) of other cuboids. Futher more this
 * Class provides basic initialization and communication methods
 * for the class Communicator2D.
 *
 * WARNING: For unstructured grids there is an iterpolation needed
 * for the method buffer_outData which is not yet implemented!
 *
 * This class is not intended to be derived from.
 */


template<typename T, template<typename U> class Lattice> class SuperLattice2D;

template<typename T>
struct Cell2D {
  T globX;
  T globY;
  int iC;

  bool operator==(Cell2D const& rhs) const {
    return globX==rhs.globX && globY==rhs.globY && iC==rhs.iC;
  };
};


template<typename T, template<typename U> class Lattice>
class CuboidNeighbourhood2D {
private:
  /// Cuboid ID
  int _iC;
  /// Number of cubboids in the structure
  int _nC;
  /// Delta of the cuboid
  T _deltaC;
  /// Reference to the super structure
  SuperLattice2D<T,Lattice>& _sLattice;

  /// Internal needed cells
  std::vector<Cell2D<T> > _inCells;
  /// External  needed cells
  std::vector<Cell2D<T> > _outCells;
  /// Internal needed neighbour cuboid and number of cells
  std::vector<int> _inC;
  std::vector<int> _inN;
  /// External needed neighbour cuboid and number of cells
  std::vector<int> _outC;
  std::vector<int> _outN;
  /// Buffer for the internal needed data
  T **_inData;
  /// Buffer for the external needed data
  T **_outData;
  /// Indecates if there was an initialization done
  bool _initInCNdone;
  int* _tempInCN;
  /// Indecates if there was an initialization done
  bool _initOutCNdone;
  /// Handels the MPI communication
#ifdef PARALLEL_MODE_MPI
  singleton::MpiNonBlockingHelper _mpiNbHelper;
#endif
public:
  /// Constructor
  //CuboidNeighbourhood2D() {};
  /// Constructor
  CuboidNeighbourhood2D(SuperLattice2D<T,Lattice>& sLattice, int iC);
  /// Copy construction
  CuboidNeighbourhood2D(CuboidNeighbourhood2D<T,Lattice> const& rhs);
  /// Copy assignment
  CuboidNeighbourhood2D operator=(CuboidNeighbourhood2D<T,Lattice> rhs);
  /// Destructor
  ~CuboidNeighbourhood2D();

  /// Read only access to _inCells
  Cell2D<T> const& get_inCell(int i) const;
  /// Returns the number of cells in _inCells
  int get_inCellsSize() const;
  /// Read only access to _inC
  int const& get_inC(int i) const;
  /// Returns the number of cells in _inC
  int get_inCsize() const;
  /// Read and write access to **_inData
  T** get_inData();
  /// Read and write access to **_outData
  T** get_outData();

  /// Adds a cell to the vector _inCells
  void add_inCell(Cell2D<T> cell);
  /// Adds a cell to the vector _outCells
  void add_outCell(Cell2D<T> cell);
  /// Gets the cuboid ID of the point globX/globY and
  /// adds a cell to the vector _inCells
  void add_inCell(T globX, T globY);
  /// Adds all cells with the distance overlap*_delta to
  /// the vector _inCells
  void add_inCells(int overlap);
  /// Initializes _inC and _inN
  void init_inCN();
  /// Initializes _outC and _outN
  void init_outCN();
  /// Initialization Helper
  void bufSend_inCells();
  /// Initialization Helper
  void recWrite_outCells();
  /// Finishes a communication step
  void finish_comm();

  /// Buffers data to be send
  // WARNING: Here is interpolation needed if globX, globY
  // are not integers. This needs to be fixed if one will
  // use unstructured grids.
  void buffer_outData();
  /// Sends data (pure mpi method)
  void send_outData();
  /// Receives data (pure mpi method)
  void receive_inData();
  /// Writes all data to the corresponding lattice cells
  void write_inData();
  /// Resets neighbourhood after initialization (init_inCN
  /// and init_outCN)
  void reset();
};

}  // namespace olb

#endif
