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

#ifndef INTERPOLATION_F_3D_HH
#define INTERPOLATION_F_3D_HH

#include<vector>    // for generic i/o

#include "interpolationF3D.h"
#include "functors/genericF.h"
#include "functors/analyticalF.h"
#include "functors/indicatorF.h"
#include "complexGrids/cuboidStructure/superLattice3D.h"
#include "core/lbHelpers.h"  // for computation of lattice rho and velocity


namespace olb {


/// a class used to convert lattice functions to analytical functions
template <typename T, template <typename U> class DESCRIPTOR>
AnalyticalFfromSuperLatticeF3D<T,DESCRIPTOR>::
  AnalyticalFfromSuperLatticeF3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperGeometry3D& _sg, bool _communicateToAll, int _overlap)
  : AnalyticalF3D<T,T>(_f.getTargetDim()), f(_f), sg(_sg), cg(f.getSuperLattice3D().get_cGeometry()), communicateToAll(_communicateToAll), overlap(_overlap) { }


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> AnalyticalFfromSuperLatticeF3D<T,DESCRIPTOR>::operator() (std::vector<T> physC) {

  // convert to lattice coordinates
  T d[3];
  std::vector<int> latticeC(4,int());

  int iX = floor((physC[0] - sg.getPositionX())/(T)sg.getSpacing());
  int iY = floor((physC[1] - sg.getPositionY())/(T)sg.getSpacing());
  int iZ = floor((physC[2] - sg.getPositionZ())/(T)sg.getSpacing());
  d[0] = (physC[0] - sg.getPositionX())/sg.getSpacing() - iX;
  d[1] = (physC[1] - sg.getPositionY())/sg.getSpacing() - iY;
  d[2] = (physC[2] - sg.getPositionZ())/sg.getSpacing() - iZ;

  f.getSuperLattice3D().communicate();

  int locX, locY, locZ;
  int dataSize = 0;
  int dataFound = 0;
  std::vector<T> pOutput;

  for (int iC = 0; iC < f.getSuperLattice3D().get_load().size(); iC++) {
    if (cg.get_cuboid(f.getSuperLattice3D().get_load().glob(iC)).checkPoint(
        iX, iY, iZ, locX, locY, locZ, overlap-1)) {
      locX-=overlap;locY-=overlap;locZ-=overlap;
      latticeC[0] = f.getSuperLattice3D().get_load().glob(iC);
      std::vector<T> output(f(latticeC).size(), T());
      for (unsigned int iD=0; iD<output.size(); iD++) {
        latticeC[1] = locX; latticeC[2] = locY; latticeC[3] = locZ;
        output[iD] += (f(latticeC)[iD]*(1-d[0])*(1-d[1])*(1-d[2]));

        latticeC[1] = locX; latticeC[2] = locY+1; latticeC[3] = locZ;
        output[iD] += (f(latticeC)[iD]*(1-d[0])*(d[1])*(1-d[2]));

        latticeC[1] = locX+1; latticeC[2] = locY; latticeC[3] = locZ;
        output[iD] += (f(latticeC)[iD]*(d[0])*(1-d[1])*(1-d[2]));

        latticeC[1] = locX+1; latticeC[2] = locY+1; latticeC[3] = locZ;
        output[iD] += (f(latticeC)[iD]*(d[0])*(d[1])*(1-d[2]));

        latticeC[1] = locX; latticeC[2] = locY; latticeC[3] = locZ+1;
        output[iD] += (f(latticeC)[iD]*(1-d[0])*(1-d[1])*(d[2]));

        latticeC[1] = locX; latticeC[2] = locY+1; latticeC[3] = locZ+1;
        output[iD] += (f(latticeC)[iD]*(1-d[0])*(d[1])*(d[2]));

        latticeC[1] = locX+1; latticeC[2] = locY; latticeC[3] = locZ+1;
        output[iD] += (f(latticeC)[iD]*(d[0])*(1-d[1])*(d[2]));

        latticeC[1] = locX+1; latticeC[2] = locY+1; latticeC[3] = locZ+1;
        output[iD] += (f(latticeC)[iD]*(d[0])*(d[1])*(d[2]));
      }
    dataSize = f(latticeC).size();
    dataFound = 1;
    pOutput = output; 
    }
  }

#ifdef PARALLEL_MODE_MPI
  if(communicateToAll) {
    singleton::mpi().reduceAndBcast(dataFound, MPI_SUM);
    singleton::mpi().reduceAndBcast(dataSize, MPI_SUM);
    dataSize/=dataFound;
    if (pOutput.size()==0) {
      for (int iD=0; iD<dataSize; iD++) {
        pOutput.push_back(T());
      }
    }
    for (int iD=0; iD<dataSize; iD++) {
      singleton::mpi().reduceAndBcast(pOutput[iD], MPI_SUM);
    }
    for (int iD=0; iD<dataSize; iD++) {
      pOutput[iD]/=dataFound;
    }
  }
#endif

  return pOutput;
};



/// a class used to convert analytical functions to lattice functions
/// input functions are interpreted as SI->SI units, the resulting lattice
/// function will map lattice->lattice units
template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeFfromAnalyticalF3D<T,DESCRIPTOR>::
  SuperLatticeFfromAnalyticalF3D(AnalyticalF3D<T,T>& _f, SuperLattice3D<T,DESCRIPTOR>& _sLattice, SuperGeometry3D& _sg, CuboidGeometry3D<T>& _cg)
    : SuperLatticeF3D<T,DESCRIPTOR>(_sLattice,_f.getTargetDim()), f(_f), sg(_sg), cg(_cg) { }

template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticeFfromAnalyticalF3D<T,DESCRIPTOR>::operator() (std::vector<int> input) {

  // convert to global coordinates
  T iX = cg.get_cuboid(input[0]).get_globPosX()+input[1];
  T iY = cg.get_cuboid(input[0]).get_globPosY()+input[2];
  T iZ = cg.get_cuboid(input[0]).get_globPosZ()+input[3];

  // convert to physical coordinates
  std::vector<T> physCoordinate;
  physCoordinate.push_back(this->sg.physCoords(iX,iY,iZ)[0]);
  physCoordinate.push_back(this->sg.physCoords(iX,iY,iZ)[1]);
  physCoordinate.push_back(this->sg.physCoords(iX,iY,iZ)[2]);

  return f(physCoordinate);
};


} // end namespace olb

#endif
