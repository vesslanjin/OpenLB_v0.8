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
 * Helper functions for the implementation of LB dynamics. This file is all
 * about efficiency. The generic template code is specialized for commonly
 * used Lattices, so that a maximum performance can be taken out of each
 * case.
 */
#ifndef ADVECTION_DIFFUSION_LB_HELPERS_H
#define ADVECTION_DIFFUSION_LB_HELPERS_H

#include "advectionDiffusionLatticeDescriptors.h"
#include "core/lbHelpers.h"
#include "core/util.h"


namespace olb {

template<typename T, class Descriptor> struct adLbDynamicsHelpers;

/// All helper functions are inside this structure
template<typename T, template<typename U> class Lattice>
struct advectionDiffusionLbHelpers {

  static T equilibrium(int iPop, T rho, const T u[Lattice<T>::d]) {
    return adLbDynamicsHelpers<T,typename Lattice<T>::BaseDescriptor>
           ::equilibrium(iPop, rho, u);
  }

  static T rlbCollision(Cell<T,Lattice>& cell, T rho, const T u[Lattice<T>::d], T omega)
  {
    return adLbDynamicsHelpers<T,typename Lattice<T>::BaseDescriptor>
           ::rlbCollision(&cell[0], rho, u, omega);
  }

  static T bgkCollision(Cell<T,Lattice>& cell, T rho, const T u[Lattice<T>::d], T omega)
  {
    return adLbDynamicsHelpers<T,typename Lattice<T>::BaseDescriptor>
           ::bgkCollision(&cell[0], rho, u, omega);
  }
};

/// All helper functions are inside this structure
template<typename T, class Descriptor>
struct adLbDynamicsHelpers {
  /// equilibrium distribution
  static T equilibrium( int iPop, T rho, const T u[Descriptor::d])
  {
    T c_u = T();
    for (int iD=0; iD < Descriptor::d; ++iD)
    {
      c_u += (T)Descriptor::c[iPop][iD] * u[iD];
    }
    return rho*Descriptor::t[iPop]*((T)1 + c_u*Descriptor::invCs2)-Descriptor::t[iPop];
  }

  /// RLB advection diffusion collision step
  static T rlbCollision( T* cell,
                         T rho, const T u[Descriptor::d],
                         T omega)
  {
    const T uSqr = util::normSqr<T,Descriptor::d>(u);
    // First-order moment for the regularization
    T j1[Descriptor::d];
    for (int iD=0; iD<Descriptor::d; ++iD)
    {
      j1[iD] = T();
    }

    T fEq[Descriptor::q];
    for (int iPop=0; iPop<Descriptor::q; ++iPop)
    {
      fEq[iPop] = adLbDynamicsHelpers<T,Descriptor>::equilibrium(iPop, rho, u);
      for (int iD=0; iD<Descriptor::d; ++iD) {
        j1[iD] += Descriptor::c[iPop][iD]*(cell[iPop]-fEq[iPop]);
      }
    }

    // Collision step
    for (int iPop=0; iPop<Descriptor::q; ++iPop)
    {
      T fNeq = T();
      for (int iD=0; iD<Descriptor::d; ++iD)
      {
        fNeq += Descriptor::c[iPop][iD]*j1[iD];
      }
      fNeq *= Descriptor::t[iPop] * Descriptor::invCs2;
      cell[iPop] = fEq[iPop] + ((T)1-omega)*fNeq;
    }
    return uSqr;
  }

  /// BGK advection diffusion collision step
  static T bgkCollision( T* cell,
                         T rho, const T u[Descriptor::d],
                         T omega)
  {
    const T uSqr = util::normSqr<T,Descriptor::d>(u);
    for (int iPop=0; iPop < Descriptor::q; ++iPop)
    {
      cell[iPop] *= (T)1-omega;
      cell[iPop] += omega * adLbDynamicsHelpers<T,Descriptor>::equilibrium (
                      iPop, rho, u); // uses linear equilibrium
    }
    return uSqr;
  }

};

} // namespace olb

#include "advectionDiffusionLbHelpers2D.h"
#include "advectionDiffusionLbHelpers3D.h"

#endif
