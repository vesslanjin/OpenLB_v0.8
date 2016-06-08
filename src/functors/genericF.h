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

/** \file
 * The description of a generic interface for all functor classes 
 * -- header file.
 */


#ifndef GENERIC_F_H
#define GENERIC_F_H

#include<vector>    // for generic i/o
#include<cmath>     // for lpnorm

/** Note: Throughout the whole source code directory genericFunctions, the
 *  template parameters for i/o dimensions are:
 *           F: S^m -> T^n  (S=source, T=target)
 */

namespace olb {

////////////////////////////////////////////////////////////////////////////////
// first level classes

/// generic functions that can represent continuous as well as discrete
/// functions
template <typename T, typename S>
class GenericF {

protected:
  int m;             // source dimension, -1 means generic/undefined
  int n;             // target dimension
  std::vector< GenericF<T,S>* > pointerVec;

public:
  GenericF(int targetDim, int sourceDim) : m(sourceDim), n(targetDim) { };
  virtual ~GenericF() {};

  const int getSourceDim() const;
  const int getTargetDim() const;

  virtual std::vector<T> operator() (std::vector<S> input) = 0;
 
  std::vector<T> operator() ();
  std::vector<T> operator() (S input0);
  std::vector<T> operator() (S input0, S input1);
  std::vector<T> operator() (S input0, S input1, S input2);
  std::vector<T> operator() (S input0, S input1, S input2, S input3);

  virtual void myErase(GenericF<T,S>* ptr);
};

} // end namespace olb

#endif
