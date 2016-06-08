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

#ifndef FD_BOUNDARIES_2D_HH
#define FD_BOUNDARIES_2D_HH

#include "boundaryPostProcessors2D.h"
#include "finiteDifference2D.h"
#include "blockLattice2D.h"
#include "util.h"
#include "lbHelpers.h"
#include "firstOrderLbHelpers.h"

namespace olb {

///////////  StraightFdBoundaryProcessor2D ///////////////////////////////////

template<typename T, template<typename U> class Lattice, int direction, int orientation>
StraightFdBoundaryProcessor2D<T,Lattice,direction,orientation>::
StraightFdBoundaryProcessor2D(int x0_, int x1_, int y0_, int y1_)
  : x0(x0_), x1(x1_), y0(y0_), y1(y1_)
{
  OLB_PRECONDITION(x0==x1 || y0==y1);
}

template<typename T, template<typename U> class Lattice, int direction,int orientation>
void StraightFdBoundaryProcessor2D<T,Lattice,direction,orientation>::
processSubDomain(BlockLattice2D<T,Lattice>& blockLattice, int x0_, int x1_, int y0_, int y1_)
{
  using namespace olb::util::tensorIndices2D;

  int newX0, newX1, newY0, newY1;
  if ( util::intersect (
         x0, x1, y0, y1,
         x0_, x1_, y0_, y1_,
         newX0, newX1, newY0, newY1 ) )
  {

    int iX;

#ifdef PARALLEL_MODE_OMP
    #pragma omp parallel for
#endif
    for (iX=newX0; iX<=newX1; ++iX) {
      T dx_u[Lattice<T>::d], dy_u[Lattice<T>::d];
      for (int iY=newY0; iY<=newY1; ++iY) {
        Cell<T,Lattice>& cell = blockLattice.get(iX,iY);
        Dynamics<T,Lattice>* dynamics = cell.getDynamics();

        T rho, u[Lattice<T>::d];
        cell.computeRhoU(rho,u);

        interpolateGradients<0>(blockLattice, dx_u, iX, iY);
        interpolateGradients<1>(blockLattice, dy_u, iX, iY);
        T dx_ux = dx_u[0];
        T dy_ux = dy_u[0];
        T dx_uy = dx_u[1];
        T dy_uy = dy_u[1];
        T omega = cell.getDynamics() -> getOmega();
        T sToPi = - rho / Lattice<T>::invCs2 / omega;
        T pi[util::TensorVal<Lattice<T> >::n];
        pi[xx] = (T)2 * dx_ux * sToPi;
        pi[yy] = (T)2 * dy_uy * sToPi;
        pi[xy] = (dx_uy + dy_ux) * sToPi;

        // Computation of the particle distribution functions
        // according to the regularized formula

        T uSqr = util::normSqr<T,2>(u);
        for (int iPop = 0; iPop < Lattice<T>::q; ++iPop) {
          cell[iPop] = dynamics -> computeEquilibrium(iPop,rho,u,uSqr) +
                       firstOrderLbHelpers<T,Lattice>::fromPiToFneq(iPop, pi);
        }
      }
    }
  }
}

template<typename T, template<typename U> class Lattice, int direction,int orientation>
void StraightFdBoundaryProcessor2D<T,Lattice,direction,orientation>::
process(BlockLattice2D<T,Lattice>& blockLattice)
{
  processSubDomain(blockLattice, x0, x1, y0, y1);
}

template<typename T, template<typename U> class Lattice, int direction,int orientation>
template<int deriveDirection>
void StraightFdBoundaryProcessor2D<T,Lattice,direction,orientation>::
interpolateGradients(BlockLattice2D<T,Lattice> const& blockLattice,
                     T velDeriv[Lattice<T>::d], int iX, int iY) const
{
  fd::DirectedGradients2D<T,Lattice,direction,orientation,direction==deriveDirection>::
  interpolateVector(velDeriv, blockLattice, iX, iY);
}

////////  StraightFdBoundaryProcessorGenerator2D ////////////////////////////////

template<typename T, template<typename U> class Lattice, int direction,int orientation>
StraightFdBoundaryProcessorGenerator2D<T,Lattice, direction,orientation>::
StraightFdBoundaryProcessorGenerator2D(int x0_, int x1_, int y0_, int y1_)
  : PostProcessorGenerator2D<T,Lattice>(x0_, x1_, y0_, y1_)
{ }

template<typename T, template<typename U> class Lattice, int direction,int orientation>
PostProcessor2D<T,Lattice>*
StraightFdBoundaryProcessorGenerator2D<T,Lattice,direction,orientation>::generate() const
{
  return new StraightFdBoundaryProcessor2D<T,Lattice,direction,orientation>
         ( this->x0, this->x1, this->y0, this->y1);
}

template<typename T, template<typename U> class Lattice, int direction,int orientation>
PostProcessorGenerator2D<T,Lattice>*
StraightFdBoundaryProcessorGenerator2D<T,Lattice,direction,orientation>::clone() const
{
  return new StraightFdBoundaryProcessorGenerator2D<T,Lattice,direction,orientation>
         (this->x0, this->x1, this->y0, this->y1);
}

/////////// OuterVelocityCornerProcessor2D /////////////////////////////////////

template<typename T, template<typename U> class Lattice, int xNormal,int yNormal>
OuterVelocityCornerProcessor2D<T, Lattice, xNormal, yNormal>::
OuterVelocityCornerProcessor2D(int x_, int y_)
  : x(x_), y(y_)
{ }

template<typename T, template<typename U> class Lattice, int xNormal,int yNormal>
void OuterVelocityCornerProcessor2D<T, Lattice, xNormal, yNormal>::
process(BlockLattice2D<T,Lattice>& blockLattice)
{
  using namespace olb::util::tensorIndices2D;

  T rho10 = blockLattice.get(x-1*xNormal, y-0*yNormal).computeRho();
  T rho01 = blockLattice.get(x-0*xNormal, y-1*yNormal).computeRho();

  T rho20 = blockLattice.get(x-2*xNormal, y-0*yNormal).computeRho();
  T rho02 = blockLattice.get(x-0*xNormal, y-2*yNormal).computeRho();

  T rho = (T)2/(T)3*(rho01+rho10) - (T)1/(T)6*(rho02+rho20);

  T dx_u[Lattice<T>::d], dy_u[Lattice<T>::d];
  fd::DirectedGradients2D<T, Lattice, 0, xNormal, true>::interpolateVector(dx_u, blockLattice, x,y);
  fd::DirectedGradients2D<T, Lattice, 1, yNormal, true>::interpolateVector(dy_u, blockLattice, x,y);
  T dx_ux = dx_u[0];
  T dy_ux = dy_u[0];
  T dx_uy = dx_u[1];
  T dy_uy = dy_u[1];

  Cell<T,Lattice>& cell = blockLattice.get(x,y);
  Dynamics<T,Lattice>* dynamics = cell.getDynamics();
  T omega = dynamics -> getOmega();

  T sToPi = - rho / Lattice<T>::invCs2 / omega;
  T pi[util::TensorVal<Lattice<T> >::n];
  pi[xx] = (T)2 * dx_ux * sToPi;
  pi[yy] = (T)2 * dy_uy * sToPi;
  pi[xy] = (dx_uy + dy_ux) * sToPi;

  // Computation of the particle distribution functions
  // according to the regularized formula
  T u[Lattice<T>::d];
  blockLattice.get(x,y).computeU(u);

  T uSqr = util::normSqr<T,2>(u);
  for (int iPop = 0; iPop < Lattice<T>::q; ++iPop) {
    cell[iPop] =
      dynamics -> computeEquilibrium(iPop,rho,u,uSqr) +
      firstOrderLbHelpers<T,Lattice>::fromPiToFneq(iPop, pi);
  }
}

template<typename T, template<typename U> class Lattice, int xNormal,int yNormal>
void OuterVelocityCornerProcessor2D<T, Lattice, xNormal, yNormal>::
processSubDomain(BlockLattice2D<T,Lattice>& blockLattice,
                 int x0_, int x1_, int y0_, int y1_ )
{
  if (util::contained(x, y, x0_, x1_, y0_, y1_)) {
    process(blockLattice);
  }
}


////////  OuterVelocityCornerProcessorGenerator2D ////////////////////////////

template<typename T, template<typename U> class Lattice, int xNormal,int yNormal>
OuterVelocityCornerProcessorGenerator2D<T, Lattice, xNormal, yNormal>::
OuterVelocityCornerProcessorGenerator2D(int x_, int y_)
  : PostProcessorGenerator2D<T,Lattice>(x_, x_, y_, y_)
{ }

template<typename T, template<typename U> class Lattice, int xNormal,int yNormal>
PostProcessor2D<T,Lattice>*
OuterVelocityCornerProcessorGenerator2D<T, Lattice, xNormal, yNormal>::generate() const
{
  return new OuterVelocityCornerProcessor2D<T, Lattice, xNormal, yNormal>
         ( this->x0, this->y0);
}

template<typename T, template<typename U> class Lattice, int xNormal,int yNormal>
PostProcessorGenerator2D<T,Lattice>*
OuterVelocityCornerProcessorGenerator2D<T, Lattice, xNormal, yNormal>::
clone() const
{
  return new OuterVelocityCornerProcessorGenerator2D<T, Lattice, xNormal, yNormal>
         ( this->x0, this->y0);
}


}  // namespace olb

#endif
