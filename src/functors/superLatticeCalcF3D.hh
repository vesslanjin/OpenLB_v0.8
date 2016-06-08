/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Lukas Baron, Tim Dornieden, Mathias J. Krause,
 *  Albert Mink
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
#ifndef SUPER_LATTICE_F_3D_HH
#define SUPER_LATTICE_F_3D_HH

#include<vector>    // for generic i/o
#include<cmath>     // for lpnorm
#include<string>     // for lpnorm

#include "superLatticeCalcF3D.h"
#include "functors/genericF.h"
#include "functors/analyticalF.h"




namespace olb {



////////////////////////////// SuperLatticeCalc3D //////////////////////////////

template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeCalc3D<T,DESCRIPTOR>::SuperLatticeCalc3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperLatticeF3D<T,DESCRIPTOR>& _g)
  : SuperLatticeF3D<T,DESCRIPTOR>( _f.getSuperLattice3D(), _f.getTargetDim() ), f(_f), g(_g) { }

template <typename T, template <typename U> class DESCRIPTOR>
void SuperLatticeCalc3D<T,DESCRIPTOR>::myErase(GenericF<T,int>* ptr) {
  for ( int i = 0; i < this->pointerVec.size(); i++ ) {
    if ( this->pointerVec[i] == ptr ) {
      // delete object refered by pointer
      delete this->pointerVec[i];
      // delete vector entry
      this->pointerVec.erase( this->pointerVec.begin() + i);
    }
  }
}


// addition
template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticePlus3D<T,DESCRIPTOR>::SuperLatticePlus3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperLatticeF3D<T,DESCRIPTOR>& _g)
: SuperLatticeCalc3D<T,DESCRIPTOR>(_f,_g) { }

template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticePlus3D<T,DESCRIPTOR>::operator()(std::vector<int> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] + this->g(input)[i] );
  }
  // start deleting MinusF and GernericF objects
//    if (this->pointerVec.size() == 0)  this->f.myErase(this);
  return output;
}

// subtraction
template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeMinus3D<T,DESCRIPTOR>::SuperLatticeMinus3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperLatticeF3D<T,DESCRIPTOR>& _g)
: SuperLatticeCalc3D<T,DESCRIPTOR>(_f,_g) { }

template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticeMinus3D<T,DESCRIPTOR>::operator()(std::vector<int> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] - this->g(input)[i] );
  }
  // start deleting MinusF and GernericF objects
//    if (this->pointerVec.size() == 0)  this->f.myErase(this);
  return output;
}


// multiplication
template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeMultiplication3D<T,DESCRIPTOR>::SuperLatticeMultiplication3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperLatticeF3D<T,DESCRIPTOR>& _g)
: SuperLatticeCalc3D<T,DESCRIPTOR>(_f,_g) { }

template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticeMultiplication3D<T,DESCRIPTOR>::operator()(std::vector<int> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] * this->g(input)[i] );
  }
  // start deleting MinusF and GernericF objects
//    if (this->pointerVec.size() == 0)  this->f.myErase(this);
  return output;
}


// division
template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeDivision3D<T,DESCRIPTOR>::SuperLatticeDivision3D(SuperLatticeF3D<T,DESCRIPTOR>& _f, SuperLatticeF3D<T,DESCRIPTOR>& _g)
: SuperLatticeCalc3D<T,DESCRIPTOR>(_f,_g) { }

template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> SuperLatticeDivision3D<T,DESCRIPTOR>::operator()(std::vector<int> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] / this->g(input)[i] );
  }
  // start deleting MinusF and GernericF objects
//    if (this->pointerVec.size() == 0)  this->f.myErase(this);
  return output;
}


// operators definitions

template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeF3D<T,DESCRIPTOR>& SuperLatticeF3D<T,DESCRIPTOR>::operator+(SuperLatticeF3D<T,DESCRIPTOR>& rhs)
{
  SuperLatticeF3D<T,DESCRIPTOR>* tmp = new SuperLatticePlus3D<T,DESCRIPTOR>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}

template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeF3D<T,DESCRIPTOR>& SuperLatticeF3D<T,DESCRIPTOR>::operator-(SuperLatticeF3D<T,DESCRIPTOR>& rhs)
{
  SuperLatticeF3D<T,DESCRIPTOR>* tmp = new SuperLatticeMinus3D<T,DESCRIPTOR>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}

template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeF3D<T,DESCRIPTOR>& SuperLatticeF3D<T,DESCRIPTOR>::operator*(SuperLatticeF3D<T,DESCRIPTOR>& rhs)
{
  SuperLatticeF3D<T,DESCRIPTOR>* tmp = new SuperLatticeMultiplication3D<T,DESCRIPTOR>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}

template <typename T, template <typename U> class DESCRIPTOR>
SuperLatticeF3D<T,DESCRIPTOR>& SuperLatticeF3D<T,DESCRIPTOR>::operator/(SuperLatticeF3D<T,DESCRIPTOR>& rhs)
{
  SuperLatticeF3D<T,DESCRIPTOR>* tmp = new SuperLatticeDivision3D<T,DESCRIPTOR>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}



} // end namespace olb

#endif
