/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2008 Orestis Malaspinas, Andrea Parmigiani, Jonas Latt
 *  Address: EPFL-STI-LIN Station 9, 1015 Lausanne
 *  E-mail: orestis.malaspinas@epfl.ch
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

#ifndef FORCED_SHAN_CHEN_COUPLING_POST_PROCESSOR_2D_HH
#define FORCED_SHAN_CHEN_COUPLING_POST_PROCESSOR_2D_HH

#include "forcedShanChenCouplingPostProcessor2D.h"
#include "core/blockLattice2D.h"
#include "core/util.h"
#include "core/finiteDifference2D.h"

namespace olb {

////////  ForcedShanChenCouplingPostProcessor2D ///////////////////////////////////

template<typename T, template<typename U> class Lattice>
ForcedShanChenCouplingPostProcessor2D <T,Lattice>::
ForcedShanChenCouplingPostProcessor2D(int x0_, int x1_, int y0_, int y1_, T G_,
                                      std::vector<SpatiallyExtendedObject2D*> partners_)
  :  x0(x0_), x1(x1_), y0(y0_), y1(y1_), G(G_), partners(partners_)
{ }

template<typename T, template<typename U> class Lattice>
void ForcedShanChenCouplingPostProcessor2D<T,Lattice>::
processSubDomain( BlockLattice2D<T,Lattice>& blockLattice,
                  int x0_, int x1_, int y0_, int y1_ )
{
  typedef Lattice<T> L;
  enum {
    uOffset     = L::ExternalField::velocityBeginsAt,
    forceOffset = L::ExternalField::forceBeginsAt
  };

  BlockLattice2D<T,Lattice> *partnerLattice = dynamic_cast<BlockLattice2D<T,Lattice> *>(partners[0]);

  int newX0, newX1, newY0, newY1;
  if ( util::intersect ( x0, x1, y0, y1,
                         x0_, x1_, y0_, y1_,
                         newX0, newX1, newY0, newY1 ) )
  {
    int nx = newX1-newX0+3; // include a one-cell boundary
    int ny = newY1-newY0+3; // include a one-cell boundary
    int offsetX = newX0-1;
    int offsetY = newY0-1;
    ScalarField2D<T> rhoField1(nx, ny);
    rhoField1.construct();
    ScalarField2D<T> rhoField2(nx, ny);
    rhoField2.construct();
    // Compute density and velocity on every site of first lattice, and store result
    //   in external scalars; envelope cells are included, because they are needed
    //   to compute the interaction potential in what follows.
    for (int iX=newX0-1; iX<=newX1+1; ++iX) {
      for (int iY=newY0-1; iY<=newY1+1; ++iY) {
        Cell<T,Lattice>& cell = blockLattice.get(iX,iY);
        rhoField1.get(iX-offsetX, iY-offsetY) = cell.computeRho();
        T* j = cell.getExternal(uOffset);
        lbHelpers<T,Lattice>::computeJ(cell,j);
      }
    }

    // Compute density and velocity on every site of second lattice, and store result
    //   in external scalars; envelope cells are included, because they are needed
    //   to compute the interaction potential in what follows.
    for (int iX=newX0-1; iX<=newX1+1; ++iX) {
      for (int iY=newY0-1; iY<=newY1+1; ++iY) {
        Cell<T,Lattice>& cell = partnerLattice->get(iX,iY);
        rhoField2.get(iX-offsetX, iY-offsetY) = cell.computeRho();
        T* j = cell.getExternal(uOffset);
        lbHelpers<T,Lattice>::computeJ(cell,j);
      }
    }

    for (int iX=newX0; iX<=newX1; ++iX) {
      for (int iY=newY0; iY<=newY1; ++iY) {
        Cell<T,Lattice>& blockCell   = blockLattice.get(iX,iY);
        Cell<T,Lattice>& partnerCell = partnerLattice->get(iX,iY);

        // Computation of the common velocity, shared among the two populations
        T rhoTot = rhoField1.get(iX-offsetX, iY-offsetY) +
                   rhoField2.get(iX-offsetX, iY-offsetY);
        T uTot[Lattice<T>::d];
        T *blockU = blockCell.getExternal(uOffset);      // contains precomputed value rho*u
        T *partnerU = partnerCell.getExternal(uOffset);  // contains precomputed value rho*u
        for (int iD = 0; iD < Lattice<T>::d; ++iD) {
          uTot[iD] = (blockU[iD] + partnerU[iD]) / rhoTot;
        }

        // Computation of the interaction potential
        T rhoBlockContribution[L::d]   = {T(), T()};
        T rhoPartnerContribution[L::d] = {T(), T()};
        for (int iPop = 0; iPop < L::q; ++iPop) {
          int nextX = iX + L::c[iPop][0];
          int nextY = iY + L::c[iPop][1];
          T blockRho   = rhoField1.get(nextX-offsetX, nextY-offsetY);
          T partnerRho = rhoField2.get(nextX-offsetX, nextY-offsetY);
          for (int iD = 0; iD < L::d; ++iD) {
            rhoBlockContribution[iD]   += blockRho * L::c[iPop][iD];
            rhoPartnerContribution[iD] += partnerRho * L::c[iPop][iD];
          }
        }

        // Computation and storage of the final velocity, consisting
        //   of u and the momentum difference due to interaction
        //   potential plus external force
        T *blockForce   = blockCell.getExternal(forceOffset);
        T *partnerForce = partnerCell.getExternal(forceOffset);
        T blockOmega   = blockCell.getDynamics()->getOmega();
        T partnerOmega = partnerCell.getDynamics()->getOmega();
        for (int iD = 0; iD < L::d; ++iD) {
          blockU[iD] = uTot[iD] + 1./blockOmega *
                       (blockForce[iD] - G * rhoPartnerContribution[iD] );
          partnerU[iD] = uTot[iD] + 1./partnerOmega *
                         (partnerForce[iD] - G * rhoBlockContribution[iD] );
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice>
void ForcedShanChenCouplingPostProcessor2D<T,Lattice>::
process(BlockLattice2D<T,Lattice>& blockLattice)
{
  processSubDomain(blockLattice, x0, x1, y0, y1);
}


/// LatticeCouplingGenerator for NS coupling

template<typename T, template<typename U> class Lattice>
ForcedShanChenCouplingGenerator2D<T,Lattice>::ForcedShanChenCouplingGenerator2D (
  int x0_, int x1_, int y0_, int y1_, T G_ )
  : LatticeCouplingGenerator2D<T,Lattice>(x0_, x1_, y0_, y1_), G(G_)
{ }

template<typename T, template<typename U> class Lattice>
PostProcessor2D<T,Lattice>* ForcedShanChenCouplingGenerator2D<T,Lattice>::generate (
  std::vector<SpatiallyExtendedObject2D*> partners) const
{
  return new ForcedShanChenCouplingPostProcessor2D<T,Lattice>(
           this->x0,this->x1,this->y0,this->y1,G, partners);
}

template<typename T, template<typename U> class Lattice>
LatticeCouplingGenerator2D<T,Lattice>* ForcedShanChenCouplingGenerator2D<T,Lattice>::clone() const {
  return new ForcedShanChenCouplingGenerator2D<T,Lattice>(*this);
}



}  // namespace olb

#endif
