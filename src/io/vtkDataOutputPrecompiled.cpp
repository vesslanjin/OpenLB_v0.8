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

#include "complexGrids/mpiManager/mpiManager.h"
#include "core/serializer.h"
#include "core/serializer.hh"
#include "vtkDataOutput.h"
#include "vtkDataOutput.hh"
#include "serializerIO.h"
#include "serializerIO.hh"
#include "base64.h"
#include "base64.hh"

namespace olb {

template
void VtkDataWriter3D::writeDataField (
  DataSerializer<char> const& serializer, std::string const& name,
  char scalingFactor, int nDim );

template
void VtkDataWriter3D::writeDataField (
  DataSerializer<unsigned char> const& serializer, std::string const& name,
  unsigned char scalingFactor, int nDim );

template
void VtkDataWriter3D::writeDataField (
  DataSerializer<short int> const& serializer, std::string const& name,
  short int scalingFactor, int nDim );

template
void VtkDataWriter3D::writeDataField (
  DataSerializer<unsigned short int> const& serializer, std::string const& name,
  unsigned short int scalingFactor, int nDim );

template
void VtkDataWriter3D::writeDataField (
  DataSerializer<int> const& serializer, std::string const& name,
  int scalingFactor, int nDim );

template
void VtkDataWriter3D::writeDataField (
  DataSerializer<unsigned int> const& serializer, std::string const& name,
  unsigned int scalingFactor, int nDim );

template
void VtkDataWriter3D::writeDataField (
  DataSerializer<long int> const& serializer, std::string const& name,
  long int scalingFactor, int nDim );

template
void VtkDataWriter3D::writeDataField (
  DataSerializer<unsigned long int> const& serializer, std::string const& name,
  unsigned long int scalingFactor, int nDim );

template
void VtkDataWriter3D::writeDataField (
  DataSerializer<float> const& serializer, std::string const& name,
  float scalingFactor, int nDim );

template
void VtkDataWriter3D::writeDataField (
  DataSerializer<double> const& serializer, std::string const& name,
  double scalingFactor, int nDim );

template
void VtkDataWriter3D::writeDataField (
  DataSerializer<long double> const& serializer, std::string const& name,
  long double scalingFactor, int nDim );

template void writeVTKData3D<double> (
  std::string const& fName,
  std::string const& scalarFieldName,
  ScalarFieldBase3D<double> const& scalarField,
  std::string const& vectorFieldName,
  TensorFieldBase3D<double,3> const& vectorField,
  double deltaX, double deltaT );

template class VtkImageOutput2D<double>;

template void VtkImageOutput2D<double>::writeData<double,double> (
  ScalarFieldBase2D<double> const& scalarField,
  std::string scalarFieldName, double scalingFactor );

template void VtkImageOutput2D<double>::writeData<double,float> (
  ScalarFieldBase2D<double> const& scalarField,
  std::string scalarFieldName, float scalingFactor );

template void VtkImageOutput2D<double>::writeData<2, double,double> (
  TensorFieldBase2D<double,2> const& tensorField,
  std::string tensorFieldName, double scalingFactor );

template void VtkImageOutput2D<double>::writeData<2, double,float> (
  TensorFieldBase2D<double,2> const& tensorField,
  std::string tensorFieldName, float scalingFactor );

template void VtkImageOutput2D<double>::writeData<9, double,double> (
  TensorFieldBase2D<double,9> const& tensorField,
  std::string tensorFieldName, double scalingFactor );

template void VtkImageOutput2D<double>::writeData<9, double,float> (
  TensorFieldBase2D<double,9> const& tensorField,
  std::string tensorFieldName, float scalingFactor );


template class VtkImageOutput3D<double>;

template void VtkImageOutput3D<double>::writeData<double,double> (
  ScalarFieldBase3D<double> const& scalarField,
  std::string scalarFieldName, double scalingFactor );

template void VtkImageOutput3D<double>::writeData<double,float> (
  ScalarFieldBase3D<double> const& scalarField,
  std::string scalarFieldName, float scalingFactor );

template void VtkImageOutput3D<double>::writeData<3, double,double> (
  TensorFieldBase3D<double,3> const& tensorField,
  std::string tensorFieldName, double scalingFactor );

template void VtkImageOutput3D<double>::writeData<3, double,float> (
  TensorFieldBase3D<double,3> const& tensorField,
  std::string tensorFieldName, float scalingFactor );

template void VtkImageOutput3D<double>::writeData<19, double,double> (
  TensorFieldBase3D<double,19> const& tensorField,
  std::string tensorFieldName, double scalingFactor );

template void VtkImageOutput3D<double>::writeData<19, double,float> (
  TensorFieldBase3D<double,19> const& tensorField,
  std::string tensorFieldName, float scalingFactor );

}
