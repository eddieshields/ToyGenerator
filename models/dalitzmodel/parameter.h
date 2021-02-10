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
  Parameter(std::string& name, const double& par, const double& err = 0.) :
    m_name( name ),
    m_par( par ), 
    m_err( Random::normal( 0 , err ) ) 
  {
    if ( m_random ) {
      m_val = m_par + m_err;
    } else { 
      m_val = m_par;
    }
  }
  /** Destructor. */
  ~Parameter() {};

  /** Returns value of parameter. */
  const double value() const { return m_par; }
  /** Returns error of parameter. */
  const double error() const { return m_err; }
  /** Returns current value of parameter. */
  const double val()   const { return m_val; }

  void setVal(double& val ) { m_val = val; }

  void setRandom() { m_random = true;  m_val = m_par + m_err; }
  void setFixed()  { m_random = false; m_val = m_par;         }

  const std::string name() { return m_name; }

  double operator=(const double& in);
  double operator*(const double in) const;
  template <class number>
  const double operator*(const number& num) const;
  std::complex<double> operator*(const std::complex<double>& in) const;
  double operator*(const Parameter& param) const;
  double operator*(Parameter& param) const;

  friend std::ostream& operator<<(std::ostream& os, const Parameter& p)
  {
    os << p.val(); 
    return os;
  }
protected:
  static bool       m_random;
  const std::string m_name;
  const double      m_par;
  const double      m_err;
  double            m_val;
};

}

#endif