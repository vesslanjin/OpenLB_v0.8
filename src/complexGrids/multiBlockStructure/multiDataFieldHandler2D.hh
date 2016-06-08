/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007, 2008 Jonas Latt and Bernd Stahl
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
 * Handler for 2D multi data field structure -- generic implementation.
 */

#ifndef MULTI_DATA_FIELD_HANDLER_2D_HH
#define MULTI_DATA_FIELD_HANDLER_2D_HH

#include "complexGrids/mpiManager/mpiManager.h"
#include "multiDataFieldHandler2D.h"
#include "complexGrids/multiBlockStructure/parallelDynamics.h"
#include "core/util.h"
#include <algorithm>
#include <numeric>


namespace olb {

////////////////////// Class SerialMultiDataFieldHandler2D /////////////////////

template<typename T>
SerialMultiDataFieldHandler2D<T>::SerialMultiDataFieldHandler2D (
  MultiDataDistribution2D const& dataDistribution_ )
  : dataDistribution(dataDistribution_)
{ }

template<typename T>
int SerialMultiDataFieldHandler2D<T>::getNx() const {
  return dataDistribution.getNx();
}
template<typename T>
int SerialMultiDataFieldHandler2D<T>::getNy() const {
  return dataDistribution.getNy();
}

template<typename T>
MultiDataDistribution2D const& SerialMultiDataFieldHandler2D<T>::getMultiDataDistribution() const {
  return dataDistribution;
}

template<typename T>
bool SerialMultiDataFieldHandler2D<T>::getLocalEnvelope(int iBlock, int& lx, int& ly) const {
  BlockParameters2D const& parameters = dataDistribution.getBlockParameters(iBlock);
  lx = parameters.getEnvelopeLx();
  ly = parameters.getEnvelopeLy();
  return true;
}

template<typename T>
T SerialMultiDataFieldHandler2D<T>::reduceSum (T localSum) const {
  return localSum;
}

template<typename T>
T SerialMultiDataFieldHandler2D<T>::reduceAverage (T localAverage, T localWeight) const {
  return localAverage;
}

template<typename T>
T SerialMultiDataFieldHandler2D<T>::reduceMin (T localMin) const {
  return localMin;
}

template<typename T>
T SerialMultiDataFieldHandler2D<T>::reduceMax (T localMax) const {
  return localMax;
}

template<typename T>
void SerialMultiDataFieldHandler2D<T>::broadCastScalar(T& scalar, int fromBlock) const {
  // Nothing to do in the serial case
}

template<typename T>
void SerialMultiDataFieldHandler2D<T>::broadCastVector(T* vect, int size, int fromBlock) const {
  // Nothing to do in the serial case
}


#ifdef PARALLEL_MODE_MPI

////////////////////// Class ParallelMultiDataFieldHandler2D /////////////////////

template<typename T>
ParallelMultiDataFieldHandler2D<T>::ParallelMultiDataFieldHandler2D (
  MultiDataDistribution2D const& dataDistribution_ )
  : dataDistribution(dataDistribution_)
{ }

template<typename T>
int ParallelMultiDataFieldHandler2D<T>::getNx() const {
  return dataDistribution.getNx();
}
template<typename T>
int ParallelMultiDataFieldHandler2D<T>::getNy() const {
  return dataDistribution.getNy();
}

template<typename T>
MultiDataDistribution2D const& ParallelMultiDataFieldHandler2D<T>::getMultiDataDistribution() const {
  return dataDistribution;
}

template<typename T>
bool ParallelMultiDataFieldHandler2D<T>::getLocalEnvelope(int iBlock, int& lx, int& ly) const {
  BlockParameters2D const& parameters = dataDistribution.getBlockParameters(iBlock);
  if ( parameters.getProcId() == singleton::mpi().getRank() ) {
    lx = parameters.getEnvelopeLx();
    ly = parameters.getEnvelopeLy();
    return true;
  }
  else {
    lx = ly = 0;
    return false;
  }
}

template<typename T>
T ParallelMultiDataFieldHandler2D<T>::reduceSum(T localSum) const {
  T globalSum;
  singleton::mpi().reduce(localSum, globalSum, MPI_SUM);
  singleton::mpi().bCast(&globalSum, 1);
  return globalSum;
}

template<typename T>
T ParallelMultiDataFieldHandler2D<T>::reduceAverage(T localAverage, T localWeight) const {
  T sumAverage, sumWeights;
  singleton::mpi().reduce(localAverage*localWeight, sumAverage, MPI_SUM);
  singleton::mpi().reduce(localWeight, sumWeights, MPI_SUM);
  if (singleton::mpi().isMainProcessor() && sumWeights>1.e-12) {
    sumAverage /= sumWeights;
  }
  singleton::mpi().bCast(&sumAverage, 1);
  return sumAverage;
}

template<typename T>
T ParallelMultiDataFieldHandler2D<T>::reduceMin(T localMin) const {
  T globalMin;
  singleton::mpi().reduce(localMin, globalMin, MPI_MIN);
  singleton::mpi().bCast(&globalMin, 1);
  return globalMin;
}

template<typename T>
T ParallelMultiDataFieldHandler2D<T>::reduceMax(T localMax) const {
  T globalMax;
  singleton::mpi().reduce(localMax, globalMax, MPI_MAX);
  singleton::mpi().bCast(&globalMax, 1);
  return globalMax;
}

template<typename T>
void ParallelMultiDataFieldHandler2D<T>::broadCastScalar(T& scalar, int fromBlock) const {
  int fromProc = dataDistribution.getBlockParameters(fromBlock).getProcId();
  singleton::mpi().bCast(&scalar, 1, fromProc);
}

template<typename T>
void ParallelMultiDataFieldHandler2D<T>::broadCastVector(T* vect, int size, int fromBlock) const {
  int fromProc = dataDistribution.getBlockParameters(fromBlock).getProcId();
  singleton::mpi().bCast(vect, size, fromProc);
}

#endif  // PARALLEL_MODE_MPI

}  // namespace olb

#endif
