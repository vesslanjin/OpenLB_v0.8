/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2008 Orestis Malaspinas, Andrea Parmigiani
 *  Address: EPFL-STI-LIN Station 9, 1015 Lausanne
 *  E-mail: orestis.malaspinas@epfl.ch
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
 *  -- generic code
 */
#ifndef ADVECTION_DIFFUSION_LATTICE_DESCRIPTORS_HH
#define ADVECTION_DIFFUSION_LATTICE_DESCRIPTORS_HH

#include "advectionDiffusionLatticeDescriptors.h"

namespace olb {
namespace descriptors {

// AdvectionDiffusion D2Q5 //////////////////////////////////////////////

template<typename T>
const int D2Q5DescriptorBase<T>::c
[D2Q5DescriptorBase<T>::q][D2Q5DescriptorBase<T>::d] =
{
  { 0, 0},
  {-1, 0}, {0, -1}, {1,0}, { 0,1}
};

template<typename T>
const int D2Q5DescriptorBase<T>::vicinity = 1;

template<typename T>
const T D2Q5DescriptorBase<T>::invCs2 = (T)3;

template<typename T>
const T D2Q5DescriptorBase<T>::t[D2Q5DescriptorBase<T>::q] =
{
  (T)1-(T)2/invCs2,
  (T)1/(invCs2*(T)2), (T)1/(invCs2*(T)2),
  (T)1/(invCs2*(T)2), (T)1/(invCs2*(T)2)
};

// AdvectionDiffusion D3Q7 ////////////////////////////////////////////////////

template<typename T>
const int D3Q7DescriptorBase<T>::c
[D3Q7DescriptorBase<T>::q][D3Q7DescriptorBase<T>::d] =
{
  { 0, 0, 0},

  {-1, 0, 0}, {0,-1, 0},
  { 0, 0,-1}, {1, 0, 0},
  { 0, 1, 0}, {0, 0, 1},
};

template<typename T>
const int D3Q7DescriptorBase<T>::vicinity = 1;

template<typename T>
const T D3Q7DescriptorBase<T>::invCs2 = (T)4;

template<typename T>
const T D3Q7DescriptorBase<T>::t[D3Q7DescriptorBase<T>::q] =
{
  (T)1-(T)3 / invCs2,

  (T)1/(invCs2*(T)2), (T)1/(invCs2*(T)2), (T)1/(invCs2*(T)2),
  (T)1/(invCs2*(T)2), (T)1/(invCs2*(T)2), (T)1/(invCs2*(T)2)
};

}  // namespace descriptors

}  // namespace olb

#endif
