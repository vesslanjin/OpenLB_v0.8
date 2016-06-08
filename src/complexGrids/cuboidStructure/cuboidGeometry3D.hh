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
 * The description of a vector of 3D cuboid  -- generic implementation.
 */


#ifndef CUBOID_GEOMETRY_3D_HH
#define CUBOID_GEOMETRY_3D_HH

#include <vector>
#include <iostream>
#include <math.h>
#include <algorithm>
#include "cuboid3D.h"
#include "cuboidGeometry3D.h"


namespace olb {

////////////////////// Class CuboidGeometry3D /////////////////////////

template<typename T>
CuboidGeometry3D<T>::CuboidGeometry3D(T globPosX, T globPosY, T globPosZ,
                                      T delta, int nX, int nY, int nZ, int nC)
  : clout(std::cout,"CuboidGeometry3D") {
  //_cuboids.reserve(10000);
  reInit(globPosX, globPosY, globPosZ, delta, nX, nY, nZ, nC);
}

template<typename T>
void CuboidGeometry3D<T>::reInit(T globPosX, T globPosY, T globPosZ,
                                      T delta, int nX, int nY, int nZ, int nC) {
  _cuboids.clear();
  _motherCuboid = Cuboid3D<T>(globPosX, globPosY, globPosZ, delta, nX, nY, nZ);
  Cuboid3D<T> cuboid(0, 0, 0, 1, nX, nY, nZ);
  add(cuboid);
  split(0, nC);
}

template<typename T>
void CuboidGeometry3D<T>::set_motherC(T globPosX, T globPosY, T globPosZ,
                                      T delta, int nX, int nY, int nZ) {
  _motherCuboid = Cuboid3D<T>(globPosX, globPosY, globPosZ, delta, nX, nY, nZ);
}

template<typename T>
Cuboid3D<T>& CuboidGeometry3D<T>::get_cuboid(int i) {
  return _cuboids[i];
}

template<typename T>
Cuboid3D<T> const& CuboidGeometry3D<T>::get_cuboid(int i) const {
  return _cuboids[i];
}


template<typename T>
int CuboidGeometry3D<T>::get_nC() const { return _cuboids.size(); }

template<typename T>
T CuboidGeometry3D<T>::get_minRatio() const {
  T minRatio = 1.;
  for (unsigned i=0; i<_cuboids.size(); i++) {
    if((T)_cuboids[i].get_nX()/(T)_cuboids[i].get_nY() < minRatio) {
      minRatio = (T)_cuboids[i].get_nX()/(T)_cuboids[i].get_nY();
    }
    if((T)_cuboids[i].get_nY()/(T)_cuboids[i].get_nZ() < minRatio) {
      minRatio = (T)_cuboids[i].get_nY()/(T)_cuboids[i].get_nZ();
    }
    if((T)_cuboids[i].get_nZ()/(T)_cuboids[i].get_nX() < minRatio) {
      minRatio = (T)_cuboids[i].get_nZ()/(T)_cuboids[i].get_nX();
    }
  }
  return minRatio;
}

template<typename T>
T CuboidGeometry3D<T>::get_maxRatio() const {
  T maxRatio = 1.;
  for (unsigned i=0; i<_cuboids.size(); i++) {
    if((T)_cuboids[i].get_nX()/(T)_cuboids[i].get_nY() > maxRatio) {
      maxRatio = (T)_cuboids[i].get_nX()/(T)_cuboids[i].get_nY();
    }
    if((T)_cuboids[i].get_nY()/(T)_cuboids[i].get_nZ() > maxRatio) {
      maxRatio = (T)_cuboids[i].get_nY()/(T)_cuboids[i].get_nZ();
    }
    if((T)_cuboids[i].get_nZ()/(T)_cuboids[i].get_nX() > maxRatio) {
      maxRatio = (T)_cuboids[i].get_nZ()/(T)_cuboids[i].get_nX();
    }
  }
  return maxRatio;
}

template<typename T>
T CuboidGeometry3D<T>::get_minVolume() const {
  T minVolume = _cuboids[0].get_volume();
  for (unsigned i=0; i<_cuboids.size(); i++) {
    if(_cuboids[i].get_volume() < minVolume) {
      minVolume = _cuboids[i].get_volume();
    }
  }
  return minVolume;
}

template<typename T>
T CuboidGeometry3D<T>::get_maxVolume() const {
  T maxVolume = _cuboids[0].get_volume();
  for (unsigned i=0; i<_cuboids.size(); i++) {
    if(_cuboids[i].get_volume() > maxVolume) {
      maxVolume = _cuboids[i].get_volume();
    }
  }
  return maxVolume;
}

template<typename T>
int CuboidGeometry3D<T>::get_minNodes() const {
  int minNodes = _cuboids[0].get_nNodesVolume();
  for (unsigned i=0; i<_cuboids.size(); i++) {
    if(_cuboids[i].get_nNodesVolume() < minNodes) {
      minNodes = _cuboids[i].get_nNodesVolume();
    }
  }
  return minNodes;
}

template<typename T>
int CuboidGeometry3D<T>::get_maxNodes() const {
  int maxNodes = _cuboids[0].get_nNodesVolume();
  for (unsigned i=0; i<_cuboids.size(); i++) {
    if(_cuboids[i].get_nNodesVolume() > maxNodes) {
      maxNodes = _cuboids[i].get_nNodesVolume();
    }
  }
  return maxNodes;
}

template<typename T>
T CuboidGeometry3D<T>::get_minDelta() const {
  T minDelta = _cuboids[0].get_delta();
  for (unsigned i=0; i<_cuboids.size(); i++) {
    if(_cuboids[i].get_delta() < minDelta) {
      minDelta = _cuboids[i].get_delta();
    }
  }
  return minDelta;
}

template<typename T>
T CuboidGeometry3D<T>::get_maxDelta() const {
  T maxDelta = _cuboids[0].get_delta();
  for (unsigned i=0; i<_cuboids.size(); i++) {
    if(_cuboids[i].get_delta() > maxDelta) {
      maxDelta = _cuboids[i].get_delta();
    }
  }
  return maxDelta;
}

template<typename T>
Cuboid3D<T> CuboidGeometry3D<T>::get_motherC() const {

  /*Cuboid3D<T> found;
  if(_cuboids.size()==0) {
      found.init(0, 0, 0, 0, 0, 0, 0);
      return found;
  }

  T delta = _cuboids[0].get_delta();
  T globPosXmin = _cuboids[0].get_globPosX();
  T globPosYmin = _cuboids[0].get_globPosY();
  T globPosZmin = _cuboids[0].get_globPosZ();
  T globPosXmax = _cuboids[0].get_globPosX() + delta*(_cuboids[0].get_nX()-1);
  T globPosYmax = _cuboids[0].get_globPosY() + delta*(_cuboids[0].get_nY()-1);
  T globPosZmax = _cuboids[0].get_globPosZ() + delta*(_cuboids[0].get_nZ()-1);

  for (unsigned i=1; i<_cuboids.size(); i++) {
      if(delta > _cuboids[i].get_delta() ) {
          delta = _cuboids[i].get_delta();
      }
      if(globPosXmin > _cuboids[i].get_globPosX() ) {
          globPosXmin = _cuboids[i].get_globPosX();
      }
      if(globPosYmin > _cuboids[i].get_globPosY() ) {
          globPosYmin = _cuboids[i].get_globPosY();
      }
      if(globPosZmin > _cuboids[i].get_globPosZ() ) {
          globPosZmin = _cuboids[i].get_globPosZ();
      }

      if(globPosXmax < _cuboids[i].get_globPosX()
                          + delta*(_cuboids[i].get_nX()-1)) {
          globPosXmax = _cuboids[i].get_globPosX()
                          + delta*(_cuboids[i].get_nX()-1);
      }
      if(globPosYmax < _cuboids[i].get_globPosY()
                          + delta*(_cuboids[i].get_nY()-1)) {
          globPosYmax = _cuboids[i].get_globPosY()
                          + delta*(_cuboids[i].get_nY()-1);
      }
      if(globPosZmax < _cuboids[i].get_globPosZ()
                          + delta*(_cuboids[i].get_nZ()-1)) {
          globPosZmax = _cuboids[i].get_globPosZ()
                          + delta*(_cuboids[i].get_nZ()-1);
      }
  }
  int nX = int(ceil((globPosXmax - globPosXmin)/delta))+1;
  int nY = int(ceil((globPosYmax - globPosYmin)/delta))+1;
  int nZ = int(ceil((globPosZmax - globPosZmin)/delta))+1;

  found.init(globPosXmin, globPosYmin, globPosZmin, delta, nX, nY, nZ);

  return found;*/
  return _motherCuboid;
}

template<typename T>
void CuboidGeometry3D<T>::printStatistics() const {
  clout << "---Cuboid Stucture Statistics---" << std::endl;
  clout << " Number of Cuboids: " << "\t" << get_nC() << std::endl;
  clout << " Delta (min): " << "\t" << "\t" << get_minDelta() << std::endl;
  clout << "       (max): " << "\t" << "\t" << get_maxDelta() << std::endl;
  clout << " Ratio (min): " << "\t" << "\t" << get_minRatio() << std::endl;
  clout << "       (max): " << "\t" << "\t" << get_maxRatio() << std::endl;
  clout << " Nodes (min): " << "\t" << "\t" << get_minNodes() << std::endl;
  clout << "       (max): " << "\t" << "\t" << get_maxNodes() << std::endl;
  clout << "--------------------------------" << std::endl;
}

template<typename T>
int CuboidGeometry3D<T>::get_iC(T globX, T globY, T globZ, int offset) const {
  unsigned i;
  for (i=0; i<_cuboids.size(); i++) {
    if (_cuboids[i].checkPoint(globX, globY, globZ, offset)) return (int)i;
  }
  return (int)i;
}

template<typename T>
int CuboidGeometry3D<T>::get_iC(T globX, T globY, T globZ,
                                int orientationX, int orientationY, int orientationZ) const {
  unsigned i;
  for (i=0; i<_cuboids.size(); i++) {
    if (_cuboids[i].checkPoint(globX, globY, globZ) &&
        _cuboids[i].checkPoint(globX + orientationX/_cuboids[i].get_delta(),
                               globY + orientationY/_cuboids[i].get_delta(),
                               globZ + orientationZ/_cuboids[i].get_delta())) {
      return (int)i;
    }
  }
  return (int)i;
}

template<typename T>
void CuboidGeometry3D<T>::add(Cuboid3D<T> cuboid) {

  _cuboids.push_back(cuboid);
}

template<typename T>
void CuboidGeometry3D<T>::remove(int iC) {

  _cuboids.erase(_cuboids.begin() + iC);
}

template<typename T>
void CuboidGeometry3D<T>::remove(olb::BlockGeometry3D& blockGeometry) {

  std::vector<Cuboid3D<T> > cuboids;
  unsigned size = _cuboids.size();

  std::vector<bool> allZero;
  for (unsigned i=0; i < size; i++) {
    allZero.push_back(1);
    for (int iX=0; iX<_cuboids[i].get_nX(); iX++) {
      for (int iY=0; iY<_cuboids[i].get_nY(); iY++) {
        for (int iZ=0; iZ<_cuboids[i].get_nZ(); iZ++) {
          if (blockGeometry.getMaterial(_cuboids[i].get_globPosX()+iX,
                                        _cuboids[i].get_globPosY()+iY,_cuboids[i].get_globPosZ()+iZ)!=0 ) allZero[i] = 0;
        }
      }
    }
  }
  for (unsigned i=0; i<size; i++) {
    if (!allZero[i] ) cuboids.push_back(_cuboids[i]);
  }
  _cuboids.clear();
  for (unsigned i=0; i<cuboids.size(); i++) {
    _cuboids.push_back(cuboids[i]);
  }
}

template<typename T>
void CuboidGeometry3D<T>::shrink(olb::BlockGeometry3D& blockGeometry) {
  unsigned i;
  int iX,iY,iZ,newX,newY,newZ,maxX,maxY,maxZ;
  bool planeEmpty=true;
  for (i=0; i<_cuboids.size(); i++) {
    // check each of the planes of the cuboid iteratively, if it is empty
    planeEmpty=true;
    for(iX=0; iX<_cuboids[i].get_nX() && planeEmpty; iX++) {
      for(iY=0; iY<_cuboids[i].get_nY() && planeEmpty; iY++) {
        for(iZ=0; iZ<_cuboids[i].get_nZ() && planeEmpty; iZ++) {
          if (blockGeometry.getMaterial(_cuboids[i].get_globPosX()+iX,
                                        _cuboids[i].get_globPosY()+iY,_cuboids[i].get_globPosZ()+iZ)!=0 ) planeEmpty=false;
        }
      }
    }
    newX = iX-1;

    planeEmpty=true;
    for(iY=0; iY<_cuboids[i].get_nY() && planeEmpty; iY++) {
      for(iX=0; iX<_cuboids[i].get_nX() && planeEmpty; iX++) {
        for(iZ=0; iZ<_cuboids[i].get_nZ() && planeEmpty; iZ++) {
          if (blockGeometry.getMaterial(_cuboids[i].get_globPosX()+iX,
                                        _cuboids[i].get_globPosY()+iY,_cuboids[i].get_globPosZ()+iZ)!=0 ) planeEmpty=false;
        }
      }
    }
    newY = iY-1;

    planeEmpty=true;
    for(iZ=0; iZ<_cuboids[i].get_nZ() && planeEmpty; iZ++) {
      for(iY=0; iY<_cuboids[i].get_nY() && planeEmpty; iY++) {
        for(iX=0; iX<_cuboids[i].get_nX() && planeEmpty; iX++) {
          if (blockGeometry.getMaterial(_cuboids[i].get_globPosX()+iX,
                                        _cuboids[i].get_globPosY()+iY,_cuboids[i].get_globPosZ()+iZ)!=0 ) planeEmpty=false;
        }
      }
    }
    newZ = iZ-1;

    planeEmpty=true;
    for(iX=_cuboids[i].get_nX() - 1 ; iX>=0 && planeEmpty; iX--) {
      for(iY=_cuboids[i].get_nY() - 1; iY>=0 && planeEmpty; iY--) {
        for(iZ=_cuboids[i].get_nZ() - 1 ; iZ>=0 && planeEmpty; iZ--) {
          if (blockGeometry.getMaterial(_cuboids[i].get_globPosX()+iX,
                                        _cuboids[i].get_globPosY()+iY,_cuboids[i].get_globPosZ()+iZ)!=0 ) planeEmpty=false;
        }
      }
    }
    maxX = iX+1;

    planeEmpty=true;
    for(iY=_cuboids[i].get_nY() - 1; iY>=0 && planeEmpty; iY--) {
      for(iX=_cuboids[i].get_nX() - 1; iX>=0 && planeEmpty; iX--) {
        for(iZ=_cuboids[i].get_nZ() - 1; iZ>=0 && planeEmpty; iZ--) {
          if (blockGeometry.getMaterial(_cuboids[i].get_globPosX()+iX,
                                        _cuboids[i].get_globPosY()+iY,_cuboids[i].get_globPosZ()+iZ)!=0 ) planeEmpty=false;
        }
      }
    }
    maxY = iY+1;

    planeEmpty=true;
    for(iZ=_cuboids[i].get_nZ() -1; iZ>=0 && planeEmpty; iZ--) {
      for(iY=_cuboids[i].get_nY() + 1; iY>=0 && planeEmpty; iY--) {
        for(iX=_cuboids[i].get_nX() + 1; iX>=0 && planeEmpty; iX--) {
          if (blockGeometry.getMaterial(_cuboids[i].get_globPosX()+iX,
                                        _cuboids[i].get_globPosY()+iY,_cuboids[i].get_globPosZ()+iZ)!=0 ) planeEmpty=false;
        }
      }
    }
    maxZ = iZ+1;

    _cuboids[i].resize(newX, newY, newZ, maxX-newX+1, maxY-newY+1, maxZ-newZ+1);
  }
}

template<typename T>
void CuboidGeometry3D<T>::remove(olb::SuperGeometry3D& superGeometry) {

  std::vector<Cuboid3D<T> > cuboids;
  unsigned size = _cuboids.size();

  std::vector<bool> allZero;
  for (unsigned i=0; i < size; i++) {
    allZero.push_back(1);
    for (int iX=0; iX<_cuboids[i].get_nX(); iX++) {
      for (int iY=0; iY<_cuboids[i].get_nY(); iY++) {
        for (int iZ=0; iZ<_cuboids[i].get_nZ(); iZ++) {
          if (superGeometry.getMaterial(_cuboids[i].get_globPosX()+iX,
                                        _cuboids[i].get_globPosY()+iY,_cuboids[i].get_globPosZ()+iZ)!=0 ) allZero[i] = 0;
        }
      }
    }
  }
  for (unsigned i=0; i<size; i++) {
    if (!allZero[i] ) cuboids.push_back(_cuboids[i]);
  }
  _cuboids.clear();
  for (unsigned i=0; i<cuboids.size(); i++) {
    _cuboids.push_back(cuboids[i]);
  }
}

template<typename T>
void CuboidGeometry3D<T>::shrink(olb::SuperGeometry3D& superGeometry) {
  unsigned i;
  int iX,iY,iZ,newX,newY,newZ,maxX,maxY,maxZ;
  bool planeEmpty=true;
  for (i=0; i<_cuboids.size(); i++) {
    // check each of the planes of the cuboid iteratively, if it is empty
    planeEmpty=true;
    for(iX=0; iX<_cuboids[i].get_nX() && planeEmpty; iX++) {
      for(iY=0; iY<_cuboids[i].get_nY() && planeEmpty; iY++) {
        for(iZ=0; iZ<_cuboids[i].get_nZ() && planeEmpty; iZ++) {
          if (superGeometry.getMaterial(_cuboids[i].get_globPosX()+iX,
                                        _cuboids[i].get_globPosY()+iY,_cuboids[i].get_globPosZ()+iZ)!=0 ) planeEmpty=false;
        }
      }
    }
    newX = iX-1;

    planeEmpty=true;
    for(iY=0; iY<_cuboids[i].get_nY() && planeEmpty; iY++) {
      for(iX=0; iX<_cuboids[i].get_nX() && planeEmpty; iX++) {
        for(iZ=0; iZ<_cuboids[i].get_nZ() && planeEmpty; iZ++) {
          if (superGeometry.getMaterial(_cuboids[i].get_globPosX()+iX,
                                        _cuboids[i].get_globPosY()+iY,_cuboids[i].get_globPosZ()+iZ)!=0 ) planeEmpty=false;
        }
      }
    }
    newY = iY-1;

    planeEmpty=true;
    for(iZ=0; iZ<_cuboids[i].get_nZ() && planeEmpty; iZ++) {
      for(iY=0; iY<_cuboids[i].get_nY() && planeEmpty; iY++) {
        for(iX=0; iX<_cuboids[i].get_nX() && planeEmpty; iX++) {
          if (superGeometry.getMaterial(_cuboids[i].get_globPosX()+iX,
                                        _cuboids[i].get_globPosY()+iY,_cuboids[i].get_globPosZ()+iZ)!=0 ) planeEmpty=false;
        }
      }
    }
    newZ = iZ-1;

    planeEmpty=true;
    for(iX=_cuboids[i].get_nX() - 1 ; iX>=0 && planeEmpty; iX--) {
      for(iY=_cuboids[i].get_nY() - 1; iY>=0 && planeEmpty; iY--) {
        for(iZ=_cuboids[i].get_nZ() - 1 ; iZ>=0 && planeEmpty; iZ--) {
          if (superGeometry.getMaterial(_cuboids[i].get_globPosX()+iX,
                                        _cuboids[i].get_globPosY()+iY,_cuboids[i].get_globPosZ()+iZ)!=0 ) planeEmpty=false;
        }
      }
    }
    maxX = iX+1;

    planeEmpty=true;
    for(iY=_cuboids[i].get_nY() - 1; iY>=0 && planeEmpty; iY--) {
      for(iX=_cuboids[i].get_nX() - 1; iX>=0 && planeEmpty; iX--) {
        for(iZ=_cuboids[i].get_nZ() - 1; iZ>=0 && planeEmpty; iZ--) {
          if (superGeometry.getMaterial(_cuboids[i].get_globPosX()+iX,
                                        _cuboids[i].get_globPosY()+iY,_cuboids[i].get_globPosZ()+iZ)!=0 ) planeEmpty=false;
        }
      }
    }
    maxY = iY+1;

    planeEmpty=true;
    for(iZ=_cuboids[i].get_nZ() -1; iZ>=0 && planeEmpty; iZ--) {
      for(iY=_cuboids[i].get_nY() + 1; iY>=0 && planeEmpty; iY--) {
        for(iX=_cuboids[i].get_nX() + 1; iX>=0 && planeEmpty; iX--) {
          if (superGeometry.getMaterial(_cuboids[i].get_globPosX()+iX,
                                        _cuboids[i].get_globPosY()+iY,_cuboids[i].get_globPosZ()+iZ)!=0 ) planeEmpty=false;
        }
      }
    }
    maxZ = iZ+1;

    _cuboids[i].resize(newX, newY, newZ, maxX-newX+1, maxY-newY+1, maxZ-newZ+1);
  }
}


template<typename T>
void CuboidGeometry3D<T>::split(int iC, int p) {

  Cuboid3D<T> temp(_cuboids[iC].get_globPosX(),_cuboids[iC].get_globPosY(),
                   _cuboids[iC].get_globPosZ(),  _cuboids[iC].get_delta(),
                   _cuboids[iC].get_nX(), _cuboids[iC].get_nY(), _cuboids[iC].get_nZ());
  temp.divide(p, _cuboids);
  remove(iC);
}

template<typename T>
void CuboidGeometry3D<T>::get_cuboidNeighbourhood(int cuboid, std::vector<int>& neighbours, int offset) {
  for (int iC=0; iC<get_nC(); iC++) {
    if(cuboid == iC) continue;
    T globX = get_cuboid(iC).get_globPosX();
    T globY = get_cuboid(iC).get_globPosY();
    T globZ = get_cuboid(iC).get_globPosZ();
    T nX = get_cuboid(iC).get_nX();
    T nY = get_cuboid(iC).get_nY();
    T nZ = get_cuboid(iC).get_nZ();
    if(get_cuboid(cuboid).checkInters(globX, globX+nX, globY, globY+nY, globZ, globZ+nZ, offset)) {
      neighbours.push_back(iC);
    }
  }
}

}  // namespace olb

#endif
