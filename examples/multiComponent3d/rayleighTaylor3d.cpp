/*  Lattice Boltzmann sample, written in C++, using the OpenLB
 *  library
 *
 *  Copyright (C) 2008 Orestis Malaspinas, Andrea Parmigiani
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

#include "olb3D.h"
#include "olb3D.hh"
#include <cstdlib>
#include <iostream>

using namespace olb;
using namespace olb::descriptors;
using namespace olb::graphics;
using namespace std;

typedef double T;
#define DESCRIPTOR ForcedShanChenD3Q19Descriptor


void prepareLattice(BlockStructure3D<T, DESCRIPTOR>& latticeOne,
                    BlockStructure3D<T, DESCRIPTOR>& latticeTwo,
                    Dynamics<T, DESCRIPTOR>& bulkDynamics1,
                    Dynamics<T, DESCRIPTOR>& bulkDynamics2,
                    Dynamics<T, DESCRIPTOR>& bounceBackRho0,
                    Dynamics<T, DESCRIPTOR>& bounceBackRho1){

  // The setup is: periodicity along horizontal direction, bounce-back on top
  // and bottom. The upper half is initially filled with fluid 1 + random noise,
  // and the lower half with fluid 2. Only fluid 1 experiences a forces,
  // directed downwards.


  int nx = latticeOne.getNx();
  int ny = latticeOne.getNy();
  int nz = latticeOne.getNz();

  /// define lattice Dynamics
  latticeOne.defineDynamics(0,nx-1, 0,ny-1, 0,nz-1, &bulkDynamics1);
  latticeTwo.defineDynamics(0,nx-1, 0,ny-1, 0,nz-1, &bulkDynamics2);

  latticeOne.defineDynamics(0,nx-1, 0,ny-1, 0,0,&instances::getBounceBack<T,DESCRIPTOR>());
  latticeTwo.defineDynamics(0,nx-1, 0,ny-1, 0,0,&instances::getBounceBack<T,DESCRIPTOR>());
  latticeOne.defineDynamics(0,nx-1, 0,ny-1, nz-1,nz-1,&instances::getBounceBack<T,DESCRIPTOR>());
  latticeTwo.defineDynamics(0,nx-1, 0,ny-1, nz-1,nz-1,&instances::getBounceBack<T,DESCRIPTOR>());
}

void setBoundaryValues(BlockStructure3D<T, DESCRIPTOR>& latticeOne,
                       BlockStructure3D<T, DESCRIPTOR>& latticeTwo,
                       T force, int iT){

  if(iT==0){
    int nx = latticeOne.getNx();
    int ny = latticeOne.getNy();
    int nz = latticeOne.getNz();
    T noise      = 2.e-1;

    /// for each point set the defineRhou and the Equilibrium
    for (int iX=0; iX<nx; ++iX) {
      for (int iY=0; iY<ny; ++iY) {
        for (int iZ=0; iZ<nz; ++iZ) {
          T f[3] = {0.,0.,-force*(1.+(double)random()/(double)RAND_MAX * noise)};
          T zeroVelocity[3] = {0.,0.,0.};
          T noForce[3] = {0.,0.,0.};
          T rho1 = (T)1;
          T rho2 = (T)1;
          if (iZ>nz/2) {
            rho2 = 0.;
            //rho1 += (double)random()/(double)RAND_MAX * noise;
          }
          else {
            rho1 = 0.;
          }

          Cell<T,DESCRIPTOR>& cell1 = latticeOne.get(iX,iY,iZ);
          cell1.defineRhoU(rho1, zeroVelocity);
          cell1.iniEquilibrium(rho1, zeroVelocity);
          cell1.defineExternalField (
            DESCRIPTOR<T>::ExternalField::forceBeginsAt,
            DESCRIPTOR<T>::ExternalField::sizeOfForce, f );

          Cell<T,DESCRIPTOR>& cell2 = latticeTwo.get(iX,iY,iZ);
          cell2.defineRhoU(rho2, zeroVelocity);
          cell2.iniEquilibrium(rho2, zeroVelocity);
          cell2.defineExternalField (
            DESCRIPTOR<T>::ExternalField::forceBeginsAt,
            DESCRIPTOR<T>::ExternalField::sizeOfForce, noForce );
        }
      }
    }
    /// Make the lattice ready for simulation
    latticeOne.initialize();
    latticeTwo.initialize();
  }
}

void getResults(BlockStructure3D<T, DESCRIPTOR>& latticeTwo,
                BlockStructure3D<T, DESCRIPTOR>& latticeOne, int iT){

  OstreamManager clout(std::cout,"getResults");

  const int saveIter = 100;
  const int vtkIter  = 200;
  const int statIter = 10;

  /// Get statistics
  if (iT%statIter==0 && iT > 0) {
    clout << "averageRhoFluidOne="   << latticeOne.getStatistics().getAverageRho();
    clout << "; averageRhoFluidTwo=" << latticeTwo.getStatistics().getAverageRho() << std::endl;
  }

  /// Writes the Gif files
  if (iT%saveIter==0) {
    OstreamManager cout(std::cout,"plotStatistics");

    cout << "Writing Gif..." << std::endl;
    int nx = latticeOne.getNx();
    ImageWriter<T> imageCreator("leeloo.map");

    imageCreator.writeScaledGif(createFileName("p", iT, 6),
                                latticeOne.getDataAnalysis().getPressure().sliceX(nx/2),
                                400,400);
  }

  /// Writes the VTK files
  if (iT%vtkIter==0) {
    OstreamManager cout(std::cout,"produceVTK");

    cout << "Writing VTK" << std::endl;

    VtkImageOutput3D<T> vtkOut(createFileName("vtk", iT, 7), (T)1);
    vtkOut.writeData<T,float>(latticeOne.getDataAnalysis().getPressure(),
                              "p", (T)1);
  }
}


int main(int argc, char *argv[]){

  /// === 1st Step: Initialization ===

  olbInit(&argc, &argv);
  singleton::directories().setOutputDir("./tmp/");
  OstreamManager clout(std::cout,"main");

  const T omega1 = 1.0;
  const T omega2 = 1.0;
  const int nx   = 75;
  const int ny   = 75;
  const int nz   = 75;
  const T G      = 3.;
  T force        = 2.e-3;

  const int maxIter  = 8000;

  /// === 3rd Step: Prepare Lattice ===

#ifndef PARALLEL_MODE_MPI  // sequential program execution
  MultiDataDistribution3D distribution = createRegularDataDistribution( nx, ny, nz, 1, 1, 1, 1 );
#else                      // parallel program execution
  MultiDataDistribution3D distribution = createRegularDataDistribution( nx, ny, nz );
#endif
  // Use a multi-block lattice even in sequential program execution. In this
  //   way, it is easier to have periodic boundaries, because one can
  //   access periodic data from the lattice envelope
  MultiBlockLattice3D<T, DESCRIPTOR> latticeOne(distribution);
  MultiBlockLattice3D<T, DESCRIPTOR> latticeTwo(distribution);

  BGKdynamics<T, DESCRIPTOR> bulkDynamics1 (
    omega1, instances::getExternalVelocityMomenta<T,DESCRIPTOR>() );
  BGKdynamics<T, DESCRIPTOR> bulkDynamics2 (
    omega2, instances::getExternalVelocityMomenta<T,DESCRIPTOR>() );

  // A bounce-back node with fictitious density 1,
  //   which is experienced by the partner fluid
  BounceBack<T, DESCRIPTOR> bounceBackRho1( 1. );
  // A bounce-back node with fictitious density 0,
  //   which is experienced by the partner fluid
  BounceBack<T, DESCRIPTOR> bounceBackRho0( 0. );

  vector<SpatiallyExtendedObject3D* > partnerForOne;
  partnerForOne.push_back(&latticeTwo);

  std::vector<T> rho0; rho0.push_back(1); rho0.push_back(1);
  ForcedShanChenCouplingGenerator3D<T,DESCRIPTOR> coupling(0,nx-1,0,ny-1, 1,nz-2,G,rho0);
  latticeOne.addLatticeCoupling(coupling, partnerForOne);

  prepareLattice(latticeOne, latticeTwo, bulkDynamics1, bulkDynamics2,
                 bounceBackRho0, bounceBackRho1);

    /// === 4th Step: Main Loop with Timer ===

  int iT = 0;
  clout << "starting simulation..." << endl;
  for (iT=0; iT<maxIter; ++iT) {

    /// === 5th Step: Definition of Initial and Boundary Conditions ===
    setBoundaryValues(latticeOne, latticeTwo, force, iT);

    /// === 6th Step: Collide and Stream Execution ===
    latticeOne.collideAndStream(true);
    latticeTwo.collideAndStream(true);

    latticeOne.executeCoupling();
    latticeTwo.executeCoupling();

    /// === 7th Step: Computation and Output of the Results ===
    getResults(latticeTwo, latticeOne, iT);
  }

}

