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
 * Data analysis (formerly known as BlockStatistics) on 2D BlockStructures -- generic implementation.
 */

#ifndef DATA_ANALYSIS_2D_HH
#define DATA_ANALYSIS_2D_HH

#include <cmath>
#include "dataAnalysis2D.h"
#include "cell.h"
#include "finiteDifference.h"
#include "util.h"

namespace olb {

/////// Struct AnalysisFieldsImpl2D  ///////////////////////

template<typename T, template<typename U> class Lattice>
AnalysisFieldsImpl2D<T,Lattice>::AnalysisFieldsImpl2D(int nx, int ny)
  : velField(nx, ny),
    momentumField(nx, ny),
    pressureField(nx, ny),
    velNormField(nx, ny),
    vortField(nx, ny),
    strainRateField(nx, ny),
    stressField(nx, ny),
    divRhoUField(nx, ny),
    poissonField(nx, ny),
    populationField(nx, ny)
{ }


/////// Struct AnalysisFields2D  ///////////////////////

template<typename T, template<typename U> class Lattice>
AnalysisFields2D<T,Lattice>::AnalysisFields2D (
  TensorField2D<T,2>& velField_,
  TensorField2D<T,2>& momentumField_,
  ScalarField2D<T>&   pressureField_,
  ScalarField2D<T>&   velNormField_,
  ScalarField2D<T>&   vortField_,
  TensorField2D<T,3>& strainRateField_,
  TensorField2D<T,3>& stressField_,
  ScalarField2D<T>&   divRhoUField_,
  ScalarField2D<T>&   poissonField_,
  TensorField2D<T,Lattice<T>::q >& populationField_ )
  :
  velField(velField_),
  momentumField(momentumField_),
  pressureField(pressureField_),
  velNormField(velNormField_),
  vortField(vortField_),
  strainRateField(strainRateField_),
  stressField(stressField_),
  divRhoUField(divRhoUField_),
  poissonField(poissonField_),
  populationField(populationField_)
{ }

template<typename T, template<typename U> class Lattice>
AnalysisFields2D<T,Lattice>::AnalysisFields2D(AnalysisFieldsImpl2D<T,Lattice>& impl)
  :
  velField(impl.velField),
  momentumField(impl.momentumField),
  pressureField(impl.pressureField),
  velNormField(impl.velNormField),
  vortField(impl.vortField),
  strainRateField(impl.strainRateField),
  stressField(impl.stressField),
  divRhoUField(impl.divRhoUField),
  poissonField(impl.poissonField),
  populationField(impl.populationField)
{ }

/////// Class DataAnalysis2D  /////////////////////////////

template<typename T, template<typename U> class Lattice>
DataAnalysis2D<T,Lattice>::DataAnalysis2D(BlockStructure2D<T,Lattice> const& block_)
  : block(block_),
    pointsToDefaultFields(true),
    defaultFields(block.getNx(), block.getNy()),
    fields(defaultFields)
{
  flags.reset();
}

template<typename T, template<typename U> class Lattice>
DataAnalysis2D<T,Lattice>::DataAnalysis2D(BlockStructure2D<T,Lattice> const& block_,
    AnalysisFields2D<T,Lattice>& fields_ )
  : block(block_),
    pointsToDefaultFields(false),
    defaultFields(block.getNx(), block.getNy()),
    fields(fields_ )
{
  flags.reset();
}

template<typename T, template<typename U> class Lattice>
DataAnalysis2D<T,Lattice>::DataAnalysis2D(DataAnalysis2D<T,Lattice> const& rhs)
  : block(rhs.block),
    pointsToDefaultFields(rhs.pointsToDefaultFields),
    defaultFields(rhs.defaultFields),
    fields( pointsToDefaultFields ? defaultFields : rhs.fields )
{ }

template<typename T, template<typename U> class Lattice>
DataAnalysis2D<T,Lattice>::~DataAnalysis2D() { }

template<typename T, template<typename U> class Lattice>
void DataAnalysis2D<T,Lattice>::reset() const {
  flags.reset();
}

template<typename T, template<typename U> class Lattice>
TensorFieldBase2D<T,2> const&
DataAnalysis2D<T,Lattice>::getVelocity() const
{
  computeVelocityField();
  return fields.velField;
}

template<typename T, template<typename U> class Lattice>
TensorFieldBase2D<T,2> const&
DataAnalysis2D<T,Lattice>::getMomentum() const
{
  computeMomentumField();
  return fields.momentumField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase2D<T> const&
DataAnalysis2D<T,Lattice>::getPressure() const
{
  computePressureField();
  return fields.pressureField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase2D<T> const&
DataAnalysis2D<T,Lattice>::getVelocityNorm() const
{
  computeVelocityNormField();
  return fields.velNormField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase2D<T> const&
DataAnalysis2D<T,Lattice>::getVorticity() const
{
  computeVorticityField();
  return fields.vortField;
}

template<typename T, template<typename U> class Lattice>
TensorFieldBase2D<T,3> const&
DataAnalysis2D<T,Lattice>::getStrainRate() const
{
  computeStrainRateField();
  return fields.strainRateField;
}

template<typename T, template<typename U> class Lattice>
TensorFieldBase2D<T,3> const&
DataAnalysis2D<T,Lattice>::getStrainRateFromStress() const
{
  computeStrainRateFieldFromStress();
  return fields.stressField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase2D<T> const&
DataAnalysis2D<T,Lattice>::getDivRhoU() const
{
  computeDivRhoUField();
  return fields.divRhoUField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase2D<T> const&
DataAnalysis2D<T,Lattice>::getPoissonTerm() const
{
  computePoissonTerm();
  return fields.poissonField;
}

template<typename T, template<typename U> class Lattice>
TensorFieldBase2D<T, Lattice<T>::q > const&
DataAnalysis2D<T,Lattice>::getPopulations() const
{
  computePopulationField();
  return fields.populationField;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::computeMeanEnstrophy() const {
  computeVelocityField();
  int nx = fields.velField.getNx()-1;
  int ny = fields.velField.getNy()-1;

  T enstrophy = T();
  for (int iX=0; iX<nx; ++iX) {
    for (int iY=0; iY<ny; ++iY) {
      T dyux = (
                 fields.velField.get(iX  ,iY+1)[0]
                 + fields.velField.get(iX+1,iY+1)[0]
                 - fields.velField.get(iX  ,iY  )[0]
                 - fields.velField.get(iX+1,iY  )[0] ) / (T)2;
      T dxuy = (
                 fields.velField.get(iX+1,iY  )[1]
                 + fields.velField.get(iX+1,iY+1)[1]
                 - fields.velField.get(iX  ,iY  )[1]
                 - fields.velField.get(iX  ,iY+1)[1] ) / (T)2;
      T omega = dxuy - dyux;
      enstrophy += omega*omega;
    }
  }
  enstrophy /= (2*nx*ny);
  return enstrophy;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::computeMeanEnstrophy2() const {
  computeVorticityField();
  int nx = fields.vortField.getNx();
  int ny = fields.vortField.getNy();

  T enstrophy = T();
  for (int iX=1; iX<nx-1; ++iX) {
    for (int iY=1; iY<ny-1; ++iY) {
      enstrophy += util::sqr(fields.vortField.get(iX,iY));
    }
  }

  for (int iX=1; iX<nx-1; ++iX) {
    enstrophy += 0.5* (
                   util::sqr(fields.vortField.get(iX,0)) +
                   util::sqr(fields.vortField.get(iX,ny-1)) );
  }
  for (int iY=1; iY<ny-1; ++iY) {
    enstrophy += 0.5* (
                   util::sqr(fields.vortField.get(0,iY)) +
                   util::sqr(fields.vortField.get(nx-1,iY)) );
  }
  enstrophy += 0.25 * util::sqr(fields.vortField.get(0,0));
  enstrophy += 0.25 * util::sqr(fields.vortField.get(0,ny-1));
  enstrophy += 0.25 * util::sqr(fields.vortField.get(nx-1,0));
  enstrophy += 0.25 * util::sqr(fields.vortField.get(nx-1,ny-1));

  enstrophy /= 2*(nx-1)*(ny-1);

  return enstrophy;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis2D<T,Lattice>::computeVelocityField() const {
  if (flags.velFieldComputed) return;
  fields.velField.construct();
  for (int iX=0; iX<fields.velField.getNx(); ++iX) {
    for (int iY=0; iY<fields.velField.getNy(); ++iY) {
      block.get(iX,iY).computeU(fields.velField.get(iX,iY));
    }
  }
  flags.velFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis2D<T,Lattice>::computeMomentumField() const {
  if (flags.momentumFieldComputed) return;
  fields.momentumField.construct();
  for (int iX=0; iX<fields.momentumField.getNx(); ++iX) {
    for (int iY=0; iY<fields.momentumField.getNy(); ++iY) {
      T rho;
      block.get(iX,iY).computeRhoU(rho, fields.momentumField.get(iX,iY));
      for (int iD=0; iD<Lattice<T>::d; ++iD) {
        fields.momentumField.get(iX,iY)[iD] *= rho;
      }
    }
  }
  flags.momentumFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis2D<T,Lattice>::computePressureField() const {
  if (flags.pressureFieldComputed) return;
  fields.pressureField.construct();
  for (int iX=0; iX<fields.pressureField.getNx(); ++iX) {
    for (int iY=0; iY<fields.pressureField.getNy(); ++iY) {
      fields.pressureField.get(iX,iY) = block.get(iX,iY).computeRho();
      fields.pressureField.get(iX,iY) -= (T)1;
      fields.pressureField.get(iX,iY) /= Lattice<T>::invCs2;
    }
  }
  flags.pressureFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis2D<T,Lattice>::computeVelocityNormField() const {
  if (flags.velNormFieldComputed) return;
  fields.velNormField.construct();
  computeVelocityField();
  for (int iEl=0; iEl<fields.velNormField.getNx()*fields.velNormField.getNy(); ++iEl) {
    fields.velNormField[iEl] = sqrt(util::normSqr<T,2>(fields.velField[iEl]));
  }
  flags.velNormFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::bulkVorticity(int iX, int iY) const {
  OLB_PRECONDITION(flags.velFieldComputed);
  OLB_PRECONDITION(iX>=1 && iX<=fields.vortField.getNx()-2);
  OLB_PRECONDITION(iY>=1 && iY<=fields.vortField.getNy()-2);

  T dyux = fd::centralGradient(fields.velField.get(iX,iY+1)[0],
                               fields.velField.get(iX,iY-1)[0]);
  T dxuy = fd::centralGradient(fields.velField.get(iX+1,iY)[1],
                               fields.velField.get(iX-1,iY)[1]);
  return dxuy - dyux;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::bulkXderiv (
  int iX, int iY, int iD, TensorField2D<T,2> const& field) const
{
  OLB_PRECONDITION(iX>=1 && iX<=field.getNx()-2);
  OLB_PRECONDITION(iY>=1 && iY<=field.getNy()-2);

  T dxu = fd::centralGradient(field.get(iX+1,iY)[iD],
                              field.get(iX-1,iY)[iD]);
  return dxu;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::bulkYderiv (
  int iX, int iY, int iD, TensorField2D<T,2> const& field) const
{
  OLB_PRECONDITION(iX>=1 && iX<=field.getNx()-2);
  OLB_PRECONDITION(iY>=1 && iY<=field.getNy()-2);

  T dyu = fd::centralGradient(field.get(iX,iY+1)[iD],
                              field.get(iX,iY-1)[iD]);
  return dyu;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::bulkDeriv (
  int iX, int iY, int iAlpha, int iBeta,
  TensorField2D<T,2> const& field) const
{
  switch(iAlpha) {
  case 0:
    return bulkXderiv(iX,iY,iBeta,field);
  case 1:
    return bulkYderiv(iX,iY,iBeta,field);
  default:
    OLB_ASSERT( false, "iAlpha>1!");
    return T();
  }
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::bulkStrain (
  int iX, int iY, int iAlpha, int iBeta) const
{
  OLB_PRECONDITION( flags.momentumFieldComputed );
  return ( bulkDeriv(iX,iY,iAlpha,iBeta, fields.momentumField) +
           bulkDeriv(iX,iY,iBeta,iAlpha, fields.momentumField) ) / (T)2;

}

template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::bulkDivRhoU(int iX, int iY) const {
  OLB_PRECONDITION( flags.momentumFieldComputed );
  return bulkDeriv(iX,iY, 0,0, fields.momentumField) +
         bulkDeriv(iX,iY, 1,1, fields.momentumField);
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::bulkPoisson(int iX, int iY) const {
  OLB_PRECONDITION( flags.velFieldComputed );
  T dxux = bulkDeriv(iX,iY,0,0, fields.velField);
  T dxuy = bulkDeriv(iX,iY,0,1, fields.velField);
  T dyux = bulkDeriv(iX,iY,1,0, fields.velField);
  T dyuy = bulkDeriv(iX,iY,1,1, fields.velField);
  return dxux*dxux + (T)2*dxuy*dyux + dyuy*dyuy;
}


template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::boundaryXderiv (
  int iX, int iY, int iD, TensorField2D<T,2> const& field ) const
{
  OLB_PRECONDITION(iX>=0 && iX<=field.getNx()-1);
  OLB_PRECONDITION(iY>=0 && iY<=field.getNy()-1);

  T dxu;

  if (iX==0) {
    dxu = fd::boundaryGradient(field.get(iX,iY)[iD],
                               field.get(iX+1,iY)[iD],
                               field.get(iX+2,iY)[iD]);
  }
  else if (iX==fields.vortField.getNx()-1) {
    dxu = -fd::boundaryGradient(field.get(iX,iY)[iD],
                                field.get(iX-1,iY)[iD],
                                field.get(iX-2,iY)[iD]);
  }
  else {
    dxu = fd::centralGradient(field.get(iX+1,iY)[iD],
                              field.get(iX-1,iY)[iD]);
  }

  return dxu;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::boundaryYderiv (
  int iX, int iY, int iD, TensorField2D<T,2> const& field ) const
{
  OLB_PRECONDITION(iX>=0 && iX<=field.getNx()-1);
  OLB_PRECONDITION(iY>=0 && iY<=field.getNy()-1);

  T dyu;

  if (iY==0) {
    dyu = fd::boundaryGradient(field.get(iX,iY)[iD],
                               field.get(iX,iY+1)[iD],
                               field.get(iX,iY+2)[iD]);
  }
  else if (iY==fields.vortField.getNy()-1) {
    dyu = -fd::boundaryGradient(field.get(iX,iY)[iD],
                                field.get(iX,iY-1)[iD],
                                field.get(iX,iY-2)[iD]);
  }
  else {
    dyu = fd::centralGradient(field.get(iX,iY+1)[iD],
                              field.get(iX,iY-1)[iD]);
  }

  return dyu;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::boundaryDeriv (
  int iX, int iY, int iAlpha, int iBeta,
  TensorField2D<T,2> const& field ) const
{
  switch(iAlpha) {
  case 0:
    return boundaryXderiv(iX,iY,iBeta, field);
  case 1:
    return boundaryYderiv(iX,iY,iBeta, field);
  default:
    OLB_ASSERT( false, "iAlpha>1!");
    return T();
  }
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::boundaryStrain (
  int iX, int iY, int iAlpha, int iBeta) const
{
  OLB_PRECONDITION( flags.momentumFieldComputed );
  return ( boundaryDeriv(iX,iY,iAlpha,iBeta, fields.momentumField) +
           boundaryDeriv(iX,iY,iBeta,iAlpha, fields.momentumField) ) / (T)2;

}

template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::boundaryDivRhoU(int iX, int iY) const {
  OLB_PRECONDITION( flags.momentumFieldComputed );
  return boundaryDeriv(iX,iY,0,0, fields.momentumField) +
         boundaryDeriv(iX,iY,1,1, fields.momentumField);
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::boundaryPoisson(int iX, int iY) const {
  OLB_PRECONDITION( flags.velFieldComputed );
  T dxux = boundaryDeriv(iX,iY,0,0, fields.velField);
  T dxuy = boundaryDeriv(iX,iY,0,1, fields.velField);
  T dyux = boundaryDeriv(iX,iY,1,0, fields.velField);
  T dyuy = boundaryDeriv(iX,iY,1,1, fields.velField);
  return dxux*dxux + (T)2*dxuy*dyux + dyuy*dyuy;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis2D<T,Lattice>::boundaryVorticity(int iX, int iY) const {
  OLB_PRECONDITION(flags.velFieldComputed);
  OLB_PRECONDITION(iX>=0 && iX<=fields.vortField.getNx()-1);
  OLB_PRECONDITION(iY>=0 && iY<=fields.vortField.getNy()-1);

  T dyux = boundaryYderiv(iX,iY, 0, fields.velField);
  T dxuy = boundaryXderiv(iX,iY, 1, fields.velField);

  return dxuy - dyux;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis2D<T,Lattice>::computeVorticityField() const {
  if (flags.vortFieldComputed) return;
  fields.vortField.construct();
  computeVelocityField();

  int nx = fields.vortField.getNx();
  int ny = fields.vortField.getNy();

  for (int iX=1; iX<nx-1; ++iX) {
    for (int iY=1; iY<ny-1; ++iY) {
      fields.vortField.get(iX,iY) = bulkVorticity(iX,iY);
    }
  }

  for (int iX=1; iX<nx-1; ++iX) {
    fields.vortField.get(iX,0) = boundaryVorticity(iX,0);
    fields.vortField.get(iX,ny-1) = boundaryVorticity(iX,ny-1);
  }

  for (int iY=0; iY<ny; ++iY) {
    fields.vortField.get(0,iY) = boundaryVorticity(0,iY);
    fields.vortField.get(nx-1,iY) = boundaryVorticity(nx-1,iY);
  }

  flags.vortFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis2D<T,Lattice>::computeStrainRateField() const {
  if (flags.strainRateFieldComputed) return;
  fields.strainRateField.construct();
  computeMomentumField();

  int nx = fields.vortField.getNx();
  int ny = fields.vortField.getNy();

  int iPi = 0;
  for (int iAlpha=0; iAlpha<2; ++iAlpha) {
    for (int iBeta=iAlpha; iBeta<2; ++iBeta) {

      for (int iX=1; iX<nx-1; ++iX) {
        for (int iY=1; iY<ny-1; ++iY) {
          fields.strainRateField.get(iX,iY)[iPi] =
            bulkStrain(iX,iY, iAlpha,iBeta);
        }
      }

      for (int iX=1; iX<nx-1; ++iX) {
        fields.strainRateField.get(iX,0)[iPi] =
          boundaryStrain(iX,0, iAlpha,iBeta);
        fields.strainRateField.get(iX,ny-1)[iPi] =
          boundaryStrain(iX,ny-1, iAlpha,iBeta);
      }

      for (int iY=0; iY<ny; ++iY) {
        fields.strainRateField.get(0,iY)[iPi] =
          boundaryStrain(0,iY, iAlpha,iBeta);
        fields.strainRateField.get(nx-1,iY)[iPi] =
          boundaryStrain(nx-1,iY, iAlpha,iBeta);
      }

      ++iPi;
    }
  }

  flags.strainRateFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis2D<T,Lattice>::computeStrainRateFieldFromStress() const {
  if (flags.stressFieldComputed) return;
  fields.stressField.construct();

  for (int iX=0; iX<fields.velField.getNx(); ++iX) {
    for (int iY=0; iY<fields.velField.getNy(); ++iY) {
      block.get(iX,iY).computeStress(fields.stressField.get(iX,iY));
      T omega = block.get(iX,iY).getDynamics()->getOmega();
      for (int iPi=0; iPi<3; ++iPi) {
        fields.stressField.get(iX,iY)[iPi] *=
          -omega / (T)2 * Lattice<T>::invCs2;
      }
    }
  }

  flags.stressFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis2D<T,Lattice>::computeDivRhoUField() const {
  if (flags.divRhoUFieldComputed) return;
  fields.divRhoUField.construct();
  computeMomentumField();

  int nx = fields.divRhoUField.getNx();
  int ny = fields.divRhoUField.getNy();

  for (int iX=1; iX<nx-1; ++iX) {
    for (int iY=1; iY<ny-1; ++iY) {
      fields.divRhoUField.get(iX,iY) = bulkDivRhoU(iX,iY);
    }
  }

  for (int iX=1; iX<nx-1; ++iX) {
    fields.divRhoUField.get(iX,0) = boundaryDivRhoU(iX,0);
    fields.divRhoUField.get(iX,ny-1) = boundaryDivRhoU(iX,ny-1);
  }

  for (int iY=0; iY<ny; ++iY) {
    fields.divRhoUField.get(0,iY) = boundaryDivRhoU(0,iY);
    fields.divRhoUField.get(nx-1,iY) = boundaryDivRhoU(nx-1,iY);
  }

  flags.divRhoUFieldComputed = true;
}


template<typename T, template<typename U> class Lattice>
void DataAnalysis2D<T,Lattice>::computePoissonTerm() const {
  if (flags.poissonFieldComputed) return;
  fields.poissonField.construct();
  computeVelocityField();

  int nx = fields.poissonField.getNx();
  int ny = fields.poissonField.getNy();

  for (int iX=1; iX<nx-1; ++iX) {
    for (int iY=1; iY<ny-1; ++iY) {
      fields.poissonField.get(iX,iY) = bulkPoisson(iX,iY);
    }
  }

  for (int iX=1; iX<nx-1; ++iX) {
    fields.poissonField.get(iX,0) = boundaryPoisson(iX,0);
    fields.poissonField.get(iX,ny-1) = boundaryPoisson(iX,ny-1);
  }

  for (int iY=0; iY<ny; ++iY) {
    fields.poissonField.get(0,iY) = boundaryPoisson(0,iY);
    fields.poissonField.get(nx-1,iY) = boundaryPoisson(nx-1,iY);
  }

  flags.poissonFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis2D<T,Lattice>::computePopulationField() const {
  if (flags.populationFieldComputed) return;
  fields.populationField.construct();

  int nx = fields.populationField.getNx();
  int ny = fields.populationField.getNy();
  for (int iX=0; iX<nx; ++iX) {
    for (int iY=0; iY<ny; ++iY) {
      for (int iPop=0; iPop<Lattice<T>::q; ++iPop) {
        fields.populationField.get(iX,iY)[iPop] = block.get(iX,iY)[iPop];
      }
    }
  }

  flags.populationFieldComputed = true;
}

}  // namespace olb


#endif
