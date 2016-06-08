/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Jonas Kratzke, Mathias J. Krause
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

#ifndef OFF_BOUNDARY_POST_PROCESSORS_2D_HH
#define OFF_BOUNDARY_POST_PROCESSORS_2D_HH

#include "offBoundaryPostProcessors2D.h"
#include "blockLattice2D.h"
#include "util.h"
#include "cell.h"

namespace olb {

/////////// LinearBouzidiPostProcessor2D /////////////////////////////////////

      /* Bouzidi Interpolation scheme of first order
       *
       * fluid nodes               wall  solid node
       * --o-------<-o->-----<-o->--|----x----
       *            xB         x        xN
       * directions: --> dir
       *             <-- opp
       *
      */

template<typename T, template<typename U> class Lattice>
FixedBouzidiLinearPostProcessor2D<T,Lattice>::
FixedBouzidiLinearPostProcessor2D(int x_, int y_, int dir_, T dist_)
  : x(x_), y(y_), dir(dir_), dist(dist_)
{
  if (dist < 0 || dist > 1)
    std::cout << "WARNING: Bogus distance at (" << x << "," << y << "): "
              << dist << std::endl;

  typedef Lattice<T> L;
  const int* c = L::c[dir];
  opp = util::opposite<L>(dir);
  xN = x + c[0];
  yN = y + c[1];

  if (dist >= 0.5) {
    xB = x - c[0];
    yB = y - c[1];
    q = 1/(2*dist);
    dir2 = opp;
  }
  else {
    xB = x;
    yB = y;
    q = 2*dist;
    dir2 = dir;
  }
/*
  std::cout << "FixedLinear (" << x << "," << y <<
    "), dir: " << dir << ", nP: (" << xN << "," << yN <<
    "), opp: " << opp << ", bP: (" << xB << "," << yB <<
    "), dist: " << dist << ", q: " << q << std::endl;
*/
}

template<typename T, template<typename U> class Lattice>
void FixedBouzidiLinearPostProcessor2D<T,Lattice>::
processSubDomain(BlockLattice2D<T,Lattice>& blockLattice, int x0_, int x1_, int y0_, int y1_)
{
  if (util::contained(x, y, x0_, x1_, y0_, y1_))
    process(blockLattice);
}

template<typename T, template<typename U> class Lattice>
void FixedBouzidiLinearPostProcessor2D<T,Lattice>::
process(BlockLattice2D<T,Lattice>& blockLattice)
{
  blockLattice.get(x,y)[opp] = q*blockLattice.get(xN,yN)[dir] +
                               (1-q)*blockLattice.get(xB,yB)[dir2];
}

template<typename T, template<typename U> class Lattice>
VelocityBouzidiLinearPostProcessor2D<T,Lattice>::
VelocityBouzidiLinearPostProcessor2D(int x_, int y_, int dir_, T dist_, T uX_, T uY_)
  : x(x_), y(y_), dir(dir_), dist(dist_), uX(uX_), uY(uY_)
{
  if (dist < 0 || dist > 1)
    std::cout << "WARNING: Bogus distance at (" << x << "," << y << "): "
              << dist << std::endl;

  typedef Lattice<T> L;
  const int* c = L::c[dir];
  opp = util::opposite<L>(dir);
  xN = x + c[0];
  yN = y + c[1];

  if (dist >= 0.5) {
    u = L::invCs2 * L::t[dir] * (c[0]*uX + c[1]*uY)/dist;
    xB = x - c[0];
    yB = y - c[1];
    q = 1/(2*dist);
    dir2 = opp;
  }
  else {
    u = 2 * L::invCs2 * L::t[dir] * (c[0]*uX + c[1]*uY);
    xB = x;
    yB = y;
    q = 2*dist;
    dir2 = dir;
  }
  /*
  std::cout << "process (" << x << "," << y <<
    "), dir: " << dir << ", nP: (" << xN << "," << yN <<
    "), opp: " << opp << ", bP: (" << xB << "," << yB <<
    "), u: " << u << ", U: (" << uX << "," << uY <<
    "), dist: " << dist << ", q: " << q << std::endl;
  */
}

template<typename T, template<typename U> class Lattice>
void VelocityBouzidiLinearPostProcessor2D<T,Lattice>::
processSubDomain(BlockLattice2D<T,Lattice>& blockLattice, int x0_, int x1_, int y0_, int y1_)
{
  if (util::contained(x, y, x0_, x1_, y0_, y1_))
    process(blockLattice);
}

template<typename T, template<typename U> class Lattice>
void VelocityBouzidiLinearPostProcessor2D<T,Lattice>::
process(BlockLattice2D<T,Lattice>& blockLattice)
{
  blockLattice.get(x,y)[opp] = q*blockLattice.get(xN,yN)[dir] +
                               (1-q)*blockLattice.get(xB,yB)[dir2] + u;
}

//////// CornerBouzidiPostProcessor2D ///////////////////

template<typename T, template<typename U> class Lattice>
FixedBounceBackPostProcessor2D<T,Lattice>::
FixedBounceBackPostProcessor2D(int x_, int y_, int dir_, T dist_)
  : x(x_), y(y_), dir(dir_), dist(dist_)
{
  if (dist < 0 || dist > 1)
    std::cout << "WARNING: Bogus distance at (" << x << "," << y << "): "
              << dist << std::endl;

  typedef Lattice<T> L;
  const int* c = L::c[dir];
  opp = util::opposite<L>(dir);
  xN = x + c[0];
  yN = y + c[1];
/*
  std::cout << "Corner (" << x << "," << y <<
      "), dir: " << dir << ", nP: (" << xN << "," << yN <<
      "), dist: " << dist << std::endl;
*/
}

template<typename T, template<typename U> class Lattice>
void FixedBounceBackPostProcessor2D<T,Lattice>::
processSubDomain(BlockLattice2D<T,Lattice>& blockLattice, int x0_, int x1_, int y0_, int y1_)
{
  if (util::contained(x, y, x0_, x1_, y0_, y1_))
    process(blockLattice);
}

template<typename T, template<typename U> class Lattice>
void FixedBounceBackPostProcessor2D<T,Lattice>::
process(BlockLattice2D<T,Lattice>& blockLattice)
{
  blockLattice.get(x,y)[opp] = blockLattice.get(xN,yN)[dir];
}

template<typename T, template<typename U> class Lattice>
VelocityBounceBackPostProcessor2D<T,Lattice>::
VelocityBounceBackPostProcessor2D(int x_, int y_, int dir_, T dist_, T uX_, T uY_)
  : x(x_), y(y_), dir(dir_), dist(dist_), uX(uX_), uY(uY_)
{
  if (dist < 0 || dist > 1)
    std::cout << "WARNING: Bogus distance at (" << x << "," << y << "): "
              << dist << std::endl;

  typedef Lattice<T> L;
  const int* c = L::c[dir];
  opp = util::opposite<L>(dir);
  xN = x + c[0];
  yN = y + c[1];

  u = 2 * L::invCs2 * L::t[dir] * (c[0]*uX + c[1]*uY);
/*
  std::cout << "Corner (" << x << "," << y <<
      "), dir: " << dir << ", nP: (" << xN << "," << yN <<
      "), u: " << u << ", U: (" << uX << "," << uY <<
      "), dist: " << dist << std::endl;
*/
}

template<typename T, template<typename U> class Lattice>
void VelocityBounceBackPostProcessor2D<T,Lattice>::
processSubDomain(BlockLattice2D<T,Lattice>& blockLattice, int x0_, int x1_, int y0_, int y1_)
{
  if (util::contained(x, y, x0_, x1_, y0_, y1_))
    process(blockLattice);
}

template<typename T, template<typename U> class Lattice>
void VelocityBounceBackPostProcessor2D<T,Lattice>::
process(BlockLattice2D<T,Lattice>& blockLattice)
{
  blockLattice.get(x,y)[opp] = blockLattice.get(xN,yN)[dir] + u;
}

////////  LinearBouzidiBoundaryPostProcessorGenerator ////////////////////////////////

template<typename T, template<typename U> class Lattice>
FixedBouzidiLinearPostProcessorGenerator2D<T,Lattice>::
FixedBouzidiLinearPostProcessorGenerator2D(int x_, int y_, int dir_, T dist_)
  : PostProcessorGenerator2D<T,Lattice>(x_, x_, y_, y_),
    x(x_), y(y_), dir(dir_), dist(dist_)
{ }

template<typename T, template<typename U> class Lattice>
PostProcessor2D<T,Lattice>*
FixedBouzidiLinearPostProcessorGenerator2D<T,Lattice>::generate() const
{
  return new FixedBouzidiLinearPostProcessor2D<T,Lattice>
         ( this->x, this->y, this->dir, this->dist);
}

template<typename T, template<typename U> class Lattice>
PostProcessorGenerator2D<T,Lattice>*
FixedBouzidiLinearPostProcessorGenerator2D<T,Lattice>::clone() const
{
  return new FixedBouzidiLinearPostProcessorGenerator2D<T,Lattice>
         (this->x, this->y, this->dir, this->dist);
}

template<typename T, template<typename U> class Lattice>
VelocityBouzidiLinearPostProcessorGenerator2D<T,Lattice>::
VelocityBouzidiLinearPostProcessorGenerator2D(int x_, int y_, int dir_, T dist_, T uX_, T uY_)
  : PostProcessorGenerator2D<T,Lattice>(x_, x_, y_, y_),
    x(x_), y(y_), dir(dir_), dist(dist_), uX(uX_), uY(uY_)
{ }

template<typename T, template<typename U> class Lattice>
PostProcessor2D<T,Lattice>*
VelocityBouzidiLinearPostProcessorGenerator2D<T,Lattice>::generate() const
{
  return new VelocityBouzidiLinearPostProcessor2D<T,Lattice>
         ( this->x, this->y, this->dir, this->dist, this->uX, this->uY );
}

template<typename T, template<typename U> class Lattice>
PostProcessorGenerator2D<T,Lattice>*
VelocityBouzidiLinearPostProcessorGenerator2D<T,Lattice>::clone() const
{
  return new VelocityBouzidiLinearPostProcessorGenerator2D<T,Lattice>
         (this->x, this->y, this->dir, this->dist, this->uX, this->uY);
}

/////////// CornerBouzidiBoundaryPostProcessorGenerator /////////////////////////////////////

template<typename T, template<typename U> class Lattice>
FixedBounceBackPostProcessorGenerator2D<T,Lattice>::
FixedBounceBackPostProcessorGenerator2D(int x_, int y_, int dir_, T dist_)
  : PostProcessorGenerator2D<T,Lattice>(x_, x_, y_, y_),
    x(x_), y(y_), dir(dir_), dist(dist_)
{ }

template<typename T, template<typename U> class Lattice>
PostProcessor2D<T,Lattice>*
FixedBounceBackPostProcessorGenerator2D<T,Lattice>::generate() const
{
  return new FixedBounceBackPostProcessor2D<T,Lattice>
         ( this->x, this->y, this->dir, this->dist);
}

template<typename T, template<typename U> class Lattice>
PostProcessorGenerator2D<T,Lattice>*
FixedBounceBackPostProcessorGenerator2D<T,Lattice>::clone() const
{
  return new FixedBounceBackPostProcessorGenerator2D<T,Lattice>
         (this->x, this->y, this->dir, this->dist);
}

template<typename T, template<typename U> class Lattice>
VelocityBounceBackPostProcessorGenerator2D<T,Lattice>::
VelocityBounceBackPostProcessorGenerator2D(int x_, int y_, int dir_, T dist_, T uX_, T uY_)
  : PostProcessorGenerator2D<T,Lattice>(x_, x_, y_, y_),
    x(x_), y(y_), dir(dir_), dist(dist_), uX(uX_), uY(uY_)
{ }

template<typename T, template<typename U> class Lattice>
PostProcessor2D<T,Lattice>*
VelocityBounceBackPostProcessorGenerator2D<T,Lattice>::generate() const
{
  return new VelocityBounceBackPostProcessor2D<T,Lattice>
         ( this->x, this->y, this->dir, this->dist, this->uX, this->uY );
}

template<typename T, template<typename U> class Lattice>
PostProcessorGenerator2D<T,Lattice>*
VelocityBounceBackPostProcessorGenerator2D<T,Lattice>::clone() const
{
  return new VelocityBounceBackPostProcessorGenerator2D<T,Lattice>
         (this->x, this->y, this->dir, this->dist, this->uX, this->uY);
}

}  // namespace olb

#endif
