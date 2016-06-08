/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007, 2008 Bernd Stahl and Jonas Latt
 *  Address: Battelle Batiment A, Route de Drize 7, 1227 Carouge, Switzerland
 *  E-mail: bernd.stahl@cui.unige.ch
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
 * Scalar, vector and tensor fields for 2D data analysis -- template instantiation.
 */

#include "multiDataFields3D.h"
#include "multiDataFields3D.hh"
#include "core/latticeDescriptors.h"
#include "core/latticeDescriptors.hh"

namespace olb {

using namespace descriptors;

template class MultiScalarField3D<double>;
template class ParallelScalarFieldSerializerPolicy3D<double>;
template class ParallelScalarFieldUnSerializerPolicy3D<double>;

template class MultiTensorField3D<double, 3>; // for vectors
template class ParallelTensorFieldSerializerPolicy3D<double, 3>;
template class ParallelTensorFieldUnSerializerPolicy3D<double, 3>;
template class MultiTensorField3D<double, 6>; // for symmetric tensors
template class ParallelTensorFieldSerializerPolicy3D<double, 6>;
template class ParallelTensorFieldUnSerializerPolicy3D<double, 6>;
template class MultiTensorField3D<double, 9>; // for non-symmetric tensors
template class ParallelTensorFieldSerializerPolicy3D<double, 9>;
template class ParallelTensorFieldUnSerializerPolicy3D<double, 9>;
template class MultiTensorField3D<double,19>; // for full populations
template class ParallelTensorFieldSerializerPolicy3D<double, 19>;
template class ParallelTensorFieldUnSerializerPolicy3D<double, 19>;

}  // namespace olb
