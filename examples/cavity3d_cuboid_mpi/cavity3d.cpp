/*  Lattice Boltzmann sample, written in C++, using the OpenLB
 *  library
 *
 *  Copyright (C) 2006, 2007, 2012 Jonas Latt, Mathias J. Krause
 *  Vincent Heuveline
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
#ifndef OLB_PRECOMPILED // Unless precompiled version is used,
#include "olb3D.hh"   // include full template code
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

void prepareLattice(LBconverter<T> const& converter,
		  SuperLattice3D<T,DESCRIPTOR>& lattice,
                  Dynamics<T, DESCRIPTOR>& bulkDynamics,
                  sOnLatticeBoundaryCondition3D<T,DESCRIPTOR>& bc ) {
  const int nx = converter.numNodes(1);
  const int ny = converter.numNodes(1);
  const int nz = converter.numNodes(1);
  const T omega = converter.getOmega();

  /// define lattice Dynamics
  lattice.defineDynamics(0,nx-1, 0,ny-1, 0,nz-1, &bulkDynamics);

  /// sets boundary
  bc.addVelocityBoundary0N(   0,   0,   1,ny-2,   1,nz-2, omega);
  bc.addVelocityBoundary0P(nx-1,nx-1,   1,ny-2,   1,nz-2, omega);
  bc.addVelocityBoundary1N(   1,nx-2,   0,   0,   1,nz-2, omega);
  bc.addVelocityBoundary1P(   1,nx-2,ny-1,ny-1,   1,nz-2, omega);
  bc.addVelocityBoundary2N(   1,nx-2,   1,ny-2,   0,   0, omega);
  bc.addVelocityBoundary2P(   1,nx-2,   1,ny-2,nz-1,nz-1, omega);

  /// set Velocity

  bc.addExternalVelocityEdge0NN(   1,nx-2,   0,   0,   0,   0, omega);
  bc.addExternalVelocityEdge0NP(   1,nx-2,   0,   0,nz-1,nz-1, omega);
  bc.addExternalVelocityEdge0PN(   1,nx-2,ny-1,ny-1,   0,   0, omega);
  bc.addExternalVelocityEdge0PP(   1,nx-2,ny-1,ny-1,nz-1,nz-1, omega);

  bc.addExternalVelocityEdge1NN(   0,   0,   1,ny-2,   0,   0, omega);
  bc.addExternalVelocityEdge1NP(nx-1,nx-1,   1,ny-2,   0,   0, omega);
  bc.addExternalVelocityEdge1PN(   0,   0,   1,ny-2,nz-1,nz-1, omega);
  bc.addExternalVelocityEdge1PP(nx-1,nx-1,   1,ny-2,nz-1,nz-1, omega);

  bc.addExternalVelocityEdge2NN(   0,   0,   0,   0,   1,nz-2, omega);
  bc.addExternalVelocityEdge2NP(   0,   0,ny-1,ny-1,   1,nz-2, omega);
  bc.addExternalVelocityEdge2PN(nx-1,nx-1,   0,   0,   1,nz-2, omega);
  bc.addExternalVelocityEdge2PP(nx-1,nx-1,ny-1,ny-1,   1,nz-2, omega);

  bc.addExternalVelocityCornerNNN(   0,   0,   0, omega);
  bc.addExternalVelocityCornerNNP(   0,   0,nz-1, omega);
  bc.addExternalVelocityCornerNPN(   0,ny-1,   0, omega);
  bc.addExternalVelocityCornerNPP(   0,ny-1,nz-1, omega);
  bc.addExternalVelocityCornerPNN(nx-1,   0,   0, omega);
  bc.addExternalVelocityCornerPNP(nx-1,   0,nz-1, omega);
  bc.addExternalVelocityCornerPPN(nx-1,ny-1,   0, omega);
  bc.addExternalVelocityCornerPPP(nx-1,ny-1,nz-1, omega);
}

void setBoundaryValues(LBconverter<T> const&converter,
                       SuperLattice3D<T,DESCRIPTOR>& lattice, int iT){

  if(iT==0){
    const int nx = converter.numNodes(1);
    const int ny = converter.numNodes(1);
    const int nz = converter.numNodes(1);
    /// for each point set the defineRhou and the Equilibrium

    T vel_a[] = { T(), T(), T()};

    lattice.defineRhoU    (0, nx-1, 0, ny-1, 0, nz-1, (T)1, vel_a);
    lattice.iniEquilibrium(0, nx-1, 0, ny-1, 0, nz-1, (T)1, vel_a);

    T u = converter.getLatticeU();
    T vel_b[] = { u, T(), T()};

    lattice.defineRhoU    (0, nx-1, ny-1, ny-1, 0, nz-1, (T)1, vel_b);
    lattice.iniEquilibrium(0, nx-1, ny-1, ny-1, 0, nz-1, (T)1, vel_b);

    /// Make the lattice ready for simulation

    lattice.initialize();

  }

}


void getResults(SuperLattice3D<T,DESCRIPTOR>& sLattice,
                LBconverter<T> const& converter, int iT, Timer<double>& timer,
                const T maxT) {

  const T logT     = (T)1.;
  const T vtkSave  = (T)1.;



  /// Get statistics
  if (iT%converter.numTimeSteps(logT)==0 && iT>0) {
    timer.update(iT);
    timer.printStep(2);
    sLattice.getStatistics().print(iT,iT*converter.getDeltaT());
  }

  /// Writes the VTK files
  if (iT%converter.numTimeSteps(vtkSave)==0 && iT>0) {
    vector<const ScalarFieldBase3D<T>* > scalar;
    vector<const TensorFieldBase3D<T,3>* > tensor;

    for (int iC=0; iC<sLattice.get_load().size(); iC++) {
      const TensorFieldBase3D<T,3>* velocity = &sLattice.get_lattice(iC).getDataAnalysis().getVelocity();
      const ScalarFieldBase3D<T>* pressure = &sLattice.get_lattice(iC).getDataAnalysis().getPressure();
      scalar.push_back( pressure );
      tensor.push_back( velocity );
    }

    CuboidVTKout3D<T>::writeFlowField (
      createFileName("vtk", iT, 6),
      "Pressure", scalar,
      "Velocity", tensor,
      sLattice.get_cGeometry(), sLattice.get_load(), converter.physVelocity(), converter.physPressure());
  }

  if (iT == converter.numTimeSteps(maxT)-1 ){
    timer.stop();
    timer.printSummary();
  }

}



int main(int argc, char **argv) {

    /// === 1st Step: Initialization ===

  olbInit(&argc, &argv);
  singleton::directories().setOutputDir("./tmp/");
  OstreamManager clout(std::cout,"main");

  LBconverter<T> converter(
    (int) 3,                               // dim
    (T)   1./30.,                          // latticeL_
    (T)   1e-1,                            // latticeU_
    (T)   1./1000.,                        // charNu_
    (T)   1.                               // charL_ = 1,
  );

  writeLogFile(converter, "cavity3d");

/// === 3rd Step: Prepare Lattice ===
 
  const T maxT     = (T)20.;

#ifdef PARALLEL_MODE_MPI
  CuboidGeometry3D<T> cGeometry(0, 0, 0, 1, converter.numNodes(1),
                                converter.numNodes(1), converter.numNodes(1), singleton::mpi().getSize());
#else
  CuboidGeometry3D<T> cGeometry(0, 0, 0, 1, converter.numNodes(1),
                                converter.numNodes(1), converter.numNodes(1), 7);
#endif

  cGeometry.printStatistics();

  SuperLattice3D<T, DESCRIPTOR> sLattice(cGeometry,2);


  ConstRhoBGKdynamics<T, DESCRIPTOR> bulkDynamics (
    converter.getOmega(), instances::getBulkMomenta<T,D3Q19Descriptor>());


  sOnLatticeBoundaryCondition3D<T,DESCRIPTOR> sBoundaryCondition(sLattice);
  createInterpBoundaryCondition3D<T,DESCRIPTOR>(sBoundaryCondition);

  prepareLattice(converter, sLattice, bulkDynamics, sBoundaryCondition);


    /// === 4th Step: Main Loop with Timer ===

  Timer<double> timer(converter.numTimeSteps(maxT), converter.numNodes(1)*converter.numNodes(1)*converter.numNodes(1) );
  timer.start();
  int iT;

  for (iT=0; iT < converter.numTimeSteps(maxT); ++iT) {

    /// === 5th Step: Definition of Initial and Boundary Conditions ===
    setBoundaryValues(converter, sLattice, iT);


    /// === 6th Step: Collide and Stream Execution ===
    sLattice.collideAndStream();

    /// === 7th Step: Computation and Output of the Results ===
    getResults(sLattice, converter, iT, timer, maxT);

  }
  clout << iT << endl;



  return 0;
}

