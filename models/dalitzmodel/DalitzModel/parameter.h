#ifndef DALITZMODEL_PARAMETER_H
#define DALITZMODEL_PARAMETER_H

// STL.
#include <iostream>
#include <complex>
#include <vector>

// DalitzModel.
#include "random.h"
#include "colours.h"

namespace DalitzModel {

using complex_t = std::complex<double>;

class Parameter
{
protected:
  static std::vector<Parameter*> m_parameters;
  static bool m_random;
  double m_value = {0.};
  double m_error = {0.};

public:
  double m_state = {0.};
  Parameter() { Parameter::m_parameters.push_back( this ); }
  Parameter(const double& val, const double& err = 0) :
    m_value( val ),
    m_error( Random::normal( 0 , err ) )
  {
    if ( Parameter::m_random ) m_state = m_value + m_error;
    else m_state = m_value;
    Parameter::m_parameters.push_back( this );
  }
  Parameter(const Parameter& other) :
    m_value( other.m_value ),
    m_error( other.m_error),
    m_state( other.m_state )
  {
    Parameter::m_parameters.push_back( this );
  }
  virtual ~Parameter()
  {
    // Remove parameter from list;
  }

  double value() const { return m_value; }
  double error() const { return m_error; }

  void SetValue(const double& value) { m_value = value; }
  void SetError(const double& error) { m_error = error; }

  static void SetRandom(bool flag = true);

  // Operators.
  friend std::ostream& operator<<(std::ostream& os, const Parameter& param)
  {
    os << MAGENTA << std::fixed << std::setprecision(5) << param.m_value << " +- " 
                  << std::fixed << std::setprecision(5) << param.m_error << RESET;
    return os;
  }
  friend std::istream& operator>>(std::istream& is, Parameter& param)
  {
    // Input of the form " value +- error".
    std::string pm;
    double err_val;
    is >> param.m_value >> pm >> err_val;
    param.m_error = Random::normal( 0 , err_val );
    if ( Parameter::m_random ) param.m_state = param.m_value + param.m_error;
    else param.m_state = param.m_value;
    return is;
  }


  // Operators.
  friend const double operator+(const Parameter& left, const Parameter& right)
  {
    return left.m_state + right.m_state;
  }
  
  friend const double operator-(const Parameter& left, const Parameter& right)
  {
    return left.m_state - right.m_state;
  }
  
  friend const double operator*(const Parameter& left, const Parameter& right)
  {
    return left.m_state * right.m_state;
  }
  
  friend const double operator/(const Parameter& left, const Parameter& right)
  {
    return left.m_state / right.m_state;
  }
  
  friend const double operator+(const Parameter& left, const int& right)
  {
    return left.m_state + (double)right;
  }
  
  friend const double operator-(const Parameter& left, const int& right)
  {
    return left.m_state - (double)right;
  }
  
  friend const double operator*(const Parameter& left, const int& right)
  {
    return left.m_state * (double)right;
  }
  
  friend const double operator/(const Parameter& left, const int& right)
  {
    return left.m_state / (double)right;
  }
  
  friend const double operator+(const Parameter& left, const double& right)
  {
    return left.m_state + right;
  }
  
  friend const double operator-(const Parameter& left, const double& right)
  {
    return left.m_state - right;
  }
  
  friend const double operator*(const Parameter& left, const double& right)
  {
    return left.m_state * right;
  }
  
  friend const double operator/(const Parameter& left, const double& right)
  {
    return left.m_state / right;
  }
  
  friend const double operator+(const Parameter& left, const float& right)
  {
    return left.m_state + (double)right;
  }
  
  friend const double operator-(const Parameter& left, const float& right)
  {
    return left.m_state - (double)right;
  }
  
  friend const double operator*(const Parameter& left, const float& right)
  {
    return left.m_state * (double)right;
  }
  
  friend const double operator/(const Parameter& left, const float& right)
  {
    return left.m_state / (double)right;
  }
  
  friend const complex_t operator+(const Parameter& left, const complex_t& right)
  {
    return left.m_state + right;
  }
  
  friend const complex_t operator-(const Parameter& left, const complex_t& right)
  {
    return left.m_state - right;
  }
  
  friend const complex_t operator*(const Parameter& left, const complex_t& right)
  {
    return left.m_state * right;
  }
  
  friend const complex_t operator/(const Parameter& left, const complex_t& right)
  {
    return left.m_state / right;
  }
  
  friend const double operator+(const int& left, const Parameter& right)
  {
    return (double)left + right.m_state;
  }
  
  friend const double operator-(const int& left, const Parameter& right)
  {
    return (double)left - right.m_state;
  }
  
  friend const double operator*(const int& left, const Parameter& right)
  {
    return (double)left * right.m_state;
  }
  
  friend const double operator/(const int& left, const Parameter& right)
  {
    return (double)left / right.m_state;
  }
  
  friend const double operator+(const double& left, const Parameter& right)
  {
    return left + right.m_state;
  }
  
  friend const double operator-(const double& left, const Parameter& right)
  {
    return left - right.m_state;
  }
  
  friend const double operator*(const double& left, const Parameter& right)
  {
    return left * right.m_state;
  }
  
  friend const double operator/(const double& left, const Parameter& right)
  {
    return left / right.m_state;
  }
  
  friend const double operator+(const float& left, const Parameter& right)
  {
    return (double)left + right.m_state;
  }
  
  friend const double operator-(const float& left, const Parameter& right)
  {
    return (double)left - right.m_state;
  }
  
  friend const double operator*(const float& left, const Parameter& right)
  {
    return (double)left * right.m_state;
  }
  
  friend const double operator/(const float& left, const Parameter& right)
  {
    return (double)left / right.m_state;
  }
  
  friend const complex_t operator+(const complex_t& left, const Parameter& right)
  {
    return left + right.m_state;
  }
  friend const complex_t operator-(const complex_t& left, const Parameter& right)
  {
    return left - right.m_state;
  }
  friend const complex_t operator*(const complex_t& left, const Parameter& right)
  {
    return left * right.m_state;
  }
  friend const complex_t operator/(const complex_t& left, const Parameter& right)
  {
    return left / right.m_state;
  }
};

} // namespace DalitzModel

#endif