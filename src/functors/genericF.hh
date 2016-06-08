/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012-2013 Lukas Baron, Mathias J. Krause, Albert Mink
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

#ifndef GENERIC_F_HH
#define GENERIC_F_HH


/** \file
 * The description of a generic interface for all functor classes 
 * -- generic implementation.
 */

#include"genericF.h"
#include<vector>    // for generic i/o
#include<cmath>     // for lpnorm

namespace olb {

template <typename T, typename S>
const int GenericF<T,S>::getSourceDim() const {
  return m;
}

template <typename T, typename S>
const int GenericF<T,S>::getTargetDim() const {
  return n;
}

template <typename T, typename S>
std::vector<T> GenericF<T,S>::operator() () {
  std::vector<S> v;
  return operator()(v);
}

template <typename T, typename S>
std::vector<T> GenericF<T,S>::operator() (S input0) {
  std::vector<S> v;
  v.push_back(input0); 
  return operator()(v);
}

template <typename T, typename S>
std::vector<T> GenericF<T,S>::operator() (S input0, S input1) {
  std::vector<S> v;
  v.push_back(input0); v.push_back(input1);
  return operator()(v);
}

template <typename T, typename S>
std::vector<T> GenericF<T,S>::operator() (S input0, S input1, S input2) {
  std::vector<S> v;
  v.push_back(input0); v.push_back(input1); v.push_back(input2);
  return operator()(v);
}

template <typename T, typename S>
std::vector<T> GenericF<T,S>::operator() (S input0, S input1, S input2, S input3) {
  std::vector<S> v;
  v.push_back(input0); v.push_back(input1); v.push_back(input2); v.push_back(input3);
  return operator()(v);
}
 
template <typename T, typename S>
void GenericF<T,S>::myErase(GenericF<T,S>* ptr) {
  unsigned i;
  for(i = 0; i < this->pointerVec.size(); i++ ) {
    if( this->pointerVec[i] == ptr ) {
      delete this->pointerVec[i];
      // jump out of for-loop
      break;
    }
  }
  // delete vector entry
  this->pointerVec.erase( this->pointerVec.begin() + i);
}

} // end namespace olb

#endif
