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
 * Representation of the 3D geometry -- header file.
 */

#ifndef BLOCK_GEOMETRY_3D_H
#define BLOCK_GEOMETRY_3D_H

#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "blockGeometryStatistics3D.h"
#include "dataFields3D.h"
#include "io/vtkDataOutput.h"
#include "io/ostreamManager.h"
#include "functors/analyticalF.h"

/// All OpenLB code is contained in this namespace.
namespace olb {

class BlockGeometry3D {

private:
  /// Position of voxel (0/0/0)
  double _x0, _y0, _z0;
  /// Spacing
  double _h;
  /// Number of voxels in each direction
  int _nx, _ny, _nz;
  /// Size of ghost voxel layer
  int _offset;
  /// Matrix of voxels with material number / boundary number
  olb::ScalarField3D<unsigned short> _geometryData;
  /// Statistic class
  BlockGeometryStatistics3D _statistics;
  /// Statistic class
  bool _statisticsUpdateNeeded;
  /// class specific output stream
  mutable OstreamManager clout;

public:
  /// Constructor
  BlockGeometry3D() :
    _geometryData(0, 0, 0),
    clout(std::cout,"BlockGeometry3D")
  {
    this->reInit(0, 0, 0, 0, 0, 0, 0, 0);
    _statisticsUpdateNeeded = true;
  }
  ;
  /// Constructor
  BlockGeometry3D(double x0, double y0, double z0, double h, int nX, int nY,
                  int nZ, int offset = 1) :
    _geometryData(nX + 2 * offset, nY + 2 * offset, nZ + 2 * offset),
    clout(std::cout,"BlockGeometry3D")
  {
    this->reInit(x0, y0, z0, h, nX, nY, nZ, offset);
    _statisticsUpdateNeeded = true;
  }
  ;

  /// Copy constructor
  BlockGeometry3D(BlockGeometry3D& rhs) :
    _geometryData(0, 0, 0),
    clout(std::cout,"BlockGeometry3D")
  {
    _x0 = rhs._x0;
    _y0 = rhs._y0;
    _z0 = rhs._z0;
    _h = rhs._h;
    _nx = rhs._nx;
    _ny = rhs._ny;
    _nz = rhs._nz;
    _offset = rhs._offset;
    _geometryData.swap(rhs._geometryData);
    _statisticsUpdateNeeded = true;
  }
  ;

  /// Copy assignment
  BlockGeometry3D operator=(BlockGeometry3D rhs) {
    BlockGeometry3D tmp(rhs);
    _statisticsUpdateNeeded = true;
    return tmp;
  };

  /// Returns a statistics object
  BlockGeometryStatistics3D& getStatistics() {
    if (_statisticsUpdateNeeded) {
      _statistics.reInit(this);
      _statisticsUpdateNeeded = false;
    }
    return _statistics;
  };

  /// returns the x-position of voxel (0/0/0)
  double getPositionX();
  /// sets a new x-position of voxel (0/0/0)
  void setPositionX(double x0);

  /// returns the y-position of voxel (0/0/0)
  double getPositionY();
  /// sets a new y-position of voxel (0/0/0)
  void setPositionY(double y0);

  /// returns the Z-position of voxel (0/0/0)
  double getPositionZ();
  /// sets a new Z-position of voxel (0/0/0)
  void setPositionZ(double z0);

  /// returns the spacing _h
  double getSpacing();
  /// sets a new spacing h
  void setSpacing(double h);

  /// returns the offset
  int getOffset();
  /// sets a new spacing h
  void setOffset(int offset);

  /// returns number of voxels in X-direction
  int getNx();
  /// sets a new number of voxels in X-direction
  void setNx(int nX);

  /// returns number of voxels in Y-direction
  int getNy();
  /// sets a new number of voxels in Y-direction
  void setNy(int nY);

  /// returns number of voxels in Z-direction
  int getNz();
  /// sets a new number of voxels in Z-direction
  void setNz(int nZ);

  /// re-initialization of the Data
  void reInit(double x0, double y0, double z0, double h, int nX, int nY,
              int nZ, int offset,
              olb::ScalarField3D<unsigned short>* geometryData = NULL);
  /// returns the (iX,iY,iZ) entry in the 3D scalar field
  unsigned short getMaterial(int iX, int iY, int iZ);
  /// sets the (iX,iY,iZ) entry in the 3D scalar field
  void setMaterial(int iX, int iY, int iZ, unsigned short material);

  /// returns the raw data field
  olb::ScalarField3D<unsigned short>* getRawData();

  /// new functions

  /// outer cleaning
  void clean();

  /// remove fluid fluids from the outer domain
  void outerClean();

  /// inner cleaning for all boundary types
  void innerClean();

  /// inner cleaning for specific boundary types
  void innerClean(int bcType);

  /// replace one material with another
  void rename(unsigned short fromM, unsigned short toM);

  /// replace one material that fulfills an indicator functor condition with another
  void rename(unsigned short fromM, unsigned short toM,
              AnalyticalF3D<bool,double>& condition);

  /// replace one material with another respecting an offset (overlap)
  void rename(unsigned short fromM, unsigned short toM,
              unsigned offsetX, unsigned offsetY, unsigned offsetZ);



  /// rename several voxels with a new material number using a seed point and directions indicated by offsetX,Y,Z != 0
  void regionGrowing(unsigned short fromM, unsigned short toM,
                     int seedX, int seedY, int seedZ,
                     int offsetX, int offsetY, int offsetZ,
                     std::map<std::vector<int>, int >* tmp=NULL);


 


  /// returns true if at (iX,iY,iZ) and in a neighbourhood of size (offsetX,offsetY,offsetZ) only voxels with material no material are there
  bool check(unsigned short material, int iX, int iY, int iZ,
             unsigned offsetX, unsigned offsetY, unsigned offsetZ);

  /// returns the coordinates of a voxel with material
  bool find(unsigned short material,
            unsigned offsetX, unsigned offsetY, unsigned offsetZ,
            int& iX, int& iY, int& iZ);












  /// check for errors (searches for all outer voxels (=0) with an inner voxel (=1) as a direct neighbour)
  void checkForErrors();

  /// refine Mesh
  void refineMesh(int level = 2);

  /// adds offset
  void addOffset(int offset);

  /// removes offset
  void removeOffset();


  /// prints the chosen part of the Geometry
  void printLayer(int x0, int x1, int y0, int y1, int z0, int z1,
                  bool linenumber = false);
  void printLayer(int direction, int layer, bool linenumber = false);

  /// prints the chosen node and its neighbourhood
  void printNode(int x0, int y0, int z0);

  /// Writes a vti-File
  void writeVti(std::string filename);

  /// Transform lattice to physical Coordinates
  std::vector<double> physCoords(std::vector<double> coords);
  std::vector<double> physCoords(int iX, int iY, int iZ);
  double physCoordX(int iX);
  double physCoordY(int iY);
  double physCoordZ(int iZ);

};

} // namespace olb

#endif
