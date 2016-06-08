/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Mathias J. Krause
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

#ifndef BOUNDARY_CONDITIONS_3D_H
#define BOUNDARY_CONDITIONS_3D_H

#include <vector>
#include <map>
#include <cmath>
#include <assert.h>
#include "../../src/functors/analyticalF.h"

template <typename T>
class VelocityProfile : public AnalyticalF3D<T,T> {

public:
  VelocityProfile(int material = 0, T scale= T(1) ) : AnalyticalF3D<T,T>(3) {
    _scale = scale;
    _material = material;
    std::vector<T> help(3,0);

    /// List of Materials
    _materials.push_back(3);
    _materials.push_back(4);
    _materials.push_back(5);

    /// Setting values for the normals
    help[0] = 0.0;
    help[1] = 1.0;
    help[2] = 0.0;
    normalize(help);
    _material2normal[3] = help;
    help[0] =  2.5522;
    help[1] =  5.0294;
    help[2] = -1.5237;
    normalize(help);
    _material2normal[4] = help;
    help[0] = -1.5129;
    help[1] =  5.1039;
    help[2] = -2.8431;
    normalize(help);
    _material2normal[5] = help;

    /// Setting values for the centerpoints
    help[0] = 218.1250;
    help[1] = 249.9870;
    help[2] =  23.4818;
    _material2centerpoint[3] = help;
    help[0] = 205.3696;
    help[1] =  90.0103;
    help[2] =  34.6537;
    _material2centerpoint[4] = help;
    help[0] = 238.8403;
    help[1] =  90.0099;
    help[2] =  34.3228;
    _material2centerpoint[5] = help;
   
    /// Setting values for the radi
    _material2radius[3] = 11.2342;
    _material2radius[4] =  5.4686;
    _material2radius[5] =  5.8006;
  };

  /// Returns normal vector
  std::vector<T> getNormal(int material) {
    std::vector<T> temp;
    temp.push_back(_material2normal[material][0]);
    temp.push_back(_material2normal[material][1]);
    temp.push_back(_material2normal[material][2]);
    return temp;
  };

  /// Returns centerpoint vector
  std::vector<T> getCenterpoint(int material) {
    std::vector<T> temp;
    temp.push_back(_material2centerpoint[material][0]);
    temp.push_back(_material2centerpoint[material][1]);
    temp.push_back(_material2centerpoint[material][2]);
    return temp;
  };

  /// Returns radi
  T getRadius(int material) {
    return _material2radius[material];
  };

  /// Returns material no
  int getMaterial(int i) {
    return _materials[i];
  }

  /// Returns total number of outflow and inflow domains 
  int noMaterials() {
    return _materials.size();
  }

  /// Returns poiseuille velocity for a point within the circle and 0 for a point outside the circle for a given material  
  T getPoiseuilleFlow(int material, std::vector<T> physCoords) {
    T t = (physCoords[0]*_material2normal[material][0]
                +physCoords[1]*_material2normal[material][1]
                +physCoords[2]*_material2normal[material][2])
               - (_material2centerpoint[material][0]*_material2normal[material][0]
                  +_material2centerpoint[material][1]*_material2normal[material][1]
                  +_material2centerpoint[material][2]*_material2normal[material][2]);

    T ip1 = _material2centerpoint[material][0] + t*_material2normal[material][0],
           ip2 = _material2centerpoint[material][1] + t*_material2normal[material][1],
           ip3 = _material2centerpoint[material][2] + t*_material2normal[material][2];

    T r = std::pow(ip1-physCoords[0], 2.) + std::pow(ip2-physCoords[1], 2.) + std::pow(ip3-physCoords[2], 2.);
    if (std::sqrt(r) < _material2radius[material]) {
      return -(-1./std::pow(_material2radius[material], 2.) * r + 1.);
    }
    return 0;
  };

  std::vector<T> operator()(std::vector<T> x) {
    std::vector<T> y;
    y.push_back( getPoiseuilleFlow(_material,x)*getNormal(_material)[0]*_scale );
    y.push_back( getPoiseuilleFlow(_material,x)*getNormal(_material)[1]*_scale );
    y.push_back( getPoiseuilleFlow(_material,x)*getNormal(_material)[2]*_scale );
    return y;
  }

private:
  T _scale;
  int _material;
  /// Vector of materials. Each material repesents a different outflow or inflow domain
  std::vector<int> _materials;
  /// The normals of the outflow or inflow domains are stored here
  std::map<int, std::vector<T> > _material2normal;
  /// The centerpoints of the outflow or inflow domains are stored here
  std::map<int, std::vector<T> > _material2centerpoint;
  /// The radi of the outflow or inflow domains are stored here
  std::map<int, T > _material2radius;
  /// Normalizes a given vector
  void normalize(std::vector<T> &vec) {
    T norm = std::sqrt(vec[0]*vec[0] + vec[1]*vec[1] + vec[2]*vec[2]);
    vec[0] = vec[0]/norm;
    vec[1] = vec[1]/norm;
    vec[2] = vec[2]/norm;
  }
};

#endif // BOUNDARY_CONDITIONS_3D_H

