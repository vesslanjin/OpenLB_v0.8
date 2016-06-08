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

#ifndef SUPER_LATTICE_LOCAL_F_3D_HH
#define SUPER_LATTICE_LOCAL_F_3D_HH

#include<vector>    // for generic i/o
#include<cmath>     // for lpnorm

#include "superLatticeLocalF3D.h"

#include "superLatticeBaseF3D.h"
#include "functors/genericF.h"
#include "functors/analyticalF.h"
#include "functors/indicatorF.h"
#include "complexGrids/cuboidStructure/superLattice3D.h"
#include "core/lbHelpers.h"  // for computation of lattice rho and velocity

namespace olb {


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeDissipation3D<T,DESCRIPTOR>::SuperLatticeDissipation3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, const LBconverter<T>& _converter)
  : SuperLatticeF3D<T,DESCRIPTOR>(_sLattice,1), converter(_converter) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticeDissipation3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {
  int globIC = input[0]; int locix= input[1]; int lociy= input[2]; int lociz= input[3];
  if ( this->sLattice.get_load().rank(globIC) == singleton::mpi().getRank() ) {
    // local coords are given, fetch local cell and compute value(s)
    T rho, uTemp[DESCRIPTOR<T>::d], pi[util::TensorVal<DESCRIPTOR<T> >::n];
    T overlap = this->sLattice.get_overlap();
    this->sLattice.get_blockLattice(this->sLattice.get_load().loc(globIC)).get(locix+overlap, lociy+overlap, lociz+overlap).computeAllMomenta(rho, uTemp, pi);

    T PiNeqNormSqr = pi[0]*pi[0] + 2.*pi[1]*pi[1] + pi[2]*pi[2];
    if (util::TensorVal<DESCRIPTOR<T> >::n == 6)
      PiNeqNormSqr += pi[2]*pi[2] + pi[3]*pi[3] + 2.*pi[4]*pi[4] +pi[5]*pi[5];

    T nuLattice = converter.getLatticeNu();
    T omega = converter.getOmega();
    T finalResult = PiNeqNormSqr*nuLattice*pow(omega*DESCRIPTOR<T>::invCs2,2)/rho/2.;

    return std::vector<T>(1,finalResult);
  } else {
    return std::vector<T>(); // empty vector
  }
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeDensity3D<T,DESCRIPTOR>::SuperLatticeDensity3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice)
  : SuperLatticeF3D<T,DESCRIPTOR>(_sLattice,1) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticeDensity3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {
  int globIC = input[0]; int locix= input[1]; int lociy= input[2]; int lociz= input[3];
  if ( this->sLattice.get_load().rank(globIC) == singleton::mpi().getRank() ) {
    // local coords are given, fetch local cell and compute value(s)

    T overlap = this->sLattice.get_overlap();
    return std::vector<T>(1, this->sLattice
      .get_blockLattice(this->sLattice.get_load().loc(globIC)).get(locix+overlap, lociy+overlap, lociz+overlap)
      .computeRho() );
  } else {
    return std::vector<T>(); // empty vector
  }
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeVelocity3D<T,DESCRIPTOR>::SuperLatticeVelocity3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice)
  : SuperLatticeF3D<T,DESCRIPTOR>(_sLattice,3) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticeVelocity3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {
  int globIC = input[0]; int locix= input[1]; int lociy= input[2]; int lociz= input[3];
  if ( this->sLattice.get_load().rank(globIC) == singleton::mpi().getRank() ) {
    T rho, u[3];
    T overlap = this->sLattice.get_overlap();
    this->sLattice.get_blockLattice(this->sLattice.get_load().loc(globIC))
      .get(locix+overlap, lociy+overlap, lociz+overlap).computeRhoU(rho,u);
    std::vector<T> v(u, u+3);  // first adress, last adress
    return v;
  } else {
    return std::vector<T>();
  }
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeGeometry3D<T,DESCRIPTOR>::SuperLatticeGeometry3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, SuperGeometry3D& _superGeometry)
  : SuperLatticeF3D<T,DESCRIPTOR>(_sLattice,1), superGeometry(_superGeometry) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticeGeometry3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {
  int globIC = input[0]; int locix= input[1]; int lociy= input[2]; int lociz= input[3];
  if ( this->sLattice.get_load().rank(globIC) == singleton::mpi().getRank() ) {
    // local coords are given, fetch local cell and compute value(s)

    int globX = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosX() + locix;
    int globY = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosY() + lociy;
    int globZ = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosZ() + lociz;

    return std::vector<T>(1, this->superGeometry.getMaterial(globX, globY, globZ) );
  } else {
    return std::vector<T>(); // empty vector
  }
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeRank3D<T,DESCRIPTOR>::SuperLatticeRank3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice)
  : SuperLatticeF3D<T,DESCRIPTOR>(_sLattice,1) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticeRank3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {
  int globIC = input[0]; // int locix= input[1]; int lociy= input[2]; int lociz= input[3];
  if ( this->sLattice.get_load().rank(globIC) == singleton::mpi().getRank() ) {
    T rank[1];
    rank[0] = singleton::mpi().getRank() + 1;
    std::vector<T> out(rank, rank+1);  // first adress, last adress
    return out;
  } else {
    return std::vector<T>();
  }
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeCuboid3D<T,DESCRIPTOR>::SuperLatticeCuboid3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice)
  : SuperLatticeF3D<T,DESCRIPTOR>(_sLattice,1) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticeCuboid3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {
  int globIC = input[0]; // int locix= input[1]; int lociy= input[2]; int lociz= input[3];
  if ( this->sLattice.get_load().rank(globIC) == singleton::mpi().getRank() ) {
    T cuboid[1];
    cuboid[0] = globIC+1;
    std::vector<T> out(cuboid, cuboid+1);  // first adress, last adress
    return out;
  } else {
    return std::vector<T>();
  }
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticePhysPressure3D<T,DESCRIPTOR>::SuperLatticePhysPressure3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, const LBconverter<T>& _converter)
  : SuperLatticePhysF3D<T,DESCRIPTOR>(_sLattice,_converter,1) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticePhysPressure3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {

  int globIC = input[0]; int locix= input[1]; int lociy= input[2]; int lociz= input[3];
  if ( this->sLattice.get_load().rank(globIC) == singleton::mpi().getRank() ) {
    // local coords are given, fetch local cell and compute value(s)
    T overlap = this->sLattice.get_overlap();
    return std::vector<T>(1, this->converter.physPressureFromRho(this->sLattice
      .get_blockLattice(this->sLattice.get_load().loc(globIC)).get(locix+overlap, lociy+overlap, lociz+overlap).computeRho()));
  } else {
    return std::vector<T>(); // empty vector
  }
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticePhysVelocity3D<T,DESCRIPTOR>::SuperLatticePhysVelocity3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, const LBconverter<T>& _converter)
  : SuperLatticePhysF3D<T,DESCRIPTOR>(_sLattice,_converter,3) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticePhysVelocity3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {
  int globIC = input[0]; int locix= input[1]; int lociy= input[2]; int lociz= input[3];
  if ( this->sLattice.get_load().rank(globIC) == singleton::mpi().getRank() ) {
    T rho, u[3];
    T overlap = this->sLattice.get_overlap();  
    this->sLattice.get_blockLattice(this->sLattice.get_load().loc(globIC))
      .get(locix+overlap, lociy+overlap, lociz+overlap).computeRhoU(rho,u);     
    std::vector<T> v(u, u+3);  // first adress, last adress
    u[0]=this->converter.physVelocity(v[0]);
    u[1]=this->converter.physVelocity(v[1]);
    u[2]=this->converter.physVelocity(v[2]);
    std::vector<T> y(u, u+3);
    return y; 
  } else {
    return std::vector<T>();
  }
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticePhysBoundaryForce3D<T,DESCRIPTOR>::SuperLatticePhysBoundaryForce3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, SuperGeometry3D& _superGeometry, int _material, const LBconverter<T>& _converter)
  : SuperLatticePhysF3D<T,DESCRIPTOR>(_sLattice,_converter,3), superGeometry(_superGeometry), material(_material) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticePhysBoundaryForce3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {
  int globIC = input[0]; int locix= input[1]; int lociy= input[2]; int lociz= input[3];

  if ( this->sLattice.get_load().rank(globIC) == singleton::mpi().getRank() ) {
    int globX = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosX() + locix;
    int globY = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosY() + lociy;
    int globZ = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosZ() + lociz;
    std::vector<T> force(3, T()); 
    if(superGeometry.getMaterial(globX, globY, globZ) == material) {
      for (int iPop = 1; iPop < DESCRIPTOR<T>::q ; ++iPop){
        // Get direction
        const int* c = DESCRIPTOR<T>::c[iPop];
        // Get next cell located in the current direction
        // Check if the next cell is a fluid node
        if (superGeometry.getMaterial(globX + c[0], globY + c[1], globZ + c[2]) == 1) {
          T overlap = this->sLattice.get_overlap();
          // Get f_q of next fluid cell where l = opposite(q)
          T f = this->sLattice.get_blockLattice(this->sLattice.get_load().loc(globIC)).get(locix+overlap + c[0], lociy+overlap + c[1], lociz+overlap + c[2])[iPop];
          // Get f_l of the boundary cell
          // Add f_q and f_opp
          f += this->sLattice.get_blockLattice(this->sLattice.get_load().loc(globIC)).get(locix+overlap, lociy+overlap, lociz+overlap)[util::opposite<DESCRIPTOR<T> >(iPop)];
          // Update force
          force[0] -= c[0]*f;
          force[1] -= c[1]*f;
          force[2] -= c[2]*f;
        }
      }
      force[0]=this->converter.physForce(force[0]);
      force[1]=this->converter.physForce(force[1]);
      force[2]=this->converter.physForce(force[2]);
      return force;
    }
    else {
      return force;
    }
  }
  else {
    return std::vector<T>();
  }
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticePhysCorrBoundaryForce3D<T,DESCRIPTOR>::SuperLatticePhysCorrBoundaryForce3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice, SuperGeometry3D& _superGeometry, int _material, const LBconverter<T>& _converter)
  : SuperLatticePhysF3D<T,DESCRIPTOR>(_sLattice,_converter,3), superGeometry(_superGeometry), material(_material) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticePhysCorrBoundaryForce3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {
  int globIC = input[0]; int locix= input[1]; int lociy= input[2]; int lociz= input[3];

  std::vector<T> force(3, T());
  if ( this->sLattice.get_load().rank(globIC) == singleton::mpi().getRank() ) {
    int globX = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosX() + locix;
    int globY = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosY() + lociy;
    int globZ = (int)this->sLattice.get_cGeometry().get_cuboid(globIC).get_globPosZ() + lociz;
    if(superGeometry.getMaterial(globX, globY, globZ) == material) {
      for (int iPop = 1; iPop < DESCRIPTOR<T>::q ; ++iPop){
        // Get direction
        const int* c = DESCRIPTOR<T>::c[iPop];
        // Get next cell located in the current direction
        // Check if the next cell is a fluid node
        if (superGeometry.getMaterial(globX + c[0], globY + c[1], globZ + c[2]) == 1) {
          T overlap = this->sLattice.get_overlap(); 
          // Get f_q of next fluid cell where l = opposite(q)
          T f = this->sLattice.get_blockLattice(this->sLattice.get_load().loc(globIC)).get(locix+overlap + c[0], lociy+overlap + c[1], lociz+overlap + c[2])[iPop];
          // Get f_l of the boundary cell
          // Add f_q and f_opp
          f += this->sLattice.get_blockLattice(this->sLattice.get_load().loc(globIC)).get(locix+overlap, lociy+overlap, lociz+overlap)[util::opposite<DESCRIPTOR<T> >(iPop)];
          // Update force
          force[0] -= c[0]*(f-2.*DESCRIPTOR<T>::t[iPop]);
          force[1] -= c[1]*(f-2.*DESCRIPTOR<T>::t[iPop]);
          force[2] -= c[2]*(f-2.*DESCRIPTOR<T>::t[iPop]);
        }
      }
      force[0]=this->converter.physForce(force[0]);
      force[1]=this->converter.physForce(force[1]);
      force[2]=this->converter.physForce(force[2]);
      return force;
    }
    else {
      return force;
    }
  }
  else {
    return force;
  }
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticePorosity3D<T,DESCRIPTOR>::SuperLatticePorosity3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice,
                     SuperGeometry3D& _superGeometry,
                     int _material,
                     const LBconverter<T>& _converter)
: SuperLatticePhysF3D<T,DESCRIPTOR>(_sLattice,_converter,1), superGeometry(_superGeometry), material(_material) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticePorosity3D<T,DESCRIPTOR>::operator()(std::vector<int> input) {
  int globIC = input[0]; int locix= input[1]; int lociy= input[2]; int lociz= input[3];

  T* value = new T[1];
  T overlap = this->sLattice.get_overlap();
  this->sLattice.get_blockLattice(this->sLattice.get_load().loc(globIC)).get(locix+overlap, lociy+overlap, lociz+overlap).computeExternalField(0,1,value);
  std::vector<T> result(1,value[0]);
  delete value;
  return result;
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticePhysPermeability3D<T,DESCRIPTOR>::SuperLatticePhysPermeability3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice,
                               SuperGeometry3D& _superGeometry,
                               int _material,
                               const LBconverter<T>& _converter)
: SuperLatticePhysF3D<T,DESCRIPTOR>(_sLattice,_converter,1), superGeometry(_superGeometry),  material(_material) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticePhysPermeability3D<T,DESCRIPTOR>::operator()(std::vector<int> input) {
  int globIC = input[0]; int locix= input[1]; int lociy= input[2]; int lociz= input[3];

  T* value = new T[1];
  T overlap = this->sLattice.get_overlap();
  this->sLattice.get_blockLattice(this->sLattice.get_load().loc(globIC)).get(locix+overlap, lociy+overlap, lociz+overlap).computeExternalField(0,1,value);
  std::vector<T> result(1,this->converter.physPermeability(value[0]));
  delete value;
  if (!(result[0]<42)&&!(result[0]>42)&&!(result[0]==42)) result[0] = 999999;
  if (isinf(result[0])) result[0] = 1e6;
  return result;
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticePhysDarcyForce3D<T,DESCRIPTOR>::SuperLatticePhysDarcyForce3D(SuperLattice3D<T,DESCRIPTOR>& _sLattice,
                             SuperGeometry3D& _superGeometry,
                             int _material,
                             const LBconverter<T>& _converter)
: SuperLatticePhysF3D<T,DESCRIPTOR>(_sLattice,_converter,3), superGeometry(_superGeometry), material(_material) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticePhysDarcyForce3D<T,DESCRIPTOR>::operator()(std::vector<int> input) {
  SuperLatticePhysPermeability3D<T,DESCRIPTOR> permeability(this->sLattice,this->superGeometry,this->material,this->converter);
  SuperLatticeVelocity3D<T,DESCRIPTOR> velocity(this->sLattice);

  T nu = this->converter.getCharNu();
  T K = permeability(input)[0];
  std::vector<T> u = velocity(input);

  std::vector<T> result(3,0);
  result[0] = -nu/K*u[0];
  result[1] = -nu/K*u[1];
  result[2] = -nu/K*u[2];

  return result;
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeAverage3D<T,DESCRIPTOR>::SuperLatticeAverage3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperGeometry3D& _superGeometry, int _material, T _radius)
  : SuperLatticeF3D<T,DESCRIPTOR>(_f.getSuperLattice3D(), _f.getTargetDim()), f(_f), superGeometry(_superGeometry), material(_material), radius(_radius) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticeAverage3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {
  CuboidGeometry3D<T>& cGeometry = f.getSuperLattice3D().get_cGeometry();
  loadBalancer& load = f.getSuperLattice3D().get_load();

  //create boolean indicator functor isInSphere
  std::vector<T> center(3,0);
  center[0] = (int)cGeometry.get_cuboid(load.glob(input[0])).get_globPosX() + input[1];
  center[1] = (int)cGeometry.get_cuboid(load.glob(input[0])).get_globPosY() + input[2];
  center[2] = (int)cGeometry.get_cuboid(load.glob(input[0])).get_globPosZ() + input[3];
  SphereAnalyticalF3D<bool,T> isInSphere(center,radius);

  // iterate over all cuboids & points and test for material && isInSphere
  std::vector<T> tmp( this->n, T() );
  int numVoxels(0);
  if (this->superGeometry.getMaterial(center[0],center[1],center[2]) == material) {
    for (int iC=0; iC<load.size(); iC++) {
      int nX = cGeometry.get_cuboid(load.glob(iC)).get_nX();
      int nY = cGeometry.get_cuboid(load.glob(iC)).get_nY();
      int nZ = cGeometry.get_cuboid(load.glob(iC)).get_nZ();
      for (int iX=0;iX<nX;iX++) {
        for (int iY=0;iY<nY;iY++) {
          for (int iZ=0;iZ<nZ;iZ++) {
            std::vector<T> glob(3,0);
            glob[0] = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosX() + iX;
            glob[1] = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosY() + iY;
            glob[2] = (int)cGeometry.get_cuboid(load.glob(iC)).get_globPosZ() + iZ;
            if (this->superGeometry.getMaterial(glob[0],glob[1],glob[2]) == material
                && isInSphere(glob)[0]==true) {
              for (unsigned iD=0; iD<f(load.glob(0),0,0,0).size(); iD++) {
                tmp[iD]+=f(load.glob(iC),iX,iY,iZ)[iD];
              }
              numVoxels++;
            }
          }
        }
      }
    }

#ifdef PARALLEL_MODE_MPI
    singleton::mpi().reduceAndBcast(numVoxels, MPI_SUM);
#endif
    for (int iD=0; iD<f.getTargetDim(); iD++) {
#ifdef PARALLEL_MODE_MPI
      singleton::mpi().reduceAndBcast(tmp[iD], MPI_SUM);
#endif
      if (numVoxels>0) {
        tmp[iD] /= numVoxels;
      }
    }
  }
  return tmp;
}


template <typename T, template <typename U> class DESCRIPTOR>
SuperL2Norm3D<T,DESCRIPTOR>::SuperL2Norm3D(SuperLatticeF3D<T,DESCRIPTOR>& _f)
  : SuperLatticeF3D<T,DESCRIPTOR>(_f.getSuperLattice3D(),1), f(_f) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperL2Norm3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {
  std::vector<T> data = f(input);
  std::vector<T> tmp(1,0);
  for (unsigned i=0; i<data.size(); i++) {
    tmp[0] += data[i]*data[i];
  }
  tmp[0] = sqrt(tmp[0]);
  return tmp;
}


} // end namespace olb

#endif
