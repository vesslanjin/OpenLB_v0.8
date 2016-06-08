/*  Lattice Boltzmann sample, written in C++, using the OpenLB
 *  library
 *
 *  Copyright (C) 2011-2013 Mathias J. Krause
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

using namespace std;
#include "olb3D.h"
#ifndef OLB_PRECOMPILED // Unless precompiled version is used,
#include "olb3D.hh"   // include full template code;
#endif
#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

using namespace olb;
using namespace olb::descriptors;
using namespace olb::graphics;
using namespace olb::util;

typedef double T;
#define DESCRIPTOR D3Q19Descriptor

#include "boundaryConditions3d.h"


//simulation parameters
int N = 1; // resolution of the modell

VelocityProfile<T> velProfile;

void prepareLattice(SuperLattice3D<T, D3Q19Descriptor>& lattice,
                 LBconverter<T> const& converter, Dynamics<T, DESCRIPTOR>& bulkDynamics,
                 sOnLatticeBoundaryCondition3D<T, DESCRIPTOR>& bc,
                 sOffLatticeBoundaryCondition3D<T,DESCRIPTOR>& offBc,
                 STLreader<T>& stlReader, SuperGeometry3D& superGeometry) {

  const T omega = converter.getOmega();

  /// material=0 --> do nothing
  lattice.defineDynamics(superGeometry,0,&instances::getNoDynamics<T, DESCRIPTOR>());

  /// material=1 --> bulk dynamics
  lattice.defineDynamics(superGeometry,1,&bulkDynamics);

  /// material=2 --> no dynamics + bouzidi zero velocity
  lattice.defineDynamics(superGeometry,2,&instances::getNoDynamics<T,DESCRIPTOR>());
  offBc.addZeroVelocityBoundary(superGeometry,2,stlReader);

  /// material=3 --> no dynamics + bouzidi velocity (inflow)
  lattice.defineDynamics(superGeometry,3,&instances::getNoDynamics<T,DESCRIPTOR>());
  offBc.addVelocityBoundary(superGeometry,3,stlReader);

  /// material=4,5 --> bulk dynamics + pressure (outflow)
  lattice.defineDynamics(superGeometry,4,&bulkDynamics);
  lattice.defineDynamics(superGeometry,5,&bulkDynamics);
  bc.addPressureBoundary(superGeometry,4,omega);
  bc.addPressureBoundary(superGeometry,5,omega);

  /// Initial conditions
  ConstAnalyticalF3D<T,T> rhoF(1);
  std::vector<T> velocity(3,T());
  ConstAnalyticalF3D<T,T> uF(velocity);

  lattice.iniEquilibrium(superGeometry,1,rhoF,uF);
  lattice.iniEquilibrium(superGeometry,3,rhoF,uF);
  lattice.iniEquilibrium(superGeometry,4,rhoF,uF);
  lattice.iniEquilibrium(superGeometry,5,rhoF,uF);

  /// Lattice initialize
  lattice.initialize();

  return;
}


void setBoundaryValues(sOffLatticeBoundaryCondition3D<T,DESCRIPTOR>& offBc,
  LBconverter<T> const& converter, int iT,
  SuperGeometry3D& superGeometry) 
  {
  if (iT%50 == 0) {
    int iTperiode = converter.numTimeSteps(0.5);
    SinusStartScale<T,int> nSinusStartScale(iTperiode,converter.getLatticeU() );
    std::vector<T> maxVelocity(3,T());
    std::vector<int> help; help.push_back(iT);
    maxVelocity[0] = nSinusStartScale(help)[0];
    CirclePoiseuille3D<T> velocity(superGeometry,3,maxVelocity[0]);
    //CirclePoiseuille3D<T> velocity(velProfile.getCenterpoint(3), velProfile.getNormal(3),  maxVelocity[0], velProfile.getRadius(3));
    offBc.defineU(superGeometry,3,velocity);
  }
}


void prepareGeometry(STLreader<T>& stlReader, SuperGeometry3D& superGeometry, CuboidGeometry3D<T>& cuboidGeometry, heuristicLoadBalancer<T>& loadBalancer ) {

  OstreamManager clout(std::cout,"prepareGeometry");
  
  stlReader.setOuterMaterialNo(2);
  stlReader.read(superGeometry, 2u, 50 * N);

  superGeometry.clean();

  SuperGeometryStatistics3D& geometryStatistics = superGeometry.getStatistics();
 
  list<int> materials;
  materials.push_back(3);
  materials.push_back(4);
  materials.push_back(5);

  std::list<int>::iterator i;
  for (i=materials.begin(); i!=materials.end(); i++) {

    T thickness = 1.2*superGeometry.getSpacing();
    std::vector<T> center = velProfile.getCenterpoint(*i);
    std::vector<T> normal(3,T(0)); normal[1] = 1.; // = velProfile.getNormal(*i);
    T radius = 1.4*velProfile.getRadius(*i);
    CylinderAnalyticalF3D<bool,T> cylinder(center, normal, radius, thickness);
    superGeometry.rename(2,*i,cylinder);

    std::vector<int> testDirection = superGeometry.getStatistics().computeDiscreteNormal(*i);
    testDirection[0] *=2; testDirection[1] *=2; testDirection[2] *=2;
    superGeometry.rename(*i,2,1,testDirection);
    testDirection[0] *=-1; testDirection[1] *=-1; testDirection[2] *=-1;
    superGeometry.rename(*i,2,0,testDirection);
  }

  superGeometry.clean();
  superGeometry.innerClean(3);
  superGeometry.checkForErrors();

  clout<<"spacing="<<superGeometry.getSpacing()<<"; nX="<< superGeometry.getNx()<<"; nY="<< superGeometry.getNy()<<"; nX="<< superGeometry.getNz()<<std::endl;
  superGeometry.getStatistics().countVoxel();

  int noOfCuboids = std::min(16*N,2*singleton::mpi().getSize() );

  cuboidGeometry = CuboidGeometry3D<T>(superGeometry.getPositionX(), superGeometry.getPositionY(), superGeometry.getPositionZ(),
                                  superGeometry.getSpacing(), superGeometry.getNx(), superGeometry.getNy(), superGeometry.getNz(), noOfCuboids);
  cuboidGeometry.printStatistics();
  cuboidGeometry.remove(superGeometry);
  cuboidGeometry.shrink(superGeometry);
  cuboidGeometry.printStatistics();

  loadBalancer.reInit(cuboidGeometry, superGeometry);
  stlReader.splitGeometry(cuboidGeometry, loadBalancer);
}


void getResults(SuperLattice3D<T, DESCRIPTOR>& sLattice,
                    LBconverter<T>& converter, int iT, int maxT,
                    Dynamics<T, DESCRIPTOR>& bulkDynamics,
                    SuperGeometry3D& superGeometry, Timer<double>& timer) {

  OstreamManager clout(std::cout,"getResults");

  if (iT==0) {
    /// Writes the converter log file
    writeLogFile(converter, "aorta3d");
    /// Writes the geometry, cuboid no. and rank no. as vti file for visualization
    SuperLatticeGeometry3D<T, DESCRIPTOR> geometry(sLattice, superGeometry);
    SuperLatticeCuboid3D<T, DESCRIPTOR> cuboid(sLattice);
    SuperLatticeRank3D<T, DESCRIPTOR> rank(sLattice);
    CuboidVTKout3D<T>::write<DESCRIPTOR>(geometry); 
    CuboidVTKout3D<T>::write<DESCRIPTOR>(cuboid); 
    CuboidVTKout3D<T>::write<DESCRIPTOR>(rank); 
    superGeometry.getStatistics().countVoxel();
  }

  /// Writes the vtk files
  int iTperiodVTK = converter.numTimeSteps(0.1);
  if (iT%iTperiodVTK==0) {

    SuperLatticePhysVelocity3D<T, DESCRIPTOR> velocity(sLattice, converter);
    SuperLatticePhysPressure3D<T, DESCRIPTOR> pressure(sLattice, converter);

    CuboidVTKout3D<T>::write<DESCRIPTOR>(velocity, iT); 
    CuboidVTKout3D<T>::write<DESCRIPTOR>(pressure, iT);
  }

  int iTperiodConsole = converter.numTimeSteps(0.1);
  if (iT%iTperiodConsole==0) {

    timer.update(iT);
    timer.printStep();

    sLattice.getStatistics().print(iT,iT*converter.getDeltaT());

    list<int> materials;
    materials.push_back(3);
    materials.push_back(4);
    materials.push_back(5);

    for (list<int>::iterator i=materials.begin(); i!=materials.end(); ++i) {

    const int x0 = superGeometry.getStatistics().getMin(*i)[0];
    const int y0 = superGeometry.getStatistics().getMin(*i)[1];
    const int z0 = superGeometry.getStatistics().getMin(*i)[2];

    const int x1 = superGeometry.getStatistics().getMax(*i)[0];
    const int y1 = superGeometry.getStatistics().getMax(*i)[1];
    const int z1 = superGeometry.getStatistics().getMax(*i)[2];

    Cell<T,D3Q19Descriptor> cell;

    int numV = 0;
    T inflow = 0.;
    T minV = 10., maxV=-10.;
    T meanRho = 0.;

    vector<T> normal = velProfile.getNormal(*i);

    for (int ix = x0; ix < x1+1; ix++) {
      for (int iy = y0; iy < y1+1; iy++) {
        for (int iz = z0; iz < z1+1; iz++) {
          if(superGeometry.getMaterial(ix,iy,iz)==*i) {
            int tmp = 0;
            if (*i==3) tmp=1;
            if(sLattice.get(ix,iy-tmp,iz,cell) ) {
              T rho;
              T vel[] = { T(), T(), T() };
              cell.defineDynamics( &bulkDynamics );
              cell.computeRhoU(rho,vel);
              T normalV = normal[0]*vel[0] + normal[1]*vel[1] + normal[2]*vel[2];
              if (normalV<minV) minV=normalV;
              if (normalV>maxV) maxV=normalV;
              inflow += normalV;
              meanRho += rho;
              numV++;
            }
          }
        }
      }
    }

    clout<< "material=" << *i << "; numVoxel=" << numV <<"; flowRate [ml/s]=" << converter.physFlowRate(inflow)*1000*1000 << std::endl;
    clout<< "material=" << *i << "; numVoxel=" << numV <<"; meanU [m/s]=" << converter.physVelocity(inflow/numV) << std::endl;
    clout<< "material=" << *i << "; numVoxel=" << numV <<"; minU [m/s]=" << converter.physVelocity(minV) << std::endl;
    clout<< "material=" << *i << "; numVoxel=" << numV <<"; maxU [m/s]=" << converter.physVelocity(maxV) << std::endl;
    clout<< "material=" << *i << "; numVoxel=" << numV <<"; meanP [Pa]=" << converter.physPressureFromRho(meanRho/numV) << std::endl;
    clout<< "material=" << *i << "; numVoxel=" << numV <<"; meanP [mmHg]=" << converter.physPressureFromRho(meanRho/numV)/133.322 << std::endl;
    }
  }

  if (sLattice.getStatistics().getMaxU() > 0.3) {
    clout << "PROBLEM uMax=" << sLattice.getStatistics().getMaxU() << endl;
    SuperLatticePhysVelocity3D<T, DESCRIPTOR> velocity(sLattice, converter);
    SuperLatticePhysPressure3D<T, DESCRIPTOR> pressure(sLattice, converter);
    CuboidVTKout3D<T>::write<DESCRIPTOR>(velocity, iT); 
    CuboidVTKout3D<T>::write<DESCRIPTOR>(pressure, iT);

    std::exit(0);
  }
}




int main(int argc, char* argv[]) {

  /// === 1st Step: Initialization ===
  olbInit(&argc, &argv);
  singleton::directories().setOutputDir("./tmp/");
  OstreamManager clout(std::cout,"main");
  // display messages from every single mpi process
  //clout.setMultiOutput(true);


  /// === 2nd Step: Prepare Geometry ===  

  /// Instantiation of the STLreader class
  STLreader<T> stlReader("aorta3db.stl");
  /// Instantiation of an empty superGeometry
  SuperGeometry3D superGeometry;
  /// Instantiation of an empty cuboidGeometry
  CuboidGeometry3D<T> cuboidGeometry;
  /// Instantiation of an empty loadBalancer
  heuristicLoadBalancer<T> loadBalancer;

  prepareGeometry(stlReader, superGeometry, cuboidGeometry, loadBalancer); 


  /// === 3rd Step: Prepare Lattice === 

  LBconverter<T> converter(
    3,                                     // dim
    (T) superGeometry.getSpacing()/1000.,  // latticeL_
    (T) 0.05,                              // latticeU_
    (T) 0.003/1055.,                       // charNu_
    (T) 0.02246,                           // charL_ = 1,
    (T) 0.45,                              // charU_ = 1,
    (T) 1055,                              // charRho_ = 1,
    (T) 0                                  // charPressure_ = 0
  );

  int maxT = converter.numTimeSteps(2.);
  SuperLattice3D<T, DESCRIPTOR> sLattice(cuboidGeometry, 2, &loadBalancer);

    SuperLatticeGeometry3D<T, DESCRIPTOR> geometry(sLattice, superGeometry);

    CuboidVTKout3D<T>::write<DESCRIPTOR>(geometry); 


  SmagorinskyBGKdynamics<T, DESCRIPTOR> bulkDynamics(converter.getOmega(),
                                          instances::getBulkMomenta<T, DESCRIPTOR>(), 0.15, converter.getDeltaX(), converter.getDeltaT());
  //BGKdynamics<T, DESCRIPTOR> bulkDynamics(converter.getOmega(),
  //                                        instances::getBulkMomenta<T, DESCRIPTOR>());
  sOnLatticeBoundaryCondition3D<T, D3Q19Descriptor>
    sBoundaryCondition(sLattice);
  createInterpBoundaryCondition3D<T, D3Q19Descriptor>
   (sBoundaryCondition);

  sOffLatticeBoundaryCondition3D<T, DESCRIPTOR>
    sOffBoundaryCondition(sLattice);
  createBouzidiBoundaryCondition3D<T, DESCRIPTOR>
    (sOffBoundaryCondition);

  util::Timer<T> timer1(converter.numTimeSteps(maxT), superGeometry.getStatistics().getNVoxel() );
  timer1.start();

  prepareLattice(sLattice, converter, bulkDynamics,
              sBoundaryCondition, sOffBoundaryCondition,
              stlReader, superGeometry);
  
  timer1.stop();
  timer1.printSummary();

  /// === 4th Step: Main Loop with Timer ===

  util::Timer<T> timer(maxT, superGeometry.getStatistics().getNVoxel() );
  timer.start();

  for (int iT = 0; iT < maxT; iT++) {

    /// === 5th Step: Definition of Initial and Boundary Conditions ===
    setBoundaryValues(sOffBoundaryCondition, converter, iT, superGeometry);

    /// === 6th Step: Collide and Stream Execution ===
    sLattice.collideAndStream();

    /// === 7th Step: Computation and Output of the Results ===
    getResults(sLattice, converter, iT, maxT, bulkDynamics, superGeometry,timer);


  }

  timer.stop();
  timer.printSummary();

  return 0;
}
