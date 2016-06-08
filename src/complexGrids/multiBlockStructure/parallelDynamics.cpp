/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007, 2008 Jonas Latt
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
 * Parallel dynamics object -- template instantiation.
 */

#include "complexGrids/mpiManager/mpiManager.h"
#include "parallelDynamics.h"
#include "parallelDynamics.hh"
#include "core/latticeDescriptors.h"
#include "core/latticeDescriptors.hh"

namespace olb {

#ifdef PARALLEL_MODE_MPI
template class ParallelDynamics<double, descriptors::D2Q9Descriptor>;
template class ConstParallelDynamics<double, descriptors::D2Q9Descriptor>;

template class ParallelDynamics<double, descriptors::D3Q19Descriptor>;
template class ConstParallelDynamics<double, descriptors::D3Q19Descriptor>;
#endif

}
