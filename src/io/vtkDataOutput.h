/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Bernd Stahl, Jonas Latt
 *  Address: Battelle Batiment A, Route de Drize 7, 1227 Carouge, Switzerland
 *  E-mail: bernd.stahl@cui.unige.ch
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


#ifndef VTK_DATA_OUTPUT_H
#define VTK_DATA_OUTPUT_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "core/serializer.h"
#include "core/dataFieldBase3D.h"

namespace olb {

class VtkDataWriter3D {
public:
  VtkDataWriter3D(std::string const& fileName_);
  ~VtkDataWriter3D();
  void writeHeader(int x0, int x1, int y0, int y1, int z0, int z1,
                   double originX, double originY, double originZ, double deltaX);
  void startPiece(int x0, int x1, int y0, int y1, int z0, int z1);
  void endPiece();
  void writeFooter();
  template <typename T>
  void writeDataField(DataSerializer<T> const& serializer, std::string const& name, T scalingFactor, int nDim);
private:
  VtkDataWriter3D(VtkDataWriter3D const& rhs);
  VtkDataWriter3D operator=(VtkDataWriter3D const& rhs);
private:
  std::string fileName;
  std::ofstream *ostr;
};

template<typename T>
class VtkImageOutput2D {
public:
  VtkImageOutput2D(std::string fName, T deltaX_=(T)1, T originX_=(T)0, T originY_=(T)0);
  ~VtkImageOutput2D();
  template<typename S, typename TConv>
  void writeData(ScalarFieldBase2D<S> const& scalarField,
                 std::string scalarFieldName, TConv scalingFactor=(S)1);
  template<int n, typename S, typename TConv>
  void writeData(TensorFieldBase2D<S,n> const& tensorField,
                 std::string tensorFieldName, TConv scalingFactor=(S)1);
private:
  void writeHeader(int nx_, int ny_);
  void writeFooter();
private:
  std::string fullName;
  VtkDataWriter3D vtiOut;
  T deltaX;
  T originX, originY;
  bool headerWritten;
  int nx, ny;
};

template<typename T>
class VtkImageOutput3D {
public:
  VtkImageOutput3D(std::string fName, T deltaX_=(T)1, T originX_=(T)0, T originY_=(T)0, T originZ_=(T)0);
  ~VtkImageOutput3D();
  template<typename S, typename TConv>
  void writeData(ScalarFieldBase3D<S> const& scalarField,
                 std::string scalarFieldName, TConv scalingFactor=(S)1);
  template<int n, typename S, typename TConv>
  void writeData(TensorFieldBase3D<S,n> const& tensorField,
                 std::string tensorFieldName, TConv scalingFactor=(S)1);
private:
  void writeHeader(int nx_, int ny_, int nz_);
  void writeFooter();
private:
  std::string fullName;
  VtkDataWriter3D vtiOut;
  T deltaX;
  T originX, originY, originZ;
  bool headerWritten;
  int nx, ny, nz;
};


template<typename T> void writeVTKData3D (
  std::string const& fName,
  std::string const& scalarFieldName,
  ScalarFieldBase3D<T> const& scalarField,
  std::string const& vectorFieldName,
  TensorFieldBase3D<T,3> const& vectorField,
  T deltaX, T deltaT );

} // namespace olb

#endif
