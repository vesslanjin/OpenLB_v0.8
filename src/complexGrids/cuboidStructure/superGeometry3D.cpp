/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2013 Mathias J. Krause
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
 * Representation of the 3D geometry -- implementation.
 */

#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>

#include "io/vtkDataOutput.h"
#include "io/vtkDataOutput.hh"
#include "superGeometry3D.h"
#include "core/dataFields3D.h"
#include "core/dataFields3D.hh"
#include "core/dataFields2D.h"
#include "core/dataFields2D.hh"
#include "core/serializer.h"
#include "core/serializer.hh"
#include "io/serializerIO.h"
#include "io/serializerIO.hh"
#include "io/base64.h"
#include "io/base64.hh"
#include "io/ostreamManager.h"




namespace olb {

double SuperGeometry3D::getPositionX() {
  return _x0;
}

void SuperGeometry3D::setPositionX(double x0) {
  _x0 = x0;
}

double SuperGeometry3D::getPositionY() {
  return _y0;
}

void SuperGeometry3D::setPositionY(double y0) {
  _y0 = y0;
}

double SuperGeometry3D::getPositionZ() {
  return _z0;
}

void SuperGeometry3D::setPositionZ(double z0) {
  _z0 = z0;
}

double SuperGeometry3D::getSpacing() {
  return _h;
}

void SuperGeometry3D::setSpacing(double h) {
  _h = h;
}

int SuperGeometry3D::getOffset() {
  return _offset;
}
;

void SuperGeometry3D::setOffset(int offset) {
  _offset = offset;
}

int SuperGeometry3D::getNx() {
  return _nx;
}

void SuperGeometry3D::setNx(int nX) {
  _nx = nX;
}

int SuperGeometry3D::getNy() {
  return _ny;
}

void SuperGeometry3D::setNy(int nY) {
  _ny = nY;
}
;

int SuperGeometry3D::getNz() {
  return _nz;
}

void SuperGeometry3D::setNz(int nZ) {
  _nz = nZ;
}

void SuperGeometry3D::reInit(double x0, double y0, double z0, double h, int nX,
                             int nY, int nZ, int offset,
                             olb::ScalarField3D<unsigned short>* geometryData) {

  setPositionX(x0);
  setPositionY(y0);
  setPositionZ(z0);

  setSpacing(h);

  setNx(nX);
  setNy(nY);
  setNz(nZ);

  setOffset(offset);

  if (geometryData != NULL) {
    _geometryData.swap(*geometryData);
  }
  else {
    olb::ScalarField3D<unsigned short> geometryDataTemp(nX + 2 * offset, nY + 2 * offset, nZ + 2 * offset);
    _geometryData.swap(geometryDataTemp);
    _geometryData.construct();
    _geometryData.reset();
    geometryDataTemp.deConstruct();
  }
}

unsigned short SuperGeometry3D::getMaterial(int iX, int iY, int iZ) {
  unsigned short material;
  if (iX + _offset < 0 || iX + 1 > _nx + _offset || iY + _offset < 0 || iY
      + 1 > _ny + _offset || iZ + _offset < 0 || iZ + 1 > _nz + _offset)
    material = 0;
  else
    material = _geometryData.get(iX + _offset, iY + _offset, iZ + _offset);
  return material;
}

void SuperGeometry3D::setMaterial(int iX, int iY, int iZ,
                                  unsigned short material) {
  _geometryData.get(iX + _offset, iY + _offset, iZ + _offset) = material;
  _statisticsUpdateNeeded = true;
}

olb::ScalarField3D<unsigned short>* SuperGeometry3D::getRawData() {
  return &_geometryData;
}

/// new Functions

void SuperGeometry3D::clean() {
  int counter=0;
  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {
      for (int iZ = 0; iZ < _nz; iZ++) {

        if (getMaterial(iX, iY, iZ) != 1 && getMaterial(iX, iY, iZ)
            != 0) {

          if (
            getMaterial(iX - 1, iY, iZ) != 1
            && getMaterial(iX, iY - 1, iZ) != 1
            && getMaterial(iX, iY, iZ - 1) != 1
            && getMaterial(iX - 1, iY - 1, iZ) != 1
            && getMaterial(iX, iY - 1, iZ - 1) != 1
            && getMaterial(iX - 1, iY, iZ - 1) != 1
            && getMaterial(iX - 1, iY - 1, iZ - 1) != 1
            && getMaterial(iX + 1, iY, iZ) != 1
            && getMaterial(iX, iY + 1, iZ) != 1
            && getMaterial(iX, iY, iZ + 1) != 1
            && getMaterial(iX + 1, iY + 1, iZ) != 1
            && getMaterial(iX, iY + 1, iZ + 1) != 1
            && getMaterial(iX + 1, iY, iZ + 1) != 1
            && getMaterial(iX + 1, iY + 1, iZ + 1) != 1
            && getMaterial(iX - 1, iY + 1, iZ) != 1
            && getMaterial(iX + 1, iY - 1, iZ) != 1
            && getMaterial(iX, iY - 1, iZ + 1) != 1
            && getMaterial(iX, iY + 1, iZ - 1) != 1
            && getMaterial(iX - 1, iY, iZ + 1) != 1
            && getMaterial(iX + 1, iY, iZ - 1) != 1
            && getMaterial(iX + 1, iY + 1, iZ - 1) != 1
            && getMaterial(iX + 1, iY - 1, iZ - 1) != 1
            && getMaterial(iX + 1, iY - 1, iZ + 1) != 1
            && getMaterial(iX - 1, iY + 1, iZ + 1) != 1
            && getMaterial(iX - 1, iY - 1, iZ + 1) != 1
            && getMaterial(iX - 1, iY + 1, iZ - 1) != 1) {

            setMaterial(iX, iY, iZ, 0);
            counter++;
          }
        }
      }
    }
  }
  clout << "cleaned "<< counter << " outer boundary voxel(s)" << std::endl;
}

void SuperGeometry3D::outerClean() {
  int counter=0;
  for (int iX = -_offset; iX < _nx + _offset; iX++) {
    for (int iY = -_offset; iY < _ny + _offset; iY++) {
      for (int iZ = -_offset; iZ < _nz + _offset; iZ++) {

        if (getMaterial(iX, iY, iZ) == 1) {
          if (   getMaterial(iX - 1, iY,     iZ    ) == 0
              || getMaterial(iX,     iY - 1, iZ    ) == 0
              || getMaterial(iX,     iY,     iZ - 1) == 0
              || getMaterial(iX - 1, iY - 1, iZ    ) == 0
              || getMaterial(iX,     iY - 1, iZ - 1) == 0
              || getMaterial(iX - 1, iY,     iZ - 1) == 0
              || getMaterial(iX - 1, iY - 1, iZ - 1) == 0
              || getMaterial(iX + 1, iY,     iZ    ) == 0
              || getMaterial(iX,     iY + 1, iZ    ) == 0
              || getMaterial(iX,     iY,     iZ + 1) == 0
              || getMaterial(iX + 1, iY + 1, iZ    ) == 0
              || getMaterial(iX,     iY + 1, iZ + 1) == 0
              || getMaterial(iX + 1, iY,     iZ + 1) == 0
              || getMaterial(iX + 1, iY + 1, iZ + 1) == 0
              || getMaterial(iX - 1, iY + 1, iZ    ) == 0
              || getMaterial(iX + 1, iY - 1, iZ    ) == 0
              || getMaterial(iX,     iY - 1, iZ + 1) == 0
              || getMaterial(iX,     iY + 1, iZ - 1) == 0
              || getMaterial(iX - 1, iY,     iZ + 1) == 0
              || getMaterial(iX + 1, iY,     iZ - 1) == 0
              || getMaterial(iX + 1, iY + 1, iZ - 1) == 0
              || getMaterial(iX + 1, iY - 1, iZ - 1) == 0
              || getMaterial(iX + 1, iY - 1, iZ + 1) == 0
              || getMaterial(iX - 1, iY + 1, iZ + 1) == 0
              || getMaterial(iX - 1, iY - 1, iZ + 1) == 0
              || getMaterial(iX - 1, iY + 1, iZ - 1) == 0) {
            setMaterial(iX, iY, iZ, 0);
            counter++;
          }
        }
      }
    }
  }
  clout << "cleaned "<< counter << " outer fluid voxel(s)" << std::endl;
}


void SuperGeometry3D::innerClean() {
  int count = 0;
  int count2 = 0;

  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {
      for (int iZ = 0; iZ < _nz; iZ++) {

        if (getMaterial(iX, iY, iZ) != 1 && getMaterial(iX, iY, iZ) != 0) {
          count++;

          if (getMaterial(iX - 1, iY, iZ) == 1) {
            if (getMaterial(iX, iY + 1, iZ) == 1) {
              if (getMaterial(iX, iY - 1, iZ) == 1) {
                setMaterial(iX, iY, iZ, 1);
                count2++;
              }
            }
          }
          if (getMaterial(iX + 1, iY, iZ) == 1) {
            if (getMaterial(iX, iY + 1, iZ) == 1) {
              if (getMaterial(iX, iY - 1, iZ) == 1) {
                setMaterial(iX, iY, iZ, 1);
                count2++;
              }
            }
          }
          if (getMaterial(iX, iY + 1, iZ) == 1) {
            if (getMaterial(iX + 1, iY, iZ) == 1) {
              if (getMaterial(iX - 1, iY, iZ) == 1) {
                setMaterial(iX, iY, iZ, 1);
                count2++;
              }
            }
          }
          if (getMaterial(iX, iY - 1, iZ) == 1) {
            if (getMaterial(iX + 1, iY, iZ) == 1) {
              if (getMaterial(iX - 1, iY, iZ) == 1) {
                setMaterial(iX, iY, iZ, 1);
                count2++;
              }
            }
          }
        }
      }
    }
  }
  clout << "cleaned "<< count2 << " inner boundary voxel(s)" << std::endl;
}

void SuperGeometry3D::innerClean(int bcType) {
  int count = 0;
  int count2 = 0;

  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {
      for (int iZ = 0; iZ < _nz; iZ++) {

        if (getMaterial(iX, iY, iZ) != 1 && getMaterial(iX, iY, iZ)
            != 0 && getMaterial(iX, iY, iZ) == bcType) {
          count++;

          if (getMaterial(iX - 1, iY, iZ) == 1) {
            if (getMaterial(iX, iY + 1, iZ) == 1) {
              if (getMaterial(iX, iY - 1, iZ) == 1) {
                setMaterial(iX, iY, iZ, 1);
                count2++;
              }
            }
          }
          if (getMaterial(iX + 1, iY, iZ) == 1) {
            if (getMaterial(iX, iY + 1, iZ) == 1) {
              if (getMaterial(iX, iY - 1, iZ) == 1) {
                setMaterial(iX, iY, iZ, 1);
                count2++;
              }
            }
          }
          if (getMaterial(iX, iY + 1, iZ) == 1) {
            if (getMaterial(iX + 1, iY, iZ) == 1) {
              if (getMaterial(iX - 1, iY, iZ) == 1) {
                setMaterial(iX, iY, iZ, 1);
                count2++;
              }
            }
          }
          if (getMaterial(iX, iY - 1, iZ) == 1) {
            if (getMaterial(iX + 1, iY, iZ) == 1) {
              if (getMaterial(iX - 1, iY, iZ) == 1) {
                setMaterial(iX, iY, iZ, 1);
                count2++;
              }
            }
          }
        }
      }
    }
  }
  clout << "cleaned "<< count2
        << " inner boundary voxel(s) of Type " << bcType << std::endl;
}

void SuperGeometry3D::rename(unsigned short fromM, unsigned short toM) {

  for (int iX = -_offset; iX < _nx + _offset; iX++) {
    for (int iY = -_offset; iY < _ny + _offset; iY++) {
      for (int iZ = -_offset; iZ < _nz + _offset; iZ++) {
        if (getMaterial(iX, iY, iZ) == fromM)
        setMaterial(iX, iY, iZ, toM);
      }
    }
  }
}

void SuperGeometry3D::rename(unsigned short fromM, unsigned short toM, AnalyticalF3D<bool,double>& condition) {

  for (int iX = -_offset; iX < _nx + _offset; iX++) {
    for (int iY = -_offset; iY < _ny + _offset; iY++) {
      for (int iZ = -_offset; iZ < _nz + _offset; iZ++) {
        if (getMaterial(iX, iY, iZ) == fromM) {
          if(condition(physCoords(iX,iY,iZ))[0]) {
            setMaterial(iX, iY, iZ, toM);
            //if (getMaterial(iX+1, iY, iZ) == fromM) setMaterial(iX+1, iY, iZ, toM);
            //if (getMaterial(iX-1, iY, iZ) == fromM) setMaterial(iX-1, iY, iZ, toM);
            //if (getMaterial(iX, iY+1, iZ) == fromM) setMaterial(iX, iY+1, iZ, toM);
            //if (getMaterial(iX, iY-1, iZ) == fromM) setMaterial(iX, iY-1, iZ, toM);
            //if (getMaterial(iX, iY, iZ+1) == fromM) setMaterial(iX, iY, iZ+1, toM);
            //if (getMaterial(iX, iY, iZ-1) == fromM) setMaterial(iX, iY, iZ-1, toM);
          }
        }
      }
    }
  }
}

void SuperGeometry3D::rename(unsigned short fromM, unsigned short toM, unsigned offsetX, unsigned offsetY, unsigned offsetZ) {

  for (int iX = -_offset; iX < _nx + _offset; iX++) {
    for (int iY = -_offset; iY < _ny + _offset; iY++) {
      for (int iZ = -_offset; iZ < _nz + _offset; iZ++) {
        if (getMaterial(iX, iY, iZ) == fromM) {
          bool found = true;
          for (int iOffsetX = -offsetX; iOffsetX <= (int) offsetX; ++iOffsetX) {
            for (int iOffsetY = -offsetY; iOffsetY <= (int) offsetY; ++iOffsetY) {
              for (int iOffsetZ = -offsetZ; iOffsetZ <= (int) offsetZ; ++iOffsetZ) {
                if (getMaterial(iX + iOffsetX, iY + iOffsetY, iZ + iOffsetZ) != fromM) {
                  if (getMaterial(iX + iOffsetX, iY + iOffsetY, iZ + iOffsetZ) != 1245) {
                    found = false;
                  }
                }
              }
            }
          }
          if (found) {
            setMaterial(iX, iY, iZ, 1245);
          }
        }
      }
    }
  }
  rename(1245,toM);
}

void SuperGeometry3D::rename(unsigned short fromM, unsigned short toM, unsigned short testM, std::vector<int> testDirection) {
  for (int iX = -_offset; iX < _nx + _offset; iX++) {
    for (int iY = -_offset; iY < _ny + _offset; iY++) {
      for (int iZ = -_offset; iZ < _nz + _offset; iZ++) {
        if (getMaterial(iX, iY, iZ) == fromM) {

          // flag that indicates the renaming of the current voxel, valid voxels are not renamed
          bool isValid = true;
          for (int iOffsetX = std::min(testDirection[0],0); iOffsetX <= std::max(testDirection[0],0); ++iOffsetX) {
            for (int iOffsetY = std::min(testDirection[1],0); iOffsetY <= std::max(testDirection[1],0); ++iOffsetY) {
              for (int iOffsetZ = std::min(testDirection[2],0); iOffsetZ <= std::max(testDirection[2],0); ++iOffsetZ) {
                if (iOffsetX!=0 || iOffsetY!=0 || iOffsetZ!=0) {
                  if (getMaterial(iX + iOffsetX, iY + iOffsetY, iZ + iOffsetZ) != testM) {
                    isValid = false;
                  }
                }
              }
            }
          }

          if (!isValid) {
            setMaterial(iX, iY, iZ, toM);
          }

        }
      }
    }
  }
}


bool SuperGeometry3D::check(unsigned short material, int iX, int iY,
                                      int iZ, unsigned offsetX, unsigned offsetY, unsigned offsetZ) {

  bool found = true;
  for (int iOffsetX = -offsetX; iOffsetX <= (int) offsetX; ++iOffsetX) {
    for (int iOffsetY = -offsetY; iOffsetY <= (int) offsetY; ++iOffsetY) {
      for (int iOffsetZ = -offsetZ; iOffsetZ <= (int) offsetZ; ++iOffsetZ) {
        if (getMaterial(iX + iOffsetX, iY + iOffsetY,
                                        iZ + iOffsetZ) != material)
          found = false;
      }
    }
  }
  return found;
}

bool SuperGeometry3D::find(unsigned short material, unsigned offsetX,
                                     unsigned offsetY, unsigned offsetZ, int& foundX, int& foundY,
                                     int& foundZ) {

  bool found = false;
  for (foundX = 0; foundX < _nx; foundX++) {
    for (foundY = 0; foundY < _ny; foundY++) {
      for (foundZ = 0; foundZ < _nz; foundZ++) {
        found = check(material, foundX, foundY, foundZ, offsetX,
                      offsetY, offsetZ);
        if (found)
          return found;
      }
    }
  }
  return found;
}

/**
performs a region growing that marks all voxels that belong to the same connected region
 of material Number fromM outgoing from seed point (seedX,seedY,seedZ) with material Number toM. Search directions for the region growing algorithm are activated with searchX, searchY, searchZ, e.g. (true,true,false) for a search only in the x-y-Plane.
 */

void SuperGeometry3D::regionGrowing(unsigned short fromM, unsigned short toM,
    int seedX, int seedY, int seedZ, bool searchX, bool searchY, bool searchZ,
    std::map<std::vector<int>, int>* tmp) {

  std::map<std::vector<int>, int> tmp2;
  bool firstCall = false;
  if (tmp == NULL) {
    tmp = &tmp2;
    firstCall = true;
  }

  if (getMaterial(seedX, seedY, seedZ) == fromM) {
    std::vector<int> found;
    found.push_back(seedX);
    found.push_back(seedY);
    found.push_back(seedZ);
    if (tmp->count(found) == 0) {
      (*tmp)[found] = 2;
      if (searchX != 0) {
        regionGrowing(fromM, toM, seedX + 1, seedY, seedZ, searchX,
                      searchY, searchZ, tmp);
        regionGrowing(fromM, toM, seedX - 1, seedY, seedZ, searchX,
                      searchY, searchZ, tmp);
      }
      if (searchY != 0) {
        regionGrowing(fromM, toM, seedX, seedY + 1, seedZ, searchX,
                      searchY, searchZ, tmp);
        regionGrowing(fromM, toM, seedX, seedY - 1, seedZ, searchX,
                      searchY, searchZ, tmp);
      }
      if (searchZ != 0) {
        regionGrowing(fromM, toM, seedX, seedY, seedZ + 1, searchX,
                      searchY, searchZ, tmp);
        regionGrowing(fromM, toM, seedX, seedY, seedZ - 1, searchX,
                      searchY, searchZ, tmp);
      }
    }
  }
  if (firstCall) {
    std::map<std::vector<int>, int>::iterator iter;
    for (iter = tmp->begin(); iter != tmp->end(); iter++) {
      setMaterial((iter->first)[0],(iter->first)[1],(iter->first)[2],toM);
     }
  }
  return;
}




void SuperGeometry3D::checkForErrors() {
  bool Error = false;

  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {
      for (int iZ = 0; iZ < _nz; iZ++) {
        if (getMaterial(iX, iY, iZ) == 0) {
          if (   getMaterial(iX - 1, iY,     iZ    ) == 1
              || getMaterial(iX,     iY - 1, iZ    ) == 1
              || getMaterial(iX,     iY,     iZ - 1) == 1
              || getMaterial(iX - 1, iY - 1, iZ    ) == 1
              || getMaterial(iX,     iY - 1, iZ - 1) == 1
              || getMaterial(iX - 1, iY,     iZ - 1) == 1
              || getMaterial(iX - 1, iY - 1, iZ - 1) == 1
              || getMaterial(iX + 1, iY,     iZ    ) == 1
              || getMaterial(iX,     iY + 1, iZ    ) == 1
              || getMaterial(iX,     iY,     iZ + 1) == 1
              || getMaterial(iX + 1, iY + 1, iZ    ) == 1
              || getMaterial(iX,     iY + 1, iZ + 1) == 1
              || getMaterial(iX + 1, iY,     iZ + 1) == 1
              || getMaterial(iX + 1, iY + 1, iZ + 1) == 1
              || getMaterial(iX - 1, iY + 1, iZ    ) == 1
              || getMaterial(iX + 1, iY - 1, iZ    ) == 1
              || getMaterial(iX,     iY - 1, iZ + 1) == 1
              || getMaterial(iX,     iY + 1, iZ - 1) == 1
              || getMaterial(iX - 1, iY,     iZ + 1) == 1
              || getMaterial(iX + 1, iY,     iZ - 1) == 1
              || getMaterial(iX + 1, iY + 1, iZ - 1) == 1
              || getMaterial(iX + 1, iY - 1, iZ - 1) == 1
              || getMaterial(iX + 1, iY - 1, iZ + 1) == 1
              || getMaterial(iX - 1, iY + 1, iZ + 1) == 1
              || getMaterial(iX - 1, iY - 1, iZ + 1) == 1
              || getMaterial(iX - 1, iY + 1, iZ - 1) == 1) {
            Error = true;
          }
        }
      }
    }
  }

  if (Error == true) {
    clout << "error!" << std::endl;
  } else {
    clout << "the model is correct!" << std::endl;
  }
}

void SuperGeometry3D::refineMesh(int level) {

  // new number of Voxels in X-,Y-,and Z-direction and new spacing

  int _nXnew = level * _nx;
  int _nYnew = level * _ny;
  int _nZnew = level * _nz;
  double _hnew = _h / ((double) level);

  olb::ScalarField3D<unsigned short> _refinedGeometryData(_nXnew, _nYnew,
      _nZnew);
  _refinedGeometryData.construct();

  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {
      for (int iZ = 0; iZ < _nz; iZ++) {
        for (int li = 0; li < level; li++) {
          for (int lj = 0; lj < level; lj++) {
            for (int lk = 0; lk < level; lk++) {

              _refinedGeometryData.get(level * iX + li, level
                                       * iY + lj, level * iZ + lk) = getMaterial(
                                             iX, iY, iZ);

            }
          }
        }
      }
    }
  }

  for (int iX = 0; iX < _nXnew; iX++) {
    for (int iY = 0; iY < _nYnew; iY++) {
      for (int iZ = 0; iZ < _nZnew; iZ++) {

        if (iX == 0 || iY == 0 || iZ == 0 || iX == _nXnew - 1 || iY
            == _nYnew - 1 || iZ == _nZnew - 1)
          _refinedGeometryData.get(iX, iY, iZ) = 0;
      }
    }
  }

  reInit(_x0, _y0, _z0, _hnew, _nXnew - 2, _nYnew - 2, _nZnew - 2, 1,
         &_refinedGeometryData);
}

void SuperGeometry3D::addOffset(int offset) {

  int _nXnew = _nx + 2 * offset;
  int _nYnew = _ny + 2 * offset;
  int _nZnew = _nz + 2 * offset;

  olb::ScalarField3D<unsigned short>* _geometryDataOffset;
  _geometryDataOffset = NULL;
  _geometryDataOffset = new olb::ScalarField3D<unsigned short>(_nXnew,
      _nYnew, _nZnew);
  _geometryDataOffset->construct();

  for (int iX = 0; iX < _nXnew; iX++) {
    for (int iY = 0; iY < _nYnew; iY++) {
      for (int iZ = 0; iZ < _nZnew; iZ++) {
        _geometryDataOffset->get(iX, iY, iZ) = 0;
      }
    }
  }
  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {
      for (int iZ = 0; iZ < _nz; iZ++) {

        _geometryDataOffset->get(iX + offset, iY + offset, iZ + offset)
        = _geometryData.get(iX, iY, iZ);

      }
    }
  }

  reInit(_x0, _y0, _z0, _h, _nXnew, _nYnew, _nZnew, _offset + offset,
         _geometryDataOffset);
}

void SuperGeometry3D::removeOffset() {
  int _nXnew = _nx - 2 * _offset;
  int _nYnew = _ny - 2 * _offset;
  int _nZnew = _nz - 2 * _offset;

  olb::ScalarField3D<unsigned short>* _geometryDataNoOffset;
  _geometryDataNoOffset = NULL;
  _geometryDataNoOffset = new olb::ScalarField3D<unsigned short>(_nXnew,
      _nYnew, _nZnew);
  _geometryDataNoOffset->construct();

  for (int iX = 0; iX < _nXnew; iX++) {
    for (int iY = 0; iY < _nYnew; iY++) {
      for (int iZ = 0; iZ < _nZnew; iZ++) {
        _geometryDataNoOffset->get(iX, iY, iZ) = 0;
      }
    }
  }

  for (int iX = _offset; iX < _nx - _offset; iX++) {
    for (int iY = _offset; iY < _ny - _offset; iY++) {
      for (int iZ = _offset; iZ < _nz - _offset; iZ++) {
        _geometryDataNoOffset->get(iX - _offset, iY - _offset, iZ
                                   - _offset) = _geometryData.get(iX, iY, iZ);
      }
    }
  }
  reInit(_x0, _y0, _z0, _h, _nXnew, _nYnew, _nZnew, 0, _geometryDataNoOffset);
}

void SuperGeometry3D::printLayer(int x0, int x1, int y0, int y1, int z0,
                                 int z1, bool linenumber) {
  for (int x = x0; x <= x1; x++) {
    if (linenumber)
      clout << x << ": ";
    for (int y = y0; y <= y1; y++) {
      for (int z = z0; z <= z1; z++) {
        clout << getMaterial(x, y, z) << " ";
      }
      if (y1 - y0 != 0 && z1 - z0 != 0)
        clout << std::endl;
    }
    if (x1 - x0 != 0)
      clout << std::endl;
  }
  clout << std::endl;
}

void SuperGeometry3D::printLayer(int direction, int layer, bool linenumber) {
  assert(direction >= 0 && direction <= 2);
  switch (direction) {
  case 0:
    printLayer(layer, layer, 0, getNy() - 1, 0, getNz() - 1, linenumber);
    break;
  case 1:
    printLayer(0, getNx() - 1, layer, layer, 0, getNz() - 1, linenumber);
    break;
  case 2:
    printLayer(0, getNx() - 1, 0, getNy() - 1, layer, layer, linenumber);
    break;
  }
}

void SuperGeometry3D::printNode(int x0, int y0, int z0) {
  for (int x = x0 - 1; x <= x0 + 1; x++) {
    clout << "x=" << x << std::endl;
    for (int y = y0 - 1; y <= y0 + 1; y++) {
      for (int z = z0 - 1; z <= z0 + 1; z++) {
        clout << getMaterial(x, y, z) << " ";
      }
      clout << std::endl;
    }
    clout << std::endl;
  }
  clout << std::endl;
}

void SuperGeometry3D::writeVti(std::string file) {

  olb::VtkImageOutput3D<double> vtkOut(file, _h, _x0-_offset*_h, _y0-_offset*_h, _z0-_offset*_h);
  vtkOut.writeData<unsigned short,unsigned short>(_geometryData, "geometry");
  clout << "wrote vti-File" << std::endl;
}

std::vector<double> SuperGeometry3D::physCoords(std::vector<int> coords) {
  std::vector<double> result(3,0.);
  result[0] = physCoordX(coords[0]);
  result[1] = physCoordY(coords[1]);
  result[2] = physCoordZ(coords[2]);
  return result;
}

std::vector<double> SuperGeometry3D::physCoords(std::vector<double> coords) {
  std::vector<double> result(3,0.);
  result[0] = physCoordX(coords[0]);
  result[1] = physCoordY(coords[1]);
  result[2] = physCoordZ(coords[2]);
  return result;
}

std::vector<double> SuperGeometry3D::physCoords(int iX, int iY, int iZ) {
  std::vector<double> result(3,0.);
  result[0] = physCoordX(iX);
  result[1] = physCoordY(iY);
  result[2] = physCoordZ(iZ);
  return result;
}

double SuperGeometry3D::physCoordX(int iX) {
  return iX*_h + _x0;
}

double SuperGeometry3D::physCoordY(int iY) {
  return iY*_h + _y0;
}

double SuperGeometry3D::physCoordZ(int iZ) {
  return iZ*_h + _z0;
}

} // namespace olb
