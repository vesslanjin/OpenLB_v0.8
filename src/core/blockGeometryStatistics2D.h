/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2011 Mathias J. Krause, Simon Zimny
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
 * Statistics of a geometry represented by a blockGeometry2D -- header file.
 */

#ifndef BLOCK_GEOMETRY_STATISTICS_2D_H
#define BLOCK_GEOMETRY_STATISTICS_2D_H

#include <vector>
#include <map>
#include <string>

#include "blockGeometry2D.h"
#include "io/ostreamManager.h"

/// All OpenLB code is contained in this namespace.
namespace olb {

class BlockGeometryStatistics2D {

private:
  /// class specific cout
  mutable OstreamManager clout;
  /// Input file name
  BlockGeometry2D* _blockGeometry;

  /// Number of voxels in each direction
  int _nX, _nY;

  /// Size of ghost voxel layer
  int _offset;

  /// Spacing
  double _h;

  std::map<unsigned short, int> _material2n;
  std::map<unsigned short, std::vector<int> > _material2min;
  std::map<unsigned short, std::vector<int> > _material2max;

public:
  /// Constructor
  BlockGeometryStatistics2D(BlockGeometry2D* blockGeometry)
    : clout(std::cout,"BlockGeometryStatistics2D") {
    reInit(blockGeometry);
  }
  ;
  /// Destructor
  ~BlockGeometryStatistics2D() {
  }
  ;

  /// reinitializes the blockGeometryStatistics (without checking the offset!!!!!!!)
  void reInit(BlockGeometry2D* blockGeometry) {
    _blockGeometry = blockGeometry;
    _material2n = std::map<unsigned short, int>();
    _nX = blockGeometry->getNx();
    _nY = blockGeometry->getNy();
    _h = blockGeometry->getSpacing();
    _offset = blockGeometry->getOffset();

    for (int iX = 0; iX < _nX; ++iX) {
      for (int iY = 0; iY < _nY; ++iY) {
        takeStatistics(iX, iY);
      }
    }
  }
  ;

  void takeStatistics(int iX, int iY);

  /// counts the number of voxels for the different boundary conditions (plus the number of inner and outer voxels)
  void countVoxel();

  /// returns normal that points into the fluid for paraxial surfaces
  std::vector<int> computeNormal(int iX, int iY);

  /// returns the number of voxels for a boundary condition type
  int getNVoxel(int bcType);

  std::vector<int> getMin(unsigned short material);

  std::vector<int> getMax(unsigned short material);

  std::vector<int> getNCo(unsigned short material);

  std::vector<int> getType(int iX, int iY);

  BlockGeometry2D* getBlockGeometry();

};

} // namespace olb

#endif
