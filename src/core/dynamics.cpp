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

/** \file
 * A collection of dynamics classes (e.g. BGK) with which a Cell object
 * can be instantiated -- template instantiation.
 */
#include "dynamics.h"
#include "dynamics.hh"
#include "latticeDescriptors.h"
#include "latticeDescriptors.hh"

namespace olb {

template class Dynamics<double, descriptors::D2Q9Descriptor>;
template class Momenta<double, descriptors::D2Q9Descriptor>;
template class BasicDynamics<double, descriptors::D2Q9Descriptor>;
template class BGKdynamics<double, descriptors::D2Q9Descriptor>;
template class ConstRhoBGKdynamics<double, descriptors::D2Q9Descriptor>;
template class IncBGKdynamics<double, descriptors::D2Q9Descriptor>;
template class RLBdynamics<double, descriptors::D2Q9Descriptor>;
template class CombinedRLBdynamics<double, descriptors::D2Q9Descriptor,
         RLBdynamics<double, descriptors::D2Q9Descriptor> >;
template class CombinedRLBdynamics<double, descriptors::D2Q9Descriptor,
         BGKdynamics<double, descriptors::D2Q9Descriptor> >;
template class BulkMomenta<double, descriptors::D2Q9Descriptor>;
template class BounceBack<double, descriptors::D2Q9Descriptor>;
template class NoDynamics<double, descriptors::D2Q9Descriptor>;
template class OffDynamics<double, descriptors::D2Q9Descriptor>;

template class Dynamics<double, descriptors::D3Q19Descriptor>;
template class Momenta<double, descriptors::D3Q19Descriptor>;
template class BasicDynamics<double, descriptors::D3Q19Descriptor>;
template class BGKdynamics<double, descriptors::D3Q19Descriptor>;
template class ConstRhoBGKdynamics<double, descriptors::D3Q19Descriptor>;
template class IncBGKdynamics<double, descriptors::D3Q19Descriptor>;
template class RLBdynamics<double, descriptors::D3Q19Descriptor>;
template class CombinedRLBdynamics<double, descriptors::D3Q19Descriptor,
         RLBdynamics<double, descriptors::D3Q19Descriptor> >;
template class CombinedRLBdynamics<double, descriptors::D3Q19Descriptor,
         BGKdynamics<double, descriptors::D3Q19Descriptor> >;
template class BulkMomenta<double, descriptors::D3Q19Descriptor>;
template class BounceBack<double, descriptors::D3Q19Descriptor>;
template class NoDynamics<double, descriptors::D3Q19Descriptor>;
template class OffDynamics<double, descriptors::D3Q19Descriptor>;

namespace instances {

template BulkMomenta<double, descriptors::D2Q9Descriptor>& getBulkMomenta();

template BounceBack<double, descriptors::D2Q9Descriptor>& getBounceBack();

template NoDynamics<double, descriptors::D2Q9Descriptor>& getNoDynamics();

template BulkMomenta<double, descriptors::D3Q19Descriptor>& getBulkMomenta();

template BounceBack<double, descriptors::D3Q19Descriptor>& getBounceBack();

template NoDynamics<double, descriptors::D3Q19Descriptor>& getNoDynamics();

}

}
