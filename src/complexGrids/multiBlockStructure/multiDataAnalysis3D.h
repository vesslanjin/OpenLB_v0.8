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

#ifndef MULTI_DATA_ANALYSIS_3D_H
#define MULTI_DATA_ANALYSIS_3D_H

#include "core/dataAnalysis3D.h"
#include "complexGrids/multiBlockStructure/multiBlockLattice3D.h"
#include "multiDataFields3D.h"
#include <vector>

namespace olb {

template<typename T, template<typename U> class Lattice>
struct MultiAnalysisFieldsImpl3D {
  MultiAnalysisFieldsImpl3D(MultiDataDistribution3D const& distribution);
  MultiTensorField3D<T,3> velField;
  MultiTensorField3D<T,3> momentumField;
  MultiScalarField3D<T>   pressureField;
  MultiScalarField3D<T>   velNormField;
  MultiTensorField3D<T,3> vortField;
  MultiScalarField3D<T>   vortNormField;
  MultiScalarField3D<T>   qCritField;
  MultiTensorField3D<T,6> strainRateField;
  MultiTensorField3D<T,6> stressField;
  MultiScalarField3D<T>   divRhoUField;
  MultiScalarField3D<T>   poissonField;
  MultiTensorField3D<T,Lattice<T>::q > populationField;
};

/// Data analysis on serial block lattices, using serial data fields
template<typename T, template<typename U> class Lattice>
class MultiDataAnalysis3D : public DataAnalysisBase3D<T,Lattice> {
public:
  MultiDataAnalysis3D(MultiBlockLattice3D<T,Lattice> const& block_);
  MultiDataAnalysis3D(MultiBlockLattice3D<T,Lattice> const& block_,
                      AnalysisFields3D<T,Lattice>& fields_ );
  ~MultiDataAnalysis3D();
public:
  virtual void reset() const;

  virtual TensorFieldBase3D<T,3> const& getVelocity() const;
  virtual TensorFieldBase3D<T,3> const& getMomentum() const;
  virtual ScalarFieldBase3D<T> const& getPressure() const;
  virtual TensorFieldBase3D<T,3> const& getVorticity() const;
  virtual ScalarFieldBase3D<T> const& getVelocityNorm() const;
  virtual ScalarFieldBase3D<T> const& getVorticityNorm() const;
  virtual ScalarFieldBase3D<T> const& getQCrit() const;
  virtual TensorFieldBase3D<T,6> const& getStrainRate() const;
  virtual TensorFieldBase3D<T,6> const& getStrainRateFromStress() const;
  virtual ScalarFieldBase3D<T> const& getDivRhoU() const;
  virtual ScalarFieldBase3D<T> const& getPoissonTerm() const;
  virtual TensorFieldBase3D<T,Lattice<T>::q > const& getPopulations() const;

  virtual T computeMeanEnstrophy() const;

  virtual int getNx() const { return block.getNx(); }
  virtual int getNy() const { return block.getNy(); }
  virtual int getNz() const { return block.getNz(); }
private:
  MultiDataAnalysis3D(MultiDataAnalysis3D<T,Lattice> const& rhs);
private:
  MultiBlockLattice3D<T,Lattice> const& block;
  std::vector<DataAnalysis3D<T,Lattice> const*>  perBlockAnalysis;
  mutable MultiAnalysisFieldsImpl3D<T,Lattice>     fields;
};


}  // namespace olb;

#endif
