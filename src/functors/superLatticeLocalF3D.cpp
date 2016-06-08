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

#include "superLatticeLocalF3D.h"
#include "superLatticeLocalF3D.hh"
#include "core/latticeDescriptors.h"

namespace olb {

template class SuperLatticeDissipation3D<double,descriptors::D3Q19Descriptor>;
template class SuperLatticeDensity3D<double,descriptors::D3Q19Descriptor>;
template class SuperLatticeVelocity3D<double,descriptors::D3Q19Descriptor>;
template class SuperLatticeGeometry3D<double,descriptors::D3Q19Descriptor>;
template class SuperLatticeRank3D<double,descriptors::D3Q19Descriptor>;
template class SuperLatticeCuboid3D<double,descriptors::D3Q19Descriptor>;
template class SuperLatticePhysPressure3D<double,descriptors::D3Q19Descriptor>;
template class SuperLatticePhysVelocity3D<double,descriptors::D3Q19Descriptor>;
template class SuperLatticePhysBoundaryForce3D<double,descriptors::D3Q19Descriptor>;
template class SuperLatticePhysCorrBoundaryForce3D<double,descriptors::D3Q19Descriptor>;
template class SuperLatticePorosity3D<double,descriptors::D3Q19Descriptor>;
template class SuperLatticePhysPermeability3D<double,descriptors::D3Q19Descriptor>;
template class SuperLatticePhysDarcyForce3D<double,descriptors::D3Q19Descriptor>;
template class SuperLatticeAverage3D<double,descriptors::D3Q19Descriptor>;
template class SuperL2Norm3D<double,descriptors::D3Q19Descriptor>;

} // end namespace olb
