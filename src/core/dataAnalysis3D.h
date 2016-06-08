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
 * Data analysis (formerly known as BlockStatistics) on 3D BlockStructures -- header file.
 */

#ifndef DATA_ANALYSIS_3D_H
#define DATA_ANALYSIS_3D_H

#include "dataAnalysisBase3D.h"
#include "blockLattice3D.h"
#include "dataFields3D.h"
#include "analysisFlags.h"

namespace olb {

template<typename T, template<typename U> class Lattice>
struct AnalysisFieldsImpl3D {
  AnalysisFieldsImpl3D(int nx, int ny, int nz);
  TensorField3D<T,3> velField;
  TensorField3D<T,3> momentumField;
  ScalarField3D<T>   pressureField;
  ScalarField3D<T>   velNormField;
  TensorField3D<T,3> vortField;
  ScalarField3D<T>   vortNormField;
  ScalarField3D<T>   qCritField;
  TensorField3D<T,6> strainRateField;
  TensorField3D<T,6> stressField;
  ScalarField3D<T>   divRhoUField;
  ScalarField3D<T>   poissonField;
  TensorField3D<T,Lattice<T>::q > populationField;
};

template<typename T, template<typename U> class Lattice>
struct AnalysisFields3D {
  AnalysisFields3D (
    TensorField3D<T,3>& velField_,
    TensorField3D<T,3>& momentumField_,
    ScalarField3D<T>&   pressureField_,
    ScalarField3D<T>&   velNormField_,
    TensorField3D<T,3>& vortField_,
    ScalarField3D<T>&   vortNormField_,
    ScalarField3D<T>&   qCritField_,
    TensorField3D<T,6>& strainRateField_,
    TensorField3D<T,6>& stressField_,
    ScalarField3D<T>&   divRhoUField_,
    ScalarField3D<T>&   poissonField_,
    TensorField3D<T,Lattice<T>::q >& populationField_ );

  AnalysisFields3D(AnalysisFieldsImpl3D<T,Lattice>& impl);

  TensorField3D<T,3>& velField;
  TensorField3D<T,3>& momentumField;
  ScalarField3D<T>&   pressureField;
  ScalarField3D<T>&   velNormField;
  TensorField3D<T,3>& vortField;
  ScalarField3D<T>&   vortNormField;
  ScalarField3D<T>&   qCritField;
  TensorField3D<T,6>& strainRateField;
  TensorField3D<T,6>& stressField;
  ScalarField3D<T>&   divRhoUField;
  ScalarField3D<T>&   poissonField;
  TensorField3D<T,Lattice<T>::q >& populationField;
};

/// Data analysis on serial block lattices, using serial data fields
template<typename T, template<typename U> class Lattice>
class DataAnalysis3D : public DataAnalysisBase3D<T,Lattice> {
public:
  DataAnalysis3D(BlockStructure3D<T,Lattice> const& block_);
  DataAnalysis3D(BlockStructure3D<T,Lattice> const& block_, AnalysisFields3D<T,Lattice>& fields_ );
  DataAnalysis3D(DataAnalysis3D<T,Lattice> const& rhs);
  ~DataAnalysis3D();
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
 // virtual T computeQCritField() const;

  virtual int getNx() const { return block.getNx(); }
  virtual int getNy() const { return block.getNy(); }
  virtual int getNz() const { return block.getNz(); }
private:
  void computeVelocityField() const;
  void computeMomentumField() const;
  void computePressureField() const;
  void computeVelocityNormField() const;
  void computeVorticityNormField() const;
  void computeQCritField() const;
  void computeVorticityField() const;
  void computeStrainRateField() const;
  void computeStrainRateFieldFromStress() const;
  void computeDivRhoUField() const;
  void computePoissonTerm() const;
  void computePopulations() const;
  T bulkVorticityX(int iX, int iY, int iZ) const;
  T bulkVorticityY(int iX, int iY, int iZ) const;
  T bulkVorticityZ(int iX, int iY, int iZ) const;
  T boundaryVorticityX(int iX, int iY, int iZ) const;
  T boundaryVorticityY(int iX, int iY, int iZ) const;
  T boundaryVorticityZ(int iX, int iY, int iZ) const;
  T bulkXderiv(int iX, int iY, int iZ, int iD, TensorField3D<T,3> const& field) const;
  T bulkYderiv(int iX, int iY, int iZ, int iD, TensorField3D<T,3> const& field) const;
  T bulkZderiv(int iX, int iY, int iZ, int iD, TensorField3D<T,3> const& field) const;
  T bulkDeriv(int iX, int iY, int iZ, int iAlpha, int iBeta, TensorField3D<T,3> const& field) const;
  T bulkStrain(int iX, int iY, int iZ, int iAlpha, int iBeta) const;
  T bulkDivRhoU(int iX, int iY, int iZ) const;
  T bulkPoisson(int iX, int iY, int iZ) const;
  T boundaryXderiv(int iX, int iY, int iZ, int iD, TensorField3D<T,3> const& field) const;
  T boundaryYderiv(int iX, int iY, int iZ, int iD, TensorField3D<T,3> const& field) const;
  T boundaryZderiv(int iX, int iY, int iZ, int iD, TensorField3D<T,3> const& field) const;
  T boundaryDeriv(int iX, int iY, int iZ, int iAlpha, int iBeta, TensorField3D<T,3> const& field) const;
  T boundaryStrain(int iX, int iY, int iZ, int iAlpha, int iBeta) const;
  T boundaryDivRhoU(int iX, int iY, int iZ) const;
  T boundaryPoisson(int iX, int iY, int iZ) const;
  T qCriterion(int iX, int iY, int iZ) const;
private:
  BlockStructure3D<T,Lattice> const& block;
  bool pointsToDefaultFields;
  mutable AnalysisFieldsImpl3D<T,Lattice> defaultFields;
  mutable AnalysisFields3D<T,Lattice>     fields;
  mutable AnalysisFlags3D                 flags;
};


}  // namespace olb;

#endif
