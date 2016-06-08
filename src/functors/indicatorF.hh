/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2013 Lukas Baron, Mathias J. Krause
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

#ifndef INDICATOR_F_HH
#define INDICATOR_F_HH

#include<vector>    // for generic i/o
#include<cmath>     // for lpnorm

#include "indicatorF.h"
#include "analyticalF.h"
#include "io/stlReader.h"

namespace olb {


template <typename T, typename S>
SphereAnalyticalF1D<T,S>::SphereAnalyticalF1D(std::vector<S> center, S radius) : AnalyticalF3D<T,S>(1), _center(center), _radius2(radius*radius) { }


template <typename T, typename S>
std::vector<T> SphereAnalyticalF1D<T,S>::operator()(std::vector<S> x) {
  std::vector<T> y;
  T result = T(); 
  if ( (_center[0]-x[0])*(_center[0]-x[0]) <= _radius2 ) result = T(1);
  y.push_back(result);
  return y;
}


template <typename T, typename S>
SphereAnalyticalF2D<T,S>::SphereAnalyticalF2D(std::vector<S> center, S radius) : AnalyticalF3D<T,S>(1), _center(center), _radius2(radius*radius) { }


template <typename T, typename S>
std::vector<T> SphereAnalyticalF2D<T,S>::operator()(std::vector<S> x) {
  std::vector<T> y;
  T result = T(); 
  if ( (_center[0]-x[0])*(_center[0]-x[0])+(_center[1]-x[1])*(_center[1]-x[1]) <= _radius2 ) result = T(1);
  y.push_back(result);
  return y;
}


template <typename T, typename S>
SphereAnalyticalF3D<T,S>::SphereAnalyticalF3D(std::vector<S> center, S radius) : AnalyticalF3D<T,S>(1), _center(center), _radius2(radius*radius) { }


template <typename T, typename S>
std::vector<T> SphereAnalyticalF3D<T,S>::operator()(std::vector<S> x) {
  std::vector<T> y;
  T result = T(); 
  if ( (_center[0]-x[0])*(_center[0]-x[0])+(_center[1]-x[1])*(_center[1]-x[1])+(_center[2]-x[2])*(_center[2]-x[2]) <= _radius2 ) result = T(1);
  y.push_back(result);
  return y;
}


template <typename T, typename S>
EllipseAnalyticalF2D<T,S>::EllipseAnalyticalF2D(std::vector<S> center, S a, S b) : AnalyticalF3D<T,S>(1), _center(center), _a2(a*a), _b2(b*b) { }


template <typename T, typename S>
std::vector<T> EllipseAnalyticalF2D<T,S>::operator()(std::vector<S> input) {
  std::vector<T> y;
  T result = T();
  if ( (_center[0]-input[0])*(_center[0]-input[0]) / (_a2) +(_center[1]-input[1])*(_center[1]-input[1]) /(_b2) < 1. ) result = T(1);
  y.push_back(result);
  return y;
}


template <typename T, typename S>
CylinderAnalyticalF3D<T,S>::CylinderAnalyticalF3D(std::vector<S> center, std::vector<S> normal, S radius, S thickness) : AnalyticalF3D<T,S>(1), _center(center), _normal(normal), _radius(radius), _thickness(thickness) { }


template <typename T, typename S>
std::vector<S> CylinderAnalyticalF3D<T,S>::normalize(std::vector<S> vec) {
  S sum(0);
  std::vector<S> newVec(vec.size(),0);
  for (unsigned int iD=0; iD<vec.size(); iD++) {
    sum += vec[iD]*vec[iD];
  }
  S norm = pow(sum, 0.5);
  assert(norm>0);
  for (unsigned int iD=0; iD<vec.size(); iD++) {
    newVec[iD] = vec[iD]/norm;
  }
  return newVec;
}


template <typename T, typename S>
std::vector<S> CylinderAnalyticalF3D<T,S>::crossProduct3D(std::vector<S> a, std::vector<S> b) {
  std::vector<S> v;
  v.push_back(a[2]*b[3]-a[3]*b[2]);
  v.push_back(a[3]*b[1]-a[1]*b[3]);
  v.push_back(a[1]*b[2]-a[2]*b[1]);
  return v;
}


template <typename T, typename S>
std::vector<S> CylinderAnalyticalF3D<T,S>::vectorNorm(std::vector<S> a) {
  std::vector<S> v(1,0);
  for (unsigned iD=0; iD<a.size(); iD++) {
    v[0] += a[iD]*a[iD];
  }
  v[0] = sqrt(v[0]);
  return v;
}


template <typename T, typename S>
std::vector<T> CylinderAnalyticalF3D<T,S>::operator()(std::vector<S> x) {
  std::vector<bool> output(1,0);
  output[0] = false;
  // compute distance to the axis
  std::vector<S> tmp1 = normalize(_normal);
  std::vector<S> tmp2 = x;
  for (unsigned iD=0; iD<tmp2.size(); iD++) {
    tmp2[iD] -= _center[iD];
  }
  // compute distance to plane
  S d = S();
  for (unsigned iD=0; iD<tmp2.size(); iD++) {
    d += tmp1[iD]*tmp2[iD];
  }
  // compute distance to center (origin)
  S distToCenter = vectorNorm(tmp2)[0];
  //cout << "axis=" << distToAxis << "; center=" << distToCenter << endl;
  // compare with radius
  if (d*d <= _thickness*_thickness) {
    if (distToCenter*distToCenter - d*d <= _radius*_radius) {
      output[0] = true;
    }
  }
  return output;
}


template <typename T, typename S>
StlIndicatorF3D<T,S>::StlIndicatorF3D(STLreader<S>& _stlReader, S _eps) : AnalyticalF3D<T,S>(1), stlReader(_stlReader), eps(_eps) { }


template <typename T, typename S>
std::vector<T> StlIndicatorF3D<T,S>::operator()(std::vector<S> x) {
  std::vector<T> result(1,false);
  S distance = 2.*eps;

  stlReader.readDistance (x[0]-eps,x[1],x[2], 2.*eps, 0., 0., distance);
  if (distance<2.*eps) { result[0] = true; return result;}
  stlReader.readDistance (x[0],x[1]-eps,x[2], 0., 2.*eps, 0., distance);
  if (distance<2.*eps) { result[0] = true; return result;}
  stlReader.readDistance (x[0],x[1],x[2]-eps, 0., 0., 2.*eps, distance);
  if (distance<2.*eps) { result[0] = true; return result;}

  distance = 1.42*2.*eps;
  stlReader.readDistance (x[0]-1.42*eps,x[1]-1.42*eps,x[2], 1.42*2.*eps, 1.42*2.*eps, 0., distance);
  if (distance<1.42*2.*eps) { result[0] = true; return result;}
  stlReader.readDistance (x[0]-1.42*eps,x[1]+1.42*eps,x[2], 1.42*2.*eps, -1.42*2.*eps, 0., distance);
  if (distance<1.42*2.*eps) { result[0] = true; return result;}
  stlReader.readDistance (x[0]-1.42*eps,x[1],x[2]-1.42*eps, 1.42*2.*eps, 0., 1.42*2.*eps, distance);
  if (distance<1.42*2.*eps) { result[0] = true; return result;}
  stlReader.readDistance (x[0]-1.42*eps,x[1],x[2]+1.42*eps, 1.42*2.*eps, 0., -1.42*2.*eps, distance);
  if (distance<1.42*2.*eps) { result[0] = true; return result;}
  stlReader.readDistance (x[0],x[1]-1.42*eps,x[2]-1.42*eps, 0, 1.42*2.*eps, 1.42*2.*eps, distance);
  if (distance<1.42*2.*eps) { result[0] = true; return result;}
  stlReader.readDistance (x[0],x[1]-1.42*eps,x[2]+1.42*eps, 0, 1.42*2.*eps, -1.42*2.*eps, distance);
  if (distance<1.42*2.*eps) { result[0] = true; return result;}

  distance = 1.7321*2.*eps;
  stlReader.readDistance (x[0]-1.7321*eps,x[1]-1.7321*eps,x[2]-1.7321*eps, 1.7321*2.*eps, 1.7321*2.*eps, 1.7321*2.*eps, distance);
  if (distance<1.7321*2.*eps) { result[0] = true; return result;}
  stlReader.readDistance (x[0]-1.7321*eps,x[1]-1.7321*eps,x[2]+1.7321*eps, 1.7321*2.*eps, 1.7321*2.*eps, -1.7321*2.*eps, distance);
  if (distance<1.7321*2.*eps) { result[0] = true; return result;}
  stlReader.readDistance (x[0]-1.7321*eps,x[1]+1.7321*eps,x[2]-1.7321*eps, 1.7321*2.*eps, -1.7321*2.*eps, 1.7321*2.*eps, distance);
  if (distance<1.7321*2.*eps) { result[0] = true; return result;}
  stlReader.readDistance (x[0]-1.7321*eps,x[1]+1.7321*eps,x[2]+1.7321*eps, 1.7321*2.*eps, -1.7321*2.*eps, -1.7321*2.*eps, distance);
  if (distance<1.7321*2.*eps) { result[0] = true; return result;}

  return result;
}


} // namespace olb

#endif
