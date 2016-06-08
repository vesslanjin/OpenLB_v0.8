/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007, 2009 Mathias J. Krause, Jonas Latt
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
 * (only for uniform grids) -- template instantiation.
 */

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "complexGrids/mpiManager/mpiManager.h"
#include "cuboidVTKout3D.h"
#include "cuboidVTKout3D.hh"
#include "core/latticeDescriptors.h"
#include "core/latticeDescriptors.hh"
#include "core/singleton.h"
#include "io/imageWriter.h"


namespace olb {

template class CuboidVTKout3D<double>;


template <>
template <>
void CuboidVTKout3D<double>::writePiece(
    std::string& fullName,
    std::string const& fName,
    SuperLatticeF3D<double,descriptors::D3Q19Descriptor>& f,
    int iC, int nx, int ny, int nz,
    double deltaX, double frac, int offset,
    int originX, int originY, int originZ ) {
  std::ofstream fout(fullName.c_str(), std::ios::app);
  if (!fout) clout << "Error: could not open " << fullName << std::endl;
  int x0 = originX/offset;
  if (originX%offset!=0) x0++;
  int y0 = originY/offset;
  if (originY%offset!=0) y0++;
  int z0 = originZ/offset;
  if (originZ%offset!=0) z0++;
  int x1 = (originX + nx-1)/offset;
  int y1 = (originY + ny-1)/offset;
  int z1 = (originZ + nz-1)/offset;

  fout << "<Piece Extent=\""
       << x0 <<" "<< x1 <<" "
       << y0 <<" "<< y1 <<" "
       << z0 <<" "<< z1 <<"\">\n";
  int dim = f.getTargetDim();
  if (dim == 1) {
    fout << "<PointData Scalars=\""
         << fName << "\">\n";
    fout << "<DataArray type=\"Float32\" Name=\""
         << fName <<"\">\n";
  }
  else {
    fout << "<PointData Vectors=\""
         << fName << "\">\n"; 
    fout << "<DataArray type=\"Float32\" Name=\""
         << fName << "\" "
         << "NumberOfComponents=\""
         << dim <<"\">\n";
  }

  for (int iZ=0; iZ<nz; ++iZ) {
    for (int iY=0; iY<ny; ++iY) {
      for (int iX=0; iX<nx; ++iX) {
        if ((iZ+originZ)%offset == 0 && (iY+originY)%offset == 0 && (iX+originX)%offset == 0 ) {
          for (int iDim=0; iDim<dim; ++iDim) {
            fout << f(iC,iX,iY,iZ)[iDim]*frac << " ";
          }
        }
      }
    }
  }
  fout << "\n";
  fout << "</DataArray>\n";
  fout << "</PointData>\n";
  fout << "</Piece>\n"; 
  fout.close();
}

template <>
template <>
void CuboidVTKout3D<double>::write(SuperLatticeF3D<double,descriptors::D3Q19Descriptor>& f, int iT, int offset ) {

  CuboidGeometry3D<double> const& cGeometry = f.getSuperLattice3D().get_cGeometry();
  loadBalancer& load = f.getSuperLattice3D().get_load();

  int rank = 0;
  int size = 1;
#ifdef PARALLEL_MODE_MPI
  rank = singleton::mpi().getRank();
  size = singleton::mpi().getSize();
#endif

  std::string fullName = singleton::directories().getVtkOutDir() + graphics::createFileName(f.name(), iT, 7) + ".vti";

  int nx     = cGeometry.get_motherC().get_nX()-1;
  int ny     = cGeometry.get_motherC().get_nY()-1;
  int nz     = cGeometry.get_motherC().get_nZ()-1;
  double delta = cGeometry.get_motherC().get_delta();
  double originX = cGeometry.get_motherC().get_globPosX();
  double originY = cGeometry.get_motherC().get_globPosY();
  double originZ = cGeometry.get_motherC().get_globPosZ();

  if(rank==0) {
    writePreamble(fullName, nx/offset, ny/offset, nz/offset, originX, originY, originZ, delta*offset);
  }
#ifdef PARALLEL_MODE_MPI
  singleton::mpi().barrier();
#endif

  for (int iRank=0; iRank<size; iRank++) {
    if(rank==iRank) {
      for (int iC=0; iC<load.size(); iC++) {
        double globX = cGeometry.get_cuboid(load.glob(iC)).get_globPosX();
        double globY = cGeometry.get_cuboid(load.glob(iC)).get_globPosY();
        double globZ = cGeometry.get_cuboid(load.glob(iC)).get_globPosZ();
        int nx2 = cGeometry.get_cuboid(load.glob(iC)).get_nX();
        int ny2 = cGeometry.get_cuboid(load.glob(iC)).get_nY();
        int nz2 = cGeometry.get_cuboid(load.glob(iC)).get_nZ();

        double deltaX = cGeometry.get_cuboid(load.glob(iC)).get_delta();
        /*int originX;
        int originY;
        int originZ;
        if(!cGeometry.get_motherC().checkPoint(globX, globY, globZ, originX, originY, originZ)) {
            std::cerr << "The grid is not uniform! Cant write vtk file " << fullName << std::endl;
            return;
        }*/

        writePiece(fullName, f.name(), f,
                   load.glob(iC), nx2, ny2, nz2, 
                   deltaX, 1, offset, globX, globY, globZ);
      }
    }
#ifdef PARALLEL_MODE_MPI
    singleton::mpi().barrier();
#endif
  }

  if(rank==0) {
    writePostScript(fullName);
  }
  return;
}





}
