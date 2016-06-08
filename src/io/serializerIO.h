/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Jonas Latt
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

#ifndef SERIALIZER_IO_H
#define SERIALIZER_IO_H

#include "core/serializer.h"

namespace olb {

template<typename T>
void serializer2ostr(DataSerializer<T> const& serializer, std::ostream* ostr, bool enforceUint=false);

template<typename T>
void istr2unSerializer(DataUnSerializer<T>& unSerializer, std::istream* istr, bool enforceUint=false);

template<typename T>
void saveData(Serializable<T> const& object, std::string fName, bool enforceUint=false);

template<typename T, typename SizeType>
void loadData(Serializable<T>& object, std::string fName, bool enforceUint=false);

template<typename T>
void saveAsciiData(Serializable<T> const& object, std::string fName);

} // namespace olb

#endif
