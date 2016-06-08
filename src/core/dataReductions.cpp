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
 * Classes and free functions to perform reduction operations on data fields -- template instantiation.
 */

#include "dataReductions.h"
#include "dataReductions.hh"
#include "dataFields2D.h"
#include "dataFields2D.hh"
#include "dataFields3D.h"
#include "dataFields3D.hh"
#include "complexGrids/multiBlockStructure/multiDataFields2D.h"
#include "complexGrids/multiBlockStructure/multiDataFields2D.hh"
#include "complexGrids/multiBlockStructure/multiDataFields3D.h"
#include "complexGrids/multiBlockStructure/multiDataFields3D.hh"

namespace olb {

template class MinReduction<double>;
template class MaxReduction<double>;
template class AverageReduction<double>;
template class NormSqrReduction<double>;

template double computeMin<double, ScalarField2D>(ScalarField2D<double> const& field);
template double computeMax<double, ScalarField2D>(ScalarField2D<double> const& field);
template double computeAverage<double, ScalarField2D>(ScalarField2D<double> const& field);
template double computeNormSqr<double, ScalarField2D>(ScalarField2D<double> const& field);
template double computeRMS<double, ScalarField2D>(ScalarField2D<double> const& field);

template double computeMin<double, ScalarField3D>(ScalarField3D<double> const& field);
template double computeMax<double, ScalarField3D>(ScalarField3D<double> const& field);
template double computeAverage<double, ScalarField3D>(ScalarField3D<double> const& field);
template double computeNormSqr<double, ScalarField3D>(ScalarField3D<double> const& field);
template double computeRMS<double, ScalarField3D>(ScalarField3D<double> const& field);

template double computeMin<double,MultiScalarField2D> (
  MultiScalarField2D<double> const& field );
template double computeMax<double,MultiScalarField2D> (
  MultiScalarField2D<double> const& field );
template double computeAverage<double,MultiScalarField2D> (
  MultiScalarField2D<double> const& field );
template double computeNormSqr<double,MultiScalarField2D> (
  MultiScalarField2D<double> const& field );
template double computeRMS<double,MultiScalarField2D> (
  MultiScalarField2D<double> const& field );

template double computeMin<double,MultiScalarField3D> (
  MultiScalarField3D<double> const& field );
template double computeMax<double,MultiScalarField3D> (
  MultiScalarField3D<double> const& field );
template double computeAverage<double,MultiScalarField3D> (
  MultiScalarField3D<double> const& field );
template double computeNormSqr<double,MultiScalarField3D> (
  MultiScalarField3D<double> const& field );
template double computeRMS<double,MultiScalarField3D> (
  MultiScalarField3D<double> const& field );

}  // namespace olb
