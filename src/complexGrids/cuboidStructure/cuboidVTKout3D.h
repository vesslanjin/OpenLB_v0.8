/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006, 2007, 2009, 2012 Mathias J. Krause, Jonas Latt, Tim Dornieden
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
 * A method to write vtk data for cuboid geometries
 * (only for uniform grids) -- header file.
 */

#ifndef CUBOID_VTK_OUT_3D_H
#define CUBOID_VTK_OUT_3D_H

#include <sstream>
#include <iomanip>
#include <vector>

#include "core/dataFields3D.h"
#include "cuboidGeometry3D.h"
#include "core/loadBalancer.h"
#include "io/ostreamManager.h"
#include "functors/superLatticeBaseF3D.h"


namespace olb {

template<typename T>
class CuboidVTKout3D {
public:
  CuboidVTKout3D();
  /// A method to write vtk data for uniform grids
  static void writeFlowField (
    std::string const& fName,
    std::string const& scalarFieldName,
    std::vector<const ScalarFieldBase3D<T>* > scalarField,
    std::string const& vectorFieldName,
    std::vector<const TensorFieldBase3D<T,3>* > vectorField,
    CuboidGeometry3D<T> const& cGeometry,
    loadBalancer& load, T frac1, T frac2, int offset=1 );
  template <template <typename U> class DESCRIPTOR>
  static void write(SuperLatticeF3D<T,DESCRIPTOR>& f, int iT=0, int offset=1 );
  static void writeThread(std::string const& fName,
                          CuboidGeometry3D<T> const& cGeometry,
                          loadBalancer& load, int offset=1);
  static void writeDecomposition(std::string const& fName,
                                 CuboidGeometry3D<T> const& cGeometry,
                                 int offset=1);
  static void writeCuboid(std::string const& fName,
                          CuboidGeometry3D<T> const& cGeometry,
                          loadBalancer& load, T frac1, T frac2, int offset=1);
private:
  static OstreamManager clout;
  static void writePreamble(std::string& fullName, int nx, int ny, int nz, T originX, T originY, T originZ, T delta);
  static void writePiece(
    std::string& fullName,
    std::string const& scalarFieldName,
    const ScalarFieldBase3D<T>* scalarField,
    std::string const& vectorFieldName,
    const TensorFieldBase3D<T,3>* vectorField,
    T deltaX, T frac1, T frac2, int offset=1,
    int originX=0, int originY=0, int originZ=0 );
  template <template <typename U> class DESCRIPTOR>
  static void writePiece(
    std::string& fullName,
    std::string const& fName,
    SuperLatticeF3D<T,DESCRIPTOR>& f,
    int iC, int nx, int ny, int nz,
    T deltaX, T frac, int offset=1,
    int originX=0, int originY=0, int originZ=0 );
  static void writePostScript(std::string& fullName);
};

}  // namespace olb


#endif
