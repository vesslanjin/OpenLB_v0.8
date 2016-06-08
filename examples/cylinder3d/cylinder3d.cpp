/*  Lattice Boltzmann sample, written in C++, using the OpenLB
 *  library
 *
 *  Copyright (C) 2011-2013 Mathias J. Krause, Thomas Henn, Tim Dornieden
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

/* cylinder3d.cpp:
 * This example examines a steady flow past a cylinder placed in a
 * channel. At the inlet, a Poiseuille profile is imposed on the velocity,
 * where as the outlet implements an outflow condition: grad_n u = 0 and
 * rho = 1. It also shows the usage of the STL-reader and explains how
 * to set boundary conditions automatically.
 */

#include "olb3D.h"
#ifndef OLB_PRECOMPILED // Unless precompiled version is used
#include "olb3D.hh"     // Include full template code
#endif
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace olb;
using namespace olb::descriptors;
using namespace olb::graphics;
using namespace olb::util;
using namespace std;

typedef double T;
#define DESCRIPTOR D3Q19Descriptor
#define time_sec() ({struct timeval tp; gettimeofday(&tp, 0); tp.tv_sec + tp. tv_usec * 1.e-6;})

int N = 1; // resolution of the model

void prepareGeometry( LBconverter<T> const& converter, STLreader<T>& stlReader,
                      SuperGeometry3D& superGeometry, CuboidGeometry3D<T>& cuboidGeometry,
                      heuristicLoadBalancer<T>& loadBalancer ) {

  OstreamManager clout(std::cout,"prepareGeometry");
  clout << "Prepare Geometry ..." << std::endl;

  /// Sets the material number outside the surface
  stlReader.setOuterMaterialNo(2);

  /// Reads the stl-file and stores it in blockGeometry
  stlReader.read(superGeometry, 0u, 250*N);

  clout << "Grid Size: Nx=" << superGeometry.getNx() << "; Ny="  << superGeometry.getNy() << "; Nz=" << superGeometry.getNz() << endl;

  /// Set material number for inflow
  for (int iY = 1; iY < superGeometry.getNy() - 1; iY++) {
    for (int iZ = 1; iZ < superGeometry.getNz() - 1; iZ++) {
      superGeometry.setMaterial(0, iY, iZ, 3);
    }
  }
  /// Set material number for outflow
  for (int iY = 1; iY < superGeometry.getNy() - 1; iY++) {
    for (int iZ = 1; iZ < superGeometry.getNz() - 1; iZ++) {
      superGeometry.setMaterial(superGeometry.getNx()-1, iY, iZ, 4);
    }
  }
  /// Set material number for cylinder
  for (int iX = 1; iX < superGeometry.getNx() - 1; iX++) {
    for (int iY = 1; iY < superGeometry.getNy() - 1; iY++) {
      for (int iZ = 1; iZ < superGeometry.getNz() - 1; iZ++) {
        if (superGeometry.getMaterial(iX, iY, iZ) == 2) {
          superGeometry.setMaterial(iX, iY, iZ, 5);
        }
      }
    }
  }


  /// Removes all not needed boundary voxels outside the surface
  superGeometry.clean();
  /// Removes all not needed boundary voxels inside the surface
  superGeometry.innerClean();
  superGeometry.checkForErrors();

  int noCuboids = singleton::mpi().getSize();
  if (noCuboids<7) noCuboids = 7;

  //delete cuboidGeometry;
  cuboidGeometry.reInit(superGeometry.getPositionX(), superGeometry.getPositionY(), superGeometry.getPositionZ(), superGeometry.getSpacing(), superGeometry.getNx(), superGeometry.getNy(), superGeometry.getNz(), noCuboids );

  //delete loadBalancer;
  loadBalancer.reInit(cuboidGeometry, superGeometry);
  stlReader.splitGeometry(cuboidGeometry, loadBalancer);

  clout << "Prepare Geometry ... OK" << std::endl;
  return;
}


void prepareLattice(SuperLattice3D<T,DESCRIPTOR>& sLattice,
                 LBconverter<T> const& converter,
                 Dynamics<T, DESCRIPTOR>& bulkDynamics,
                 sOnLatticeBoundaryCondition3D<T,DESCRIPTOR>& bc,
                 sOffLatticeBoundaryCondition3D<T,DESCRIPTOR>& offBc,
                 STLreader<T>& stlReader,
                 SuperGeometry3D& superGeometry) {

  OstreamManager clout(std::cout,"prepareLattice");
  clout << "Prepare Lattice ..." << std::endl;

  const T omega = converter.getOmega();

  if (singleton::mpi().isMainProcessor()) {
    superGeometry.getStatistics().countVoxel();
  }

  /// Material=0 -->do nothing
  sLattice.defineDynamics(superGeometry, 0, &instances::getNoDynamics<T, DESCRIPTOR>());

  /// Material=1 -->bulk dynamics
  sLattice.defineDynamics(superGeometry, 1, &bulkDynamics);

  /// Material=2 -->bounce back
  sLattice.defineDynamics(superGeometry, 2, &instances::getBounceBack<T, DESCRIPTOR>());

  /// Material=3 -->bulk dynamics (inflow)
  sLattice.defineDynamics(superGeometry, 3, &bulkDynamics);

  /// Material=4 -->bulk dynamics (outflow)
  sLattice.defineDynamics(superGeometry, 4, &bulkDynamics);

  /// Setting of the boundary conditions
  bc.addVelocityBoundary(superGeometry, 3, omega);
  bc.addPressureBoundary(superGeometry, 4, omega);

  /// Material=5 -->bouzidi
  sLattice.defineDynamics(superGeometry, 5, &instances::getNoDynamics<T,DESCRIPTOR>());
  offBc.addZeroVelocityBoundary(superGeometry, 5, stlReader);

  clout << "Prepare Lattice ... OK" << std::endl;
  return;
}

/// Generates a slowly increasing sinuidal inflow for the first iTMax timesteps
void setBoundaryValues(SuperLattice3D<T, DESCRIPTOR>& sLattice,
                   LBconverter<T> const& converter, int iT, T maxPhysT,
                   SuperGeometry3D& superGeometry) {

  OstreamManager clout(std::cout,"setBoundaryValues");

  // No of time steps for smooth start-up
  int iTmaxStart = converter.numTimeSteps(maxPhysT*0.8);
  int iTperiod = 50;

  if (iT==0) {
    const int nx = superGeometry.getNx();
    const int ny = superGeometry.getNy();
    const int nz = superGeometry.getNz();
    T vel_a[] = { T(), T(), T()};
    sLattice.defineRhoU    (0, nx-1, 0, ny-1, 0, nz-1, (T)1, vel_a);
    sLattice.iniEquilibrium(0, nx-1, 0, ny-1, 0, nz-1, (T)1, vel_a);

    /// Make the lattice ready for simulation
    sLattice.initialize();
  }

  else if (iT%iTperiod==0 && iT<= iTmaxStart) {
    //clout << "Set Boundary Values ..." << std::endl;

    //SinusStartScale<T,int> startScale(iTmaxStart, (T) 1);
    PolynomialStartScale<T,int> startScale(iTmaxStart, T(1));
    std::vector<int> iTvec(1,iT);
    T frac = startScale(iTvec)[0];

    // Creates and sets the Poiseuille inflow profile using functors
    std::vector<T> maxVelocity(3,0);
    maxVelocity[0] = 2.25*frac*converter.getLatticeU();

    RectanglePoiseuille3D<T> poiseuilleU(superGeometry, 3, maxVelocity);
    sLattice.defineU(superGeometry, 3, poiseuilleU);

    //clout << "step=" << iT << "; scalingFactor=" << frac << std::endl;
  }
  //clout << "Set Boundary Values ... ok" << std::endl;
}

/// Computes the pressure drop between the voxels before and after the cylinder
void getResults(SuperLattice3D<T, DESCRIPTOR>& sLattice,
                    LBconverter<T>& converter, int iT,
                    SuperGeometry3D& superGeometry, Timer<double>& timer,
		    STLreader<T>& stlReader ) {

  OstreamManager clout(std::cout,"getResults");

  if (iT==0) {
    /// Writes the converter log file
    writeLogFile(converter, "cylinder3d");
    /// Writes the geometry, cuboid no. and rank no. as vti file for visualization
    SuperLatticeGeometry3D<T, DESCRIPTOR> geometry(sLattice, superGeometry);
    SuperLatticeCuboid3D<T, DESCRIPTOR> cuboid(sLattice);
    SuperLatticeRank3D<T, DESCRIPTOR> rank(sLattice);
    CuboidVTKout3D<T>::write<DESCRIPTOR>(geometry);
    CuboidVTKout3D<T>::write<DESCRIPTOR>(cuboid);
    CuboidVTKout3D<T>::write<DESCRIPTOR>(rank);
  }

  /// Writes the vtk files
  if (iT%converter.numTimeSteps(.6)==0) {
    // Create the data-reading functors...
    SuperLatticePhysVelocity3D<T, DESCRIPTOR> velocity(sLattice, converter);
    SuperLatticePhysPressure3D<T, DESCRIPTOR> pressure(sLattice, converter);
    SuperLatticeYplus3D<T, DESCRIPTOR> yPlus(sLattice, converter, superGeometry, stlReader, 5);
    //SuperLatticePhysQCrit3D<T, DESCRIPTOR> qCrit(sLattice, converter, superGeometry);

    // ...and pass them to the generic write function
    CuboidVTKout3D<T>::write<DESCRIPTOR>(velocity, iT);
    CuboidVTKout3D<T>::write<DESCRIPTOR>(pressure, iT);
    CuboidVTKout3D<T>::write<DESCRIPTOR>(yPlus, iT);
    //CuboidVTKout3D<T>::write<DESCRIPTOR>(qCrit, iT);
  }

  /// Writes output on the console
  if (iT%converter.numTimeSteps(.3)==0) {
    timer.update(iT);
    timer.printStep();
    sLattice.getStatistics().print(iT,iT*converter.getDeltaT());

    SuperLatticePhysPressure3D<T, DESCRIPTOR> pressure(sLattice, converter);
    AnalyticalFfromSuperLatticeF3D<T, DESCRIPTOR> intpolatePressure(pressure, superGeometry, true);
    SuperLatticePhysDrag3D<T,DESCRIPTOR> drag(sLattice, superGeometry, 5, converter);

    std::vector<T> point1(3,T()); std::vector<T> point2(3,T());
    point1[0]=0.45*1000; point1[1]=0.2*1000; point1[2]=0.205*1000;
    point2[0]=0.565*1000; point2[1]=0.2*1000; point2[2]=0.205*1000;
    T pressureDrop = intpolatePressure(point1)[0]-intpolatePressure(point2)[0];
    clout << "pressureDrop=" << pressureDrop;

    std::vector<int> input;
    clout << "; drag=" << drag(input)[0] << "; lift=" << drag(input)[1] << endl;

    SuperLatticeYplus3D<T, DESCRIPTOR> yPlus(sLattice, converter, superGeometry, stlReader, 5);
    SuperL2Norm3D<T,DESCRIPTOR> yPlusL2Norm(yPlus);
    SuperMax<T,DESCRIPTOR> yPlusL2NormMax(yPlusL2Norm, superGeometry, 1);

    T yPlusMax = yPlusL2NormMax(input)[0];
    clout << "yPlusNormMax=" << yPlusMax << endl;
  }
  return;
}



int main(int argc, char* argv[]) {

  /// === 1st Step: Initialization ===

  olbInit(&argc, &argv);
  singleton::directories().setOutputDir("./tmp/");
  OstreamManager clout(std::cout,"main");
  // display messages from every single mpi process
  //clout.setMultiOutput(true);

  LBconverter<T> converter(
    (int) 3,                               // dim
    (T)   0.01/N,                          // latticeL_
    (T)   0.05,                            // latticeU_
    (T)   0.001,                           // charNu_
    (T)   0.1,                             // charL_ = 1
    (T)   0.2                              // charU_ = 1
  );
  //T maxPhysT = 30.;                       // max. simulation time in s, SI unit
  T maxPhysT = 3.;                       // max. simulation time in s, SI unit

  /// === 2nd Step: Prepare Geometry ===

  /// Instantiation of the STLreader class
  STLreader<T> stlReader("cylinder3d.stl");
  /// Instantiation of an empty blockGeometry
  SuperGeometry3D superGeometry;
  /// Instantiation of an empty cuboidGeometry
  CuboidGeometry3D<T> cuboidGeometry;
  /// Instantiation of an empty loadBalancer
  heuristicLoadBalancer<T> loadBalancer;

  prepareGeometry(converter, stlReader, superGeometry, cuboidGeometry, loadBalancer);


  /// === 3rd Step: Prepare Lattice ===

  SuperLattice3D<T, DESCRIPTOR> sLattice(cuboidGeometry, 2, &loadBalancer);

  BGKdynamics<T, DESCRIPTOR> bulkDynamics(converter.getOmega(), instances::getBulkMomenta<T, DESCRIPTOR>());

  sOnLatticeBoundaryCondition3D<T, DESCRIPTOR> sBoundaryCondition(sLattice);
  createInterpBoundaryCondition3D<T, DESCRIPTOR> (sBoundaryCondition);

  sOffLatticeBoundaryCondition3D<T, DESCRIPTOR> sOffBoundaryCondition(sLattice);
  createBouzidiBoundaryCondition3D<T, DESCRIPTOR> (sOffBoundaryCondition);

  prepareLattice(sLattice, converter, bulkDynamics, sBoundaryCondition, sOffBoundaryCondition, stlReader, superGeometry);

  /// === 4th Step: Main Loop with Timer ===

  Timer<double> timer(converter.numTimeSteps(maxPhysT), superGeometry.getNx()*superGeometry.getNy()*superGeometry.getNz() );
  timer.start();

	T st, et;
    int iT=0;
    setBoundaryValues(sLattice, converter, iT, maxPhysT, superGeometry);
    st=time_sec();
    sLattice.collideAndStream();
    getResults(sLattice, converter, iT, superGeometry, timer, stlReader);
  //for (int iT = 0; iT <= converter.numTimeSteps(maxPhysT); ++iT) {
  for (int iT = 1; iT <= converter.numTimeSteps(maxPhysT); ++iT) {

    /// === 5th Step: Definition of Initial and Boundary Conditions ===
    setBoundaryValues(sLattice, converter, iT, maxPhysT, superGeometry);

    /// === 6th Step: Collide and Stream Execution ===
    sLattice.collideAndStream();

    /// === 7th Step: Computation and Output of the Results ===
  //  getResults(sLattice, converter, iT, superGeometry, timer, stlReader);
  }
    et=time_sec();
    cout << "timestep:"<<converter.numTimeSteps(maxPhysT)<<"kernel time: " << et - st << endl;

  timer.stop();
  timer.printSummary();
}

