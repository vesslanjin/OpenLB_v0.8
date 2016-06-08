/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Mathias Krause
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


#include <vector>
#include <map>
#include "loadBalancer.h"
#include "olbDebug.h"

namespace olb {

loadBalancer::loadBalancer(int rank, int size, int globChunkSize, int offset) {
  init_chunkD(rank, size, globChunkSize, offset);
}

void loadBalancer::init_chunkD(int rank, int size, int globChunkSize, int offset) {

  OLB_PRECONDITION(rank>=0 && size>=1 && offset>=0)
  OLB_PRECONDITION(size<=globChunkSize &&  rank<size);

  // nice way to calculate # of chunks per processor
  locChunkSize = (globChunkSize+size-rank-1)/size;
  if (rank+1 <= globChunkSize-(globChunkSize/size)*size) {
    firstGlobNum = globChunkSize/size * rank + rank + offset;
    lastGlobNum  = firstGlobNum + locChunkSize - 1;
  }
  else {
    firstGlobNum = globChunkSize/size * rank + globChunkSize - (globChunkSize/size)*size + offset;
    lastGlobNum  = firstGlobNum + locChunkSize - 1;
  }
  for (int i=0; i<locChunkSize; i++) {
    _loc[firstGlobNum + i] = i;
    _glob.push_back(firstGlobNum + i);
  }
  int temp = offset;
  for (int iRank=0; iRank<size; iRank++) {
    int iLocChunkSize = (globChunkSize+size-iRank-1)/size;
    for (int i=0; i<iLocChunkSize; i++) {
      _rank[temp] = iRank;
      temp++;
    }
  }
}

int loadBalancer::get_locChunkSize() const {
  return locChunkSize;
}

int loadBalancer::get_firstGlobNum() const {
  return firstGlobNum;
}

int loadBalancer::get_lastGlobNum() const {
  return lastGlobNum;
}

int loadBalancer::loc(const int& glob) {
  return _loc[glob];
}

int loadBalancer::loc(int glob) const {
  std::map<int,int>::const_iterator iter = _loc.find(glob);
  return iter->second;
}

int loadBalancer::glob(int loc) const {
  return _glob[loc];
}

int loadBalancer::rank(const int& glob) {
  return _rank[glob];
}

int loadBalancer::rank(int glob) const {
  std::map<int,int>::const_iterator iter = _rank.find(glob);
  return iter->second;
}

int loadBalancer::size() {
  return locChunkSize;
}

int loadBalancer::size() const {
  return locChunkSize;
}

void loadBalancer::debug() const {
  for(unsigned i = 0; i < _glob.size(); i++) {
    std::cout << "glob[" << i << "]=" << _glob[i] << std::endl;
  }
  for(std::map<int,int>::const_iterator it = _loc.begin(); it != _loc.end();
      it++) {
    std::cout << "loc[" << (*it).first << "]=" << (*it).second << std::endl;
  }
  for(std::map<int,int>::const_iterator it = _rank.begin(); it != _rank.end();
      it++) {
    std::cout << "rank[" << (*it).first << "]=" << (*it).second << std::endl;
  }
}

}  // namespace olb
