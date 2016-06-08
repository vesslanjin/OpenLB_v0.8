/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Lukas Baron, Tim Dornieden, Mathias J. Krause,
 *  Albert Mink
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

#ifndef SUPER_LATTICE_BASE_F_2D_HH
#define SUPER_LATTICE_BASE_F_2D_HH

#include<vector>    // for generic i/o

#include "superLatticeBaseF2D.h"


namespace olb {

template<typename T, template<typename U> class DESCRIPTOR> class SuperLatticeF2D;

template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeF2D<T,DESCRIPTOR>::SuperLatticeF2D(SuperLattice2D<T,DESCRIPTOR>& _sLattice, int targetDim)
    : GenericF<T,int>(targetDim,3), sLattice(_sLattice) { }

template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticePhysF2D<T,DESCRIPTOR>::SuperLatticePhysF2D(SuperLattice2D<T,DESCRIPTOR>& _sLattice, const LBconverter<T>& _converter, int targetDim)
    : SuperLatticeF2D<T,DESCRIPTOR>(_sLattice, targetDim), converter(_converter) { }


} // end namespace olb

#endif
