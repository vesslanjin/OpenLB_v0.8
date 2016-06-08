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
 * Representation of the 2D geometry -- implementation.
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
#include "superGeometry2D.h"
#include "core/dataFields2D.h"
#include "core/dataFields2D.hh"
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

double SuperGeometry2D::getPositionX() {
  return _x0;
}

void SuperGeometry2D::setPositionX(double x0) {
  _x0 = x0;
}

double SuperGeometry2D::getPositionY() {
  return _y0;
}

void SuperGeometry2D::setPositionY(double y0) {
  _y0 = y0;
}

double SuperGeometry2D::getSpacing() {
  return _h;
}

void SuperGeometry2D::setSpacing(double h) {
  _h = h;
}

int SuperGeometry2D::getOffset() {
  return _offset;
}
;

void SuperGeometry2D::setOffset(int offset) {
  _offset = offset;
}

int SuperGeometry2D::getNx() {
  return _nx;
}

void SuperGeometry2D::setNx(int nX) {
  _nx = nX;
}

int SuperGeometry2D::getNy() {
  return _ny;
}

void SuperGeometry2D::setNy(int nY) {
  _ny = nY;
}
;


void SuperGeometry2D::reInit(double x0, double y0, double h, int nX,
                             int nY, int offset,
                             olb::ScalarField2D<unsigned short>* geometryData) {

  setPositionX(x0);
  setPositionY(y0);

  setSpacing(h);

  setNx(nX);
  setNy(nY);

  setOffset(offset);

  if (geometryData != NULL) {
    _geometryData.swap(*geometryData);
  }
  else {
    olb::ScalarField2D<unsigned short> geometryDataTemp(nX + 2 * offset, nY + 2 * offset);
    _geometryData.swap(geometryDataTemp);
    _geometryData.construct();
    _geometryData.reset();
    geometryDataTemp.deConstruct();
  }
}

unsigned short SuperGeometry2D::getMaterial(int iX, int iY) {
  unsigned short material;
  if (iX + _offset < 0 || iX + 1 > _nx + _offset || iY + _offset < 0 || iY
      + 1 > _ny + _offset)
    material = 0;
  else
    material = _geometryData.get(iX + _offset, iY + _offset);
  return material;
}

void SuperGeometry2D::setMaterial(int iX, int iY,
                                  unsigned short material) {
  _geometryData.get(iX + _offset, iY + _offset) = material;
  _statisticsUpdateNeeded = true;
}

olb::ScalarField2D<unsigned short>* SuperGeometry2D::getRawData() {
  return &_geometryData;
}

/// new Functions

void SuperGeometry2D::clean() {
  int counter=0;
  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {
        if (getMaterial(iX, iY) != 1 && getMaterial(iX, iY)
            != 0) {

          if (getMaterial(iX - 1, iY) != 1
            && getMaterial(iX, iY - 1) != 1
            && getMaterial(iX - 1, iY - 1) != 1
            && getMaterial(iX + 1, iY) != 1
            && getMaterial(iX, iY + 1) != 1
            && getMaterial(iX + 1, iY + 1) != 1
            && getMaterial(iX - 1, iY + 1) != 1
            && getMaterial(iX + 1, iY - 1) != 1) {
            setMaterial(iX, iY, 0);
            counter++;
          }
        }
      }
  }
  clout << "cleaned "<< counter << " outer boundary voxel(s)" << std::endl;
}

void SuperGeometry2D::outerClean() {
  int counter=0;
  for (int iX = -_offset; iX < _nx + _offset; iX++) {
    for (int iY = -_offset; iY < _ny + _offset; iY++) {
        if (getMaterial(iX, iY) == 1) {
          if (   getMaterial(iX - 1, iY    ) == 0
              || getMaterial(iX,     iY - 1) == 0
              || getMaterial(iX - 1, iY - 1) == 0
              || getMaterial(iX + 1, iY    ) == 0
              || getMaterial(iX,     iY + 1) == 0
              || getMaterial(iX + 1, iY + 1) == 0
              || getMaterial(iX - 1, iY + 1) == 0
              || getMaterial(iX + 1, iY - 1) == 0) {
            setMaterial(iX, iY, 0);
            counter++;
          }
      }
    }
  }
  clout << "cleaned "<< counter << " outer fluid voxel(s)" << std::endl;
}


void SuperGeometry2D::innerClean() {
  int count = 0;
  int count2 = 0;

  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {

    	if (getMaterial(iX, iY) != 1 && getMaterial(iX, iY) != 0) {
          count++;

          if (getMaterial(iX - 1, iY) == 1) {
            if (getMaterial(iX, iY + 1) == 1) {
              if (getMaterial(iX, iY - 1) == 1) {
                setMaterial(iX, iY, 1);
                count2++;
              }
            }
          }
          if (getMaterial(iX + 1, iY) == 1) {
            if (getMaterial(iX, iY + 1) == 1) {
              if (getMaterial(iX, iY - 1) == 1) {
                setMaterial(iX, iY, 1);
                count2++;
              }
            }
          }
          if (getMaterial(iX, iY + 1) == 1) {
            if (getMaterial(iX + 1, iY) == 1) {
              if (getMaterial(iX - 1, iY) == 1) {
                setMaterial(iX, iY, 1);
                count2++;
              }
            }
          }
          if (getMaterial(iX, iY - 1) == 1) {
            if (getMaterial(iX + 1, iY) == 1) {
              if (getMaterial(iX - 1, iY) == 1) {
                setMaterial(iX, iY, 1);
                count2++;
              }
            }
          }
      }
    }
  }
  clout << "cleaned "<< count2 << " inner boundary voxel(s)" << std::endl;
}

void SuperGeometry2D::innerClean(int bcType) {
  int count = 0;
  int count2 = 0;

  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {
        if (getMaterial(iX, iY) != 1 && getMaterial(iX, iY)
            != 0 && getMaterial(iX, iY) == bcType) {
          count++;

          if (getMaterial(iX - 1, iY) == 1) {
            if (getMaterial(iX, iY + 1) == 1) {
              if (getMaterial(iX, iY - 1) == 1) {
                setMaterial(iX, iY, 1);
                count2++;
              }
            }
          }
          if (getMaterial(iX + 1, iY) == 1) {
            if (getMaterial(iX, iY + 1) == 1) {
              if (getMaterial(iX, iY - 1) == 1) {
                setMaterial(iX, iY, 1);
                count2++;
              }
            }
          }
          if (getMaterial(iX, iY + 1) == 1) {
            if (getMaterial(iX + 1, iY) == 1) {
              if (getMaterial(iX - 1, iY) == 1) {
                setMaterial(iX, iY, 1);
                count2++;
              }
            }
          }
          if (getMaterial(iX, iY - 1) == 1) {
            if (getMaterial(iX + 1, iY) == 1) {
              if (getMaterial(iX - 1, iY) == 1) {
                setMaterial(iX, iY, 1);
                count2++;
              }
            }
          }
      }
    }
  }
  clout << "cleaned "<< count2
        << " inner boundary voxel(s) of Type " << bcType << std::endl;
}

void SuperGeometry2D::rename(unsigned short fromM, unsigned short toM) {

  for (int iX = 0; iX < _nx + 2*_offset; iX++) {
    for (int iY = 0; iY < _ny + 2*_offset; iY++) {
        if (_geometryData.get(iX, iY) == fromM)
          _geometryData.get(iX, iY) = toM;
      }
  }
}

void SuperGeometry2D::rename(unsigned short fromM, unsigned short toM, AnalyticalF2D<double,bool>& condition) {

  for (int iX = 0; iX < _nx + 2*_offset; iX++) {
    for (int iY = 0; iY < _ny + 2*_offset; iY++) {
        if (_geometryData.get(iX, iY) == fromM && condition(physCoords(iX-_offset,iY-_offset))[0] ) {
          _geometryData.get(iX, iY) = toM;
        }
    }
  }
}

void SuperGeometry2D::rename(unsigned short fromM, unsigned short toM, unsigned offsetX, unsigned offsetY, unsigned offsetZ) {

  for (int iX = 0; iX < _nx + 2*_offset; iX++) {
    for (int iY = 0; iY < _ny + 2*_offset; iY++) {
        if (getMaterial(iX, iY) == fromM) {
          bool found = true;
          for (int iOffsetX = -offsetX; iOffsetX <= (int) offsetX; ++iOffsetX) {
            for (int iOffsetY = -offsetY; iOffsetY <= (int) offsetY; ++iOffsetY) {
                if (getMaterial(iX + iOffsetX, iY + iOffsetY) != fromM) {
                  if (getMaterial(iX + iOffsetX, iY + iOffsetY) != 1245) {
                    found = false;
                  }
                }
            }
          }
          if (found) {
            setMaterial(iX, iY, 1245);
          }
        }
    }
  }
  rename(1245,toM);
}


bool SuperGeometry2D::check(unsigned short material, int iX, int iY, unsigned offsetX, unsigned offsetY) {

  bool found = true;
  for (int iOffsetX = -offsetX; iOffsetX <= (int) offsetX; ++iOffsetX) {
    for (int iOffsetY = -offsetY; iOffsetY <= (int) offsetY; ++iOffsetY) {
        if (getMaterial(iX + iOffsetX, iY + iOffsetY) != material)
          found = false;
    }
  }
  return found;
}

bool SuperGeometry2D::find(unsigned short material, unsigned offsetX,
                                     unsigned offsetY, int& foundX, int& foundY) {

  bool found = false;
  for (foundX = 0; foundX < _nx; foundX++) {
    for (foundY = 0; foundY < _ny; foundY++) {
        found = check(material, foundX, foundY, offsetX,
                      offsetY);
        if (found)
          return found;
    }
  }
  return found;
}

void SuperGeometry2D::regionGrowing(unsigned short fromM, unsigned short toM,
    int seedX, int seedY, int offsetX, int offsetY,
    std::map<std::vector<int>, int>* tmp) {

  std::map<std::vector<int>, int> tmp2;
  bool firstCall = false;
  if (tmp == NULL) {
    tmp = &tmp2;
    firstCall = true;
  }

  if (getMaterial(seedX, seedY) == fromM) {
    std::vector<int> found;
    found.push_back(seedX);
    found.push_back(seedY);
    if (tmp->count(found) == 0) {
      (*tmp)[found] = 2;
      if (offsetX != 0) {
        regionGrowing(fromM, toM, seedX + 1, seedY, offsetX,
                      offsetY,  tmp);
        regionGrowing(fromM, toM, seedX - 1, seedY, offsetX,
                      offsetY,  tmp);
      }
      if (offsetY != 0) {
        regionGrowing(fromM, toM, seedX, seedY + 1,  offsetX,
                      offsetY, tmp);
        regionGrowing(fromM, toM, seedX, seedY - 1,  offsetX,
                      offsetY, tmp);
      }
    }
  }
  if (firstCall) {
    std::map<std::vector<int>, int>::iterator iter;
    for (iter = tmp->begin(); iter != tmp->end(); iter++) {
      setMaterial((iter->first)[0],(iter->first)[1],toM);
     }
  }
  return;
}




void SuperGeometry2D::checkForErrors() {
  bool Error = false;

  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {
        if (getMaterial(iX, iY) == 0) {
          if (   getMaterial(iX - 1, iY    ) == 1
              || getMaterial(iX,     iY - 1) == 1
              || getMaterial(iX - 1, iY - 1) == 1
              || getMaterial(iX + 1, iY    ) == 1
              || getMaterial(iX,     iY + 1) == 1
              || getMaterial(iX + 1, iY + 1) == 1
              || getMaterial(iX - 1, iY + 1) == 1
              || getMaterial(iX + 1, iY - 1) == 1) {
            Error = true;
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

void SuperGeometry2D::refineMesh(int level) {

  // new number of Voxels in X-,Y-,and Z-direction and new spacing

  int _nXnew = level * _nx;
  int _nYnew = level * _ny;
  double _hnew = _h / ((double) level);

  olb::ScalarField2D<unsigned short> _refinedGeometryData(_nXnew, _nYnew);
  _refinedGeometryData.construct();

  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {
        for (int li = 0; li < level; li++) {
          for (int lj = 0; lj < level; lj++) {
              _refinedGeometryData.get(level * iX + li, level
                                       * iY + lj) = getMaterial(
                                             iX, iY);
          }
        }
    }
  }

  for (int iX = 0; iX < _nXnew; iX++) {
    for (int iY = 0; iY < _nYnew; iY++) {
        if (iX == 0 || iY == 0 || iX == _nXnew - 1 || iY
            == _nYnew - 1)
          _refinedGeometryData.get(iX, iY) = 0;
    }
  }

  reInit(_x0, _y0, _hnew, _nXnew - 2, _nYnew - 2, 1, &_refinedGeometryData);
}

void SuperGeometry2D::addOffset(int offset) {

  int _nXnew = _nx + 2 * offset;
  int _nYnew = _ny + 2 * offset;

  olb::ScalarField2D<unsigned short>* _geometryDataOffset;
  _geometryDataOffset = NULL;
  _geometryDataOffset = new olb::ScalarField2D<unsigned short>(_nXnew,
      _nYnew);
  _geometryDataOffset->construct();

  for (int iX = 0; iX < _nXnew; iX++) {
    for (int iY = 0; iY < _nYnew; iY++) {
        _geometryDataOffset->get(iX, iY) = 0;
    }
  }
  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {
     _geometryDataOffset->get(iX + offset, iY + offset)
     = _geometryData.get(iX, iY);
    }
  }

  reInit(_x0, _y0, _h, _nXnew, _nYnew, _offset + offset,
         _geometryDataOffset);
}

void SuperGeometry2D::removeOffset() {
  int _nXnew = _nx - 2 * _offset;
  int _nYnew = _ny - 2 * _offset;

  olb::ScalarField2D<unsigned short>* _geometryDataNoOffset;
  _geometryDataNoOffset = NULL;
  _geometryDataNoOffset = new olb::ScalarField2D<unsigned short>(_nXnew,
      _nYnew);
  _geometryDataNoOffset->construct();

  for (int iX = 0; iX < _nXnew; iX++) {
    for (int iY = 0; iY < _nYnew; iY++) {
        _geometryDataNoOffset->get(iX, iY) = 0;
    }
  }

  for (int iX = _offset; iX < _nx - _offset; iX++) {
    for (int iY = _offset; iY < _ny - _offset; iY++) {
      _geometryDataNoOffset->get(iX - _offset, iY - _offset) = _geometryData.get(iX, iY);
    }
  }
  reInit(_x0, _y0, _h, _nXnew, _nYnew, 0, _geometryDataNoOffset);
}

void SuperGeometry2D::printLayer(int x0, int x1, int y0, int y1, bool linenumber) {
  for (int x = x0; x <= x1; x++) {
    if (linenumber)
      clout << x << ": ";
    for (int y = y0; y <= y1; y++) {
        clout << getMaterial(x, y) << " ";
      if (y1 - y0 != 0)
        clout << std::endl;
    }
    if (x1 - x0 != 0)
      clout << std::endl;
  }
  clout << std::endl;
}

void SuperGeometry2D::printLayer(int direction, int layer, bool linenumber) {
  assert(direction >= 0 && direction <= 2);
  switch (direction) {
  case 0:
    printLayer(layer, layer, 0, getNy() - 1, linenumber);
    break;
  case 1:
    printLayer(0, getNx() - 1, layer, layer, linenumber);
    break;
  }
}

void SuperGeometry2D::printNode(int x0, int y0) {
  for (int x = x0 - 1; x <= x0 + 1; x++) {
    clout << "x=" << x << std::endl;
    for (int y = y0 - 1; y <= y0 + 1; y++) {
        clout << getMaterial(x, y) << " ";
    }
    clout << std::endl;
  }
  clout << std::endl;
}

void SuperGeometry2D::writeVti(std::string file) {

  olb::VtkImageOutput2D<double> vtkOut(file, _h, _x0-_offset*_h, _y0-_offset*_h);
  vtkOut.writeData<unsigned short,unsigned short>(_geometryData, "geometry");
  clout << "wrote vti-File" << std::endl;
}

std::vector<double> SuperGeometry2D::physCoords(std::vector<int> coords) {
  std::vector<double> result(3,0.);
  result[0] = physCoordX(coords[0]);
  result[1] = physCoordY(coords[1]);
  return result;
}

std::vector<double> SuperGeometry2D::physCoords(std::vector<double> coords) {
  std::vector<double> result(3,0.);
  result[0] = physCoordX(coords[0]);
  result[1] = physCoordY(coords[1]);
  return result;
}

std::vector<double> SuperGeometry2D::physCoords(int iX, int iY) {
  std::vector<double> result(3,0.);
  result[0] = physCoordX(iX);
  result[1] = physCoordY(iY);
  return result;
}

double SuperGeometry2D::physCoordX(int iX) {
  return iX*_h + _x0;
}

double SuperGeometry2D::physCoordY(int iY) {
  return iY*_h + _y0;
}

} // namespace olb
