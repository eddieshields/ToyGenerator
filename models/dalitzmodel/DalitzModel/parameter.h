#ifndef DALITZMODEL_PARAMETER_H
#define DALITZMODEL_PARAMETER_H

// STL.
#include <iostream>
#include <vector>
#include <algorithm>

// DalitzModel.
#include "random.h"
#include "colours.h"
#include "types.h"

namespace DalitzModel {

enum Uncertainty {
  Fixed,
  Floating
};

class Parameter
{
protected:
  static std::vector<Parameter*> m_parameters;
  static bool m_random;
  real_t m_value = {0.};
  real_t m_error = {0.};

public:
  real_t m_state = {0.};
  Parameter() { Parameter::m_parameters.push_back( this ); }
  Parameter(const real_t& val, const real_t& err = 0) :
    m_value( val ),
    m_error( Random::normal( 0 , err ) )
  {
    if ( Parameter::m_random ) m_state = m_value + m_error;
    else m_state = m_value;
    Parameter::m_parameters.push_back( this );
  }
  Parameter(const Parameter& other) :
    m_value( other.m_value ),
    m_error( other.m_error ),
    m_state( other.m_state )
  {
    Parameter::m_parameters.push_back( this );
  }
  virtual ~Parameter()
  {
    m_parameters.erase(std::remove(m_parameters.begin(), m_parameters.end(), this), m_parameters.end());
  }

  void set_state()
  {
    switch( ParameterUncertaintyType::Type )
    {
    case Uncertainty::Floating:
      m_state = m_value + m_error;
      break;
    default:
      m_state = m_value;
      break;
    }
  }

  /** ParameterUncertainty  
   * 
   * Nested class that can be used to change the system of coordinates
   * used for the Coefficients.
   */
  struct ParameterUncertaintyType
  {
    static Uncertainty Type;
    void operator=(Uncertainty uncert_type)
    {
      if ( uncert_type == Type ) return;
      switchUncertaintySystem( uncert_type );
    }
    void switchUncertaintySystem(Uncertainty uncert_type)
    {
      if ( uncert_type == Type ) return;
      switch(uncert_type)
      {
      case Uncertainty::Fixed:
        INFO("Switching to fixed uncertainty");
        for (auto p : Parameter::m_parameters) {
          p->m_state = p->m_value;
        }
        break;
      case Uncertainty::Floating:
        INFO("Switching to floating uncertainty");
        for (auto p : Parameter::m_parameters) {
          p->m_state = p->m_value + p->m_error;
        }
        break;
      default:
        break;
      }
    }
  };
  static ParameterUncertaintyType ParameterUncertainty;

  real_t value() const { return m_value; }
  real_t error() const { return m_error; }

  void SetValue(const real_t& value) { m_value = value; }
  void SetError(const real_t& error) { m_error = error; }

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
    real_t err_val;
    is >> param.m_value >> pm >> err_val;
    param.m_error = Random::normal( 0 , err_val );
    if ( Parameter::m_random ) param.m_state = param.m_value + param.m_error;
    else param.m_state = param.m_value;
    return is;
  }


  // Operators.
  friend const real_t operator+(const Parameter& left, const Parameter& right)
  {
    return left.m_state + right.m_state;
  }
  
  friend const real_t operator-(const Parameter& left, const Parameter& right)
  {
    return left.m_state - right.m_state;
  }
  
  friend const real_t operator*(const Parameter& left, const Parameter& right)
  {
    return left.m_state * right.m_state;
  }
  
  friend const real_t operator/(const Parameter& left, const Parameter& right)
  {
    return left.m_state / right.m_state;
  }
  
  friend const real_t operator+(const Parameter& left, const int& right)
  {
    return left.m_state + (real_t)right;
  }
  
  friend const real_t operator-(const Parameter& left, const int& right)
  {
    return left.m_state - (real_t)right;
  }
  
  friend const real_t operator*(const Parameter& left, const int& right)
  {
    return left.m_state * (real_t)right;
  }
  
  friend const real_t operator/(const Parameter& left, const int& right)
  {
    return left.m_state / (real_t)right;
  }
  
  friend const real_t operator+(const Parameter& left, const real_t& right)
  {
    return left.m_state + right;
  }
  
  friend const real_t operator-(const Parameter& left, const real_t& right)
  {
    return left.m_state - right;
  }
  
  friend const real_t operator*(const Parameter& left, const real_t& right)
  {
    return left.m_state * right;
  }
  
  friend const real_t operator/(const Parameter& left, const real_t& right)
  {
    return left.m_state / right;
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
  
  friend const real_t operator+(const int& left, const Parameter& right)
  {
    return (real_t)left + right.m_state;
  }
  
  friend const real_t operator-(const int& left, const Parameter& right)
  {
    return (real_t)left - right.m_state;
  }
  
  friend const real_t operator*(const int& left, const Parameter& right)
  {
    return (real_t)left * right.m_state;
  }
  
  friend const real_t operator/(const int& left, const Parameter& right)
  {
    return (real_t)left / right.m_state;
  }
  
  friend const real_t operator+(const real_t& left, const Parameter& right)
  {
    return left + right.m_state;
  }
  
  friend const real_t operator-(const real_t& left, const Parameter& right)
  {
    return left - right.m_state;
  }
  
  friend const real_t operator*(const real_t& left, const Parameter& right)
  {
    return left * right.m_state;
  }
  
  friend const real_t operator/(const real_t& left, const Parameter& right)
  {
    return left / right.m_state;
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