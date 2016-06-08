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
 * A helper for initialising 3D boundaries -- generic implementation.
 */

#ifndef SUPER_BOUNDARY_CONDITION_3D_HH
#define SUPER_BOUNDARY_CONDITION_3D_HH

#include <vector>
#include "core/boundaryCondition3D.h"
#include "superBoundaryCondition3D.h"
#include "superLattice3D.h"

namespace olb {

///////// class superBoundaryCondition3D ///////////////////////////////

template<typename T, template<typename U> class Lattice>
sOnLatticeBoundaryCondition3D<T, Lattice>::sOnLatticeBoundaryCondition3D(
  SuperLattice3D<T, Lattice>& sLattice) :
  clout(std::cout,"sOnLatticeBoundaryCondition3D"),
  _sLattice(sLattice),
  _output(false) {
}

template<typename T, template<typename U> class Lattice>
sOnLatticeBoundaryCondition3D<T, Lattice>::sOnLatticeBoundaryCondition3D(
  sOnLatticeBoundaryCondition3D<T, Lattice> const& rhs) :
  clout(std::cout,"sOnLatticeBoundaryCondition3D"),
  _sLattice(rhs._sLattice),
  _output(false) {

  _blockBCs = rhs._blockBCs;
  _overlap = rhs._overlap;
}

template<typename T, template<typename U> class Lattice>
sOnLatticeBoundaryCondition3D<T, Lattice> sOnLatticeBoundaryCondition3D<T,
Lattice>::operator=(sOnLatticeBoundaryCondition3D<T, Lattice> rhs) {

  sOnLatticeBoundaryCondition3D<T, Lattice> tmp(rhs);
  return tmp;
}

template<typename T, template<typename U> class Lattice>
sOnLatticeBoundaryCondition3D<T, Lattice>::~sOnLatticeBoundaryCondition3D() {

  for (unsigned iC = 0; iC < _blockBCs.size(); iC++) {
    delete _blockBCs[iC];
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addVelocityBoundary0N(T x0,
    T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addVelocityBoundary0N(locX0, locX1, locY0, locY1,
                                           locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addVelocityBoundary0N(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addVelocityBoundary0P(T x0,
    T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addVelocityBoundary0P(locX0, locX1, locY0, locY1,
                                           locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addVelocityBoundary0P(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addVelocityBoundary1N(T x0,
    T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addVelocityBoundary1N(locX0, locX1, locY0, locY1,
                                           locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addVelocityBoundary1N(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addVelocityBoundary1P(T x0,
    T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addVelocityBoundary1P(locX0, locX1, locY0, locY1,
                                           locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addVelocityBoundary1P(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addVelocityBoundary2N(T x0,
    T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addVelocityBoundary2N(locX0, locX1, locY0, locY1,
                                           locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addVelocityBoundary2N(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addVelocityBoundary2P(T x0,
    T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addVelocityBoundary2P(locX0, locX1, locY0, locY1,
                                           locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addVelocityBoundary2P(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addPressureBoundary0N(T x0,
    T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addPressureBoundary0N(locX0, locX1, locY0, locY1,
                                           locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addPressureBoundary0N(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addPressureBoundary0P(T x0,
    T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addPressureBoundary0P(locX0, locX1, locY0, locY1,
                                           locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addPressureBoundary0P(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addPressureBoundary1N(T x0,
    T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addPressureBoundary1N(locX0, locX1, locY0, locY1,
                                           locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addPressureBoundary1N(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addPressureBoundary1P(T x0,
    T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addPressureBoundary1P(locX0, locX1, locY0, locY1,
                                           locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addPressureBoundary1P(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addPressureBoundary2N(T x0,
    T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addPressureBoundary2N(locX0, locX1, locY0, locY1,
                                           locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addPressureBoundary2N(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addPressureBoundary2P(T x0,
    T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addPressureBoundary2P(locX0, locX1, locY0, locY1,
                                           locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addPressureBoundary2P(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityEdge0NN(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addExternalVelocityEdge0NN(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityEdge0NN(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityEdge0NP(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addExternalVelocityEdge0NP(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityEdge0NP(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityEdge0PN(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addExternalVelocityEdge0PN(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityEdge0PN(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityEdge0PP(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addExternalVelocityEdge0PP(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityEdge0PP(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityEdge1NN(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addExternalVelocityEdge1NN(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityEdge1NN(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityEdge1NP(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addExternalVelocityEdge1NP(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityEdge1NP(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityEdge1PN(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addExternalVelocityEdge1PN(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityEdge1PN(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityEdge1PP(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addExternalVelocityEdge1PP(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityEdge1PP(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityEdge2NN(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addExternalVelocityEdge2NN(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityEdge2NN(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityEdge2NP(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addExternalVelocityEdge2NP(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityEdge2NP(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityEdge2PN(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addExternalVelocityEdge2PN(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityEdge2PN(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityEdge2PP(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addExternalVelocityEdge2PP(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityEdge2PP(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityEdge0NN(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addInternalVelocityEdge0NN(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityEdge0NN(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityEdge0NP(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addInternalVelocityEdge0NP(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityEdge0NP(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityEdge0PN(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addInternalVelocityEdge0PN(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityEdge0PN(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityEdge0PP(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addInternalVelocityEdge0PP(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityEdge0PP(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityEdge1NN(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addInternalVelocityEdge1NN(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityEdge1NN(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityEdge1NP(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addInternalVelocityEdge1NP(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityEdge1NP(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityEdge1PN(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addInternalVelocityEdge1PN(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityEdge1PN(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityEdge1PP(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addInternalVelocityEdge1PP(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityEdge1PP(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityEdge2NN(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addInternalVelocityEdge2NN(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityEdge2NN(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityEdge2NP(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addInternalVelocityEdge2NP(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityEdge2NP(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityEdge2PN(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addInternalVelocityEdge2PN(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityEdge2PN(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityEdge2PP(
  T x0, T x1, T y0, T y1, T z0, T z1, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX0, locX1, locY0, locY1, locZ0, locZ1;
  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1,
        overlap)) {
      _blockBCs[iC]->addInternalVelocityEdge2PP(locX0, locX1, locY0,
          locY1, locZ0, locZ1, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkInters(x0, x1,
        y0, y1, z0, z1, locX0, locX1, locY0, locY1, locZ0, locZ1)) {
      addPoints2CommBC(locX0, locX1, locY0, locY1, locZ0, locZ1, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityEdge2PP(" << x0 <<", " << x1 << ", " << y0 << ", " << y1 << ", " << z0 << ", " << z1 << ", " << omega << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityCornerNNN(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addExternalVelocityCornerNNN(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityCornerNNN(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityCornerNNP(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addExternalVelocityCornerNNP(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityCornerNNP(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityCornerNPN(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addExternalVelocityCornerNPN(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityCornerNPN(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityCornerNPP(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addExternalVelocityCornerNPP(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityCornerNPP(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityCornerPNN(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addExternalVelocityCornerPNN(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityCornerPNN(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityCornerPNP(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addExternalVelocityCornerPNP(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityCornerPNP(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityCornerPPN(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addExternalVelocityCornerPPN(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityCornerPPN(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addExternalVelocityCornerPPP(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addExternalVelocityCornerPPP(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addExternalVelocityCornerPPP(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityCornerNNN(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addInternalVelocityCornerNNN(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityCornerNNN(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityCornerNNP(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addInternalVelocityCornerNNP(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityCornerNNP(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityCornerNPN(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addInternalVelocityCornerNPN(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityCornerNPN(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityCornerNPP(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addInternalVelocityCornerNPP(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityCornerNPP(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityCornerPNN(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addInternalVelocityCornerPNN(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityCornerPNN(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityCornerPNP(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addInternalVelocityCornerPNP(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityCornerPNP(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityCornerPPN(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addInternalVelocityCornerPPN(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityCornerPPN(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addInternalVelocityCornerPPP(
  T x, T y, T z, T omega) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC = 0; iC < nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addInternalVelocityCornerPPP(locX, locY, locZ, omega);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addInternalVelocityCornerPPP(" << x <<", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addVelocityBoundary(
  SuperGeometry3D& superGeometry, int material, int x0, int x1, int y0, int y1,
  int z0, int z1, T omega) {
  std::vector<int> discreteNormal(4, 0);

  for (int iX = x0; iX <= x1; iX++) {
    for (int iY = y0; iY <= y1; iY++) {
      for (int iZ = z0; iZ <= z1; iZ++) {

        if (superGeometry.getMaterial(iX, iY, iZ)
            == material) {
          discreteNormal = superGeometry.getStatistics().getType(iX, iY, iZ);
          if (discreteNormal[0] == 0) {

            if (discreteNormal[1] != 0 && discreteNormal[1] == -1) {

              addVelocityBoundary0N(iX, iX, iY, iY, iZ, iZ, omega);

            }

            else if (discreteNormal[1] != 0 && discreteNormal[1]
                     == 1) {

              addVelocityBoundary0P(iX, iX, iY, iY, iZ, iZ, omega);

            }

            else if (discreteNormal[2] != 0 && discreteNormal[2]
                     == -1) {

              addVelocityBoundary1N(iX, iX, iY, iY, iZ, iZ, omega);

            }

            else if (discreteNormal[2] != 0 && discreteNormal[2]
                     == 1) {

              addVelocityBoundary1P(iX, iX, iY, iY, iZ, iZ, omega);

            }

            else if (discreteNormal[3] != 0 && discreteNormal[3]
                     == -1) {

              addVelocityBoundary2N(iX, iX, iY, iY, iZ, iZ, omega);

            }

            else if (discreteNormal[3] != 0 && discreteNormal[3]
                     == 1) {

              addVelocityBoundary2P(iX, iX, iY, iY, iZ, iZ, omega);

            }
          }

          else if (discreteNormal[0] == 1) {

            if (discreteNormal[1] == 1 && discreteNormal[2] == 1
                && discreteNormal[3] == 1) {

              addExternalVelocityCornerPPP(iX, iY, iZ, omega);

            }

            else if (discreteNormal[1] == 1 && discreteNormal[2]
                     == -1 && discreteNormal[3] == 1) {

              addExternalVelocityCornerPNP(iX, iY, iZ, omega);

            }

            else if (discreteNormal[1] == 1 && discreteNormal[2]
                     == 1 && discreteNormal[3] == -1) {

              addExternalVelocityCornerPPN(iX, iY, iZ, omega);

            }

            else if (discreteNormal[1] == 1 && discreteNormal[2]
                     == -1 && discreteNormal[3] == -1) {

              addExternalVelocityCornerPNN(iX, iY, iZ, omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == 1 && discreteNormal[3] == 1) {

              addExternalVelocityCornerNPP(iX, iY, iZ, omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == -1 && discreteNormal[3] == 1) {

              addExternalVelocityCornerNNP(iX, iY, iZ, omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == 1 && discreteNormal[3] == -1) {

              addExternalVelocityCornerNPN(iX, iY, iZ, omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == -1 && discreteNormal[3] == -1) {

              addExternalVelocityCornerNNN(iX, iY, iZ, omega);

            }
            ///                     addExternalVelocityCorner<discreteNormal[1],discreteNormal[2],discreteNormal[3]>(iX,iY,iZ, omega);
          }

          else if (discreteNormal[0] == 2) {

            if (discreteNormal[1] == 1 && discreteNormal[2] == 1
                && discreteNormal[3] == 1) {

              addInternalVelocityCornerPPP(iX, iY, iZ, omega);

            }

            else if (discreteNormal[1] == 1 && discreteNormal[2]
                     == -1 && discreteNormal[3] == 1) {

              addInternalVelocityCornerPNP(iX, iY, iZ, omega);

            }

            else if (discreteNormal[1] == 1 && discreteNormal[2]
                     == 1 && discreteNormal[3] == -1) {

              addInternalVelocityCornerPPN(iX, iY, iZ, omega);

            }

            else if (discreteNormal[1] == 1 && discreteNormal[2]
                     == -1 && discreteNormal[3] == -1) {

              addInternalVelocityCornerPNN(iX, iY, iZ, omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == 1 && discreteNormal[3] == 1) {

              addInternalVelocityCornerNPP(iX, iY, iZ, omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == -1 && discreteNormal[3] == 1) {

              addInternalVelocityCornerNNP(iX, iY, iZ, omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == 1 && discreteNormal[3] == -1) {

              addInternalVelocityCornerNPN(iX, iY, iZ, omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == -1 && discreteNormal[3] == -1) {

              addInternalVelocityCornerNNN(iX, iY, iZ, omega);

            }
            ///                     addInternalVelocityCorner<discreteNormal[1],discreteNormal[2],discreteNormal[3]>(iX,iY,iZ, omega);
          }

          else if (discreteNormal[0] == 3) {

            if (discreteNormal[1] == 0 && discreteNormal[2] == 1
                && discreteNormal[3] == 1) {

              addExternalVelocityEdge0PP(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == 0 && discreteNormal[2]
                     == -1 && discreteNormal[3] == 1) {

              addExternalVelocityEdge0NP(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == 0 && discreteNormal[2]
                     == 1 && discreteNormal[3] == -1) {

              addExternalVelocityEdge0PN(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == 0 && discreteNormal[2]
                     == -1 && discreteNormal[3] == -1) {

              addExternalVelocityEdge0NN(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == 1 && discreteNormal[2]
                     == 0 && discreteNormal[3] == 1) {

              addExternalVelocityEdge1PP(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == 0 && discreteNormal[3] == 1) {

              addExternalVelocityEdge1PN(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == 1 && discreteNormal[2]
                     == 0 && discreteNormal[3] == -1) {

              addExternalVelocityEdge1NP(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == 0 && discreteNormal[3] == -1) {

              addExternalVelocityEdge1NN(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == 1 && discreteNormal[2]
                     == 1 && discreteNormal[3] == 0) {

              addExternalVelocityEdge2PP(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == 1 && discreteNormal[3] == 0) {

              addExternalVelocityEdge2NP(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == 1 && discreteNormal[2]
                     == -1 && discreteNormal[3] == 0) {

              addExternalVelocityEdge2PN(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == -1 && discreteNormal[3] == 0) {

              addExternalVelocityEdge2NN(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }
          }

          else if (discreteNormal[0] == 4) {

            if (discreteNormal[1] == 0 && discreteNormal[2] == 1
                && discreteNormal[3] == 1) {

              addInternalVelocityEdge0PP(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == 0 && discreteNormal[2]
                     == -1 && discreteNormal[3] == 1) {

              addInternalVelocityEdge0NP(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == 0 && discreteNormal[2]
                     == 1 && discreteNormal[3] == -1) {

              addInternalVelocityEdge0PN(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == 0 && discreteNormal[2]
                     == -1 && discreteNormal[3] == -1) {

              addInternalVelocityEdge0NN(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == 1 && discreteNormal[2]
                     == 0 && discreteNormal[3] == 1) {

              addInternalVelocityEdge1PP(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == 0 && discreteNormal[3] == 1) {

              addInternalVelocityEdge1PN(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == 1 && discreteNormal[2]
                     == 0 && discreteNormal[3] == -1) {

              addInternalVelocityEdge1NP(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == 0 && discreteNormal[3] == -1) {

              addInternalVelocityEdge1NN(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == 1 && discreteNormal[2]
                     == 1 && discreteNormal[3] == 0) {

              addInternalVelocityEdge2PP(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == 1 && discreteNormal[3] == 0) {

              addInternalVelocityEdge2NP(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == 1 && discreteNormal[2]
                     == -1 && discreteNormal[3] == 0) {

              addInternalVelocityEdge2PN(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }

            else if (discreteNormal[1] == -1 && discreteNormal[2]
                     == -1 && discreteNormal[3] == 0) {

              addInternalVelocityEdge2NN(iX, iX, iY, iY, iZ, iZ,
                                         omega);

            }
          }
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addVelocityBoundary(
  SuperGeometry3D& superGeometry, int material, T omega) {

  addVelocityBoundary(superGeometry, material, 0,
                      superGeometry.getNx(), 0,
                      superGeometry.getNy(), 0,
                      superGeometry.getNz(), omega);

}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addPressureBoundary(
  SuperGeometry3D& superGeometry, int material, int x0, int x1, int y0, int y1,
  int z0, int z1, T omega) {
  std::vector<int> discreteNormal(4, 0);

  for (int iX = x0; iX <= x1; iX++) {
    for (int iY = y0; iY <= y1; iY++) {
      for (int iZ = z0; iZ <= z1; iZ++) {

        if (superGeometry.getMaterial(iX, iY, iZ)
            == material) {

          discreteNormal = superGeometry.getStatistics().getType(iX, iY, iZ);

          if (discreteNormal[0] == 0) {

            if (discreteNormal[1] != 0 && discreteNormal[1] == -1) {

              addPressureBoundary0N(iX, iX, iY, iY, iZ, iZ, omega);

            }

            else if (discreteNormal[1] != 0 && discreteNormal[1]
                     == 1) {

              addPressureBoundary0P(iX, iX, iY, iY, iZ, iZ, omega);

            }

            else if (discreteNormal[2] != 0 && discreteNormal[2]
                     == -1) {

              addPressureBoundary1N(iX, iX, iY, iY, iZ, iZ, omega);

            }

            else if (discreteNormal[2] != 0 && discreteNormal[2]
                     == 1) {

              addPressureBoundary1P(iX, iX, iY, iY, iZ, iZ, omega);

            }

            else if (discreteNormal[3] != 0 && discreteNormal[3]
                     == -1) {

              addPressureBoundary2N(iX, iX, iY, iY, iZ, iZ, omega);

            }

            else if (discreteNormal[3] != 0 && discreteNormal[3]
                     == 1) {

              addPressureBoundary2P(iX, iX, iY, iY, iZ, iZ, omega);

            }
          }
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addPressureBoundary(
  SuperGeometry3D& superGeometry, int material, T omega) {

  addPressureBoundary(superGeometry, material, 0,
                      superGeometry.getNx(), 0,
                      superGeometry.getNy(), 0,
                      superGeometry.getNz(), omega);

}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::addPoints2CommBC(int x0,
    int x1, int y0, int y1, int z0, int z1, int iCglob) {

  if (_overlap != 0) {
    int nC = _sLattice.get_cGeometry().get_nC();
    T globX = _sLattice.get_cGeometry().get_cuboid(iCglob).get_globPosX();
    T globY = _sLattice.get_cGeometry().get_cuboid(iCglob).get_globPosY();
    T globZ = _sLattice.get_cGeometry().get_cuboid(iCglob).get_globPosZ();
    T delta = _sLattice.get_cGeometry().get_cuboid(iCglob).get_delta();

    for (int iOverl = 1; iOverl <= _overlap; iOverl++) {
      for (int iX = x0 - iOverl; iX <= x1 + iOverl; iX++) {
        for (int iY = y0 - iOverl; iY <= y1 + iOverl; iY++) {
          for (int iZ = z0 - iOverl; iZ <= z1 + iOverl; iZ++) {
            if (iX == x0 - iOverl || iX == x1 + iOverl || iY == y0
                - iOverl || iY == y1 + iOverl || iZ == z0
                - iOverl || iZ == z1 + iOverl) {
              T nextX = globX + iX * delta;
              T nextY = globY + iY * delta;
              T nextZ = globZ + iZ * delta;
              int found_iC = _sLattice.get_cGeometry().get_iC(
                               nextX, nextY, nextZ);
              if (found_iC != nC && found_iC != iCglob) {
                _sLattice.get_commBC().add_cell(iCglob, nextX,
                                                nextY, nextZ);
              }
            }
          }
        }
      }
    }
  }
}

////////////////// Factory functions //////////////////////////////////

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
void createLocalBoundaryCondition3D(
  sOnLatticeBoundaryCondition3D<T, Lattice>& sBC) {

  int nC = sBC.get_sLattice().get_load().size();
  sBC.set_overlap(0);
  for (int iC = 0; iC < nC; iC++) {
    OnLatticeBoundaryCondition3D<T, Lattice>* blockBC =
      createLocalBoundaryCondition3D(
        sBC.get_sLattice().get_blockLattice(iC));
    sBC.get_blockBCs().push_back(blockBC);
  }
}

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
void createInterpBoundaryCondition3D(
  sOnLatticeBoundaryCondition3D<T, Lattice>& sBC) {

  int nC = sBC.get_sLattice().get_load().size();
  sBC.set_overlap(1);
  for (int iC = 0; iC < nC; iC++) {
    OnLatticeBoundaryCondition3D<T, Lattice>* blockBC =
      createInterpBoundaryCondition3D<T,Lattice,MixinDynamics>(
        sBC.get_sLattice().get_blockLattice(iC));
    sBC.get_blockBCs().push_back(blockBC);
  }
}

//////////////// Output functions //////////////////////////////////
template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::outputOn() {
  _output = true;
}

template<typename T, template<typename U> class Lattice>
void sOnLatticeBoundaryCondition3D<T, Lattice>::outputOff() {
  _output = false;
}

} // namespace olb

#endif
