#ifndef TOYGEN_PARAMETER_H
#define TOYGEN_PARAMETER_H

// Package.
#include "random.h"

// SL.
#include <iostream>
#include <complex>

namespace DalitzModel {

/** @brief Parameter class that represents any parameter.
 * 
 * This class holds the value of any parameter. But additionally it takes in an error
 * on the parameter that could be provided from a previous experiment or measurement.
 * By configuring \see Options::SetParRandom() the parameter will have a random value
 * added to it taken from a Gaussian with a mean of zero and a width of its error.
 * This allows the effects of uncertainities on parameters to be studied.
 * 
 * @author Edward Shields
 * @date   05/11/2020
 */
class Parameter
{
public:
  /** Constructor. */
  Parameter(const double& par, const double& err = 0.) : _par( par ), _err( Random::normal( 0 , err ) ) {};
  /** Destructor. */
  ~Parameter() {};

  /** Returns value of parameter. */
  const double value() const { return _par; }
  /** Returns error of parameter. */
  const double error() const { return _err; }
  /** Returns current value of parameter. */
  const double val() const;

  static void setRandom() { _random = true; }
  static void setFixed()  { _random = false; }

  /** Copy method. */
  //Parameter* copy();

  double operator=(const double& in);
  double operator*(const double in) const;
  template <class number>
  const double operator*(const number& num) const;
  std::complex<double> operator*(const std::complex<double>& in) const;
  double operator*(const Parameter& param) const;
  double operator*(Parameter& param) const;
protected:
  static bool  _random;
  const double _par;
  const double _err;
};

}

#endif