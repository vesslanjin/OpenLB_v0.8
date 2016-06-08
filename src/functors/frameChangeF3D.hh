/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2013 Gilles Zahnd, Mathias J. Krause
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

#ifndef FRAME_CHANGE_F_3D_HH
#define FRAME_CHANGE_F_3D_HH

#include<vector>
#include<cmath>
#include<string>
#include"math.h"

#include "frameChangeF3D.h"
#include "functors/genericF.h"
#include "functors/analyticalF.h"
#include "functors/superLatticeBaseF3D.h"
#include "functors/superLatticeLocalF3D.h"
#include "complexGrids/cuboidStructure/superLattice3D.h"
#include "core/lbHelpers.h"  // for computation of lattice rho and velocity

namespace olb {


template <typename T>
RotatingLinear3D<T>::RotatingLinear3D(std::vector<T> axisPoint_, std::vector<T> axisDirection_, T w_, T scale_)
  : AnalyticalF3D<T,T>(3), axisPoint(axisPoint_), axisDirection(axisDirection_), w(w_), scale(scale_) {
}


template <typename T>
std::vector<T> RotatingLinear3D<T>::operator()(std::vector<T> x) {
  std::vector<T> y;
  y.resize(3);
  y[0] = (axisDirection[1]*(x[2]-axisPoint[2]) - axisDirection[2]*(x[1]-axisPoint[1]))*w*scale;
  y[1] = (axisDirection[2]*(x[0]-axisPoint[0]) - axisDirection[0]*(x[2]-axisPoint[2]))*w*scale;
  y[2] = (axisDirection[0]*(x[1]-axisPoint[1]) - axisDirection[1]*(x[0]-axisPoint[0]))*w*scale;
  return y;
}


template <typename T>
RotatingQuadratic1D<T>::RotatingQuadratic1D(std::vector<T> axisPoint_, std::vector<T> axisDirection_,
                    T w_, T scale_, T additive_)
  : AnalyticalF3D<T,T>(1), w(w_), scale(scale_), additive(additive_) {
  axisPoint.resize(3);
  axisDirection.resize(3);
  for(int i=0; i<3; i++) {
    axisPoint[i]=axisPoint_[i];
    axisDirection[i]=axisDirection_[i];
  }
}


template <typename T>
std::vector<T> RotatingQuadratic1D<T>::operator()(std::vector<T> x) {
  std::vector<T> y;
  y.resize(1);
  T radiusSquared =  ((x[1]-axisPoint[1])*(x[1]-axisPoint[1])
                      +(x[2]-axisPoint[2])*(x[2]-axisPoint[2]))*axisDirection[0]
                    + ((x[0]-axisPoint[0])*(x[0]-axisPoint[0])
                      +(x[2]-axisPoint[2])*(x[2]-axisPoint[2]))*axisDirection[1]
                    + ((x[1]-axisPoint[1])*(x[1]-axisPoint[1])
                      +(x[0]-axisPoint[0])*(x[0]-axisPoint[0]))*axisDirection[2];
  y[0] = scale*w*w/2*radiusSquared+additive;
  return y;
}


template <typename T, template <typename U> class DESCRIPTOR>
RotatingForceField3D<T,DESCRIPTOR>::RotatingForceField3D(SuperLattice3D<T,DESCRIPTOR>& sLattice_,
                     SuperGeometry3D& superGeometry_,
                     const LBconverter<T>& converter_,
                     std::vector<T> axisPoint_,
                     std::vector<T> axisDirection_,
                     T w_,
                     bool centrifugeForceOn_,
                     bool coriolisForceOn_)
  : SuperLatticeF3D<T,DESCRIPTOR>(sLattice_,3),
    sg(superGeometry_),
    converter(converter_),
    axisPoint(axisPoint_),
    axisDirection(axisDirection_),
    w(w_),
    centrifugeForceOn(centrifugeForceOn_),
    coriolisForceOn(coriolisForceOn_) {

  velocity = new SuperLatticePhysVelocity3D<T, DESCRIPTOR>(sLattice_,converter_);
  rho = new SuperLatticeDensity3D<T, DESCRIPTOR>(sLattice_);
}


template <typename T, template <typename U> class DESCRIPTOR>
RotatingForceField3D<T,DESCRIPTOR>::~RotatingForceField3D() {
  delete velocity;
  delete rho;
}


template <typename T, template <typename U> class DESCRIPTOR>
std::vector<T> RotatingForceField3D<T,DESCRIPTOR>::operator()(std::vector<int> x) {

  int iC = x[0];
  int iXloc = x[1];
  int iYloc = x[2];
  int iZloc = x[3];

  std::vector<T> force(3,0);
  std::vector<T> F_centri(3,0);
  std::vector<T> F_coriolis(3,0);

  if ( this->sLattice.get_load().rank(iC) == singleton::mpi().getRank() ) {
    // local coords are given, fetch local cell and compute value(s)

    int globX = (int)this->sLattice.get_cGeometry().get_cuboid(iC).get_globPosX() + iXloc;
    int globY = (int)this->sLattice.get_cGeometry().get_cuboid(iC).get_globPosY() + iYloc;
    int globZ = (int)this->sLattice.get_cGeometry().get_cuboid(iC).get_globPosZ() + iZloc;

    T xPhys = this->sg.physCoordY(globX);
    T yPhys = this->sg.physCoordY(globY);
    T zPhys = this->sg.physCoordZ(globZ);

    T scalar = (xPhys-axisPoint[0])*axisDirection[0]
              +(yPhys-axisPoint[1])*axisDirection[1]
              +(zPhys-axisPoint[2])*axisDirection[2];

    if (centrifugeForceOn) {
      F_centri[0]=w*w*(xPhys-axisPoint[0]-scalar*axisDirection[0]);
      F_centri[1]=w*w*(yPhys-axisPoint[1]-scalar*axisDirection[1]);
      F_centri[2]=w*w*(zPhys-axisPoint[2]-scalar*axisDirection[2]);
    }
    if (coriolisForceOn) {
      F_coriolis[0]=-2*w*(axisDirection[1]*(*velocity)(x)[2]-axisDirection[2]*(*velocity)(x)[1]);
      F_coriolis[1]=-2*w*(axisDirection[2]*(*velocity)(x)[0]-axisDirection[0]*(*velocity)(x)[2]);
      F_coriolis[2]=-2*w*(axisDirection[0]*(*velocity)(x)[1]-axisDirection[1]*(*velocity)(x)[0]);
    }
    force[0]= ((*rho)(x)[0]*(F_coriolis[0]+F_centri[0]))/converter.physMasslessForce();
    force[1]= ((*rho)(x)[0]*(F_coriolis[1]+F_centri[1]))/converter.physMasslessForce();
    force[2]= ((*rho)(x)[0]*(F_coriolis[2]+F_centri[2]))/converter.physMasslessForce();
  }
  return force;
}


template <typename T>
CirclePoiseuille3D<T>::CirclePoiseuille3D(std::vector<T> axisPoint_, std::vector<T> axisDirection_,  T maxVelocity_, T radius_, T scale_)
  : AnalyticalF3D<T,T>(3) {
  axisPoint.resize(3);
  axisDirection.resize(3);
  for(int i=0; i<3; i++) {
    axisDirection[i]=axisDirection_[i];
    axisPoint[i]=axisPoint_[i];
  }
  maxVelocity=maxVelocity_;
  radius=radius_;
  scale=scale_;
}


template <typename T>
CirclePoiseuille3D<T>::CirclePoiseuille3D(
SuperGeometry3D& superGeometry_, int material_, T maxVelocity_, T scale_)
  : AnalyticalF3D<T,T>(3) {
  axisPoint=superGeometry_.getStatistics().getPhysCenterC(material_);

  axisPoint=superGeometry_.getStatistics().getPhysCenterC(material_);
  std::vector<int> discreteNormal = superGeometry_.getStatistics().computeDiscreteNormal(material_);
  axisDirection.push_back((T)(discreteNormal[0]));
  axisDirection.push_back((T)(discreteNormal[1]));
  axisDirection.push_back((T)(discreteNormal[2]));

  radius=T();
  for (int iD=0; iD<3; iD++)
    radius += superGeometry_.getStatistics().getPhysRadius(material_)[iD]/2.;
  scale=scale_;
  maxVelocity=maxVelocity_;
}


template <typename T>
std::vector<T> CirclePoiseuille3D<T>::operator()(std::vector<T> x) {
  std::vector<T> velocity;
  velocity.resize(3);
  velocity[0]= scale*maxVelocity*axisDirection[0]*(1.-((x[1]-axisPoint[1])*(x[1]-axisPoint[1])+(x[2]-axisPoint[2])*(x[2]-axisPoint[2]))/radius/radius);
  velocity[1]= scale*maxVelocity*axisDirection[1]*(1.-((x[0]-axisPoint[0])*(x[0]-axisPoint[0])+(x[2]-axisPoint[2])*(x[2]-axisPoint[2]))/radius/radius);
  velocity[2]= scale*maxVelocity*axisDirection[2]*(1.-((x[1]-axisPoint[1])*(x[1]-axisPoint[1])+(x[0]-axisPoint[0])*(x[0]-axisPoint[0]))/radius/radius);

  return velocity;
}


template <typename T>
std::vector<T> RectanglePoiseuille3D<T>::normalize(std::vector<T> vec) {
  T sum(0);
  std::vector<T> newVec(vec.size(),0);
  for (unsigned int iD=0; iD<vec.size(); iD++) {
    sum += vec[iD]*vec[iD];
  }
  T norm = pow(sum, 0.5);
  assert(norm>0);
  for (unsigned int iD=0; iD<vec.size(); iD++) {
    newVec[iD] = vec[iD]/norm;
  }
  return newVec;
}


template <typename T>
RectanglePoiseuille3D<T>::RectanglePoiseuille3D(std::vector<T>& x0_, std::vector<T>& x1_, std::vector<T>& x2_, std::vector<T>& maxVelocity_)
  : AnalyticalF3D<T,T>(3), clout(std::cout,"RectanglePoiseille3D"), x0(x0_), x1(x1_), x2(x2_), maxVelocity(maxVelocity_) { }


template <typename T>
RectanglePoiseuille3D<T>::RectanglePoiseuille3D(SuperGeometry3D& superGeometry_, int material_, std::vector<T>& maxVelocity_, T offsetX, T offsetY, T offsetZ)
  : AnalyticalF3D<T,T>(3), clout(std::cout, "RectanglePoiseuille3D"), maxVelocity(maxVelocity_) {
  offsetX = superGeometry_.getSpacing();
  offsetY = superGeometry_.getSpacing();
  offsetZ = superGeometry_.getSpacing();
  std::vector<T> min = superGeometry_.getStatistics().getPhysMinC(material_);
  std::vector<T> max = superGeometry_.getStatistics().getPhysMaxC(material_);
  // set three corners of the plane, move by offset to land on the v=0
  // boundary and adapt certain values depending on the orthogonal axis to get
  // different points
  x0 = min;
  x1 = min;
  x2 = min;
  if (max[0]-min[0]==0) { // orthogonal to x-axis
    x0[1] -= offsetY;
    x0[2] -= offsetZ;
    x1[1] -= offsetY;
    x1[2] -= offsetZ;
    x2[1] -= offsetY;
    x2[2] -= offsetZ;

    x1[1] = max[1]+offsetY;
    x2[2] = max[2]+offsetZ;
  } else if (max[1]-min[1]==0) { // orthogonal to y-axis
    x0[0] -= offsetX;
    x0[2] -= offsetZ;
    x1[0] -= offsetX;
    x1[2] -= offsetZ;
    x2[0] -= offsetX;
    x2[2] -= offsetZ;

    x1[0] = max[0]+offsetX;
    x2[2] = max[2]+offsetZ;
  } else if (max[2]-min[2]==0) { // orthogonal to z-axis
    x0[0] -= offsetX;
    x0[1] -= offsetY;
    x1[0] -= offsetX;
    x1[1] -= offsetY;
    x2[0] -= offsetX;
    x2[1] -= offsetY;

    x1[0] = max[0]+offsetX;
    x2[1] = max[1]+offsetY;
  } else {
    clout << "Error: constructor from material number works only for axis-orthogonal planes" << std::endl;
  }
}


template <typename T>
std::vector<T> RectanglePoiseuille3D<T>::operator()(std::vector<T> x) {
  std::vector<T> velocity(3,T());

  // create plane normals and supports, (E1,E2) and (E3,E4) are parallel
  std::vector<std::vector<T> > n(4,std::vector<T>(3,0)); // normal vectors
  std::vector<std::vector<T> > s(4,std::vector<T>(3,0)); // support vectors
  for (int iD=0; iD<3; iD++) {
    n[0][iD] =  x1[iD]-x0[iD];
    n[1][iD] = -x1[iD]+x0[iD];
    n[2][iD] =  x2[iD]-x0[iD];
    n[3][iD] = -x2[iD]+x0[iD];
    s[0][iD] = x0[iD];
    s[1][iD] = x1[iD];
    s[2][iD] = x0[iD];
    s[3][iD] = x2[iD];
  }
  for (int iP=0; iP<4; iP++) {
    n[iP] = normalize(n[iP]);
  }

  // determine plane coefficients in the coordinate equation E_i: Ax+By+Cz+D=0
  // given form: (x-s)*n=0 => A=n1, B=n2, C=n3, D=-(s1n1+s2n2+s3n3)
  std::vector<T> A(4,0);
  std::vector<T> B(4,0);
  std::vector<T> C(4,0);
  std::vector<T> D(4,0);

  for (int iP=0; iP<4; iP++) {
    A[iP] = n[iP][0];
    B[iP] = n[iP][1];
    C[iP] = n[iP][2];
    D[iP] = -(s[iP][0]*n[iP][0] + s[iP][1]*n[iP][1] + s[iP][2]*n[iP][2]);
  }

  // determine distance to the walls by formula
  std::vector<T> d(4,0);
  T aabbcc(0);
  for (int iP=0; iP<4; iP++) {
    aabbcc = A[iP]*A[iP] + B[iP]*B[iP] + C[iP]*C[iP];
    d[iP] = abs(A[iP]*x[0]+B[iP]*x[1]+C[iP]*x[2]+D[iP])*pow(aabbcc,-0.5);
  }

  // length and width of the rectangle
  std::vector<T> l(2,0);
  l[0] = d[0]+d[1];
  l[1] = d[2]+d[3];

  T positionFactor = 16.*d[0]/l[0]*d[1]/l[0]*d[2]/l[1]*d[3]/l[1]; // between 0 and 1

  velocity[0] = maxVelocity[0]*positionFactor;
  velocity[1] = maxVelocity[1]*positionFactor;
  velocity[2] = maxVelocity[2]*positionFactor;
  return velocity;
}


template <typename T>
EllipticPoiseuille3D<T>::EllipticPoiseuille3D(std::vector<T> center, T a, T b, T maxVel) : AnalyticalF3D<T,T>(3), clout(std::cout, "EllipticPoiseuille3D"), _center(center), _a2(a*a), _b2(b*b), _maxVel(maxVel) { }


template <typename T>
std::vector<T> EllipticPoiseuille3D<T>::operator()(std::vector<T> x) {
  std::vector<T> velocity;
  velocity.resize(3);
  T cosOmega2  = std::pow(x[0]-_center[0],2.)/(std::pow(x[0]-_center[0],2.)+std::pow(x[1]-_center[1],2.));
  T rad2 = _a2*_b2 /((_b2-_a2)*cosOmega2 + _a2) ;
  T x2 =  (std::pow(x[0]-_center[0],2.)+std::pow(x[1]-_center[1],2.))/ rad2;

  //	clout << _center[0] << " " << _center[1] << " " << x[0] << " " << x[1] << " " << std::sqrt(rad2) << " " << std::sqrt(std::pow(x[0]-_center[0],2.)+std::pow(x[1]-_center[1],2.)) << " " << x2 << std::endl;

  velocity[0] = 0.;
  velocity[1] = 0.;
  velocity[2] = _maxVel*(-x2+1);
  if(_center[0] == x[0] && _center[1] == x[1]) velocity[2] = _maxVel;
  return velocity;
}


} // end namespace olb
#endif
