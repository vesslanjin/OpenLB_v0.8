/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006, 2007, 2008 Jonas Latt and Bernd Stahl
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
 * Data analysis 2D MultiBlockStructures -- header file.
 */

#ifndef MULTI_DATA_ANALYSIS_2D_H
#define MULTI_DATA_ANALYSIS_2D_H

#include "core/dataAnalysis2D.h"
#include "complexGrids/multiBlockStructure/multiBlockLattice2D.h"
#include "multiDataFields2D.h"
#include <vector>

namespace olb {

template<typename T, template<typename U> class Lattice>
struct MultiAnalysisFieldsImpl2D {
  MultiAnalysisFieldsImpl2D(MultiDataDistribution2D const& distribution);
  MultiTensorField2D<T,2> velField;
  MultiTensorField2D<T,2> momentumField;
  MultiScalarField2D<T>   pressureField;
  MultiScalarField2D<T>   velNormField;
  MultiScalarField2D<T>   vortField;
  MultiTensorField2D<T,3> strainRateField;
  MultiTensorField2D<T,3> stressField;
  MultiScalarField2D<T>   divRhoUField;
  MultiScalarField2D<T>   poissonField;
  MultiTensorField2D<T,Lattice<T>::q > populationField;
};

/// Data analysis on serial block lattices, using serial data fields
template<typename T, template<typename U> class Lattice>
class MultiDataAnalysis2D : public DataAnalysisBase2D<T,Lattice> {
public:
  MultiDataAnalysis2D(MultiBlockLattice2D<T,Lattice> const& block_);
  ~MultiDataAnalysis2D();
public:
  virtual void reset() const;

  virtual TensorFieldBase2D<T,2> const& getVelocity() const;
  virtual TensorFieldBase2D<T,2> const& getMomentum() const;
  virtual ScalarFieldBase2D<T> const& getPressure() const;
  virtual ScalarFieldBase2D<T> const& getVorticity() const;
  virtual ScalarFieldBase2D<T> const& getVelocityNorm() const;
  virtual TensorFieldBase2D<T,3> const& getStrainRate() const;
  virtual TensorFieldBase2D<T,3> const& getStrainRateFromStress() const;
  virtual ScalarFieldBase2D<T> const& getDivRhoU() const;
  virtual ScalarFieldBase2D<T> const& getPoissonTerm() const;
  virtual TensorFieldBase2D<T,Lattice<T>::q > const& getPopulations() const;

  virtual T computeMeanEnstrophy() const;
  virtual T computeMeanEnstrophy2() const;

  virtual int getNx() const { return block.getNx(); }
  virtual int getNy() const { return block.getNy(); }
private:
  MultiDataAnalysis2D(MultiDataAnalysis2D<T,Lattice> const& rhs);
private:
  MultiBlockLattice2D<T,Lattice> const& block;
  std::vector<DataAnalysis2D<T,Lattice> const*>  perBlockAnalysis;
  mutable MultiAnalysisFieldsImpl2D<T,Lattice> fields;
};

}  // namespace olb;

#endif
