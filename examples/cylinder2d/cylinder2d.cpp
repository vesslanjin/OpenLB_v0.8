/*  Lattice Boltzmann sample, written in C++, using the OpenLB
 *  library
 *
 *  Copyright (C) 2006 Jonas Latt, 2012 Tim Dornieden
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

/* cylinder2d.cpp:
 * This example examines an unsteady flow past a cylinder placed in a channel.
 * The cylinder is offset somewhat from the center of the flow to make the
 * steady-state symmetrical flow unstable. At the inlet, a Poiseuille profile is
 * imposed on the velocity, where as the outlet implements an outflow condition:
 * grad_x p = 0. At Reynolds numbers around 100, an unstable periodic pattern is
 * created, the Karman vortex street.
 */


#include "olb2D.h"
#ifndef OLB_PRECOMPILED // Unless precompiled version is used,
#include "olb2D.hh"   // include full template code
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
#define DESCRIPTOR D2Q9Descriptor
#define time_sec() ({struct timeval tp; gettimeofday(&tp, 0); tp.tv_sec + tp. tv_usec * 1.e-6;})
// Parameters for the simulation setup
//const int nx     = 336;
//const int ny     = 64;
//const int nx     = 4096;
//const int ny     = 1024;
const int nx     = 16384;
const int ny     = 4096;
const T uMax     = 0.02;
const T Re       = 100.;
const int obst_x = nx/5-1;
const int obst_y = ny/2-1;
const int obst_r = ny/10+1;
const T nu       = uMax * 2.*obst_r / Re;
const T omega    = 1. / (3.*nu+1./2.);
const int maxT   = 100;
//const int maxT   = 200;
const int tSave  = 10;
const int itStart = 10;


// Set up the geometry of the simulation
void prepareLattice(BlockStructure2D<T,DESCRIPTOR>& lattice,
                    Dynamics<T, DESCRIPTOR>& bulkDynamics,
                    OnLatticeBoundaryCondition2D<T,DESCRIPTOR>& boundaryCondition ){

  // Set bulk dynamics
  lattice.defineDynamics(0,nx-1,0,ny-1,    &bulkDynamics);

  // Set top boundary condition
  boundaryCondition.addVelocityBoundary1P(1,nx-2,ny-1,ny-1, omega);
  // Set bottom boundary condition
  boundaryCondition.addVelocityBoundary1N(1,nx-2,   0,   0, omega);
  // Set left boundary condition
  boundaryCondition.addVelocityBoundary0N(0,0, 1, ny-2, omega);
  // Set right boundary condition
  boundaryCondition.addPressureBoundary0P(nx-1,nx-1, 1, ny-2, omega);

  // Set corner nodes condition
  boundaryCondition.addExternalVelocityCornerNN(0,0, omega);
  boundaryCondition.addExternalVelocityCornerNP(0,ny-1, omega);
  boundaryCondition.addExternalVelocityCornerPN(nx-1,0, omega);
  boundaryCondition.addExternalVelocityCornerPP(nx-1,ny-1, omega);
}




void setBoundaryValues(BlockStructure2D<T, DESCRIPTOR>& lattice,
                       int iT){
  OstreamManager clout(std::cout,"setBoundaryValues");

  // Definition of the obstacle (bounce-back nodes) 
  // Set initial condition
  if(iT==0){ 
    for (int iX=0; iX<nx; ++iX) {
      for (int iY=0; iY<ny; ++iY) {
        T u[2] = {0.,0.};
        T rho = (T)1;
        if ( (iX-obst_x)*(iX-obst_x) +
             (iY-obst_y)*(iY-obst_y) <= obst_r*obst_r )
        {
          lattice.defineDynamics( iX,iX,iY,iY,
                                  &instances::getBounceBack<T,DESCRIPTOR>() );
        }
        else {
          lattice.get(iX,iY).defineRhoU(rho, u);
          lattice.get(iX,iY).iniEquilibrium(rho, u);
        }
      }
    }
  // Make the lattice ready for simulation
  lattice.initialize();
  }

  if (iT <= itStart) {
    const int ny = lattice.getNy();
  
    // Smooth start curve, sinus
    // SinusStartScale<T,int> nSinusStartScale(itStart, (T)1);
    // T frac = nSinusStartScale(iT);

    // Smooth start curve, polynomial
    PolynomialStartScale<T,int> nPolynomialStartScale(itStart, T(1));
    std::vector<int> help; help.push_back(iT);
    T frac = nPolynomialStartScale(help)[0];

    SquareAnalyticalF<T,T> nPoiseuilleVelocity((ny-1.)/2., (ny-1.)/2., uMax);
    T p0 =8.*nu*uMax*(nx-1)/(2.*(ny-1)*(ny-1));
    LinearAnalyticalF1D<T,T> nPoiseuillePressure(0 , p0 , nx-1 , -p0 );
  
    for (int iY = 0; iY < ny; ++iY) {  
      std::vector<T> help2;
      help2.push_back((T)iY);
      T u[2] = {frac * nPoiseuilleVelocity(help2)[0],0.};
      help2[0] = T();
      T rho = (T)1 + nPoiseuillePressure(help2)[0] * DESCRIPTOR<T>::invCs2;
      lattice.get(0,iY).defineRhoU(rho, u);  
    }
  }
}

void getResults(BlockStructure2D<T, DESCRIPTOR>& lattice, int iT){
  if (iT%tSave==0 && iT !=0) {
    OstreamManager clout(std::cout,"main");
    clout.setMultiOutput(false);
    /// Get statistics
    clout << "step=" << iT
          << "; avEnergy="
          << lattice.getStatistics().getAverageEnergy()
          << "; avRho="
          << lattice.getStatistics().getAverageRho()
          << "; uMax="
          << lattice.getStatistics().getMaxU() << endl;

    DataAnalysisBase2D<T,DESCRIPTOR> const& analysis = lattice.getDataAnalysis();
#if 0 //zhoushan disable output result
    // Creation of images representing intermediate simulation results
    ImageWriter<T> imageWriter("leeloo");
    // Creation of gif images. This works only on systems on
    // which ImageMagick is installed. If you have the
    // program gifmerge, you can create an animation with the help
    // of a command of the kind "gifmerge -5 u*.gif > anim_u"
    createFileName("p", iT, 6);
    analysis.getPressure();
    createFileName("u", iT, 6);
    analysis.getVelocityNorm();

//   imageWriter.writeScaledGif(createFileName("p", iT, 6),
//                               analysis.getPressure());
//    imageWriter.writeScaledGif(createFileName("u", iT, 6),
//                               analysis.getVelocityNorm());
#endif	
  }
}


int main(int argc, char* argv[]) {

  /// === 1st Step: Initialization ===
  olbInit(&argc, &argv);
  singleton::directories().setOutputDir("./tmp/");

  /// === 3rd Step: Prepare Lattice ===
#ifndef PARALLEL_MODE_MPI  // sequential program execution
  BlockLattice2D<T, DESCRIPTOR> lattice( nx, ny );
#else                      // parallel program execution
  MultiBlockLattice2D<T, DESCRIPTOR> lattice (
    createRegularDataDistribution( nx, ny ) );
#endif

  BGKdynamics<T, DESCRIPTOR> bulkDynamics (
    omega,
    instances::getBulkMomenta<T,DESCRIPTOR>()
  );

  // Initialize an object that produces the boundary condition.
  // createLocalBoundaryCondition2D: local, regularized boundary condition
  // createInterpBoundaryCondition2D: non-local boundary, based on an
  //                                  interpolation of the stress tensor.

  // choose between local and non-local boundary condition
  OnLatticeBoundaryCondition2D<T,DESCRIPTOR>*
  // boundaryCondition = createInterpBoundaryCondition2D(lattice);
  boundaryCondition = createLocalBoundaryCondition2D(lattice);

  prepareLattice(lattice, bulkDynamics, *boundaryCondition);

	T st, et;
    int iT=0;
    setBoundaryValues(lattice, iT);
    lattice.collideAndStream();
    getResults(lattice, iT);
      st=time_sec();
  /// === 4th Step: Main Loop with Timer ===
  //for (int iT=0; iT<maxT; ++iT) {
  for (int iT=1; iT<maxT; ++iT) {

    /// === 5th Step: Definition of Initial and Boundary Conditions ===
    //T t0,t1,t2,t3;
    //t0 = time_sec();
    setBoundaryValues(lattice, iT);
    //t1 = time_sec();
    /// === 6th Step: Collide and Stream Execution ===
    lattice.collideAndStream();
    //t2 = time_sec();
    /// === 7th Step: Computation and Output of the Results ===
    getResults(lattice, iT);
    //t3 = time_sec();
    //cout << "in main function, loop 0 : " << t1-t0 << ", loop 1: " << t2 - t1 << ", loop 2: " << t3 - t2 << endl;
  }
      et=time_sec();
    cout << "time: " << et - st << endl;

  delete boundaryCondition;
}
