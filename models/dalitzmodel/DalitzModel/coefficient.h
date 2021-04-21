#ifndef DALITZMODEL_COEFFICIENT_H
#define DALITZMODEL_COEFFICIENT_H

// STL.
#include <iostream>
#include <vector>
#include <algorithm>

// DalitzModel.
#include "parameter.h"
#include "colours.h"
#include "types.h"

namespace DalitzModel {

class Parameter;

enum Coordinates {
  Rectangular,
  Polar
};


class Coefficient
{
friend class Parameter;
private:
  static std::vector<Coefficient*> m_coefficients;
  Parameter m_c1 = {0.};
  Parameter m_c2 = {0.};

public:
  //static Coordinates Coords
  complex_t m_state = {complex_t(0.,0.)};

  Coefficient() { m_coefficients.push_back( this ); }
  Coefficient(const real_t& c1, const real_t& c2) :
    m_c1( c1 ),
    m_c2( c2 )
  {
    set_state();
    m_coefficients.push_back( this );
  }
  Coefficient(const Parameter& c1, const Parameter& c2) :
    m_c1( c1 ),
    m_c2( c2 )
  {
    set_state();
    m_coefficients.push_back( this );
  }
  Coefficient(const Coefficient& coeff) :
    m_c1( coeff.m_c1 ),
    m_c2( coeff.m_c2 )
  {
    set_state();
    m_coefficients.push_back( this );
  }

  virtual ~Coefficient()
  {
    m_coefficients.erase(std::remove(m_coefficients.begin(), m_coefficients.end(), this), m_coefficients.end());
  }

  void set_state()
  {
    switch( CoefficientCoordinates::Type )
    {
    case Coordinates::Polar:
      m_state = std::polar( m_c1.m_state , m_c2.m_state );
      break;
    default:
      m_state = complex_t( m_c1.m_state , m_c2.m_state );
      break;
    }
  }


  /** CoordinateSytem
   * 
   * Nested class that can be used to change the system of coordinates
   * used for the Coefficients.
   */
  struct CoefficientCoordinates
  {
    static Coordinates Type;
    void operator=(Coordinates coord_type)
    {
      if ( coord_type == Type ) return;
      switchCoordinateSystem( coord_type );
    }
    void operator=(std::string coord_type)
    {
      Coordinates tmp;
      if ( coord_type == "Rectangular" ) {
        tmp = Coordinates::Rectangular;
      } else if ( coord_type == "Polar" ) {
        tmp = Coordinates::Polar;
      } else {
        return;
      }
      switchCoordinateSystem( tmp );
    }
    void switchCoordinateSystem(Coordinates coord_type)
    {
      if ( coord_type == Type ) return;
      switch(coord_type)
      {
      case Coordinates::Polar:
        INFO("Switching to polar coordinates");
        for (auto c : Coefficient::m_coefficients) {
          c->m_state = std::polar( c->m_c1.m_state , c->m_c2.m_state );
        }
        break;
      case Coordinates::Rectangular:
        INFO("Switching to rectangular coordinates");
        for (auto c : Coefficient::m_coefficients) {
          c->m_state = complex_t( c->m_c1.m_state , c->m_c2.m_state );
        }
        break;
      default:
        break;
      }
    }
  };
  static CoefficientCoordinates CoordinatesSystem;

  // Operators.
  friend std::ostream& operator<<(std::ostream& os, const Coefficient& coeff)
  {
    os << MAGENTA << coeff.m_state << RESET; //<< "(" << std::fixed << std::setprecision(5) << coeff.m_c1.m_state 
                  //<< "," << std::fixed << std::setprecision(5) << coeff.m_c2.m_state 
                  //<< ")" << RESET;
    return os;
  }
  friend std::istream& operator>>(std::istream& is, Coefficient& coeff)
  {
    // Input of the form " c1 , c2".
    std::string comma;
    is >> coeff.m_c1 >> comma >> coeff.m_c2;
    switch( Coefficient::CoefficientCoordinates::Type )
    {
    case Coordinates::Polar:
      coeff.m_state = std::polar(coeff.m_c1.m_state,coeff.m_c2.m_state);
      break;
    default:
      coeff.m_state = complex_t(coeff.m_c1.m_state,coeff.m_c2.m_state);
      break;
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
    return left.m_state + (real_t)right;
  }
  
  friend const complex_t operator-(const Coefficient& left, const int& right)
  {
    return left.m_state - (real_t)right;
  }
  
  friend const complex_t operator*(const Coefficient& left, const int& right)
  {
    return left.m_state * (real_t)right;
  }
  
  friend const complex_t operator/(const Coefficient& left, const int& right)
  {
    return left.m_state / (real_t)right;
  }
  
  friend const complex_t operator+(const Coefficient& left, const real_t& right)
  {
    return left.m_state + right;
  }
  
  friend const complex_t operator-(const Coefficient& left, const real_t& right)
  {
    return left.m_state - right;
  }
  
  friend const complex_t operator*(const Coefficient& left, const real_t& right)
  {
    return left.m_state * right;
  }
  
  friend const complex_t operator/(const Coefficient& left, const real_t& right)
  {
    return left.m_state / right;
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
    return (real_t)left + right.m_state;
  }
  
  friend const complex_t operator-(const int& left, const Coefficient& right)
  {
    return (real_t)left - right.m_state;
  }
  
  friend const complex_t operator*(const int& left, const Coefficient& right)
  {
    return (real_t)left * right.m_state;
  }
  
  friend const complex_t operator/(const int& left, const Coefficient& right)
  {
    return (real_t)left / right.m_state;
  }
  
  friend const complex_t operator+(const real_t& left, const Coefficient& right)
  {
    return left + right.m_state;
  }
  
  friend const complex_t operator-(const real_t& left, const Coefficient& right)
  {
    return left - right.m_state;
  }
  
  friend const complex_t operator*(const real_t& left, const Coefficient& right)
  {
    return left * right.m_state;
  }
  
  friend const complex_t operator/(const real_t& left, const Coefficient& right)
  {
    return left / right.m_state;
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