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
 * Data analysis (formerly known as BlockStatistics) on 3D BlockStructures -- generic implementation.
 */

#ifndef DATA_ANALYSIS_3D_HH
#define DATA_ANALYSIS_3D_HH

#include <cmath>
#include "dataAnalysis3D.h"
#include "cell.h"
#include "finiteDifference.h"
#include "util.h"
using namespace std;
namespace olb {

/////// Struct AnalysisFieldsImpl3D  ///////////////////////

template<typename T, template<typename U> class Lattice>
AnalysisFieldsImpl3D<T,Lattice>::AnalysisFieldsImpl3D(int nx, int ny, int nz)
  : velField(nx, ny, nz),
    momentumField(nx, ny, nz),
    pressureField(nx, ny, nz),
    velNormField(nx, ny, nz),
    vortField(nx, ny, nz),
    vortNormField(nx, ny, nz),
    qCritField(nx, ny, nz),
    strainRateField(nx, ny, nz),
    stressField(nx, ny, nz),
    divRhoUField(nx, ny, nz),
    poissonField(nx, ny, nz),
    populationField(nx, ny, nz)
{ }


/////// Struct AnalysisFields3D  ///////////////////////

template<typename T, template<typename U> class Lattice>
AnalysisFields3D<T,Lattice>::AnalysisFields3D (
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
  TensorField3D<T,Lattice<T>::q >& populationField_ )
  :
  velField(velField_),
  momentumField(momentumField_),
  pressureField(pressureField_),
  velNormField(velNormField_),
  vortField(vortField_),
  vortNormField(vortNormField_),
  qCritField(qCritField_),
  strainRateField(strainRateField_),
  stressField(stressField_),
  divRhoUField(divRhoUField_),
  poissonField(poissonField_),
  populationField(populationField_)
{ }

template<typename T, template<typename U> class Lattice>
AnalysisFields3D<T,Lattice>::AnalysisFields3D(AnalysisFieldsImpl3D<T,Lattice>& impl)
  :
  velField(impl.velField),
  momentumField(impl.momentumField),
  pressureField(impl.pressureField),
  velNormField(impl.velNormField),
  vortField(impl.vortField),
  vortNormField(impl.vortNormField),
  qCritField(impl.qCritField),
  strainRateField(impl.strainRateField),
  stressField(impl.stressField),
  divRhoUField(impl.divRhoUField),
  poissonField(impl.poissonField),
  populationField(impl.populationField)
{ }


/////// Class DataAnalysis3D  /////////////////////////////

template<typename T, template<typename U> class Lattice>
DataAnalysis3D<T,Lattice>::DataAnalysis3D (
  BlockStructure3D<T,Lattice> const& block_ )
  : block(block_),
    pointsToDefaultFields(true),
    defaultFields(block.getNx(), block.getNy(), block.getNz()),
    fields(defaultFields)
{
  flags.reset();
}

template<typename T, template<typename U> class Lattice>
DataAnalysis3D<T,Lattice>::DataAnalysis3D(BlockStructure3D<T,Lattice> const& block_,
    AnalysisFields3D<T,Lattice>& fields_ )
  : block(block_),
    pointsToDefaultFields(false),
    defaultFields(block.getNx(), block.getNy(), block.getNz()),
    fields(fields_ )
{
  flags.reset();
}

template<typename T, template<typename U> class Lattice>
DataAnalysis3D<T,Lattice>::DataAnalysis3D(DataAnalysis3D<T,Lattice> const& rhs)
  : block(rhs.block),
    pointsToDefaultFields(rhs.pointsToDefaultFields),
    defaultFields(rhs.defaultFields),
    fields( pointsToDefaultFields ? defaultFields : rhs.fields )
{ }


template<typename T, template<typename U> class Lattice>
DataAnalysis3D<T,Lattice>::~DataAnalysis3D() { }

template<typename T, template<typename U> class Lattice>
void DataAnalysis3D<T,Lattice>::reset() const {
  flags.reset();
}

template<typename T, template<typename U> class Lattice>
TensorFieldBase3D<T,3> const& DataAnalysis3D<T,Lattice>::getVelocity() const
{
  computeVelocityField();
  return fields.velField;
}

template<typename T, template<typename U> class Lattice>
TensorFieldBase3D<T,3> const&
DataAnalysis3D<T,Lattice>::getMomentum() const
{
  computeMomentumField();
  return fields.momentumField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase3D<T> const&
DataAnalysis3D<T,Lattice>::getPressure() const
{
  computePressureField();
  return fields.pressureField;
}

template<typename T, template<typename U> class Lattice>
TensorFieldBase3D<T,3> const&
DataAnalysis3D<T,Lattice>::getVorticity() const
{
  computeVorticityField();
  return fields.vortField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase3D<T> const&
DataAnalysis3D<T,Lattice>::getVelocityNorm() const
{
  computeVelocityNormField();
  return fields.velNormField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase3D<T> const&
DataAnalysis3D<T,Lattice>::getVorticityNorm() const
{
  computeVorticityNormField();
  return fields.vortNormField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase3D<T> const&
DataAnalysis3D<T,Lattice>::getQCrit() const
{
  computeQCritField();
  return fields.qCritField;
}


template<typename T, template<typename U> class Lattice>
TensorFieldBase3D<T,6> const&
DataAnalysis3D<T,Lattice>::getStrainRate() const
{
  computeStrainRateField();
  return fields.strainRateField;
}

template<typename T, template<typename U> class Lattice>
TensorFieldBase3D<T,6> const&
DataAnalysis3D<T,Lattice>::getStrainRateFromStress() const
{
  computeStrainRateFieldFromStress();
  return fields.stressField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase3D<T> const&
DataAnalysis3D<T,Lattice>::getDivRhoU() const
{
  computeDivRhoUField();
  return fields.divRhoUField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase3D<T> const&
DataAnalysis3D<T,Lattice>::getPoissonTerm() const
{
  computePoissonTerm();
  return fields.poissonField;
}

template<typename T, template<typename U> class Lattice>
TensorFieldBase3D<T, Lattice<T>::q > const&
DataAnalysis3D<T,Lattice>::getPopulations() const
{
  computePopulations();
  return fields.populationField;
}


template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::computeMeanEnstrophy() const {
  computeVelocityField();
  int nx = fields.velField.getNx()-1;
  int ny = fields.velField.getNy()-1;
  int nz = fields.velField.getNz()-1;

  T enstrophy = T();
  for (int iX=0; iX<nx; ++iX) {
    for (int iY=0; iY<ny; ++iY) {
      for (int iZ=0; iZ<nz; ++iZ) {
        T dxuy = (
                   fields.velField.get(iX+1,iY+1,iZ  )[1]
                   + fields.velField.get(iX+1,iY  ,iZ  )[1]
                   + fields.velField.get(iX+1,iY+1,iZ+1)[1]
                   + fields.velField.get(iX+1,iY  ,iZ+1)[1]
                   - fields.velField.get(iX  ,iY+1,iZ  )[1]
                   - fields.velField.get(iX  ,iY  ,iZ  )[1]
                   - fields.velField.get(iX  ,iY+1,iZ+1)[1]
                   - fields.velField.get(iX  ,iY  ,iZ+1)[1] ) / (T)4;
        T dxuz = (
                   fields.velField.get(iX+1,iY+1,iZ  )[2]
                   + fields.velField.get(iX+1,iY  ,iZ  )[2]
                   + fields.velField.get(iX+1,iY+1,iZ+1)[2]
                   + fields.velField.get(iX+1,iY  ,iZ+1)[2]
                   - fields.velField.get(iX  ,iY+1,iZ  )[2]
                   - fields.velField.get(iX  ,iY  ,iZ  )[2]
                   - fields.velField.get(iX  ,iY+1,iZ+1)[2]
                   - fields.velField.get(iX  ,iY  ,iZ+1)[2] ) / (T)4;
        T dyux = (
                   fields.velField.get(iX  ,iY+1,iZ  )[0]
                   + fields.velField.get(iX+1,iY+1,iZ  )[0]
                   + fields.velField.get(iX  ,iY+1,iZ+1)[0]
                   + fields.velField.get(iX+1,iY+1,iZ+1)[0]
                   - fields.velField.get(iX  ,iY  ,iZ  )[0]
                   - fields.velField.get(iX+1,iY  ,iZ  )[0]
                   - fields.velField.get(iX  ,iY  ,iZ+1)[0]
                   - fields.velField.get(iX+1,iY  ,iZ+1)[0] ) / (T)4;
        T dyuz = (
                   fields.velField.get(iX  ,iY+1,iZ  )[2]
                   + fields.velField.get(iX+1,iY+1,iZ  )[2]
                   + fields.velField.get(iX  ,iY+1,iZ+1)[2]
                   + fields.velField.get(iX+1,iY+1,iZ+1)[2]
                   - fields.velField.get(iX  ,iY  ,iZ  )[2]
                   - fields.velField.get(iX+1,iY  ,iZ  )[2]
                   - fields.velField.get(iX  ,iY  ,iZ+1)[2]
                   - fields.velField.get(iX+1,iY  ,iZ+1)[2] ) / (T)4;
        T dzux = (
                   fields.velField.get(iX  ,iY  ,iZ+1)[0]
                   + fields.velField.get(iX+1,iY+1,iZ+1)[0]
                   + fields.velField.get(iX  ,iY+1,iZ+1)[0]
                   + fields.velField.get(iX+1,iY  ,iZ+1)[0]
                   - fields.velField.get(iX  ,iY  ,iZ  )[0]
                   - fields.velField.get(iX+1,iY  ,iZ  )[0]
                   - fields.velField.get(iX  ,iY+1,iZ  )[0]
                   - fields.velField.get(iX+1,iY+1,iZ  )[0] ) / (T)4;
        T dzuy = (
                   fields.velField.get(iX  ,iY  ,iZ+1)[1]
                   + fields.velField.get(iX+1,iY+1,iZ+1)[1]
                   + fields.velField.get(iX  ,iY+1,iZ+1)[1]
                   + fields.velField.get(iX+1,iY  ,iZ+1)[1]
                   - fields.velField.get(iX  ,iY  ,iZ  )[1]
                   - fields.velField.get(iX+1,iY  ,iZ  )[1]
                   - fields.velField.get(iX  ,iY+1,iZ  )[1]
                   - fields.velField.get(iX+1,iY+1,iZ  )[1] ) / (T)4;

        T omegaX = dyuz - dzuy;
        T omegaY = dzux - dxuz;
        T omegaZ = dxuy - dyux;

        enstrophy += omegaX*omegaX+omegaY*omegaY+omegaZ*omegaZ;
      }
    }
  }
  enstrophy /= (2*nx*ny*nz);
  return enstrophy;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis3D<T,Lattice>::computeQCritField() const {
  if (flags.qCritFieldComputed) return;
  fields.qCritField.construct();
 for (int iX=0; iX<fields.qCritField.getNx()-1; ++iX) {
   for (int iY=0; iY<fields.qCritField.getNy()-1; ++iY) {
     for (int iZ=0; iZ<fields.qCritField.getNz()-1; ++iZ) {
        //cout << "test "<< iX<<" "<<iY<<" "<<iZ<< endl;
        fields.qCritField.get(iX,iY,iZ) =qCriterion(iX, iY, iZ);
          
      //for (size_t iEl=0; iEl<fields.qCritField.getSize(); ++iEl) {
      //  fields.qCritField.get(iX,iY,iZ) = -1./2.*qCriterion();
        //fields.qCritField[iEl] =-1./2.*fields.qCritField[iEl];
      // }
    }
   }
  }
  flags.qCritFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::qCriterion(int iX, int iY, int iZ) const {
  computeVelocityField();
  //int nx = fields.velField.getNx()-1;
  //int ny = fields.velField.getNy()-1;
  //int nz = fields.velField.getNz()-1;

  T qCrit = T();
  // for (int iX=0; iX<nx; ++iX) {
  //   for (int iY=0; iY<ny; ++iY) {
  //     for (int iZ=0; iZ<nz; ++iZ) {

        T dxux = (
                   fields.velField.get(iX+1,iY+1,iZ  )[0]
                   + fields.velField.get(iX+1,iY  ,iZ  )[0]
                   + fields.velField.get(iX+1,iY+1,iZ+1)[0]
                   + fields.velField.get(iX+1,iY  ,iZ+1)[0]
                   - fields.velField.get(iX  ,iY+1,iZ  )[0]
                   - fields.velField.get(iX  ,iY  ,iZ  )[0]
                   - fields.velField.get(iX  ,iY+1,iZ+1)[0]
                   - fields.velField.get(iX  ,iY  ,iZ+1)[0] ) / (T)4;
        T dxuy = (
                   fields.velField.get(iX+1,iY+1,iZ  )[1]
                   + fields.velField.get(iX+1,iY  ,iZ  )[1]
                   + fields.velField.get(iX+1,iY+1,iZ+1)[1]
                   + fields.velField.get(iX+1,iY  ,iZ+1)[1]
                   - fields.velField.get(iX  ,iY+1,iZ  )[1]
                   - fields.velField.get(iX  ,iY  ,iZ  )[1]
                   - fields.velField.get(iX  ,iY+1,iZ+1)[1]
                   - fields.velField.get(iX  ,iY  ,iZ+1)[1] ) / (T)4;
        T dxuz = (
                   fields.velField.get(iX+1,iY+1,iZ  )[2]
                   + fields.velField.get(iX+1,iY  ,iZ  )[2]
                   + fields.velField.get(iX+1,iY+1,iZ+1)[2]
                   + fields.velField.get(iX+1,iY  ,iZ+1)[2]
                   - fields.velField.get(iX  ,iY+1,iZ  )[2]
                   - fields.velField.get(iX  ,iY  ,iZ  )[2]
                   - fields.velField.get(iX  ,iY+1,iZ+1)[2]
                   - fields.velField.get(iX  ,iY  ,iZ+1)[2] ) / (T)4;
        T dyux = (
                   fields.velField.get(iX  ,iY+1,iZ  )[0]
                   + fields.velField.get(iX+1,iY+1,iZ  )[0]
                   + fields.velField.get(iX  ,iY+1,iZ+1)[0]
                   + fields.velField.get(iX+1,iY+1,iZ+1)[0]
                   - fields.velField.get(iX  ,iY  ,iZ  )[0]
                   - fields.velField.get(iX+1,iY  ,iZ  )[0]
                   - fields.velField.get(iX  ,iY  ,iZ+1)[0]
                   - fields.velField.get(iX+1,iY  ,iZ+1)[0] ) / (T)4;
        T dyuy = (
                   fields.velField.get(iX  ,iY+1,iZ  )[1]
                   + fields.velField.get(iX+1,iY+1,iZ  )[1]
                   + fields.velField.get(iX  ,iY+1,iZ+1)[1]
                   + fields.velField.get(iX+1,iY+1,iZ+1)[1]
                   - fields.velField.get(iX  ,iY  ,iZ  )[1]
                   - fields.velField.get(iX+1,iY  ,iZ  )[1]
                   - fields.velField.get(iX  ,iY  ,iZ+1)[1]
                   - fields.velField.get(iX+1,iY  ,iZ+1)[1] ) / (T)4;
        T dyuz = (
                   fields.velField.get(iX  ,iY+1,iZ  )[2]
                   + fields.velField.get(iX+1,iY+1,iZ  )[2]
                   + fields.velField.get(iX  ,iY+1,iZ+1)[2]
                   + fields.velField.get(iX+1,iY+1,iZ+1)[2]
                   - fields.velField.get(iX  ,iY  ,iZ  )[2]
                   - fields.velField.get(iX+1,iY  ,iZ  )[2]
                   - fields.velField.get(iX  ,iY  ,iZ+1)[2]
                   - fields.velField.get(iX+1,iY  ,iZ+1)[2] ) / (T)4;
        T dzux = (
                   fields.velField.get(iX  ,iY  ,iZ+1)[0]
                   + fields.velField.get(iX+1,iY+1,iZ+1)[0]
                   + fields.velField.get(iX  ,iY+1,iZ+1)[0]
                   + fields.velField.get(iX+1,iY  ,iZ+1)[0]
                   - fields.velField.get(iX  ,iY  ,iZ  )[0]
                   - fields.velField.get(iX+1,iY  ,iZ  )[0]
                   - fields.velField.get(iX  ,iY+1,iZ  )[0]
                   - fields.velField.get(iX+1,iY+1,iZ  )[0] ) / (T)4;
        T dzuy = (
                   fields.velField.get(iX  ,iY  ,iZ+1)[1]
                   + fields.velField.get(iX+1,iY+1,iZ+1)[1]
                   + fields.velField.get(iX  ,iY+1,iZ+1)[1]
                   + fields.velField.get(iX+1,iY  ,iZ+1)[1]
                   - fields.velField.get(iX  ,iY  ,iZ  )[1]
                   - fields.velField.get(iX+1,iY  ,iZ  )[1]
                   - fields.velField.get(iX  ,iY+1,iZ  )[1]
                   - fields.velField.get(iX+1,iY+1,iZ  )[1] ) / (T)4;
        T dzuz = (
                   fields.velField.get(iX  ,iY  ,iZ+1)[2]
                   + fields.velField.get(iX+1,iY+1,iZ+1)[2]
                   + fields.velField.get(iX  ,iY+1,iZ+1)[2]
                   + fields.velField.get(iX+1,iY  ,iZ+1)[2]
                   - fields.velField.get(iX  ,iY  ,iZ  )[2]
                   - fields.velField.get(iX+1,iY  ,iZ  )[2]
                   - fields.velField.get(iX  ,iY+1,iZ  )[2]
                   - fields.velField.get(iX+1,iY+1,iZ  )[2] ) / (T)4;


        qCrit = dxux*dxux+dyux*dxuy+dzux*dxuz
               +dxuy*dyux+dyuy*dyuy+dzuy*dyuz
               +dxuz*dzux+dyuz*dzuy+dzuz*dzuz;
 //       cout << qCrit<<endl;
        qCrit *= (-1./2.);
  //     }
  //   }
  // }
 
  return qCrit;
}




template<typename T, template<typename U> class Lattice>
void DataAnalysis3D<T,Lattice>::computeVelocityField() const {
  if (flags.velFieldComputed) return;
  fields.velField.construct();
  for (int iX=0; iX<fields.velField.getNx(); ++iX) {
    for (int iY=0; iY<fields.velField.getNy(); ++iY) {
      for (int iZ=0; iZ<fields.velField.getNz(); ++iZ) {
        block.get(iX,iY,iZ).computeU(fields.velField.get(iX,iY,iZ));
      }
    }
  }
  flags.velFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis3D<T,Lattice>::computeMomentumField() const {
  if (flags.momentumFieldComputed) return;
  fields.momentumField.construct();
  for (int iX=0; iX<fields.momentumField.getNx(); ++iX) {
    for (int iY=0; iY<fields.momentumField.getNy(); ++iY) {
      for (int iZ=0; iZ<fields.momentumField.getNz(); ++iZ) {
        T rho;
        block.get(iX,iY,iZ).computeRhoU (
          rho, fields.momentumField.get(iX,iY,iZ) );
        for (int iD=0; iD<Lattice<T>::d; ++iD) {
          fields.momentumField.get(iX,iY,iZ)[iD] *= rho;
        }
      }
    }
  }
  flags.momentumFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis3D<T,Lattice>::computePressureField() const {
  if (flags.pressureFieldComputed) return;
  fields.pressureField.construct();
  for (int iX=0; iX<fields.pressureField.getNx(); ++iX) {
    for (int iY=0; iY<fields.pressureField.getNy(); ++iY) {
      for (int iZ=0; iZ<fields.pressureField.getNz(); ++iZ) {
        fields.pressureField.get(iX,iY,iZ) =
          block.get(iX,iY,iZ).computeRho();
        fields.pressureField.get(iX,iY,iZ) -= (T)1;
        fields.pressureField.get(iX,iY,iZ) /= Lattice<T>::invCs2;
      }
    }
  }
  flags.pressureFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis3D<T,Lattice>::computeVelocityNormField() const {
  if (flags.velNormFieldComputed) return;
  fields.velNormField.construct();
  computeVelocityField();
  for (size_t iEl=0; iEl<fields.velNormField.getSize(); ++iEl) {
    fields.velNormField[iEl] = sqrt(util::normSqr<T,3>(fields.velField[iEl]));
  }
  flags.velNormFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis3D<T,Lattice>::computeVorticityNormField() const {
  if (flags.vortNormFieldComputed) return;
  fields.vortNormField.construct();
  computeVorticityField();
  for (size_t iEl=0; iEl<fields.vortNormField.getSize(); ++iEl) {
    fields.vortNormField[iEl] = sqrt(util::normSqr<T,3>(fields.vortField[iEl]));
  }
  flags.vortNormFieldComputed = true;
}



// template<typename T, template<typename U> class Lattice>
// void DataAnalysis3D<T,Lattice>::computeQCritField() const {
//   if (flags.qCritFieldComputed) return;
//   fields.qCritField.construct();
  

//   for (size_t iEl=0; iEl<fields.qCritField.getSize(); ++iEl) {
//     fields.qCritField[iEl] = -1./2.*fields.strainRateField[iEl];
//   }
//   flags.qCritFieldComputed = true;
// }



template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::bulkVorticityX(int iX, int iY, int iZ) const {
  OLB_PRECONDITION(flags.velFieldComputed);
  OLB_PRECONDITION(iX>=1 && iX<=fields.vortField.getNx()-2);
  OLB_PRECONDITION(iY>=1 && iY<=fields.vortField.getNy()-2);
  OLB_PRECONDITION(iZ>=1 && iZ<=fields.vortField.getNz()-2);

  T dyuz = bulkYderiv(iX,iY,iZ, 2, fields.velField);
  T dzuy = bulkZderiv(iX,iY,iZ, 1, fields.velField);

  return dyuz - dzuy;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::bulkVorticityY(int iX, int iY, int iZ) const {
  OLB_PRECONDITION(flags.velFieldComputed);
  OLB_PRECONDITION(iX>=1 && iX<=fields.vortField.getNx()-2);
  OLB_PRECONDITION(iY>=1 && iY<=fields.vortField.getNy()-2);
  OLB_PRECONDITION(iZ>=1 && iZ<=fields.vortField.getNz()-2);

  T dzux = bulkZderiv(iX,iY,iZ, 0, fields.velField);
  T dxuz = bulkXderiv(iX,iY,iZ, 2, fields.velField);

  return dzux - dxuz;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::bulkVorticityZ(int iX, int iY, int iZ) const {
  OLB_PRECONDITION(iX>=1 && iX<=fields.vortField.getNx()-2);
  OLB_PRECONDITION(iY>=1 && iY<=fields.vortField.getNy()-2);
  OLB_PRECONDITION(iZ>=1 && iZ<=fields.vortField.getNz()-2);

  T dxuy = bulkXderiv(iX,iY,iZ, 1, fields.velField);
  T dyux = bulkYderiv(iX,iY,iZ, 0, fields.velField);

  return dxuy - dyux;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::bulkXderiv (
  int iX, int iY, int iZ, int iD,
  TensorField3D<T,3> const& field) const
{
  OLB_PRECONDITION(iX>=1 && iX<=field.getNx()-2);
  OLB_PRECONDITION(iY>=1 && iY<=field.getNy()-2);
  OLB_PRECONDITION(iZ>=1 && iZ<=field.getNz()-2);

  T dxu = fd::centralGradient(field.get(iX+1,iY,iZ)[iD],
                              field.get(iX-1,iY,iZ)[iD]);
  return dxu;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::bulkYderiv (
  int iX, int iY, int iZ, int iD,
  TensorField3D<T,3> const& field) const
{
  OLB_PRECONDITION(iX>=1 && iX<=field.getNx()-2);
  OLB_PRECONDITION(iY>=1 && iY<=field.getNy()-2);
  OLB_PRECONDITION(iZ>=1 && iZ<=field.getNz()-2);

  T dyu = fd::centralGradient(field.get(iX,iY+1,iZ)[iD],
                              field.get(iX,iY-1,iZ)[iD]);
  return dyu;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::bulkZderiv (
  int iX, int iY, int iZ, int iD,
  TensorField3D<T,3> const& field) const
{
  OLB_PRECONDITION(iX>=1 && iX<=field.getNx()-2);
  OLB_PRECONDITION(iY>=1 && iY<=field.getNy()-2);
  OLB_PRECONDITION(iZ>=1 && iZ<=field.getNz()-2);

  T dzu = fd::centralGradient(field.get(iX,iY,iZ+1)[iD],
                              field.get(iX,iY,iZ-1)[iD]);
  return dzu;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::bulkDeriv (
  int iX, int iY, int iZ, int iAlpha, int iBeta,
  TensorField3D<T,3> const& field) const
{
  switch(iAlpha) {
  case 0:
    return bulkXderiv(iX,iY,iZ, iBeta, field);
  case 1:
    return bulkYderiv(iX,iY,iZ, iBeta, field);
  case 2:
    return bulkZderiv(iX,iY,iZ, iBeta, field);
  default:
    OLB_ASSERT( false, "iAlpha>2!");
    return T();
  }
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::bulkStrain (
  int iX, int iY, int iZ, int iAlpha, int iBeta) const
{
  OLB_PRECONDITION( flags.momentumFieldComputed );
  return ( bulkDeriv(iX,iY,iZ, iAlpha,iBeta, fields.momentumField) +
           bulkDeriv(iX,iY,iZ, iBeta,iAlpha, fields.momentumField) ) / (T)2;

}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::bulkDivRhoU(int iX, int iY, int iZ) const {
  OLB_PRECONDITION( flags.momentumFieldComputed );
  return bulkDeriv(iX,iY,iZ, 0,0, fields.momentumField) +
         bulkDeriv(iX,iY,iZ, 1,1, fields.momentumField) +
         bulkDeriv(iX,iY,iZ, 2,2, fields.momentumField);
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::bulkPoisson(int iX, int iY, int iZ) const {
  OLB_PRECONDITION( flags.velFieldComputed );

  T dxux = bulkDeriv(iX,iY,iZ, 0,0, fields.velField);
  T dxuy = bulkDeriv(iX,iY,iZ, 0,1, fields.velField);
  T dxuz = bulkDeriv(iX,iY,iZ, 0,2, fields.velField);
  T dyux = bulkDeriv(iX,iY,iZ, 1,0, fields.velField);
  T dyuy = bulkDeriv(iX,iY,iZ, 1,1, fields.velField);
  T dyuz = bulkDeriv(iX,iY,iZ, 1,2, fields.velField);
  T dzux = bulkDeriv(iX,iY,iZ, 2,0, fields.velField);
  T dzuy = bulkDeriv(iX,iY,iZ, 2,1, fields.velField);
  T dzuz = bulkDeriv(iX,iY,iZ, 2,2, fields.velField);

  return dxux*dxux + dyuy*dyuy + dzuz*dzuz +
         (T)2*( dxuy*dyux + dxuz*dzux + dyuz*dzuy );
}


template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::boundaryXderiv (
  int iX, int iY, int iZ, int iD,
  TensorField3D<T,3> const& field) const
{
  OLB_PRECONDITION(iX>=0 && iX<=field.getNx()-1);
  OLB_PRECONDITION(iY>=0 && iY<=field.getNy()-1);
  OLB_PRECONDITION(iZ>=0 && iZ<=field.getNz()-1);

  T dxu;

  if (iX==0) {
    dxu = fd::boundaryGradient(field.get(iX,iY,iZ)[iD],
                               field.get(iX+1,iY,iZ)[iD],
                               field.get(iX+2,iY,iZ)[iD]);
  }
  else if (iX==field.getNx()-1) {
    dxu = -fd::boundaryGradient(field.get(iX,iY,iZ)[iD],
                                field.get(iX-1,iY,iZ)[iD],
                                field.get(iX-2,iY,iZ)[iD]);
  }
  else {
    dxu = fd::centralGradient(field.get(iX+1,iY,iZ)[iD],
                              field.get(iX-1,iY,iZ)[iD]);
  }

  return dxu;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::boundaryYderiv (
  int iX, int iY, int iZ, int iD,
  TensorField3D<T,3> const& field) const
{
  OLB_PRECONDITION(iX>=0 && iX<=field.getNx()-1);
  OLB_PRECONDITION(iY>=0 && iY<=field.getNy()-1);
  OLB_PRECONDITION(iZ>=0 && iZ<=field.getNz()-1);

  T dyu;

  if (iY==0) {
    dyu = fd::boundaryGradient(field.get(iX,iY,iZ)[iD],
                               field.get(iX,iY+1,iZ)[iD],
                               field.get(iX,iY+2,iZ)[iD]);
  }
  else if (iY==field.getNy()-1) {
    dyu = -fd::boundaryGradient(field.get(iX,iY,iZ)[iD],
                                field.get(iX,iY-1,iZ)[iD],
                                field.get(iX,iY-2,iZ)[iD]);
  }
  else {
    dyu = fd::centralGradient(field.get(iX,iY+1,iZ)[iD],
                              field.get(iX,iY-1,iZ)[iD]);
  }

  return dyu;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::boundaryZderiv (
  int iX, int iY, int iZ, int iD,
  TensorField3D<T,3> const& field) const
{
  OLB_PRECONDITION(iX>=0 && iX<=field.getNx()-1);
  OLB_PRECONDITION(iY>=0 && iY<=field.getNy()-1);
  OLB_PRECONDITION(iZ>=0 && iZ<=field.getNz()-1);

  T dzu;

  if (iZ==0) {
    dzu = fd::boundaryGradient(field.get(iX,iY,iZ)[iD],
                               field.get(iX,iY,iZ+1)[iD],
                               field.get(iX,iY,iZ+2)[iD]);
  }
  else if (iZ==field.getNz()-1) {
    dzu = -fd::boundaryGradient(field.get(iX,iY,iZ)[iD],
                                field.get(iX,iY,iZ-1)[iD],
                                field.get(iX,iY,iZ-2)[iD]);
  }
  else {
    dzu = fd::centralGradient(field.get(iX,iY,iZ+1)[iD],
                              field.get(iX,iY,iZ-1)[iD]);
  }

  return dzu;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::boundaryDeriv (
  int iX, int iY, int iZ, int iAlpha, int iBeta,
  TensorField3D<T,3> const& field) const
{
  switch(iAlpha) {
  case 0:
    return boundaryXderiv(iX,iY,iZ, iBeta, field);
  case 1:
    return boundaryYderiv(iX,iY,iZ, iBeta, field);
  case 2:
    return boundaryZderiv(iX,iY,iZ, iBeta, field);
  default:
    OLB_ASSERT( false, "iAlpha>2!");
    return T();
  }
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::boundaryStrain (
  int iX, int iY, int iZ, int iAlpha, int iBeta) const
{
  OLB_PRECONDITION( flags.momentumFieldComputed );
  return ( boundaryDeriv(iX,iY,iZ,iAlpha,iBeta, fields.momentumField) +
           boundaryDeriv(iX,iY,iZ,iBeta,iAlpha, fields.momentumField) ) / (T)2;

}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::boundaryDivRhoU (
  int iX, int iY, int iZ) const
{
  OLB_PRECONDITION( flags.momentumFieldComputed );
  return boundaryDeriv(iX,iY,iZ, 0,0, fields.momentumField) +
         boundaryDeriv(iX,iY,iZ, 1,1, fields.momentumField) +
         boundaryDeriv(iX,iY,iZ, 2,2, fields.momentumField);
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::boundaryPoisson (
  int iX, int iY, int iZ) const
{
  OLB_PRECONDITION( flags.velFieldComputed );

  T dxux = boundaryDeriv(iX,iY,iZ, 0,0, fields.velField);
  T dxuy = boundaryDeriv(iX,iY,iZ, 0,1, fields.velField);
  T dxuz = boundaryDeriv(iX,iY,iZ, 0,2, fields.velField);
  T dyux = boundaryDeriv(iX,iY,iZ, 1,0, fields.velField);
  T dyuy = boundaryDeriv(iX,iY,iZ, 1,1, fields.velField);
  T dyuz = boundaryDeriv(iX,iY,iZ, 1,2, fields.velField);
  T dzux = boundaryDeriv(iX,iY,iZ, 2,0, fields.velField);
  T dzuy = boundaryDeriv(iX,iY,iZ, 2,1, fields.velField);
  T dzuz = boundaryDeriv(iX,iY,iZ, 2,2, fields.velField);

  return dxux*dxux + dyuy*dyuy + dzuz*dzuz +
         (T)2*( dxuy*dyux + dxuz*dzux + dyuz*dzuy );
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::boundaryVorticityX (
  int iX, int iY, int iZ) const
{
  OLB_PRECONDITION(flags.velFieldComputed);
  OLB_PRECONDITION(iX>=0 && iX<=fields.vortField.getNx()-1);
  OLB_PRECONDITION(iY>=0 && iY<=fields.vortField.getNy()-1);
  OLB_PRECONDITION(iZ>=0 && iZ<=fields.vortField.getNz()-1);

  T dyuz = boundaryYderiv(iX,iY,iZ, 2, fields.velField);
  T dzuy = boundaryZderiv(iX,iY,iZ, 1, fields.velField);

  return dyuz - dzuy;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::boundaryVorticityY (
  int iX, int iY, int iZ) const
{
  OLB_PRECONDITION(flags.velFieldComputed);
  OLB_PRECONDITION(iX>=0 && iX<=fields.vortField.getNx()-1);
  OLB_PRECONDITION(iY>=0 && iY<=fields.vortField.getNy()-1);
  OLB_PRECONDITION(iZ>=0 && iZ<=fields.vortField.getNz()-1);

  T dzux = boundaryZderiv(iX,iY,iZ, 0, fields.velField);
  T dxuz = boundaryXderiv(iX,iY,iZ, 2, fields.velField);

  return dzux - dxuz;
}

template<typename T, template<typename U> class Lattice>
T DataAnalysis3D<T,Lattice>::boundaryVorticityZ (
  int iX, int iY, int iZ) const
{
  OLB_PRECONDITION(flags.velFieldComputed);
  OLB_PRECONDITION(iX>=0 && iX<=fields.vortField.getNx()-1);
  OLB_PRECONDITION(iY>=0 && iY<=fields.vortField.getNy()-1);
  OLB_PRECONDITION(iZ>=0 && iZ<=fields.vortField.getNz()-1);

  T dxuy = boundaryXderiv(iX,iY,iZ, 1, fields.velField);
  T dyux = boundaryYderiv(iX,iY,iZ, 0, fields.velField);

  return dxuy - dyux;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis3D<T,Lattice>::computeVorticityField() const {
  if (flags.vortFieldComputed) return;
  fields.vortField.construct();
  computeVelocityField();

  int nx = fields.vortField.getNx();
  int ny = fields.vortField.getNy();
  int nz = fields.vortField.getNz();

  for (int iX=1; iX<nx-1; ++iX) {
    for (int iY=1; iY<ny-1; ++iY) {
      for (int iZ=1; iZ<nz-1; ++iZ) {
        fields.vortField.get(iX,iY,iZ)[0] = bulkVorticityX(iX,iY,iZ);
        fields.vortField.get(iX,iY,iZ)[1] = bulkVorticityY(iX,iY,iZ);
        fields.vortField.get(iX,iY,iZ)[2] = bulkVorticityZ(iX,iY,iZ);
      }
    }
  }

  for (int iX=0; iX<nx-1; ++iX) {
    for (int iY=0; iY<ny-1; ++iY) {
      fields.vortField.get(iX,iY,0)[0] = boundaryVorticityX(iX,iY,0);
      fields.vortField.get(iX,iY,0)[1] = boundaryVorticityY(iX,iY,0);
      fields.vortField.get(iX,iY,0)[2] = boundaryVorticityZ(iX,iY,0);
      fields.vortField.get(iX,iY,nz-1)[0] = boundaryVorticityX(iX,iY,nz-1);
      fields.vortField.get(iX,iY,nz-1)[1] = boundaryVorticityY(iX,iY,nz-1);
      fields.vortField.get(iX,iY,nz-1)[2] = boundaryVorticityZ(iX,iY,nz-1);
    }
  }

  for (int iX=0; iX<nx-1; ++iX) {
    for (int iZ=0; iZ<nz-1; ++iZ) {
      fields.vortField.get(iX,0,iZ)[0] = boundaryVorticityX(iX,0,iZ);
      fields.vortField.get(iX,0,iZ)[1] = boundaryVorticityY(iX,0,iZ);
      fields.vortField.get(iX,0,iZ)[2] = boundaryVorticityZ(iX,0,iZ);
      fields.vortField.get(iX,ny-1,iZ)[0] = boundaryVorticityX(iX,ny-1,iZ);
      fields.vortField.get(iX,ny-1,iZ)[1] = boundaryVorticityY(iX,ny-1,iZ);
      fields.vortField.get(iX,ny-1,iZ)[2] = boundaryVorticityZ(iX,ny-1,iZ);
    }
  }

  for (int iY=0; iY<ny-1; ++iY) {
    for (int iZ=0; iZ<nz-1; ++iZ) {
      fields.vortField.get(0,iY,iZ)[0] = boundaryVorticityX(0,iY,iZ);
      fields.vortField.get(0,iY,iZ)[1] = boundaryVorticityY(0,iY,iZ);
      fields.vortField.get(0,iY,iZ)[2] = boundaryVorticityZ(0,iY,iZ);
      fields.vortField.get(nx-1,iY,iZ)[0] = boundaryVorticityX(nx-1,iY,iZ);
      fields.vortField.get(nx-1,iY,iZ)[1] = boundaryVorticityY(nx-1,iY,iZ);
      fields.vortField.get(nx-1,iY,iZ)[2] = boundaryVorticityZ(nx-1,iY,iZ);
    }
  }

  flags.vortFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis3D<T,Lattice>::computeStrainRateField() const {
  if (flags.strainRateFieldComputed) return;
  fields.strainRateField.construct();
  computeMomentumField();

  int nx = fields.vortField.getNx();
  int ny = fields.vortField.getNy();
  int nz = fields.vortField.getNz();

  int iPi = 0;
  for (int iAlpha=0; iAlpha<3; ++iAlpha) {
    for (int iBeta=iAlpha; iBeta<3; ++iBeta) {

      for (int iX=1; iX<nx-1; ++iX) {
        for (int iY=1; iY<ny-1; ++iY) {
          for (int iZ=1; iZ<nz-1; ++iZ) {
            fields.strainRateField.get(iX,iY,iZ)[iPi] =
              bulkStrain(iX,iY,iZ, iAlpha,iBeta);
          }
        }
      }

      for (int iX=0; iX<nx; ++iX) {
        for (int iY=0; iY<ny; ++iY) {
          fields.strainRateField.get(iX,iY,0)[iPi] =
            boundaryStrain(iX,iY,0, iAlpha,iBeta);
          fields.strainRateField.get(iX,iY,nz-1)[iPi] =
            boundaryStrain(iX,iY,nz-1, iAlpha,iBeta);
        }
      }

      for (int iX=0; iX<nx; ++iX) {
        for (int iZ=0; iZ<nz; ++iZ) {
          fields.strainRateField.get(iX,0,iZ)[iPi] =
            boundaryStrain(iX,0,iZ, iAlpha,iBeta);
          fields.strainRateField.get(iX,ny-1,iZ)[iPi] =
            boundaryStrain(iX,ny-1,iZ, iAlpha,iBeta);
        }
      }

      for (int iY=0; iY<ny; ++iY) {
        for (int iZ=0; iZ<nz; ++iZ) {
          fields.strainRateField.get(0,iY,iZ)[iPi] =
            boundaryStrain(0,iY,iZ, iAlpha,iBeta);
          fields.strainRateField.get(nx-1,iY,iZ)[iPi] =
            boundaryStrain(nx-1,iY,iZ, iAlpha,iBeta);
        }
      }

      ++iPi;
    }
  }

  flags.strainRateFieldComputed = true;
}




template<typename T, template<typename U> class Lattice>
void DataAnalysis3D<T,Lattice>::computeStrainRateFieldFromStress() const {
  if (flags.stressFieldComputed) return;
  fields.stressField.construct();

  for (int iX=0; iX<fields.velField.getNx(); ++iX) {
    for (int iY=0; iY<fields.velField.getNy(); ++iY) {
      for (int iZ=0; iZ<fields.velField.getNz(); ++iZ) {
        block.get(iX,iY,iZ).computeStress(fields.stressField.get(iX,iY,iZ));
        T omega = block.get(iX,iY,iZ).getDynamics()->getOmega();
        for (int iPi=0; iPi<6; ++iPi) {
          fields.stressField.get(iX,iY,iZ)[iPi] *= -omega / (T)2 * Lattice<T>::invCs2;
        }
      }
    }
  }

  flags.stressFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis3D<T,Lattice>::computeDivRhoUField() const {
  if (flags.divRhoUFieldComputed) return;
  fields.divRhoUField.construct();
  computeMomentumField();

  int nx = fields.divRhoUField.getNx();
  int ny = fields.divRhoUField.getNy();
  int nz = fields.divRhoUField.getNz();

  for (int iX=1; iX<nx-1; ++iX) {
    for (int iY=1; iY<ny-1; ++iY) {
      for (int iZ=1; iZ<nz-1; ++iZ) {
        fields.divRhoUField.get(iX,iY,iZ) = bulkDivRhoU(iX,iY,iZ);
      }
    }
  }

  for (int iX=0; iX<nx-1; ++iX) {
    for (int iY=0; iY<ny-1; ++iY) {
      fields.divRhoUField.get(iX,iY,0) = boundaryDivRhoU(iX,iY,0);
      fields.divRhoUField.get(iX,iY,nz-1) = boundaryDivRhoU(iX,iY,nz-1);
    }
  }

  for (int iX=0; iX<nx-1; ++iX) {
    for (int iZ=0; iZ<nz-1; ++iZ) {
      fields.divRhoUField.get(iX,0,iZ) = boundaryDivRhoU(iX,0,iZ);
      fields.divRhoUField.get(iX,ny-1,iZ) = boundaryDivRhoU(iX,ny-1,iZ);
    }
  }

  for (int iY=0; iY<ny-1; ++iY) {
    for (int iZ=0; iZ<nz-1; ++iZ) {
      fields.divRhoUField.get(0,iY,iZ) = boundaryDivRhoU(0,iY,iZ);
      fields.divRhoUField.get(nx-1,iY,iZ) = boundaryDivRhoU(nx-1,iY,iZ);
    }
  }

  flags.divRhoUFieldComputed = true;
}


template<typename T, template<typename U> class Lattice>
void DataAnalysis3D<T,Lattice>::computePoissonTerm() const {
  if (flags.poissonFieldComputed) return;
  fields.poissonField.construct();
  computeVelocityField();

  int nx = fields.poissonField.getNx();
  int ny = fields.poissonField.getNy();
  int nz = fields.poissonField.getNz();

  for (int iX=1; iX<nx-1; ++iX) {
    for (int iY=1; iY<ny-1; ++iY) {
      for (int iZ=1; iZ<nz-1; ++iZ) {
        fields.poissonField.get(iX,iY,iZ) = bulkPoisson(iX,iY,iZ);
      }
    }
  }

  for (int iX=0; iX<nx-1; ++iX) {
    for (int iY=0; iY<ny-1; ++iY) {
      fields.poissonField.get(iX,iY,0) = boundaryPoisson(iX,iY,0);
      fields.poissonField.get(iX,iY,nz-1) = boundaryPoisson(iX,iY,nz-1);
    }
  }

  for (int iX=0; iX<nx-1; ++iX) {
    for (int iZ=0; iZ<nz-1; ++iZ) {
      fields.poissonField.get(iX,0,iZ) = boundaryPoisson(iX,0,iZ);
      fields.poissonField.get(iX,ny-1,iZ) = boundaryPoisson(iX,ny-1,iZ);
    }
  }

  for (int iY=0; iY<ny-1; ++iY) {
    for (int iZ=0; iZ<nz-1; ++iZ) {
      fields.poissonField.get(0,iY,iZ) = boundaryPoisson(0,iY,iZ);
      fields.poissonField.get(nx-1,iY,iZ) = boundaryPoisson(nx-1,iY,iZ);
    }
  }

  flags.poissonFieldComputed = true;
}

template<typename T, template<typename U> class Lattice>
void DataAnalysis3D<T,Lattice>::computePopulations() const {
  if (flags.populationFieldComputed) return;
  fields.populationField.construct();

  int nx = fields.populationField.getNx();
  int ny = fields.populationField.getNy();
  int nz = fields.populationField.getNz();

  for (int iX=0; iX<nx; ++iX) {
    for (int iY=0; iY<ny; ++iY) {
      for (int iZ=0; iZ<nz; ++iZ) {
        for (int iPop=0; iPop<Lattice<T>::q; ++iPop) {
          fields.populationField.get(iX,iY,iZ)[iPop] = block.get(iX,iY,iZ)[iPop];
        }
      }
    }
  }

  flags.populationFieldComputed = true;
}

}  // namespace olb


#endif
