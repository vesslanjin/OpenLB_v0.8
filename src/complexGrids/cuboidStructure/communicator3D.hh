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
 * cuboids -- generic implementation.
 */


#ifndef COMMUNICATOR_3D_HH
#define COMMUNICATOR_3D_HH

#include "complexGrids/mpiManager/mpiManager.h"
#include <vector>
#include "communicator3D.h"
#include "cuboidNeighbourhood3D.h"
#include "cuboidGeometry3D.h"
#include "superLattice3D.h"


namespace olb {

/////////////////// Class Communicator3D //////////////////////


template<typename T, template<typename U> class Lattice>
Communicator3D<T,Lattice>::Communicator3D(SuperLattice3D<T,Lattice>& sLattice):_sLattice(sLattice) {
  _initDone = false;
}

template<typename T, template<typename U> class Lattice>
void Communicator3D<T,Lattice>::init_nh() {

  _nC = _sLattice.get_cGeometry().get_nC();

  for (int iC=0; iC<_sLattice.get_load().size(); iC++) {
    CuboidNeighbourhood3D<T,Lattice> nh(_sLattice,_sLattice.get_load().glob(iC));
    _nh.push_back(nh);
  }
}

template<typename T, template<typename U> class Lattice>
void Communicator3D<T,Lattice>::add_cell(int iC, T globX, T globY, T globZ) {

  if( iC >= _sLattice.get_load().get_firstGlobNum() &&
      iC <= _sLattice.get_load().get_lastGlobNum() )
  {
    _nh[_sLattice.get_load().loc(iC)].add_inCell(globX, globY, globZ);
  }
}

template<typename T, template<typename U> class Lattice>
void Communicator3D<T,Lattice>::add_cells(int overlap) {

  for (int iC=0; iC<_sLattice.get_load().size(); iC++) {
    for (int i=1; i<=overlap; i++) {
      _nh[iC].add_inCells(i);
    }
  }
}

template<typename T, template<typename U> class Lattice>
void Communicator3D<T,Lattice>::init() {

  reset();
  for (int iC=0; iC<_sLattice.get_load().size(); iC++) {
    _nh[iC].init_inCN();
    for (int i=0; i<_nh[iC].get_inCellsSize(); i++) {
      int ID = _nh[iC].get_inCell(i).iC;
#ifdef PARALLEL_MODE_MPI
      if ( singleton::mpi().getRank() ==_sLattice.get_load().rank(ID) )
#endif
      {
        Cell3D<T> temp;
        temp.globX = _nh[iC].get_inCell(i).globX;
        temp.globY = _nh[iC].get_inCell(i).globY;
        temp.globZ = _nh[iC].get_inCell(i).globZ;
        temp.iC    = _sLattice.get_load().glob(iC);
        _nh[_sLattice.get_load().loc(ID)].add_outCell(temp);
      }
    }
  }

  for (int iC=0; iC<_sLattice.get_load().size(); iC++) {
    _nh[iC].init_outCN();
  }

#ifdef PARALLEL_MODE_MPI
  for (int iC=0; iC<_sLattice.get_load().size(); iC++) {
    _nh[iC].finish_comm();
  }
  for (int iC=0; iC<_sLattice.get_load().size(); iC++) {
    _nh[iC].bufSend_inCells();
  }
  for (int iC=0; iC<_sLattice.get_load().size(); iC++) {
    _nh[iC].recWrite_outCells();
  }
  for (int iC=0; iC<_sLattice.get_load().size(); iC++) {
    _nh[iC].finish_comm();
  }
#endif
}

template<typename T, template<typename U> class Lattice>
void Communicator3D<T,Lattice>::reset() {

  if (_initDone) {
    for (int iC=0; iC<_sLattice.get_load().size(); iC++) {
      _nh[iC].reset();
    }
    _initDone = false;
  }
}

template<typename T, template<typename U> class Lattice>
void Communicator3D<T,Lattice>::send() {

  for (int iC=0; iC<_sLattice.get_load().size(); iC++) {
    _nh[iC].buffer_outData();
#ifdef PARALLEL_MODE_MPI
    _nh[iC].send_outData();
#endif
  }
}

template<typename T, template<typename U> class Lattice>
void Communicator3D<T,Lattice>::receive() {

  for (int iC=0; iC<_sLattice.get_load().size(); iC++) {
#ifdef PARALLEL_MODE_MPI
    _nh[iC].receive_inData();
#else
    for (int i=0; i<_nh[iC].get_inCsize(); i++) {
      _nh[iC].get_inData()[_nh[iC].get_inC(i)] =
        _nh[_nh[iC].get_inC(i)].get_outData()[iC];
    }
#endif
  }
#ifdef PARALLEL_MODE_MPI
  for (int iC=0; iC<_sLattice.get_load().size(); iC++) {
    _nh[iC].finish_comm();
  }
#endif
}

template<typename T, template<typename U> class Lattice>
void Communicator3D<T,Lattice>::write() {

  for (int iC=0; iC<_sLattice.get_load().size(); iC++) {
    _nh[iC].write_inData();
  }
}

}

#endif
