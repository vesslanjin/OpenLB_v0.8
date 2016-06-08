/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Lukas Baron, Tim Dornieden, Mathias J. Krause,
 *  Albert Mink
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

#ifndef SUPER_LATTICE_INTEGRAL_F_3D_HH
#define SUPER_LATTICE_INTEGRAL_F_3D_HH

#include<vector>    // for generic i/o
#include<cmath>     // for lpnorm
#include<string>     // for lpnorm

#include "superLatticeIntegralF3D.h"
#include "functors/genericF.h"
#include "functors/analyticalF.h"
#include "functors/indicatorF.h"
#include "complexGrids/cuboidStructure/superLattice3D.h"
#include "core/lbHelpers.h"  // for computation of lattice rho and velocity

namespace olb {


template <typename T, template <typename U> class DESCRIPTOR>
SuperMax<T,DESCRIPTOR>::SuperMax(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperGeometry3D& _superGeometry, int _material)
  : SuperLatticeF3D<T,DESCRIPTOR>(_f.getSuperLattice3D(),_f.getTargetDim()), f(_f), superGeometry(_superGeometry), material(_material) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperMax<T,DESCRIPTOR>::operator() (std::vector<int> input) {

  f.getSuperLattice3D().communicate();
  CuboidGeometry3D<T>& cGeometry = f.getSuperLattice3D().get_cGeometry();
  loadBalancer& load = f.getSuperLattice3D().get_load();

  std::vector<T> tmp(this->getTargetDim(), T() );
  for (int i=0; i<this->getTargetDim(); i++) {

    for (int iC=0; iC<load.size(); iC++) {
      int nX = cGeometry.get_cuboid(load.glob(iC)).get_nX();
      int nY = cGeometry.get_cuboid(load.glob(iC)).get_nY();
      int nZ = cGeometry.get_cuboid(load.glob(iC)).get_nZ();
      for (int iX=0;iX<nX;iX++) {
        for (int iY=0;iY<nY;iY++) {
          for (int iZ=0;iZ<nZ;iZ++) {
            int globX = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosX() + iX;
            int globY = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosY() + iY;
            int globZ = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosZ() + iZ;
            if (superGeometry.getMaterial(globX, globY, globZ) == material) {
              if (fabs(f(load.glob(iC),iX,iY,iZ)[i]) > tmp[i]) {
                tmp[i]=fabs(f(load.glob(iC),iX,iY,iZ)[i]);
              }
            }
          }
        }
      }
    }
#ifdef PARALLEL_MODE_MPI
    singleton::mpi().reduceAndBcast(tmp[i], MPI_MAX);
#endif
  }
  return tmp;
}

template <typename T, template <typename U> class DESCRIPTOR>
SuperSum3D<T,DESCRIPTOR>::SuperSum3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperGeometry3D& _superGeometry, int _material) 
  : SuperLatticeF3D<T,DESCRIPTOR>(_f.getSuperLattice3D(),_f.getTargetDim()), f(_f), superGeometry(_superGeometry), material(_material) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperSum3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {
  f.getSuperLattice3D().communicate();
  CuboidGeometry3D<T>& cGeometry = f.getSuperLattice3D().get_cGeometry();
  loadBalancer& load = f.getSuperLattice3D().get_load();

  std::vector<T> tmp(this->getTargetDim(), T() );
  for (int i=0; i<this->getTargetDim(); i++) {
    for (int iC=0; iC<load.size(); iC++) {
      int nX = cGeometry.get_cuboid(load.glob(iC)).get_nX();
      int nY = cGeometry.get_cuboid(load.glob(iC)).get_nY();
      int nZ = cGeometry.get_cuboid(load.glob(iC)).get_nZ();
      for (int iX=0;iX<nX;iX++) {
        for (int iY=0;iY<nY;iY++) {
          for (int iZ=0;iZ<nZ;iZ++) {
            int globX = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosX() + iX;
            int globY = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosY() + iY;
            int globZ = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosZ() + iZ;
            if (this->superGeometry.getMaterial(globX, globY, globZ) == material) {
              //if (f(load.glob(iC),iX,iY,iZ)[i]!=0) std::cout<< f(load.glob(iC),iX,iY,iZ)[i] <<std::endl;
              tmp[i]+=f(load.glob(iC),iX,iY,iZ)[i];
            }
          }
        }
      }
    }
#ifdef PARALLEL_MODE_MPI
singleton::mpi().reduceAndBcast(tmp[i], MPI_SUM);
#endif
  }
  return tmp;
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperIntegral3D<T,DESCRIPTOR>::SuperIntegral3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperGeometry3D& _superGeometry, int _material) 
  : SuperLatticeF3D<T,DESCRIPTOR>(_f.getSuperLattice3D(),_f.getTargetDim()), f(_f), superGeometry(_superGeometry), material(_material) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperIntegral3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {

  f.getSuperLattice3D().communicate();
  CuboidGeometry3D<T>& cGeometry = f.getSuperLattice3D().get_cGeometry();
  loadBalancer& load = f.getSuperLattice3D().get_load();

  std::vector<T> tmp(this->n, T() );
  for (int i=0; i<this->n; i++) {
    for (int iC=0; iC<load.size(); iC++) {
      int nX = cGeometry.get_cuboid(load.glob(iC)).get_nX();
      int nY = cGeometry.get_cuboid(load.glob(iC)).get_nY();
      int nZ = cGeometry.get_cuboid(load.glob(iC)).get_nZ();
      T weight = pow(this->superGeometry.getSpacing(),3);
      for (int iX=0;iX<nX;iX++) {
        for (int iY=0;iY<nY;iY++) {
          for (int iZ=0;iZ<nZ;iZ++) {
            int globX = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosX() + iX;
            int globY = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosY() + iY;
            int globZ = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosZ() + iZ;
            if (this->superGeometry.getMaterial(globX, globY, globZ) == material) {
              tmp[i]+=f(load.glob(iC),iX,iY,iZ)[i]*weight;
            }
          }
        }
      }
    }
#ifdef PARALLEL_MODE_MPI
singleton::mpi().reduceAndBcast(tmp[i], MPI_SUM);
#endif
  }
  return tmp;
}

template <typename T, template <typename U> class DESCRIPTOR>
SuperL1Norm3D<T,DESCRIPTOR>::SuperL1Norm3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperGeometry3D& _superGeometry, int _material) 
  : SuperLatticeF3D<T,DESCRIPTOR>(_f.getSuperLattice3D(),_f.getTargetDim()), f(_f), superGeometry(_superGeometry), material(_material) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperL1Norm3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {

  f.getSuperLattice3D().communicate();
  CuboidGeometry3D<T>& cGeometry = f.getSuperLattice3D().get_cGeometry();
  loadBalancer& load = f.getSuperLattice3D().get_load();

  int numVoxels(0);
  std::vector<T> tmp(this->n, T() );
  for (int i=0; i<this->n; i++) {

    for (int iC=0; iC<load.size(); iC++) {
      int nX = cGeometry.get_cuboid(load.glob(iC)).get_nX();
      int nY = cGeometry.get_cuboid(load.glob(iC)).get_nY();
      int nZ = cGeometry.get_cuboid(load.glob(iC)).get_nZ();
      for (int iX=0;iX<nX;iX++) {
        for (int iY=0;iY<nY;iY++) {
          for (int iZ=0;iZ<nZ;iZ++) {
            int globX = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosX() + iX;
            int globY = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosY() + iY;
            int globZ = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosZ() + iZ;
            if (this->superGeometry.getMaterial(globX, globY, globZ) == material) {
              tmp[i]+=fabs(f(load.glob(iC),iX,iY,iZ)[i]);
              numVoxels++;
            }
          }
        }
      }
    }
#ifdef PARALLEL_MODE_MPI
singleton::mpi().reduceAndBcast(tmp[i], MPI_SUM);
#endif
  }
#ifdef PARALLEL_MODE_MPI
singleton::mpi().reduceAndBcast(numVoxels, MPI_SUM);
#endif
  return tmp;
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperL223D<T,DESCRIPTOR>::SuperL223D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperGeometry3D& _superGeometry, int _material)
  : SuperLatticeF3D<T,DESCRIPTOR>(_f.getSuperLattice3D(),_f.getTargetDim()), f(_f), superGeometry(_superGeometry), material(_material) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperL223D<T,DESCRIPTOR>::operator() (std::vector<int> input) {

  f.getSuperLattice3D().communicate();
  CuboidGeometry3D<T>& cGeometry = f.getSuperLattice3D().get_cGeometry();
  loadBalancer& load = f.getSuperLattice3D().get_load();

  std::vector<T> tmp(this->n, T() );
  for (int i=0; i<this->n; i++) {

    for (int iC=0; iC<load.size(); iC++) {
      int nX = cGeometry.get_cuboid(load.glob(iC)).get_nX();
      int nY = cGeometry.get_cuboid(load.glob(iC)).get_nY();
      int nZ = cGeometry.get_cuboid(load.glob(iC)).get_nZ();
      T weight = pow(this->superGeometry.getSpacing(),3);
      for (int iX=0;iX<nX;iX++) {
        for (int iY=0;iY<nY;iY++) {
          for (int iZ=0;iZ<nZ;iZ++) {
            int globX = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosX() + iX;
            int globY = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosY() + iY;
            int globZ = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosZ() + iZ;
            if (this->superGeometry.getMaterial(globX, globY, globZ) == material) {
              tmp[i]+=f(load.glob(iC),iX,iY,iZ)[i]*f(load.glob(iC),iX,iY,iZ)[i]*weight;
            }
          }
        }
      }
    }
#ifdef PARALLEL_MODE_MPI
singleton::mpi().reduceAndBcast(tmp[i], MPI_SUM);
#endif
  }
  return tmp;
}


template <typename T>
SuperGeometryFaces3D<T>::SuperGeometryFaces3D(SuperGeometry3D& _superGeometry, int _material, const LBconverter<T>& _converter)
  : GenericF<T,int>(7,4), superGeometry(_superGeometry), material(_material), converter(_converter) { }


template <typename T>
std::vector<T> SuperGeometryFaces3D<T>::operator() (std::vector<int> input) {

  int counter[] = {0,0,0,0,0,0,0};
  if (superGeometry.getStatistics().getNVoxel(material)!=0) {
    const int x0 = superGeometry.getStatistics().getMin(material)[0];
    const int y0 = superGeometry.getStatistics().getMin(material)[1];
    const int z0 = superGeometry.getStatistics().getMin(material)[2];
    const int x1 = superGeometry.getStatistics().getMax(material)[0];
    const int y1 = superGeometry.getStatistics().getMax(material)[1];
    const int z1 = superGeometry.getStatistics().getMax(material)[2];

    // Iterate over all cells and count the cells of the face
    for (int iX = x0; iX <= x1; iX++) {
      for (int iY = y0; iY <= y1; iY++) {
        for (int iZ = z0; iZ <= z1; iZ++) {
          // Lock at solid nodes only
          if (superGeometry.getMaterial(iX, iY, iZ) == material) {
            if (superGeometry.getMaterial(iX-1, iY, iZ) == 1) {
              counter[0]++;
            }
            if (superGeometry.getMaterial(iX, iY-1, iZ) == 1) {
              counter[1]++;
            }
            if (superGeometry.getMaterial(iX, iY, iZ-1) == 1) {
              counter[2]++;
            }
            if (superGeometry.getMaterial(iX+1, iY, iZ) == 1) {
              counter[3]++;
            }
            if (superGeometry.getMaterial(iX, iY+1, iZ) == 1) {
              counter[4]++;
            }
            if (superGeometry.getMaterial(iX, iY, iZ+1) == 1) {
              counter[5]++;
            }
          }
        }
      }
    }

    T dx2 = converter.getLatticeL()*converter.getLatticeL();
    std::vector<T> output;
    T total = T();
    for (int i=0;i<6;i++) {
      output.push_back((T) counter[i] * dx2);
      total+=(T) counter[i] * dx2;
    }
    output.push_back(total);
    return output;
    } 
    else {
      return std::vector<T>(7,T());
    }
  }


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticePhysDrag3D<T,DESCRIPTOR>::SuperLatticePhysDrag3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, SuperGeometry3D& _superGeometry, int _material, const LBconverter<T>& _converter)
  : SuperLatticePhysF3D<T,DESCRIPTOR>(_sLattice,_converter,3), superGeometry(_superGeometry), material(_material) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticePhysDrag3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {

  SuperGeometryFaces3D<T> faces(superGeometry, material, this->converter);
  SuperLatticePhysBoundaryForce3D<T,DESCRIPTOR> f(this->sLattice, superGeometry, material, this->converter);
  SuperSum3D<T,DESCRIPTOR> sumF(f, superGeometry, material);

  T factor = 2. / (this->converter.getCharRho() * this->converter.getCharU() * this->converter.getCharU());

  std::vector<T> drag(3,T());
  drag[0] = factor * sumF(input)[0] / faces(input)[0];
  drag[1] = factor * sumF(input)[1] / faces(input)[1];
  drag[2] = factor * sumF(input)[2] / faces(input)[2];
  return drag;
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticePhysCorrDrag3D<T,DESCRIPTOR>::SuperLatticePhysCorrDrag3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, SuperGeometry3D& _superGeometry, int _material, const LBconverter<T>& _converter)
  : SuperLatticePhysF3D<T,DESCRIPTOR>(_sLattice,_converter,3), superGeometry(_superGeometry), material(_material) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticePhysCorrDrag3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {

  SuperGeometryFaces3D<T> faces(superGeometry, material, this->converter);

  SuperLatticePhysCorrBoundaryForce3D<T,DESCRIPTOR> f(this->sLattice, superGeometry, material, this->converter);
  SuperSum3D<T,DESCRIPTOR> sumF(f, superGeometry, material);

  T factor = 2. / (this->converter.getCharRho() * this->converter.getCharU() * this->converter.getCharU());

  std::vector<T> drag(3,T());
  drag[0] = factor * sumF(input)[0] / faces(input)[0];
  drag[1] = factor * sumF(input)[1] / faces(input)[1];
  drag[2] = factor * sumF(input)[2] / faces(input)[2];
  return drag;


}


} // end namespace olb

#endif
