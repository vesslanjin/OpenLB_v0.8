/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2008 Andrea Parmigiani, Orestis Malaspinas,
 *  Jonas Latt
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
 * Descriptor for all types of 2D and 3D lattices. In principle, thanks
 * to the fact that the OpenLB code is generic, it is sufficient to
 * write a new descriptor when a new type of lattice is to be used.
 *  -- header file
 */
#ifndef FORCED_SHAN_CHEN_LATTICE_DESCRIPTORS_H
#define FORCED_SHAN_CHEN_LATTICE_DESCRIPTORS_H

#include <vector>

namespace olb {

namespace descriptors {

struct ForcedShanChenExternal2Ddescriptor {
  static const int numScalars = 4;
  static const int numSpecies = 2;
  static const int velocityBeginsAt = 0;
  static const int sizeOfVelocity   = 2;
  static const int forceBeginsAt    = 2;
  static const int sizeOfForce      = 2;
};

/// D2Q9 lattice
template <typename T>
struct ForcedShanChenD2Q9Descriptor
{
  typedef ForcedShanChenD2Q9Descriptor<T> BaseDescriptor;
  typedef ForcedShanChenExternal2Ddescriptor ExternalField;
  enum { d = 2, q = 9 };      ///< number of dimensions/distr. functions
  static const int c[q][d];   ///< lattice directions
  static const T t[q];        ///< lattice weights
  static const T invCs2;      ///< inverse square of speed of sound
  static const int vicinity=1;
};

struct ForcedShanChenExternal3Ddescriptor {
  static const int numScalars = 6;
  static const int numSpecies = 2;
  static const int velocityBeginsAt = 0;
  static const int sizeOfVelocity   = 3;
  static const int forceBeginsAt    = 3;
  static const int sizeOfForce      = 3;
};

/// D3Q19 lattice
template <typename T> struct ForcedShanChenD3Q19Descriptor {
  typedef ForcedShanChenD3Q19Descriptor<T> BaseDescriptor;
  typedef ForcedShanChenExternal3Ddescriptor ExternalField;
  enum { d = 3, q = 19 };     ///< number of dimensions/distr. functions
  static const int c[q][d];   ///< lattice directions
  static const T t[q];        ///< lattice weights
  static const T invCs2;      ///< inverse square of speed of sound
  static const int vicinity=1;
};

}  // namespace descriptors

}  // namespace olb

#endif
