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

/** \file A helper for initialising 3D boundaries -- header file.  */
#ifndef OFF_BOUNDARY_INSTANTIATOR_3D_H
#define OFF_BOUNDARY_INSTANTIATOR_3D_H

#include "offBoundaryCondition3D.h"
#include "blockGeometryStatistics3D.h"
#include "io/ostreamManager.h"
#include "util.h"
#include "../io/stlReader.h"

namespace olb {

/**
* This class gets the needed processors from BoundaryManager and adds them
* to the Processor Vector of the Lattice
*/

template<typename T, template<typename U> class Lattice, class BoundaryManager>
class OffBoundaryConditionInstantiator3D: public OffLatticeBoundaryCondition3D<T,
    Lattice> {
public:
  OffBoundaryConditionInstantiator3D(BlockStructure3D<T, Lattice>& block_);
  ~OffBoundaryConditionInstantiator3D();

  void addOnePointZeroVelocityBoundary(int x, int y, int z, int iPop, T dist);
  void addTwoPointZeroVelocityBoundary(int x, int y, int z, int iPop, T dist);

  void addOnePointVelocityBoundary(int x, int y, int z, int iPop, T dist);
  void addTwoPointVelocityBoundary(int x, int y, int z, int iPop, T dist);

  virtual void addOffDynamics(int x, int y, int z, T location[Lattice<T>::d]);
  virtual void addOffDynamics(int x, int y, int z, T location[Lattice<T>::d], T distances[Lattice<T>::q]);
  virtual void addOffDynamics(BlockGeometryStatistics3D* blockGeoSta, int material);

  void addZeroVelocityBoundary(BlockGeometryStatistics3D* blockGeoSta, int x, int y, int z, int iPop, T dist);
  void addVelocityBoundary(BlockGeometryStatistics3D* blockGeoSta, int x, int y, int z, int iPop, T dist);

  void addZeroVelocityBoundary(BlockGeometryStatistics3D* blockGeoSta, STLreader<T>* stlreader, int material);

  void outputOn();
  void outputOff();

  virtual BlockStructure3D<T, Lattice>& getBlock();
  virtual BlockStructure3D<T, Lattice> const& getBlock() const;
private:
  BlockStructure3D<T, Lattice>& block;
  //std::vector<Momenta<T, Lattice>*> momentaVector;
  std::vector<Dynamics<T, Lattice>*> dynamicsVector;
  bool _output;
  mutable OstreamManager clout;
};

///////// class OffBoundaryConditionInstantiator3D ////////////////////////

template<typename T, template<typename U> class Lattice, class BoundaryManager>
OffBoundaryConditionInstantiator3D<T, Lattice, BoundaryManager>::OffBoundaryConditionInstantiator3D(
  BlockStructure3D<T, Lattice>& block_) :
  block(block_), _output(false), clout(std::cout,"BoundaryConditionInstantiator3D") {
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
OffBoundaryConditionInstantiator3D<T, Lattice, BoundaryManager>::~OffBoundaryConditionInstantiator3D() {
  for (unsigned iDynamics = 0; iDynamics < dynamicsVector.size(); ++iDynamics) {
    delete dynamicsVector[iDynamics];
  }
  /*
  for (unsigned iMomenta = 0; iMomenta < dynamicsVector.size(); ++iMomenta) {
    delete momentaVector[iMomenta];
  }*/
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator3D<T, Lattice, BoundaryManager>::addOnePointZeroVelocityBoundary(
    int x, int y, int z, int iPop, T dist) {
  PostProcessorGenerator3D<T, Lattice>* postProcessor =
    BoundaryManager::getOnePointZeroVelocityBoundaryProcessor
    (x, y, z, iPop, dist);
  if (postProcessor)
    this->getBlock().addPostProcessor(*postProcessor);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator3D<T, Lattice, BoundaryManager>::addTwoPointZeroVelocityBoundary(
    int x, int y, int z, int iPop, T dist) {
  PostProcessorGenerator3D<T, Lattice>* postProcessor =
    BoundaryManager::getTwoPointZeroVelocityBoundaryProcessor
    (x, y, z, iPop, dist);
  if (postProcessor)
    this->getBlock().addPostProcessor(*postProcessor);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator3D<T, Lattice, BoundaryManager>::addOnePointVelocityBoundary(
    int x, int y, int z, int iPop, T dist) {
  PostProcessorGenerator3D<T, Lattice>* postProcessor =
    BoundaryManager::getOnePointVelocityBoundaryProcessor
    (x, y, z, iPop, dist);
  if (postProcessor)
    this->getBlock().addPostProcessor(*postProcessor);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator3D<T, Lattice, BoundaryManager>::addTwoPointVelocityBoundary(
    int x, int y, int z, int iPop, T dist) {
  PostProcessorGenerator3D<T, Lattice>* postProcessor =
    BoundaryManager::getTwoPointVelocityBoundaryProcessor
    (x, y, z, iPop, dist);
  if (postProcessor)
    this->getBlock().addPostProcessor(*postProcessor);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator3D<T, Lattice, BoundaryManager>::addOffDynamics(
    int x, int y, int z, T location[Lattice<T>::d]) {
  Dynamics<T,Lattice>* dynamics
  = BoundaryManager::getOffDynamics(location);
  this->getBlock().defineDynamics(x,x,y,y,z,z, dynamics);
  dynamicsVector.push_back(dynamics);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator3D<T, Lattice, BoundaryManager>::addOffDynamics(
    int x, int y, int z, T location[Lattice<T>::d], T distances[Lattice<T>::q]) {
  Dynamics<T,Lattice>* dynamics
  = BoundaryManager::getOffDynamics(location, distances);
  this->getBlock().defineDynamics(x,x,y,y,z,z, dynamics);
  dynamicsVector.push_back(dynamics);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator3D<T, Lattice, BoundaryManager>::addOffDynamics(
  BlockGeometryStatistics3D* blockGeoSta, int material) {
  if (blockGeoSta->getNVoxel(material)!=0) {
    const int x0 = blockGeoSta->getMin(material)[0];
    const int y0 = blockGeoSta->getMin(material)[1];
    const int z0 = blockGeoSta->getMin(material)[2];
    const int x1 = blockGeoSta->getMax(material)[0];
    const int y1 = blockGeoSta->getMax(material)[1];
    const int z1 = blockGeoSta->getMax(material)[2];
    for (int ix = x0; ix <= x1; ix++)
    for (int iy = y0; iy <= y1; iy++)
    for (int iz = z0; iz <= z1; iz++)
    if (blockGeoSta->getBlockGeometry()->getMaterial(ix,iy,iz) == material ){
      T location[Lattice<T>::d];
      location[0] = blockGeoSta->getBlockGeometry()->physCoordX(ix);
      location[1] = blockGeoSta->getBlockGeometry()->physCoordY(iy);
      location[2] = blockGeoSta->getBlockGeometry()->physCoordZ(iz);
      addOffDynamics(ix, iy, iz, location);
    }
  }
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator3D<T, Lattice, BoundaryManager>::addZeroVelocityBoundary(
    BlockGeometryStatistics3D* blockGeoSta, int x, int y, int z, int iPop, T dist) {
  const int* c = Lattice<T>::c[iPop];
  if (blockGeoSta->getBlockGeometry()->getMaterial(x-c[0], y-c[1], z-c[2]) != 1)
    addOnePointZeroVelocityBoundary(x, y, z, iPop, dist);
  else
    addTwoPointZeroVelocityBoundary(x, y, z, iPop, dist);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator3D<T, Lattice, BoundaryManager>::addZeroVelocityBoundary(
    BlockGeometryStatistics3D* blockGeoSta, STLreader<T>* stlreader, int material) {
  if (blockGeoSta->getNVoxel(material)!=0) {
    const int x0 = blockGeoSta->getMin(material)[0];
    const int y0 = blockGeoSta->getMin(material)[1];
    const int z0 = blockGeoSta->getMin(material)[2];
    const int x1 = blockGeoSta->getMax(material)[0];
    const int y1 = blockGeoSta->getMax(material)[1];
    const int z1 = blockGeoSta->getMax(material)[2];
    for (int ix = x0; ix <= x1; ix++) {
      for (int iy = y0; iy <= y1; iy++) {
        for (int iz = z0; iz <= z1; iz++) {
          if (blockGeoSta->getBlockGeometry()->getMaterial(ix,iy,iz) == material ) {
            for (int q = 1; q < Lattice<T>::q ; ++q) {
              const int* c = Lattice<T>::c[q];
              const int iXn = ix + c[0];
              const int iYn = iy + c[1];
              const int iZn = iz + c[2];
              if (blockGeoSta->getBlockGeometry()->getMaterial(iXn,iYn,iZn) == 1 ) {
                T globPhysX=blockGeoSta->getBlockGeometry()->physCoordX(iXn);
                T globPhysY=blockGeoSta->getBlockGeometry()->physCoordY(iYn);
                T globPhysZ=blockGeoSta->getBlockGeometry()->physCoordZ(iZn);
                T voxelSize=blockGeoSta->getBlockGeometry()->getSpacing();
                T dist = -1;
                stlreader->readDistance(globPhysX, globPhysY, globPhysZ, -voxelSize*c[0], -voxelSize*c[1], -voxelSize*c[2], dist);
                dist /= voxelSize*sqrt(c[0]*c[0]+c[1]*c[1]+c[2]*c[2]);
                addZeroVelocityBoundary(blockGeoSta, iXn, iYn, iZn, util::opposite<Lattice<T> >(q), dist);
              }
            }
          }
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator3D<T, Lattice, BoundaryManager>::addVelocityBoundary(
    BlockGeometryStatistics3D* blockGeoSta, int x, int y, int z, int iPop, T dist) {
  const int* c = Lattice<T>::c[iPop];
  if (blockGeoSta->getBlockGeometry()->getMaterial(x-c[0], y-c[1], z-c[2]) != 1)
    addOnePointVelocityBoundary(x, y, z, iPop, dist);
  else
    addTwoPointVelocityBoundary(x, y, z, iPop, dist);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
BlockStructure3D<T, Lattice>& OffBoundaryConditionInstantiator3D<T, Lattice,
BoundaryManager>::getBlock() {
  return block;
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
BlockStructure3D<T, Lattice> const& OffBoundaryConditionInstantiator3D<T, Lattice,
BoundaryManager>::getBlock() const {
  return block;
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator3D<T, Lattice, BoundaryManager>::outputOn() {
  _output = true;
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator3D<T, Lattice, BoundaryManager>::outputOff() {
  _output = false;
}

}

#endif
