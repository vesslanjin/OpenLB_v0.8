/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Bernd Stahl
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
 * Base class for data analysis on 3D BlockStructures -- header file.
 */

#ifndef DATA_ANALYSIS_BASE_3D_H
#define DATA_ANALYSIS_BASE_3D_H

#include "dataFieldBase3D.h"

namespace olb {

/// Interface for the variants of 3D data analysis classes.
template<typename T, template<typename U> class Lattice>
class DataAnalysisBase3D {
public:
  virtual ~DataAnalysisBase3D() { }
public:
  virtual void reset() const =0;

  virtual TensorFieldBase3D<T,3> const& getVelocity() const =0;
  virtual TensorFieldBase3D<T,3> const& getMomentum() const =0;
  virtual ScalarFieldBase3D<T> const& getPressure() const =0;
  virtual TensorFieldBase3D<T,3> const& getVorticity() const =0;
  virtual ScalarFieldBase3D<T> const& getVelocityNorm() const =0;
  virtual ScalarFieldBase3D<T> const& getVorticityNorm() const=0;
  virtual ScalarFieldBase3D<T> const& getQCrit() const =0;
  // Compute strain rate using finite differences
  virtual TensorFieldBase3D<T,6> const& getStrainRate() const =0;
  // Compute strain rate from the stress (using the local particle populations)
  virtual TensorFieldBase3D<T,6> const& getStrainRateFromStress() const =0;
  virtual ScalarFieldBase3D<T> const& getDivRhoU() const =0;
  virtual ScalarFieldBase3D<T> const& getPoissonTerm() const =0;
  virtual TensorFieldBase3D<T,Lattice<T>::q > const& getPopulations() const =0;

  virtual T computeMeanEnstrophy() const =0;

  virtual int getNx() const =0;
  virtual int getNy() const =0;
  virtual int getNz() const =0;
};


}  // namespace olb;

#endif
