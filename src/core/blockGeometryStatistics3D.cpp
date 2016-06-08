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
 * Statistics of a geometry represented by a blockGeometry3D -- implementation.
 */

#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <cmath>

#include "blockGeometry3D.h"
#include "blockGeometryStatistics3D.h"

namespace olb {


void BlockGeometryStatistics3D::reInit(BlockGeometry3D* blockGeometry) {
  _blockGeometry = blockGeometry;
  _material2n = std::map<unsigned short, int>();
  _nX = blockGeometry->getNx();
  _nY = blockGeometry->getNy();
  _nZ = blockGeometry->getNz();
  _h = blockGeometry->getSpacing();
  _offset = blockGeometry->getOffset();

  for (int iX = 0; iX < _nX; ++iX) {
    for (int iY = 0; iY < _nY; ++iY) {
      for (int iZ = 0; iZ < _nZ; ++iZ) {
        takeStatistics(iX, iY, iZ);
      }
    }
  }
}

void BlockGeometryStatistics3D::takeStatistics(int iX, int iY, int iZ) {
  unsigned short type = _blockGeometry->getMaterial(iX, iY, iZ);
  if (_material2n.count(type) == 0) {
    _material2n[type] = 1;
    std::vector<int> minCo;
    std::vector<int> maxCo;
    minCo.push_back(iX);
    minCo.push_back(iY);
    minCo.push_back(iZ);
    _material2min[type] = minCo;
    maxCo.push_back(iX);
    maxCo.push_back(iY);
    maxCo.push_back(iZ);
    _material2max[type] = maxCo;

  } else {
    _material2n[type]++;
    if (iX < _material2min[type][0])
      _material2min[type][0] = iX;
    if (iY < _material2min[type][1])
      _material2min[type][1] = iY;
    if (iZ < _material2min[type][2])
      _material2min[type][2] = iZ;
    if (iX > _material2max[type][0])
      _material2max[type][0] = iX;
    if (iY > _material2max[type][1])
      _material2max[type][1] = iY;
    if (iZ > _material2max[type][2])
      _material2max[type][2] = iZ;
  }
}

void BlockGeometryStatistics3D::countVoxel() {

  std::map<unsigned short, int>::iterator iter;
  for (iter = _material2n.begin(); iter != _material2n.end(); iter++) {
    clout << "materialNumber=" << iter->first
          << "; count=" << iter->second << std::endl;
  }
}

std::vector<int> BlockGeometryStatistics3D::computeNormal(int iX, int iY,
    int iZ) {
  std::vector<int> normal;
  normal.push_back(0);
  normal.push_back(0);
  normal.push_back(0);

  if (iX != 0) {
    if (_blockGeometry->getMaterial(iX - 1, iY, iZ) == 1)
      normal[0] = -1;
  }
  if (iX != _nX - 1) {
    if (_blockGeometry->getMaterial(iX + 1, iY, iZ) == 1)
      normal[0] = 1;
  }
  if (iY != 0) {
    if (_blockGeometry->getMaterial(iX, iY - 1, iZ) == 1)
      normal[1] = -1;
  }
  if (iY != _nY - 1) {
    if (_blockGeometry->getMaterial(iX, iY + 1, iZ) == 1)
      normal[1] = 1;
  }
  if (iZ != 0) {
    if (_blockGeometry->getMaterial(iX, iY, iZ - 1) == 1)
      normal[2] = -1;
  }
  if (iZ != _nZ - 1) {
    if (_blockGeometry->getMaterial(iX, iY, iZ + 1) == 1)
      normal[2] = 1;
  }
  return normal;
}

int BlockGeometryStatistics3D::getNVoxel(int bcType) {
  return _material2n[bcType];
}

int BlockGeometryStatistics3D::getNVoxel() {
  int total = 0;
  std::map<unsigned short, int>::iterator iter;
  for (iter = _material2n.begin(); iter != _material2n.end(); iter++) {
    if(iter->first!=0)
      total+=iter->second;
  }
  return total;
}

std::vector<int> BlockGeometryStatistics3D::getMin(unsigned short material) {
  return _material2min[material];
}
;

std::vector<int> BlockGeometryStatistics3D::getMax(unsigned short material) {
  return _material2max[material];
}
;

std::vector<int> BlockGeometryStatistics3D::getNCo(unsigned short material) {
  std::vector<int> nCo;
  for (int i = 0; i < 3; i++)
    nCo.push_back(_material2max[material][i] - _material2min[material][i]);
  return nCo;
}

BlockGeometry3D* BlockGeometryStatistics3D::getBlockGeometry() {
  return _blockGeometry;
}

std::vector<int> BlockGeometryStatistics3D::getType(int iX, int iY, int iZ) {

  std::vector<int> discreteNormal(4, 0);
  std::vector<int> discreteNormal2(4, 0);
  std::vector<int> nullVector(4, 0);

  if (_blockGeometry->getMaterial(iX, iY, iZ) != 1
      && _blockGeometry->getMaterial(iX, iY, iZ) != 0) {

    ///boundary0N and boundary 0P
    if (_blockGeometry->getMaterial(iX, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 0
        && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0) {

      if (_blockGeometry->getMaterial(iX + 1, iY, iZ) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 0;
          discreteNormal[1] = -1;
          discreteNormal[2] = 0;
          discreteNormal[3] = 0;

        }

        else {

          discreteNormal2[0] = 0;
          discreteNormal2[1] = -1;
          discreteNormal2[2] = 0;
          discreteNormal2[3] = 0;
        }

      }

      if (_blockGeometry->getMaterial(iX - 1, iY, iZ) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 0;
          discreteNormal[1] = 1;
          discreteNormal[2] = 0;
          discreteNormal[3] = 0;
        }

        else {

          discreteNormal2[0] = 0;
          discreteNormal2[1] = 1;
          discreteNormal2[2] = 0;
          discreteNormal2[3] = 0;
        }

      }
    }

    /// boundary1N and boundary1P
    if (_blockGeometry->getMaterial(iX, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 0
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 0) {

      if (_blockGeometry->getMaterial(iX, iY + 1, iZ) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 0;
          discreteNormal[1] = 0;
          discreteNormal[2] = -1;
          discreteNormal[3] = 0;
        }

        else {

          discreteNormal2[0] = 0;
          discreteNormal2[1] = 0;
          discreteNormal2[2] = -1;
          discreteNormal2[3] = 0;
        }

      }

      if (_blockGeometry->getMaterial(iX, iY - 1, iZ) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 0;
          discreteNormal[1] = 0;
          discreteNormal[2] = 1;
          discreteNormal[3] = 0;
        }

        else {

          discreteNormal2[0] = 0;
          discreteNormal2[1] = 0;
          discreteNormal2[2] = 1;
          discreteNormal2[3] = 0;
        }

      }
    }

    /// boundary2N and boundary2P
    if (_blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0) {

      if (_blockGeometry->getMaterial(iX, iY, iZ + 1) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 0;
          discreteNormal[1] = 0;
          discreteNormal[2] = 0;
          discreteNormal[3] = -1;
        }

        else {

          discreteNormal2[0] = 0;
          discreteNormal2[1] = 0;
          discreteNormal2[2] = 0;
          discreteNormal2[3] = -1;
        }

      }

      if (_blockGeometry->getMaterial(iX, iY, iZ - 1) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 0;
          discreteNormal[1] = 0;
          discreteNormal[2] = 0;
          discreteNormal[3] = 1;
        }

        else {

          discreteNormal2[0] = 0;
          discreteNormal2[1] = 0;
          discreteNormal2[2] = 0;
          discreteNormal2[3] = 1;
        }

      }
    }

    /// externalCornerNNN and externalCornerNPN
    if (_blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 0
        && _blockGeometry->getMaterial(iX + 1, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX + 1, iY, iZ + 1) != 0) {

      if (_blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0
          && _blockGeometry->getMaterial(iX + 1, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX + 1, iY + 1, iZ) != 0
          && _blockGeometry->getMaterial(iX, iY + 1, iZ + 1) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ + 1) != 0
          && _blockGeometry->getMaterial(iX + 1, iY + 1, iZ + 1) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 1;
          discreteNormal[1] = -1;
          discreteNormal[2] = -1;
          discreteNormal[3] = -1;
        }

        else {

          discreteNormal2[0] = 1;
          discreteNormal2[1] = -1;
          discreteNormal2[2] = -1;
          discreteNormal2[3] = -1;
        }

      }

      if (_blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0
          && _blockGeometry->getMaterial(iX + 1, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX + 1, iY - 1, iZ) != 0
          && _blockGeometry->getMaterial(iX, iY - 1, iZ + 1) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ + 1) != 0
          && _blockGeometry->getMaterial(iX + 1, iY - 1, iZ + 1) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 1;
          discreteNormal[1] = -1;
          discreteNormal[2] = 1;
          discreteNormal[3] = -1;
        }

        else {

          discreteNormal2[0] = 1;
          discreteNormal2[1] = -1;
          discreteNormal2[2] = 1;
          discreteNormal2[3] = -1;
        }

      }
    }

    /// externalCornerNPP and externalCornerNNP
    if (_blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 0
        && _blockGeometry->getMaterial(iX + 1, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX + 1, iY, iZ - 1) != 0) {

      if (_blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0
          && _blockGeometry->getMaterial(iX + 1, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX + 1, iY - 1, iZ) != 0
          && _blockGeometry->getMaterial(iX, iY - 1, iZ - 1) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ - 1) != 0
          && _blockGeometry->getMaterial(iX + 1, iY - 1, iZ - 1) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 1;
          discreteNormal[1] = -1;
          discreteNormal[2] = 1;
          discreteNormal[3] = 1;
        }

        else {

          discreteNormal2[0] = 1;
          discreteNormal2[1] = -1;
          discreteNormal2[2] = 1;
          discreteNormal2[3] = 1;
        }

      }

      if (_blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0
          && _blockGeometry->getMaterial(iX + 1, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX + 1, iY + 1, iZ) != 0
          && _blockGeometry->getMaterial(iX, iY + 1, iZ - 1) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ - 1) != 0
          && _blockGeometry->getMaterial(iX + 1, iY + 1, iZ - 1) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 1;
          discreteNormal[1] = -1;
          discreteNormal[2] = -1;
          discreteNormal[3] = 1;

        }

        else {

          discreteNormal2[0] = 1;
          discreteNormal2[1] = -1;
          discreteNormal2[2] = -1;
          discreteNormal2[3] = 1;
        }

      }
    }

    /// externalCornerPPP and externalCornerPNP
    if (_blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 0
        && _blockGeometry->getMaterial(iX - 1, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ - 1) != 0) {

      if (_blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0
          && _blockGeometry->getMaterial(iX, iY - 1, iZ - 1) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ - 1) != 0
          && _blockGeometry->getMaterial(iX - 1, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX - 1, iY - 1, iZ) != 0
          && _blockGeometry->getMaterial(iX - 1, iY - 1, iZ - 1) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 1;
          discreteNormal[1] = 1;
          discreteNormal[2] = 1;
          discreteNormal[3] = 1;
        }

        else {

          discreteNormal2[0] = 1;
          discreteNormal2[1] = 1;
          discreteNormal2[2] = 1;
          discreteNormal2[3] = 1;
        }
      }

      if (_blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0
          && _blockGeometry->getMaterial(iX, iY + 1, iZ - 1) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ - 1) != 0
          && _blockGeometry->getMaterial(iX - 1, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX - 1, iY + 1, iZ) != 0
          && _blockGeometry->getMaterial(iX - 1, iY + 1, iZ - 1) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 1;
          discreteNormal[1] = 1;
          discreteNormal[2] = -1;
          discreteNormal[3] = 1;
        }

        else {

          discreteNormal2[0] = 1;
          discreteNormal2[1] = 1;
          discreteNormal2[2] = -1;
          discreteNormal2[3] = 1;
        }

      }
    }

    /// externalCornerPNN and externalCornerPPN
    if (_blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 0
        && _blockGeometry->getMaterial(iX - 1, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ + 1) != 0) {

      if (_blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0
          && _blockGeometry->getMaterial(iX, iY + 1, iZ + 1) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ + 1) != 0
          && _blockGeometry->getMaterial(iX - 1, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX - 1, iY + 1, iZ) != 0
          && _blockGeometry->getMaterial(iX - 1, iY + 1, iZ + 1) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 1;
          discreteNormal[1] = 1;
          discreteNormal[2] = -1;
          discreteNormal[3] = -1;

        }

        else {

          discreteNormal2[0] = 1;
          discreteNormal2[1] = 1;
          discreteNormal2[2] = -1;
          discreteNormal2[3] = -1;
        }

      }

      if (_blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0
          && _blockGeometry->getMaterial(iX, iY - 1, iZ + 1) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ + 1) != 0
          && _blockGeometry->getMaterial(iX - 1, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX - 1, iY - 1, iZ) != 0
          && _blockGeometry->getMaterial(iX - 1, iY - 1, iZ + 1) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 1;
          discreteNormal[1] = 1;
          discreteNormal[2] = 1;
          discreteNormal[3] = -1;

        }

        else {

          discreteNormal2[0] = 1;
          discreteNormal2[1] = 1;
          discreteNormal2[2] = 1;
          discreteNormal2[3] = -1;
        }

      }
    }

    /// internalCornerPPP and internalCornerPNP
    if (_blockGeometry->getMaterial(iX - 1, iY, iZ) == 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) == 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 0
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 0) {

      if (_blockGeometry->getMaterial(iX, iY - 1, iZ) == 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 2;
          discreteNormal[1] = 1;
          discreteNormal[2] = 1;
          discreteNormal[3] = 1;

        }

        else {

          discreteNormal2[0] = 2;
          discreteNormal2[1] = 1;
          discreteNormal2[2] = 1;
          discreteNormal2[3] = 1;
        }

      }

      if (_blockGeometry->getMaterial(iX, iY + 1, iZ) == 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 2;
          discreteNormal[1] = 1;
          discreteNormal[2] = -1;
          discreteNormal[3] = 1;

        }

        else {

          discreteNormal2[0] = 2;
          discreteNormal2[1] = 1;
          discreteNormal2[2] = -1;
          discreteNormal2[3] = 1;
        }

      }
    }

    /// internalCornerPNN and InternalCornerPPN
    if (_blockGeometry->getMaterial(iX - 1, iY, iZ) == 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) == 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 0
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 0) {

      if (_blockGeometry->getMaterial(iX, iY + 1, iZ) == 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 2;
          discreteNormal[1] = 1;
          discreteNormal[2] = -1;
          discreteNormal[3] = -1;
        }

        else {

          discreteNormal2[0] = 2;
          discreteNormal2[1] = 1;
          discreteNormal2[2] = -1;
          discreteNormal2[3] = -1;
        }

      }

      if (_blockGeometry->getMaterial(iX, iY - 1, iZ) == 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 2;
          discreteNormal[1] = 1;
          discreteNormal[2] = 1;
          discreteNormal[3] = -1;
        }

        else {

          discreteNormal2[0] = 2;
          discreteNormal2[1] = 1;
          discreteNormal2[2] = 1;
          discreteNormal2[3] = -1;
        }

      }
    }

    /// internalCornerNPP and internalCornerNNP
    if (_blockGeometry->getMaterial(iX + 1, iY, iZ) == 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) == 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 0) {

      if (_blockGeometry->getMaterial(iX, iY - 1, iZ) == 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 2;
          discreteNormal[1] = -1;
          discreteNormal[2] = 1;
          discreteNormal[3] = 1;
        }

        else {

          discreteNormal2[0] = 2;
          discreteNormal2[1] = -1;
          discreteNormal2[2] = 1;
          discreteNormal2[3] = 1;
        }

      }

      if (_blockGeometry->getMaterial(iX, iY + 1, iZ) == 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 2;
          discreteNormal[1] = -1;
          discreteNormal[2] = -1;
          discreteNormal[3] = 1;
        }

        else {

          discreteNormal2[0] = 2;
          discreteNormal2[1] = -1;
          discreteNormal2[2] = -1;
          discreteNormal2[3] = 1;
        }

      }
    }

    /// internalCornerNPN and internalCornerNNN
    if (_blockGeometry->getMaterial(iX + 1, iY, iZ) == 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) == 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 0) {

      if (_blockGeometry->getMaterial(iX, iY - 1, iZ) == 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 2;
          discreteNormal[1] = -1;
          discreteNormal[2] = 1;
          discreteNormal[3] = -1;
        }

        else {

          discreteNormal2[0] = 2;
          discreteNormal2[1] = -1;
          discreteNormal2[2] = 1;
          discreteNormal2[3] = -1;
        }

      }

      if (_blockGeometry->getMaterial(iX, iY + 1, iZ) == 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 2;
          discreteNormal[1] = -1;
          discreteNormal[2] = -1;
          discreteNormal[3] = -1;
        }

        else {

          discreteNormal2[0] = 2;
          discreteNormal2[1] = -1;
          discreteNormal2[2] = -1;
          discreteNormal2[3] = -1;
        }

      }
    }

    /// externalEdge0PN and externalEdge0NN
    if (_blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 0
        && _blockGeometry->getMaterial(iX + 1, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ + 1) != 1) {

      if (_blockGeometry->getMaterial(iX, iY - 1, iZ + 1) == 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 3;
          discreteNormal[1] = 0;
          discreteNormal[2] = 1;
          discreteNormal[3] = -1;
        }

        else {

          discreteNormal2[0] = 3;
          discreteNormal2[1] = 0;
          discreteNormal2[2] = 1;
          discreteNormal2[3] = -1;
        }

      }

      if (_blockGeometry->getMaterial(iX, iY + 1, iZ + 1) == 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 3;
          discreteNormal[1] = 0;
          discreteNormal[2] = -1;
          discreteNormal[3] = -1;

        }

        else {

          discreteNormal2[0] = 3;
          discreteNormal2[1] = 0;
          discreteNormal2[2] = -1;
          discreteNormal2[3] = -1;
        }

      }
    }

    /// externalEdge0NP and externalEdge0PP
    if (_blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 0
        && _blockGeometry->getMaterial(iX + 1, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ - 1) != 1) {

      if (_blockGeometry->getMaterial(iX, iY + 1, iZ - 1) == 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 3;
          discreteNormal[1] = 0;
          discreteNormal[2] = -1;
          discreteNormal[3] = 1;
        }

        else {

          discreteNormal2[0] = 3;
          discreteNormal2[1] = 0;
          discreteNormal2[2] = -1;
          discreteNormal2[3] = 1;
        }

      }

      if (_blockGeometry->getMaterial(iX, iY - 1, iZ - 1) == 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 3;
          discreteNormal[1] = 0;
          discreteNormal[2] = 1;
          discreteNormal[3] = 1;

        }

        else {

          discreteNormal2[0] = 3;
          discreteNormal2[1] = 0;
          discreteNormal2[2] = 1;
          discreteNormal2[3] = 1;
        }

      }
    }

    /// externalEdge1NN and externalEdge1NP
    if (_blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 0) {

      if (_blockGeometry->getMaterial(iX + 1, iY, iZ + 1) == 1
          && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
          && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 0
          && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 3;
          discreteNormal[1] = -1;
          discreteNormal[2] = 0;
          discreteNormal[3] = -1;

        }

        else {

          discreteNormal2[0] = 3;
          discreteNormal2[1] = -1;
          discreteNormal2[2] = 0;
          discreteNormal2[3] = -1;
        }

      }

      if (_blockGeometry->getMaterial(iX - 1, iY, iZ + 1) == 1
          && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
          && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 0
          && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 3;
          discreteNormal[1] = 1;
          discreteNormal[2] = 0;
          discreteNormal[3] = -1;

        }

        else {

          discreteNormal2[0] = 3;
          discreteNormal2[1] = 1;
          discreteNormal2[2] = 0;
          discreteNormal2[3] = -1;
        }

      }
    }

    /// externalEdge1PN and externalEdge1PP
    if (_blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 0) {

      if (_blockGeometry->getMaterial(iX + 1, iY, iZ - 1) == 1
          && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
          && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 0
          && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 3;
          discreteNormal[1] = -1;
          discreteNormal[2] = 0;
          discreteNormal[3] = 1;

        }

        else {

          discreteNormal2[0] = 3;
          discreteNormal2[1] = -1;
          discreteNormal2[2] = 0;
          discreteNormal2[3] = 1;
        }

      }

      if (_blockGeometry->getMaterial(iX - 1, iY, iZ - 1) == 1
          && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
          && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 0
          && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 3;
          discreteNormal[1] = 1;
          discreteNormal[2] = 0;
          discreteNormal[3] = 1;

        }

        else {

          discreteNormal2[0] = 3;
          discreteNormal2[1] = 1;
          discreteNormal2[2] = 0;
          discreteNormal2[3] = 1;
        }

      }
    }

    /// externalEdge2NN and externalEdge2PN
    if (_blockGeometry->getMaterial(iX, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 0
        && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0) {

      if (_blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
          && _blockGeometry->getMaterial(iX + 1, iY + 1, iZ) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 3;
          discreteNormal[1] = -1;
          discreteNormal[2] = -1;
          discreteNormal[3] = 0;

        }

        else {

          discreteNormal2[0] = 3;
          discreteNormal2[1] = -1;
          discreteNormal2[2] = -1;
          discreteNormal2[3] = 0;
        }

      }

      if (_blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
          && _blockGeometry->getMaterial(iX - 1, iY + 1, iZ) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 3;
          discreteNormal[1] = 1;
          discreteNormal[2] = -1;
          discreteNormal[3] = 0;
        }

        else {

          discreteNormal2[0] = 3;
          discreteNormal2[1] = 1;
          discreteNormal2[2] = -1;
          discreteNormal2[3] = 0;
        }

      }
    }

    /// externalEdge2PP and externalEdge2NP
    if (_blockGeometry->getMaterial(iX, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 0
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0) {

      if (_blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
          && _blockGeometry->getMaterial(iX - 1, iY - 1, iZ) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 3;
          discreteNormal[1] = 1;
          discreteNormal[2] = 1;
          discreteNormal[3] = 0;
        }

        else {

          discreteNormal2[0] = 3;
          discreteNormal2[1] = 1;
          discreteNormal2[2] = 1;
          discreteNormal2[3] = 0;
        }

      }

      if (_blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
          && _blockGeometry->getMaterial(iX + 1, iY - 1, iZ) == 1) {

        if (discreteNormal == nullVector) {

          discreteNormal[0] = 3;
          discreteNormal[1] = -1;
          discreteNormal[2] = 1;
          discreteNormal[3] = 0;

        }

        else {

          discreteNormal2[0] = 3;
          discreteNormal2[1] = -1;
          discreteNormal2[2] = 1;
          discreteNormal2[3] = 0;
        }

      }
    }

    ///internalEdge0NN and internalEdge0PN
    if (_blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) == 1) {

      if (_blockGeometry->getMaterial(iX, iY + 1, iZ) == 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0
          && _blockGeometry->getMaterial(iX - 1, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX - 1, iY - 1, iZ) != 0
          && _blockGeometry->getMaterial(iX + 1, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX + 1, iY - 1, iZ) != 0) {

        discreteNormal[0] = 4;
        discreteNormal[1] = 0;
        discreteNormal[2] = -1;
        discreteNormal[3] = -1;

      }

      if (_blockGeometry->getMaterial(iX, iY - 1, iZ) == 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0
          && _blockGeometry->getMaterial(iX - 1, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX - 1, iY + 1, iZ) != 0
          && _blockGeometry->getMaterial(iX + 1, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX + 1, iY + 1, iZ) != 0) {

        discreteNormal[0] = 4;
        discreteNormal[1] = 0;
        discreteNormal[2] = 1;
        discreteNormal[3] = -1;

      }
    }

    /// internalEdge0NP and internalEdge0PP
    if (_blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) == 1) {

      if (_blockGeometry->getMaterial(iX, iY + 1, iZ) == 1
          && _blockGeometry->getMaterial(iX - 1, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX - 1, iY - 1, iZ) != 0
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0
          && _blockGeometry->getMaterial(iX + 1, iY - 1, iZ) != 1
          && _blockGeometry->getMaterial(iX + 1, iY - 1, iZ) != 0) {

        discreteNormal[0] = 4;
        discreteNormal[1] = 0;
        discreteNormal[2] = -1;
        discreteNormal[3] = 1;

      }

      if (_blockGeometry->getMaterial(iX, iY - 1, iZ) == 1
          && _blockGeometry->getMaterial(iX - 1, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX - 1, iY + 1, iZ) != 0
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0
          && _blockGeometry->getMaterial(iX + 1, iY + 1, iZ) != 1
          && _blockGeometry->getMaterial(iX + 1, iY + 1, iZ) != 0) {

        discreteNormal[0] = 4;
        discreteNormal[1] = 0;
        discreteNormal[2] = 1;
        discreteNormal[3] = 1;

      }
    }

    /// internalEdge1PP and internalEdge 1NP
    if (_blockGeometry->getMaterial(iX - 1, iY, iZ) == 1
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX + 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0) {

      if (_blockGeometry->getMaterial(iX, iY, iZ - 1) == 1
          && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 1
          && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 0
          && _blockGeometry->getMaterial(iX, iY + 1, iZ + 1) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ + 1) != 0
          && _blockGeometry->getMaterial(iX, iY - 1, iZ + 1) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ + 1) != 0) {

        discreteNormal[0] = 4;
        discreteNormal[1] = 1;
        discreteNormal[2] = 0;
        discreteNormal[3] = 1;

      }

      if (_blockGeometry->getMaterial(iX, iY, iZ + 1) == 1
          && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1
          && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 0
          && _blockGeometry->getMaterial(iX, iY + 1, iZ - 1) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ - 1) != 0
          && _blockGeometry->getMaterial(iX, iY - 1, iZ - 1) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ - 1) != 0) {

        discreteNormal[0] = 4;
        discreteNormal[1] = 1;
        discreteNormal[2] = 0;
        discreteNormal[3] = -1;

      }
    }

    /// internalEdge1PN and internalEdge1NN
    if (_blockGeometry->getMaterial(iX + 1, iY, iZ) == 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 1
        && _blockGeometry->getMaterial(iX - 1, iY, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0
        && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0) {

      if (_blockGeometry->getMaterial(iX, iY, iZ - 1) == 1
          && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 1
          && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 0
          && _blockGeometry->getMaterial(iX, iY + 1, iZ + 1) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ + 1) != 0
          && _blockGeometry->getMaterial(iX, iY - 1, iZ + 1) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ + 1) != 0) {

        discreteNormal[0] = 4;
        discreteNormal[1] = -1;
        discreteNormal[2] = 0;
        discreteNormal[3] = 1;

      }

      if (_blockGeometry->getMaterial(iX, iY, iZ + 1) == 1
          && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1
          && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 0
          && _blockGeometry->getMaterial(iX, iY + 1, iZ - 1) != 1
          && _blockGeometry->getMaterial(iX, iY + 1, iZ - 1) != 0
          && _blockGeometry->getMaterial(iX, iY - 1, iZ - 1) != 1
          && _blockGeometry->getMaterial(iX, iY - 1, iZ - 1) != 0) {

        discreteNormal[0] = 4;
        discreteNormal[1] = -1;
        discreteNormal[2] = 0;
        discreteNormal[3] = -1;

      }
    }

    /// internalEdge2PP and internalEdge2NP
    if (_blockGeometry->getMaterial(iX, iY - 1, iZ) == 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 0
        && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY + 1, iZ) != 0) {

      if (_blockGeometry->getMaterial(iX - 1, iY, iZ) == 1
          && _blockGeometry->getMaterial(iX - 1, iY - 1, iZ) == 1) {

        discreteNormal[0] = 4;
        discreteNormal[1] = 1;
        discreteNormal[2] = 1;
        discreteNormal[3] = 0;

      }

      if (_blockGeometry->getMaterial(iX + 1, iY, iZ) == 1
          && _blockGeometry->getMaterial(iX + 1, iY - 1, iZ) == 1) {

        discreteNormal[0] = 4;
        discreteNormal[1] = -1;
        discreteNormal[2] = 1;
        discreteNormal[3] = 0;

      }
    }

    /// internalEdge2PN and internalEdge2NN
    if (_blockGeometry->getMaterial(iX, iY + 1, iZ) == 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ - 1) != 0
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 1
        && _blockGeometry->getMaterial(iX, iY, iZ + 1) != 0
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 1
        && _blockGeometry->getMaterial(iX, iY - 1, iZ) != 0) {

      if (_blockGeometry->getMaterial(iX - 1, iY, iZ) == 1
          && _blockGeometry->getMaterial(iX - 1, iY + 1, iZ) == 1) {

        discreteNormal[0] = 4;
        discreteNormal[1] = 1;
        discreteNormal[2] = -1;
        discreteNormal[3] = 0;

      }

      if (_blockGeometry->getMaterial(iX + 1, iY, iZ) == 1
          && _blockGeometry->getMaterial(iX + 1, iY + 1, iZ) == 1) {

        discreteNormal[0] = 4;
        discreteNormal[1] = -1;
        discreteNormal[2] = -1;
        discreteNormal[3] = 0;

      }
    }

    ///special boundary conditions

    if (discreteNormal2 != nullVector) {

      discreteNormal
      = checkExtraBoundary(discreteNormal, discreteNormal2);
    }

  }

  return discreteNormal;

}

/// This function compares two discrete normals (discreteNormal, discreteNormal2) in case of a duplicate assignment of boundary types.
/// The goal of this function is to combine these special boundaryVoxels to an existing one (in this case boundary or externalEdge) according to
/// the x-, y- and z-values of their discrete normals.
/// In the following the algorithm is declared only for the x value, but it is also valid for the y and z values.
///
/// for x1 = x2, the new value of x is x1 (1)
/// for x1*x2 = -1, the new value of x is 0 (2)
/// for x1*x2 = 0, the new value is 0   (3)
///
/// It may be possible that all three values equal 0. To avoid that the values are tested again (x²+y²+z²==0) and the loosest assumption (3) is
/// redefined to.
///
/// If x,y and z == 0 --> find those x,y or z which are 0 because of (3) and redefine them to the value !=0
///
/// Additionally the calculated entries are multiplied with (-1) to get the right existing boundary.


std::vector<int> BlockGeometryStatistics3D::checkExtraBoundary(
  std::vector<int> discreteNormal, std::vector<int> discreteNormal2) {

  std::vector<int> Data(6, 0);

  for (int i = 1; i < 4; i++) {

    if (discreteNormal[i] == discreteNormal2[i]) {
      Data[i - 1] = (-1) * discreteNormal2[i];
      Data[i + 2] = 1;

    }

    else if (discreteNormal[i] * discreteNormal2[i] == -1) {
      Data[i - 1] = 0;
      Data[i + 2] = 2;

    }

    else if (discreteNormal[i] * discreteNormal2[i] == 0) {
      Data[i - 1] = 0;
      Data[i + 2] = 3;

    }
  }

  std::vector<int> newDiscreteNormal(4, 0);

  for (int i = 1; i < 4; i++) {
    newDiscreteNormal[i] = Data[i - 1];
  }

  if (Data[0] * Data[0] + Data[1] * Data[1] + Data[2] * Data[2] == 0) {

    for (int i = 1; i < 4; i++) {

      if (Data[i + 2] == 3) {

        if (discreteNormal[i] == 0) {

          newDiscreteNormal[i] = (-1) * discreteNormal2[i];
        } else {

          newDiscreteNormal[i] = (-1) * discreteNormal[i];
        }
      }
    }
  }

  if (newDiscreteNormal[1] * newDiscreteNormal[1] + newDiscreteNormal[2]
      * newDiscreteNormal[2] + newDiscreteNormal[3]
      * newDiscreteNormal[3] == 1) {
    newDiscreteNormal[0] = 0;
  } else {
    newDiscreteNormal[0] = 3;
  }
  return newDiscreteNormal;
}

bool BlockGeometryStatistics3D::check(unsigned short material, int iX, int iY,
                                      int iZ, unsigned offsetX, unsigned offsetY, unsigned offsetZ) {

  bool found = true;
  for (int iOffsetX = -offsetX; iOffsetX <= (int) offsetX; ++iOffsetX) {
    for (int iOffsetY = -offsetY; iOffsetY <= (int) offsetY; ++iOffsetY) {
      for (int iOffsetZ = -offsetZ; iOffsetZ <= (int) offsetZ; ++iOffsetZ) {
        if (_blockGeometry->getMaterial(iX + iOffsetX, iY + iOffsetY,
                                        iZ + iOffsetZ) != material)
          found = false;
      }
    }
  }
  return found;
}

bool BlockGeometryStatistics3D::find(unsigned short material, unsigned offsetX,
                                     unsigned offsetY, unsigned offsetZ, int& foundX, int& foundY,
                                     int& foundZ) {

  bool found = false;
  for (foundX = 0; foundX < _nX; foundX++) {
    for (foundY = 0; foundY < _nY; foundY++) {
      for (foundZ = 0; foundZ < _nZ; foundZ++) {
        found = check(material, foundX, foundY, foundZ, offsetX,
                      offsetY, offsetZ);
        if (found)
          return found;
      }
    }
  }
  return found;
}

void BlockGeometryStatistics3D::regionGrowing(unsigned short material,
    int seedX, int seedY, int seedZ, int offsetX, int offsetY, int offsetZ,
    std::map<std::vector<int>, int>& tmp) {

  if (_blockGeometry->getMaterial(seedX, seedY, seedZ) == material) {
    std::vector<int> found;
    found.push_back(seedX);
    found.push_back(seedY);
    found.push_back(seedZ);
    if (tmp.count(found) == 0) {
      tmp[found] = 2;
      if (offsetX != 0) {
        regionGrowing(material, seedX + 1, seedY, seedZ, offsetX,
                      offsetY, offsetZ, tmp);
        regionGrowing(material, seedX - 1, seedY, seedZ, offsetX,
                      offsetY, offsetZ, tmp);
      }
      if (offsetY != 0) {
        regionGrowing(material, seedX, seedY + 1, seedZ, offsetX,
                      offsetY, offsetZ, tmp);
        regionGrowing(material, seedX, seedY - 1, seedZ, offsetX,
                      offsetY, offsetZ, tmp);
      }
      if (offsetZ != 0) {
        regionGrowing(material, seedX, seedY, seedZ + 1, offsetX,
                      offsetY, offsetZ, tmp);
        regionGrowing(material, seedX, seedY, seedZ - 1, offsetX,
                      offsetY, offsetZ, tmp);
      }
    }
  }
  return;
}
;

} // namespace olb
