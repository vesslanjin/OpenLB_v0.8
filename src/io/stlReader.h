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
 * Input in STL format -- header file.
 */

#ifndef STL_READER_H
#define STL_READER_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

#include "external/cvmlcpp/base/Matrix"
#include "external/cvmlcpp/volume/Geometry"
#include "external/cvmlcpp/volume/VolumeIO"
#include "external/cvmlcpp/volume/Voxelizer"
#include "external/cvmlcpp/volume/DTree"

#include "core/blockGeometry3D.h"
#include "complexGrids/cuboidStructure/superGeometry3D.h"
#include "core/loadBalancer.h"
#include "complexGrids/cuboidStructure/cuboidGeometry3D.h"


namespace olb {

typedef cvmlcpp::DTreeProxy<int,3> DNode3D;

template<typename T>
class STLreader {
public:
  /**
   * Constructs a new STLreader from a file
   * \param fName The STL file name
   */
  STLreader(const std::string& fName);

  /**
   * destructor
   */
  ~STLreader();

  void scale(T scaling) {
    _geometry.scale(scaling);
  }

  void translate(T deltaX = 0, T deltaY = 0, T deltaZ = 0) {
    if (deltaX == 0 && deltaY == 0 && deltaZ == 0){
      deltaX = -_geometry.min(X);
      deltaY = -_geometry.min(Y);
      deltaZ = -_geometry.min(Z);
    }
    _geometry.translate(deltaX, deltaY, deltaZ);
  }

  /**
   * Read a voxel mesh from the stl file
   * \param matrix        contains the voxel mesh
   * \param direction
   * \param voxelNumber   number of voxels in direction
   * \param fraction      If fraction% of a voxel belong to the geometry the voxel belongs to the geometry
   * \param samples       The number of samples along each dimension of the voxels.
   * \params offset...    extent the geometry in the particular axis (N= negative, P= positiv)
   */
  void read(BlockGeometry3D &matrix,
            unsigned direction, unsigned voxelNumber, unsigned pad=0,
            double fraction=0, unsigned samples=3u,
            unsigned offsetXN=0, unsigned offsetXP=0,
            unsigned offsetYN=0, unsigned offsetYP=0,
            unsigned offsetZN=0, unsigned offsetZP=0) const;

  void read(SuperGeometry3D &matrix,
            unsigned direction, unsigned voxelNumber, unsigned pad=0,
            double fraction=0, unsigned samples=3u,
            unsigned offsetXN=0, unsigned offsetXP=0,
            unsigned offsetYN=0, unsigned offsetYP=0,
            unsigned offsetZN=0, unsigned offsetZP=0) const;

  /**
   * Read a voxel mesh from the stl file
   * \param matrix        to return the value
   * \param voxelSize     The size of voxels.
   * \param fraction      If fraction% of a voxel belong to the geometry the voxel belongs to the geometry
   * \param samples       The number of samples along each dimension of the voxels.
   * \params offset...    extent the geometry in the particular axis (N= negative, P= positiv)
   */
  void read(BlockGeometry3D &matrix, double voxelSize, unsigned pad=0,
            double fraction=0, unsigned samples=16u,
            unsigned offsetXN=0, unsigned offsetXP=0,
            unsigned offsetYN=0, unsigned offsetYP=0,
            unsigned offsetZN=0, unsigned offsetZP=0) const;

  void read(SuperGeometry3D &matrix, double voxelSize, unsigned pad=0,
            double fraction=0, unsigned samples=16u,
            unsigned offsetXN=0, unsigned offsetXP=0,
            unsigned offsetYN=0, unsigned offsetYP=0,
            unsigned offsetZN=0, unsigned offsetZP=0) const;
  /**
   * Read a voxel mesh from the stl file
   * \param matrix        To return the cuboid geometry
   * \param cGeometry     To return the value
   * \param voxelNumber   the number of voxels to generate
   * \param minCuboidSize The size of the smallest cuboid (each side will be
   *            greater or equal)
   */
  void read(CuboidGeometry3D<T> &cGeometry, BlockGeometry3D &matrix, unsigned voxelNumber, unsigned minCuboidSize=10, unsigned pad=0);

  void read(CuboidGeometry3D<T> &cGeometry, SuperGeometry3D &matrix, unsigned voxelNumber, unsigned minCuboidSize=10, unsigned pad=0);
  /**
   * Read a voxel mesh from the stl file and generate an octree of cuboids
   * \param matrix        To return the cuboid geometry
   * \param cGeometry     To return the value
   * \param voxelSize     The size of voxels to generate
   * \param minCuboidSize The size of the smallest cuboid (each side will be
   *            greater or equal)
   */
  void readOctree(CuboidGeometry3D<T> &cGeometry, BlockGeometry3D &matrix, double voxelSize, unsigned minCuboidSize=10, unsigned pad=0) const;

  void readOctree(CuboidGeometry3D<T> &cGeometry, SuperGeometry3D &matrix, double voxelSize, unsigned minCuboidSize=10, unsigned pad=0) const;

  /**
   * Read distance from a point to the next facet of the STL along a specific direction
   * \params x,y,z          the point from which the distance is to be determined
   * \params dirX,dirY,dirZ the vector along which the distance is to be determined
   * all quantities in physical units
   */
  bool readDistance(T x, T y, T z, T dirX, T dirY, T dirZ, T & distance);
  bool readDistanceCuboid(T x, T y, T z, T dirX, T dirY, T dirZ, int lociC, T & distance);

  void setInnerMaterialNo(unsigned no);
  void setOuterMaterialNo(unsigned no);
  Cuboid3D<T> cuboidFromNode(DNode3D &node, int height, cvmlcpp::DTree<int,3u> &tree) const;
  void setMaterialForNode(BlockGeometry3D &matrix, DNode3D &node, int height, cvmlcpp::DTree<int,3u> &tree) const;
  void setMaterialForNode(SuperGeometry3D &matrix, DNode3D &node, int height, cvmlcpp::DTree<int,3u> &tree) const;

  void splitGeometry(CuboidGeometry3D<T> &cGeometry, loadBalancer &load);

private:
  cvmlcpp::Geometry<float> _geometry;
  std::vector<cvmlcpp::Geometry<float> > _cuboidGeometries;
  int _innerMaterialNo, _outerMaterialNo;
  int _nX, _nY, _nZ;
};

}  // namespace olb

#endif  // STL_READER_H
