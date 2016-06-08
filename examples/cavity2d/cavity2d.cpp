/*  Lattice Boltzmann sample, written in C++, using the OpenLB
 *  library
 *
 *  Copyright (C) 2006 - 2012 Mathias J. Krause, Jonas Fietz,
 *  Jonas Latt, Jonas Kratzke
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

using namespace olb;
using namespace olb::descriptors;
using namespace olb::graphics;
using namespace olb::util;
using namespace std;

typedef double T;
#define DESCRIPTOR D2Q9Descriptor

void prepareLattice(LBconverter<T> const* converter,
                    BlockStructure2D<T,DESCRIPTOR>& lattice,
                    Dynamics<T, DESCRIPTOR>& bulkDynamics,
                    OnLatticeBoundaryCondition2D<T,DESCRIPTOR>& bc ){

  const int nx = lattice.getNx();
  const int ny = lattice.getNy();
  const T omega = converter->getOmega();

  // link lattice with dynamics for collision step
  lattice.defineDynamics(0,nx-1, 0,ny-1, &bulkDynamics);

  // left boundary
  bc.addVelocityBoundary0N(   0,   0,   1,ny-2, omega);
  // right boundary
  bc.addVelocityBoundary0P(nx-1,nx-1,   1,ny-2, omega);
  // bottom boundary
  bc.addVelocityBoundary1N(   1,nx-2,   0,   0, omega);
  // top boundary
  bc.addVelocityBoundary1P(   1,nx-2,ny-1,ny-1, omega);

  // corners
  bc.addExternalVelocityCornerNN(   0,   0, omega);
  bc.addExternalVelocityCornerNP(   0,ny-1, omega);
  bc.addExternalVelocityCornerPN(nx-1,   0, omega);
  bc.addExternalVelocityCornerPP(nx-1,ny-1, omega);
}

void setBoundaryValues(LBconverter<T> const* converter,
                       BlockStructure2D<T,DESCRIPTOR>& lattice, int iT){

  if(iT==0){

    const int nx = lattice.getNx();
    const int ny = lattice.getNy();

    // set initial values: v = [0,0]
    for (int iX=0; iX<nx; ++iX) {
      for (int iY=0; iY<ny; ++iY) {
        T vel[] = { T(), T()};
        lattice.get(iX,iY).defineRhoU((T)1, vel);
        lattice.get(iX,iY).iniEquilibrium((T)1, vel);
      }
    }

    // set non-zero velocity for upper boundary cells
    for (int iX=1; iX<nx-1; ++iX) {
      T u = converter->getLatticeU();
      T vel[] = { u, T() };
      lattice.get(iX,ny-1).defineRhoU((T)1, vel);
      lattice.get(iX,ny-1).iniEquilibrium((T)1, vel);
    }

    // Make the lattice ready for simulation
    lattice.initialize();
  }
}

void getResults(BlockStructure2D<T,DESCRIPTOR>& lattice,
                LBconverter<T> const* converter, int iT, Timer<double>* timer,
                const T logT, const T imSave, const T vtkSave, const T maxT,
                std::string filenameGif, std::string filenameVtk,
                const bool timerPrintSum, const int timerPrintMode, const int timerTimeSteps) {

  const int imSize = 600;

  /// Get statistics
  if (iT%converter->numTimeSteps(logT)==0) {
    lattice.getStatistics().print(iT, converter->physTime(iT));
  }

  if (iT%timerTimeSteps==0) {
    timer->print(iT,timerPrintMode);
  }

  /// Writes the Gif files
  if (iT%converter->numTimeSteps(imSave)==0 && iT>0) {
    DataAnalysisBase2D<T,DESCRIPTOR> const& analysis = lattice.getDataAnalysis();

    ImageWriter<T> imageWriter("leeloo");
    imageWriter.writeScaledGif(createFileName(filenameGif, iT, 6),
                               analysis.getVelocityNorm(),
                               imSize, imSize );
  }

  /// Writes the VTK files
  if (iT%converter->numTimeSteps(vtkSave)==0 && iT>0) {
    DataAnalysisBase2D<T,DESCRIPTOR> const& analysis = lattice.getDataAnalysis();

    T dx = converter->getLatticeL();
    T dt = converter->physTime();
    VtkImageOutput2D<T> vtkOut(createFileName(filenameVtk, iT, 6), dx);
    vtkOut.writeData<double>(analysis.getVorticity(), "vorticity", (T)1/dt);
    vtkOut.writeData<2,double>(analysis.getVelocity(), "velocity", dx/dt);
  }

  if (iT == converter->numTimeSteps(maxT)-1 ){
  timer->stop();
  if (timerPrintSum==true)
    timer->printSummary();
  }


}



int main(int argc, char* argv[]) {

    /// === 1st Step: Initialization ===

  olbInit(&argc, &argv);
  OstreamManager clout(std::cout,"main");

  string fName("cavity2d.xml");
  XMLreader config(fName);

  bool multiOutput=false;
  config["Output"]["MultiOutput"].read(multiOutput);
  clout.setMultiOutput(multiOutput);

  std::string olbdir, outputdir;
  config["Application"]["OlbDir"].read(olbdir);
  config["Output"]["OutputDir"].read(outputdir);
  singleton::directories().setOlbDir(olbdir);
  singleton::directories().setOutputDir(outputdir);

// call creator functions using xml data
  LBconverter<T>* converter = createLBconverter<T>(config);
  int N = converter->numNodes();
  Timer<T>* timer           = createTimer<T>(config, *converter, N*N);

/// === 3rd Step: Prepare Lattice ===

  T logT;
  T imSave;
  T vtkSave;
  T maxT;
  int timerSkipType;
  bool timerPrintSum = true;
  int timerPrintMode = 0;
  int timerTimeSteps = 1;

  config["Application"]["PhysParam"]["MaxTime"].read(maxT);
  config["Output"]["Log"]["SaveTime"].read(logT);
  config["Output"]["VisualizationImages"]["SaveTime"].read(imSave);
  config["Output"]["VisualizationVTK"]["SaveTime"].read(vtkSave);
  config["Output"]["Timer"]["SkipType"].read(timerSkipType);
  config["Output"]["Timer"]["PrintSummary"].read(timerPrintSum);
  config["Output"]["Timer"]["PrintMode"].read(timerPrintMode);

  if (timerSkipType == 0) {
    timerTimeSteps=converter->numTimeSteps(config["Output"]["Timer"]["PhysTime"].get<T>());
  } else {
    config["Output"]["Timer"]["TimeSteps"].read(timerTimeSteps);
  }

  writeLogFile(*converter, config["Output"]["Log"]["Filename"].get<std::string>());

  std::string filenameGif = config["Output"]["VisualizationImages"]["Filename"].get<std::string>();

  std::string filenameVtk = config["Output"]["VisualizationVTK"]["Filename"].get<std::string>();

#ifndef PARALLEL_MODE_MPI  // sequential program execution
  BlockLattice2D<T, DESCRIPTOR> lattice(N, N);
#else                      // parallel program execution
  MultiBlockLattice2D<T, DESCRIPTOR> lattice (
    createRegularDataDistribution(N, N) );
#endif

  ConstRhoBGKdynamics<T, DESCRIPTOR> bulkDynamics (
    converter->getOmega(),
    instances::getBulkMomenta<T,DESCRIPTOR>()
  );

  OnLatticeBoundaryCondition2D<T,DESCRIPTOR>*
  boundaryCondition = createInterpBoundaryCondition2D(lattice);

  prepareLattice(converter, lattice, bulkDynamics, *boundaryCondition);

    /// === 4th Step: Main Loop with Timer ===

  timer->start();

  int iT=0;
  for (iT=0; converter->physTime(iT)<maxT; ++iT) {
    

    /// === 5th Step: Definition of Initial and Boundary Conditions ===
    setBoundaryValues(converter, lattice, iT);

    /// === 6th Step: Collide and Stream Execution ===
    lattice.collideAndStream();

    /// === 7th Step: Computation and Output of the Results ===
    getResults(lattice, converter, iT, timer, logT, imSave, vtkSave, maxT, filenameGif, filenameVtk,
               timerPrintSum, timerPrintMode, timerTimeSteps);
   

  }


  delete converter;
  delete timer;
  delete boundaryCondition;

  return 0;
}
