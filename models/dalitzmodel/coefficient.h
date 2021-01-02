#ifndef TOYGEN_COEFFICIENT_H
#define TOYGEN_COEFFICIENT_H

// Package.
#include "parameter.h"

// SL.
#include <iostream>
#include <complex>

namespace DalitzModel {

/** @brief Coeff class to provide complex coefficients with different coordinate systems.
 * 
 * Complex coefficient that can be used to multiply amplitudes. Works for both 
 * rectangular and polar coordinate systems that can be configured by
 * Options::Coordinates().
 * 
 * @author Edward Shields
 * @date   05/11/2020
 */
class Coeff
{
public:
  /** Constructor. */
  Coeff(const Parameter& c1, const Parameter& c2) : _c1( c1 ), _c2( c2 )
  {}
  /** Destructor. */
  ~Coeff() {};

  /** Returns first part of complex coefficient. */
  const Parameter& c1() { return _c1; }
  /** Returns second part of complex coefficient. */
  const Parameter& c2() { return _c2; }

  static void setRectangular() { m_rectangular = true; }
  static void setPolar()       { m_rectangular = false; }

  /** Multiplication operator for a double. */
  std::complex< double > operator*(const double& num);
  /** Multiplication operator for a complex number. */
  std::complex< double > operator*(const std::complex< double >& num);

private:
  const Parameter _c1;
  const Parameter _c2;
  static bool m_rectangular;
};

}

#endif