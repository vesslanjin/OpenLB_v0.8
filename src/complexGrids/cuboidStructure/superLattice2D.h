/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Mathias J. Krause
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
 * The description of a 2D super lattice -- header file.
 */


#ifndef SUPER_LATTICE_2D_H
#define SUPER_LATTICE_2D_H

#include <vector>

#include "core/blockLattice2D.h"
#include "core/blockLatticeView2D.h"
#include "communicator2D.h"
#include "cuboidGeometry2D.h"
#include "core/loadBalancer.h"
#include "core/postProcessing.h"


/// All OpenLB code is contained in this namespace.
namespace olb {

/// A super lattice combines a number of block lattices that are ordered
/// in a cuboid geometry.
/** The communication between the block lattices is done by two
 * communicators. One (_commStream) is responible to provide the data for
 * the streaming the other (_commBC) for the non-local boundary conditions.
 * To simplify the code structure ghost cells in an overlap of size
 * (_overlap) is indrocuced. It depends on the non-locality of the
 * boundary conditions but is at least one because of the streaming
 *
 * The algorithm is parallelized with mpi. The load balancer (_load)
 * distributes the block lattices to processes.
 *
 * WARNING: For unstructured grids there is an iterpolation needed
 * for the method buffer_outData in coboidNeighbourhood which is not
 * yet implemented! Moreover this class needs to be chanced
 * that the number of times steps for the collision and streaming is
 * is dependent of the refinement level.
 *
 * This class is not intended to be derived from.
 */


template<typename T, template<typename U> class Lattice> class Communicator2D;


template<typename T, template<typename U> class Lattice>
class SuperLattice2D {

private:
  /// Lattices with ghost cell layer of size overlap
  std::vector<BlockLattice2D<T,Lattice> >     _blockLattices;
  /// View of the lattices without overlap
  std::vector<BlockLatticeView2D<T,Lattice> > _lattices;
  /// The grid structure is stored here
  CuboidGeometry2D<T>&                        _cGeometry;
  /// Size of ghost cell layer (must be greater than 1 and
  /// greater_overlapBC, default =1)
  int                                         _overlap;
  // Size of the refinement overlap
  int                                         _overlapRefinement;
  /// This communicator handels the communication for the streaming
  Communicator2D<T,Lattice>                   _commStream;
  /// This communicator handels the communication for the postprocessors
  Communicator2D<T,Lattice>                   _commBC;
  /// Specifies if there is communication for non local boundary conditions
  /// needed. It is automatically swichted on if overlapBC >= 1 by the
  /// calling the constructer. (default =false)
  bool                                        _commBC_on;
  /// Distribution of the coboids of the cuboid structure
  loadBalancer                                _load;
  /// Statistic of the super structure
  LatticeStatistics<T>                        *_statistics;
  /// Specifies if there is statistic calculated. It is always
  /// needed for the ConstRhoBGK dynamics. (default =true)
  bool                                        _statistics_on;
public:
  /// Construction of a super structure
  SuperLattice2D(CuboidGeometry2D<T>& cGeometry, int overlapBC = 0, int overlapRefinement = 0);

  /// Read and write access to a block lattice
  BlockLattice2D<T,Lattice>& get_blockLattice(int locIC)
  { return _blockLattices[locIC]; };
  /// Read only access to a block lattice
  BlockLattice2D<T,Lattice> const& get_blockLattice(int locIC) const
  { return _blockLattices[locIC]; };
  /// Read and write access to a lattice (block lattice view, one
  /// without overlap).
  BlockLatticeView2D<T,Lattice>& get_lattice(int locIC)
  { return _lattices[locIC]; };
  /// Read only access to a lattice
  BlockLatticeView2D<T,Lattice> const& get_lattice(int locIC) const
  { return _lattices[locIC]; };
  /// Read and write access to a block lattice
  CuboidGeometry2D<T>& get_cGeometry()
  { return _cGeometry; };
  /// Read only access to a block lattice
  CuboidGeometry2D<T> const& get_cGeometry() const
  { return _cGeometry; };
  /// Read only access to the overlap
  int get_overlap() const
  { return _overlap;};
  /// Read and write access to the streaming communicator
  Communicator2D<T,Lattice>& get_commStream()
  { return _commStream; };
  /// Read only access to the streaming communicator
  Communicator2D<T,Lattice> const& get_commStream() const
  { return _commStream; };
  /// Read and write access to the boundary communicator
  Communicator2D<T,Lattice>& get_commBC()
  { return _commBC; };
  /// Read only access to the boundary communicator
  Communicator2D<T,Lattice> const& get_commBC() const
  { return _commBC; };
  /// Read and write access to the load balancer
  loadBalancer& get_load()
  { return _load; };
  /// Read only access to the load balancer
  loadBalancer const& get_load() const
  { return _load; };
  /// Return a handle to the LatticeStatistics object
  LatticeStatistics<T>& getStatistics();
  /// Return a constant handle to the LatticeStatistics object
  LatticeStatistics<T> const& getStatistics() const;

  /// Write access to lattice cells that returns false if
  /// iX/iY is not in any of the cuboids
  bool set(T iX, T iY, Cell<T,Lattice> const& cell);
  /// Read only access to lattice cells that returns false if
  /// iX/iY is not in any of the cuboids
  bool get(T iX, T iY, Cell<T,Lattice>& cell) const;
  /// Read only access to lattice cells over the cuboid number 
  /// and local coordinates   WARNING!!! NO ERROR HANDLING IMPLEMENTED!!!
  Cell<T,Lattice> get(int iC, T locX, T locY) const;
  /// Initialize all lattice cells to become ready for simulation
  void initialize();
  /// Defines the dynamics on a rectangular domain

  void defineDynamics (T x0, T x1, T y0, T y1,
                       Dynamics<T,Lattice>* dynamics );

  /// Defines the dynamics on a rectangular domain by material
  void defineDynamics(BlockGeometryStatistics2D* blockGeoSta, T x0, T x1,
                      T y0, T y1, Dynamics<T, Lattice>* dynamics,
                      int material);

  /// Defines the dynamics by material
  void defineDynamics(BlockGeometryStatistics2D* blockGeoSta, Dynamics<T,
                      Lattice>* dynamics, int material);

  /// Defines rho on a rectangular domain
  void defineRhoU (T x0, T x1, T y0, T y1,
                   T rho, const T u[Lattice<T>::d] );
  /// Defines rho on a rectangular domain
  void defineRho (T x0, T x1, T y0, T y1,
                  T rho );
  /// Defines u on a rectangular domain
  void defineU (T x0, T x1, T y0, T y1,
                const T u[Lattice<T>::d] );
  /// Defines an external field on a rectangular domain
  void defineExternalField (T x0, T x1, T y0, T y1,
                            int fieldBeginsAt, int sizeOfField, T* field );
  /// Initializes the equilibrium
  void iniEquilibrium (T x0, T x1, T y0, T y1,
                       T rho, const T u[Lattice<T>::d] );

  /// Apply collision step to a rectangular domain
  void collide(T x0, T x1, T y0, T y1);
  /// Apply collision step to the whole domain
  void collide();
  /// TO BE DONE: Apply collision step to a rectangular domain,
  /// with fixed velocity
  // void staticCollide(T x0, T x1, T y0, T y1,
  //                  TensorField2D<T,2> const& u);
  /// TO BE DONE: Apply collision step to the whole domain,
  /// with fixed velocity
  // void staticCollide(TensorField2D<T,2> const& u);
  /// Apply streaming step to a rectangular domain
  void stream(T x0, T x1, T y0, T y1);
  /// Apply streaming step to the whole domain
  void stream();
  /// TO BE DONE: Apply first collision, then streaming step
  /// to a rectangular domain
  // void collideAndStream(T x0, T x1, T y0, T y1);
  /// Apply first collision, then streaming step
  /// to the whole domain
  void collideAndStream();
  /// Subtract a constant offset from the density within the whole domain
  void stripeOffDensityOffset (int x0_, int x1_, int y0_, int y1_,
                               T offset );
  /// Subtract a constant offset from the density within a rect. domain
  void stripeOffDensityOffset(T offset);
  /// Switches Statistics on (default on)
  void statisticsOn() {_statistics_on = true;};
  /// Switches Statistics off (default on). That speeds up
  /// the execution time.
  void statisticsOff() {_statistics_on = false;};
  /// TO BE DONE: Development of a general IO concept!
  /// Save Data to files fName
  void save(std::string fName, bool enforceUint = false);
  /// Load Data from files fName
  void load(std::string fName, bool enforceUint = false);

private:
  /// Resets and reduce the statistics
  void reset_statistics();
};

} // namespace olb

#endif
