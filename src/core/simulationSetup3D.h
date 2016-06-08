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

#ifndef SIMULATION_SETUP_3D_H
#define SIMULATION_SETUP_3D_H

#include "blockLattice3D.h"
#include "blockLatticeView3D.h"


namespace olb {

template <typename T, template<typename U> class Lattice>
void iniFirstOrder3D(BlockLatticeView3D<T,Lattice> lattice);

template <typename T, template<typename U> class Lattice>
void convergeFixedVelocity(BlockLattice3D<T,Lattice>& lattice,
                           T epsilon, int step=10);

template <typename T, template<typename U> class Lattice>
void iniPressure3D(BlockLatticeView3D<T,Lattice> lattice,
                   T epsilon, T lambda=1.8);

}  // namespace olb

#endif
