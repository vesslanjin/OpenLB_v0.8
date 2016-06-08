/*  This file is part of the OpenLB library
 *
 *  Copyright (C) 2007 Bernd Stahl and Jonas Latt
 *  Address: Battelle Batiment A, Route de Drize 7, 1227 Carouge, Switzerland
 *  E-mail: bernd.stahl@cui.unige.ch
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
 * Classes and free functions to perform reduction operations on data fields -- header file.
 */

#ifndef DATA_REDUCTIONS_H
#define DATA_REDUCTIONS_H

namespace olb {

template<typename T>
class DataReduction {
public:
  virtual ~DataReduction() { }
  virtual T getNeutralElement() const =0;
  virtual void reset() =0;
  virtual void takeElement(T const& element) =0;
  virtual void reduceParallel() =0;
  virtual T getResult() const =0;
};

template<typename T>
class MinReduction : public DataReduction<T> {
public:
  MinReduction() : minimum(neutralElement) { }
  virtual T getNeutralElement() const { return neutralElement; }
  virtual void reset() { minimum = neutralElement; }
  virtual void takeElement(T const& element);
  virtual void reduceParallel();
  virtual T getResult() const { return minimum; }
private:
  static const T neutralElement;
  T minimum;
};

template<typename T>
class MaxReduction : public DataReduction<T> {
public:
  MaxReduction() : maximum(neutralElement) { }
  virtual T getNeutralElement() const { return neutralElement; }
  virtual void reset() { maximum = neutralElement; }
  virtual void takeElement(T const& element);
  virtual void reduceParallel();
  virtual T getResult() const { return maximum; }
private:
  static const T neutralElement;
  T maximum;
};

template<typename T>
class AverageReduction : public DataReduction<T> {
public:
  AverageReduction() : average(neutralElement), weight(T()) { }
  virtual T getNeutralElement() const { return neutralElement; }
  virtual void reset() { average = neutralElement; weight=T(); }
  virtual void takeElement(T const& element);
  virtual void reduceParallel();
  virtual T getResult() const;
private:
  static const T neutralElement;
  T average;
  T weight;
};

template<typename T>
class NormSqrReduction : public DataReduction<T> {
public:
  NormSqrReduction() : normSqr(neutralElement), weight(T()) { }
  virtual T getNeutralElement() const { return neutralElement; }
  virtual void reset() { normSqr = neutralElement; weight=T(); }
  virtual void takeElement(T const& element);
  virtual void reduceParallel();
  virtual T getResult() const;
private:
  static const T neutralElement;
  T normSqr;
  T weight;
};


template<typename T, template<typename U> class ScalarField>
T computeMin(ScalarField<T> const& field);

template<typename T, template<typename U> class ScalarField>
T computeMax(ScalarField<T> const& field);

template<typename T, template<typename U> class ScalarField>
T computeAverage(ScalarField<T> const& field);

template<typename T, template<typename U> class ScalarField>
T computeNormSqr(ScalarField<T> const& field);

template<typename T, template<typename U> class ScalarField>
T computeRMS(ScalarField<T> const& field);

} // namespace olb

#endif
