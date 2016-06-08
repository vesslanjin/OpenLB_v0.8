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

#ifndef VTK_DATA_OUTPUT_HH
#define VTK_DATA_OUTPUT_HH

#include "complexGrids/mpiManager/mpiManager.h"
#include "vtkDataOutput.h"
#include "serializerIO.h"
#include "core/singleton.h"
#include "core/olbDebug.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>

namespace olb {


////////// struct VtkTypeNames ///////////////////////////////////

template<typename T>
class VtkTypeNames {
public:
  static std::string getName();
private:
  static std::string getBaseName();
};

template<typename T>
std::string VtkTypeNames<T>::getName() {
  std::stringstream sstream;
  sstream << getBaseName();
  sstream << 8 * sizeof(T);

  std::string tName;
  sstream >> tName;
  return tName;
}


////////// class VtkDataWriter3D ////////////////////////////////////////

template<typename T>
void VtkDataWriter3D::writeDataField(DataSerializer<T> const& serializer,
                                     std::string const& name, T scalingFactor, int nDim)
{
  if (singleton::mpi().isMainProcessor()) {
    (*ostr) << "<DataArray type=\"" << VtkTypeNames<T>::getName()
            << "\" Name=\"" << name
            << "\" format=\"binary\" encoding=\"base64";
    if (nDim>1) {
      (*ostr) << "\" NumberOfComponents=\"" << nDim;
    }
    (*ostr) << "\">\n";
  }

  // undocumented requirement of the vtk xml file format:
  // in front of every binary blob, base64 or raw-binary, appended or not,
  // there is an UInt32 length indicator, giving the size of the binary blob in bytes;
  // when using base64 encoding, that length header must be encoded separately;
  // there must be no newline between the encoded length indicator and the encoded data block.
  //
  // those properties are properly handled by the serializer2ostr function, if unsigned int is
  // equal to UInt32. If not, you are on your own.

  ScalingSerializer<T> scaledSerializer(serializer, scalingFactor);
  // true means: enforce unsigned int
  serializer2ostr<T>(scaledSerializer, ostr, true);

  if (singleton::mpi().isMainProcessor()) {
    (*ostr) << "\n</DataArray>\n";
  }
}


////////// class VtkImageOutput2D ////////////////////////////////////

template<typename T>
VtkImageOutput2D<T>::VtkImageOutput2D(std::string fName, T deltaX_, T originX_, T originY_)
  : fullName ( singleton::directories().getVtkOutDir() + fName+".vti" ),
    vtiOut( fullName ),
    deltaX(deltaX_),
    originX(originX_),
    originY(originY_),
    headerWritten( false )
{ }

template<typename T>
VtkImageOutput2D<T>::~VtkImageOutput2D() {
  writeFooter();
}

template<typename T>
void VtkImageOutput2D<T>::writeHeader(int nx_, int ny_) {
  if (headerWritten) {
    OLB_PRECONDITION( nx == nx_);
    OLB_PRECONDITION( ny == ny_);
  }
  else {
    nx = nx_;
    ny = ny_;
    vtiOut.writeHeader(0,nx-1,0,ny-1,0,0, originX,originY,0,deltaX);
    vtiOut.startPiece(0,nx-1,0,ny-1,0,0);
    headerWritten = true;
  }
}

template<typename T>
void VtkImageOutput2D<T>::writeFooter() {
  if (headerWritten) {
    vtiOut.endPiece();
    vtiOut.writeFooter();
    headerWritten = false;
  }
}

template<typename T>
template<typename S, typename TConv>
void VtkImageOutput2D<T>::writeData( ScalarFieldBase2D<S> const& scalarField,
                                     std::string scalarFieldName, TConv scalingFactor )
{
  writeHeader(scalarField.getNx(), scalarField.getNy());
  TypeConversionSerializer<S,TConv> convSerializer(scalarField.getSerializer(IndexOrdering::backward) );
  vtiOut.writeDataField( convSerializer, scalarFieldName, scalingFactor, 1);
}

template<typename T>
template<int n, typename S, typename TConv>
void VtkImageOutput2D<T>::writeData( TensorFieldBase2D<S,n> const& tensorField,
                                     std::string tensorFieldName, TConv scalingFactor )
{
  writeHeader(tensorField.getNx(), tensorField.getNy());
  TypeConversionSerializer<S,TConv> convSerializer(tensorField.getSerializer(IndexOrdering::backward) );
  vtiOut.writeDataField(convSerializer, tensorFieldName, scalingFactor, n);
}

////////// class VtkImageOutput3D ////////////////////////////////////

template<typename T>
VtkImageOutput3D<T>::VtkImageOutput3D(std::string fName, T deltaX_, T originX_, T originY_, T originZ_)
  : fullName ( singleton::directories().getVtkOutDir() + fName+".vti" ),
    vtiOut( fullName ),
    deltaX(deltaX_),
    originX(originX_),
    originY(originY_),
    originZ(originZ_),
    headerWritten( false )
{ }

template<typename T>
VtkImageOutput3D<T>::~VtkImageOutput3D() {
  writeFooter();
}

template<typename T>
void VtkImageOutput3D<T>::writeHeader(int nx_, int ny_, int nz_) {
  if (headerWritten) {
    OLB_PRECONDITION( nx == nx_);
    OLB_PRECONDITION( ny == ny_);
    OLB_PRECONDITION( nz == nz_);
  }
  else {
    nx = nx_;
    ny = ny_;
    nz = nz_;
    vtiOut.writeHeader(0,nx-1,0,ny-1,0,nz-1,originX,originY,originZ,deltaX);
    vtiOut.startPiece(0,nx-1,0,ny-1,0,nz-1);
    headerWritten = true;
  }
}

template<typename T>
void VtkImageOutput3D<T>::writeFooter() {
  if (headerWritten) {
    vtiOut.endPiece();
    vtiOut.writeFooter();
    headerWritten = false;
  }
}

template<typename T>
template<typename S, typename TConv>
void VtkImageOutput3D<T>::writeData( ScalarFieldBase3D<S> const& scalarField,
                                     std::string scalarFieldName, TConv scalingFactor )
{
  writeHeader(scalarField.getNx(), scalarField.getNy(), scalarField.getNz());
  TypeConversionSerializer<S,TConv> convSerializer(scalarField.getSerializer(IndexOrdering::backward) );
  vtiOut.writeDataField( convSerializer, scalarFieldName, scalingFactor, 1);
}

template<typename T>
template<int n, typename S, typename TConv>
void VtkImageOutput3D<T>::writeData( TensorFieldBase3D<S,n> const& tensorField,
                                     std::string tensorFieldName, TConv scalingFactor )
{
  writeHeader(tensorField.getNx(), tensorField.getNy(), tensorField.getNz());
  TypeConversionSerializer<S,TConv> convSerializer(tensorField.getSerializer(IndexOrdering::backward) );
  vtiOut.writeDataField(convSerializer, tensorFieldName, scalingFactor, n);
}


////////// Free Functions //////////////////////////////////////////////

template<typename T> void writeVTKData3D (
  std::string const& fName,
  std::string const& scalarFieldName,
  ScalarFieldBase3D<T> const& scalarField,
  std::string const& vectorFieldName,
  TensorFieldBase3D<T,3> const& vectorField,
  T deltaX, T deltaT )
{
  std::string fullName = singleton::directories().getVtkOutDir() + fName+".vti";
  VtkDataWriter3D vtiOut(fullName);
  int nx = scalarField.getNx();
  int ny = scalarField.getNy();
  int nz = scalarField.getNz();
  vtiOut.writeHeader(0,nx-1,0,ny-1,0,nz-1,0,0,0,deltaX);

  vtiOut.startPiece(0,nx-1,0,ny-1,0,nz-1);
  vtiOut.writeDataField(scalarField.getSerializer(IndexOrdering::backward), scalarFieldName, 1./deltaT, 1);

  vtiOut.writeDataField(vectorField.getSerializer(IndexOrdering::backward), vectorFieldName, deltaX/deltaT, 3);
  vtiOut.endPiece();

  vtiOut.writeFooter();
}



}  // namespace olb

#endif


