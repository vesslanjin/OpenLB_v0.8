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
 * Statistics of a geometry represented by a blockGeometry2D -- implementation.
 */

#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <cmath>

#include "blockGeometryStatistics2D.h"

namespace olb {

void BlockGeometryStatistics2D::takeStatistics(int iX, int iY) {
  unsigned short type = _blockGeometry->getMaterial(iX, iY);
  if (_material2n.count(type) == 0) {
    _material2n[type] = 1;
    std::vector<int> minCo;
    std::vector<int> maxCo;
    minCo.push_back(iX);
    minCo.push_back(iY);
    _material2min[type] = minCo;
    maxCo.push_back(iX);
    maxCo.push_back(iY);
    _material2max[type] = maxCo;

  } else {
    _material2n[type]++;
    if (iX < _material2min[type][0])
      _material2min[type][0] = iX;
    if (iY < _material2min[type][1])
      _material2min[type][1] = iY;
    if (iX > _material2max[type][0])
      _material2max[type][0] = iX;
    if (iY > _material2max[type][1])
      _material2max[type][1] = iY;
  }
}

void BlockGeometryStatistics2D::countVoxel() {

  std::map<unsigned short, int>::iterator iter;
  for (iter = _material2n.begin(); iter != _material2n.end(); iter++) {
    clout << "materialNumber=" << iter->first << "; count=" << iter->second
          << std::endl;
  }
}

std::vector<int> BlockGeometryStatistics2D::computeNormal(int iX, int iY) {
  std::vector<int> normal;
  normal.push_back(0);
  normal.push_back(0);

  if (iX != 0) {
    if (_blockGeometry->getMaterial(iX - 1, iY) == 1)
      normal[0] = -1;
  }
  if (iX != _nX - 1) {
    if (_blockGeometry->getMaterial(iX + 1, iY) == 1)
      normal[0] = 1;
  }
  if (iY != 0) {
    if (_blockGeometry->getMaterial(iX, iY - 1) == 1)
      normal[1] = -1;
  }
  if (iY != _nY - 1) {
    if (_blockGeometry->getMaterial(iX, iY + 1) == 1)
      normal[1] = 1;
  }

  return normal;
}

int BlockGeometryStatistics2D::getNVoxel(int bcType) {
  return _material2n[bcType];
}

std::vector<int> BlockGeometryStatistics2D::getMin(unsigned short material) {
  return _material2min[material];
}
;

std::vector<int> BlockGeometryStatistics2D::getMax(unsigned short material) {
  return _material2max[material];
}
;

std::vector<int> BlockGeometryStatistics2D::getNCo(unsigned short material) {
  std::vector<int> nCo;
  for (int i = 0; i < 2; i++)
    nCo.push_back(_material2max[material][i] - _material2min[material][i]);
  return nCo;
}

BlockGeometry2D* BlockGeometryStatistics2D::getBlockGeometry() {
  return _blockGeometry;
}

std::vector<int> BlockGeometryStatistics2D::getType(int iX, int iY) {

  std::vector<int> discreteNormal(3, 0);

  if (_blockGeometry->getMaterial(iX, iY) != 1
      && _blockGeometry->getMaterial(iX, iY) != 0) {

    ///boundary0N and boundary 0P
    if (_blockGeometry->getMaterial(iX, iY + 1) != 1
        && _blockGeometry->getMaterial(iX, iY + 1) != 0
        && _blockGeometry->getMaterial(iX, iY - 1) != 1
        && _blockGeometry->getMaterial(iX, iY - 1) != 0) {

      if (_blockGeometry->getMaterial(iX + 1, iY) == 1) {

        discreteNormal[0] = 0;
        discreteNormal[1] = -1;
        discreteNormal[2] = 0;

      }

      if (_blockGeometry->getMaterial(iX - 1, iY) == 1) {

        discreteNormal[0] = 0;
        discreteNormal[1] = 1;
        discreteNormal[2] = 0;

      }
    }

    /// boundary1N and boundary1P
    if (_blockGeometry->getMaterial(iX + 1, iY) != 1
        && _blockGeometry->getMaterial(iX + 1, iY) != 0
        && _blockGeometry->getMaterial(iX - 1, iY) != 1
        && _blockGeometry->getMaterial(iX - 1, iY) != 0) {

      if (_blockGeometry->getMaterial(iX, iY + 1) == 1) {

        discreteNormal[0] = 0;
        discreteNormal[1] = 0;
        discreteNormal[2] = -1;

      }

      if (_blockGeometry->getMaterial(iX, iY - 1) == 1) {

        discreteNormal[0] = 0;
        discreteNormal[1] = 0;
        discreteNormal[2] = 1;

      }
    }

    /// externalCornerNN and externalCornerNP
    if (_blockGeometry->getMaterial(iX + 1, iY) != 1
        && _blockGeometry->getMaterial(iX + 1, iY) != 0) {

      if (_blockGeometry->getMaterial(iX, iY + 1) != 1
          && _blockGeometry->getMaterial(iX, iY + 1) != 0
          && _blockGeometry->getMaterial(iX + 1, iY + 1) == 1) {

        discreteNormal[0] = 1;
        discreteNormal[1] = -1;
        discreteNormal[2] = -1;

      }

      if (_blockGeometry->getMaterial(iX, iY - 1) != 1
          && _blockGeometry->getMaterial(iX, iY - 1) != 0
          && _blockGeometry->getMaterial(iX + 1, iY - 1) == 1) {

        discreteNormal[0] = 1;
        discreteNormal[1] = -1;
        discreteNormal[2] = 1;

      }
    }

    /// externalCornerPN and externalCornerPP
    if (_blockGeometry->getMaterial(iX - 1, iY) != 1
        && _blockGeometry->getMaterial(iX - 1, iY) != 0) {

      if (_blockGeometry->getMaterial(iX, iY + 1) != 1
          && _blockGeometry->getMaterial(iX, iY + 1) != 0
          && _blockGeometry->getMaterial(iX - 1, iY + 1) == 1) {

        discreteNormal[0] = 1;
        discreteNormal[1] = 1;
        discreteNormal[2] = -1;

      }

      if (_blockGeometry->getMaterial(iX, iY - 1) != 1
          && _blockGeometry->getMaterial(iX, iY - 1) != 0
          && _blockGeometry->getMaterial(iX - 1, iY - 1) == 1) {

        discreteNormal[0] = 1;
        discreteNormal[1] = 1;
        discreteNormal[2] = 1;
      }
    }

    /// internalCornerNN and internalCornerNP
    if (_blockGeometry->getMaterial(iX - 1, iY) != 1
        && _blockGeometry->getMaterial(iX - 1, iY) != 0) {

      if (_blockGeometry->getMaterial(iX, iY - 1) != 1
          && _blockGeometry->getMaterial(iX, iY - 1) != 0
          && _blockGeometry->getMaterial(iX - 1, iY - 1) == 0) {

        discreteNormal[0] = 2;
        discreteNormal[1] = -1;
        discreteNormal[2] = -1;

      }

      if (_blockGeometry->getMaterial(iX, iY + 1) != 1
          && _blockGeometry->getMaterial(iX, iY + 1) != 0
          && _blockGeometry->getMaterial(iX - 1, iY + 1) == 0) {

        discreteNormal[0] = 2;
        discreteNormal[1] = -1;
        discreteNormal[2] = 1;

      }
    }

    /// internalCornerPN and internalCornerPP
    if (_blockGeometry->getMaterial(iX + 1, iY) != 1
        && _blockGeometry->getMaterial(iX + 1, iY) != 0) {

      if (_blockGeometry->getMaterial(iX, iY - 1) != 1
          && _blockGeometry->getMaterial(iX, iY - 1) != 0
          && _blockGeometry->getMaterial(iX + 1, iY - 1) == 0) {

        discreteNormal[0] = 2;
        discreteNormal[1] = 1;
        discreteNormal[2] = -1;

      }

      if (_blockGeometry->getMaterial(iX, iY + 1) != 1
          && _blockGeometry->getMaterial(iX, iY + 1) != 0
          && _blockGeometry->getMaterial(iX + 1, iY + 1) == 0) {

        discreteNormal[0] = 2;
        discreteNormal[1] = 1;
        discreteNormal[2] = 1;

      }
    }
  }
  return discreteNormal;
}

} // namespace olb
