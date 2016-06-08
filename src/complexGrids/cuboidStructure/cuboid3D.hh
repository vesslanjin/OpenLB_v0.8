/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Mathias J. Krause
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
 * The description of a single 3D cuboid -- generic implementation.
 */


#ifndef CUBOID_3D_HH
#define CUBOID_3D_HH

#include <iostream>
#include <math.h>
#include <vector>
#include "cuboidGeometry2D.h"
#include "cuboid3D.h"
#include "core/lbHelpers.h"


namespace olb {

////////////////////// Class Cuboid3D /////////////////////////

template<typename T>
Cuboid3D<T>::Cuboid3D() : clout(std::cout,"Cuboid3D") {}


template<typename T>
Cuboid3D<T>::Cuboid3D(T globPosX, T globPosY, T globPosZ, T delta ,int nX, int nY, int nZ)
  : clout(std::cout,"Cuboid3D") {
  this->init(globPosX, globPosY, globPosZ, delta, nX, nY, nZ);
}

template<typename T>
void Cuboid3D<T>::init(T globPosX, T globPosY, T globPosZ, T delta, int nX, int nY, int nZ) {
  _globPosX = globPosX;
  _globPosY = globPosY;
  _globPosZ = globPosZ;
  _delta    = delta;
  _nX       = nX;
  _nY       = nY;
  _nZ       = nZ;
}

template<typename T>
T Cuboid3D<T>::get_globPosX() const { return _globPosX; }

template<typename T>
T Cuboid3D<T>::get_globPosY() const { return _globPosY; }

template<typename T>
T Cuboid3D<T>::get_globPosZ() const { return _globPosZ; }

template<typename T>
T Cuboid3D<T>::get_delta() const { return _delta; }

template<typename T>
int Cuboid3D<T>::get_nX() const { return _nX; }

template<typename T>
int Cuboid3D<T>::get_nY() const { return _nY; }

template<typename T>
int Cuboid3D<T>::get_nZ() const { return _nZ; }

template<typename T>
T Cuboid3D<T>::get_volume() const { return _nY*_nX*_nZ*_delta*_delta*_delta; }

template<typename T>
int Cuboid3D<T>::get_nNodesVolume() const { return _nY*_nX*_nZ; }

template<typename T>
T Cuboid3D<T>::get_perimeter() const {
  return 2*_delta*_delta*(_nX*_nY + _nY*_nZ + _nZ*_nX);
}

template<typename T>
int Cuboid3D<T>::get_nNodesPerimeter() const {
  return 2*((_nX-1)*(_nY-1) + (_nY-1)*(_nZ-1) + (_nZ-1)*(_nX-1));
}

template<typename T>
void Cuboid3D<T>::print() const {
  clout << "--------Cuboid Details----------" << std::endl;
  clout << " Corner (x/y/z): " << "\t" << "("
        << this->get_globPosX() << "/" << this->get_globPosY()
        << "/" << this->get_globPosZ() << ")" << std::endl;
  clout << " Delta: " << "\t" << "\t" << this->get_delta() << std::endl;
  clout << " Perimeter: " << "\t" << "\t" << this->get_perimeter() << std::endl;
  clout << " Volume: " << "\t" << "\t" << this->get_volume() << std::endl;
  clout << " Extent (x/y/z): " << "\t" << "("
        << this->get_nX() << "/" << this->get_nY() << "/"
        << this->get_nZ() << ")" << std::endl;
  clout << " Nodes at Perimeter: " << "\t" << this->get_nNodesPerimeter() << std::endl;
  clout << " Nodes in Volume: " << "\t" << this->get_nNodesVolume() << std::endl;
  clout << "--------------------------------" << std::endl;
}


template<typename T>
bool Cuboid3D<T>::checkPoint(T globX, T globY, T globZ, int overlap) const {
  if (_globPosX <= globX + overlap*_delta &&
      _globPosX + T(_nX-1+overlap)*_delta  >= globX &&
      _globPosY <= globY + overlap *_delta &&
      _globPosY + T(_nY-1+overlap)*_delta  >= globY &&
      _globPosZ <= globZ + overlap *_delta &&
      _globPosZ + T(_nZ-1+overlap)*_delta  >= globZ ) {
    return true;
  }
  else return false;
}

template<typename T>
bool Cuboid3D<T>::checkPoint(T globX, T globY, T globZ, int &locX, int &locY, int &locZ, int overlap) const {
  if (overlap!=0) {
    Cuboid3D tmp(_globPosX - overlap*_delta, _globPosY - overlap*_delta, _globPosZ - overlap*_delta,
                 _delta , _nX + overlap*2, _nY + overlap*2, _nZ + overlap*2);
    return tmp.checkPoint(globX, globY, globZ, locX, locY, locZ);
  }
  else if (!checkPoint(globX, globY, globZ)) return false;
  else {
    T tempX = globX - (T)_globPosX;
    T tempY = globY - (T)_globPosY;
    T tempZ = globZ - (T)_globPosZ;
    if(tempX==(int)tempX && tempY==(int)tempY && tempZ==(int)tempZ) {
      locX = (int)tempX;
      locY = (int)tempY;
      locZ = (int)tempZ;
      return true;
    }
    else return false;
  }
}

template<typename T>
bool Cuboid3D<T>::checkInters(T globX0, T globX1, T globY0, T globY1, T globZ0, T globZ1, int overlap) const {

  T locX0d = std::max(_globPosX-overlap*_delta,globX0);
  T locY0d = std::max(_globPosY-overlap*_delta,globY0);
  T locZ0d = std::max(_globPosZ-overlap*_delta,globZ0);
  T locX1d = std::min(_globPosX+(_nX+overlap-1)*_delta,globX1);
  T locY1d = std::min(_globPosY+(_nY+overlap-1)*_delta,globY1);
  T locZ1d = std::min(_globPosZ+(_nZ+overlap-1)*_delta,globZ1);


  if (!(locX1d>=locX0d && locY1d>=locY0d && locZ1d>=locZ0d)) return false;
  return true;
}

template<typename T>
bool Cuboid3D<T>::checkInters(T globX0, T globX1, T globY0, T globY1, T globZ0, T globZ1,
                              int &locX0, int &locX1, int &locY0, int &locY1, int &locZ0, int &locZ1, int overlap) const {
  if (overlap!=0) {
    Cuboid3D tmp(_globPosX - overlap*_delta, _globPosY - overlap*_delta, _globPosZ - overlap*_delta,
                 _delta , _nX + overlap*2, _nY + overlap*2, _nZ + overlap*2);
    return tmp.checkInters(globX0, globX1, globY0, globY1, globZ0, globZ1,
                           locX0, locX1, locY0, locY1, locZ0, locZ1);
  }
  else if (!checkInters(globX0, globX1, globY0, globY1, globZ0, globZ1)) {
    locX0 = 1;
    locX1 = 0;
    locY0 = 1;
    locY1 = 0;
    locZ0 = 1;
    locZ1 = 0;
    return false;
  }
  else {
    locX0 = 0;
    for (int i=0; _globPosX + i*_delta < globX0; i++) {locX0 = i+1;}
    locX1 = _nX-1;
    for (int i=_nX-1; _globPosX + i*_delta > globX1; i--) {locX1 = i-1;}
    locY0 = 0;
    for (int i=0; _globPosY + i*_delta < globY0; i++) {locY0 = i+1;}
    locY1 = _nY-1;
    for (int i=_nY-1; _globPosY + i*_delta > globY1; i--) {locY1 = i-1;}
    locZ0 = 0;
    for (int i=0; _globPosZ + i*_delta < globZ0; i++) {locZ0 = i+1;}
    locZ1 = _nZ-1;
    for (int i=_nZ-1; _globPosZ + i*_delta > globZ1; i--) {locZ1 = i-1;}
    return true;
  }
}

template<typename T>
void Cuboid3D<T>::divide(int nX, int nY, int nZ, std::vector<Cuboid3D<T> > &childrenC) const {
  T globPosX_child, globPosY_child, globPosZ_child;
  int xN_child = 0;
  int yN_child = 0;
  int zN_child = 0;

  globPosX_child = _globPosX;
  globPosY_child = _globPosY;
  globPosZ_child = _globPosZ;

  for (int iX=0; iX<nX; iX++) {
    for (int iY=0; iY<nY; iY++) {
      for (int iZ=0; iZ<nZ; iZ++) {
        xN_child       = (_nX+nX-iX-1)/nX;
        yN_child       = (_nY+nY-iY-1)/nY;
        zN_child       = (_nZ+nZ-iZ-1)/nZ;
        Cuboid3D<T> child(globPosX_child, globPosY_child, globPosZ_child,
                          _delta, xN_child, yN_child, zN_child);
        childrenC.push_back(child);
        globPosZ_child += zN_child*_delta;
      }
      globPosZ_child = _globPosZ;
      globPosY_child += yN_child*_delta;
    }
    globPosY_child = _globPosY;
    globPosX_child += xN_child*_delta;
  }
}


template<typename T>
void Cuboid3D<T>::resize(int X, int Y, int Z, int nX, int nY, int nZ) {
  _globPosX = _globPosX+X;
  _globPosY = _globPosY+Y;
  _globPosZ = _globPosZ+Z;

  _nX = nX;
  _nY = nY;
  _nZ = nZ;
}


template<typename T>
void Cuboid3D<T>::divide(int p, std::vector<Cuboid3D<T> > &childrenC) const {

  OLB_PRECONDITION(p>0);

  int iX = 1;
  int iY = 1;
  int iZ = p;
  int nX = _nX/iX;
  int bestIx = iX;
  int nY = _nY/iY;
  int bestIy = iY;
  int nZ = _nZ/iZ;
  int bestIz = iZ;
  T bestRatio = ((T)(_nX/iX)/(T)(_nY/iY)-1)*((T)(_nX/iX)/(T)(_nY/iY)-1)
                + ((T)(_nY/iY)/(T)(_nZ/iZ)-1)*((T)(_nY/iY)/(T)(_nZ/iZ)-1)
                + ((T)(_nZ/iZ)/(T)(_nX/iX)-1)*((T)(_nZ/iZ)/(T)(_nX/iX)-1);

  for (int iX=1; iX<=p; iX++) {
    for (int iY=1; iY*iX<=p; iY++) {
      for (int iZ=p/(iX*iY); iZ*iY*iX<=p; iZ++) {
        if ((iX+1)*iY*iZ>p && iX*(iY+1)*iZ>p ) {
          T ratio = ((T)(_nX/iX)/(T)(_nY/iY)-1)*((T)(_nX/iX)/(T)(_nY/iY)-1)
                    + ((T)(_nY/iY)/(T)(_nZ/iZ)-1)*((T)(_nY/iY)/(T)(_nZ/iZ)-1)
                    + ((T)(_nZ/iZ)/(T)(_nX/iX)-1)*((T)(_nZ/iZ)/(T)(_nX/iX)-1);
          if (ratio<bestRatio) {
            bestRatio = ratio;
            bestIx = iX;
            bestIy = iY;
            bestIz = iZ;
            nX = _nX/iX;
            nY = _nY/iY;
            nZ = _nZ/iZ;
          }
        }
      }
    }
  }

  int rest = p - bestIx*bestIy*bestIz;

  // split in one cuboid
  if (rest==0) {
    divide(bestIx, bestIy, bestIz, childrenC);
    return;
  }
  else {

    // add in z than in y direction
    if (nZ>nY && nZ>nX) {

      int restY = rest%bestIy;
      // split in two cuboid
      if (restY==0) {
        int restX = rest/bestIy;
        CuboidGeometry2D<T> helpG(_globPosX, _globPosZ, _delta, _nX, _nZ, bestIx*bestIz+restX);

        int yN_child = 0;
        T globPosY_child = _globPosY;

        for (int iY=0; iY<bestIy; iY++) {
          yN_child         = (_nY+bestIy-iY-1)/bestIy;
          for (int iC=0; iC<helpG.get_nC(); iC++) {
            int xN_child     = helpG.get_cuboid(iC).get_nX();
            int zN_child     = helpG.get_cuboid(iC).get_nY();
            T globPosX_child = helpG.get_cuboid(iC).get_globPosX();
            T globPosZ_child = helpG.get_cuboid(iC).get_globPosY();

            Cuboid3D<T> child(globPosX_child, globPosY_child, globPosZ_child,
                              _delta, xN_child, yN_child, zN_child);
            childrenC.push_back(child);

          }
          globPosY_child += yN_child*_delta;
        }
        return;
      }

      // spilt in four cuboid

      int restX = rest/bestIy+1;
      int yN_child = 0;
      T globPosY_child = _globPosY;
      int splited_nY = (int) (_nY * (T)((bestIx*bestIz+restX)*restY)/(T)p);
      CuboidGeometry2D<T> helpG0(_globPosX, _globPosZ, _delta, _nX, _nZ, bestIx*bestIz+restX);

      for (int iY=0; iY<restY; iY++) {
        yN_child         = (splited_nY+restY-iY-1)/restY;
        for (int iC=0; iC<helpG0.get_nC(); iC++) {
          int xN_child     = helpG0.get_cuboid(iC).get_nX();
          int zN_child     = helpG0.get_cuboid(iC).get_nY();
          T globPosX_child = helpG0.get_cuboid(iC).get_globPosX();
          T globPosZ_child = helpG0.get_cuboid(iC).get_globPosY();

          Cuboid3D<T> child(globPosX_child, globPosY_child, globPosZ_child,
                            _delta, xN_child, yN_child, zN_child);
          childrenC.push_back(child);
        }
        globPosY_child += yN_child*_delta;
      }

      splited_nY = _nY - splited_nY;
      restX = rest/bestIy;
      CuboidGeometry2D<T> helpG1(_globPosX, _globPosZ, _delta, _nX, _nZ, bestIx*bestIz+restX);
      yN_child = 0;

      for (int iY=0; iY<bestIy-restY; iY++) {
        yN_child         = (splited_nY+bestIy-restY-iY-1)/(bestIy-restY);
        for (int iC=0; iC<helpG1.get_nC(); iC++) {
          int xN_child     = helpG1.get_cuboid(iC).get_nX();
          int zN_child     = helpG1.get_cuboid(iC).get_nY();
          T globPosX_child = helpG1.get_cuboid(iC).get_globPosX();
          T globPosZ_child = helpG1.get_cuboid(iC).get_globPosY();

          Cuboid3D<T> child(globPosX_child, globPosY_child, globPosZ_child,
                            _delta, xN_child, yN_child, zN_child);
          childrenC.push_back(child);
        }
        globPosY_child += yN_child*_delta;
      }
      return;
    }

    // add in x than in y direction
    else if (nX>nY && nX>nZ) {
      int restY = rest%bestIy;
      // split in two cuboid
      if (restY==0) {
        int restZ = rest/bestIy;
        CuboidGeometry2D<T> helpG(_globPosX, _globPosZ, _delta, _nX, _nZ, bestIx*bestIz+restZ);

        int yN_child = 0;
        T globPosY_child = _globPosY;

        for (int iY=0; iY<bestIy; iY++) {
          yN_child         = (_nY+bestIy-iY-1)/bestIy;
          for (int iC=0; iC<helpG.get_nC(); iC++) {
            int xN_child     = helpG.get_cuboid(iC).get_nX();
            int zN_child     = helpG.get_cuboid(iC).get_nY();
            T globPosX_child = helpG.get_cuboid(iC).get_globPosX();
            T globPosZ_child = helpG.get_cuboid(iC).get_globPosY();

            Cuboid3D<T> child(globPosX_child, globPosY_child, globPosZ_child,
                              _delta, xN_child, yN_child, zN_child);
            childrenC.push_back(child);

          }
          globPosY_child += yN_child*_delta;
        }
        return;
      }

      // spilt in four cuboid

      int restZ = rest/bestIy+1;

      int yN_child = 0;
      T globPosY_child = _globPosY;
      int splited_nY = (int) (_nY * (T)((bestIx*bestIz+restZ)*restY)/(T)p);
      CuboidGeometry2D<T> helpG0(_globPosX, _globPosZ, _delta, _nX, _nZ, bestIx*bestIz+restZ);

      for (int iY=0; iY<restY; iY++) {
        yN_child         = (splited_nY+restY-iY-1)/restY;
        for (int iC=0; iC<helpG0.get_nC(); iC++) {
          int xN_child     = helpG0.get_cuboid(iC).get_nX();
          int zN_child     = helpG0.get_cuboid(iC).get_nY();
          T globPosX_child = helpG0.get_cuboid(iC).get_globPosX();
          T globPosZ_child = helpG0.get_cuboid(iC).get_globPosY();

          Cuboid3D<T> child(globPosX_child, globPosY_child, globPosZ_child,
                            _delta, xN_child, yN_child, zN_child);
          childrenC.push_back(child);
        }
        globPosY_child += yN_child*_delta;
      }

      splited_nY = _nY - splited_nY;
      restZ = rest/bestIy;

      CuboidGeometry2D<T> helpG1(_globPosX, _globPosZ, _delta, _nX, _nZ, bestIx*bestIz+restZ);
      yN_child = 0;

      for (int iY=0; iY<bestIy-restY; iY++) {
        yN_child         = (splited_nY+bestIy-restY-iY-1)/(bestIy-restY);
        for (int iC=0; iC<helpG1.get_nC(); iC++) {
          int xN_child     = helpG1.get_cuboid(iC).get_nX();
          int zN_child     = helpG1.get_cuboid(iC).get_nY();
          T globPosX_child = helpG1.get_cuboid(iC).get_globPosX();
          T globPosZ_child = helpG1.get_cuboid(iC).get_globPosY();

          Cuboid3D<T> child(globPosX_child, globPosY_child, globPosZ_child,
                            _delta, xN_child, yN_child, zN_child);
          childrenC.push_back(child);
        }
        globPosY_child += yN_child*_delta;
      }
      return;
    }

    // add in y than in x direction
    else {
      int restX = rest%bestIx;
      // split in two cuboid
      if (restX==0) {
        int restZ = rest/bestIx;
        CuboidGeometry2D<T> helpG(_globPosZ, _globPosY, _delta, _nZ, _nY, bestIz*bestIy+restZ);


        int xN_child = 0;
        T globPosX_child = _globPosX;

        for (int iX=0; iX<bestIx; iX++) {
          xN_child         = (_nX+bestIx-iX-1)/bestIx;
          for (int iC=0; iC<helpG.get_nC(); iC++) {
            int zN_child     = helpG.get_cuboid(iC).get_nX();
            int yN_child     = helpG.get_cuboid(iC).get_nY();
            T globPosZ_child = helpG.get_cuboid(iC).get_globPosX();
            T globPosY_child = helpG.get_cuboid(iC).get_globPosY();

            Cuboid3D<T> child(globPosX_child, globPosY_child, globPosZ_child,
                              _delta, xN_child, yN_child, zN_child);
            childrenC.push_back(child);
          }
          globPosX_child += xN_child*_delta;
        }
        return;
      }

      // spilt in four cuboid

      int restZ = rest/bestIx+1;
      int xN_child = 0;
      T globPosX_child = _globPosX;
      int splited_nX = (int) (_nX * (T)((bestIz*bestIy+restZ)*restX)/(T)p);
      CuboidGeometry2D<T> helpG0(_globPosZ, _globPosY, _delta, _nZ, _nY, bestIz*bestIy+restZ);

      for (int iX=0; iX<restX; iX++) {
        xN_child         = (splited_nX+restX-iX-1)/restX;
        for (int iC=0; iC<helpG0.get_nC(); iC++) {
          int zN_child     = helpG0.get_cuboid(iC).get_nX();
          int yN_child     = helpG0.get_cuboid(iC).get_nY();
          T globPosZ_child = helpG0.get_cuboid(iC).get_globPosX();
          T globPosY_child = helpG0.get_cuboid(iC).get_globPosY();

          Cuboid3D<T> child(globPosX_child, globPosY_child, globPosZ_child,
                            _delta, xN_child, yN_child, zN_child);
          childrenC.push_back(child);
        }
        globPosX_child += xN_child*_delta;
      }

      splited_nX = _nX - splited_nX;
      restZ = rest/bestIx;
      CuboidGeometry2D<T> helpG1(_globPosZ, _globPosY, _delta, _nZ, _nY, bestIz*bestIy+restZ);
      xN_child = 0;

      for (int iX=0; iX<bestIx-restX; iX++) {
        xN_child         = (splited_nX+bestIx-restX-iX-1)/(bestIx-restX);
        for (int iC=0; iC<helpG1.get_nC(); iC++) {
          int zN_child     = helpG1.get_cuboid(iC).get_nX();
          int yN_child     = helpG1.get_cuboid(iC).get_nY();
          T globPosZ_child = helpG1.get_cuboid(iC).get_globPosX();
          T globPosY_child = helpG1.get_cuboid(iC).get_globPosY();

          Cuboid3D<T> child(globPosX_child, globPosY_child, globPosZ_child,
                            _delta, xN_child, yN_child, zN_child);
          childrenC.push_back(child);
        }
        globPosX_child += xN_child*_delta;
      }
      return;
    }
  }
}

}  // namespace olb

#endif
