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
 * Statistics for MultiBlocks -- generic implementation.
 */
#ifndef MULTI_BLOCK_STATISTICS_HH
#define MULTI_BLOCK_STATISTICS_HH

#include "multiBlockStatistics.h"
#include "core/olbDebug.h"
#include <cmath>
#include <numeric>
#include <limits>


namespace olb {

////////////////////// Class MultiBlockReductor /////////////////////////

template<typename T>
MultiBlockReductor<T>::MultiBlockReductor()
  : newSubscriptions(0)
{ }

template<typename T>
void MultiBlockReductor<T>::subscribeSum(T& element) {
  if (firstSubscription) {
    std::vector<T*> newSums(1);
    newSums[0] = &element;
    sumElements.push_back(newSums);
  }
  else {
    sumElements[iSumElements].push_back(&element);
    iSumElements++;
  }
}

template<typename T>
void MultiBlockReductor<T>::subscribeAverage(size_t const& weight, T& element) {
  if (firstSubscription) {
    std::vector<T*> newAverages(1);
    newAverages[0] = &element;
    averageElements.push_back(newAverages);

    std::vector<size_t const*> newWeights(1);
    newWeights[0] = &weight;
    averageWeights.push_back(newWeights);
  }
  else {
    averageElements[iAverageElements].push_back(&element);
    averageWeights[iAverageElements].push_back(&weight);
    iAverageElements++;
  }
}

template<typename T>
void MultiBlockReductor<T>::subscribeMin(T& element) {
  if (firstSubscription) {
    std::vector<T*> newMins(1);
    newMins[0] = &element;
    minElements.push_back(newMins);
  }
  else {
    minElements[iMinElements].push_back(&element);
    iMinElements++;
  }
}

template<typename T>
void MultiBlockReductor<T>::subscribeMax(T& element) {
  if (firstSubscription) {
    std::vector<T*> newMaxs(1);
    newMaxs[0] = &element;
    maxElements.push_back(newMaxs);
  }
  else {
    maxElements[iMaxElements].push_back(&element);
    iMaxElements++;
  }
}

template<typename T>
void MultiBlockReductor<T>::startNewSubscription() {
  ++newSubscriptions;
  iAverageElements = iSumElements = iMinElements = iMaxElements = 0;
  firstSubscription = newSubscriptions == 1;
}

template<typename T>
void MultiBlockReductor<T>::saveGlobalReductions (
  std::vector<T> const& averageGlobals, std::vector<T> const& sumGlobals,
  std::vector<T> const& minGlobals, std::vector<T> const& maxGlobals)
{
  OLB_PRECONDITION( averageGlobals.size() == averageElements.size() );
  OLB_PRECONDITION( sumGlobals.size()     == sumElements.size() );
  OLB_PRECONDITION( minGlobals.size()     == minElements.size() );
  OLB_PRECONDITION( maxGlobals.size()     == maxElements.size() );

  for (unsigned i1Average=0; i1Average<averageElements.size(); ++i1Average) {
    for (unsigned i2Average=0; i2Average<averageElements[i1Average].size(); ++i2Average) {
      *averageElements[i1Average][i2Average] = averageGlobals[i1Average];
    }
  }
  for (unsigned i1Sum=0; i1Sum<sumElements.size(); ++i1Sum) {
    for (unsigned i2Sum=0; i2Sum<sumElements[i1Sum].size(); ++i2Sum) {
      *sumElements[i1Sum][i2Sum] = sumGlobals[i1Sum];
    }
  }
  for (unsigned i1Min=0; i1Min<minElements.size(); ++i1Min) {
    for (unsigned i2Min=0; i2Min<minElements[i1Min].size(); ++i2Min) {
      *minElements[i1Min][i2Min] = minGlobals[i1Min];
    }
  }
  for (unsigned i1Max=0; i1Max<maxElements.size(); ++i1Max) {
    for (unsigned i2Max=0; i2Max<maxElements[i1Max].size(); ++i2Max) {
      *maxElements[i1Max][i2Max] = maxGlobals[i1Max];
    }
  }
}

template<typename T>
void MultiBlockReductor<T>::getAverages(std::vector<T>& elements, std::vector<T>& weights) {
  for (unsigned i1Average=0; i1Average<averageElements.size(); ++i1Average) {
    T sumWeights = T();
    T averageElement = T();
    for (unsigned i2Average=0; i2Average<averageElements[i1Average].size(); ++i2Average) {
      T newElement = *averageElements[i1Average][i2Average];
      T newWeight = (T)*averageWeights[i1Average][i2Average];
      averageElement += newWeight * newElement;
      sumWeights += newWeight;
    }
    if (fabs(sumWeights)>1.e-12) {
      averageElement /= sumWeights;
    }
    elements.push_back(averageElement);
    weights.push_back(sumWeights);
  }
}

template<typename T>
void MultiBlockReductor<T>::getSums(std::vector<T>& elements) {
  for (unsigned i1Sum=0; i1Sum<sumElements.size(); ++i1Sum) {
    T sumElement = T();
    for (unsigned i2Sum=0; i2Sum<sumElements[i1Sum].size(); ++i2Sum) {
      sumElement += *sumElements[i1Sum][i2Sum];
    }
    elements.push_back(sumElement);
  }
}

template<typename T>
void MultiBlockReductor<T>::getMaxs(std::vector<T>& elements) {
  for (unsigned i1Max=0; i1Max<maxElements.size(); ++i1Max) {
    T maxElement = std::numeric_limits<T>::min();
    for (unsigned i2Max=0; i2Max<maxElements[i1Max].size(); ++i2Max) {
      T newElement = *maxElements[i1Max][i2Max];
      if (newElement > maxElement) {
        maxElement = newElement;
      }
    }
    elements.push_back(maxElement);
  }
}

template<typename T>
void MultiBlockReductor<T>::getMins(std::vector<T>& elements) {
  for (unsigned i1Min=0; i1Min<minElements.size(); ++i1Min) {
    T minElement = std::numeric_limits<T>::max();
    for (unsigned i2Min=0; i2Min<minElements[i1Min].size(); ++i2Min) {
      T newElement = *minElements[i1Min][i2Min];
      if (newElement < minElement) {
        minElement = newElement;
      }
    }
    elements.push_back(minElement);
  }
}


}  // namespace olb

#endif
