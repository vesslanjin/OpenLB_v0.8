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

#include "simulationSetup2D.h"
#include "simulationSetup2D.hh"

namespace olb {

template void iniFirstOrder2D<double, descriptors::D2Q9Descriptor> (
  BlockLatticeView2D<double, descriptors::D2Q9Descriptor> lattice);

template void convergeFixedVelocity<double, descriptors::D2Q9Descriptor> (
  BlockLattice2D<double, descriptors::D2Q9Descriptor>& lattice,
  double epsilon, int step);

template void computePressure2D<double, descriptors::D2Q9Descriptor>
( ScalarFieldBase2D<double> const& poissonTerm,
  ScalarFieldBase2D<double>& pressure,
  double epsilon, double lambda );

template void iniPressure2D (
  BlockLatticeView2D<double, descriptors::D2Q9Descriptor> lattice,
  double epsilon, double lambda );

} // namespace olb
