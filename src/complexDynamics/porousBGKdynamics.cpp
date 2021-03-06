/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Mathias J. Krause, Jonas Latt
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

#include "porousBGKdynamics.h"
#include "porousBGKdynamics.hh"
#include "porousBGKdynamicsDescriptors.h"
#include "core/latticeDescriptors.h"
#include "core/latticeDescriptors.hh"

namespace olb {

template class PorousBGKdynamics<double, descriptors::PorousD2Q9Descriptor>;
template class PorousBGKdynamics<double, descriptors::PorousD3Q19Descriptor>;

template class ExtendedPorousBGKdynamics<double, descriptors::ExtendedPorousD2Q9Descriptor>;
template class PorousBGKdynamics<double, descriptors::ExtendedPorousD3Q19Descriptor>;

}
