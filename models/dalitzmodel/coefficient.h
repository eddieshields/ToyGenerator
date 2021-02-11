#ifndef DALITZMODEL_COEFFICIENT_H
#define DALITZMODEL_COEFFICIENT_H

// STL.
#include <iostream>
#include <complex>

// DalitzModel.
#include "parameter.h"
#include "colours.h"

namespace DalitzModel {

using complex_t = std::complex<double>;

class Parameter;

enum Coordinates {
  Rectangular,
  Polar
};

class Coefficient
{
friend class Parameter;
private:
  
  static Coordinates m_coords;
  Parameter m_c1 = {0.};
  Parameter m_c2 = {0.};

public:
  complex_t m_state = {complex_t(0.,0.)};
  Coefficient() = default;
  Coefficient(const double& c1, const double& c2) :
    m_c1( c1 ),
    m_c2( c2 )
  {
    switch( m_coords )
    {
    case Coordinates::Polar:
      m_state = std::polar( c1 , c2 );
    default:
      m_state = complex_t( c1 , c2 );
    }
  }
  Coefficient(const Parameter& c1, const Parameter& c2) :
    m_c1( c1 ),
    m_c2( c2 )
  {
    switch( m_coords )
    {
    case Coordinates::Polar:
      m_state = std::polar( c1.m_state , c2.m_state );
    default:
      m_state = complex_t( c1.m_state , c2.m_state );
    }
  }
  virtual ~Coefficient() {}

  // Operators.
  friend std::ostream& operator<<(std::ostream& os, const Coefficient& coeff)
  {
    os << MAGENTA << "(" << std::fixed << std::setprecision(5) << coeff.m_c1.m_state 
                  << "," << std::fixed << std::setprecision(5) << coeff.m_c2.m_state 
                  << ")" << RESET;
    return os;
  }
  friend std::istream& operator>>(std::istream& is, Coefficient& coeff)
  {
    // Input of the form " c1 , c2".
    std::string comma;
    is >> coeff.m_c1 >> comma >> coeff.m_c2;
    switch( m_coords )
    {
    case Coordinates::Polar:
      coeff.m_state = std::polar(coeff.m_c1.m_state,coeff.m_c2.m_state);
    default:
      coeff.m_state = complex_t(coeff.m_c1.m_state,coeff.m_c2.m_state);
    }
    return is;
  }

  // Operators.
  friend const complex_t operator+(const Coefficient& left, const Coefficient& right)
  {
    return left.m_state + right.m_state;
  }
  
  friend const complex_t operator-(const Coefficient& left, const Coefficient& right)
  {
    return left.m_state - right.m_state;
  }
  
  friend const complex_t operator*(const Coefficient& left, const Coefficient& right)
  {
    return left.m_state * right.m_state;
  }
  
  friend const complex_t operator/(const Coefficient& left, const Coefficient& right)
  {
    return left.m_state / right.m_state;
  }
  
  friend const complex_t operator+(const Coefficient& left, const int& right)
  {
    return left.m_state + (double)right;
  }
  
  friend const complex_t operator-(const Coefficient& left, const int& right)
  {
    return left.m_state - (double)right;
  }
  
  friend const complex_t operator*(const Coefficient& left, const int& right)
  {
    return left.m_state * (double)right;
  }
  
  friend const complex_t operator/(const Coefficient& left, const int& right)
  {
    return left.m_state / (double)right;
  }
  
  friend const complex_t operator+(const Coefficient& left, const double& right)
  {
    return left.m_state + right;
  }
  
  friend const complex_t operator-(const Coefficient& left, const double& right)
  {
    return left.m_state - right;
  }
  
  friend const complex_t operator*(const Coefficient& left, const double& right)
  {
    return left.m_state * right;
  }
  
  friend const complex_t operator/(const Coefficient& left, const double& right)
  {
    return left.m_state / right;
  }
  
  friend const complex_t operator+(const Coefficient& left, const float& right)
  {
    return left.m_state + (double)right;
  }
  
  friend const complex_t operator-(const Coefficient& left, const float& right)
  {
    return left.m_state - (double)right;
  }
  
  friend const complex_t operator*(const Coefficient& left, const float& right)
  {
    return left.m_state * (double)right;
  }
  
  friend const complex_t operator/(const Coefficient& left, const float& right)
  {
    return left.m_state / (double)right;
  }
  
  friend const complex_t operator+(const Coefficient& left, const complex_t& right)
  {
    return left.m_state + right;
  }
  
  friend const complex_t operator-(const Coefficient& left, const complex_t& right)
  {
    return left.m_state - right;
  }
  
  friend const complex_t operator*(const Coefficient& left, const complex_t& right)
  {
    return left.m_state * right;
  }
  
  friend const complex_t operator/(const Coefficient& left, const complex_t& right)
  {
    return left.m_state / right;
  }
  
  friend const complex_t operator+(const Coefficient& left, const Parameter& right)
  {
    return left.m_state + right.m_state;
  }
  
  friend const complex_t operator-(const Coefficient& left, const Parameter& right)
  {
    return left.m_state - right.m_state;
  }
  
  friend const complex_t operator*(const Coefficient& left, const Parameter& right)
  {
    return left.m_state * right.m_state;
  }
  
  friend const complex_t operator/(const Coefficient& left, const Parameter& right)
  {
    return left.m_state / right.m_state;
  }
  
  friend const complex_t operator+(const int& left, const Coefficient& right)
  {
    return (double)left + right.m_state;
  }
  
  friend const complex_t operator-(const int& left, const Coefficient& right)
  {
    return (double)left - right.m_state;
  }
  
  friend const complex_t operator*(const int& left, const Coefficient& right)
  {
    return (double)left * right.m_state;
  }
  
  friend const complex_t operator/(const int& left, const Coefficient& right)
  {
    return (double)left / right.m_state;
  }
  
  friend const complex_t operator+(const double& left, const Coefficient& right)
  {
    return left + right.m_state;
  }
  
  friend const complex_t operator-(const double& left, const Coefficient& right)
  {
    return left - right.m_state;
  }
  
  friend const complex_t operator*(const double& left, const Coefficient& right)
  {
    return left * right.m_state;
  }
  
  friend const complex_t operator/(const double& left, const Coefficient& right)
  {
    return left / right.m_state;
  }
  
  friend const complex_t operator+(const float& left, const Coefficient& right)
  {
    return (double)left + right.m_state;
  }
  
  friend const complex_t operator-(const float& left, const Coefficient& right)
  {
    return (double)left - right.m_state;
  }
  
  friend const complex_t operator*(const float& left, const Coefficient& right)
  {
    return (double)left * right.m_state;
  }
  
  friend const complex_t operator/(const float& left, const Coefficient& right)
  {
    return (double)left / right.m_state;
  }
  
  friend const complex_t operator+(const complex_t& left, const Coefficient& right)
  {
    return left + right.m_state;
  }
  friend const complex_t operator-(const complex_t& left, const Coefficient& right)
  {
    return left - right.m_state;
  }
  friend const complex_t operator*(const complex_t& left, const Coefficient& right)
  {
    return left * right.m_state;
  }
  friend const complex_t operator/(const complex_t& left, const Coefficient& right)
  {
    return left / right.m_state;
  }
  
  friend const complex_t operator+(const Parameter& left, const Coefficient& right)
  {
    return left.m_state + right.m_state;
  }
  
  friend const complex_t operator-(const Parameter& left, const Coefficient& right)
  {
    return left.m_state - right.m_state;
  }
  
  friend const complex_t operator*(const Parameter& left, const Coefficient& right)
  {
    return left.m_state * right.m_state;
  }
  
  friend const complex_t operator/(const Parameter& left, const Coefficient& right)
  {
    return left.m_state / right.m_state;
  }
};

} // namespace DalitzModel

#endif