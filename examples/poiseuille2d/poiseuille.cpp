/*  Lattice Boltzmann sample, written in C++, using the OpenLB
 *  library
 *
 *  Copyright (C) 2006, 2007, 2012 Jonas Latt, Mathias J. Krause
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

#include "olb2D.h"
#ifndef OLB_PRECOMPILED // Unless precompiled version is used,
#include "olb2D.hh"   // include full template code
#endif
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace olb;
using namespace olb::descriptors;
using namespace olb::graphics;
using namespace std;

typedef enum {velocity, pressure} BoundaryType;

typedef double T;
#define DESCRIPTOR D2Q9Descriptor

T poiseuilleVelocity(int iY, LBconverter<T> const& converter) {
  T y = converter.physLength(iY);
  return 4.*converter.getLatticeU() * (y-y*y);
}

T poiseuillePressure(int iX, LBconverter<T> const& converter) {
  T Lx = converter.numCells(2);
  T Ly = converter.numCells(1);
  return 8.*converter.getLatticeNu()*converter.getLatticeU() / (Ly*Ly) * (Lx/(T)2-(T)iX);
}


void prepareLattice(LBconverter<T> const& converter,
                    BlockStructure2D<T, DESCRIPTOR>& lattice,
                    Dynamics<T, DESCRIPTOR>& bulkDynamics,
                    OnLatticeBoundaryCondition2D<T,DESCRIPTOR>& boundaryCondition,
                    BoundaryType boundaryType ){

  int nx = lattice.getNx();
  int ny = lattice.getNy();
  T   omega = converter.getOmega();

  /// define lattice Dynamics
  lattice.defineDynamics(0,nx-1, 0,ny-1, &bulkDynamics);

  /// sets boundary
  boundaryCondition.addVelocityBoundary1P(1,nx-2,ny-1,ny-1, omega);
  boundaryCondition.addVelocityBoundary1N(1,nx-2,   0,   0, omega);

  if (boundaryType==velocity) {
    boundaryCondition.addVelocityBoundary0N(0,0, 1, ny-2, omega);
    boundaryCondition.addVelocityBoundary0P(nx-1,nx-1, 1, ny-2, omega);
  }
  else {
    boundaryCondition.addPressureBoundary0N(0,0, 1, ny-2, omega);
    boundaryCondition.addPressureBoundary0P(nx-1,nx-1, 1, ny-2, omega);
  }

  /// set Velocity
  boundaryCondition.addExternalVelocityCornerNN(0,0, omega);
  boundaryCondition.addExternalVelocityCornerNP(0,ny-1, omega);
  boundaryCondition.addExternalVelocityCornerPN(nx-1,0, omega);
  boundaryCondition.addExternalVelocityCornerPP(nx-1,ny-1, omega);
}

void setBoundaryValues(LBconverter<T> const&converter,
                       BlockStructure2D<T,DESCRIPTOR>& lattice, int iT){

  int nx = lattice.getNx();
  int ny = lattice.getNy();

  if(iT==0){
    for (int iX=0; iX<nx; ++iX) {
      for (int iY=0; iY<ny; ++iY) {
        T u[2] = {poiseuilleVelocity(iY, converter),0.};
        T rho = (T)1 + poiseuillePressure(iX, converter) * DESCRIPTOR<T>::invCs2;
        lattice.get(iX,iY).defineRhoU(rho, u);
        lattice.get(iX,iY).iniEquilibrium(rho, u);
      }
    }
    /// Make the lattice ready for simulation
    lattice.initialize();
  }
}

void getResults(BlockStructure2D<T,DESCRIPTOR>& lattice,
                LBconverter<T>& converter, int iT) {

  const T lx   = 2.;
  const T ly   = 1.;

  const int saveIter = 2000;
  const int statIter = 100;

  const int imSize = 400;

  if (iT%statIter==0) {
    T middleU[2];
    lattice.get(converter.numNodes(lx)/2, converter.numNodes(ly)/2).computeU(middleU);
    OstreamManager cout(std::cout,"plotStatistics");
    T dx = converter.getDeltaX();
    T dt = converter.getDeltaT();
    cout << "iteration=" << setw(5) << iT;
    cout << "; t=" << setprecision(3) << setw(6)
         << iT*converter.getDeltaT();
    cout << "; E=" << setprecision(10) << setw(15)
         << lattice.getStatistics().getAverageEnergy()*dx*dx/dt/dt;
    cout << "; rho=" << setprecision(8) << setw(11)
         << lattice.getStatistics().getAverageRho();
    cout << "; uMax= " << setprecision(8) << setw(11)
         << middleU[0]*dx/dt;
    cout << endl;
  }

  if (iT%saveIter==0) {
    DataAnalysisBase2D<T,DESCRIPTOR> const& analysis = lattice.getDataAnalysis();

    ImageWriter<T> imageWriter("leeloo");
    imageWriter.writeScaledGif(createFileName("p", iT, 6),
                               analysis.getPressure(), imSize, imSize);
    imageWriter.writeScaledGif(createFileName("u", iT, 6),
                               analysis.getVelocityNorm(), imSize, imSize);
    ofstream *ofile = 0;
    if (singleton::mpi().isMainProcessor()) {
      ofile = new ofstream((singleton::directories().getLogOutDir()+"centerVel.dat").c_str());
    }
    for (int iY=0; iY<lattice.getNy(); ++iY) {
      T dx = converter.getDeltaX();
      T dt = converter.getDeltaT();
      T analytical = poiseuilleVelocity(iY, converter);
      T numerical[2];
      lattice.get(lattice.getNx()/2, iY).computeU(numerical);

      if (singleton::mpi().isMainProcessor()) {
        *ofile << iY*dx << " " << analytical*dx/dt
               << " " << numerical[0]*dx/dt << "\n";
      }
    }
    delete ofile;
  }
}

int main(int argc, char* argv[]) {

  /// === 1st Step: Initialization ===
  olbInit(&argc, &argv);
  singleton::directories().setOutputDir("./tmp/");

  const BoundaryType boundaryType = velocity;
  const T uMax = 0.02;
  const T Re   = 10.;
  const int N  = 50;

  const T lx   = 2.;
  const T ly   = 1.;

  const int maxIter  = 20000;


  LBconverter<T> converter(
    (int) 2,                               // dim
    1./N,                                  // latticeL_
    uMax,                                  // latticeU_
    (T)   1./Re,                           // charNu_
    (T)   1.                               // charL_ = 1,
  );
  writeLogFile(converter, "poiseuille2d");

  /// === 3rd Step: Prepare Lattice ===

#ifndef PARALLEL_MODE_MPI  // sequential program execution
  BlockLattice2D<T, DESCRIPTOR> lattice(converter.numNodes(lx), converter.numNodes(ly) );
#else                      // parallel program execution
  MultiDataDistribution2D distribution =
    createRegularDataDistribution(converter.numNodes(lx), converter.numNodes(ly) );
  MultiBlockLattice2D<T, DESCRIPTOR> lattice(distribution);
#endif

  // choose between local and non-local boundary condition
  OnLatticeBoundaryCondition2D<T,DESCRIPTOR>*
  boundaryCondition = createInterpBoundaryCondition2D(lattice);
  // boundaryCondition = createLocalBoundaryCondition2D(lattice);

  BGKdynamics<T, DESCRIPTOR> bulkDynamics (
    converter.getOmega(),
    instances::getBulkMomenta<T,DESCRIPTOR>()
  );

  prepareLattice(converter, lattice, bulkDynamics, *boundaryCondition, boundaryType);

  /// === 4th Step: Main Loop with Timer ===

  for (int iT=0; iT<maxIter; ++iT) {

    /// === 5th Step: Definition of Initial and Boundary Conditions ===
    setBoundaryValues(converter, lattice, iT);

    /// === 6th Step: Collide and Stream Execution ===
    lattice.collideAndStream();

    /// === 7th Step: Computation and Output of the Results ===
    getResults(lattice, converter, iT);

  }

  delete boundaryCondition;
}

