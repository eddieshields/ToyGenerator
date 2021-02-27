#ifndef DALITZMODEL_RESONANCE_H
#define DALITZMODEL_RESONANCE_H

// STL.
#include <iostream>
#include <iomanip>
#include <string>
#include <complex>

// DalitzModel.
#include "parameter.h"
#include "coefficient.h"
#include "phasespace.h"
#include "colours.h"
#include "msgservice.h"
#include "types.h"

namespace DalitzModel {

class Resonance
{
protected:
  Coefficient m_coeff;
  Parameter   m_mass;
  Parameter   m_width;
  Parameter   m_r;
  int         m_l;
  int         m_resoA;
  int         m_resoB;
  int         m_noRes;

  std::string m_name;

  bool        m_helicity = {false};

  real_t      m_massSq;
public:
  Resonance() = default;
  Resonance(std::string& name, const Coefficient& coeff,
            const int& resoA, const int& resoB,
            const Parameter& mass, const Parameter& width,
            const int& l, const Parameter& r) :
    m_coeff( coeff ),
    m_mass( mass ),
    m_width( width ),
    m_r( r ),
    m_l( l ),
    m_resoA( resoA ),
    m_resoB( resoB ),
    m_name( name )
  {
    m_massSq = m_mass * m_mass;
    m_noRes = 6 - m_resoA - m_resoB;
  }
  Resonance(std::string& name, const real_t& coeff1, const real_t& coeff2,
            const int& resoA, const int& resoB,
            const real_t& mass, const real_t& width,
            const int& l, const real_t& r) :
    m_coeff( coeff1 , coeff2 ),
    m_mass( mass ),
    m_width( width ),
    m_r( r ),
    m_l( l ),
    m_resoA( resoA ),
    m_resoB( resoB ),
    m_name( name )
  {
    m_massSq = m_mass * m_mass;
    m_noRes = 6 - m_resoA - m_resoB;
  }
  Resonance(const Resonance& other) :
    m_coeff( other.m_coeff ),
    m_mass( other.m_mass ),
    m_width( other.m_width ),
    m_r( other.m_r ),
    m_l( other.m_l ),
    m_resoA( other.m_resoA ),
    m_resoB( other.m_resoB ),
    m_name( other.m_name )
  {
    m_massSq = m_mass * m_mass;
    m_noRes = 6 - m_resoA - m_resoB;
  }
  virtual ~Resonance() {}

  /** Conjugate copy.
   * 
   * Make conjugate copy of the resonance.
   */
  Resonance* cnj_copy() const;
  virtual Resonance* copy() const = 0;

  // Pointer for linked list.
  Resonance* next = {nullptr};

  // Propagator.
  virtual const complex_t propagator(const PhaseSpace& ps, const real_t& mSqAB) const = 0;

  // Operators.
  friend std::ostream& operator<<(std::ostream& os, const Resonance& reso)
    {
    os << MAGENTA << std::left << std::setw( 9 ) << reso.m_name << ": ";
    os << MAGENTA << "coeff = " << reso.m_coeff << MAGENTA <<", ";
    os << MAGENTA << "resoA = " << reso.m_resoA << MAGENTA <<", ";
    os << MAGENTA << "resoB = " << reso.m_resoB << MAGENTA <<", ";
    os << MAGENTA << "mass = "  << reso.m_mass  << MAGENTA <<", ";
    os << MAGENTA << "width = " << reso.m_width << MAGENTA <<", ";
    os << MAGENTA << "l = "     << reso.m_l     << MAGENTA <<", ";
    os << MAGENTA << "rBW = "   << reso.m_r;
    os << RESET;

    return os;
  }
  friend std::istream& operator>>(std::istream& is, Resonance& reso)
  {
    // Input of the form "c1 c2 resoA resoB mass width l rBW".
    real_t c1, c2;
    is >> c1 >> c2
       >> reso.m_resoA
       >> reso.m_resoB
       >> reso.m_mass
       >> reso.m_width
       >> reso.m_l
       >> reso.m_r;
    reso.m_coeff = Coefficient(c1,c2);
    return is;
  }

  // Getters.
  inline std::string name()  const { return m_name; }
  inline real_t      mass()  const { return m_mass.m_state; }
  inline real_t      m()     const { return m_mass.m_state; }
  inline real_t      mSq()   const { return m_massSq; }
  inline real_t      width() const { return m_width.m_state; }
  inline real_t      r()     const { return m_r.m_state; }
  inline int         l()     const { return m_l; }

  const complex_t evaluate(const PhaseSpace& ps, const real_t& mSq12, const real_t& mSq13);
  const complex_t evaluate(const PhaseSpace& ps, const real_t& mSq12, const real_t& mSq13, const real_t& mSq23);

  inline const real_t M2AB(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const;
  inline const real_t M2AC(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const;
  inline const real_t M2BC(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const;

  // Methods.
  /** Kallen function.
   * 
   *  Returns lambda( x, y, z ) = x^2 + y^2 + z^2 - 2xy - 2xz - 2yz.
   */
  real_t kallen              (const real_t& x, const real_t& y, const real_t& z) const;
  /** Momentum of a resonant particle in the rest frame of the resonant pair.
   */
  real_t q                   (const PhaseSpace& ps, const real_t& mSqAB) const;
  /** Momentum of the non-resonant particle in the rest frame of the resonant pair.
   */
  real_t p                   (const PhaseSpace& ps, const real_t& mSqAB) const;
  /** Phase space factor
   * 
   * 2 q / m, where q is the momentum of a resonant particle in the
   * rest frame of the resonant pair, and m is the invariant mass of the resonant pair.
   * \param mSq1 Squared mass of first particle is resonant pair.
   * \param mSq2 Squared mass of second particle in resonance pair.
   */
  real_t rho                 (const PhaseSpace& ps, const real_t& mSqAB, const real_t& mSq1, const real_t& mSq2) const;
  /** Phase space factor
   * 
   * 2 q / m, where q is the momentum of a resonant particle in the
   * rest frame of the resonant pair, and m is the invariant mass of the resonant pair.
   */
  real_t rho                 (const PhaseSpace& ps, const real_t& mSqAB) const;
  /** Zemach tensor.
   */
  real_t zemach              (const PhaseSpace& ps, const real_t& mSqAB, const real_t& mSqAC, const real_t& mSqBC) const;
  real_t helicity            (const PhaseSpace& ps, const real_t& mSqAB, const real_t& mSqAC, const real_t& mSqBC) const;
  real_t blattWeisskopfPrime (const PhaseSpace& ps, const real_t& mSqAB) const;
  real_t blattWeisskopfPrimeP(const PhaseSpace& ps, const real_t& mSqAB) const;
  real_t blattWeisskopf      (const PhaseSpace& ps, const real_t& mSqAB) const;
  real_t angular             (const PhaseSpace& ps, const real_t& mSqAB, const real_t& mSqAC, const real_t& mSqBC) const;

};

}

#endif