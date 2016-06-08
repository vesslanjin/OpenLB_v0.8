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

#ifndef OFF_BOUNDARY_POST_PROCESSORS_2D_H
#define OFF_BOUNDARY_POST_PROCESSORS_2D_H

#include "postProcessing.h"
#include "blockLattice2D.h"

namespace olb {

/**
* This class computes the Linear Bouzidi BC
*/

template<typename T, template<typename U> class Lattice>
class FixedBouzidiLinearPostProcessor2D : public LocalPostProcessor2D<T,Lattice>
{
public:
  FixedBouzidiLinearPostProcessor2D(int x_, int y_, int dir_, T dist_);
  virtual int extent() const { return 1; }
  virtual int extent(int whichDirection) const { return 1; }
  virtual void process(BlockLattice2D<T,Lattice>& blockLattice);
  virtual void processSubDomain(BlockLattice2D<T,Lattice>& blockLattice,
                                int x0_, int x1_, int y0_, int y1_ );
private:
  int x, y;
  int xN, yN, xB, yB;
  int dir, opp, dir2;
  T q, dist;
};

template<typename T, template<typename U> class Lattice>
class FixedBounceBackPostProcessor2D : public LocalPostProcessor2D<T,Lattice>
{
public:
  FixedBounceBackPostProcessor2D(int x_, int y_, int dir_, T dist_);
  virtual int extent() const { return 1; }
  virtual int extent(int whichDirection) const { return 1; }
  virtual void process(BlockLattice2D<T,Lattice>& blockLattice);
  virtual void processSubDomain(BlockLattice2D<T,Lattice>& blockLattice,
                                int x0_, int x1_, int y0_, int y1_ );
private:
  int x, y;
  int xN, yN;
  int dir, opp;
  T dist;
};


template<typename T, template<typename U> class Lattice>
class VelocityBouzidiLinearPostProcessor2D : public LocalPostProcessor2D<T,Lattice>
{
public:
  VelocityBouzidiLinearPostProcessor2D(int x_, int y_, int dir_, T dist_, T uX_, T uY_);
  virtual int extent() const { return 1; }
  virtual int extent(int whichDirection) const { return 1; }
  virtual void process(BlockLattice2D<T,Lattice>& blockLattice);
  virtual void processSubDomain(BlockLattice2D<T,Lattice>& blockLattice,
                                int x0_, int x1_, int y0_, int y1_ );
private:
  int x, y;
  int xN, yN, xB, yB;
  int dir, opp, dir2;
  T q, dist;
  T u, uX, uY;
};

template<typename T, template<typename U> class Lattice>
class VelocityBounceBackPostProcessor2D : public LocalPostProcessor2D<T,Lattice>
{
public:
  VelocityBounceBackPostProcessor2D(int x_, int y_, int dir_, T dist_, T uX_, T uY_);
  virtual int extent() const { return 1; }
  virtual int extent(int whichDirection) const { return 1; }
  virtual void process(BlockLattice2D<T,Lattice>& blockLattice);
  virtual void processSubDomain(BlockLattice2D<T,Lattice>& blockLattice,
                                int x0_, int x1_, int y0_, int y1_ );
private:
  int x, y;
  int xN, yN;
  int dir, opp;
  T dist;
  T u, uX, uY;
};

/**
* Linear Bouzidi BC Generator
*/

template<typename T, template<typename U> class Lattice>
class FixedBouzidiLinearPostProcessorGenerator2D : public PostProcessorGenerator2D<T,Lattice>
{
public:
    FixedBouzidiLinearPostProcessorGenerator2D(int x_, int y_, int dir_, T dist_);
  virtual PostProcessor2D<T,Lattice>* generate() const;
  virtual PostProcessorGenerator2D<T,Lattice>*  clone() const;
private:
  int x, y;
  int dir;
  T dist;
};

template<typename T, template<typename U> class Lattice>
class FixedBounceBackPostProcessorGenerator2D : public PostProcessorGenerator2D<T,Lattice>
{
public:
  FixedBounceBackPostProcessorGenerator2D(int x_, int y_, int dir_, T dist_);
  virtual PostProcessor2D<T,Lattice>* generate() const;
  virtual PostProcessorGenerator2D<T,Lattice>*  clone() const;
private:
  int x, y;
  int dir;
  T dist;
};

template<typename T, template<typename U> class Lattice>
class VelocityBouzidiLinearPostProcessorGenerator2D : public PostProcessorGenerator2D<T,Lattice>
{
public:
    VelocityBouzidiLinearPostProcessorGenerator2D(int x_, int y_, int dir_, T dist_, T uX_, T uY_);
  virtual PostProcessor2D<T,Lattice>* generate() const;
  virtual PostProcessorGenerator2D<T,Lattice>*  clone() const;
private:
  int x, y;
  int dir;
  T dist;
  T uX, uY;
};

template<typename T, template<typename U> class Lattice>
class VelocityBounceBackPostProcessorGenerator2D : public PostProcessorGenerator2D<T,Lattice>
{
public:
  VelocityBounceBackPostProcessorGenerator2D(int x_, int y_, int dir_, T dist_, T uX_, T uY_);
  virtual PostProcessor2D<T,Lattice>* generate() const;
  virtual PostProcessorGenerator2D<T,Lattice>*  clone() const;
private:
  int x, y;
  int dir;
  T dist;
  T uX, uY;
};

}

#endif
