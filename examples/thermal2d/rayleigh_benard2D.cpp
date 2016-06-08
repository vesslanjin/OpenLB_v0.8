/*  Lattice Boltzmann sample, written in C++, using the OpenLB
 *  library
 *
 *  Copyright (C) 2008 Orestis Malaspinas
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
#include "olb2D.hh"
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sys/time.h>

using namespace olb;
using namespace olb::descriptors;
using namespace olb::graphics;
using namespace std;

typedef double T;

#define NSDESCRIPTOR ForcedD2Q9Descriptor
#define TDESCRIPTOR AdvectionDiffusionD2Q5Descriptor
#define time_sec() ({struct timeval tp; gettimeofday(&tp, 0); tp.tv_sec + tp. tv_usec * 1.e-6;})
const int maxIter  = 1000000000;
const int saveIter = 2500;

void prepareLattice( AdvectionDiffusionUnitLB<T,NSDESCRIPTOR,TDESCRIPTOR> &converter,
                     BlockStructure2D<T, NSDESCRIPTOR>& NSlattice,
                     BlockStructure2D<T, TDESCRIPTOR>& ADlattice,
                     ForcedBGKdynamics<T, NSDESCRIPTOR> &bulkDynamics,
                     Dynamics<T, TDESCRIPTOR>& advectionDiffusionBulkDynamics,
                     OnLatticeBoundaryCondition2D<T,NSDESCRIPTOR>& NSboundaryCondition,
                     OnLatticeAdvectionDiffusionBoundaryCondition2D<T,TDESCRIPTOR>& TboundaryCondition ){

  OstreamManager cout(std::cout,"prepareLattice");

  int nx = ADlattice.getNx();
  int ny = ADlattice.getNy();
  double Tomega  = converter.getOmegaT();
  double NSomega = converter.getOmegaNS();

  /// define lattice Dynamics
  cout << "defining dynamics" << endl;

  ADlattice.defineDynamics(0,nx-1, 0,ny-1, &advectionDiffusionBulkDynamics);
  NSlattice.defineDynamics(0,nx-1, 0,ny-1, &bulkDynamics);

  /// sets boundary
  NSboundaryCondition.addVelocityBoundary1P(0,nx-1,ny-1,ny-1, NSomega);
  NSboundaryCondition.addVelocityBoundary1N(0,nx-1,   0,   0, NSomega);

  TboundaryCondition.addTemperatureBoundary1P(0,nx-1,ny-1,ny-1, Tomega);
  TboundaryCondition.addTemperatureBoundary1N(0,nx-1,   0,   0, Tomega);
}

void setBoundaryValues(AdvectionDiffusionUnitLB<T,NSDESCRIPTOR,TDESCRIPTOR> &converter,
                       BlockStructure2D<T, NSDESCRIPTOR>& NSlattice,
                       BlockStructure2D<T, TDESCRIPTOR>& ADlattice,
                       int iT){

  if(iT==0){
    int nx = ADlattice.getNx();
    int ny = ADlattice.getNy();
    typedef advectionDiffusionLbHelpers<T,TDESCRIPTOR> TlbH;

    /// for each point set the defineRhou and the Equilibrium
    for (int iX=0; iX<nx; ++iX) {
      for (int iY=0; iY<ny; ++iY) {
        T u[2] = {0.,0.};
        T rho = (T)1;
        NSlattice.get(iX,iY).defineRhoU(rho, u);
        NSlattice.get(iX,iY).iniEquilibrium(rho, u);
        T force[2] = {T(), T()};
        NSlattice.get(iX,iY).defineExternalField (
          NSDESCRIPTOR<T>::ExternalField::forceBeginsAt,
          NSDESCRIPTOR<T>::ExternalField::sizeOfForce,
          force );
      }
    }

    T Tcold = converter.getTcold();
    T Thot  = converter.getThot();

    for (int iX=0; iX<nx; ++iX) {
      for (int iY=0; iY<ny; ++iY) {
        T u[2] = {0.,0.};
        T temperature =Tcold;
        if (iY==0)
          temperature = Thot;

        ADlattice.get(iX,iY).defineRho(temperature);
        T tEq[TDESCRIPTOR<T>::q];
        for (int iPop = 0; iPop < TDESCRIPTOR<T>::q; ++iPop) {
          tEq[iPop] = TlbH::equilibrium(iPop,temperature,u);
        }
        ADlattice.get(iX,iY).definePopulations(tEq);
        ADlattice.get(iX,iY).defineExternalField (
          TDESCRIPTOR<T>::ExternalField::velocityBeginsAt,
          TDESCRIPTOR<T>::ExternalField::sizeOfVelocity,
          u );
      }
    }

    ADlattice.get(nx/2,1).defineRho(Thot+Thot/(T)5);

    /// Make the lattice ready for simulation
    NSlattice.initialize();
    ADlattice.initialize();
  }
}

void couplingBetweenNavierStokesAndAdvectionDiffusion(
  BlockStructure2D<T, TDESCRIPTOR>& ADlattice,
  BlockStructure2D<T,NSDESCRIPTOR>& NSlattice,
  AdvectionDiffusionUnitLB<T,NSDESCRIPTOR,TDESCRIPTOR> &converter)
{

  int nx = NSlattice.getNx();
  int ny = NSlattice.getNy();

  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//
  // This coupling must be necessarily be put on the Navier-Stokes lattice!!
  // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!//

  std::vector<SpatiallyExtendedObject2D* > partnerForNavierStokes;

  partnerForNavierStokes.push_back(&ADlattice);
  partnerForNavierStokes.push_back(&NSlattice);

  std::vector<T> dir;
  dir.push_back(T());
  dir.push_back((T)1);

  NavierStokesAdvectionDiffusionCouplingGenerator2D<T,NSDESCRIPTOR>
  coupling(0,nx-1,0,ny-1, converter.getGravity(),
           converter.getT0(), converter.getDeltaTemperature(), dir);

  NSlattice.addLatticeCoupling(coupling,partnerForNavierStokes);
}

void getResults(BlockStructure2D<T, NSDESCRIPTOR>&    NSlattice,
                    BlockStructure2D<T, TDESCRIPTOR>&    ADlattice, int iT){

  OstreamManager cout(std::cout,"getResults");

  /// Get statistics and write Gif files
  if (iT%saveIter==0) {
    cout << "Writing stats at time " << iT << "." << std::endl;
    cout << ADlattice.getStatistics().getAverageEnergy() << endl;
    cout << "Writing Gif..." << std::endl;
    ImageWriter<T> imageCreator("leeloo.map");

    imageCreator.writeScaledGif(createFileName("t", iT, 7),
                                ADlattice.getDataAnalysis().getPressure(),
                                600,300);
    imageCreator.writeScaledGif(createFileName("uy", iT, 6),
                                NSlattice.getDataAnalysis().getVelocityNorm(),
                                600,300);
  }

}

T computeNusselt(BlockStructure2D<T, NSDESCRIPTOR>& NSlattice,
                 BlockStructure2D<T,TDESCRIPTOR> &ADlattice,
                 AdvectionDiffusionUnitLB<T,NSDESCRIPTOR,TDESCRIPTOR> &converter)
{
  int nx = NSlattice.getNx();
  int ny = NSlattice.getNy();

  T u_T = T();
  for (int iX = 0; iX < nx; ++iX)
  {
    for (int iY = 0; iY < ny; ++iY)
    {
      const T uy =
        NSlattice.getDataAnalysis().getVelocity().extractComponent(1).get(iX,iY);
      u_T += uy * ADlattice.get(iX,iY).computeRho();
    }
  }
  T nusselt = (T)1 + u_T*converter.getDeltaX() /
              (converter.getKappa() *
               (converter.getThot()-converter.getTcold()));

  return nusselt;
}

int main(int argc, char *argv[]) {

    /// === 1st Step: Initialization ===
  OstreamManager clout(std::cout,"main");
  olbInit(&argc, &argv);
  singleton::directories().setOutputDir("./tmp/");

  double Ra    = 10000;
  double Pr    = 1;
  int N        = 50;
  double dt    = 0.001;

  if (argc == 5) {
    Ra    = atof(argv[1]);
    Pr    = atof(argv[2]);
    N     = atoi(argv[3]);
    dt    = atof(argv[4]);
  }
  else {
    clout << "Warning : Wrong number of parameters specified." << endl;
    clout << "1 : Rayleigh.    default: " << Ra << endl;
    clout << "2 : Prandtl.     default: " << Pr << endl;
    clout << "3 : N.           default: " << N << endl;
    clout << "4 : Delta t.     default: " << dt << endl;
    clout << "Now using default values instead.";
  }

  clout << "Starting simulation with parameters Ra=" << Ra << " Pr=" << Pr << " N=" << N << " dt=" << dt << endl;

  AdvectionDiffusionUnitLB<T,NSDESCRIPTOR,TDESCRIPTOR> converter(
    Ra,   // Ra
    Pr,   // Pr
    0.0,  // Tcold
    1.0,  // Thot
    N,    // N
    dt,   // dt
    2.0,  // lx
    1.0   // ly
  );
  writeLogFile<T,NSDESCRIPTOR,TDESCRIPTOR>(converter,"2D rayleigh-benard");

  const double Raprova = converter.getN() * converter.getN() *
                         converter.getN() * converter.getDeltaTemperature() *
                         converter.getGravity() / (converter.getNu()*converter.getKappa());

  const double Prprova = converter.getNu() / converter.getKappa();

  clout << Raprova << " " << Prprova << endl;
  clout << converter.getOmegaNS() << " " << converter.getOmegaT() << endl;

  int nx = converter.getNx();
  int ny = converter.getNy();

  /// === 3rd Step: Prepare Lattice ===

#ifndef PARALLEL_MODE_MPI  // sequential program execution
  MultiDataDistribution2D distribution = createRegularDataDistribution( nx, ny, 1, 1, 1 );
#else                      // parallel program execution
  MultiDataDistribution2D distribution = createRegularDataDistribution( nx, ny );
#endif
  MultiBlockLattice2D<T, TDESCRIPTOR> ADlattice(distribution);
  MultiBlockLattice2D<T, NSDESCRIPTOR> NSlattice(distribution);

  OnLatticeBoundaryCondition2D<T,NSDESCRIPTOR>* NSboundaryCondition =
    createLocalBoundaryCondition2D(NSlattice);

  OnLatticeAdvectionDiffusionBoundaryCondition2D<T,TDESCRIPTOR>* TboundaryCondition =
    createAdvectionDiffusionBoundaryCondition2D(ADlattice);

  ForcedBGKdynamics<T, NSDESCRIPTOR> NSbulkDynamics(
    converter.getOmegaNS(),
    instances::getBulkMomenta<T,NSDESCRIPTOR>());


  AdvectionDiffusionRLBdynamics<T, TDESCRIPTOR> TbulkDynamics (
    converter.getOmegaT(),
    instances::getAdvectionDiffusionBulkMomenta<T,TDESCRIPTOR>()
  );

  couplingBetweenNavierStokesAndAdvectionDiffusion(ADlattice, NSlattice, converter);

  prepareLattice(converter,
                 NSlattice, ADlattice,
                 NSbulkDynamics, TbulkDynamics,
                 *NSboundaryCondition, *TboundaryCondition );

    /// === 4th Step: Main Loop with Timer ===

  util::ValueTracer<T> converge(0.01,(T)ny,1.0e-5);
  int iT = 0;
  clout << "starting simulation" << endl;
  T st, et;
  st=time_sec();
  for (iT=0; iT<maxIter; ++iT) {

    if (converge.hasConverged()) {
      clout << "FINAL CONVERGENCE!!! " << endl;
      break;
    }

    /// === 5th Step: Definition of Initial and Boundary Conditions ===
    setBoundaryValues(converter, NSlattice, ADlattice, iT);

    /// === 6th Step: Collide and Stream Execution ===
    ADlattice.collideAndStream(true);
    NSlattice.collideAndStream(true);

    converge.takeValue(ADlattice.getStatistics().getAverageEnergy(),true);

    NSlattice.executeCoupling();
    ADlattice.executeCoupling();

    /// === 7th Step: Computation and Output of the Results ===
    getResults(NSlattice, ADlattice, iT);
  }
  et=time_sec();
  clout << "totaltime elapsed for iterations: " << et - st << endl;
  clout << "Time " << iT << "." << std::endl;
  clout << "Nusselt = " << computeNusselt(NSlattice, ADlattice, converter) << endl;

  delete NSboundaryCondition;
  delete TboundaryCondition;
}
