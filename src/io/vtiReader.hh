/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2012 Thomas Henn
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


#ifndef VTI_READER_HH
#define VTI_READER_HH

#include "vtiReader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <math.h>
#include <cassert>

namespace olb {
using namespace std;

template<typename T>
void VTIreader3D<T>::printInfo() {
	clout << "Origin: " << _x0 << " "  << _y0 << " "  << _z0 << endl;
	clout << "Extend: " << _x << " "  << _y << " "  << _z << endl;
	clout << "Spacing: " << _delta << endl;
}

template<typename T>
VTIreader3D<T>::VTIreader3D(const std::string& fName ) : XMLreader(fName) {
	// get _x, _y, _z
	int x, y, z;
	stringstream stream_val_0((*this)["ImageData"].getAttribute("WholeExtent"));
	stream_val_0 >> x >> _x >> y >> _y >> z >> _z;
	_x = _x-x+1; _y = _y-y+1; _z = _z-z+1;

	// get _delta
	stringstream stream_val_1((*this)["ImageData"].getAttribute("Spacing"));
	stream_val_1 >> _delta;

	stringstream stream_val_2((*this)["ImageData"].getAttribute("Origin"));
	stream_val_2 >> _x0 >> _y0 >> _z0;
}

template<typename T>
VTIreader3D<T>::~VTIreader3D(){}

template<typename T>
void VTIreader3D<T>::getCuboid(Cuboid3D<T>& cuboid) {
	cuboid.init(_x0, _y0, _z0, _delta, _x, _y, _z);
}

template<typename T>
void VTIreader3D<T>::getCuboids(std::vector<Cuboid3D<T>* >& cuboids) {
	std::vector<XMLreader*>::const_iterator it;
	int i=0;
	for (it = (*this)["ImageData"].begin(); it != (*this)["ImageData"].end(); it++) {
		if ((*it)->getName() == "Piece") {
			++i;
			stringstream extstr((*it)->getAttribute("Extent"));
			int extents[6];
			for (int i=0; i<6; i++) {
				extstr >> extents[i];
			}
			Cuboid3D<T>* cuboid = new Cuboid3D<T>(extents[0], extents[2], extents[4], _delta, extents[1]-extents[0]+1, extents[3]-extents[2]+1, extents[5]-extents[4]+1);
			cuboids.push_back(cuboid);
		}
	}
}

template<typename T>
void VTIreader3D<T>::getScalarMultiPieceData(std::vector<const ScalarFieldBase3D<T>* >& bases, const std::string dName) {
	std::vector<XMLreader*>::const_iterator it;
	for (it = (*this)["ImageData"].begin(); it != (*this)["ImageData"].end(); it++) {
		if ((*it)->getName() == "Piece") {
			stringstream extstr((*it)->getAttribute("Extent"));
			int extents[6];
			for (int i=0; i<6; i++) {
				extstr >> extents[i];
			}
			std::vector<XMLreader*>::const_iterator it2;
			for (it2 = (*it)->operator[]("PointData").begin(); it2 != (*it)->operator[]("PointData").end(); it2++) {
				if ((*it2)->getAttribute("Name") == dName && (*it2)->getName() == "DataArray"){
					ScalarField3D<T>* tmp = new ScalarField3D<T>(extents[1]-extents[0]+1, extents[3]-extents[2]+1, extents[5]-extents[4]+1);
					tmp->construct();				std::string data_str;
					if ((*it2)->read(data_str)) {
						stringstream stream_val(data_str);
						for (int iz = 0; iz < extents[5]-extents[4]+1; iz++) {
							for (int iy = 0; iy < extents[3]-extents[2]+1; iy++) {
								for (int ix = 0; ix < extents[1]-extents[0]+1; ix++) {
									T tmp2;
									stream_val >> tmp2;
									tmp->get(ix, iy, iz) = tmp2;
								}
							}
						}
					}
					bases.push_back(tmp);
				}
			}
		}
	}
}

template<typename T>
void VTIreader3D<T>::getVectorMultiPieceData(std::vector<const TensorFieldBase3D<T, 3>* >& bases, const std::string dName) {
	std::vector<XMLreader*>::const_iterator it;
	for (it = (*this)["ImageData"].begin(); it != (*this)["ImageData"].end(); it++) {
		if ((*it)->getName() == "Piece") {
			stringstream extstr((*it)->getAttribute("Extent"));
			int extents[6];
			for (int i=0; i<6; i++) {
				extstr >> extents[i];
			}
			std::vector<XMLreader*>::const_iterator it2;
			for (it2 = (*it)->operator[]("PointData").begin(); it2 != (*it)->operator[]("PointData").end(); it2++) {
				if ((*it2)->getAttribute("Name") == dName && (*it2)->getName() == "DataArray"){
					TensorField3D<T, 3>* tmp = new TensorField3D<T, 3>(extents[1]-extents[0]+1, extents[3]-extents[2]+1, extents[5]-extents[4]+1);
					tmp->construct();
					std::string data_str;
					if ((*it2)->read(data_str)) {
						stringstream stream_val(data_str);
						for (int iz = 0; iz < extents[5]-extents[4]+1; iz++) {
							for (int iy = 0; iy < extents[3]-extents[2]+1; iy++) {
								for (int ix = 0; ix < extents[1]-extents[0]+1; ix++) {
									for (int i=0; i < 3; i++) {
										T tmpval;
										stream_val >> tmpval;
										tmp->get(ix, iy, iz)[i] = tmpval;
									}
								}
							}
						}
					}
					bases.push_back(tmp);
				}
			}
		}
	}
}

template<typename T>
bool VTIreader3D<T>::getScalarData(ScalarField3D<T>* base, const std::string dName) {
	std::vector<XMLreader*>::const_iterator it;
	for (it = (*this)["ImageData"]["Piece"]["PointData"].begin(); it != (*this)["ImageData"]["Piece"]["PointData"].end(); it++) {
		if ((*it)->getAttribute("Name") == dName && (*it)->getName() == "DataArray"){
			ScalarField3D<T>* tmp = new ScalarField3D<T>(_x, _y, _z);
			tmp->construct();
			std::string data_str;
			if ((*it)->read(data_str)) {
				stringstream stream_val(data_str);
				for (int iz = 0; iz < _z; iz++) {
					for (int iy = 0; iy < _y; iy++) {
						for (int ix = 0; ix < _x; ix++) {
							T tmp2;
							stream_val >> tmp2;
							tmp->get(ix, iy, iz) = tmp2;
						}
					}
				}
			}
			base->swap(*tmp);
			delete tmp;
			return true;
		}
	}
	return false;
}

template<typename T>
bool VTIreader3D<T>::getVectorData(TensorField3D<T, 3>* base, const std::string dName) {
	std::vector<XMLreader*>::const_iterator it;
	for (it = (*this)["ImageData"]["Piece"]["PointData"].begin(); it != (*this)["ImageData"]["Piece"]["PointData"].end(); it++) {
		if ((*it)->getAttribute("Name") == dName && (*it)->getName() == "DataArray"){
			TensorField3D<T, 3>* tmp = new TensorField3D<T, 3>(_x, _y, _z);
			tmp->construct();
			std::string data_str;
			if ((*it)->read(data_str)) {
				stringstream stream_val(data_str);
				for (int iz = 0; iz < _z; iz++) {
					for (int iy = 0; iy < _y; iy++) {
						for (int ix = 0; ix < _x; ix++) {
							for (int i=0; i < 3; i++) {
								T tmpval;
								stream_val >> tmpval;
								tmp->get(ix, iy, iz)[i] = tmpval;
							}
						}
					}
				}
			}
			base->swap(*tmp);
			delete tmp;
			return true;
		}
	}
	return false;
}


// ************************************ 2D ********************************************** //


template<typename T>
void VTIreader2D<T>::printInfo() {
	clout << "Origin: " << _x0 << " "  << _y0 << endl;
	clout << "Extend: " << _x  << " "  << _y  << endl;
	clout << "Spacing: " << _delta << endl;
}

template<typename T>
VTIreader2D<T>::VTIreader2D(const std::string& fName ) : XMLreader(fName) {
	// get _x, _y, _z
	int x, y, z;
	stringstream stream_val_0((*this)["ImageData"].getAttribute("WholeExtent"));
	stream_val_0 >> x >> _x >> y >> _y >> z >> _z;
	_x = _x-x+1; _y = _y-y+1; _z = _z-z+1;

	// get _delta
	stringstream stream_val_1((*this)["ImageData"].getAttribute("Spacing"));
	stream_val_1 >> _delta;

	stringstream stream_val_2((*this)["ImageData"].getAttribute("Origin"));
	stream_val_2 >> _x0 >> _y0 >> _z0;
}

template<typename T>
VTIreader2D<T>::~VTIreader2D(){}

template<typename T>
void VTIreader2D<T>::getCuboid(Cuboid2D<T>& cuboid) {
	cuboid.init(_x0, _y0, _delta, _x, _y);
}

template<typename T>
void VTIreader2D<T>::getCuboids(std::vector<Cuboid2D<T>* >& cuboids) {
	std::vector<XMLreader*>::const_iterator it;
	int i=0;
	for (it = (*this)["ImageData"].begin(); it != (*this)["ImageData"].end(); it++) {
		if ((*it)->getName() == "Piece") {
			++i;
			stringstream extstr((*it)->getAttribute("Extent"));
			int extents[6];
			for (int i=0; i<6; i++) {
				extstr >> extents[i];
			}
			Cuboid2D<T>* cuboid = new Cuboid2D<T>(extents[0], extents[2], _delta, extents[1]-extents[0]+1, extents[3]-extents[2]+1);
			cuboids.push_back(cuboid);
		}
	}
}

template<typename T>
void VTIreader2D<T>::getScalarMultiPieceData(std::vector<const ScalarFieldBase2D<T>* >& bases, const std::string dName) {
	std::vector<XMLreader*>::const_iterator it;
	for (it = (*this)["ImageData"].begin(); it != (*this)["ImageData"].end(); it++) {
		if ((*it)->getName() == "Piece") {
			stringstream extstr((*it)->getAttribute("Extent"));
			int extents[6];
			for (int i=0; i<6; i++) {
				extstr >> extents[i];
			}
			std::vector<XMLreader*>::const_iterator it2;
			for (it2 = (*it)->operator[]("PointData").begin(); it2 != (*it)->operator[]("PointData").end(); it2++) {
				if ((*it2)->getAttribute("Name") == dName && (*it2)->getName() == "DataArray"){
					ScalarField2D<T>* tmp = new ScalarField2D<T>(extents[1]-extents[0]+1, extents[3]-extents[2]+1);
					tmp->construct();
					std::string data_str;
					if ((*it2)->read(data_str)) {
						stringstream stream_val(data_str);
						for (int iz = 0; iz < extents[5]-extents[4]+1; iz++) {
							for (int iy = 0; iy < extents[3]-extents[2]+1; iy++) {
								for (int ix = 0; ix < extents[1]-extents[0]+1; ix++) {
									T tmp2;
									stream_val >> tmp2;
									tmp->get(ix, iy) = tmp2;
								}
							}
						}
					}
					bases.push_back(tmp);
				}
			}
		}
	}
}

template<typename T>
void VTIreader2D<T>::getVectorMultiPieceData(std::vector<const TensorFieldBase2D<T, 2>* >& bases, const std::string dName) {
	std::vector<XMLreader*>::const_iterator it;
	for (it = (*this)["ImageData"].begin(); it != (*this)["ImageData"].end(); it++) {
		if ((*it)->getName() == "Piece") {
			stringstream extstr((*it)->getAttribute("Extent"));
			int extents[6];
			for (int i=0; i<6; i++) {
				extstr >> extents[i];
			}
			std::vector<XMLreader*>::const_iterator it2;
			for (it2 = (*it)->operator[]("PointData").begin(); it2 != (*it)->operator[]("PointData").end(); it2++) {
				if ((*it2)->getAttribute("Name") == dName && (*it2)->getName() == "DataArray"){
					TensorField2D<T, 2>* tmp = new TensorField2D<T, 2>(extents[1]-extents[0]+1, extents[3]-extents[2]+1);
					tmp->construct();
					std::string data_str;
					if ((*it2)->read(data_str)) {
						stringstream stream_val(data_str);
						for (int iz = 0; iz < extents[5]-extents[4]+1; iz++) {
							for (int iy = 0; iy < extents[3]-extents[2]+1; iy++) {
								for (int ix = 0; ix < extents[1]-extents[0]+1; ix++) {
									T tmpval;
									for (int i=0; i < 2; i++) {
										stream_val >> tmpval;
										tmp->get(ix, iy)[i] = tmpval;
									}
									stream_val >> tmpval;
								}
							}
						}
					}
					bases.push_back(tmp);
				}
			}
		}
	}
}

template<typename T>
bool VTIreader2D<T>::getScalarData(ScalarField2D<T>* base, const std::string dName) {
	std::vector<XMLreader*>::const_iterator it;
	for (it = (*this)["ImageData"]["Piece"]["PointData"].begin(); it != (*this)["ImageData"]["Piece"]["PointData"].end(); it++) {
		if ((*it)->getAttribute("Name") == dName && (*it)->getName() == "DataArray"){
			ScalarField2D<T>* tmp = new ScalarField2D<T>(_x, _y);
			tmp->construct();
			std::string data_str;
			if ((*it)->read(data_str)) {
				stringstream stream_val(data_str);
				for (int iz = 0; iz < _z; iz++) {
					for (int iy = 0; iy < _y; iy++) {
						for (int ix = 0; ix < _x; ix++) {
							T tmp2;
							stream_val >> tmp2;
							tmp->get(ix, iy) = tmp2;
						}
					}
				}
			}
			base->swap(*tmp);
			delete tmp;
			return true;
		}
	}
	return false;
}

template<typename T>
bool VTIreader2D<T>::getVectorData(TensorField2D<T, 2>* base, const std::string dName) {
	std::vector<XMLreader*>::const_iterator it;
	for (it = (*this)["ImageData"]["Piece"]["PointData"].begin(); it != (*this)["ImageData"]["Piece"]["PointData"].end(); it++) {
		if ((*it)->getAttribute("Name") == dName && (*it)->getName() == "DataArray"){
			TensorField2D<T, 2>* tmp = new TensorField2D<T, 2>(_x, _y);
			tmp->construct();
			std::string data_str;
			if ((*it)->read(data_str)) {
				stringstream stream_val(data_str);
				for (int iz = 0; iz < _z; iz++) {
					for (int iy = 0; iy < _y; iy++) {
						for (int ix = 0; ix < _x; ix++) {
							T tmpval;
							for (int i=0; i < 2; i++) {
								stream_val >> tmpval;
								tmp->get(ix, iy)[i] = tmpval;
							}
							stream_val >> tmpval;
						}
					}
				}
			}
			base->swap(*tmp);
			delete tmp;
			return true;
		}
	}
	return false;
}


}
#endif
