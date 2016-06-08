/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Lukas Baron, Tim Dornieden, Mathias J. Krause, Albert Mink
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

#ifndef ANALYTICAL_CALC_F_HH
#define ANALYTICAL_CALC_F_HH

#include<vector>    // for generic i/o
#include<cmath>     // for lpnorm

#include "analyticCalcF.h"
#include "functors/analyticalF.h"
#include "functors/genericF.h"


namespace olb {



//////////////////////////////// AnalyticCalc1D ////////////////////////////////
template <typename T, typename S>
AnalyticCalc1D<T,S>::AnalyticCalc1D(AnalyticalF1D<T,S>& _f, AnalyticalF1D<T,S>& _g) : AnalyticalF1D<T,S>(_f.getTargetDim()), f(_f), g(_g) { }

template <typename T, typename S>
void AnalyticCalc1D<T,S>::myErase(GenericF<T,S>* ptr) {
  for( unsigned i = 0; i < this->pointerVec.size(); i++ ) {
    if( this->pointerVec[i] == ptr ) {
      // delete object refered by pointer 
      delete this->pointerVec[i];
      // delete vector entry
      this->pointerVec.erase( this->pointerVec.begin() + i);
    }
  }
  if( this->pointerVec.size() == 0 )  f.myErase(this);
};



template <typename T, typename S>
AnalyticPlus1D<T,S>::AnalyticPlus1D(AnalyticalF1D<T,S>& _f, AnalyticalF1D<T,S>& _g) : AnalyticCalc1D<T,S>(_f,_g) { }

template <typename T, typename S>
std::vector<T> AnalyticPlus1D<T,S>::operator()(std::vector<S> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] + this->g(input)[i] );
  }
  // start deleting PlusF and GenericF objects
  if (this->pointerVec.size() == 0) this->f.myErase(this);
  return output;
}



template <typename T, typename S>
AnalyticMinus1D<T,S>::AnalyticMinus1D(AnalyticalF1D<T,S>& _f, AnalyticalF1D<T,S>& _g) : AnalyticCalc1D<T,S>(_f,_g) { }

template <typename T, typename S>
std::vector<T> AnalyticMinus1D<T,S>::operator()(std::vector<S> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] - this->g(input)[i] );
  }
  if (this->pointerVec.size() == 0)  this->f.myErase(this);
  return output;
}



template <typename T, typename S>
AnalyticMultiplication1D<T,S>::AnalyticMultiplication1D(AnalyticalF1D<T,S>& _f, AnalyticalF1D<T,S>& _g) : AnalyticCalc1D<T,S>(_f,_g) { }

template <typename T, typename S>
std::vector<T> AnalyticMultiplication1D<T,S>::operator()(std::vector<S> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] * this->g(input)[i] );
  }
  if (this->pointerVec.size() == 0) this->f.myErase(this);
  return output;
}



template <typename T, typename S>
AnalyticDivision1D<T,S>::AnalyticDivision1D(AnalyticalF1D<T,S>& _f, AnalyticalF1D<T,S>& _g) : AnalyticCalc1D<T,S>(_f,_g) { }

template <typename T, typename S>
std::vector<T> AnalyticDivision1D<T,S>::operator()(std::vector<S> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] / this->g(input)[i] );
  }
  if (this->pointerVec.size() == 0) this->f.myErase(this);
  return output;
}



template <typename T, typename S>
AnalyticalF1D<T,S>& AnalyticalF1D<T,S>::operator+(AnalyticalF1D<T,S>& rhs) {
  AnalyticalF1D<T,S>* tmp = new AnalyticPlus1D<T,S>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}

template <typename T, typename S>
AnalyticalF1D<T,S>& AnalyticalF1D<T,S>::operator-(AnalyticalF1D<T,S>& rhs) {
  AnalyticalF1D<T,S>* tmp = new AnalyticMinus1D<T,S>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}

template <typename T, typename S>
AnalyticalF1D<T,S>& AnalyticalF1D<T,S>::operator*(AnalyticalF1D<T,S>& rhs) {
  AnalyticalF1D<T,S>* tmp = new AnalyticMultiplication1D<T,S>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}

template <typename T, typename S>
AnalyticalF1D<T,S>& AnalyticalF1D<T,S>::operator/(AnalyticalF1D<T,S>& rhs) {
  AnalyticalF1D<T,S>* tmp = new AnalyticDivision1D<T,S>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}




//////////////////////////////// AnalyticCalc2D ////////////////////////////////

template <typename T, typename S>
AnalyticCalc2D<T,S>::AnalyticCalc2D(AnalyticalF2D<T,S>& _f, AnalyticalF2D<T,S>& _g) : AnalyticalF2D<T,S>(_f.getTargetDim()), f(_f), g(_g) { }

template <typename T, typename S>
void AnalyticCalc2D<T,S>::myErase(GenericF<T,S>* ptr) {
  for( unsigned i = 0; i < this->pointerVec.size(); i++ ) {
    if( this->pointerVec[i] == ptr ) {
      // delete object refered by pointer 
      delete this->pointerVec[i];
      // delete vector entry
      this->pointerVec.erase( this->pointerVec.begin() + i);
    }
  }
  if( this->pointerVec.size() == 0 ) f.myErase(this);
};



template <typename T, typename S>
AnalyticPlus2D<T,S>::AnalyticPlus2D(AnalyticalF2D<T,S>& _f, AnalyticalF2D<T,S>& _g) : AnalyticCalc2D<T,S>(_f,_g) { }

template <typename T, typename S>
std::vector<T> AnalyticPlus2D<T,S>::operator()(std::vector<S> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] + this->g(input)[i] );
  }
  if (this->pointerVec.size() == 0) this->f.myErase(this);
  return output;
}



template <typename T, typename S>
AnalyticMinus2D<T,S>::AnalyticMinus2D(AnalyticalF2D<T,S>& _f, AnalyticalF2D<T,S>& _g) : AnalyticCalc2D<T,S>(_f,_g) { }

template <typename T, typename S>
std::vector<T> AnalyticMinus2D<T,S>::operator()(std::vector<S> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] - this->g(input)[i] );
  }
  if (this->pointerVec.size() == 0) this->f.myErase(this);
  return output;
}



template <typename T, typename S>
AnalyticMultiplication2D<T,S>::AnalyticMultiplication2D(AnalyticalF2D<T,S>& _f, AnalyticalF2D<T,S>& _g) : AnalyticCalc2D<T,S>(_f,_g) { }

template <typename T, typename S>
std::vector<T> AnalyticMultiplication2D<T,S>::operator()(std::vector<S> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] * this->g(input)[i] );
  }
  if (this->pointerVec.size() == 0) this->f.myErase(this);
  return output;
}



template <typename T, typename S>
AnalyticDivision2D<T,S>::AnalyticDivision2D(AnalyticalF2D<T,S>& _f, AnalyticalF2D<T,S>& _g) : AnalyticCalc2D<T,S>(_f,_g) { }

template <typename T, typename S>
std::vector<T> AnalyticDivision2D<T,S>::operator()(std::vector<S> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] / this->g(input)[i] );
  }
  if (this->pointerVec.size() == 0) this->f.myErase(this);
  return output;
}



template <typename T, typename S>
AnalyticalF2D<T,S>& AnalyticalF2D<T,S>::operator+(AnalyticalF2D<T,S>& rhs) {
  AnalyticalF2D<T,S>* tmp = new AnalyticPlus2D<T,S>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}

template <typename T, typename S>
AnalyticalF2D<T,S>& AnalyticalF2D<T,S>::operator-(AnalyticalF2D<T,S>& rhs) {
  AnalyticalF2D<T,S>* tmp = new AnalyticMinus2D<T,S>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}

template <typename T, typename S>
AnalyticalF2D<T,S>& AnalyticalF2D<T,S>::operator*(AnalyticalF2D<T,S>& rhs) {
  AnalyticalF2D<T,S>* tmp = new AnalyticMultiplication2D<T,S>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}

template <typename T, typename S>
AnalyticalF2D<T,S>& AnalyticalF2D<T,S>::operator/(AnalyticalF2D<T,S>& rhs) {
  AnalyticalF2D<T,S>* tmp = new AnalyticDivision2D<T,S>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}



//////////////////////////////// AnalyticCalc3D ////////////////////////////////

template <typename T, typename S>
AnalyticCalc3D<T,S>::AnalyticCalc3D(AnalyticalF3D<T,S>& _f, AnalyticalF3D<T,S>& _g) : AnalyticalF3D<T,S>(_f.getTargetDim()), f(_f), g(_g) { }

template <typename T, typename S>
void AnalyticCalc3D<T,S>::myErase(GenericF<T,S>* ptr) {
  for( unsigned i = 0; i < this->pointerVec.size(); i++ ) {
    if( this->pointerVec[i] == ptr ) {
      // delete object refered by pointer 
      delete this->pointerVec[i];
      // delete vector entry
      this->pointerVec.erase( this->pointerVec.begin() + i);
    }
  }
  if( this->pointerVec.size() == 0 )  f.myErase(this);
};



template <typename T, typename S>
AnalyticPlus3D<T,S>::AnalyticPlus3D(AnalyticalF3D<T,S>& _f, AnalyticalF3D<T,S>& _g) : AnalyticCalc3D<T,S>(_f,_g) { }

template <typename T, typename S>
std::vector<T> AnalyticPlus3D<T,S>::operator()(std::vector<S> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] + this->g(input)[i] );
  }
  if (this->pointerVec.size() == 0) this->f.myErase(this);
  return output;
}



template <typename T, typename S>
AnalyticMinus3D<T,S>::AnalyticMinus3D(AnalyticalF3D<T,S>& _f, AnalyticalF3D<T,S>& _g) : AnalyticCalc3D<T,S>(_f,_g) { }

template <typename T, typename S>
std::vector<T> AnalyticMinus3D<T,S>::operator()(std::vector<S> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] - this->g(input)[i] );
  }
  if (this->pointerVec.size() == 0) this->f.myErase(this);
  return output;
}



template <typename T, typename S>
AnalyticMultiplication3D<T,S>::AnalyticMultiplication3D(AnalyticalF3D<T,S>& _f, AnalyticalF3D<T,S>& _g) : AnalyticCalc3D<T,S>(_f,_g) { }

template <typename T, typename S>
std::vector<T> AnalyticMultiplication3D<T,S>::operator()(std::vector<S> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] * this->g(input)[i] );
  }
  if (this->pointerVec.size() == 0) this->f.myErase(this);
  return output;
}



template <typename T, typename S>
AnalyticDivision3D<T,S>::AnalyticDivision3D(AnalyticalF3D<T,S>& _f, AnalyticalF3D<T,S>& _g) : AnalyticCalc3D<T,S>(_f,_g) { }

template <typename T, typename S>
std::vector<T> AnalyticDivision3D<T,S>::operator()(std::vector<S> input) {
  std::vector<T> output;
  for(int i = 0; i < this->f.getTargetDim(); i++) {
    output.push_back( this->f(input)[i] / this->g(input)[i] );
  }
  if (this->pointerVec.size() == 0) this->f.myErase(this);
  return output;
}



template <typename T, typename S>
AnalyticalF3D<T,S>& AnalyticalF3D<T,S>::operator/(AnalyticalF3D<T,S>& rhs) {
  AnalyticalF3D<T,S>* tmp = new AnalyticDivision3D<T,S>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}
template <typename T, typename S>
AnalyticalF3D<T,S>& AnalyticalF3D<T,S>::operator*(AnalyticalF3D<T,S>& rhs) {
  AnalyticalF3D<T,S>* tmp = new AnalyticMultiplication3D<T,S>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}

template <typename T, typename S>
AnalyticalF3D<T,S>& AnalyticalF3D<T,S>::operator-(AnalyticalF3D<T,S>& rhs) {
  AnalyticalF3D<T,S>* tmp = new AnalyticMinus3D<T,S>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}

template <typename T, typename S>
AnalyticalF3D<T,S>& AnalyticalF3D<T,S>::operator+(AnalyticalF3D<T,S>& rhs) {
  AnalyticalF3D<T,S>* tmp = new AnalyticPlus3D<T,S>(*this,rhs);
  this->pointerVec.push_back(tmp);
  return *tmp;
}


} // end namespace olb

#endif
