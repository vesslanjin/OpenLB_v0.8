/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Jonas Fietz, Mathias J. Krause
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


#ifndef HEURISTIC_LOAD_BALANCER_H
#define HEURISTIC_LOAD_BALANCER_H

#include "complexGrids/mpiManager/mpiManager.h"
#include "complexGrids/cuboidStructure/cuboidGeometry3D.h"
#include "complexGrids/cuboidStructure/cuboidNeighbourhood3D.h"
#include "loadBalancer.h"
#include "io/ostreamManager.h"




namespace olb {


template<typename T>
class heuristicLoadBalancer : public loadBalancer {
private:
  // Handles the MPI communication
#ifdef PARALLEL_MODE_MPI
  singleton::MpiNonBlockingHelper _mpiNbHelper;
#endif
  CuboidGeometry3D<T>* _cGeometry;
  BlockGeometry3D* _blockGeometry;
  SuperGeometry3D* _superGeometry;

public:
  /*
   * Constructs a load balancer from a given cuboid geometry
   * using a heurist
   * \param cGeometry: The cuboid geometry to base the load balance on
   * \param blockGeometry: Used to determine number of full and empty cells
   *             if given
   * \param ratioFullEmpty: Time it takes for full cells in relation to
   *              empty cells
   */
  heuristicLoadBalancer() {};

  heuristicLoadBalancer(CuboidGeometry3D<T>& cGeometry, BlockGeometry3D& blockGeometry, const double ratioFullEmpty=3.7);

  void reInit(CuboidGeometry3D<T>& cGeometry, BlockGeometry3D& blockGeometry, const double ratioFullEmpty=3.7);

  heuristicLoadBalancer(CuboidGeometry3D<T>& cGeometry, SuperGeometry3D& superGeometry, const double ratioFullEmpty=3.7);

  void reInit(CuboidGeometry3D<T>& cGeometry, SuperGeometry3D& superGeometry, const double ratioFullEmpty=3.7);

};
}  // namespace olb

#endif
