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

#ifndef ANALYTICAL_F_H
#define ANALYTICAL_F_H

#include<vector>    // for generic i/o
#include<cmath>     // for lpnorm

#include "functors/genericF.h"
#include "io/ostreamManager.h"

/** Note: Throughout the whole source code directory genericFunctions, the
 *  template parameters for i/o dimensions are:
 *           F: S^m -> T^n  (S=source, T=target)
 */

namespace olb {

////////////////////////////////////////////////////////////////////////////////
// 2nd level classes
// note: the number behind the AnalyticalF indicates the SOURCE dimension,
//       the target dimension for AnalyticalF is always 1 to reduce complexity
// note: for LatticeFunctions the number indicates the SOURCE dimension,
//       target dim depends on return variable type, so std::vector<T> is used

/// represents analytical functions without units, 1D-->1D
template <typename T, typename S>
class AnalyticalF1D : public GenericF<T,S> {
public:
  AnalyticalF1D(int n) : GenericF<T,S>(n,1) { }
  AnalyticalF1D<T,S>& operator-(AnalyticalF1D<T,S>& rhs);
  AnalyticalF1D<T,S>& operator+(AnalyticalF1D<T,S>& rhs);
  AnalyticalF1D<T,S>& operator*(AnalyticalF1D<T,S>& rhs);
  AnalyticalF1D<T,S>& operator/(AnalyticalF1D<T,S>& rhs);
};
//-----------------------------------------------------------------------------------
template <typename T, typename S>
class AnalyticalF2D : public GenericF<T,S> {
public:
  AnalyticalF2D(int n) : GenericF<T,S>(n,2) { }
  AnalyticalF2D<T,S>& operator-(AnalyticalF2D<T,S>& rhs);
  AnalyticalF2D<T,S>& operator+(AnalyticalF2D<T,S>& rhs);
  AnalyticalF2D<T,S>& operator*(AnalyticalF2D<T,S>& rhs);
  AnalyticalF2D<T,S>& operator/(AnalyticalF2D<T,S>& rhs);
};
//-------------------------------------------------------------------------------------
template <typename T, typename S>
class AnalyticalF3D : public GenericF<T,S> {
public:
  AnalyticalF3D(int n) : GenericF<T,S>(n,3) { }
  AnalyticalF3D<T,S>& operator-(AnalyticalF3D<T,S>& rhs);
  AnalyticalF3D<T,S>& operator+(AnalyticalF3D<T,S>& rhs);
  AnalyticalF3D<T,S>& operator*(AnalyticalF3D<T,S>& rhs);
  AnalyticalF3D<T,S>& operator/(AnalyticalF3D<T,S>& rhs);
};


/*
template <typename T, typename S>
class UserDefinedGenericF3D : public AnalyticalF3D<T,S> {
private:

public:
  UserDefinedGenericF3D() : AnalyticalF3D<T,S>() { };

  virtual std::vector<T> operator()(std::vector<S> x) {
    std::vector<T> y;
    return y;
  };
};

template <typename T, typename S>
class UserDefined1F3D : public UserDefinedGenericF3D<T,S> {
private:

public:
  UserDefined1F3D() : UserDefinedGenericF3D<T,S>() {}

  //std::vector<T> operator()(std::vector<S> x);
};

template <typename T, typename S>
class UserDefined2F3D : public UserDefinedGenericF3D<T,S> {
private:

public:
  UserDefined2F3D() : UserDefinedGenericF3D<T,S>() { }

  //std::vector<T> operator()(std::vector<S> x);
};
*/
////////////////////////////////////////////////////////////////////////////////
// 3rd level classes: AnalyticalF


template <typename T, typename S>
class ComposedAnalyticalF3D : public AnalyticalF3D<T,S> {
private:
  AnalyticalF3D<T,S>& _f0;
  AnalyticalF3D<T,S>& _f1;
  AnalyticalF3D<T,S>& _f2;
public:
  ComposedAnalyticalF3D(AnalyticalF3D<T,S>& f0, AnalyticalF3D<T,S>& f1, AnalyticalF3D<T,S>& f2);
  std::vector<T> operator()(std::vector<S> x);
};



/// represents all constant functions from 1D,2D,3D->1D
template <typename T, typename S>
class ConstAnalyticalF1D : public AnalyticalF1D<T,S> {
private:
  std::vector<T> c;
public:
  ConstAnalyticalF1D(T value);
  ConstAnalyticalF1D(std::vector<T>& value);
  std::vector<T> operator()(std::vector<S> x);
};

template <typename T, typename S>
class ConstAnalyticalF2D : public AnalyticalF2D<T,S> {
private:
 std::vector<T> c;
public:
  ConstAnalyticalF2D(T value);
  ConstAnalyticalF2D(std::vector<T>& value);
  std::vector<T> operator()(std::vector<S> x);
};

template <typename T, typename S>
class ConstAnalyticalF3D : public AnalyticalF3D<T,S> {
private:
 std::vector<T> c;
public:
  ConstAnalyticalF3D(T value);
  ConstAnalyticalF3D(std::vector<T>& value);
  std::vector<T> operator()(std::vector<S> x);
};


/// represents all linear functions from 1D,2D,3D->1D through the values v0, v1, ... 
/// for the points 1D: x0, x1; 2D: (x0,y0), (x1,y1), ... ; 3D: (x0,yo,z0), (x1,y1,z1),... 
/// note: Output depends only on first parameter
template <typename T, typename S>
class LinearAnalyticalF1D : public AnalyticalF1D<T,S> {
private:
T a;
T b;
OstreamManager clout;
public:
  LinearAnalyticalF1D(S _x0, T _v0, S _x1, T _v1);
  
  //LinearAnalyticalF1D(S _x0, T _v0, S _lx, T _lv) 
  //  : AnalyticalF1D<T,S>(1,1), clout(std::cout,"LinearAnalyticalF1D") {
  //if (lx==0) 
	//clout <<"Error: x1-x2=0" << endl;
  //else {
  //  a=lv/lx;
  //  b=v0-x0*a;
  //  }
  //};
  LinearAnalyticalF1D(T _a, T _b);
  std::vector<T> operator()(std::vector<S> x);
 
};


template <typename T, typename S>
class LinearAnalyticalF2D : public AnalyticalF2D<T,S> {
  protected:
    T a;
    T b;
    T c;
    OstreamManager clout;
  public:
  LinearAnalyticalF2D(S _x0, S _y0, T _v0, S _x1, S _y1, T _v1, S _x2, S _y2, T _v2);

  /*
  LinearAnalyticalF2D(S _x0, S _y0, T _v0, S _lx, S _ly, T _lv, S _mx, S _my, T _mv)
	:AnalyticalF2D<T,S>(2,1) {
    T n2=lx*my-ly*mx;
    if (n2==0)
      cout << "Error function" << endl;
    else {
      T n0 = ly*mv - lv*my;
      T n1 = lv*mx - lx*mv;
      a = -n0/n2;
      b = -n1/n2;
      c = v0 + (x0*n0 + y0*n1)/n2;
      }
    };
    */
  LinearAnalyticalF2D(T _a, T _b, T _c);
  std::vector<T> operator()(std::vector<S> x);
};


/// represents linear functions through 3 points (planes)
template <typename T, typename S>
class LinearAnalyticalF3D : public AnalyticalF3D<T,S> {
  protected:
    T a;
    T b;
    T c;
    T d;
    OstreamManager clout;
  public:
  LinearAnalyticalF3D(S x0, S y0, S z0, T v0, S x1, S y1, S z1, T v1, S x2, S y2, S z2, T v2, S x3, S y3, S z3, T v3);

  /*
   * L: overload error, which function is wanted?
  LinearAnalyticalF3D(S _x0, S _y0, S _z0, T _v0, S _lx, S _ly, S _lz, T _lv, S _mx, S _my, S _mz, T _mv, S _nx, S _ny, S _nz, T _nv)
        :AnalyticalF3D<T,S>(1,3) {
    T n = (ny*lx-nx*ly)*(mx*lz-mz*lx)+(nz*lx-nx*lz)*(my*lx-mx*ly)
    if (n==0)
       cout << "Error function" << endl;
    else {
      T w = (ly*nx-lx*ny)*(mv-mx*lv/lx)/(my*lx-mx*ly)+nv-nx*lv/lx;
      T zx = ly*(mx*lz-mz*lx)-lz*(my*lx-mx*ly);
      T rx = lv/lx-ly*mv/(my*lx-mx*ly)+ly*mx*lv/(my*lx*lx-mx*ly*lx);
      T zy = lx*(mx*lz-mz*lx);
      T ry = (lx*mv-mx*lv)/(my*lx-mx*ly);
      T zz = lx*(my*lx-mx*ly);
      T h = w/n;
      T a = rx+zx*h;
      T b = ry+zy*h;
      T c = zz*h;
      T d = v0-x0*a-y0*b-z0*c;
      }
    };
    */

  LinearAnalyticalF3D(T _a, T _b, T _c, T _d);
  std::vector<T> operator()(std::vector<S> x);
};




/// implements a start curve based on sinus for a continuous transition at 0 and 1
template <typename T, typename S>
class SinusStartScale : public AnalyticalF1D<T,S> {
 protected:
 S numTimeSteps;
 T maxValue;
 T pi;
 public:
 SinusStartScale(int _numTimeSteps=1, T _maxValue=1);
  std::vector<T> operator()(std::vector<S> x);
};


/// implements a start curve based on a polynomial fifth order for a continuous transition at 0 and 1: maxValue*(6*y*y*y*y*y-15*y*y*y*y+10*y*y*y)

template <typename T, typename S>
class PolynomialStartScale : public AnalyticalF1D<T,S> {
protected:
  S numTimeSteps;
  T maxValue;
public:
  PolynomialStartScale(S _numTimeSteps=S(1), T _maxValue=T(1));
  std::vector<T> operator()(std::vector<S> x);
};

/// represents an inverse parabola profile like it is used in Poiseuille inflow
/// note: output depends only on first parameter, maps 1D,2D,3D->1D
template <typename T, typename S>
class SquareAnalyticalF : public AnalyticalF1D<T,S>, public AnalyticalF2D<T,S> {
private:
  S cp;
  S r;
  T max;
public:
  SquareAnalyticalF(S _cp, S _r, T _max);
  std::vector<T> operator()(std::vector<S> x);
};


template <typename T, typename S>
class ScaledAnalyticalF3D : public AnalyticalF3D<T,S> {
private:
  T scale;
  AnalyticalF3D<T,S>& f;
public:
  ScaledAnalyticalF3D(AnalyticalF3D<T,S>& _f, T _scale);
  std::vector<T> operator()(std::vector<S> x);
};

// some ideas...

/// represents bilinear functions from 1D -> 2D
template <typename T, typename S>
class BilinearAnalyticalF : public AnalyticalF1D<T,S> { };


/*
/// represents arbitrary polynomial functions
template <typename T, typename S>
class PolynomialAnalyticalF : public AnalyticalF1D<T,S> {
private:
  std::vector<T> c;
public:
  PolynomialAnalyticalF(std::vector<int> coeffs) : c(coeffs), AnalyticalF1D<T,S>(2,1) { }
  T operator() (S x) {
    T sum = 0;
    for (int i=0; i<size(coeffs); i++) {
      sum += coeffs(i)*pow(x,i);                    // sum+= c(i)*x^i
    }
    return sum;
  }
};
*/


} // end namespace olb

#endif
