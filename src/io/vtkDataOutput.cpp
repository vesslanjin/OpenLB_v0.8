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

////////// class VtkDataWriter3D ////////////////////////////////////////

VtkDataWriter3D::VtkDataWriter3D(std::string const& fileName_)
  : fileName(fileName_),
    ostr(0)
{
  if (singleton::mpi().isMainProcessor()) {
    ostr = new std::ofstream(fileName.c_str());
    if (!(*ostr)) {
      std::cerr << "could not open file " <<  fileName << "\n";
      return;
    }
  }
}

VtkDataWriter3D::~VtkDataWriter3D() {
  delete ostr;
}

void VtkDataWriter3D::writeHeader(int x0, int x1, int y0, int y1, int z0, int z1,
                                  double originX, double originY, double originZ, double deltaX)
{
  if (singleton::mpi().isMainProcessor()) {
    (*ostr) << "<?xml version=\"1.0\"?>\n";
    (*ostr) << "<VTKFile type=\"ImageData\" version=\"0.1\" byte_order=\"LittleEndian\">\n";
    (*ostr) << "<ImageData WholeExtent=\""
            << x0 << " " << x1 << " "
            << y0 << " " << y1 << " "
            << z0 << " " << z1 << "\" "
            << "Origin=\""
            << originX << " " << originY << " " << originZ << "\" "
            << "Spacing=\""
            << deltaX << " " << deltaX << " " << deltaX << "\">\n";
  }
}

void VtkDataWriter3D::startPiece(int x0, int x1, int y0, int y1, int z0, int z1) {
  if (singleton::mpi().isMainProcessor()) {
    (*ostr) << "<Piece Extent=\""
            << x0 << " " << x1 << " "
            << y0 << " " << y1 << " "
            << z0 << " " << z1 << "\">\n";
    (*ostr) << "<PointData>\n";
  }
}

void VtkDataWriter3D::endPiece() {
  if (singleton::mpi().isMainProcessor()) {
    (*ostr) << "</PointData>\n";
    (*ostr) << "</Piece>\n";
  }
}

void VtkDataWriter3D::writeFooter() {
  if (singleton::mpi().isMainProcessor()) {
    (*ostr) << "</ImageData>\n";
    (*ostr) << "</VTKFile>\n";
  }
}

template<>
std::string VtkTypeNames<bool>::getBaseName() {
  return "Int";
}

template<>
std::string VtkTypeNames<char>::getBaseName() {
  return "Int";
}

template<>
std::string VtkTypeNames<unsigned char>::getBaseName() {
  return "UInt";
}

template<>
std::string VtkTypeNames<short int>::getBaseName() {
  return "Int";
}

template<>
std::string VtkTypeNames<unsigned short int>::getBaseName() {
  return "UInt";
}

template<>
std::string VtkTypeNames<int>::getBaseName() {
  return "Int";
}

template<>
std::string VtkTypeNames<unsigned int>::getBaseName() {
  return "UInt";
}

template<>
std::string VtkTypeNames<long int>::getBaseName() {
  return "Int";
}

template<>
std::string VtkTypeNames<unsigned long int>::getBaseName() {
  return "UInt";
}

template<>
std::string VtkTypeNames<float>::getBaseName() {
  return "Float";
}

template<>
std::string VtkTypeNames<double>::getBaseName() {
  return "Float";
}

template<>
std::string VtkTypeNames<long double>::getBaseName() {
  return "Float";
}

}
