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
 * A helper for initialising 2D boundaries -- generic implementation.
 */


#ifndef SUPER_OFF_BOUNDARY_CONDITION_2D_HH
#define SUPER_OFF_BOUNDARY_CONDITION_2D_HH

#include <vector>
#include "core/offBoundaryCondition2D.h"
#include "superOffBoundaryCondition2D.h"
#include "superLattice2D.h"


namespace olb {


///////// class superOffBoundaryCondition2D ///////////////////////////////

template<typename T, template<typename U> class Lattice>
sOffLatticeBoundaryCondition2D<T,Lattice>::
sOffLatticeBoundaryCondition2D (SuperLattice2D<T,Lattice>& sLattice )
  : clout(std::cout,"sOffLatticeBoundaryCondition2D"),
    _sLattice(sLattice),
    _output(false)
{}

template<typename T, template<typename U> class Lattice>
sOffLatticeBoundaryCondition2D<T,Lattice>::
sOffLatticeBoundaryCondition2D(sOffLatticeBoundaryCondition2D<T,Lattice> const& rhs)
  : clout(std::cout,"sOffLatticeBoundaryCondition2D"),
    _sLattice(rhs._sLattice),
    _output(false)
{
  _blockBCs = rhs._blockBCs;
  _overlap = rhs._overlap;
}

template<typename T, template<typename U> class Lattice>
sOffLatticeBoundaryCondition2D<T,Lattice> sOffLatticeBoundaryCondition2D<T,Lattice>::operator=(
  sOffLatticeBoundaryCondition2D<T,Lattice> rhs) {

  sOffLatticeBoundaryCondition2D<T,Lattice> tmp(rhs);
  return tmp;
}

template<typename T, template<typename U> class Lattice>
sOffLatticeBoundaryCondition2D<T,Lattice>::
~sOffLatticeBoundaryCondition2D() {

  for (unsigned iC=0; iC<_blockBCs.size(); iC++) {
    delete _blockBCs[iC];
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition2D<T,Lattice>::
addOnePointFixedBoundary(int x, int y, int dir, T dist){

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY;

  for (int iC=0; iC<nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
        locX, locY, overlap)) {
      _blockBCs[iC]->addOnePointFixedBoundary(locX, locY, dir, dist);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
        locX, locY)) {
      addPoints2CommBC(locX, locX, locY, locY, iCglob);
    }
  }
  if (_output) {
    clout << "addOnePointFixedBoundary(" << x << ", " << y << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition2D<T,Lattice>::
addTwoPointFixedBoundary(int x, int y, int dir, T dist){

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY;

  for (int iC=0; iC<nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
        locX, locY, overlap)) {
      _blockBCs[iC]->addTwoPointFixedBoundary(locX, locY, dir, dist);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
        locX, locY)) {
      addPoints2CommBC(locX, locX, locY, locY, iCglob);
    }
  }
  if (_output) {
    clout << "addTwoPointFixedBoundary(" << x << ", " << y << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition2D<T,Lattice>::
addThreePointFixedBoundary(int x, int y, int dir, T dist){

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY;

  for (int iC=0; iC<nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
        locX, locY, overlap)) {
      _blockBCs[iC]->addThreePointFixedBoundary(locX, locY, dir, dist);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
        locX, locY)) {
      addPoints2CommBC(locX, locX, locY, locY, iCglob);
    }
  }
  if (_output) {
    clout << "addThreePointFixedBoundary(" << x << ", " << y << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition2D<T,Lattice>::
addOnePointVelocityBoundary(int x, int y, int dir, T dist, T uX, T uY){

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY;

  for (int iC=0; iC<nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
        locX, locY, overlap)) {
      _blockBCs[iC]->addOnePointVelocityBoundary(locX, locY, dir, dist, uX, uY);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
        locX, locY)) {
      addPoints2CommBC(locX, locX, locY, locY, iCglob);
    }
  }
  if (_output) {
    clout << "addOnePointVelocityBoundary(" << x << ", " << y << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition2D<T,Lattice>::
addTwoPointVelocityBoundary(int x, int y, int dir, T dist, T uX, T uY){

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY;

  for (int iC=0; iC<nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
        locX, locY, overlap)) {
      _blockBCs[iC]->addTwoPointVelocityBoundary(locX, locY, dir, dist, uX, uY);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
        locX, locY)) {
      addPoints2CommBC(locX, locX, locY, locY, iCglob);
    }
  }
  if (_output) {
    clout << "addTwoPointVelocityBoundary(" << x << ", " << y << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition2D<T,Lattice>::
addThreePointVelocityBoundary(int x, int y, int dir, T dist, T uX, T uY){

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY;

  for (int iC=0; iC<nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
        locX, locY, overlap)) {
      _blockBCs[iC]->addThreePointVelocityBoundary(locX, locY, dir, dist, uX, uY);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y,
        locX, locY)) {
      addPoints2CommBC(locX, locX, locY, locY, iCglob);
    }
  }
  if (_output) {
    clout << "addThreePointVelocityBoundary(" << x << ", " << y << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition2D<T,Lattice>::
addFixedBoundary(BlockGeometryStatistics2D* blockGeoSta, int x, int y, int dir, T dist) {
  const int* c = Lattice<T>::c[dir];
  if (blockGeoSta->getBlockGeometry()->getMaterial(x-c[0], y-c[1]) != 1)
    addOnePointFixedBoundary(x, y, dir, dist);
  else if (blockGeoSta->getBlockGeometry()->getMaterial(x-2*c[0], y-2*c[1]) != 1)
    addTwoPointFixedBoundary(x, y, dir, dist);
  else
    addThreePointFixedBoundary(x, y, dir, dist);
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition2D<T,Lattice>::
addVelocityBoundary(BlockGeometryStatistics2D* blockGeoSta, int x, int y, int dir, T dist, T uX, T uY) {
  const int* c = Lattice<T>::c[dir];
  if (blockGeoSta->getBlockGeometry()->getMaterial(x-c[0], y-c[1]) != 1)
    addOnePointVelocityBoundary(x, y, dir, dist, uX, uY);
  else if (blockGeoSta->getBlockGeometry()->getMaterial(x-2*c[0], y-2*c[1]) != 1)
    addTwoPointVelocityBoundary(x, y, dir, dist, uX, uY);
  else
    addThreePointVelocityBoundary(x, y, dir, dist, uX, uY);
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition2D<T,Lattice>::
addPoints2CommBC(int x0, int x1, int y0, int y1, int iCglob) {

  if (_overlap!=0) {
    int nC  = _sLattice.get_cGeometry().get_nC();
    T globX = _sLattice.get_cGeometry().get_cuboid(iCglob).get_globPosX();
    T globY = _sLattice.get_cGeometry().get_cuboid(iCglob).get_globPosY();
    T delta = _sLattice.get_cGeometry().get_cuboid(iCglob).get_delta();

    for (int iOverl=1; iOverl<=_overlap; iOverl++) {
      for (int iX=x0-iOverl; iX<=x1+iOverl; iX++) {
        for (int iY=y0-iOverl; iY<=y1+iOverl; iY++) {
          if (iX==x0-iOverl || iX==x1+iOverl ||
              iY==y0-iOverl || iY==y1+iOverl) {
            T nextX = globX +iX*delta;
            T nextY = globY +iY*delta;
            int found_iC = _sLattice.get_cGeometry().get_iC(nextX, nextY);
            if (found_iC!=nC && found_iC!=iCglob) {
              _sLattice.get_commBC().add_cell(iCglob, nextX, nextY);
            }
          }
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition2D<T,Lattice>::outputOn() {
  _output = true;
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition2D<T,Lattice>::outputOff() {
  _output = false;
}

////////////////// Factory functions //////////////////////////////////

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
void createBouzidiBoundaryCondition2D(sOffLatticeBoundaryCondition2D<T,Lattice>& sBC) {

  int nC = sBC.get_sLattice().get_load().size();
  sBC.set_overlap(1);
  for (int iC=0; iC<nC; iC++) {
    OffLatticeBoundaryCondition2D<T,Lattice>* blockBC
    = createBouzidiBoundaryCondition2D<T,Lattice,MixinDynamics>(sBC.get_sLattice().get_blockLattice(iC));
    sBC.get_blockBCs().push_back(blockBC);
  }
}

}  // namespace olb

#endif
