/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2006, 2007 Jonas Latt and Bernd Stahl
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
 * Data analysis (formerly known as BlockStatistics) on 2D BlockStructures -- header file.
 */

#ifndef DATA_ANALYSIS_2D_H
#define DATA_ANALYSIS_2D_H

#include "dataAnalysisBase2D.h"
#include "blockLattice2D.h"
#include "dataFields2D.h"
#include "analysisFlags.h"

namespace olb {

template<typename T, template<typename U> class Lattice>
struct AnalysisFieldsImpl2D {
  AnalysisFieldsImpl2D(int nx, int ny);
  TensorField2D<T,2> velField;
  TensorField2D<T,2> momentumField;
  ScalarField2D<T>   pressureField;
  ScalarField2D<T>   velNormField;
  ScalarField2D<T>   vortField;
  TensorField2D<T,3> strainRateField;
  TensorField2D<T,3> stressField;
  ScalarField2D<T>   divRhoUField;
  ScalarField2D<T>   poissonField;
  TensorField2D<T,Lattice<T>::q > populationField;
};

template<typename T, template<typename U> class Lattice>
struct AnalysisFields2D {
  AnalysisFields2D (
    TensorField2D<T,2>& velField_,
    TensorField2D<T,2>& momentumField_,
    ScalarField2D<T>&   pressureField_,
    ScalarField2D<T>&   velNormField_,
    ScalarField2D<T>&   vortField_,
    TensorField2D<T,3>& strainRateField_,
    TensorField2D<T,3>& stressField_,
    ScalarField2D<T>&   divRhoUField_,
    ScalarField2D<T>&   poissonField_,
    TensorField2D<T,Lattice<T>::q >& populationField_ );

  AnalysisFields2D(AnalysisFieldsImpl2D<T,Lattice>& impl);

  TensorField2D<T,2>& velField;
  TensorField2D<T,2>& momentumField;
  ScalarField2D<T>&   pressureField;
  ScalarField2D<T>&   velNormField;
  ScalarField2D<T>&   vortField;
  TensorField2D<T,3>& strainRateField;
  TensorField2D<T,3>& stressField;
  ScalarField2D<T>&   divRhoUField;
  ScalarField2D<T>&   poissonField;
  TensorField2D<T,Lattice<T>::q >& populationField;
};

/// Data analysis on serial block lattices, using serial data fields
template<typename T, template<typename U> class Lattice>
class DataAnalysis2D : public DataAnalysisBase2D<T,Lattice> {
public:
  DataAnalysis2D(BlockStructure2D<T,Lattice> const& block_);
  DataAnalysis2D(BlockStructure2D<T,Lattice> const& block_, AnalysisFields2D<T,Lattice>& fields_ );
  DataAnalysis2D(DataAnalysis2D<T,Lattice> const& rhs);
  ~DataAnalysis2D();
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
  void computeVelocityField() const;
  void computeMomentumField() const;
  void computePressureField() const;
  void computeVelocityNormField() const;
  void computeVorticityField() const;
  void computeStrainRateField() const;
  void computeStrainRateFieldFromStress() const;
  void computeDivRhoUField() const;
  void computePoissonTerm() const;
  void computePopulationField() const;
  T bulkVorticity(int iX, int iY) const;
  T boundaryVorticity(int iX, int iY) const;
  T bulkXderiv(int iX, int iY, int iD, TensorField2D<T,2> const& field) const;
  T bulkYderiv(int iX, int iY, int iD, TensorField2D<T,2> const& field) const;
  T bulkDeriv(int iX, int iY, int iAlpha, int iBeta, TensorField2D<T,2> const& field) const;
  T bulkStrain(int iX, int iY, int iAlpha, int iBeta) const;
  T bulkDivRhoU(int iX, int iY) const;
  T bulkPoisson(int iX, int iY) const;
  T boundaryXderiv(int iX, int iY, int iD, TensorField2D<T,2> const& field) const;
  T boundaryYderiv(int iX, int iY, int iD, TensorField2D<T,2> const& field) const;
  T boundaryDeriv(int iX, int iY, int iAlpha, int iBeta, TensorField2D<T,2> const& field) const;
  T boundaryStrain(int iX, int iY, int iAlpha, int iBeta) const;
  T boundaryDivRhoU(int iX, int iY) const;
  T boundaryPoisson(int iX, int iY) const;
private:
  BlockStructure2D<T,Lattice> const& block;
  bool pointsToDefaultFields;
  mutable AnalysisFieldsImpl2D<T,Lattice> defaultFields;
  mutable AnalysisFields2D<T,Lattice>     fields;
  mutable AnalysisFlags2D                 flags;
};

}  // namespace olb;

#endif
