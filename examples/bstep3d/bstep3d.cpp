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
using namespace std;

typedef double T;
#define DESCRIPTOR D3Q19Descriptor
#define time_sec() ({struct timeval tp; gettimeofday(&tp, 0); tp.tv_sec + tp. tv_usec * 1.e-6;})

void prepareLattice(LBconverter<T> const& converter,
                    BlockStructure3D<T,DESCRIPTOR>& lattice,
                    Dynamics<T, DESCRIPTOR>& bulkDynamics,
                    OnLatticeBoundaryCondition3D<T,DESCRIPTOR>& bc ){
  const T lx1   = 5.0;
  const T ly1   = 0.75;
  const T omega = converter.getOmega();

  const int nx = lattice.getNx();
  const int ny = lattice.getNy();
  const int nz = lattice.getNz();
  const int nx1 = converter.numCells(lx1)-2;
  const int ny1 = converter.numCells(ly1)-2;

  /// define lattice Dynamics
  lattice.defineDynamics(0,nx-1, 0,ny-1, 0,nz-1, &bulkDynamics);
  lattice.defineDynamics(0,nx1-1,0,ny1-1,0,nz-1,
                         &instances::getNoDynamics<T,DESCRIPTOR>());

  /// sets boundary
  bc.addVelocityBoundary0N(    0,    0,ny1+1, ny-2,   1,nz-2, omega);
  bc.addVelocityBoundary0N(  nx1,  nx1,    1,ny1-1,   1,nz-2, omega);
  bc.addVelocityBoundary0P(nx-1 , nx-1,    1, ny-2,   1,nz-2, omega);
  bc.addVelocityBoundary1N(    1,nx1-1,  ny1,  ny1,   1,nz-2, omega);
  bc.addVelocityBoundary1N(nx1+1, nx-2,    0,    0,   1,nz-2, omega);
  bc.addVelocityBoundary1P(    1, nx-2, ny-1, ny-1,   1,nz-2, omega);
  bc.addVelocityBoundary2N(    1, nx-2,ny1+1, ny-2,   0,   0, omega);
  bc.addVelocityBoundary2N(nx1+1, nx-2,    1,  ny1,   0,   0, omega);
  bc.addVelocityBoundary2P(    1, nx-2,ny1+1, ny-2,nz-1,nz-1, omega);
  bc.addVelocityBoundary2P(nx1+1, nx-2,    1,  ny1,nz-1,nz-1, omega);

  /// set Velocity  

  bc.addExternalVelocityEdge0NN(    1,nx1-1,  ny1,  ny1,    0,    0, omega);
  bc.addExternalVelocityEdge0NN(nx1+1, nx-2,    0,    0,    0,    0, omega);
  bc.addExternalVelocityEdge0NP(    1,nx1-1,  ny1,  ny1, nz-1, nz-1, omega);
  bc.addExternalVelocityEdge0NP(nx1+1, nx-2,    0,    0, nz-1, nz-1, omega);
  bc.addExternalVelocityEdge0PN(    1, nx-2, ny-1, ny-1,    0,    0, omega);
  bc.addExternalVelocityEdge0PP(    1, nx-2, ny-1, ny-1, nz-1, nz-1, omega);

  bc.addExternalVelocityEdge1NN(    0,    0,ny1+1, ny-2,    0,    0, omega);
  bc.addExternalVelocityEdge1NN(  nx1,  nx1,    1,ny1-1,    0,    0, omega);
  bc.addExternalVelocityEdge1NP( nx-1, nx-1,    1, ny-2,    0,    0, omega);
  bc.addExternalVelocityEdge1PN(    0,    0,ny1+1, ny-2, nz-1, nz-1, omega);
  bc.addExternalVelocityEdge1PN(  nx1,  nx1,    1,ny1-1, nz-1, nz-1, omega);
  bc.addExternalVelocityEdge1PP( nx-1, nx-1,    1, ny-2, nz-1, nz-1, omega);

  bc.addExternalVelocityEdge2NN(   0,   0, ny1, ny1,   1,nz-2, omega);
  bc.addExternalVelocityEdge2NN( nx1, nx1,   0,   0,   1,nz-2, omega);
  bc.addExternalVelocityEdge2NP(   0,   0,ny-1,ny-1,   1,nz-2, omega);
  bc.addExternalVelocityEdge2PN(nx-1,nx-1,   0,   0,   1,nz-2, omega);
  bc.addExternalVelocityEdge2PP(nx-1,nx-1,ny-1,ny-1,   1,nz-2, omega);

  bc.addExternalVelocityCornerNNN(   0, ny1,   0, omega);
  bc.addExternalVelocityCornerNNN( nx1,   0,   0, omega);
  bc.addExternalVelocityCornerNNP(   0, ny1,nz-1, omega);
  bc.addExternalVelocityCornerNNP( nx1,   0,nz-1, omega);
  bc.addExternalVelocityCornerNPN(   0,ny-1,   0, omega);
  bc.addExternalVelocityCornerNPN( nx1, ny1,   0, omega);
  bc.addExternalVelocityCornerNPP(   0,ny-1,nz-1, omega);
  bc.addExternalVelocityCornerNPP( nx1, ny1,nz-1, omega);
  bc.addExternalVelocityCornerPNN(nx-1,   0,   0, omega);
  bc.addExternalVelocityCornerPNP(nx-1,   0,nz-1, omega);
  bc.addExternalVelocityCornerPPN(nx-1,ny-1,   0, omega);
  bc.addExternalVelocityCornerPPP(nx-1,ny-1,nz-1, omega);

  bc.addInternalVelocityEdge2NN(  nx1,  nx1,  ny1,  ny1,  1, nz-2, omega);
}

void setBoundaryValues(LBconverter<T> const& converter,
                       BlockStructure3D<T,DESCRIPTOR>& lattice, int iT){

  if(iT==0){

    const T lx1   = 5.0;
    const T ly1   = 0.75;

    const int nx = lattice.getNx();
    const int ny = lattice.getNy();
    const int nz = lattice.getNz();
    const int nx1 = converter.numCells(lx1)-2;
    const int ny1 = converter.numCells(ly1)-2;

    /// for each point set the defineRhou and the Equilibrium
    for (int iX=0; iX<nx; ++iX) {
      for (int iY=0; iY<ny; ++iY) {
        for (int iZ=0; iZ<nz; ++iZ) {
          T vel[] = { T(), T(), T() };
          lattice.get(iX,iY,iZ).defineRhoU((T)1, vel);
          lattice.get(iX,iY,iZ).iniEquilibrium((T)1, vel);
        }
      }
    }

    for (int iX=0; iX<=nx1; ++iX) {
      for (int iY=ny1+1; iY<ny-1; ++iY) {
        for (int iZ=1; iZ<nz-1; ++iZ) {
          T vel[] = { converter.getLatticeU(), T(), T() };
          lattice.get(iX,iY,iZ).defineRhoU((T)1, vel);
          lattice.get(iX,iY,iZ).iniEquilibrium((T)1, vel);
        }
      }
    }

    for (int iX=nx1+1; iX<nx; ++iX) {
      for (int iY=1; iY<ny-1; ++iY) {
        for (int iZ=1; iZ<nz-1; ++iZ) {
          T u = converter.getLatticeU()*ly1/1.5;
          T vel[] = { u, T(), T() };
          lattice.get(iX,iY,iZ).defineRhoU((T)1, vel);
          lattice.get(iX,iY,iZ).iniEquilibrium((T)1, vel);
        }
      }
    }
    /// Make the lattice ready for simulation
    lattice.initialize();
  }
}


void getResults(BlockStructure3D<T,DESCRIPTOR>& lattice,
                LBconverter<T> const& converter, int iT,
                const T maxT) {

  OstreamManager clout(std::cout,"getResults");

  //const T logT     = (T)1/(T)100;
  const T logT     = (T)1/(T)1;
  const T imSave   = (T)1/(T)10;
  const T vtkSave  = (T)10;
  const T checkpointing = (T) 20;

  const int imSize = 600;
  const int nz = converter.numNodes(1.5);

  /// Get statistics
  //if (iT%converter.numTimeSteps(logT)==0 && iT>0) {
  if (iT%10==0 && iT>0) {
    lattice.getStatistics().print(iT,converter.physTime(iT) );
  }
#if 0
  /// Writes the Gif files
  if (iT%converter.numTimeSteps(imSave)==0 && iT>0) {
    DataAnalysisBase3D<T,DESCRIPTOR> const& analysis = lattice.getDataAnalysis();
    ImageWriter<T> imageWriter("leeloo");

    imageWriter.writeScaledGif(createFileName("uz", iT, 6),
                               analysis.getVelocityNorm().sliceZ(nz/2),
                               imSize, imSize );
  }

  /// Writes the VTK files
  if (iT%converter.numTimeSteps(vtkSave)==0 && iT>0) {
    T dx = converter.getDeltaX();
    T dt = converter.getDeltaT();
    DataAnalysisBase3D<T,DESCRIPTOR> const& analysis = lattice.getDataAnalysis();
    VtkImageOutput3D<T> vtkOut(createFileName("vtk", iT, 6), dx);
    vtkOut.writeData<T,float>(analysis.getVorticityNorm(), "vorticityNorm", (T)1/dt);
    vtkOut.writeData<3,T,float>(analysis.getVelocity(), "velocity", dx/dt);
  }

  if (iT%converter.numTimeSteps(checkpointing)==0 && iT>0) {
    clout << "Checkpointing the system at t=" << iT << endl;
    saveData(lattice, "bstep3d.checkpoint");
    // The data can be reloaded using
    //     loadData(lattice, "bstep3d.checkpoint");
  }

#endif

}



 

int main(int argc, char* argv[]) {

    /// === 1st Step: Initialization ===

  olbInit(&argc, &argv);
  singleton::directories().setOutputDir("./tmp/");
  OstreamManager clout(std::cout,"main");

  LBconverter<T> converter(
    (int) 3,                               // dim
    (T)   1./20.,                          // latticeL_
    (T)   4e-2,                            // latticeU_
    (T)   1./100.,                         // charNu_
    (T)   1.                               // charL_ = 1,
  );

  writeLogFile(converter, "backwardFacingStep2d");

/// === 3rd Step: Prepare Lattice ===

  //const T maxT     = (T)100.1;
  const T maxT     = (T)0.21;


  writeLogFile(converter, "3D backward facing step");

#ifndef PARALLEL_MODE_MPI  // sequential program execution
  BlockLattice3D<T, DESCRIPTOR> lattice(
    converter.numNodes(18), converter.numNodes(1.5), converter.numNodes(1.5) );
#else                      // parallel program execution
  MultiBlockLattice3D<T, DESCRIPTOR> lattice ( createRegularDataDistribution(
        //converter.numNodes(18), converter.numNodes(1.5), converter.numNodes(1.5) ) );//401*31*31
        converter.numNodes(36), converter.numNodes(12), converter.numNodes(12) ) );
#endif

  ConstRhoBGKdynamics<T, DESCRIPTOR> bulkDynamics (
    converter.getOmega(),
    instances::getBulkMomenta<T,DESCRIPTOR>()
  );

  // choose between local and non-local boundary condition
  OnLatticeBoundaryCondition3D<T,DESCRIPTOR>*
  //boundaryCondition = createInterpBoundaryCondition3D(lattice);
  boundaryCondition = createLocalBoundaryCondition3D(lattice);

  prepareLattice(converter, lattice, bulkDynamics, *boundaryCondition);

    /// === 4th Step: Main Loop with Timer ===

	T st, et;
    int iT=0;
      st=time_sec();
//    setBoundaryValues(converter, lattice, iT);
      et=time_sec();
    cout << "set boundary: " << et - st << endl;
      st=time_sec();
    lattice.collideAndStream();
    getResults(lattice, converter, iT, maxT);
  //for (iT=0; iT < converter.numTimeSteps(maxT); ++iT) {
  //for (iT=1; iT < converter.numTimeSteps(maxT); ++iT) {
  for (iT=1; iT < 100; ++iT) {

    /// === 5th Step: Definition of Initial and Boundary Conditions ===
    setBoundaryValues(converter, lattice, iT);


    /// === 6th Step: Collide and Stream Execution ===
    lattice.collideAndStream();

    /// === 7th Step: Computation and Output of the Results ===
    getResults(lattice, converter, iT, maxT);


  }
      et=time_sec();
    cout << "steps:"<<converter.numTimeSteps(maxT)<<"kernel time: " << et - st << endl;
  std::cout<<"nx:"<<converter.numNodes(36)<<"ny:"<<converter.numNodes(12)<<"nz:"<<converter.numNodes(12)<<std::endl;

  delete boundaryCondition;
}
