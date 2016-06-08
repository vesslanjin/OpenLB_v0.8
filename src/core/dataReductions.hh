/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Bernd Stahl and Jonas Latt
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
 * Classes and free functions to perform reduction operations on data fields -- generic implementation.
 */

#ifndef DATA_REDUCTIONS_HH
#define DATA_REDUCTIONS_HH

#include "complexGrids/mpiManager/mpiManager.h"
#include <cmath>
#include <limits>
#include "dataReductions.h"

namespace olb {

//////// Class MinReduction //////////////////////////////////

template<typename T>
const T MinReduction<T>::neutralElement = std::numeric_limits<T>::max();

template<typename T>
void MinReduction<T>::takeElement(T const& element) {
  if (element < minimum) {
    minimum = element;
  }
}

template<typename T>
void MinReduction<T>::reduceParallel() {
#ifdef PARALLEL_MODE_MPI
  singleton::mpi().reduceAndBcast(minimum, MPI_MIN);
#endif
}

//////// Class MaxReduction //////////////////////////////////

template<typename T>
const T MaxReduction<T>::neutralElement = std::numeric_limits<T>::min();

template<typename T>
void MaxReduction<T>::takeElement(T const& element) {
  if (element > maximum) {
    maximum = element;
  }
}

template<typename T>
void MaxReduction<T>::reduceParallel() {
#ifdef PARALLEL_MODE_MPI
  singleton::mpi().reduceAndBcast(maximum, MPI_MAX);
#endif
}

//////// Class AverageReduction //////////////////////////////////

template<typename T>
const T AverageReduction<T>::neutralElement = T();

template<typename T>
void AverageReduction<T>::takeElement(T const& element) {
  average += element;
  weight++;
}

template<typename T>
void AverageReduction<T>::reduceParallel() {
#ifdef PARALLEL_MODE_MPI
  singleton::mpi().reduceAndBcast(average, MPI_SUM);
  singleton::mpi().reduceAndBcast(weight, MPI_SUM);
#endif
}

template<typename T>
T AverageReduction<T>::getResult() const {
  if (weight<1e-12) return T();
  return average / weight;
}

//////// Class NormSqrReduction //////////////////////////////////

template<typename T>
const T NormSqrReduction<T>::neutralElement = T();

template<typename T>
void NormSqrReduction<T>::takeElement(T const& element) {
  normSqr += element*element;
  weight++;
}

template<typename T>
void NormSqrReduction<T>::reduceParallel() {
#ifdef PARALLEL_MODE_MPI
  singleton::mpi().reduceAndBcast(normSqr, MPI_SUM);
  singleton::mpi().reduceAndBcast(weight, MPI_SUM);
#endif
}

template<typename T>
T NormSqrReduction<T>::getResult() const {
  if (weight<1e-12) return T();
  return normSqr / weight;
}

//////// Free reduction functions //////////////////////////////////

template<typename T, template<typename U> class ScalarField>
T computeMin(ScalarField<T> const& field) {
  MinReduction<T> minReduction;
  return field.computeReduction(minReduction);
}

template<typename T, template<typename U> class ScalarField>
T computeMax(ScalarField<T> const& field) {
  MaxReduction<T> maxReduction;
  return field.computeReduction(maxReduction);
}

template<typename T, template<typename U> class ScalarField>
T computeAverage(ScalarField<T> const& field) {
  AverageReduction<T> averageReduction;
  return field.computeReduction(averageReduction);
}

template<typename T, template<typename U> class ScalarField>
T computeNormSqr(ScalarField<T> const& field) {
  NormSqrReduction<T> normSqrReduction;
  return field.computeReduction(normSqrReduction);
}

template<typename T, template<typename U> class ScalarField>
T computeRMS(ScalarField<T> const& field) {
  return sqrt(computeNormSqr(field));
}

} // namespace olb

#endif
