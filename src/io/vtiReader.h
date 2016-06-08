/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Thomas Henn
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

#ifndef VTI_READER_H
#define VTI_READER_H

#include <string>
#include <vector>

/*#include "io/xmlReader.h"
#include "io/xmlReader.cpp"*/
#include "complexGrids/cuboidStructure/cuboid3D.h"
#include "complexGrids/cuboidStructure/cuboid2D.h"
#include "core/dataFields3D.h"
#include "io/ostreamManager.h"
#include "io/xmlReader.cpp"

//typedef double T;
namespace olb {

template<typename T>
class VTIreader3D : public XMLreader {
      VTIreader3D();

  public:
      VTIreader3D(const std::string& fName);
      ~VTIreader3D();

      void getCuboid(Cuboid3D<T>& cuboid);
      void getCuboids(std::vector<Cuboid3D<T>* >& cuboids);
      bool getScalarData(ScalarField3D<T>* base, const std::string dName);
      bool getVectorData(TensorField3D<T, 3>* base, const std::string dName);
      void getScalarMultiPieceData(std::vector<const ScalarFieldBase3D<T>* >& bases, const std::string dName);
      void getVectorMultiPieceData(std::vector<const TensorFieldBase3D<T, 3>* >& bases, const std::string dName);
      void printInfo();


  private:
      /* Origin */
      int _x0, _y0, _z0;
      /* #Nodes */
      int _x, _y, _z;
      T _delta;
      T *_data;
};

template<typename T>
class VTIreader2D : public XMLreader {
      VTIreader2D();

  public:
      VTIreader2D(const std::string& fName);
      ~VTIreader2D();

      void getCuboid(Cuboid2D<T>& cuboid);
      void getCuboids(std::vector<Cuboid2D<T>* >& cuboids);
      bool getScalarData(ScalarField2D<T>* base, const std::string dName);
      bool getVectorData(TensorField2D<T, 2>* base, const std::string dName);
      void getScalarMultiPieceData(std::vector<const ScalarFieldBase2D<T>* >& bases, const std::string dName);
      void getVectorMultiPieceData(std::vector<const TensorFieldBase2D<T, 2>* >& bases, const std::string dName);
      void printInfo();


  private:
      /* Origin */
      int _x0, _y0, _z0;
      /* #Nodes */
      int _x, _y, _z;
      T _delta;
      T *_data;
};

} // namespace olb

#endif
