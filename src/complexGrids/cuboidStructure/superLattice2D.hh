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
 * The description of a 2D super lattice -- generic implementation.
 */


#ifndef SUPER_LATTICE_2D_HH
#define SUPER_LATTICE_2D_HH

#include<limits>

#include "complexGrids/mpiManager/mpiManager.h"
#include "core/blockLattice2D.h"
#include "core/cell.h"
#include "communicator2D.h"
#include "cuboidGeometry2D.h"
#include "core/loadBalancer.h"
#include "core/postProcessing.h"
#include "superLattice2D.h"
#include "io/base64.h"


namespace olb {


////////////////////// Class SuperLattice2D /////////////////////////


template<typename T, template<typename U> class Lattice>
SuperLattice2D<T,Lattice>::SuperLattice2D (
  CuboidGeometry2D<T>& cGeometry, int overlapBC, int overlapRefinement)
  :_cGeometry(cGeometry),_overlapRefinement(overlapRefinement),_commStream(*this),_commBC(*this) {

  if (overlapBC >= 1) {
    _commBC_on = true;
    _overlap = overlapBC;
  }
  else {
    _commBC_on = false;
    _overlap = 1;
  }

  int rank = 0;
  int size = 1;
#ifdef PARALLEL_MODE_MPI
  rank = singleton::mpi().getRank();
  size = singleton::mpi().getSize();
#endif
  _load.init_chunkD(rank, size, _cGeometry.get_nC(), 0);

  for (int iC=0; iC<_load.size(); iC++) {
    int nX = _cGeometry.get_cuboid(_load.glob(iC)).get_nX() + 2*_overlap;
    int nY = _cGeometry.get_cuboid(_load.glob(iC)).get_nY() + 2*_overlap;
    if(_cGeometry.get_cuboid(_load.glob(iC)).get_refinementLevel() > 0) {
	    nX += 2*_overlapRefinement-1;
	    nY += 2*_overlapRefinement-1;
    }

    BlockLattice2D<T, Lattice> tmp(0, 0);
    _blockLattices.push_back(tmp);
    BlockLattice2D<T, Lattice> blockLattice(nX, nY);
    _blockLattices.back().swap(blockLattice);

  }
  for (int iC=0; iC<_load.size(); iC++) {
    BlockLatticeView2D<T,Lattice>lattice( _blockLattices[iC],
                                          _overlap, _blockLattices[iC].getNx() - _overlap - 1 ,
                                          _overlap, _blockLattices[iC].getNy() - _overlap - 1);
    _lattices.push_back(lattice);
  }
  _statistics = new LatticeStatistics<T>;
  _statistics_on = true;

  _commStream.init_nh();
  _commStream.add_cells(1);
  _commStream.init();

  if (_commBC_on) _commBC.init_nh();
}


template<typename T, template<typename U> class Lattice>
bool SuperLattice2D<T,Lattice>::set(T iX, T iY, Cell<T,Lattice> const& cell) {

  bool found = false;
  int locX, locY;
  for (int iC=0; iC<_load.size(); iC++) {
    if(_cGeometry.get_cuboid(_load.glob(iC)).checkPoint(iX, iY, locX, locY, _overlap)) {
      _blockLattices[iC].get(locX,locY) = cell;
      found = true;
    }
  }
  return found;
}

template<typename T, template<typename U> class Lattice>
bool SuperLattice2D<T,Lattice>::get(T iX, T iY, Cell<T,Lattice>& cell) const {

  int locX, locY;
  bool found = false;
  int foundIC = 0;

  for (int iC=0; iC<_cGeometry.get_nC(); iC++) {
    if(_cGeometry.get_cuboid(iC).checkPoint(iX, iY, locX, locY)) {
      found = true;
      foundIC = iC;
      break;
    }
  }

#ifdef PARALLEL_MODE_MPI
  const int sizeOfCell = Lattice<T>::q + Lattice<T>::ExternalField::numScalars;
  T* cellData = new T[sizeOfCell];

  if (found) {
    if (_load.rank(foundIC)==singleton::mpi().getRank()) {
      _lattices[_load.loc(foundIC)].get(locX,locY).serialize(cellData);
    }
    singleton::mpi().bCast(cellData, sizeOfCell, _load.rank(foundIC));
    cell.unSerialize(cellData);
    delete [] cellData;
  }
#else
  if (found) {
    cell = _lattices[_load.loc(foundIC)].get(locX,locY);
  }
#endif

  return found;
}

template<typename T, template<typename U> class Lattice>
Cell<T,Lattice> SuperLattice2D<T,Lattice>::get(int iC, T locX, T locY) const {
  Cell<T,Lattice> cell;
#ifdef PARALLEL_MODE_MPI
  const int sizeOfCell = Lattice<T>::q + Lattice<T>::ExternalField::numScalars;
  T* cellData = new T[sizeOfCell];

  if (_load.rank(iC)==singleton::mpi().getRank()) {
    _lattices[_load.loc(iC)].get(locX,locY).serialize(cellData);
  }
  singleton::mpi().bCast(cellData, sizeOfCell, _load.rank(iC));
  cell.unSerialize(cellData);

  delete [] cellData;
#else
  cell = _lattices[_load.loc(iC)].get(locX,locY);
#endif
  return cell;
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::initialize() {

  if (_commBC_on) {
    _commBC.init();
  }
  for (int iC=0; iC<_load.size(); iC++) {
    //AENDERN VON INI in BLOCKLATTICEVIEW!!!!
    //_lattices[iC].initialize();
    //_lattices[iC].postProcess();
  }
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::defineDynamics (
  T x0, T x1, T y0, T y1, Dynamics<T,Lattice>* dynamics ) {

  int locX0, locX1, locY0, locY1;
  for (int iC=0; iC<_load.size(); iC++) {
    if (_cGeometry.get_cuboid(_load.glob(iC)).checkInters(x0, x1, y0, y1, locX0, locX1, locY0, locY1, _overlap)) {
      _blockLattices[iC].defineDynamics(locX0, locX1, locY0, locY1, dynamics);
    }
  }
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T, Lattice>::defineDynamics(BlockGeometryStatistics2D* blockGeoSta,
    T x0, T x1, T y0, T y1,
    Dynamics<T, Lattice>* dynamics,
    int material) {
  int locX, locY;
  for (int iX = x0; iX <= x1; ++iX) {
    for (int iY = y0; iY <= y1; ++iY) {
      if (blockGeoSta->getBlockGeometry()->getMaterial(iX, iY)
          == material) {
        for (int iC = 0; iC < _load.size(); iC++) {
          if (_cGeometry.get_cuboid(_load.glob(iC)).checkPoint(
                iX, iY, locX, locY, _overlap)) {
            _blockLattices[iC].defineDynamics(locX, locX, locY,
                                              locY, dynamics);
          }
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T, Lattice>::defineDynamics(
  BlockGeometryStatistics2D* blockGeoSta,
  Dynamics<T, Lattice>* dynamics,
  int material) {

  defineDynamics(blockGeoSta,
                 -_overlap, blockGeoSta->getBlockGeometry()->getNx() - 1 + _overlap,
                 -_overlap, blockGeoSta->getBlockGeometry()->getNy() - 1 + _overlap,
                 dynamics, material);
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::defineRhoU (
  T x0, T x1, T y0, T y1, T rho, const T u[Lattice<T>::d] ) {

  int locX0, locX1, locY0, locY1;
  for (int iC=0; iC<_load.size(); iC++) {
    if (_cGeometry.get_cuboid(_load.glob(iC)).checkInters(x0, x1, y0, y1, locX0, locX1, locY0, locY1, _overlap)) {
      for (int iX=locX0; iX<=locX1; iX++) {
        for (int iY=locY0; iY<=locY1; iY++) {
          _blockLattices[iC].get(iX,iY).defineRhoU(rho, u);
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::defineRho (
  T x0, T x1, T y0, T y1, T rho ) {

  int locX0, locX1, locY0, locY1;
  for (int iC=0; iC<_load.size(); iC++) {
    if (_cGeometry.get_cuboid(_load.glob(iC)).checkInters( x0, x1, y0, y1,
        locX0, locX1, locY0, locY1, _overlap)) {
      for (int iX=locX0; iX<=locX1; iX++) {
        for (int iY=locY0; iY<=locY1; iY++) {
          _blockLattices[iC].get(iX,iY).defineRho(rho);
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::defineU (
  T x0, T x1, T y0, T y1, const T u[Lattice<T>::d] ) {

  int locX0, locX1, locY0, locY1;
  for (int iC=0; iC<_load.size(); iC++) {
    if (_cGeometry.get_cuboid(_load.glob(iC)).checkInters( x0, x1, y0, y1,
        locX0, locX1, locY0, locY1, _overlap)) {
      for (int iX=locX0; iX<=locX1; iX++) {
        for (int iY=locY0; iY<=locY1; iY++) {
          _blockLattices[iC].get(iX,iY).defineU(u);
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::defineExternalField (
  T x0, T x1, T y0, T y1, int fieldBeginsAt, int sizeOfField, T* field ) {
  int locX0, locX1, locY0, locY1;
  for (int iC=0; iC<_load.size(); iC++) {
    if (_cGeometry.get_cuboid(_load.glob(iC)).checkInters(x0, x1, y0, y1, locX0, locX1, locY0, locY1, _overlap)) {
      for (int iX=locX0; iX<=locX1; iX++) {
        for (int iY=locY0; iY<=locY1; iY++) {
          _blockLattices[iC].get(iX,iY).defineExternalField (
            fieldBeginsAt, sizeOfField, field);
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::iniEquilibrium (
  T x0, T x1, T y0, T y1, T rho, const T u[Lattice<T>::d] ) {

  int locX0, locX1, locY0, locY1;
  for (int iC=0; iC<_load.size(); iC++) {
    if (_cGeometry.get_cuboid(_load.glob(iC)).checkInters(x0, x1, y0, y1, locX0, locX1, locY0, locY1, _overlap)) {
      for (int iX=locX0; iX<=locX1; iX++) {
        for (int iY=locY0; iY<=locY1; iY++) {
          _blockLattices[iC].get(iX,iY).iniEquilibrium(rho, u);
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::collide () {

  for (int iC=0; iC<_load.size(); iC++) {
    _lattices[iC].collide();
  }
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::collide (T x0, T x1, T y0, T y1) {

  int locX0, locX1, locY0, locY1;
  for (int iC=0; iC<_load.size(); iC++) {
    if (_cGeometry.get_cuboid(_load.glob(iC)).checkInters(x0, x1, y0, y1, locX0, locX1, locY0, locY1, _overlap)) {
      _lattices[iC].collide(locX0, locX1, locY0, locY1);
    }
  }
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::stream () {

  _commStream.send();
  _commStream.receive();
  _commStream.write();

  for (int iC=0; iC<_load.size(); iC++) {
    _blockLattices[iC].stream(_overlap-1, _blockLattices[iC].getNx() - _overlap,
                              _overlap-1, _blockLattices[iC].getNy() - _overlap);
  }
  if (_commBC_on) {
    _commBC.send();
    _commBC.receive();
    _commBC.write();
  }

  for (int iC=0; iC<_load.size(); iC++) {
    _lattices[iC].postProcess();
  }
  if (_statistics_on) reset_statistics();
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::stream (T x0, T x1, T y0, T y1) {

  _commStream.send();
  _commStream.receive();
  _commStream.write();

  int locX0, locX1, locY0, locY1;
  for (int iC=0; iC<_load.size(); iC++) {
    if (_cGeometry.get_cuboid(_load.glob(iC)).checkInters(x0, x1, y0, y1, locX0, locX1, locY0, locY1, _overlap)) {
      _blockLattices[iC].stream(locX0, locX1, locY0, locY1);
    }
  }
  if (_commBC_on) {
    _commBC.send();
    _commBC.receive();
    _commBC.write();
  }

  for (int iC=0; iC<_load.size(); iC++) {
    _lattices[iC].postProcess();
  }
  if (_statistics_on) reset_statistics();
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::collideAndStream () {

  for (int iC=0; iC<_load.size(); iC++) {
    int x1 = _lattices[iC].getNx() - 1;
    int y1 = _lattices[iC].getNy() - 1;
    _lattices[iC].collide(0,x1,0,0);
    _lattices[iC].collide(0,x1,y1,y1);
    _lattices[iC].collide(0,0,1,y1-1);
    _lattices[iC].collide(x1,x1,1,y1-1);
  }

  for (int iC=0; iC<_load.size(); iC++) {
    _blockLattices[iC].bulkCollideAndStream(_overlap+1, _blockLattices[iC].getNx() - _overlap-2,
                                            _overlap+1, _blockLattices[iC].getNy() - _overlap-2);
  }

  _commStream.send();
  _commStream.receive();
  _commStream.write();

  for (int iC=0; iC<_load.size(); iC++) {
    int x1 = _blockLattices[iC].getNx() - 1;
    int y1 = _blockLattices[iC].getNy() - 1;
    _blockLattices[iC].boundaryStream(0,x1,0,y1, _overlap-1,x1-_overlap+1,  _overlap-1,_overlap);
    _blockLattices[iC].boundaryStream(0,x1,0,y1, _overlap-1,x1-_overlap+1,  y1-_overlap,y1-_overlap+1);
    _blockLattices[iC].boundaryStream(0,x1,0,y1, _overlap-1, _overlap,      _overlap+1, y1-_overlap-1);
    _blockLattices[iC].boundaryStream(0,x1,0,y1, x1-_overlap,x1-_overlap+1, _overlap+1, y1-_overlap-1);
  }


  if (_commBC_on) {
    _commStream.send();
    _commStream.receive();
    _commStream.write();
    //_commBC.send();
    //_commBC.receive();
    //_commBC.write();
  }

  for (int iC=0; iC<_load.size(); iC++) {
    _lattices[iC].postProcess();
  }
  if (_statistics_on) reset_statistics();
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::stripeOffDensityOffset (
  int x0, int x1, int y0, int y1, T offset )
{

  int locX0, locX1, locY0, locY1;
  for (int iC = 0; iC < _load.size(); iC++) {
    if (_cGeometry.get_cuboid(_load.glob(iC)).checkInters(x0, x1, y0, y1,
        locX0, locX1, locY0, locY1, _overlap)) {
      _blockLattices[iC].stripeOffDensityOffset(locX0, locX1, locY0, locY1,
          offset);
    }
  }
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::stripeOffDensityOffset(T offset) {

  for (int iC = 0; iC < _load.size(); iC++) {
    _blockLattices[iC].stripeOffDensityOffset(offset);
  }
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::save(std::string fName, bool enforceUint) {
  for (int block = 0; block < _cGeometry.get_nC(); ++block){
    std::ofstream* ostr = 0;
    if (singleton::mpi().getRank() == _load.rank(block)) {
      std::stringstream ss;
      ss << fName << block;
      ostr = new std::ofstream(ss.str().c_str());
      OLB_PRECONDITION( *ostr );
    }
    DataSerializer<T> const& serializer = _blockLattices[_load.loc(block)].getSerializer(IndexOrdering::memorySaving);

    size_t fullSize = 0;
    if (singleton::mpi().getRank() == _load.rank(block)) {
      fullSize = serializer.getSize();
      size_t binarySize = (size_t) (fullSize * sizeof(T));
      if (enforceUint) {
        Base64Encoder<unsigned int> sizeEncoder(*ostr, 1);
        OLB_PRECONDITION(binarySize <= std::numeric_limits<unsigned int>::max());
        unsigned int uintBinarySize = (unsigned int)binarySize;
        sizeEncoder.encode(&uintBinarySize, 1);
      }
      else {
        Base64Encoder<size_t> sizeEncoder(*ostr, 1);
        sizeEncoder.encode(&binarySize, 1);
      }
    }
    Base64Encoder<T>* dataEncoder = 0;
    if (singleton::mpi().getRank() == _load.rank(block)) {
      dataEncoder = new Base64Encoder<T>(*ostr, fullSize);
    }
    while (!serializer.isEmpty()) {
      size_t bufferSize;
      const T* dataBuffer = serializer.getNextDataBuffer(bufferSize);
      if (singleton::mpi().getRank() == _load.rank(block)) {
        dataEncoder->encode(dataBuffer, bufferSize);
      }
    }
    delete dataEncoder;
    delete ostr;
  }
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::load(std::string fName, bool enforceUint) {
  for (int block = 0; block < _cGeometry.get_nC(); ++block){
    if (singleton::mpi().getRank() == _load.rank(block)) {
      std::ifstream* istr = 0;
      std::stringstream ss;
      ss << fName << block;
      istr = new std::ifstream(ss.str().c_str());
      OLB_PRECONDITION( *istr );
      DataUnSerializer<T>& unSerializer = _blockLattices[_load.loc(block)].getUnSerializer(IndexOrdering::memorySaving);
      size_t binarySize;
      if (enforceUint) {
        unsigned int uintBinarySize;
        Base64Decoder<unsigned int> sizeDecoder(*istr, 1);
        sizeDecoder.decode(&uintBinarySize, 1);
        binarySize = uintBinarySize;
      }
      else {
        Base64Decoder<size_t> sizeDecoder(*istr, 1);
        sizeDecoder.decode(&binarySize, 1);
      }
      size_t fullSize = binarySize / sizeof(T);
      OLB_PRECONDITION(fullSize == unSerializer.getSize());
      Base64Decoder<T>* dataDecoder = 0;
      dataDecoder = new Base64Decoder<T>(*istr, unSerializer.getSize());
      while (!unSerializer.isFull()) {
        size_t bufferSize = 0;
        T* dataBuffer = unSerializer.getNextDataBuffer(bufferSize);
        dataDecoder->decode(dataBuffer, bufferSize);
        unSerializer.commitData();
      }
      delete dataDecoder;
      delete istr;
    }
  }
}

template<typename T, template<typename U> class Lattice>
void SuperLattice2D<T,Lattice>::reset_statistics () {

  T weight;
  T sum_weight       = 0;
  T average_rho      = 0;
  T average_energy   = 0;
  T maxU             = 0;
  T delta            = 0;

  getStatistics().reset();

  for (int iC=0; iC<_load.size(); iC++) {
    delta           = _cGeometry.get_cuboid(_load.glob(iC)).get_delta();
    weight          = _blockLattices[iC].getStatistics().getNumCells()
                      * delta*delta;
    sum_weight     += weight;
    average_rho    +=
      _blockLattices[iC].getStatistics().getAverageRho() * weight;
    average_energy +=
      _blockLattices[iC].getStatistics().getAverageEnergy() * weight;
    if(maxU<_blockLattices[iC].getStatistics().getMaxU() / delta) {
      maxU = _blockLattices[iC].getStatistics().getMaxU() / delta;
    }
  }
#ifdef PARALLEL_MODE_MPI
  singleton::mpi().reduceAndBcast(sum_weight, MPI_SUM);
  singleton::mpi().reduceAndBcast(average_rho, MPI_SUM);
  singleton::mpi().reduceAndBcast(average_energy, MPI_SUM);
  singleton::mpi().reduceAndBcast(maxU,  MPI_MAX);
#endif

  average_rho         = average_rho / sum_weight;
  average_energy      = average_energy / sum_weight;

  getStatistics().reset(average_rho, average_energy, maxU, (int)sum_weight);
  for (int iC=0; iC<_load.size(); iC++) {
    delta = _cGeometry.get_cuboid(_load.glob(iC)).get_delta();
    _blockLattices[iC].getStatistics().reset(average_rho,
        average_energy, maxU * delta, (int)sum_weight);
  }
}

template<typename T, template<typename U> class Lattice>
LatticeStatistics<T>& SuperLattice2D<T,Lattice>::getStatistics() {

  return *_statistics;
}

template<typename T, template<typename U> class Lattice>
LatticeStatistics<T> const&
SuperLattice2D<T,Lattice>::getStatistics() const {

  return *_statistics;
}

} // namespace olb

#endif
