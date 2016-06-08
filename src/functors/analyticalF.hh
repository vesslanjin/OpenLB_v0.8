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

#ifndef ANALYTICAL_F_HH
#define ANALYTICAL_F_HH

#include<vector>    // for generic i/o
#include<cmath>     // for lpnorm

#include "analyticalF.h"
#include "functors/genericF.h"
#include "io/ostreamManager.h"

namespace olb {



template <typename T, typename S>
ComposedAnalyticalF3D<T,S>::ComposedAnalyticalF3D(AnalyticalF3D<T,S>& f0, AnalyticalF3D<T,S>& f1, AnalyticalF3D<T,S>& f2) : AnalyticalF3D<T,S>(3), _f0(f0), _f1(f1), _f2(f2) { }


template <typename T, typename S>
std::vector<T> ComposedAnalyticalF3D<T,S>::operator()(std::vector<S> x) {
  std::vector<T> y;
  y.push_back(_f0(x)[0]);
  y.push_back(_f1(x)[0]);
  y.push_back(_f2(x)[0]);
  return y;
}



template <typename T, typename S>
ConstAnalyticalF1D<T,S>::ConstAnalyticalF1D(T value)
: AnalyticalF1D<T,S>(1) {
  c.push_back(value);
}

template <typename T, typename S>
ConstAnalyticalF1D<T,S>::ConstAnalyticalF1D(std::vector<T>& value)
: AnalyticalF1D<T,S>(value.size()), c(value) { }

template <typename T, typename S>
std::vector<T> ConstAnalyticalF1D<T,S>::operator()(std::vector<S> x) {
  return c;
}



template <typename T, typename S>
ConstAnalyticalF2D<T,S>::ConstAnalyticalF2D(T value)
: AnalyticalF2D<T,S>(1) {
  c.push_back(value);
}

template <typename T, typename S>
ConstAnalyticalF2D<T,S>::ConstAnalyticalF2D(std::vector<T>& value)
: AnalyticalF2D<T,S>(value.size()), c(value) { }

template <typename T, typename S>
std::vector<T> ConstAnalyticalF2D<T,S>::operator()(std::vector<S> x) {
  return c;
}



template <typename T, typename S>
ConstAnalyticalF3D<T,S>::ConstAnalyticalF3D(T value)
: AnalyticalF3D<T,S>(1) { c.push_back(value); };

template <typename T, typename S>
ConstAnalyticalF3D<T,S>::ConstAnalyticalF3D(std::vector<T>& value)
  : AnalyticalF3D<T,S>(value.size()), c(value) { }

template <typename T, typename S>
std::vector<T> ConstAnalyticalF3D<T,S>::operator()(std::vector<S> x) {
  return c;
}



template <typename T, typename S>
LinearAnalyticalF1D<T,S>::LinearAnalyticalF1D(S _x0, T _v0, S _x1, T _v1) 
: AnalyticalF1D<T,S>(1), clout( std::cout,"LinearAnalyticalF1D" ) {
  if ((_x1-_x0)==0)
    clout << "Error: x1-x2=0" << std::endl;
  else {
    a = (_v1-_v0)/(_x1-_x0);
    b = _v0-_x0*a;
  }
}

template <typename T, typename S>
LinearAnalyticalF1D<T,S>::LinearAnalyticalF1D(T _a, T _b)  : AnalyticalF1D<T,S>(1), a(_a), b(_b),
  clout(std::cout,"LinearAnalyticalF1D") { }

template <typename T, typename S>
std::vector<T> LinearAnalyticalF1D<T,S>::operator()(std::vector<S> x) {
  std::vector<T> y;
  y.push_back( a*x[0] + b );
  return y;
}



template <typename T, typename S>
LinearAnalyticalF2D<T,S>::LinearAnalyticalF2D(S _x0, S _y0, T _v0, S _x1, S _y1, T _v1, S _x2, S _y2, T _v2)
: AnalyticalF2D<T,S>(1), clout(std::cout,"LinearAnalyticalF2D") {
  T n2=(_x1-_x0)*(_y2-_y0)-(_y1-_y0)*(_x2-_x0);
  if (n2==0)
    clout << "Error function" << std::endl;
  else {
    T n0=(_y1-_y0)*(_v2-_v0)-(_v1-_v0)*(_y2-_y0);
    T n1=(_v1-_v0)*(_x2-_x0)-(_x1-_x0)*(_v2-_v0);
    a= -n0/n2;
    b= -n1/n2;
    c= (_x0*n0+_y0*n1+_v0*n2)/n2;
  }
}

template <typename T, typename S>
LinearAnalyticalF2D<T,S>::LinearAnalyticalF2D(T _a, T _b, T _c)
: AnalyticalF2D<T,S>(1), a(_a), b(_b), c(_c), clout(std::cout,"LinearAnalyticalF2D") { }

template <typename T, typename S>
std::vector<T> LinearAnalyticalF2D<T,S>::operator()(std::vector<S> x) {
  std::vector<T> y;
  y.push_back( a*x[0] + b*x[1] + c );
  return y;
}



template <typename T, typename S>
LinearAnalyticalF3D<T,S>::LinearAnalyticalF3D(S x0, S y0, S z0, T v0, S x1, S y1, S z1, T v1, S x2, S y2, S z2, T v2, S x3, S y3, S z3, T v3)
: AnalyticalF3D<T,S>(1), clout(std::cout,"LinearAnalyticalF3D") {
  T n = ((y3-y0)*(x1-x0)-(x3-x0)*(y1-y0))*((x2-x0)*(z1-z0)-(z2-z0)*(x1-x0))+((z3-z0)*(x1-x0)-(x3-x0)*(z1-z0))*((y2-y0)*(x1-x0)-(x2-x0)*(y1-y0));
  if (n==0)
    clout << "Error function" << std::endl;
  else {
    T w = ((y1-y0)*(x3-x0)-(x1-x0)*(y3-y0))*((v2-v0)-(x2-x0)*(v1-v0)/(x1-x0))/((y2-y0)*(x1-x0)-(x2-x0)*(y1-y0))+(v3-v0)-(x3-x0)*(v1-v0)/(x1-x0);
    T zx = (y1-y0)*((x2-x0)*(z1-z0)-(z2-z0)*(x1-x0))-(z1-z0)*((y2-y0)*(x1-x0)-(x2-x0)*(y1-y0));
    T rx = (v1-v0)/(x1-x0)-(y1-y0)*(v2-v0)/((y2-y0)*(x1-x0)-(x2-x0)*(y1-y0))+(y1-y0)*(x2-x0)*(v1-v0)/((y2-y0)*(x1-x0)*(x1-x0)-(x2-x0)*(y1-y0)*(x1-x0));
    T zy = (x1-x0)*((x2-x0)*(z1-z0)-(z2-z0)*(x1-x0));
    T ry = ((x1-x0)*(v2-v0)-(x2-x0)*(v1-v0))/((y2-y0)*(x1-x0)-(x2-x0)*(y1-y0));
    T zz = (x1-x0)*((y2-y0)*(x1-x0)-(x2-x0)*(y1-y0));
    T h = w/n;
    a = rx+zx*h;
    b = ry+zy*h;
    c = zz*h;
    d = v0-x0*a-y0*b-z0*c;
  }
};

template <typename T, typename S>
LinearAnalyticalF3D<T,S>::LinearAnalyticalF3D(T _a, T _b, T _c, T _d)
: AnalyticalF3D<T,S>(1), a(_a), b(_b), c(_c), d(_d), clout(std::cout,"LinearAnalyticalF3D") { };

template <typename T, typename S>
std::vector<T> LinearAnalyticalF3D<T,S>::operator()(std::vector<S> x) {
  std::vector<T> y;
  y.push_back( a*x[0] + b*x[1] + c*x[2] + d  );
  return y;
}



template <typename T, typename S>
SinusStartScale<T,S>::SinusStartScale(int _numTimeSteps, T _maxValue) : AnalyticalF1D<T,S>(1), numTimeSteps(_numTimeSteps), maxValue(_maxValue), pi(4.0*atan(1.0)) { };

template <typename T, typename S>
std::vector<T> SinusStartScale<T,S>::operator()(std::vector<S> x) {
  std::vector<T> y;
  y.push_back( (maxValue * (sin(-pi / 2.0 + (T)x[0] / (T)numTimeSteps * pi) + 1.0)) / 2.0);
  return y;
}

template <typename T, typename S>
PolynomialStartScale<T,S>::PolynomialStartScale(S _numTimeSteps, T _maxValue) : AnalyticalF1D<T,S>(1), numTimeSteps(_numTimeSteps), maxValue(_maxValue) { }

template <typename T, typename S>
std::vector<T> PolynomialStartScale<T,S>::operator()(std::vector<S> x) {
  std::vector<T> y;
  y.push_back( (T) x[0] / (T) numTimeSteps);
  y[0] = maxValue * y[0]*y[0]*y[0] * ( 10.0 + y[0] * (6.0*y[0] - 15.0) );
  return y;
}



template <typename T, typename S>
SquareAnalyticalF<T,S>::SquareAnalyticalF(S _cp, S _r, T _max)
  : AnalyticalF1D<T,S>(1), AnalyticalF2D<T,S>(1),
    cp(_cp), r(_r), max(_max) { }

template <typename T, typename S>
std::vector<T> SquareAnalyticalF<T,S>::operator()(std::vector<S> x) {
  std::vector<T> y;
  y.push_back( max*(1-(x[0]-cp)*(x[0]-cp)/(T)r/(T)r) );
  return y;
}



template <typename T, typename S>
ScaledAnalyticalF3D<T,S>::ScaledAnalyticalF3D(AnalyticalF3D<T,S>& _f, T _scale)
  : AnalyticalF3D<T,S>(1), f(_f), scale(_scale) { }

template <typename T, typename S>
std::vector<T> ScaledAnalyticalF3D<T,S>::operator()(std::vector<S> x) {
  std::vector<T> y;
  y.push_back( scale*f(x)[0]);
  y.push_back( scale*f(x)[1]);
  y.push_back( scale*f(x)[2]);
  return y;
}




} // end namespace olb

#endif
