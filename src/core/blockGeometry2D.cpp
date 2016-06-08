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
 * Representation of the 3D geometry -- implementation.
 */

#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>
#include <cmath>

#include "io/vtkDataOutput.h"
#include "io/vtkDataOutput.hh"
#include "blockGeometry2D.h"
#include "../src/core/dataFields3D.h"
#include "../src/core/dataFields3D.hh"
#include "../src/core/dataFields2D.h"
#include "../src/core/dataFields2D.hh"
#include "../src/core/serializer.h"
#include "../src/core/serializer.hh"
#include "../src/io/serializerIO.h"
#include "../src/io/serializerIO.hh"
#include "../src/io/base64.h"
#include "../src/io/base64.hh"

namespace olb {

double BlockGeometry2D::getPositionX() {
  return _x0;
}

void BlockGeometry2D::setPositionX(double x0) {
  _x0 = x0;
}

double BlockGeometry2D::getPositionY() {
  return _y0;
}

void BlockGeometry2D::setPositionY(double y0) {
  _y0 = y0;
}

double BlockGeometry2D::getSpacing() {
  return _h;
}

void BlockGeometry2D::setSpacing(double h) {
  _h = h;
}

int BlockGeometry2D::getOffset() {
  return _offset;
}
;

void BlockGeometry2D::setOffset(int offset) {
  _offset = offset;
}

int BlockGeometry2D::getNx() {
  return _nx;
}

void BlockGeometry2D::setNx(int nX) {
  _nx = nX;
}

int BlockGeometry2D::getNy() {
  return _ny;
}

void BlockGeometry2D::setNy(int nY) {
  _ny = nY;
}
;

void BlockGeometry2D::reInit(double x0, double y0, double h, int nX, int nY,
                             int offset, olb::ScalarField2D<unsigned short>* geometryData) {

  setPositionX(x0);
  setPositionY(y0);

  setSpacing(h);

  setNx(nX);
  setNy(nY);

  setOffset(offset);

  if (geometryData != NULL) {
    _geometryData.swap(*geometryData);
  } else {
    olb::ScalarField2D<unsigned short> geometryDataTemp(nX + 2 * offset, nY + 2 * offset);
    _geometryData.swap(geometryDataTemp);
    _geometryData.construct();
    _geometryData.reset();
    geometryDataTemp.deConstruct();
  }
}

unsigned short BlockGeometry2D::getMaterial(int iX, int iY) {
  unsigned short material;
  if (iX + _offset < 0 || iX + 1 > _nx + _offset || iY + _offset < 0 || iY
      + 1 > _ny + _offset)
    material = 0;
  else
    material = _geometryData.get(iX + _offset, iY + _offset);
  return material;
}

void BlockGeometry2D::setMaterial(int iX, int iY, unsigned short material) {
  _geometryData.get(iX + _offset, iY + _offset) = material;
}

olb::ScalarField2D<unsigned short>* BlockGeometry2D::getRawData() {
  return &_geometryData;
}

/// new Functions

void BlockGeometry2D::clean() {
  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {

      if (getMaterial(iX, iY) != 1 && getMaterial(iX, iY) != 0) {

        if (getMaterial(iX - 1, iY) != 1 && getMaterial(iX, iY - 1)
            != 1 && getMaterial(iX + 1, iY) != 1 && getMaterial(iX,
                iY + 1) != 1 && getMaterial(iX - 1, iY - 1) != 1
            && getMaterial(iX - 1, iY + 1) != 1 && getMaterial(iX
                + 1, iY - 1) != 1 && getMaterial(iX + 1, iY + 1) != 1) {

          setMaterial(iX, iY, 0);

        }
      }
    }
  }
  clout << "cleaned" << std::endl;
}

void BlockGeometry2D::innerClean() {
  int count = 0;
  int count2 = 0;

  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {

      if (getMaterial(iX, iY) != 1 && getMaterial(iX, iY) != 0) {
        count++;

        if (getMaterial(iX - 1, iY) == 1) {
          if (getMaterial(iX + 1, iY) == 1) {
            setMaterial(iX, iY, 1);
            count2++;
          }
        }
        if (getMaterial(iX, iY - 1) == 1) {
          if (getMaterial(iX, iY + 1) == 1) {
            setMaterial(iX, iY, 1);
            count2++;
          }
        }
      }
    }
  }
  clout << "cleaned "<< count2 << " inner boundary voxel(s)" << std::endl;
}

void BlockGeometry2D::rename(unsigned short fromM, unsigned short toM) {

  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {
      if (getMaterial(iX, iY) == fromM)
        setMaterial(iX, iY, toM);
    }
  }
}

void BlockGeometry2D::checkForErrors() {
  bool Error = false;

  for (int iX = 0; iX < _nx; iX++) {
    for (int iY = 0; iY < _ny; iY++) {

      if (getMaterial(iX, iY) == 0) {

        if (getMaterial(iX - 1, iY) == 1 || getMaterial(iX, iY - 1)
            == 1 || getMaterial(iX + 1, iY) == 1 || getMaterial(iX,
                iY + 1) == 1 || getMaterial(iX - 1, iY - 1) == 1
            || getMaterial(iX + 1, iY - 1) == 1 || getMaterial(iX
                + 1, iY - 1) == 1 || getMaterial(iX + 1, iY + 1) == 1) {

          Error = true;

        }
      }
    }
  }

  if (Error == true) {
    clout << "Error: from function checkForErrors()!" << std::endl;
  } else {
    clout << "the model is correct!" << std::endl;
  }
}

void BlockGeometry2D::refineMesh(int level) {

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

          _refinedGeometryData.get(level * iX + li, level * iY + lj)
          = getMaterial(iX, iY);

        }
      }
    }
  }

  for (int iX = 0; iX < _nXnew; iX++) {
    for (int iY = 0; iY < _nYnew; iY++) {

      if (iX == 0 || iY == 0 || iX == _nXnew - 1 || iY == _nYnew - 1)
        _refinedGeometryData.get(iX, iY) = 0;
    }
  }

  reInit(_x0, _y0, _hnew, _nXnew - 2, _nYnew - 2, 1, &_refinedGeometryData);
}

void BlockGeometry2D::addOffset(int offset) {

  int _nXnew = _nx + 2 * offset;
  int _nYnew = _ny + 2 * offset;

  olb::ScalarField2D<unsigned short>* _geometryDataOffset;
  _geometryDataOffset = NULL;
  _geometryDataOffset
  = new olb::ScalarField2D<unsigned short>(_nXnew, _nYnew);
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

  reInit(_x0, _y0, _h, _nXnew, _nYnew, _offset + offset, _geometryDataOffset);
}

void BlockGeometry2D::removeOffset() {
  int _nXnew = _nx - 2 * _offset;
  int _nYnew = _ny - 2 * _offset;

  clout << _nXnew << " " << _nYnew << std::endl;

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
      _geometryDataNoOffset->get(iX - _offset, iY - _offset)
      = _geometryData.get(iX, iY);
    }
  }
  reInit(_x0, _y0, _h, _nXnew, _nYnew, 0, _geometryDataNoOffset);
}

void BlockGeometry2D::print() {
  for (int i = 0; i< _nx; i++) {
    for (int j = 0; j<  _ny; j++) {
      clout << getMaterial(i, j) << " ";
    }
    clout << std::endl;
  }
}

void BlockGeometry2D::printNode(int x0, int y0) {
  for (int i = x0-1; i<=x0+1 ; i++) {
    for (int j = y0-1; j<=y0+1; j++) {
      clout << getMaterial(i, j) << " ";
    }
    clout << std::endl;
  }
}

void BlockGeometry2D::writeVti(std::string file) {

  olb::VtkImageOutput2D<double> vtkOut(file, _h, _x0-_offset*_h, _y0-_offset*_h);
  vtkOut.writeData<unsigned short,unsigned short>(_geometryData, "geometry");
  clout << "wrote vti-File" << std::endl;
}

std::vector<double> BlockGeometry2D::physCoords(int iX, int iY) {
  std::vector<double> result(3,0.);
  result[0] = physCoordX(iX);
  result[1] = physCoordY(iY);
  return result;
}

double BlockGeometry2D::physCoordX(int iX) {
  return iX*_h + _x0;
}

double BlockGeometry2D::physCoordY(int iY) {
  return iY*_h + _y0;
}

} // namespace olb
