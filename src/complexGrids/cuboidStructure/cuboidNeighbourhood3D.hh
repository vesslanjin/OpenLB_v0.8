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
 * The description of a 3D cuboid neighbourhood -- generic implementation.
 */


#ifndef CUBOID_NEIGHBOURHOOD_3D_HH
#define CUBOID_NEIGHBOURHOOD_3D_HH

#include "complexGrids/mpiManager/mpiManager.h"
#include <vector>
#include "cuboidNeighbourhood3D.h"
#include "cuboidGeometry3D.h"
#include "core/dynamics.h"
#include "core/cell.h"
#include "superLattice3D.h"


namespace olb {


//////////////// Class CuboidNeighbourhood3D //////////////////

template<typename T, template<typename U> class Lattice>
CuboidNeighbourhood3D<T,Lattice>::CuboidNeighbourhood3D(
  SuperLattice3D<T,Lattice>& sLattice, int iC):_sLattice(sLattice) {
  _iC            = iC;
  _nC            = _sLattice.get_cGeometry().get_nC();
  _deltaC        = _sLattice.get_cGeometry().get_cuboid(iC).get_delta();
  _initInCNdone  = false;
  _initOutCNdone = false;
}

template<typename T, template<typename U> class Lattice>
CuboidNeighbourhood3D<T,Lattice>::CuboidNeighbourhood3D (
  CuboidNeighbourhood3D<T,Lattice> const& rhs ):_sLattice(rhs._sLattice) {
  _iC            = rhs._iC;
  _nC            = rhs._nC;
  _deltaC        = rhs._deltaC;
  _inCells       = rhs._inCells;
  _outCells      = rhs._outCells;
  _inC           = rhs._inC;
  _inN           = rhs._inN;
  _outC          = rhs._outC;
  _outN          = rhs._outN;
  _initInCNdone  = false;
  _initOutCNdone = false;
}

template<typename T, template<typename U> class Lattice>
CuboidNeighbourhood3D<T,Lattice> CuboidNeighbourhood3D<T,Lattice>::operator= (
  CuboidNeighbourhood3D<T,Lattice> rhs )  {
  CuboidNeighbourhood3D<T,Lattice> tmp(rhs);
  return tmp;
}

template<typename T, template<typename U> class Lattice>
CuboidNeighbourhood3D<T,Lattice>::~CuboidNeighbourhood3D<T,Lattice>() {
  reset();
}


template<typename T, template<typename U> class Lattice>
Cell3D<T> const& CuboidNeighbourhood3D<T,Lattice>::get_inCell(int i) const {
  return _inCells[i];
}

template<typename T, template<typename U> class Lattice>
int CuboidNeighbourhood3D<T,Lattice>::get_inCellsSize() const {
  return _inCells.size();
}

template<typename T, template<typename U> class Lattice>
int const& CuboidNeighbourhood3D<T,Lattice>::get_inC(int i) const {
  return _inC[i];
}

template<typename T, template<typename U> class Lattice>
int CuboidNeighbourhood3D<T,Lattice>::get_inCsize() const {
  return _inC.size();
}

template<typename T, template<typename U> class Lattice>
T** CuboidNeighbourhood3D<T,Lattice>::get_inData() {
  return _inData;
}

template<typename T, template<typename U> class Lattice>
T** CuboidNeighbourhood3D<T,Lattice>::get_outData() {
  return _outData;
}


template<typename T, template<typename U> class Lattice>
void CuboidNeighbourhood3D<T,Lattice>::add_inCell(Cell3D<T> cell) {
  _inCells.push_back(cell);
}

template<typename T, template<typename U> class Lattice>
void CuboidNeighbourhood3D<T,Lattice>::add_outCell(Cell3D<T> cell) {
  _outCells.push_back(cell);
}

template<typename T, template<typename U> class Lattice>
void CuboidNeighbourhood3D<T,Lattice>::add_inCell(T globX, T globY, T globZ) {

  Cell3D<T> found;
  int iC = _sLattice.get_cGeometry().get_iC(globX, globY, globZ);
  if(iC!=_sLattice.get_cGeometry().get_nC()) {
    found.globX = globX;
    found.globY = globY;
    found.globZ = globZ;
    found.iC = iC;
    for (unsigned i=0; i<_inCells.size(); i++) {
      if(_inCells[i]==found) return;
    }
    _inCells.push_back(found);
  }
}

template<typename T, template<typename U> class Lattice>
void CuboidNeighbourhood3D<T,Lattice>::add_inCells(int overlap) {
  int xN  = _sLattice.get_cGeometry().get_cuboid(_iC).get_nX();
  int yN  = _sLattice.get_cGeometry().get_cuboid(_iC).get_nY();
  int zN  = _sLattice.get_cGeometry().get_cuboid(_iC).get_nZ();
  T globX = _sLattice.get_cGeometry().get_cuboid(_iC).get_globPosX();
  T globY = _sLattice.get_cGeometry().get_cuboid(_iC).get_globPosY();
  T globZ = _sLattice.get_cGeometry().get_cuboid(_iC).get_globPosZ();
  T delta = _sLattice.get_cGeometry().get_cuboid(_iC).get_delta();
  Cell3D<T> found;

  for (int iX=0-overlap; iX<xN+overlap; iX++) {
    for (int iY=0-overlap; iY<yN+overlap; iY++) {
      for (int iZ=0-overlap; iZ<zN+overlap; iZ++) {
        if (iX == 0 - overlap || iX == xN + overlap -1 ||
            iY == 0 - overlap || iY == yN + overlap -1 ||
            iZ == 0 - overlap || iZ == zN + overlap -1 ) {

          T nextX = globX + iX*delta;
          T nextY = globY + iY*delta;
          T nextZ = globZ + iZ*delta;
          int iC = _sLattice.get_cGeometry().get_iC(nextX, nextY, nextZ);
          if (iC!=_sLattice.get_cGeometry().get_nC()) {
            found.globX = nextX;
            found.globY = nextY;
            found.globZ = nextZ;
            found.iC = iC;
            _inCells.push_back(found);
          }
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void CuboidNeighbourhood3D<T,Lattice>::init_inCN() {

  _inC.clear();
  _inN.clear();

  _inData = new T* [_nC];
  _tempInCN = new int [_nC];
  for (int i=0; i<_nC; i++) {
    _tempInCN[i]=0;
  }

  for (unsigned i=0; i<_inCells.size(); i++) {
    _tempInCN[_inCells[i].iC]++;
  }
  for (int i=0; i<_nC; i++) {
    if (_tempInCN[i]!=0) {
      _inC.push_back(i);
      _inN.push_back(_tempInCN[i]);
#ifdef PARALLEL_MODE_MPI
      _inData[i] = new T [_tempInCN[i]*Lattice<T>::q];
#endif
    }
#ifdef PARALLEL_MODE_MPI
    else _inData[i] = NULL;
#endif
  }

#ifdef PARALLEL_MODE_MPI
  int counter=0;
  for (int i=0; i<_nC; i++) {
    int dRank = _sLattice.get_load().rank(i);
    if ( singleton::mpi().getRank() != dRank )
      counter++;
  }
  _mpiNbHelper.allocate(counter);
  counter=0;
  for (int i=0; i<_nC; i++) {
    int dRank = _sLattice.get_load().rank(i);
    if ( singleton::mpi().getRank() != dRank ) {
      singleton::mpi().iSend(&_tempInCN[i] , 1, dRank, &_mpiNbHelper.get_mpiRequest()[counter], i*_nC+_iC);
      counter++;
    }
  }
#endif

  _initInCNdone = true;
}

template<typename T, template<typename U> class Lattice>
void CuboidNeighbourhood3D<T,Lattice>::init_outCN() {

  _outC.clear();
  _outN.clear();
  _outData = new T* [_nC];

  std::vector<int> temp(_nC,0);

  for (unsigned i=0; i<_outCells.size(); i++) {
    temp[_outCells[i].iC]++;
  }

  for (int i=0; i<_nC; i++) {
#ifdef PARALLEL_MODE_MPI
    int sRank = _sLattice.get_load().rank(i);
    if ( singleton::mpi().getRank() != sRank ) {
      singleton::mpi().receive(&temp[i], 1, sRank, _iC*_nC+i);
    }
#endif
    if (temp[i]!=0) {
      _outC.push_back(i);
      _outN.push_back(temp[i]);
    }
    _outData[i] = new T [temp[i]*Lattice<T>::q];
  }

  _initOutCNdone = true;
}

template<typename T, template<typename U> class Lattice>
void CuboidNeighbourhood3D<T,Lattice>::bufSend_inCells() {

#ifdef PARALLEL_MODE_MPI
  _mpiNbHelper.free();

  std::vector<int> temp(_nC,0);
  for (unsigned i=0; i<_inCells.size(); i++) {
    int iC = _inCells[i].iC;
    if (singleton::mpi().getRank() != _sLattice.get_load().rank(iC)) {
      _inData[iC][3*temp[iC]] = _inCells[i].globX;
      _inData[iC][3*temp[iC]+1] = _inCells[i].globY;
      _inData[iC][3*temp[iC]+2] = _inCells[i].globZ;
      temp[iC]++;
    }
  }

  int counter=0;
  for (unsigned iC=0; iC<_inC.size(); iC++) {
    //int dRank = _sLattice.get_load().rank(_inC[iC]);
    //if ( singleton::mpi().getRank() != dRank )
    counter++;
  }

  _mpiNbHelper.allocate(counter);
  counter=0;
  for (unsigned iC=0; iC<_inC.size(); iC++) {
    int dRank = _sLattice.get_load().rank(_inC[iC]);
    //if ( singleton::mpi().getRank() != dRank ) {
    singleton::mpi().iSend( _inData[_inC[iC]],
                            _inN[iC]*3, dRank, &_mpiNbHelper.get_mpiRequest()[counter], _inC[iC]*_nC+_iC);
    counter++;
    //}
  }
#endif
}

template<typename T, template<typename U> class Lattice>
void CuboidNeighbourhood3D<T,Lattice>::recWrite_outCells() {

#ifdef PARALLEL_MODE_MPI
  for (unsigned iC=0; iC<_outC.size(); iC++) {
    int sRank = _sLattice.get_load().rank(_outC[iC]);
    singleton::mpi().receive(_outData[_outC[iC]], _outN[iC]*3, sRank, _iC*_nC+_outC[iC]);
    if ( singleton::mpi().getRank() != sRank ) {
      //singleton::mpi().receive(_outData[_outC[iC]], _outN[iC]*3, sRank, _iC*_nC+_outC[iC]);
      Cell3D<T> found;
      found.iC = _outC[iC];
      for (int i=0; i<_outN[iC]; i++) {
        found.globX = _outData[_outC[iC]][3*i];
        found.globY = _outData[_outC[iC]][3*i+1];
        found.globZ = _outData[_outC[iC]][3*i+2];
        _outCells.push_back(found);
      }
    }
  }
#endif
}

template<typename T, template<typename U> class Lattice>
void CuboidNeighbourhood3D<T,Lattice>::finish_comm() {

#ifdef PARALLEL_MODE_MPI
  singleton::mpi().waitAll(_mpiNbHelper);
#endif

}

template<typename T, template<typename U> class Lattice>
void CuboidNeighbourhood3D<T,Lattice>::buffer_outData() {

  std::vector<int> temp(_nC,0);
  int iCloc = _sLattice.get_load().loc(_iC);
  for (unsigned i=0; i<_outCells.size(); i++) {
    int iC = _outCells[i].iC;
    // WARNING: Here is interpolation needed if globX, globY
    // are not integers. This needs to be fixed if one will
    // use unstructured grids.
    int iX = (int)_outCells[i].globX -
             (int)_sLattice.get_cGeometry().get_cuboid(_iC).get_globPosX();
    int iY = (int)_outCells[i].globY -
             (int)_sLattice.get_cGeometry().get_cuboid(_iC).get_globPosY();
    int iZ = (int)_outCells[i].globZ -
             (int)_sLattice.get_cGeometry().get_cuboid(_iC).get_globPosZ();
    for (unsigned iPop=0; iPop<Lattice<T>::q; iPop++) {
      _outData[iC][temp[iC]*Lattice<T>::q + iPop]
      =_sLattice.get_lattice(iCloc).get(iX,iY,iZ)[iPop];
    }
    temp[iC]++;
  }
}

template<typename T, template<typename U> class Lattice>
void CuboidNeighbourhood3D<T,Lattice>::send_outData() {
#ifdef PARALLEL_MODE_MPI
  for (unsigned iC=0; iC<_outC.size(); iC++) {
    int dRank = _sLattice.get_load().rank(_outC[iC]);
    singleton::mpi().iSend( _outData[_outC[iC]],
                            _outN[iC]*Lattice<T>::q, dRank, &_mpiNbHelper.get_mpiRequest()[iC], _outC[iC]*_nC+_iC);
  }
#endif
}

template<typename T, template<typename U> class Lattice>
void CuboidNeighbourhood3D<T,Lattice>::receive_inData() {
#ifdef PARALLEL_MODE_MPI
  for (unsigned iC=0; iC<_inC.size(); iC++) {
    int sRank = _sLattice.get_load().rank(_inC[iC]);
    singleton::mpi().receive(_inData[_inC[iC]], _inN[iC]*Lattice<T>::q, sRank, _iC*_nC+_inC[iC]);
  }
#endif
}

template<typename T, template<typename U> class Lattice>
void CuboidNeighbourhood3D<T,Lattice>::write_inData() {

  int iCloc = _sLattice.get_load().loc(_iC);
  int overlap = _sLattice.get_overlap();
  std::vector<int> temp(_nC,0);
  for (unsigned i=0; i<_inCells.size(); i++) {
    int iC = _inCells[i].iC;
    int iX = (int)(_inCells[i].globX -
                   _sLattice.get_cGeometry().get_cuboid(_iC).get_globPosX());
    int iY = (int)(_inCells[i].globY -
                   _sLattice.get_cGeometry().get_cuboid(_iC).get_globPosY());
    int iZ = (int)(_inCells[i].globZ -
                   _sLattice.get_cGeometry().get_cuboid(_iC).get_globPosZ());

    for (unsigned iPop=0; iPop<Lattice<T>::q; iPop++) {
      _sLattice.get_blockLattice(iCloc).get(iX+overlap,iY+overlap,iZ+overlap)[iPop] =
        _inData[iC][temp[iC]*Lattice<T>::q + iPop];
    }
    temp[iC]++;
  }
}

template<typename T, template<typename U> class Lattice>
void CuboidNeighbourhood3D<T,Lattice>::reset() {

  if (_initInCNdone) {
#ifdef PARALLEL_MODE_MPI
    for (int iC=0; iC<_nC; iC++) {
      delete _inData[iC];
    }
#endif
    delete _inData;
    delete _tempInCN;
    _initInCNdone = false;
  }
  if (_initOutCNdone) {
    for (int iC=0; iC<_nC; iC++) {
      delete _outData[iC];
    }
    delete _outData;
#ifdef PARALLEL_MODE_MPI
    _mpiNbHelper.free();
#endif
    _initOutCNdone = false;
  }
  _inCells.clear();
  _outCells.clear();
  _inC.clear();
  _outC.clear();
  _inN.clear();
  _outN.clear();
}

}  // namespace olb

#endif
