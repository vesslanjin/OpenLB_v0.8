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

#ifndef MULTI_DATA_ANALYSIS_2D_HH
#define MULTI_DATA_ANALYSIS_2D_HH

#include "multiDataAnalysis2D.h"
#include "core/olbDebug.h"

namespace olb {

/////// Struct MultiAnalysisFieldsImpl2D  ///////////////////////

template<typename T, template<typename U> class Lattice>
MultiAnalysisFieldsImpl2D<T,Lattice>::MultiAnalysisFieldsImpl2D (
  MultiDataDistribution2D const& distribution )
  : velField(distribution),
    momentumField(distribution),
    pressureField(distribution),
    velNormField(distribution),
    vortField(distribution),
    strainRateField(distribution),
    stressField(distribution),
    divRhoUField(distribution),
    poissonField(distribution),
    populationField(distribution)
{ }


/////// Class MultiDataAnalysis2D  /////////////////////////////

template<typename T, template<typename U> class Lattice>
MultiDataAnalysis2D<T,Lattice>::MultiDataAnalysis2D(MultiBlockLattice2D<T,Lattice> const& block_)
  : block(block_),
    fields(block.getMultiData())
{
  perBlockAnalysis.resize(block.getMultiData().getNumBlocks());
  for (unsigned iBlock=0; iBlock<perBlockAnalysis.size(); ++iBlock) {
    if (block.getBlockLattices()[iBlock]) {
      AnalysisFields2D<T,Lattice> newField (
        *fields.velField.getTensorFields()[iBlock],
        *fields.momentumField.getTensorFields()[iBlock],
        *fields.pressureField.getScalarFields()[iBlock],
        *fields.velNormField.getScalarFields()[iBlock],
        *fields.vortField.getScalarFields()[iBlock],
        *fields.strainRateField.getTensorFields()[iBlock],
        *fields.stressField.getTensorFields()[iBlock],
        *fields.divRhoUField.getScalarFields()[iBlock],
        *fields.poissonField.getScalarFields()[iBlock],
        *fields.populationField.getTensorFields()[iBlock] );
      perBlockAnalysis[iBlock] = new DataAnalysis2D<T,Lattice> (
        *block.getBlockLattices()[iBlock], newField );
    }
    else {
      perBlockAnalysis[iBlock] = 0;
    }
  }
}

template<typename T, template<typename U> class Lattice>
MultiDataAnalysis2D<T,Lattice>::~MultiDataAnalysis2D() {
  for (unsigned iBlock=0; iBlock<perBlockAnalysis.size(); ++iBlock) {
    delete perBlockAnalysis[iBlock];
  }
}

template<typename T, template<typename U> class Lattice>
void MultiDataAnalysis2D<T,Lattice>::reset() const {
  for (unsigned iBlock=0; iBlock<perBlockAnalysis.size(); ++iBlock) {
    if (perBlockAnalysis[iBlock]) {
      perBlockAnalysis[iBlock] -> reset();
    }
  }
}

template<typename T, template<typename U> class Lattice>
TensorFieldBase2D<T,2> const& MultiDataAnalysis2D<T,Lattice>::getVelocity() const {
  fields.velField.construct();
  for (unsigned iBlock=0; iBlock<perBlockAnalysis.size(); ++iBlock) {
    if (perBlockAnalysis[iBlock]) {
      perBlockAnalysis[iBlock] -> getVelocity();
    }
  }
  return fields.velField;
}

template<typename T, template<typename U> class Lattice>
TensorFieldBase2D<T,2> const& MultiDataAnalysis2D<T,Lattice>::getMomentum() const {
  fields.momentumField.construct();
  for (unsigned iBlock=0; iBlock<perBlockAnalysis.size(); ++iBlock) {
    if (perBlockAnalysis[iBlock]) {
      perBlockAnalysis[iBlock] -> getMomentum();
    }
  }
  return fields.momentumField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase2D<T> const& MultiDataAnalysis2D<T,Lattice>::getPressure() const {
  fields.pressureField.construct();
  for (unsigned iBlock=0; iBlock<perBlockAnalysis.size(); ++iBlock) {
    if (perBlockAnalysis[iBlock]) {
      perBlockAnalysis[iBlock] -> getPressure();
    }
  }
  return fields.pressureField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase2D<T> const& MultiDataAnalysis2D<T,Lattice>::getVelocityNorm() const {
  fields.velNormField.construct();
  for (unsigned iBlock=0; iBlock<perBlockAnalysis.size(); ++iBlock) {
    if (perBlockAnalysis[iBlock]) {
      perBlockAnalysis[iBlock] -> getVelocityNorm();
    }
  }
  return fields.velNormField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase2D<T> const& MultiDataAnalysis2D<T,Lattice>::getVorticity() const {
  fields.vortField.construct();
  for (unsigned iBlock=0; iBlock<perBlockAnalysis.size(); ++iBlock) {
    if (perBlockAnalysis[iBlock]) {
      perBlockAnalysis[iBlock] -> getVorticity();
    }
  }
  return fields.vortField;
}

template<typename T, template<typename U> class Lattice>
TensorFieldBase2D<T,3> const& MultiDataAnalysis2D<T,Lattice>::getStrainRate() const {
  fields.strainRateField.construct();
  for (unsigned iBlock=0; iBlock<perBlockAnalysis.size(); ++iBlock) {
    if (perBlockAnalysis[iBlock]) {
      perBlockAnalysis[iBlock] -> getStrainRate();
    }
  }
  return fields.strainRateField;
}

template<typename T, template<typename U> class Lattice>
TensorFieldBase2D<T,3> const& MultiDataAnalysis2D<T,Lattice>::getStrainRateFromStress() const {
  fields.stressField.construct();
  for (unsigned iBlock=0; iBlock<perBlockAnalysis.size(); ++iBlock) {
    if (perBlockAnalysis[iBlock]) {
      perBlockAnalysis[iBlock] -> getStrainRateFromStress();
    }
  }
  return fields.stressField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase2D<T> const& MultiDataAnalysis2D<T,Lattice>::getDivRhoU() const {
  fields.divRhoUField.construct();
  for (unsigned iBlock=0; iBlock<perBlockAnalysis.size(); ++iBlock) {
    if (perBlockAnalysis[iBlock]) {
      perBlockAnalysis[iBlock] -> getDivRhoU();
    }
  }
  return fields.divRhoUField;
}

template<typename T, template<typename U> class Lattice>
ScalarFieldBase2D<T> const& MultiDataAnalysis2D<T,Lattice>::getPoissonTerm() const {
  fields.poissonField.construct();
  for (unsigned iBlock=0; iBlock<perBlockAnalysis.size(); ++iBlock) {
    if (perBlockAnalysis[iBlock]) {
      perBlockAnalysis[iBlock] -> getPoissonTerm();
    }
  }
  return fields.poissonField;
}

template<typename T, template<typename U> class Lattice>
TensorFieldBase2D<T, Lattice<T>::q > const& MultiDataAnalysis2D<T,Lattice>::getPopulations() const {
  fields.populationField.construct();
  for (unsigned iBlock=0; iBlock<perBlockAnalysis.size(); ++iBlock) {
    if (perBlockAnalysis[iBlock]) {
      perBlockAnalysis[iBlock] -> getPopulations();
    }
  }
  return fields.populationField;
}

template<typename T, template<typename U> class Lattice>
T MultiDataAnalysis2D<T,Lattice>::computeMeanEnstrophy() const {
  OLB_ASSERT( false, "This method is not yet implemented" );
  return T();
}

template<typename T, template<typename U> class Lattice>
T MultiDataAnalysis2D<T,Lattice>::computeMeanEnstrophy2() const {
  OLB_ASSERT( false, "This method is not yet implemented" );
  return T();
}

template<typename T, template<typename U> class Lattice>
MultiDataAnalysis2D<T,Lattice>::MultiDataAnalysis2D(MultiDataAnalysis2D<T,Lattice> const& rhs)
  : block(rhs.block),
    perBlockAnalysis(rhs.perBlockAnalysis),
    fields(rhs.fields)
{ }

}  // namespace olb


#endif
