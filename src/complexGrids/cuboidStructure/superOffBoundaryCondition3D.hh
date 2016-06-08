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
 * A helper for initialising 3D boundaries -- generic implementation.
 */


#ifndef SUPER_OFF_BOUNDARY_CONDITION_3D_HH
#define SUPER_OFF_BOUNDARY_CONDITION_3D_HH

#include <vector>
#include "core/offBoundaryCondition3D.h"
#include "superOffBoundaryCondition3D.h"
#include "superLattice3D.h"
#include "core/util.h"
#include "functors/analyticalF.h"

namespace olb {

///////// class superOffBoundaryCondition3D ///////////////////////////////

template<typename T, template<typename U> class Lattice>
sOffLatticeBoundaryCondition3D<T,Lattice>::
sOffLatticeBoundaryCondition3D (SuperLattice3D<T,Lattice>& sLattice, T epsFraction )
  : clout(std::cout,"sOffLatticeBoundaryCondition3D"),
    _sLattice(sLattice),
    _epsFraction(epsFraction),
    _output(false)
{}

template<typename T, template<typename U> class Lattice>
sOffLatticeBoundaryCondition3D<T,Lattice>::
sOffLatticeBoundaryCondition3D(sOffLatticeBoundaryCondition3D<T,Lattice> const& rhs)
  : clout(std::cout,"sOffLatticeBoundaryCondition3D"),
    _sLattice(rhs._sLattice),
    _epsFraction(rhs._epsFraction),
    _output(false)
{
  _blockBCs = rhs._blockBCs;
  _overlap = rhs._overlap;
}

template<typename T, template<typename U> class Lattice>
sOffLatticeBoundaryCondition3D<T,Lattice> sOffLatticeBoundaryCondition3D<T,Lattice>::operator=(
  sOffLatticeBoundaryCondition3D<T,Lattice> rhs) {

  sOffLatticeBoundaryCondition3D<T,Lattice> tmp(rhs);
  return tmp;
}

template<typename T, template<typename U> class Lattice>
sOffLatticeBoundaryCondition3D<T,Lattice>::
~sOffLatticeBoundaryCondition3D() {

  for (unsigned iC=0; iC<_blockBCs.size(); iC++) {
    delete _blockBCs[iC];
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
addOnePointZeroVelocityBoundary(int x, int y, int z, int iPop, T dist){

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC=0; iC<nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addOnePointZeroVelocityBoundary(locX, locY, locZ, iPop, dist);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addOnePointZeroVelocityBoundary(" << x << ", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
addTwoPointZeroVelocityBoundary(int x, int y, int z, int iPop, T dist){

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC=0; iC<nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addTwoPointZeroVelocityBoundary(locX, locY, locZ, iPop, dist);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addTwoPointZeroVelocityBoundary(" << x << ", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
addOnePointVelocityBoundary(int x, int y, int z, int iPop, T dist){

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC=0; iC<nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addOnePointVelocityBoundary(locX, locY, locZ, iPop, dist);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addOnePointVelocityBoundary(" << x << ", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
addTwoPointVelocityBoundary(int x, int y, int z, int iPop, T dist){

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC=0; iC<nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addTwoPointVelocityBoundary(locX, locY, locZ, iPop, dist);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addTwoPointVelocityBoundary(" << x << ", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
addOffDynamics(int x, int y, int z, T location[Lattice<T>::d]) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC=0; iC<nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addOffDynamics(locX, locY, locZ, location);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addOffDynamics(" << x << ", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
addOffDynamics(int x, int y, int z, T location[Lattice<T>::d], T distances[Lattice<T>::q]) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC=0; iC<nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _blockBCs[iC]->addOffDynamics(locX, locY, locZ, location, distances);
    }
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ)) {
      addPoints2CommBC(locX, locX, locY, locY, locZ, locZ, iCglob);
    }
  }
  if (_output) {
    clout << "addOffDynamics(" << x << ", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
addOffDynamics(SuperGeometry3D& superGeometry, int material) {
  if (superGeometry.getStatistics().getNVoxel(material)!=0) {
    const int x0 = superGeometry.getStatistics().getMin(material)[0];
    const int y0 = superGeometry.getStatistics().getMin(material)[1];
    const int z0 = superGeometry.getStatistics().getMin(material)[2];
    const int x1 = superGeometry.getStatistics().getMax(material)[0];
    const int y1 = superGeometry.getStatistics().getMax(material)[1];
    const int z1 = superGeometry.getStatistics().getMax(material)[2];
    for (int ix = x0; ix <= x1; ix++)
    for (int iy = y0; iy <= y1; iy++)
    for (int iz = z0; iz <= z1; iz++)
    if (superGeometry.getMaterial(ix,iy,iz) == material ){
      T location[Lattice<T>::d];
      location[0] = superGeometry.physCoordX(ix);
      location[1] = superGeometry.physCoordY(iy);
      location[2] = superGeometry.physCoordZ(iz);
      addOffDynamics(ix, iy, iz, location);
    }
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
addZeroVelocityBoundary(SuperGeometry3D& superGeometry, int material, STLreader<T>& stlReader, std::list<int> materials) {

  clout.setMultiOutput(true);
  if (superGeometry.getStatistics().getNVoxel(material)!=0) {
    for (int lociC=0; lociC<_sLattice.get_load().get_locChunkSize(); lociC++){
      int globiC = _sLattice.get_load().glob(lociC);

      int nX = _sLattice.get_cGeometry().get_cuboid(globiC).get_nX();
      int nY = _sLattice.get_cGeometry().get_cuboid(globiC).get_nY();
      int nZ = _sLattice.get_cGeometry().get_cuboid(globiC).get_nZ();
      int globX = _sLattice.get_cGeometry().get_cuboid(globiC).get_globPosX();
      int globY = _sLattice.get_cGeometry().get_cuboid(globiC).get_globPosY();
      int globZ = _sLattice.get_cGeometry().get_cuboid(globiC).get_globPosZ();

      clout << "Cuboid globiC " << globiC
            << " starts to read distances for ZeroVelocity Boundary..." << std::endl;
      for (int ix = globX; ix < globX+nX; ix++)
      for (int iy = globY; iy < globY+nY; iy++)
      for (int iz = globZ; iz < globZ+nZ; iz++){
        std::list<int>::iterator mat;
        for (mat=materials.begin(); mat!=materials.end(); ++mat)
        if (superGeometry.getMaterial(ix,iy,iz) == *mat ) {
          for (int iPop = 1; iPop < Lattice<T>::q ; ++iPop) {
            const int* c = Lattice<T>::c[iPop];
            const int iXn = ix + c[0];
            const int iYn = iy + c[1];
            const int iZn = iz + c[2];
            if (superGeometry.getMaterial(iXn,iYn,iZn) == material ) {
              T dist = -1;
              T globPhysX=superGeometry.physCoordX(ix);
              T globPhysY=superGeometry.physCoordY(iy);
              T globPhysZ=superGeometry.physCoordZ(iz);
              T voxelSize=superGeometry.getSpacing();
              T cPhysNorm = voxelSize*sqrt(c[0]*c[0]+c[1]*c[1]+c[2]*c[2]);
              if (!stlReader.readDistanceCuboid(globPhysX,
                                      globPhysY,
                                      globPhysZ,
                                      voxelSize*c[0],
                                      voxelSize*c[1],
                                      voxelSize*c[2],
                                      lociC, dist)){
                T epsX = voxelSize*c[0]*_epsFraction;
                T epsY = voxelSize*c[1]*_epsFraction;
                T epsZ = voxelSize*c[2]*_epsFraction;
                if(!stlReader.readDistanceCuboid(globPhysX-epsX,
                                            globPhysY-epsY,
                                            globPhysZ-epsZ,
                                            voxelSize*c[0]+2*epsX,
                                            voxelSize*c[1]+2*epsY,
                                            voxelSize*c[2]+2*epsZ,
                                            lociC, dist)) {
                  clout << "ERROR: no boundary found at (" << ix << "," << iy << "," << iz <<") ~ ("
                        << globPhysX << "," << globPhysY << "," << globPhysZ <<"), "
                        << "in direction " << iPop << ": "
                        << std::endl;
                 superGeometry.printNode(ix,iy,iz);
                 // exit(-1);
                }
                T distNew = (dist - sqrt(epsX*epsX+epsY*epsY+epsZ*epsZ))/cPhysNorm;
                if (distNew < 0.5)
                  dist = 0;
                else
                  dist = 0.5*cPhysNorm;
                clout << "WARNING: distance at (" << ix << "," << iy << "," << iz <<") ~ ("
                      << globPhysX << "," << globPhysY << "," << globPhysZ <<"), "
                      << "in direction " << iPop << ": "
                      << distNew
                      << " rounded to "
                      << dist/cPhysNorm
                      << std::endl;
              }
              dist /= cPhysNorm;
              addZeroVelocityBoundary(superGeometry, ix, iy, iz, iPop, dist);
            }
          }
        }
      }
      clout << "Cuboid globiC " << globiC
            << " finished reading distances for ZeroVelocity Boundary." << std::endl;
    }
  }
  clout.setMultiOutput(false);
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
addZeroVelocityBoundary(SuperGeometry3D& superGeometry, int x, int y, int z, int iPop, T dist) {
  const int* c = Lattice<T>::c[iPop];
  if (superGeometry.getMaterial(x-c[0], y-c[1], z-c[2]) != 1)
    addOnePointZeroVelocityBoundary(x, y, z, iPop, dist);
  else
    addTwoPointZeroVelocityBoundary(x, y, z, iPop, dist);
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
addVelocityBoundary(SuperGeometry3D& superGeometry, int material, STLreader<T>& stlReader) {
  clout << "epsFraction=" << _epsFraction << std::endl;
  if (superGeometry.getStatistics().getNVoxel(material)!=0) {
    const int x0 = superGeometry.getStatistics().getMin(material)[0];
    const int y0 = superGeometry.getStatistics().getMin(material)[1];
    const int z0 = superGeometry.getStatistics().getMin(material)[2];
    const int x1 = superGeometry.getStatistics().getMax(material)[0];
    const int y1 = superGeometry.getStatistics().getMax(material)[1];
    const int z1 = superGeometry.getStatistics().getMax(material)[2];
    for (int ix = x0; ix <= x1; ix++)
    for (int iy = y0; iy <= y1; iy++)
    for (int iz = z0; iz <= z1; iz++)
    if (superGeometry.getMaterial(ix,iy,iz) == material )
      addVelocityBoundary(superGeometry, ix, iy, iz, stlReader);
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
addVelocityBoundary(SuperGeometry3D& superGeometry, int x, int y, int z, STLreader<T>& stlReader) {
  clout.setMultiOutput(true);

  typedef Lattice<T> L;
  T distances[L::q];
  for (int iPop = 1; iPop < L::q ; ++iPop)
    distances[iPop] = -1;

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC=0; iC<nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    //clout << "Cuboid globiC " << iCglob
    //      << " starts to read distances for Velocity Boundary..." << std::endl;
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      for (int iPop = 1; iPop < L::q ; ++iPop) {
        const int* c = L::c[iPop];
        const int iXn = x + c[0];
        const int iYn = y + c[1];
        const int iZn = z + c[2];
        if (superGeometry.getMaterial(iXn,iYn,iZn) == 1 ) {
          T dist = -1;
          T globPhysX=superGeometry.physCoordX(iXn);
          T globPhysY=superGeometry.physCoordY(iYn);
          T globPhysZ=superGeometry.physCoordZ(iZn);
          T voxelSize=superGeometry.getSpacing();
          T cPhysNorm = voxelSize*sqrt(c[0]*c[0]+c[1]*c[1]+c[2]*c[2]);
          if (!stlReader.readDistanceCuboid(globPhysX,
                                  globPhysY,
                                  globPhysZ,
                                  -voxelSize*c[0],
                                  -voxelSize*c[1],
                                  -voxelSize*c[2],
                                  iC, dist)){
            T epsX = voxelSize*c[0]*_epsFraction;
            T epsY = voxelSize*c[1]*_epsFraction;
            T epsZ = voxelSize*c[2]*_epsFraction;
            if(!stlReader.readDistanceCuboid(globPhysX+epsX,
                                        globPhysY+epsY,
                                        globPhysZ+epsZ,
                                        -voxelSize*c[0]-2*epsX,
                                        -voxelSize*c[1]-2*epsY,
                                        -voxelSize*c[2]-2*epsZ,
                                        iC, dist)) {
              clout << "ERROR: no boundary found at (" << iXn << "," << iYn << "," << iZn <<") ~ ("
                    << globPhysX << "," << globPhysY << "," << globPhysZ <<"), "
                    << "in direction " << util::opposite<L>(iPop)
                    << std::endl;
              superGeometry.printNode(iXn,iYn,iZn);
            //  exit(-1);
            }
            T distNew = (dist - sqrt(epsX*epsX+epsY*epsY+epsZ*epsZ))/cPhysNorm;
            if (distNew < 0.5)
              dist = 0;
            else {
              dist = 0.5 * cPhysNorm;
              //dist = cPhysNorm;
              clout << "WARNING: distance at (" << iXn << "," << iYn << "," << iZn <<") ~ ("
                    << globPhysX << "," << globPhysY << "," << globPhysZ <<"), "
                    << "in direction " << util::opposite<L>(iPop) << ": "
                    << distNew
                    << " rounded to "
                    << dist/cPhysNorm
                    << std::endl;
            }
          }
          distances[util::opposite<L>(iPop)] = dist/cPhysNorm;
        }
      }
    }
    //clout << "Cuboid globiC " << iCglob
    //      << " finished reading distances for Velocity Boundary." << std::endl;
  }
  addVelocityBoundary(superGeometry, x, y, z, distances);
  clout.setMultiOutput(false);
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
addVelocityBoundary(SuperGeometry3D& superGeometry, int x, int y, int z, T distances[Lattice<T>::q]) {
  typedef Lattice<T> L;
  T location[Lattice<T>::d];
  location[0] = superGeometry.physCoordX(x);
  location[1] = superGeometry.physCoordY(y);
  location[2] = superGeometry.physCoordZ(z);
  T distancesCopy[L::q];
  T spacing = superGeometry.getSpacing();
  for (int iPop = 1; iPop < L::q ; ++iPop) {
    distancesCopy[iPop] = spacing*(1.-distances[iPop]);
    if (distances[iPop] == -1)
      distancesCopy[iPop] = -1;
  }
  addOffDynamics(x, y, z, location, distancesCopy);

  for (int iPop = 1; iPop < L::q ; ++iPop){
    if (distances[iPop] != -1){
      const int* c = L::c[iPop];
      addVelocityBoundary(superGeometry, x-c[0], y-c[1], z-c[2], iPop, distances[iPop]);
    }
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
addVelocityBoundary(SuperGeometry3D& superGeometry, int x, int y, int z, int iPop, T dist) {
  const int* c = Lattice<T>::c[iPop];
  if (superGeometry.getMaterial(x-c[0], y-c[1], z-c[2]) != 1)
    addOnePointVelocityBoundary(x, y, z, iPop, dist);
  else
    addTwoPointVelocityBoundary(x, y, z, iPop, dist);
}


template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
setBoundaryIntersection ( int x, int y, int z, int iPop, T distance) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC=0; iC<nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _sLattice.get_blockLattice(iC).get(locX, locY, locZ).getDynamics()->setBoundaryIntersection(iPop, distance);
    }
  }
  if (_output) {
    clout << "setBoundaryIntersection(" << x << ", " << y << ", " << z << " )" << std::endl;
  }
}

template<typename T, template<typename U> class Lattice>
bool sOffLatticeBoundaryCondition3D<T,Lattice>::
getBoundaryIntersection (int x, int y, int z, int iPop, T point[Lattice<T>::d]) {

  int locX, locY, locZ;
  for (int iC=0; iC<_sLattice.get_load().size(); iC++) {
    if (_sLattice.get_cGeometry().get_cuboid(_sLattice.get_load().glob(iC)).checkPoint( x, y, z,
        locX, locY, locZ, _sLattice.get_overlap())) {
      return _sLattice.get_blockLattice(iC).get(locX, locY, locZ).getDynamics()->getBoundaryIntersection(iPop, point);
    }
  }
  return false;
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
defineU (int x, int y, int z, int iPop, const T u[Lattice<T>::d]) {

  int overlap = _sLattice.get_overlap();
  int nC = _sLattice.get_load().size();
  int locX, locY, locZ;

  for (int iC=0; iC<nC; iC++) {
    int iCglob = _sLattice.get_load().glob(iC);
    if (_sLattice.get_cGeometry().get_cuboid(iCglob).checkPoint(x, y, z,
        locX, locY, locZ, overlap)) {
      _sLattice.get_blockLattice(iC).get(locX, locY, locZ).getDynamics()->defineU(iPop, u);
    }
  }
  if (_output) {
    clout << "defineU(" << x << ", " << y << ", " << z << " )" << std::endl;
  }
}


template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
defineU(SuperGeometry3D& superGeometry, int material, AnalyticalF3D<T,T>& u, std::list<int> bulkMaterials ) {

  if (superGeometry.getStatistics().getNVoxel(material)!=0) {
    const int x0 = superGeometry.getStatistics().getMin(material)[0];
    const int y0 = superGeometry.getStatistics().getMin(material)[1];
    const int z0 = superGeometry.getStatistics().getMin(material)[2];
    const int x1 = superGeometry.getStatistics().getMax(material)[0];
    const int y1 = superGeometry.getStatistics().getMax(material)[1];
    const int z1 = superGeometry.getStatistics().getMax(material)[2];

    for (int iX = x0; iX <= x1; iX++) {
      for (int iY = y0; iY <= y1; iY++) { 
        for (int iZ = z0; iZ <= z1; iZ++) {

          if (superGeometry.getMaterial(iX, iY, iZ) == material) {
            for (int q = 1; q < Lattice< T >::q ; ++q) {
              // Get direction
              const int* c = Lattice<T>::c[q];
              int iXn = iX + c[0];
              int iYn = iY + c[1];
              int iZn = iZ + c[2];
              std::list<int>::iterator i;
              for (i=bulkMaterials.begin(); i!=bulkMaterials.end(); ++i) {
                if (superGeometry.getMaterial(iXn, iYn, iZn) == *i) {
                  T intersection[] = { T(), T() ,T() }; // coord. of intersection
                  int opp = util::opposite<Lattice<T> >(q);
                  if (this->getBoundaryIntersection(iX, iY, iZ, opp, intersection) ) {  
                    std::vector<double> intersection2; 
                    intersection2.push_back(intersection[0]);
                    intersection2.push_back(intersection[1]);
                    intersection2.push_back(intersection[2]); 
                    T vel[] = {u(intersection2)[0], u(intersection2)[1], u(intersection2)[2]};
                    this->defineU(iX, iY, iZ, opp, vel);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}


template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::
addPoints2CommBC(int x0, int x1, int y0, int y1, int z0, int z1, int iCglob) {

  if (_overlap!=0) {
    int nC  = _sLattice.get_cGeometry().get_nC();
    T globX = _sLattice.get_cGeometry().get_cuboid(iCglob).get_globPosX();
    T globY = _sLattice.get_cGeometry().get_cuboid(iCglob).get_globPosY();
    T globZ = _sLattice.get_cGeometry().get_cuboid(iCglob).get_globPosZ();
    T delta = _sLattice.get_cGeometry().get_cuboid(iCglob).get_delta();

    for (int iOverl=1; iOverl<=_overlap; iOverl++) {
      for (int iX=x0-iOverl; iX<=x1+iOverl; iX++) {
        for (int iY=y0-iOverl; iY<=y1+iOverl; iY++) {
          for (int iZ=z0-iOverl; iZ<=z1+iOverl; iZ++) {
            if (iX==x0-iOverl || iX==x1+iOverl ||
                iY==y0-iOverl || iY==y1+iOverl ||
                iZ==z0-iOverl || iZ==z1+iOverl) {
              T nextX = globX +iX*delta;
              T nextY = globY +iY*delta;
              T nextZ = globZ +iZ*delta;
              int found_iC = _sLattice.get_cGeometry().get_iC(nextX, nextY, nextZ);
              if (found_iC!=nC && found_iC!=iCglob) {
                _sLattice.get_commBC().add_cell(iCglob, nextX, nextY, nextZ);
              }
            }
          }
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::outputOn() {
  _output = true;
}

template<typename T, template<typename U> class Lattice>
void sOffLatticeBoundaryCondition3D<T,Lattice>::outputOff() {
  _output = false;
}

////////////////// Factory functions //////////////////////////////////

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
void createBouzidiBoundaryCondition3D(sOffLatticeBoundaryCondition3D<T,Lattice>& sBC) {

  int nC = sBC.get_sLattice().get_load().size();
  sBC.set_overlap(1);
  for (int iC=0; iC<nC; iC++) {
    OffLatticeBoundaryCondition3D<T,Lattice>* blockBC
    = createBouzidiBoundaryCondition3D<T,Lattice,MixinDynamics>(sBC.get_sLattice().get_blockLattice(iC));
    sBC.get_blockBCs().push_back(blockBC);
  }
}

}  // namespace olb

#endif

