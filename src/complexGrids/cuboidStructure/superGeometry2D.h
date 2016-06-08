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
 * Representation of the 2D geometry -- header file.
 */

#ifndef SUPER_GEOMETRY_2D_H
#define SUPER_GEOMETRY_2D_H

#include <vector>
#include <map>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

#include "superGeometryStatistics2D.h"
#include "core/dataFields2D.h"
#include "io/vtkDataOutput.h"
#include "io/ostreamManager.h"
#include "functors/analyticalF.h"

/// All OpenLB code is contained in this namespace.
namespace olb {

class SuperGeometry2D {

private:
  /// Position of voxel (0/0/0)
  double _x0, _y0;
  /// Spacing
  double _h;
  /// Number of voxels in each direction
  int _nx, _ny;
  /// Size of ghost voxel layer
  int _offset;
  /// Matrix of voxels with material number / boundary number
  olb::ScalarField2D<unsigned short> _geometryData;
  /// Statistic class
  SuperGeometryStatistics2D _statistics;
  /// Statistic class
  bool _statisticsUpdateNeeded;
  /// class specific output stream
  mutable OstreamManager clout;

public:
  /// Constructor
  SuperGeometry2D() :
    _geometryData(0, 0),
    clout(std::cout,"SuperGeometry2D")
  {
    this->reInit(0, 0, 0, 0, 0, 0);
    _statisticsUpdateNeeded = true;
  }
  ;
  /// Constructor
  SuperGeometry2D(double x0, double y0, double h, int nX, int nY, int offset = 1) :
    _geometryData(nX + 2 * offset, nY + 2 * offset),
    clout(std::cout,"SuperGeometry2D")
  {
    this->reInit(x0, y0, h, nX, nY, offset);
    _statisticsUpdateNeeded = true;
  }
  ;

  /// Copy constructor
  SuperGeometry2D(SuperGeometry2D& rhs) :
    _geometryData(0, 0),
    clout(std::cout,"SuperGeometry2D")
  {
    _x0 = rhs._x0;
    _y0 = rhs._y0;
    _h = rhs._h;
    _nx = rhs._nx;
    _ny = rhs._ny;
    _offset = rhs._offset;
    _geometryData.swap(rhs._geometryData);
    _statisticsUpdateNeeded = true;
  }
  ;

  /// Copy assignment
  SuperGeometry2D operator=(SuperGeometry2D rhs) {
    SuperGeometry2D tmp(rhs);
    _statisticsUpdateNeeded = true;
    return tmp;
  };


  SuperGeometryStatistics2D& getStatistics() {
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

  /// re-initialization of the Data
  void reInit(double x0, double y0, double h, int nX, int nY, int offset,
              olb::ScalarField2D<unsigned short>* geometryData = NULL);
  /// returns the (iX,iY) entry in the 2D scalar field
  unsigned short getMaterial(int iX, int iY);
  /// sets the (iX,iY,iZ) entry in the 2D scalar field
  void setMaterial(int iX, int iY, unsigned short material);

  olb::ScalarField2D<unsigned short>* getRawData();

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

  void rename(unsigned short fromM, unsigned short toM, AnalyticalF2D<double,bool>& condition);

  void rename(unsigned short fromM, unsigned short toM, unsigned offsetX, unsigned offsetY, unsigned offsetZ);

  void regionGrowing(unsigned short fromM, unsigned short toM, int seedX, int seedY, int offsetX, int offsetY, std::map<std::vector<int>, int >* tmp=NULL);

  // Returns true if at (iX,iY) and in a neighbourhood of size (offsetX,offsetY,offsetZ) only voxels with material no material are there
  bool check(unsigned short material, int iX, int iY, unsigned offsetX, unsigned offsetY);

  bool find(unsigned short material, unsigned offsetX, unsigned offsetY, int& iX, int& iY);

  /// check for errors (searches for all outer voxels (=0) with an inner voxel (=1) as a direct neighbour)
  void checkForErrors();

  /// refine Mesh
  void refineMesh(int level = 2);

  /// adds offset
  void addOffset(int offset);

  /// removes offset
  void removeOffset();

  /// prints the chosen part of the Geometry
  void printLayer(int x0, int x1, int y0, int y1,
                  bool linenumber = false);
  void printLayer(int direction, int layer, bool linenumber = false);

  /// prints the chosen node and its neighbourhood
  void printNode(int x0, int y0);

  /// Writes a vti-File
  void writeVti(std::string filename);

  /// Transform lattice to physical Coordinates
  std::vector<double> physCoords(std::vector<int> coords);
  std::vector<double> physCoords(std::vector<double> coords);
  std::vector<double> physCoords(int iX, int iY);
  double physCoordX(int iX);
  double physCoordY(int iY);

};

} // namespace olb

#endif
