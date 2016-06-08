/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006, 2007 Jonas Latt
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

#ifndef SIMULATION_SETUP_2D_HH
#define SIMULATION_SETUP_2D_HH

#include <cmath>
#include <vector>
#include <limits>
#include <cmath>
#include <fstream>

#include "simulationSetup2D.h"
#include "blockLattice2D.h"
#include "lbHelpers.h"
#include "firstOrderLbHelpers.h"
#include "util.h"
#include "io/ostreamManager.h"

namespace olb {


template <typename T, template<typename U> class Lattice>
void iniFirstOrder2D(BlockLatticeView2D<T,Lattice> lattice) {
  TensorFieldBase2D<T,3> const& strainRate = lattice.getDataAnalysis().getStrainRate();

  for (int iX=0; iX<lattice.getNx(); ++iX) {
    for (int iY=0; iY<lattice.getNy(); ++iY) {
      T rho, u[2];
      lattice.get(iX,iY).computeRhoU(rho, u);
      T omega = lattice.get(iX,iY).getDynamics()->getOmega();
      const T uSqr = util::normSqr<T,Lattice<T>::d>(u);
      for (int iPop=0; iPop<Lattice<T>::q; ++iPop) {
        lattice.get(iX,iY)[iPop] =
          lbHelpers<T,Lattice>::equilibrium(iPop, rho, u, uSqr) +
          firstOrderLbHelpers<T,Lattice>::fromStrainToFneq (
            iPop, strainRate.get(iX,iY), omega);
      }
    }
  }
}

template <typename T, template<typename U> class Lattice>
void computePressure2D(ScalarFieldBase2D<T> const& poissonTerm,
                       ScalarFieldBase2D<T>& pressure,
                       T epsilon, T lambda)
{
  OstreamManager clout(std::cout,"computePressure2D");
  int lx = pressure.getNx();
  int ly = pressure.getNy();

  OLB_PRECONDITION(poissonTerm.getNx() == lx);
  OLB_PRECONDITION(poissonTerm.getNy() == ly);

  T averagePoisson = T();
  for (int iX=0; iX<lx; ++iX) {
    for (int iY=0; iY<ly; ++iY) {
      averagePoisson += util::sqr(poissonTerm.get(iX,iY));
    }
  }
  averagePoisson /= (lx*ly);
  averagePoisson = sqrt(averagePoisson);

  int iter=0;
  T maxResidue = (T)1;
  do {
    for (int iX=1; iX<lx-1; ++iX) {
      pressure.get(iX,0) = pressure.get(iX,1);
      pressure.get(iX,ly-1) = pressure.get(iX,ly-2);

//             pressure.get(iX,0) = (-pressure.get(iX,2)+(T)4*pressure.get(iX,1))/(T)3;
//             pressure.get(iX,ly-1) = (-pressure.get(iX,ly-3)+(T)4*pressure.get(iX,ly-2))/(T)3;
    }
    for (int iY=1; iY<ly-1; ++iY) {
      pressure.get(0,iY) = pressure.get(1,iY);
      pressure.get(lx-1,iY) = pressure.get(lx-2,iY);

//             pressure.get(0,iY) = (-pressure.get(2,iY)+(T)4*pressure.get(1,iY))/(T)3;
//             pressure.get(lx-1,iY) = (-pressure.get(lx-3,iY)+(T)4*pressure.get(lx-2,iY))/(T)3;
    }
    pressure.get(0,0)       = pressure.get(1,1);
    pressure.get(lx-1,0   ) = pressure.get(lx-2,1);
    pressure.get(0,ly-1)    = pressure.get(1,ly-2);
    pressure.get(lx-1,ly-1) = pressure.get(lx-2,ly-2);

    for (int iX=1; iX<lx-1; ++iX) {
      for (int iY=1; iY<ly-1; ++iY) {

        T sumPressure =
          pressure.get(iX+1,iY) +
          pressure.get(iX,iY+1) +
          pressure.get(iX-1,iY) +
          pressure.get(iX,iY-1);

        pressure.get(iX,iY) =
          ((T)1-lambda) * pressure.get(iX,iY) +
          (lambda/(T)4) * (sumPressure + poissonTerm.get(iX,iY) );
      }
    }

    maxResidue = std::numeric_limits<T>::min();
    for (int iX=1; iX<lx-1; ++iX) {
      for (int iY=1; iY<ly-1; ++iY) {
        T sumPressure =
          pressure.get(iX+1,iY) +
          pressure.get(iX,iY+1) +
          pressure.get(iX-1,iY) +
          pressure.get(iX,iY-1);
        T residue = fabs(sumPressure -(T)4*pressure.get(iX,iY)
                         + poissonTerm.get(iX,iY));
        if (residue > maxResidue) maxResidue = residue;
      }
    }

    if (iter%400==0) {
      clout << "SOR iteration " << iter
            << ": max residue= "
            << maxResidue/averagePoisson << std::endl;
    }

    ++iter;
  }
  while (maxResidue/averagePoisson>epsilon);

  clout << "1: p=" << pressure.get(lx/2,0) << std::endl;


  T  sumPressure = T();
  for (int iX=1; iX<lx-1; ++iX) {
    for (int iY=1; iY<ly-1; ++iY) {
      sumPressure += pressure.get(iX,iY);
    }
  }
  T averagePressure = sumPressure / ( (T)((lx-2)*(ly-2)) );
  for (int iX=0; iX<lx; ++iX) {
    for (int iY=0; iY<ly; ++iY) {
      pressure.get(iX,iY) -= averagePressure;
    }
  }
  clout << "2: p=" << pressure.get(lx/2,0) << std::endl;
  clout << "Number of SOR iterations: " << iter << std::endl;
  ScalarField2D<T> residueMatrix(lx,ly);
  residueMatrix.construct();
  residueMatrix.reset();
  for (int iX=1; iX<lx-1; ++iX) {
    for (int iY=1; iY<ly-1; ++iY) {
      T sumPressure =
        pressure.get(iX+1,iY) +
        pressure.get(iX,iY+1) +
        pressure.get(iX-1,iY) +
        pressure.get(iX,iY-1);
      T residue = fabs(sumPressure -(T)4*pressure.get(iX,iY)
                       + poissonTerm.get(iX,iY));
      residueMatrix.get(iX,iY) = residue;
    }
  }
}

template <typename T, template<typename U> class Lattice>
void iniPressure2D(BlockLatticeView2D<T,Lattice> lattice,
                   T epsilon, T lambda)
{
  int lx = lattice.getNx();
  int ly = lattice.getNy();

  ScalarField2D<T> pressure(lx, ly);
  pressure.construct(); // Allocate memory
  pressure.reset();     // Reset to zero

  computePressure2D<T,Lattice>(lattice.getDataAnalysis().getPoissonTerm(),
                               pressure,
                               epsilon, lambda );

  for (int iX=0; iX<lx; ++iX) {
    for (int iY=0; iY<ly; ++iY) {
      lattice.get(iX,iY).defineRho (
        pressure.get(iX,iY)*Lattice<T>::invCs2 + (T)1 );
    }
  }
}

template <typename T, template<typename U> class Lattice>
void testLaplace(BlockLatticeView2D<T,Lattice> lattice, T epsilon, T lambda) {
  OstreamManager clout(std::cout,"testLaplace");
  int lx = lattice.getNx();
  int ly = lattice.getNy();

  ScalarFieldBase2D<T> const& poissonTerm = lattice.getDataAnalysis().getPoissonTerm();

  ScalarField2D<T> pressure(lx, ly);
  pressure.construct();
  ScalarField2D<T> pressure2(lx, ly);
  pressure2.construct();

  T averagePoisson = T();
  for (int iX=0; iX<lx; ++iX) {
    for (int iY=0; iY<ly; ++iY) {
      pressure.get(iX,iY) = T();
      averagePoisson += util::sqr(poissonTerm.get(iX,iY));
    }
  }
  averagePoisson /= (lx*ly);
  averagePoisson = sqrt(averagePoisson);

  int iter=0;
  T maxResidue = (T)1;
  do {
    for (int iX=1; iX<lx-1; ++iX) {
      pressure.get(iX,0) = pressure.get(iX,1);
      pressure.get(iX,ly-1) = pressure.get(iX,ly-2);
    }
    for (int iY=1; iY<ly-1; ++iY) {
      pressure.get(0,iY) = pressure.get(1,iY);
      pressure.get(lx-1,iY) = pressure.get(lx-2,iY);
    }
    pressure.get(0,0)       = pressure.get(1,1);
    pressure.get(lx-1,0   ) = pressure.get(lx-2,2);
    pressure.get(0,ly-1)    = pressure.get(1,ly-2);
    pressure.get(lx-1,ly-1) = pressure.get(lx-2,ly-2);

    for (int iX=1; iX<lx-1; ++iX) {
      for (int iY=1; iY<ly-1; ++iY) {

        T sumPressure =
          pressure.get(iX+1,iY) +
          pressure.get(iX,iY+1) +
          pressure.get(iX-1,iY) +
          pressure.get(iX,iY-1);

        pressure.get(iX,iY) =
          ((T)1-lambda) * pressure.get(iX,iY) +
          (lambda/(T)4) * (sumPressure + poissonTerm.get(iX,iY) );
      }
    }

    maxResidue = std::numeric_limits<T>::min();
    for (int iX=1; iX<lx-1; ++iX) {
      for (int iY=1; iY<ly-1; ++iY) {
        T sumPressure =
          pressure.get(iX+1,iY) +
          pressure.get(iX,iY+1) +
          pressure.get(iX-1,iY) +
          pressure.get(iX,iY-1);
        T residue = fabs(sumPressure -(T)4*pressure.get(iX,iY)
                         + poissonTerm.get(iX,iY));
        if (residue > maxResidue) maxResidue = residue;
      }
    }

    if (iter%20==0) {
      clout << "SOR iteration " << iter
            << ": max residue= "
            << maxResidue/averagePoisson << std::endl;
    }
    ++iter;
  }
  while (maxResidue/averagePoisson>epsilon);

  iter = 0;
  T difference = (T)1;
  do {
    for (int iX=1; iX<lx-1; ++iX) {
      pressure2.get(iX,0) = pressure2.get(iX,1);
      pressure2.get(iX,ly-1) = pressure2.get(iX,ly-2);
    }
    for (int iY=1; iY<ly-1; ++iY) {
      pressure2.get(0,iY) = pressure2.get(1,iY);
      pressure2.get(lx-1,iY) = pressure2.get(lx-2,iY);
    }
    pressure2.get(0,0)       = pressure2.get(1,1);
    pressure2.get(lx-1,0   ) = pressure2.get(lx-2,2);
    pressure2.get(0,ly-1)    = pressure2.get(1,ly-2);
    pressure2.get(lx-1,ly-1) = pressure2.get(lx-2,ly-2);

    for (int iX=1; iX<lx-1; ++iX) {
      for (int iY=1; iY<ly-1; ++iY) {

        T sumPressure =
          pressure2.get(iX+1,iY) +
          pressure2.get(iX,iY+1) +
          pressure2.get(iX-1,iY) +
          pressure2.get(iX,iY-1);

        pressure2.get(iX,iY) =
          ((T)1-lambda) * pressure2.get(iX,iY) +
          (lambda/(T)4) * (sumPressure + poissonTerm.get(iX,iY) );
      }
    }

    difference = T();
    for (int iX=0; iX<lx; ++iX) {
      for (int iY=0; iY<ly; ++iY) {
        difference
        += util::sqr(pressure.get(iX,iY)-pressure2.get(iX,iY));
      }
    }
    difference = sqrt(difference/(T)(lx*ly))/4e-4;

    if (iter%20==0) {
      clout << difference << std::endl;
    }
    ++iter;
  }
  while (difference>epsilon);

  for (int iX=0; iX<lx; ++iX) {
    for (int iY=0; iY<ly; ++iY) {
      lattice.get(iX,iY).defineRho (
        pressure.get(iX,iY)*Lattice<T>::invCs2 + (T)1 );
    }
  }
}


template <typename T, template<typename U> class Lattice>
void convergeFixedVelocity(BlockLattice2D<T,Lattice>& lattice,
                           T epsilon, int step)
{
  BlockLatticeView2D<T,Lattice> latticeView(lattice);
  TensorFieldBase2D<T,2> const& velocity = latticeView.getDataAnalysis().getVelocity();

  T maxF = T();
  for (int iX=0; iX<latticeView.getNx(); iX+=step) {
    for (int iY=0; iY<latticeView.getNy(); iY+=step) {
      for (int iF=0; iF<Lattice<T>::q; ++iF) {
        T f = latticeView.get(iX,iY)[iF];
        if (f>maxF) {
          maxF = f;
        }
      }
    }
  }

  std::vector<T> oldValues, currentValues;
  T diff=(T)1;
  do {
    lattice.staticCollide(velocity);
    lattice.stream(true);

    for (int iX=0; iX<latticeView.getNx(); iX+=step) {
      for (int iY=0; iY<latticeView.getNy(); iY+=step) {
        currentValues.push_back (
          latticeView.get(iX,iY)[(iX+iY) % (Lattice<T>::q)] );
      }
    }

    if (oldValues.size() == currentValues.size()) {
      diff = T();
      for (unsigned iVal=0; iVal<oldValues.size(); ++iVal) {
        T candidate = std::abs(currentValues[iVal]-oldValues[iVal])
                      / maxF;
        if (candidate>diff) {
          diff=candidate;
        }
      }
    }
    oldValues.swap(currentValues);
    currentValues.clear();
  }
  while (diff > epsilon);
}

template <typename T, template<typename U> class Lattice>
void testLiShi(BlockLattice2D<T,Lattice>& lattice, T epsilon, T lambda)
{
  OstreamManager clout(std::cout,"testLiShi");
  BlockLatticeView2D<T,Lattice> latticeView(lattice);
  DataAnalysisBase2D<T,Lattice> const& analysis = latticeView.getDataAnalysis();
  TensorFieldBase2D<T,2> const& velocity = analysis.getVelocity();

  int lx = lattice.getNx();
  int ly = lattice.getNy();

  ScalarField2D<T> const& poissonTerm = analysis.getPoissonTerm();

  ScalarField2D<T> pressure(lx, ly);
  pressure.construct();

  T averagePoisson = T();
  for (int iX=0; iX<lx; ++iX) {
    for (int iY=0; iY<ly; ++iY) {
      pressure.get(iX,iY) = T();
      averagePoisson += util::sqr(poissonTerm.get(iX,iY));
    }
  }
  averagePoisson /= (lx*ly);
  averagePoisson = sqrt(averagePoisson);

  int iter=0;
  T maxResidue = (T)1;
  do {
    for (int iX=1; iX<lx-1; ++iX) {
      pressure.get(iX,0) = pressure.get(iX,1);
      pressure.get(iX,ly-1) = pressure.get(iX,ly-2);
    }
    for (int iY=1; iY<ly-1; ++iY) {
      pressure.get(0,iY) = pressure.get(1,iY);
      pressure.get(lx-1,iY) = pressure.get(lx-2,iY);
    }
    pressure.get(0,0)       = pressure.get(1,1);
    pressure.get(lx-1,0   ) = pressure.get(lx-2,2);
    pressure.get(0,ly-1)    = pressure.get(1,ly-2);
    pressure.get(lx-1,ly-1) = pressure.get(lx-2,ly-2);

    for (int iX=1; iX<lx-1; ++iX) {
      for (int iY=1; iY<ly-1; ++iY) {

        T sumPressure =
          pressure.get(iX+1,iY) +
          pressure.get(iX,iY+1) +
          pressure.get(iX-1,iY) +
          pressure.get(iX,iY-1);

        pressure.get(iX,iY) =
          ((T)1-lambda) * pressure.get(iX,iY) +
          (lambda/(T)4) * (sumPressure + poissonTerm.get(iX,iY) );
      }
    }

    maxResidue = std::numeric_limits<T>::min();
    for (int iX=1; iX<lx-1; ++iX) {
      for (int iY=1; iY<ly-1; ++iY) {
        T sumPressure =
          pressure.get(iX+1,iY) +
          pressure.get(iX,iY+1) +
          pressure.get(iX-1,iY) +
          pressure.get(iX,iY-1);
        T residue = fabs(sumPressure -(T)4*pressure.get(iX,iY)
                         + poissonTerm.get(iX,iY));
        if (residue > maxResidue) maxResidue = residue;
      }
    }

    if (iter%20==0) {
      clout << "SOR iteration " << iter
            << ": max residue= "
            << maxResidue/averagePoisson << std::endl;
    }
    ++iter;
  }
  while (maxResidue/averagePoisson>epsilon);

  T diff=(T)1;
  for(int i=0; i<50000; ++i) {
    lattice.staticCollide(velocity);
    lattice.stream();

    T averageRho = T();
    for (int iX=0; iX<lx; ++iX) {
      for (int iY=0; iY<ly; ++iY) {
        averageRho += lattice.get(iX,iY).computeRho();
      }
    }

    averageRho /= (T)(lx*ly);

    T difference = T();
    for (int iX=0; iX<lx; ++iX) {
      for (int iY=0; iY<ly; ++iY) {
        difference += util::sqr(
                        pressure.get(iX,iY)-
                        (lattice.get(iX,iY).computeRho()-averageRho)/3.);
      }
    }
    difference = sqrt(difference/(T)(lx*ly))/4e-4;

    if (i%20==0) {
      clout << difference << std::endl;
    }
  }
  while (diff > epsilon);
}

}  // namespace olb

#endif
