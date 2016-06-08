/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007, 2008 Jonas Latt
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
 * Statistics for MultiBlocks -- header file.
 */
#ifndef MULTI_BLOCK_STATISTICS_H
#define MULTI_BLOCK_STATISTICS_H

#include "core/postProcessing.h"


namespace olb {

template<typename T>
class MultiBlockReductor : public Reductor<T> {
public:
  virtual void subscribeSum(T& element);
  virtual void subscribeAverage(size_t const& weight, T& element);
  virtual void subscribeMin(T& element);
  virtual void subscribeMax(T& element);
public:
  MultiBlockReductor();
  void startNewSubscription();
  void saveGlobalReductions(std::vector<T> const& averageGlobals, std::vector<T> const& sumGlobals,
                            std::vector<T> const& minGlobals, std::vector<T> const& maxGlobals);
  void getAverages(std::vector<T>& elements, std::vector<T>& weights);
  void getSums(std::vector<T>& elements);
  void getMins(std::vector<T>& elements);
  void getMaxs(std::vector<T>& elements);
private:
  std::vector<std::vector<T*> >  averageElements;
  std::vector<std::vector<size_t const*> > averageWeights;
  std::vector<std::vector<T*> >  sumElements;
  std::vector<std::vector<T*> >  minElements;
  std::vector<std::vector<T*> >  maxElements;
  int newSubscriptions;
  bool firstSubscription;
  size_t iSumElements, iAverageElements, iMinElements, iMaxElements;
};

}

#endif
