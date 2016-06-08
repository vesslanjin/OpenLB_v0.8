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

#ifndef HEURISTIC_LOAD_BALANCER_HH
#define HEURISTIC_LOAD_BALANCER_HH

#include <algorithm>
#include "cell.h"
#include "util.h"
#include <vector>
#include <map>
#include <math.h>
#include "external/boost/boost/shared_array.hpp"
#include "heuristicLoadBalancer.h"

namespace olb {

template<typename T> heuristicLoadBalancer<T>::heuristicLoadBalancer(CuboidGeometry3D<T>& cGeometry, BlockGeometry3D& blockGeometry, const double ratioFullEmpty) {
  reInit(cGeometry, blockGeometry, ratioFullEmpty);
}

template<typename T>
void heuristicLoadBalancer<T>::reInit(CuboidGeometry3D<T>& cGeometry, BlockGeometry3D& blockGeometry, const double ratioFullEmpty) 
{

  _cGeometry = &cGeometry;
  _blockGeometry = &blockGeometry;

  int rank = 0;
  int size = 1;
  int nC = _cGeometry->get_nC();
#ifdef PARALLEL_MODE_MPI
  rank = singleton::mpi().getRank();
  size = singleton::mpi().getSize();
#endif
  std::vector<Cell3D<T> > inCells;
  int xN, yN, zN;
  T globX, globY, globZ;//, delta;

  boost::shared_array<int> tempInCN(new int[nC]);

  std::vector<int> cuboidToThread(nC);
  std::vector<int> partitionResult(nC);
  std::vector<int> vwgt(nC); // node weights
  std::vector<int> taken(nC, 0);
  std::vector<int> currentLoad(size, 0);

  if(size == 1) {
    for(int i = 0; i < nC; ++i) {
      _glob.push_back(i);
      _loc[i] = i;
      _rank[i] = 0;
    };
    locChunkSize = nC;
    return;
  }
  if(rank == 0) {
    for( int iC = 0; iC < nC; iC++) { // assemble neighbourhood information
      xN  = _cGeometry->get_cuboid(iC).get_nX();
      yN  = _cGeometry->get_cuboid(iC).get_nY();
      zN  = _cGeometry->get_cuboid(iC).get_nZ();
      globX = _cGeometry->get_cuboid(iC).get_globPosX();
      globY = _cGeometry->get_cuboid(iC).get_globPosY();
      globZ = _cGeometry->get_cuboid(iC).get_globPosZ();
      //delta = _cGeometry->get_cuboid(iC).get_delta();

      if (_blockGeometry) {
        int fullCells = 0;
        for (int iX=globX; iX<globX + xN; iX++) {
          for (int iY=globY; iY<globY + yN; iY++) {
            for (int iZ=globZ; iZ<globZ + zN; iZ++) {
              if (_blockGeometry->getMaterial(iX, iY, iZ) != 0) {
                fullCells++;
              }
            }
          }
        }
        vwgt[iC] = (xN*yN*zN - fullCells) + (ratioFullEmpty * fullCells);
      } else {
        vwgt[iC] = xN*yN*zN;
      }
    }

    int maxLoad = -1;
    int maxIC = -1;
    do {
      maxLoad = -1;
      maxIC = -1;
      for( int iC = 0 ; iC < nC; iC++) {
        if(taken[iC] == 0 && vwgt[iC] > maxLoad) {
          maxLoad = vwgt[iC];
          maxIC = iC;
        }
      }

      if(maxIC != -1) {
        double minLoad = currentLoad[0];
        int minJ = 0;
        for(int j = 1; j < size; j++) {
          if(currentLoad[j] < minLoad) {
            minLoad = currentLoad[j];
            minJ = j;
          }
        }
        taken[maxIC] = 1;
        currentLoad[minJ] += maxLoad;
        partitionResult[maxIC] = minJ;
      }
    } while(maxLoad != -1);
#if 0
    std::cout << "vwgt" << std::endl;
    for(int i = 0; i < nC; i++)  {
      std::cout << "[" << i << "]="<< vwgt[i] << std::endl;
    }

    for(int i = 0; i < size; i++) {
      std::cout << "load[" << i << "]=" << currentLoad[i] << std::endl;
    }

    std::cout << "vwgt" << std::endl;
    for(int i = 0; i < nC; i++)  {
      std::cout << vwgt[i] << std::endl;
    }
    std::cout << "xadj" << std::endl;
    for(int i = 0; i < nC+1; i++)  {
      std::cout << xadj[i] << std::endl;
    }
    std::cout << "adjncy" << std::endl;
    for(int i = 0; i <adjncy.size(); i++)  {
      std::cout << adjncy[i] << std::endl;
    }
    std::cout << "adjcwgt" << std::endl;
    for(int i = 0; i < adjcwgt.size(); i++)  {
      std::cout << adjcwgt[i] << std::endl;
    }

    std::cout << "nC" << nC << " size " << size << " inbalance " <<
              inbalance << std::endl;
#endif
    int count = 0;
    for(int i = 0; i < nC; ++i) {
      if(partitionResult[i] == 0) {
        _glob.push_back(i);
        _loc[i] = count;
        count++;
      };
      _rank[i] = partitionResult[i];
      cuboidToThread[i] = partitionResult[i];
    }
    locChunkSize = count;
  }
  // Send all threads their number of cuboids

#ifdef PARALLEL_MODE_MPI
  if(rank == 0) {
    // Send all threads their respective cuboids
    _mpiNbHelper.free();
    _mpiNbHelper.allocate(size-1);
    for(int i = 1; i < size; i++) {
      singleton::mpi().iSend(&cuboidToThread.front(),
                             nC, i, &_mpiNbHelper.get_mpiRequest()[i-1], 0);
    }
    singleton::mpi().waitAll(_mpiNbHelper);
  } else {
    int *tmpCuboids = new int[nC];
    singleton::mpi().receive(tmpCuboids, nC, 0, 0);
    int count = 0;
    for(int i = 0; i < nC; ++i) {
      if(tmpCuboids[i] == rank) {
        _glob.push_back(i);
        _loc[i] = count;
        count++;
      };
      _rank[i] = tmpCuboids[i];
    }
    delete[] tmpCuboids;
    locChunkSize = count;
  }
#endif
#ifdef OLD_DEBUG
  debug();
#endif
}


template<typename T> heuristicLoadBalancer<T>::heuristicLoadBalancer(CuboidGeometry3D<T>& cGeometry, SuperGeometry3D& superGeometry, const double ratioFullEmpty) {
  reInit(cGeometry, superGeometry, ratioFullEmpty);
}

template<typename T>
void heuristicLoadBalancer<T>::reInit(CuboidGeometry3D<T>& cGeometry, SuperGeometry3D& superGeometry, const double ratioFullEmpty) 
{

  _cGeometry = &cGeometry;
  _superGeometry = &superGeometry;

  int rank = 0;
  int size = 1;
  int nC = _cGeometry->get_nC();
#ifdef PARALLEL_MODE_MPI
  rank = singleton::mpi().getRank();
  size = singleton::mpi().getSize();
#endif
  std::vector<Cell3D<T> > inCells;
  int xN, yN, zN;
  T globX, globY, globZ;//, delta;

  boost::shared_array<int> tempInCN(new int[nC]);

  std::vector<int> cuboidToThread(nC);
  std::vector<int> partitionResult(nC);
  std::vector<int> vwgt(nC); // node weights
  std::vector<int> taken(nC, 0);
  std::vector<int> currentLoad(size, 0);

  if(size == 1) {
    for(int i = 0; i < nC; ++i) {
      _glob.push_back(i);
      _loc[i] = i;
      _rank[i] = 0;
    };
    locChunkSize = nC;
    return;
  }
  if(rank == 0) {
    for( int iC = 0; iC < nC; iC++) { // assemble neighbourhood information
      xN  = _cGeometry->get_cuboid(iC).get_nX();
      yN  = _cGeometry->get_cuboid(iC).get_nY();
      zN  = _cGeometry->get_cuboid(iC).get_nZ();
      globX = _cGeometry->get_cuboid(iC).get_globPosX();
      globY = _cGeometry->get_cuboid(iC).get_globPosY();
      globZ = _cGeometry->get_cuboid(iC).get_globPosZ();
      //delta = _cGeometry->get_cuboid(iC).get_delta();

      if (_superGeometry) {
        int fullCells = 0;
        for (int iX=globX; iX<globX + xN; iX++) {
          for (int iY=globY; iY<globY + yN; iY++) {
            for (int iZ=globZ; iZ<globZ + zN; iZ++) {
              if (_superGeometry->getMaterial(iX, iY, iZ) != 0) {
                fullCells++;
              }
            }
          }
        }
        vwgt[iC] = (xN*yN*zN - fullCells) + (ratioFullEmpty * fullCells);
      } else {
        vwgt[iC] = xN*yN*zN;
      }
    }

    int maxLoad = -1;
    int maxIC = -1;
    do {
      maxLoad = -1;
      maxIC = -1;
      for( int iC = 0 ; iC < nC; iC++) {
        if(taken[iC] == 0 && vwgt[iC] > maxLoad) {
          maxLoad = vwgt[iC];
          maxIC = iC;
        }
      }

      if(maxIC != -1) {
        double minLoad = currentLoad[0];
        int minJ = 0;
        for(int j = 1; j < size; j++) {
          if(currentLoad[j] < minLoad) {
            minLoad = currentLoad[j];
            minJ = j;
          }
        }
        taken[maxIC] = 1;
        currentLoad[minJ] += maxLoad;
        partitionResult[maxIC] = minJ;
      }
    } while(maxLoad != -1);
#if 0
    std::cout << "vwgt" << std::endl;
    for(int i = 0; i < nC; i++)  {
      std::cout << "[" << i << "]="<< vwgt[i] << std::endl;
    }

    for(int i = 0; i < size; i++) {
      std::cout << "load[" << i << "]=" << currentLoad[i] << std::endl;
    }

    std::cout << "vwgt" << std::endl;
    for(int i = 0; i < nC; i++)  {
      std::cout << vwgt[i] << std::endl;
    }
    std::cout << "xadj" << std::endl;
    for(int i = 0; i < nC+1; i++)  {
      std::cout << xadj[i] << std::endl;
    }
    std::cout << "adjncy" << std::endl;
    for(int i = 0; i <adjncy.size(); i++)  {
      std::cout << adjncy[i] << std::endl;
    }
    std::cout << "adjcwgt" << std::endl;
    for(int i = 0; i < adjcwgt.size(); i++)  {
      std::cout << adjcwgt[i] << std::endl;
    }

    std::cout << "nC" << nC << " size " << size << " inbalance " <<
              inbalance << std::endl;
#endif
    int count = 0;
    for(int i = 0; i < nC; ++i) {
      if(partitionResult[i] == 0) {
        _glob.push_back(i);
        _loc[i] = count;
        count++;
      };
      _rank[i] = partitionResult[i];
      cuboidToThread[i] = partitionResult[i];
    }
    locChunkSize = count;
  }
  // Send all threads their number of cuboids

#ifdef PARALLEL_MODE_MPI
  if(rank == 0) {
    // Send all threads their respective cuboids
    _mpiNbHelper.free();
    _mpiNbHelper.allocate(size-1);
    for(int i = 1; i < size; i++) {
      singleton::mpi().iSend(&cuboidToThread.front(),
                             nC, i, &_mpiNbHelper.get_mpiRequest()[i-1], 0);
    }
    singleton::mpi().waitAll(_mpiNbHelper);
  } else {
    int *tmpCuboids = new int[nC];
    singleton::mpi().receive(tmpCuboids, nC, 0, 0);
    int count = 0;
    for(int i = 0; i < nC; ++i) {
      if(tmpCuboids[i] == rank) {
        _glob.push_back(i);
        _loc[i] = count;
        count++;
      };
      _rank[i] = tmpCuboids[i];
    }
    delete[] tmpCuboids;
    locChunkSize = count;
  }
#endif
#ifdef OLD_DEBUG
  debug();
#endif
}
}  // namespace olb
#endif
