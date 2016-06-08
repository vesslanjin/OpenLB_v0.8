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

/** \file A helper for initialising 2D boundaries -- header file.  */
#ifndef OFF_BOUNDARY_INSTANTIATOR_2D_H
#define OFF_BOUNDARY_INSTANTIATOR_2D_H

#include "offBoundaryCondition2D.h"
#include "blockGeometryStatistics2D.h"
#include "io/ostreamManager.h"
#include "util.h"

namespace olb {

/**
* This class gets the needed processors from BoundaryManager and adds them
* to the Processor Vector of the Lattice
*/

template<typename T, template<typename U> class Lattice, class BoundaryManager>
class OffBoundaryConditionInstantiator2D: public OffLatticeBoundaryCondition2D<T,
    Lattice> {
public:
  OffBoundaryConditionInstantiator2D(BlockStructure2D<T, Lattice>& block_);
  ~OffBoundaryConditionInstantiator2D();

  void addOnePointFixedBoundary(int x, int y, int dir, T dist);
  void addTwoPointFixedBoundary(int x, int y, int dir, T dist);
  void addThreePointFixedBoundary(int x, int y, int dir, T dist);

  void addOnePointVelocityBoundary(int x, int y, int dir, T dist, T uX, T uY);
  void addTwoPointVelocityBoundary(int x, int y, int dir, T dist, T uX, T uY);
  void addThreePointVelocityBoundary(int x, int y, int dir, T dist, T uX, T uY);

  void addFixedBoundary(BlockGeometryStatistics2D* blockGeoSta, int x, int y, int dir, T dist);
  void addVelocityBoundary(BlockGeometryStatistics2D* blockGeoSta, int x, int y, int dir, T dist, T uX, T uY);

  void outputOn();
  void outputOff();

  virtual BlockStructure2D<T, Lattice>& getBlock();
  virtual BlockStructure2D<T, Lattice> const& getBlock() const;
private:
  BlockStructure2D<T, Lattice>& block;
  std::vector<Momenta<T, Lattice>*> momentaVector;
  std::vector<Dynamics<T, Lattice>*> dynamicsVector;
  bool _output;
  mutable OstreamManager clout;
};

///////// class OffBoundaryConditionInstantiator2D ////////////////////////

template<typename T, template<typename U> class Lattice, class BoundaryManager>
OffBoundaryConditionInstantiator2D<T, Lattice, BoundaryManager>::OffBoundaryConditionInstantiator2D(
  BlockStructure2D<T, Lattice>& block_) :
  block(block_), _output(false), clout(std::cout,"BoundaryConditionInstantiator2D") {
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
OffBoundaryConditionInstantiator2D<T, Lattice, BoundaryManager>::~OffBoundaryConditionInstantiator2D() {
  for (unsigned iDynamics = 0; iDynamics < dynamicsVector.size(); ++iDynamics) {
    delete dynamicsVector[iDynamics];
  }
  for (unsigned iMomenta = 0; iMomenta < dynamicsVector.size(); ++iMomenta) {
    delete momentaVector[iMomenta];
  }
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator2D<T, Lattice, BoundaryManager>::addOnePointFixedBoundary(
    int x, int y, int dir, T dist) {
  PostProcessorGenerator2D<T, Lattice>* postProcessor =
    BoundaryManager::getOnePointFixedBoundaryProcessor
    (x, y, dir, dist);
  if (postProcessor)
    this->getBlock().addPostProcessor(*postProcessor);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator2D<T, Lattice, BoundaryManager>::addTwoPointFixedBoundary(
    int x, int y, int dir, T dist) {
  PostProcessorGenerator2D<T, Lattice>* postProcessor =
    BoundaryManager::getTwoPointFixedBoundaryProcessor
    (x, y, dir, dist);
  if (postProcessor)
    this->getBlock().addPostProcessor(*postProcessor);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator2D<T, Lattice, BoundaryManager>::addThreePointFixedBoundary(
    int x, int y, int dir, T dist) {
  PostProcessorGenerator2D<T, Lattice>* postProcessor =
    BoundaryManager::getThreePointFixedBoundaryProcessor
    (x, y, dir, dist);
  if (postProcessor)
    this->getBlock().addPostProcessor(*postProcessor);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator2D<T, Lattice, BoundaryManager>::addOnePointVelocityBoundary(
    int x, int y, int dir, T dist, T uX, T uY) {
  PostProcessorGenerator2D<T, Lattice>* postProcessor =
    BoundaryManager::getOnePointVelocityBoundaryProcessor
    (x, y, dir, dist, uX, uY);
  if (postProcessor)
    this->getBlock().addPostProcessor(*postProcessor);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator2D<T, Lattice, BoundaryManager>::addTwoPointVelocityBoundary(
    int x, int y, int dir, T dist, T uX, T uY) {
  PostProcessorGenerator2D<T, Lattice>* postProcessor =
    BoundaryManager::getTwoPointVelocityBoundaryProcessor
    (x, y, dir, dist, uX, uY);
  if (postProcessor)
    this->getBlock().addPostProcessor(*postProcessor);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator2D<T, Lattice, BoundaryManager>::addThreePointVelocityBoundary(
    int x, int y, int dir, T dist, T uX, T uY) {
  PostProcessorGenerator2D<T, Lattice>* postProcessor =
    BoundaryManager::getThreePointVelocityBoundaryProcessor
    (x, y, dir, dist, uX, uY);
  if (postProcessor)
    this->getBlock().addPostProcessor(*postProcessor);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator2D<T, Lattice, BoundaryManager>::addFixedBoundary(
    BlockGeometryStatistics2D* blockGeoSta, int x, int y, int dir, T dist) {
  const int* c = Lattice<T>::c[dir];
  if (blockGeoSta->getBlockGeometry()->getMaterial(x-c[0], y-c[1]) != 1)
    addOnePointFixedBoundary(x, y, dir, dist);
  else if (blockGeoSta->getBlockGeometry()->getMaterial(x-2*c[0], y-2*c[1]) != 1)
    addTwoPointFixedBoundary(x, y, dir, dist);
  else
    addThreePointFixedBoundary(x, y, dir, dist);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator2D<T, Lattice, BoundaryManager>::addVelocityBoundary(
    BlockGeometryStatistics2D* blockGeoSta, int x, int y, int dir, T dist, T uX, T uY) {
  const int* c = Lattice<T>::c[dir];
  if (blockGeoSta->getBlockGeometry()->getMaterial(x-c[0], y-c[1]) != 1)
    addOnePointVelocityBoundary(x, y, dir, dist, uX, uY);
  else if (blockGeoSta->getBlockGeometry()->getMaterial(x-2*c[0], y-2*c[1]) != 1)
    addTwoPointVelocityBoundary(x, y, dir, dist, uX, uY);
  else
    addThreePointVelocityBoundary(x, y, dir, dist, uX, uY);
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
BlockStructure2D<T, Lattice>& OffBoundaryConditionInstantiator2D<T, Lattice,
BoundaryManager>::getBlock() {
  return block;
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
BlockStructure2D<T, Lattice> const& OffBoundaryConditionInstantiator2D<T, Lattice,
BoundaryManager>::getBlock() const {
  return block;
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator2D<T, Lattice, BoundaryManager>::outputOn() {
  _output = true;
}

template<typename T, template<typename U> class Lattice, class BoundaryManager>
void OffBoundaryConditionInstantiator2D<T, Lattice, BoundaryManager>::outputOff() {
  _output = false;
}

}

#endif
