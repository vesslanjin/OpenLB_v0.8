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
 * (only for uniform grids) -- generic implementation.
 */

#ifndef CUBOID_VTK_OUT_3D_HH
#define CUBOID_VTK_OUT_3D_HH

#include "complexGrids/mpiManager/mpiManager.h"
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "core/singleton.h"
#include "core/dataFields3D.hh"
#include "core/loadBalancer.h"
#include "cuboidGeometry3D.h"
#include "functors/superLatticeBaseF3D.h"
#include "io/imageWriter.h"

namespace olb {

template<typename T, template<typename U> class DESCRIPTOR> class SuperLatticeF3D;


////////// class CuboidVTKout3D ////////////////////////////////////////
template<typename T>
OstreamManager CuboidVTKout3D<T>::clout(std::cout,"CuboidVTKout3D");

template<typename T>
CuboidVTKout3D<T>::CuboidVTKout3D() {};

template<typename T>
void CuboidVTKout3D<T>::writeFlowField (
  std::string const& fName,
  std::string const& scalarFieldName,
  std::vector<const ScalarFieldBase3D<T>* > scalarField,
  std::string const& vectorFieldName,
  std::vector<const TensorFieldBase3D<T,3>* > vectorField,
  CuboidGeometry3D<T> const& cGeometry,
  loadBalancer& load, T frac1, T frac2, int offset )
{

  int rank = 0;
  int size = 1;
#ifdef PARALLEL_MODE_MPI
  rank = singleton::mpi().getRank();
  size = singleton::mpi().getSize();
#endif

  std::string fullName = singleton::directories().getVtkOutDir() + fName+".vti";

  int nx     = cGeometry.get_motherC().get_nX()-1;
  int ny     = cGeometry.get_motherC().get_nY()-1;
  int nz     = cGeometry.get_motherC().get_nZ()-1;
  T delta = cGeometry.get_motherC().get_delta();
  T originX = cGeometry.get_motherC().get_globPosX();
  T originY = cGeometry.get_motherC().get_globPosY();
  T originZ = cGeometry.get_motherC().get_globPosZ();

  if(rank==0) {
    writePreamble(fullName, nx/offset, ny/offset, nz/offset, originX, originY, originZ, delta*offset);
  }
#ifdef PARALLEL_MODE_MPI
  singleton::mpi().barrier();
#endif

  for (int iRank=0; iRank<size; iRank++) {
    if(rank==iRank) {
      for (int iC=0; iC<load.size(); iC++) {
        T globX = cGeometry.get_cuboid(load.glob(iC)).get_globPosX();
        T globY = cGeometry.get_cuboid(load.glob(iC)).get_globPosY();
        T globZ = cGeometry.get_cuboid(load.glob(iC)).get_globPosZ();
        T deltaX = cGeometry.get_cuboid(load.glob(iC)).get_delta();
        /*int originX;
        int originY;
        int originZ;
        if(!cGeometry.get_motherC().checkPoint(globX, globY, globZ, originX, originY, originZ)) {
            std::cerr << "The grid is not uniform! Cant write vtk file " << fullName << std::endl;
            return;
        }*/
        writePiece(fullName, scalarFieldName, scalarField[iC],
                   vectorFieldName, vectorField[iC],
                   deltaX, frac1, frac2, offset, globX, globY, globZ);
      }
    }
#ifdef PARALLEL_MODE_MPI
    singleton::mpi().barrier();
#endif
  }

  if(rank==0) {
    writePostScript(fullName);
  }
}

template <typename T>
template <template <typename U> class DESCRIPTOR>
void CuboidVTKout3D<T>::write(SuperLatticeF3D<T,DESCRIPTOR>& f, int iT, int offset ) {

  CuboidGeometry3D<T> const& cGeometry = f.getSuperLattice3D().get_cGeometry();
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
  T delta = cGeometry.get_motherC().get_delta();
  T originX = cGeometry.get_motherC().get_globPosX();
  T originY = cGeometry.get_motherC().get_globPosY();
  T originZ = cGeometry.get_motherC().get_globPosZ();

  if(rank==0) {
    writePreamble(fullName, nx/offset, ny/offset, nz/offset, originX, originY, originZ, delta*offset);
  }
#ifdef PARALLEL_MODE_MPI
  singleton::mpi().barrier();
#endif

  for (int iRank=0; iRank<size; iRank++) {
    if(rank==iRank) {
      for (int iC=0; iC<load.size(); iC++) {
        T globX = cGeometry.get_cuboid(load.glob(iC)).get_globPosX();
        T globY = cGeometry.get_cuboid(load.glob(iC)).get_globPosY();
        T globZ = cGeometry.get_cuboid(load.glob(iC)).get_globPosZ();
        int nx2 = cGeometry.get_cuboid(load.glob(iC)).get_nX();
        int ny2 = cGeometry.get_cuboid(load.glob(iC)).get_nY();
        int nz2 = cGeometry.get_cuboid(load.glob(iC)).get_nZ();

        T deltaX = cGeometry.get_cuboid(load.glob(iC)).get_delta();
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


template<typename T>
void CuboidVTKout3D<T>::writePiece(std::string& fullName,
                                   std::string const& scalarFieldName,
                                   const ScalarFieldBase3D<T>* scalarField,
                                   std::string const& vectorFieldName,
                                   const TensorFieldBase3D<T,3>* vectorField,
                                   T deltaX, T frac1, T frac2, int offset,
                                   int originX, int originY, int originZ) {

  std::ofstream fout(fullName.c_str(), std::ios::app);
  if (!fout) clout << "Error: could not open " << fullName << std::endl;

  int nx = scalarField->getNx();
  int ny = scalarField->getNy();
  int nz = scalarField->getNz();

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

  fout << "<PointData Scalars=\""
       << scalarFieldName << "\" "
       <<            "Vectors=\""
       << vectorFieldName << "\">\n";

  fout << "<DataArray type=\"Float32\" Name=\""
       << scalarFieldName << "\">\n";
  for (int iZ=0; iZ<nz; ++iZ) {
    for (int iY=0; iY<ny; ++iY) {
      for (int iX=0; iX<nx; ++iX) {
        if ((iZ+originZ)%offset == 0 && (iY+originY)%offset == 0 && (iX+originX)%offset == 0 )
          fout << scalarField->get(iX,iY,iZ)*frac2 << " ";
      }
    }
    fout << "\n";
  }
  fout << "</DataArray>\n";

  fout << "<DataArray type=\"Float32\" Name=\""
       << vectorFieldName << "\" "
       << "NumberOfComponents=\"3\">\n";

  for (int iZ=0; iZ<nz; ++iZ) {
    for (int iY=0; iY<ny; ++iY) {
      for (int iX=0; iX<nx; ++iX) {
        if ((iZ+originZ)%offset == 0 && (iY+originY)%offset == 0 && (iX+originX)%offset == 0 ) {
          fout << vectorField->get(iX,iY,iZ)[0]*frac1 << " ";
          fout << vectorField->get(iX,iY,iZ)[1]*frac1 << " ";
          fout << vectorField->get(iX,iY,iZ)[2]*frac1 << " ";
        }
      }
    }
    fout << "\n";
  }
  fout << "</DataArray>\n";
  fout << "</PointData>\n";
  fout << "</Piece>\n";

  fout.close();
}



template<typename T>
template <template <typename U> class DESCRIPTOR>
void CuboidVTKout3D<T>::writePiece(
    std::string& fullName,
    std::string const& fName,
    SuperLatticeF3D<T,DESCRIPTOR>& f,
    int iC, int nx, int ny, int nz,
    T deltaX, T frac, int offset,
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


template<typename T>
void CuboidVTKout3D<T>::writePreamble(std::string& fullName,
                                      int nx, int ny, int nz, T originX, T originY, T originZ, T delta)
{
  std::ofstream fout(fullName.c_str());
  if (!fout) clout << "Error: could not open " << fullName << std::endl;

  fout << "<?xml version=\"1.0\"?>\n";
  fout << "<VTKFile type=\"ImageData\" version=\"0.1\" "
       << "byte_order=\"LittleEndian\">\n";
  fout << "<ImageData WholeExtent=\" 0 "
       << nx << " 0 "
       << ny << " 0 "
       << nz << " \" "
       << "Origin=\"" << originX << " " << originY << " " << originZ <<"\" Spacing=\""
       << delta << " " << delta << " " << delta << "\">\n";

  fout.close();
}

template<typename T>
void CuboidVTKout3D<T>::writePostScript(std::string& fullName) {

  std::ofstream fout(fullName.c_str(), std::ios::app );
  if (!fout) clout << "Error: could not open " << fullName << std::endl;

  fout << "</ImageData>\n";
  fout << "</VTKFile>\n";

  fout.close();
}

template<typename T>
void CuboidVTKout3D<T>::writeDecomposition(std::string const& fName,
    CuboidGeometry3D<T> const& cGeometry,
    int offset )
{

  int rank = 0;
#ifdef PARALLEL_MODE_MPI
  rank = singleton::mpi().getRank();
#endif

  std::string fullName = singleton::directories().getVtkOutDir() + fName+".vti";

  std::ofstream fout(fullName.c_str());
  if (!fout) std::cerr << "could not open " << fullName << std::endl;
  fout.close();

  int nx     = cGeometry.get_motherC().get_nX()-1;
  int ny     = cGeometry.get_motherC().get_nY()-1;
  int nz     = cGeometry.get_motherC().get_nZ()-1;
  T delta = cGeometry.get_motherC().get_delta();
  T originX = cGeometry.get_motherC().get_globPosX();
  T originY = cGeometry.get_motherC().get_globPosY();
  T originZ = cGeometry.get_motherC().get_globPosZ();

#ifdef PARALLEL_MODE_MPI
  singleton::mpi().barrier();
#endif
  if(rank==0) {
    writePreamble(fullName, nx/offset, ny/offset, nz/offset, originX, originY, originZ, delta*offset);
    for (int iC=0; iC<cGeometry.get_nC(); iC++) {
      int globX = cGeometry.get_cuboid(iC).get_globPosX();
      int globY = cGeometry.get_cuboid(iC).get_globPosY();
      int globZ = cGeometry.get_cuboid(iC).get_globPosZ();

      int nX = cGeometry.get_cuboid(iC).get_nX();
      int nY = cGeometry.get_cuboid(iC).get_nY();
      int nZ = cGeometry.get_cuboid(iC).get_nZ();

      fout.open(fullName.c_str(), std::ios::app);
      fout << "<Piece Extent=\""
           << globX <<" "<< globX + nX -1 <<" "
           << globY <<" "<< globY + nY -1 <<" "
           << globZ <<" "<< globZ + nZ -1 <<"\">\n";

      fout << "<PointData Scalars=\""
           << "cuboid" << "\">\n";

      fout << "<DataArray type=\"Int32\" Name=\""
           << "cuboid" << "\">\n";
      for (int iZ=0; iZ<nZ; ++iZ) {
        for (int iY=0; iY<nY; ++iY) {
          for (int iX=0; iX<nX; ++iX) {
            if ((iZ+globZ)%offset == 0 && (iY+globY)%offset == 0 && (iX+globX)%offset == 0 )
              fout << (float)iC+(float)1 << " ";
          }
        }
        fout << "\n";
      }
      fout << "</DataArray>\n";
      fout << "</PointData>\n";
      fout << "</Piece>\n";
      fout.close();
    }
    writePostScript(fullName);
  }
#ifdef PARALLEL_MODE_MPI
  singleton::mpi().barrier();
#endif
}

template<typename T>
void CuboidVTKout3D<T>::writeThread(std::string const& fName,
                                    CuboidGeometry3D<T> const& cGeometry,
                                    loadBalancer& load, int offset )
{

  int rank = 0;
  int size = 1;
#ifdef PARALLEL_MODE_MPI
  rank = singleton::mpi().getRank();
  size = singleton::mpi().getSize();
#endif

  std::string fullName = singleton::directories().getVtkOutDir() + fName+".vti";

  std::ofstream fout(fullName.c_str());
  if (!fout) std::cerr << "could not open " << fullName << std::endl;
  fout.close();

  int nx     = cGeometry.get_motherC().get_nX()-1;
  int ny     = cGeometry.get_motherC().get_nY()-1;
  int nz     = cGeometry.get_motherC().get_nZ()-1;
  T delta = cGeometry.get_motherC().get_delta();
  T originX = cGeometry.get_motherC().get_globPosX();
  T originY = cGeometry.get_motherC().get_globPosY();
  T originZ = cGeometry.get_motherC().get_globPosZ();

#ifdef PARALLEL_MODE_MPI
  singleton::mpi().barrier();
#endif
  if(rank==0) {
    writePreamble(fullName, nx/offset, ny/offset, nz/offset, originX, originY, originZ, delta*offset);
  }
#ifdef PARALLEL_MODE_MPI
  singleton::mpi().barrier();
#endif

  for (int iRank=0; iRank<size; iRank++) {
    if(rank==iRank) {
      for (int iC=0; iC<load.size(); iC++) {
        int globX = cGeometry.get_cuboid(load.glob(iC)).get_globPosX();
        int globY = cGeometry.get_cuboid(load.glob(iC)).get_globPosY();
        int globZ = cGeometry.get_cuboid(load.glob(iC)).get_globPosZ();

        int nX = cGeometry.get_cuboid(load.glob(iC)).get_nX();
        int nY = cGeometry.get_cuboid(load.glob(iC)).get_nY();
        int nZ = cGeometry.get_cuboid(load.glob(iC)).get_nZ();

        fout.open(fullName.c_str(), std::ios::app);

        /*int originX;
        int originY;
        int originZ;
        if(!cGeometry.get_motherC().checkPoint(globX, globY, globZ, originX, originY, originZ)) {
            std::cerr << "The grid is not uniform! Cant write vtk file " << fullName << std::endl;
            return;
        }*/
        /*

            int nx = 0;
            int ny = 0;
            int nz = 0;

            int x0 = originX/offset; if (originX%offset!=0) x0++;
            int y0 = originY/offset; if (originY%offset!=0) y0++;
            int z0 = originZ/offset; if (originZ%offset!=0) z0++;
            int x1 = (originX + nx-1)/offset;
            int y1 = (originY + ny-1)/offset;
            int z1 = (originZ + nz-1)/offset;
        */
        fout << "<Piece Extent=\""
             << globX <<" "<< globX + nX -1 <<" "
             << globY <<" "<< globY + nY -1 <<" "
             << globZ <<" "<< globZ + nZ -1 <<"\">\n";

        fout << "<PointData Scalars=\""
             << "thread" << "\">\n";

        fout << "<DataArray type=\"Int32\" Name=\""
             << "thread" << "\">\n";
        for (int iZ=0; iZ<nZ; ++iZ) {
          for (int iY=0; iY<nY; ++iY) {
            for (int iX=0; iX<nX; ++iX) {
              if ((iZ+globZ)%offset == 0 && (iY+globY)%offset == 0 && (iX+globX)%offset == 0 )
                fout << (float)singleton::mpi().getRank()+(float)1 << " ";
            }
          }
          fout << "\n";
        }
        fout << "</DataArray>\n";
        fout << "</PointData>\n";
        fout << "</Piece>\n";
        fout.close();
      }
    }
#ifdef PARALLEL_MODE_MPI
    singleton::mpi().barrier();
#endif
  }

  if(rank==0) {
    writePostScript(fullName);
  }

}

template<typename T>
void CuboidVTKout3D<T>::writeCuboid(std::string const& fName,
                                    CuboidGeometry3D<T> const& cGeometry,
                                    loadBalancer& load, T frac1, T frac2, int offset )
{
  int rank = 0;
  int size = 1;
#ifdef PARALLEL_MODE_MPI
  rank = singleton::mpi().getRank();
  size = singleton::mpi().getSize();
#endif

  std::string fullName = singleton::directories().getVtkOutDir() + fName+".vti";

  std::ofstream fout(fullName.c_str());
  if (!fout) std::cerr << "could not open " << fullName << std::endl;
  fout.close();

  int nx     = cGeometry.get_motherC().get_nX()-1;
  int ny     = cGeometry.get_motherC().get_nY()-1;
  int nz     = cGeometry.get_motherC().get_nZ()-1;
  T delta = cGeometry.get_motherC().get_delta();
  T originX = cGeometry.get_motherC().get_globPosX();
  T originY = cGeometry.get_motherC().get_globPosY();
  T originZ = cGeometry.get_motherC().get_globPosZ();

#ifdef PARALLEL_MODE_MPI
  singleton::mpi().barrier();
#endif
  if(rank==0) {
    writePreamble(fullName, nx/offset, ny/offset, nz/offset, originX, originY, originZ, delta*offset);
  }
#ifdef PARALLEL_MODE_MPI
  singleton::mpi().barrier();
#endif

  for (int iRank=0; iRank<size; iRank++) {
    if(rank==iRank) {
      for (int iC=0; iC<load.size(); iC++) {
        int globX = cGeometry.get_cuboid(load.glob(iC)).get_globPosX();
        int globY = cGeometry.get_cuboid(load.glob(iC)).get_globPosY();
        int globZ = cGeometry.get_cuboid(load.glob(iC)).get_globPosZ();

        int nX = cGeometry.get_cuboid(load.glob(iC)).get_nX();
        int nY = cGeometry.get_cuboid(load.glob(iC)).get_nY();
        int nZ = cGeometry.get_cuboid(load.glob(iC)).get_nZ();

        fout.open(fullName.c_str(), std::ios::app);
        fout << "<Piece Extent=\""
             << globX <<" "<< globX + nX -1 <<" "
             << globY <<" "<< globY + nY -1 <<" "
             << globZ <<" "<< globZ + nZ -1 <<"\">\n";

        fout << "<PointData Scalars=\""
             << "cuboid" << "\">\n";

        fout << "<DataArray type=\"Int32\" Name=\""
             << "cuboid" << "\">\n";
        for (int iZ=0; iZ<nZ; ++iZ) {
          for (int iY=0; iY<nY; ++iY) {
            for (int iX=0; iX<nX; ++iX) {
              if ((iZ+globZ)%offset == 0 && (iY+globY)%offset == 0 && (iX+globX)%offset == 0 )
                fout << (float)load.glob(iC)+(float)1 << " ";
            }
          }
          fout << "\n";
        }
        fout << "</DataArray>\n";
        fout << "</PointData>\n";
        fout << "</Piece>\n";
        fout.close();
      }
    }
#ifdef PARALLEL_MODE_MPI
    singleton::mpi().barrier();
#endif
  }

  if(rank==0) {
    writePostScript(fullName);
  }

}

}  // namespace olb

#endif
