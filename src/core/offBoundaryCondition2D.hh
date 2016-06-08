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

/** \file
 * A helper for initialising 2D boundaries -- generic implementation.
 */
#ifndef OFF_BOUNDARY_CONDITION_2D_HH
#define OFF_BOUNDARY_CONDITION_2D_HH

#include "offBoundaryCondition2D.h"
#include "offBoundaryInstantiator2D.h"

namespace olb {

/**
* Boundary Managers provide specific Boundary Processors by creating them
*/

template<typename T, template<typename U> class Lattice, class MixinDynamics>
class BouzidiBoundaryManager2D {
public:

  static PostProcessorGenerator2D<T,Lattice>*
  getOnePointFixedBoundaryProcessor(int x, int y, int dir, T dist);
  static PostProcessorGenerator2D<T,Lattice>*
  getTwoPointFixedBoundaryProcessor(int x, int y, int dir, T dist);
  static PostProcessorGenerator2D<T,Lattice>*
  getThreePointFixedBoundaryProcessor(int x, int y, int dir, T dist);
  static PostProcessorGenerator2D<T,Lattice>*
  getOnePointVelocityBoundaryProcessor(int x, int y, int dir, T dist, T uX, T uY);
  static PostProcessorGenerator2D<T,Lattice>*
  getTwoPointVelocityBoundaryProcessor(int x, int y, int dir, T dist, T uX, T uY);
  static PostProcessorGenerator2D<T,Lattice>*
  getThreePointVelocityBoundaryProcessor(int x, int y, int dir, T dist, T uX, T uY);
};

////////// BouzidiBoundaryManager2D /////////////////////////////////////////

template<typename T, template<typename U> class Lattice, class MixinDynamics>
PostProcessorGenerator2D<T,Lattice>*
BouzidiBoundaryManager2D<T,Lattice,MixinDynamics>::
getOnePointFixedBoundaryProcessor(int x, int y, int dir, T dist)
{
  return new FixedBounceBackPostProcessorGenerator2D
         <T, Lattice>(x, y, dir, dist);
}

template<typename T, template<typename U> class Lattice, class MixinDynamics>
PostProcessorGenerator2D<T,Lattice>*
BouzidiBoundaryManager2D<T,Lattice,MixinDynamics>::
getTwoPointFixedBoundaryProcessor(int x, int y, int dir, T dist)
{
  return new FixedBouzidiLinearPostProcessorGenerator2D
         <T, Lattice>(x, y, dir, dist);
}

template<typename T, template<typename U> class Lattice, class MixinDynamics>
PostProcessorGenerator2D<T,Lattice>*
BouzidiBoundaryManager2D<T,Lattice,MixinDynamics>::
getThreePointFixedBoundaryProcessor(int x, int y, int dir, T dist)
{
  return new FixedBouzidiLinearPostProcessorGenerator2D
         <T, Lattice>(x, y, dir, dist);
}

template<typename T, template<typename U> class Lattice, class MixinDynamics>
PostProcessorGenerator2D<T,Lattice>*
BouzidiBoundaryManager2D<T,Lattice,MixinDynamics>::
getOnePointVelocityBoundaryProcessor(int x, int y, int dir, T dist, T uX, T uY)
{
  return new VelocityBounceBackPostProcessorGenerator2D
         <T, Lattice>(x, y, dir, dist, uX, uY);
}

template<typename T, template<typename U> class Lattice, class MixinDynamics>
PostProcessorGenerator2D<T,Lattice>*
BouzidiBoundaryManager2D<T,Lattice,MixinDynamics>::
getTwoPointVelocityBoundaryProcessor(int x, int y, int dir, T dist, T uX, T uY)
{
  return new VelocityBouzidiLinearPostProcessorGenerator2D
         <T, Lattice>(x, y, dir, dist, uX, uY);
}

template<typename T, template<typename U> class Lattice, class MixinDynamics>
PostProcessorGenerator2D<T,Lattice>*
BouzidiBoundaryManager2D<T,Lattice,MixinDynamics>::
getThreePointVelocityBoundaryProcessor(int x, int y, int dir, T dist, T uX, T uY)
{
  return new VelocityBouzidiLinearPostProcessorGenerator2D
         <T, Lattice>(x, y, dir, dist, uX, uY);
}

////////// Factory functions //////////////////////////////////////////////////

template<typename T, template<typename U> class Lattice, typename MixinDynamics>
OffLatticeBoundaryCondition2D<T,Lattice>*
createBouzidiBoundaryCondition2D(BlockStructure2D<T,Lattice>& block) {
  return new OffBoundaryConditionInstantiator2D <
         T, Lattice,
         BouzidiBoundaryManager2D<T,Lattice, MixinDynamics> > (block);
}

}  // namespace olb

#endif
