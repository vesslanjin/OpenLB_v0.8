/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2010 Mathias J. Krause, Thomas Henn, Jonas Kratzke
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
 * Input in STL format -- implementation.
 */

#ifndef STL_READER_HH
#define STL_READER_HH

#include "stlReader.h"
#include "complexGrids/mpiManager/mpiManager.h"
#include "external/cvmlcpp/volume/VolumeHelpers.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <queue>

namespace olb {


/// Use BFS to find the height of a DTree
template <typename T, std::size_t D>
int treeDepth(cvmlcpp::DTree<T,D> tree) {
  typedef cvmlcpp::DTreeProxy<T, D> DNode;
  unsigned currentDepth = 0;
  std::queue< DNode > q;
  q.push(tree.root());

  while (!q.empty()) {
    DNode node = q.front();
    q.pop();
    if (node.depth() > currentDepth) currentDepth = node.depth();
    // if the node is a branch
    if (!node.isLeaf()) {
      // we examine all of its children
      for (int i = 0; i < (1 << D); ++i) {
        q.push(node[i]);
      }
    }
  }
  return currentDepth;
}

/// using DFS to find a given node and getting the index collection that created it
template <typename T, std::size_t D>
void findPath (
  cvmlcpp::DTree<T,D> tree, cvmlcpp::DTreeProxy<T, D> &wantedNode, std::vector<int>& indexes ) {
  typedef cvmlcpp::DTreeProxy<T, D> DNode;
  DNode node = wantedNode;

  while (node.depth() > 0) {
    assert( node.depth() < indexes.size() );
    indexes[node.depth()] = node.index();
    node = node.parent();
  }
}


template<typename T>
STLreader<T>::STLreader(const std::string& fName){
  _innerMaterialNo = 1;
  _outerMaterialNo = 0;
  cvmlcpp::readSTL(_geometry, fName);
}

template<typename T>
STLreader<T>::~STLreader() {
}

template<typename T>
void STLreader<T>::read(BlockGeometry3D &matrix, unsigned direction,
                        unsigned voxelNumber, unsigned pad,
                        double fraction, unsigned samples,
                        unsigned offsetXN, unsigned offsetXP,
                        unsigned offsetYN, unsigned offsetYP,
                        unsigned offsetZN, unsigned offsetZP) const {
  assert(direction >= 0);
  assert(direction <= 2);
  // Find dimensions
  double geometrySize = 0.;
  geometrySize = std::max(geometrySize, double(_geometry.max(direction))
                          - double(_geometry.min(direction)));
  assert( geometrySize > 0.0 );
  assert( voxelNumber != 0.0 );
  double voxelSize = geometrySize / (double) voxelNumber;
  read(matrix, voxelSize, pad,
        fraction, samples,
        offsetXN, offsetXP,
        offsetYN, offsetYP,
        offsetZN, offsetZP);
}

template<typename T>
void STLreader<T>::read(SuperGeometry3D &matrix, unsigned direction,
                        unsigned voxelNumber, unsigned pad,
                        double fraction, unsigned samples,
                        unsigned offsetXN, unsigned offsetXP,
                        unsigned offsetYN, unsigned offsetYP,
                        unsigned offsetZN, unsigned offsetZP) const {
  assert(direction >= 0);
  assert(direction <= 2);
  // Find dimensions
  double geometrySize = 0.;
  geometrySize = std::max(geometrySize, double(_geometry.max(direction))
                          - double(_geometry.min(direction)));
  assert( geometrySize > 0.0 );
  assert( voxelNumber != 0.0 );
  double voxelSize = geometrySize / (double) voxelNumber;
  read(matrix, voxelSize, pad,
        fraction, samples,
        offsetXN, offsetXP,
        offsetYN, offsetYP,
        offsetZN, offsetZP);
}

template<typename T>
void STLreader<T>::read(BlockGeometry3D &matrix, double voxelSize, unsigned int pad,
                         double fraction, unsigned int samples,
                         unsigned offsetXN, unsigned offsetXP,
                         unsigned offsetYN, unsigned offsetYP,
                         unsigned offsetZN, unsigned offsetZP) const {
  if (fraction) {

    cvmlcpp::Matrix<double, 3u> voxels;
    cvmlcpp::fractionVoxelize(_geometry, voxels, voxelSize, samples, 1);
    matrix.reInit(_geometry.min(0) - (1 - 0.5 + offsetXN) * voxelSize,
                  _geometry.min(1) - (1 - 0.5 + offsetYN) * voxelSize,
                  _geometry.min(2) - (1 - 0.5 + offsetZN) * voxelSize,
                  voxelSize,
                  voxels.extents()[X] + offsetXN + offsetXP,
                  voxels.extents()[Y] + offsetYN + offsetYP,
                  voxels.extents()[Z] + offsetZN + offsetZP, pad);

    for (unsigned z = 0; z < voxels.extents()[Z]; ++z) {
      for (unsigned y = 0; y < voxels.extents()[Y]; ++y) {
        for (unsigned x = 0; x < voxels.extents()[X]; ++x) {
          if (voxels[x][y][z] > fraction)
            matrix.setMaterial(x + offsetXN, y + offsetYN, z + offsetZN, _innerMaterialNo);
          else
            matrix.setMaterial(x + offsetXN, y + offsetYN, z + offsetZN, _outerMaterialNo);
        }
      }
    }
  } else {
    cvmlcpp::Matrix<unsigned short, 3u> voxels;
    cvmlcpp::voxelize(_geometry, voxels, voxelSize, 1);
    matrix.reInit(_geometry.min(0) - (1 - 0.5 + offsetXN) * voxelSize,
                  _geometry.min(1) - (1 - 0.5 + offsetYN) * voxelSize,
                  _geometry.min(2) - (1 - 0.5 + offsetZN) * voxelSize,
                  voxelSize,
                  voxels.extents()[X] + offsetXN + offsetXP,
                  voxels.extents()[Y] + offsetYN + offsetYP,
                  voxels.extents()[Z] + offsetZN + offsetZP, pad);

    for (unsigned z = 0; z < voxels.extents()[Z]; ++z) {
      for (unsigned y = 0; y < voxels.extents()[Y]; ++y) {
        for (unsigned x = 0; x < voxels.extents()[X]; ++x) {
          if (voxels[x][y][z] == 1)
            matrix.setMaterial(x + offsetXN, y + offsetYN, z + offsetZN, _innerMaterialNo);
          else
            matrix.setMaterial(x + offsetXN, y + offsetYN, z + offsetZN, _outerMaterialNo);
        }
      }
    }
  }
}

template<typename T>
void STLreader<T>::read(SuperGeometry3D &matrix, double voxelSize, unsigned int pad,
                         double fraction, unsigned int samples,
                         unsigned offsetXN, unsigned offsetXP,
                         unsigned offsetYN, unsigned offsetYP,
                         unsigned offsetZN, unsigned offsetZP) const {
  if (fraction) {

    cvmlcpp::Matrix<double, 3u> voxels;
    cvmlcpp::fractionVoxelize(_geometry, voxels, voxelSize, samples, 1);
    matrix.reInit(_geometry.min(0) - (1 - 0.5 + offsetXN) * voxelSize,
                  _geometry.min(1) - (1 - 0.5 + offsetYN) * voxelSize,
                  _geometry.min(2) - (1 - 0.5 + offsetZN) * voxelSize,
                  voxelSize,
                  voxels.extents()[X] + offsetXN + offsetXP,
                  voxels.extents()[Y] + offsetYN + offsetYP,
                  voxels.extents()[Z] + offsetZN + offsetZP, pad);

    for (unsigned z = 0; z < voxels.extents()[Z]; ++z) {
      for (unsigned y = 0; y < voxels.extents()[Y]; ++y) {
        for (unsigned x = 0; x < voxels.extents()[X]; ++x) {
          if (voxels[x][y][z] > fraction)
            matrix.setMaterial(x + offsetXN, y + offsetYN, z + offsetZN, _innerMaterialNo);
          else
            matrix.setMaterial(x + offsetXN, y + offsetYN, z + offsetZN, _outerMaterialNo);
        }
      }
    }
  } else {
    cvmlcpp::Matrix<unsigned short, 3u> voxels;
    cvmlcpp::voxelize(_geometry, voxels, voxelSize, 1);
    matrix.reInit(_geometry.min(0) - (1 - 0.5 + offsetXN) * voxelSize,
                  _geometry.min(1) - (1 - 0.5 + offsetYN) * voxelSize,
                  _geometry.min(2) - (1 - 0.5 + offsetZN) * voxelSize,
                  voxelSize,
                  voxels.extents()[X] + offsetXN + offsetXP,
                  voxels.extents()[Y] + offsetYN + offsetYP,
                  voxels.extents()[Z] + offsetZN + offsetZP, pad);

    for (unsigned z = 0; z < voxels.extents()[Z]; ++z) {
      for (unsigned y = 0; y < voxels.extents()[Y]; ++y) {
        for (unsigned x = 0; x < voxels.extents()[X]; ++x) {
          if (voxels[x][y][z] == 1)
            matrix.setMaterial(x + offsetXN, y + offsetYN, z + offsetZN, _innerMaterialNo);
          else
            matrix.setMaterial(x + offsetXN, y + offsetYN, z + offsetZN, _outerMaterialNo);
        }
      }
    }
  }
}

template<typename T>
void STLreader<T>::read(CuboidGeometry3D<T> &cGeometry, BlockGeometry3D &matrix,
                        unsigned voxelNumber, unsigned minCuboidSize, unsigned pad) {
  // Find largest direction
  double geometrySize = 0.;
  for(int d = 0; d < 3; ++d) {
    geometrySize = std::max (
                     geometrySize,
                     double(_geometry.max(d)) - double(_geometry.min(d))
                   );
  }

  assert( geometrySize > 0.0 );
  assert( voxelNumber != 0.0 );  void initCuboidGeometries(CuboidGeometry3D<T> &cGeometry, loadBalancer &load);

  double voxelSize = geometrySize / (double) voxelNumber;
  _nX = (double(_geometry.max(0)) - double(_geometry.min(0)))/voxelSize + 3;
  _nY = (double(_geometry.max(1)) - double(_geometry.min(1)))/voxelSize + 3;
  _nZ = (double(_geometry.max(2)) - double(_geometry.min(2)))/voxelSize + 3;
  readOctree(cGeometry, matrix, voxelSize, minCuboidSize, pad);
}

template<typename T>
void STLreader<T>::read(CuboidGeometry3D<T> &cGeometry, SuperGeometry3D &matrix,
                        unsigned voxelNumber, unsigned minCuboidSize, unsigned pad) {
  // Find largest direction
  double geometrySize = 0.;
  for(int d = 0; d < 3; ++d) {
    geometrySize = std::max (
                     geometrySize,
                     double(_geometry.max(d)) - double(_geometry.min(d))
                   );
  }

  assert( geometrySize > 0.0 );
  assert( voxelNumber != 0.0 );  void initCuboidGeometries(CuboidGeometry3D<T> &cGeometry, loadBalancer &load);

  double voxelSize = geometrySize / (double) voxelNumber;
  _nX = (double(_geometry.max(0)) - double(_geometry.min(0)))/voxelSize + 3;
  _nY = (double(_geometry.max(1)) - double(_geometry.min(1)))/voxelSize + 3;
  _nZ = (double(_geometry.max(2)) - double(_geometry.min(2)))/voxelSize + 3;
  readOctree(cGeometry, matrix, voxelSize, minCuboidSize, pad);
}


template <typename T>
Cuboid3D<T> STLreader<T>::cuboidFromNode(DNode3D &node, int height, cvmlcpp::DTree<int,3u> &tree) const {
  std::vector<int> indexes(height+1);
  for (int i = 0; i < height+1; ++i) indexes[i] = 0;
  findPath(tree,node,indexes);

  int maxSize = (1  << height);
  int x0, y0, z0, x1, y1, z1;
  x0 = y0 = x1 = y1 = z0 = z1 = 1;
  int blockSize = 1; // we start from the smaller block size
  for (int i = height; i > 0; --i) {
    x0 +=  blockSize*(indexes[i] & 1); // first bit
    y0 += blockSize*((indexes[i] & 2) >> 1); // second bit
    z0 += blockSize*((indexes[i] & 4) >> 2); // third bit
    blockSize *= 2;
  }
  int extents = maxSize/(1<<node.depth());
  x1 = std::min(extents,_nX-x0-1);
  y1 = std::min(extents,_nY-y0-1);
  z1 = std::min(extents,_nZ-z0-1);


  // Extent to have a padding of one around the border
  if(x0 == 1) {
    x0 = 0;
    x1++;
  }
  if(y0 == 1) {
    y0 = 0;
    y1++;
  }
  if(z0 == 1) {
    z0 = 0;
    z1++;
  }
  if(x1 == _nX-x0-1) {
    x1++;
  }
  if(y1 == _nY-y0-1) {
    y1++;
  }
  if(z1 == _nZ-z0-1) {
    z1++;
  }
  Cuboid3D<T> cuboid(x0, y0, z0, 1, x1, y1, z1);
  return cuboid;
}


template <typename T>
void STLreader<T>::setMaterialForNode(BlockGeometry3D &matrix, DNode3D &node, int height, cvmlcpp::DTree<int,3u> &tree) const {
  std::vector<int> indexes(height+1);
  for (int i = 0; i < height+1; ++i) indexes[i] = 0;
  findPath(tree,node,indexes);

  int maxSize = (1  << height);
  int x0, y0, z0, x1, y1, z1;
  x0 = y0 = x1 = y1 = z0 = z1 = 1;
  int blockSize = 1; // we start from the smaller block size
  for (int i = height; i > 0; --i) {
    x0 +=  blockSize*(indexes[i] & 1); // first bit
    y0 += blockSize*((indexes[i] & 2) >> 1); // second bit
    z0 += blockSize*((indexes[i] & 4) >> 2); // third bit
    blockSize *= 2;
  }
  int extents = maxSize/(1<<node.depth());
  for(int x = x0; x < std::min(x0+extents, _nX); x++) {
    for(int y = y0; y < std::min(y0+extents, _nY); y++) {
      for(int z = z0; z < std::min(z0+extents, _nZ); z++) {
        if(node()) {
          matrix.setMaterial(x, y, z, _innerMaterialNo);
        } else {
          matrix.setMaterial(x, y, z, _outerMaterialNo);
        }
      }
    }
  }
}

template <typename T>
void STLreader<T>::setMaterialForNode(SuperGeometry3D &matrix, DNode3D &node, int height, cvmlcpp::DTree<int,3u> &tree) const {
  std::vector<int> indexes(height+1);
  for (int i = 0; i < height+1; ++i) indexes[i] = 0;
  findPath(tree,node,indexes);

  int maxSize = (1  << height);
  int x0, y0, z0, x1, y1, z1;
  x0 = y0 = x1 = y1 = z0 = z1 = 1;
  int blockSize = 1; // we start from the smaller block size
  for (int i = height; i > 0; --i) {
    x0 +=  blockSize*(indexes[i] & 1); // first bit
    y0 += blockSize*((indexes[i] & 2) >> 1); // second bit
    z0 += blockSize*((indexes[i] & 4) >> 2); // third bit
    blockSize *= 2;
  }
  int extents = maxSize/(1<<node.depth());
  for(int x = x0; x < std::min(x0+extents, _nX); x++) {
    for(int y = y0; y < std::min(y0+extents, _nY); y++) {
      for(int z = z0; z < std::min(z0+extents, _nZ); z++) {
        if(node()) {
          matrix.setMaterial(x, y, z, _innerMaterialNo);
        } else {
          matrix.setMaterial(x, y, z, _outerMaterialNo);
        }
      }
    }
  }
}


template<typename T>
void STLreader<T>::readOctree(CuboidGeometry3D<T> &cGeometry, BlockGeometry3D &matrix, double voxelSize, unsigned minCuboidSize, unsigned pad) const {
  unsigned limitHeight = 15;

  unsigned currentDepth = 0;
  cvmlcpp::DTree<int,3u> tree(0);

  cvmlcpp::voxelize(_geometry, tree, voxelSize);

  std::queue< DNode3D > q;
  q.push(tree.root());

  // retrieve the height of the tree for further computations
  unsigned height = treeDepth<int,3>(tree);
  unsigned limitCuboid = 1;
  while((1u << (height - limitCuboid)) > minCuboidSize) {
    limitCuboid++;
  }

  matrix.reInit(_geometry.min(0) - 0.5 * voxelSize,
                _geometry.min(1) - 0.5 * voxelSize,
                _geometry.min(2) - 0.5 * voxelSize,
                voxelSize,
                _nX, _nY, _nZ,
                pad);
  cGeometry.set_motherC(_geometry.min(0) - 0.5 * voxelSize,
                        _geometry.min(1) - 0.5 * voxelSize,
                        _geometry.min(2) - 0.5 * voxelSize,
                        voxelSize,_nX, _nY, _nZ);

  // set all borders to _outerMaterialNo
  for(int x = 0; x < _nX; x++) {
    for(int y = 0; y < _nY; y++) {
      matrix.setMaterial(x,y,0, _outerMaterialNo);
      matrix.setMaterial(x,y,_nZ-1+2*pad, _outerMaterialNo);
    }
    for(int z = 0; z < _nZ; z++) {
      matrix.setMaterial(x,0,z, _outerMaterialNo);
      matrix.setMaterial(x,_nY-1+2*pad,z, _outerMaterialNo);
    }
  }
  for(int y = 0; y < _nY; y++) {
    for(int z = 0; z < _nZ; z++) {
      matrix.setMaterial(0,y,z, _outerMaterialNo);
      matrix.setMaterial(_nX-1+2*pad,y,z, _outerMaterialNo);
    }
  }

  Cuboid3D<T> cuboid;

  while (!q.empty()) {
    DNode3D node = q.front();
    q.pop();

    if (currentDepth < node.depth()) {
      currentDepth = node.depth();
    }

    // if the node is a branch
    if (!node.isLeaf()) {
      // we examine all of its children if we have not reached a certain depth
      if (node.depth() < limitHeight) {
        if (node.depth() == limitCuboid) {
          cuboid = cuboidFromNode(node, height, tree);
          cGeometry.add(cuboid);
        }
        for (int i = 0; i < (1 << 3); ++i) {
          q.push(node[i]);
        }
      }
      else {
        if (node.depth() == limitCuboid) {
          cuboid = cuboidFromNode(node, height, tree);
          cGeometry.add(cuboid);
          assert(1==0);
          // reconstruction of the indexes up to this node
          setMaterialForNode(matrix, node, height, tree);
        }
        else {
          assert(1==0);
          // reconstruction of the indexes up to this node
          setMaterialForNode(matrix, node, height, tree);
        }
      }
    }
    // if we have a leaf node that CONTAINS only liquid before the intended depth
    else {
      setMaterialForNode(matrix, node, height, tree);
      if (node() == 1) {
        if (node.depth() <= limitCuboid) {
          // otherwise, the cuboid will already have been added
          cuboid = cuboidFromNode(node, height, tree);
          cGeometry.add(cuboid);
        }

      }
    }
  }
}

template<typename T>
void STLreader<T>::readOctree(CuboidGeometry3D<T> &cGeometry, SuperGeometry3D &matrix, double voxelSize, unsigned minCuboidSize, unsigned pad) const {
  unsigned limitHeight = 15;

  unsigned currentDepth = 0;
  cvmlcpp::DTree<int,3u> tree(0);

  cvmlcpp::voxelize(_geometry, tree, voxelSize);

  std::queue< DNode3D > q;
  q.push(tree.root());

  // retrieve the height of the tree for further computations
  unsigned height = treeDepth<int,3>(tree);
  unsigned limitCuboid = 1;
  while((1u << (height - limitCuboid)) > minCuboidSize) {
    limitCuboid++;
  }

  matrix.reInit(_geometry.min(0) - 0.5 * voxelSize,
                _geometry.min(1) - 0.5 * voxelSize,
                _geometry.min(2) - 0.5 * voxelSize,
                voxelSize,
                _nX, _nY, _nZ,
                pad);
  cGeometry.set_motherC(_geometry.min(0) - 0.5 * voxelSize,
                        _geometry.min(1) - 0.5 * voxelSize,
                        _geometry.min(2) - 0.5 * voxelSize,
                        voxelSize,_nX, _nY, _nZ);

  // set all borders to _outerMaterialNo
  for(int x = 0; x < _nX; x++) {
    for(int y = 0; y < _nY; y++) {
      matrix.setMaterial(x,y,0, _outerMaterialNo);
      matrix.setMaterial(x,y,_nZ-1+2*pad, _outerMaterialNo);
    }
    for(int z = 0; z < _nZ; z++) {
      matrix.setMaterial(x,0,z, _outerMaterialNo);
      matrix.setMaterial(x,_nY-1+2*pad,z, _outerMaterialNo);
    }
  }
  for(int y = 0; y < _nY; y++) {
    for(int z = 0; z < _nZ; z++) {
      matrix.setMaterial(0,y,z, _outerMaterialNo);
      matrix.setMaterial(_nX-1+2*pad,y,z, _outerMaterialNo);
    }
  }

  Cuboid3D<T> cuboid;

  while (!q.empty()) {
    DNode3D node = q.front();
    q.pop();

    if (currentDepth < node.depth()) {
      currentDepth = node.depth();
    }

    // if the node is a branch
    if (!node.isLeaf()) {
      // we examine all of its children if we have not reached a certain depth
      if (node.depth() < limitHeight) {
        if (node.depth() == limitCuboid) {
          cuboid = cuboidFromNode(node, height, tree);
          cGeometry.add(cuboid);
        }
        for (int i = 0; i < (1 << 3); ++i) {
          q.push(node[i]);
        }
      }
      else {
        if (node.depth() == limitCuboid) {
          cuboid = cuboidFromNode(node, height, tree);
          cGeometry.add(cuboid);
          assert(1==0);
          // reconstruction of the indexes up to this node
          setMaterialForNode(matrix, node, height, tree);
        }
        else {
          assert(1==0);
          // reconstruction of the indexes up to this node
          setMaterialForNode(matrix, node, height, tree);
        }
      }
    }
    // if we have a leaf node that CONTAINS only liquid before the intended depth
    else {
      setMaterialForNode(matrix, node, height, tree);
      if (node() == 1) {
        if (node.depth() <= limitCuboid) {
          // otherwise, the cuboid will already have been added
          cuboid = cuboidFromNode(node, height, tree);
          cGeometry.add(cuboid);
        }

      }
    }
  }
}

template<typename T>
bool STLreader<T>::readDistance(T x, T y, T z, T dirX, T dirY, T dirZ, T & distance) {


  typedef float Tf;

  const Tf X0 = x;
  const Tf Y0 = y;
  const Tf Z0 = z;
  const Tf X1 = x+dirX;
  const Tf Y1 = y+dirY;
  const Tf Z1 = z+dirZ;

  std::vector<cvmlcpp::Point3D<Tf> > points;

  typedef typename cvmlcpp::Geometry<Tf>::const_facet_iterator const_facet_iterator;
  for (const_facet_iterator f = _geometry.facetsBegin();
       f != _geometry.facetsEnd(); ++f)
  {
    const cvmlcpp::Point3D<Tf> p0 = _geometry.point( (*f)[0] );
    const cvmlcpp::Point3D<Tf> p1 = _geometry.point( (*f)[1] );
    const cvmlcpp::Point3D<Tf> p2 = _geometry.point( (*f)[2] );

    const Tf Fx0 = std::min(p2[0],std::min(p0[0],p1[0])); 
    const Tf Fx1 = std::max(p2[0],std::max(p0[0],p1[0]));
    const Tf Ix0 = std::max(X0,Fx0);
    const Tf Ix1 = std::min(X1,Fx1);
    if (Ix1>=Ix0) {
      const Tf Fy0 = std::min(p2[1],std::min(p0[1],p1[1]));
      const Tf Fy1 = std::max(p2[1],std::max(p0[1],p1[1]));
      const Tf Iy0 = std::max(Y0,Fy0);
      const Tf Iy1 = std::min(Y1,Fy1);
      if (Iy1>=Iy0) {
        const Tf Fz0 = std::min(p2[2],std::min(p0[2],p1[2]));
        const Tf Fz1 = std::max(p2[2],std::max(p0[2],p1[2]));
        const Tf Iz0 = std::max(Z0,Fz0);
        const Tf Iz1 = std::min(Z1,Fz1);
        if (Iz1>=Iz0){
          points.push_back(p0);
          points.push_back(p1);
          points.push_back(p2);
        }
      }
    }
  }

  // There should be at least 1 facet in the geometry to prevent segmentation faults
  if (points.size() == 0){
    points.push_back(_geometry.point( (*_geometry.facetsBegin())[0] ));
    points.push_back(_geometry.point( (*_geometry.facetsBegin())[1] ));
    points.push_back(_geometry.point( (*_geometry.facetsBegin())[2] ));
  }

  // after collecting all facet points belonging to the current cuboid we
  // construct a separate geometry for the cuboid
  cvmlcpp::Geometry<float> g;
  cvmlcpp::detail::constructGeometry(g, points);
  //_cuboidGeometries.push_back(g);

  bool result = cvmlcpp::distance(g,
                           cvmlcpp::Point3D<T>(x,y,z),
                           cvmlcpp::Point3D<T>(dirX,dirY,dirZ),
                           distance);
  g.clear();
  return result;

/*
  return cvmlcpp::distance(_geometry,
                           cvmlcpp::Point3D<T>(x,y,z),
                           cvmlcpp::Point3D<T>(dirX,dirY,dirZ),
                           distance);*/
}

template<typename T>
bool STLreader<T>::readDistanceCuboid(T x, T y, T z, T dirX, T dirY, T dirZ, int lociC, T & distance) {

  return cvmlcpp::distance(_cuboidGeometries[lociC],
                           cvmlcpp::Point3D<T>(x,y,z),
                           cvmlcpp::Point3D<T>(dirX,dirY,dirZ),
                           distance);
}

template<typename T>
void STLreader<T>::setInnerMaterialNo(unsigned no) {
  _innerMaterialNo = no;
}

template<typename T>
void STLreader<T>::setOuterMaterialNo(unsigned no) {
  _outerMaterialNo = no;
}

template<typename T>
void STLreader<T>::splitGeometry(CuboidGeometry3D<T> &cGeometry, loadBalancer &load){
  OstreamManager clout(std::cout, "STLreader.splitGeometry");
  clout << "total number of facets: " << _geometry.nrFacets() << std::endl;
  clout.setMultiOutput(true);
  // vector of facet geometries should be empty
  typedef float Tf;
  // get information about the coordinate system
  const T voxelsize = cGeometry.get_motherC().get_delta();
  const T originX = cGeometry.get_motherC().get_globPosX();
  const T originY = cGeometry.get_motherC().get_globPosY();
  const T originZ = cGeometry.get_motherC().get_globPosZ();
  // iterate over local cuboids
  for (int locIC = 0; locIC < load.get_locChunkSize(); locIC++){
    const int globIC = load.glob(locIC);
    // get geometric information about the current cuboid
    const Tf X0 = originX + voxelsize* (Tf) (cGeometry.get_cuboid(globIC).get_globPosX()-3);
    const Tf Y0 = originY + voxelsize* (Tf) (cGeometry.get_cuboid(globIC).get_globPosY()-3);
    const Tf Z0 = originZ + voxelsize* (Tf) (cGeometry.get_cuboid(globIC).get_globPosZ()-3);
    const Tf X1 = X0 + voxelsize* (Tf) (cGeometry.get_cuboid(globIC).get_nX()+6);
    const Tf Y1 = Y0 + voxelsize* (Tf) (cGeometry.get_cuboid(globIC).get_nY()+6);
    const Tf Z1 = Z0 + voxelsize* (Tf) (cGeometry.get_cuboid(globIC).get_nZ()+6);

    std::vector<cvmlcpp::Point3D<Tf> > points;

    typedef typename cvmlcpp::Geometry<Tf>::const_facet_iterator const_facet_iterator;
    for (const_facet_iterator f = _geometry.facetsBegin();
         f != _geometry.facetsEnd(); ++f)
      {
      const cvmlcpp::Point3D<Tf> p0 = _geometry.point( (*f)[0] );
      const cvmlcpp::Point3D<Tf> p1 = _geometry.point( (*f)[1] );
      const cvmlcpp::Point3D<Tf> p2 = _geometry.point( (*f)[2] );

      const Tf Fx0 = std::min(p2[0],std::min(p0[0],p1[0])); 
      const Tf Fx1 = std::max(p2[0],std::max(p0[0],p1[0]));
      const Tf Ix0 = std::max(X0,Fx0);
      const Tf Ix1 = std::min(X1,Fx1);
      if (Ix1>=Ix0) {
        const Tf Fy0 = std::min(p2[1],std::min(p0[1],p1[1]));
        const Tf Fy1 = std::max(p2[1],std::max(p0[1],p1[1]));
        const Tf Iy0 = std::max(Y0,Fy0);
        const Tf Iy1 = std::min(Y1,Fy1);
        if (Iy1>=Iy0) {
          const Tf Fz0 = std::min(p2[2],std::min(p0[2],p1[2]));
          const Tf Fz1 = std::max(p2[2],std::max(p0[2],p1[2]));
          const Tf Iz0 = std::max(Z0,Fz0);
          const Tf Iz1 = std::min(Z1,Fz1);
          if (Iz1>=Iz0){
            points.push_back(p0);
            points.push_back(p1);
            points.push_back(p2);
          }
        }
      }
    }

    // There should be at least 1 facet in the geometry to prevent segmentation faults
    if (points.size() == 0){
      points.push_back(_geometry.point( (*_geometry.facetsBegin())[0] ));
      points.push_back(_geometry.point( (*_geometry.facetsBegin())[1] ));
      points.push_back(_geometry.point( (*_geometry.facetsBegin())[2] ));
    }

    // after collecting all facet points belonging to the current cuboid we
    // construct a separate geometry for the cuboid
    cvmlcpp::Geometry<float> g;
    cvmlcpp::detail::constructGeometry(g, points);
    clout << "Cuboid #" << globIC << " has "<< g.nrFacets() <<" Facets" << std::endl;
    _cuboidGeometries.push_back(g);
  }
  clout.setMultiOutput(false);
  // barrier necessary!

#ifdef PARALLEL_MODE_MPI
  singleton::mpi().barrier();
#endif  // PARALLEL_MODE_MPI

}

} // namespace olb

#endif  // STL_READER_H
