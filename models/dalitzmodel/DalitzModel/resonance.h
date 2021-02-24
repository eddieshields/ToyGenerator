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

namespace DalitzModel {

using complex_t = std::complex<double>;

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

  double      m_massSq;
public:
  Resonance() = default;
  Resonance(std::string& name, const Coefficient& coeff,
            const int& resoA, const int& resoB,
            const Parameter& mass, const Parameter& width,
            const int& l, const Parameter& r) :
    m_name( name ),
    m_coeff( coeff ),
    m_mass( mass ),
    m_width( width ),
    m_r( r ),
    m_l( l ),
    m_resoA( resoA ),
    m_resoB( resoB )
  {
    m_massSq = m_mass * m_mass;
    m_noRes = 6 - m_resoA - m_resoB;
  }
  Resonance(std::string& name, const double& coeff1, const double& coeff2,
            const int& resoA, const int& resoB,
            const double& mass, const double& width,
            const int& l, const double& r) :
    m_name( name ),
    m_coeff( coeff1 , coeff2 ),
    m_mass( mass ),
    m_width( width ),
    m_r( r ),
    m_l( l ),
    m_resoA( resoA ),
    m_resoB( resoB )
  {
    m_massSq = m_mass * m_mass;
    m_noRes = 6 - m_resoA - m_resoB;
  }
  Resonance(const Resonance& other) :
    m_name( other.m_name ),
    m_coeff( other.m_coeff ),
    m_mass( other.m_mass ),
    m_width( other.m_width ),
    m_r( other.m_r ),
    m_l( other.m_l ),
    m_resoA( other.m_resoA ),
    m_resoB( other.m_resoB )
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
  virtual const complex_t propagator(const PhaseSpace& ps, const double& mSqAB) const = 0;

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
    double c1, c2;
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
  std::string name()  const { return m_name; }
  double      mass()  const { return m_mass.m_state; }
  double      m()     const { return m_mass.m_state; }
  double      mSq()   const { return m_massSq; }
  double      width() const { return m_width.m_state; }
  double      r()     const { return m_r.m_state; }
  int         l()     const { return m_l; }

  const complex_t evaluate(const PhaseSpace& ps, const double& mSq12, const double& mSq13);
  const complex_t evaluate(const PhaseSpace& ps, const double& mSq12, const double& mSq13, const double& mSq23);

  const double M2AB(const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double M2AC(const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double M2BC(const double& mSq12, const double& mSq13, const double& mSq23) const;

  // Methods.
  /** Kallen function.
   * 
   *  Returns lambda( x, y, z ) = x^2 + y^2 + z^2 - 2xy - 2xz - 2yz.
   */
  double kallen              (const double& x, const double& y, const double& z) const;
  /** Momentum of a resonant particle in the rest frame of the resonant pair.
   */
  double q                   (const PhaseSpace& ps, const double& mSqAB) const;
  /** Momentum of the non-resonant particle in the rest frame of the resonant pair.
   */
  double p                   (const PhaseSpace& ps, const double& mSqAB) const;
  /** Phase space factor
   * 
   * 2 q / m, where q is the momentum of a resonant particle in the
   * rest frame of the resonant pair, and m is the invariant mass of the resonant pair.
   * \param mSq1 Squared mass of first particle is resonant pair.
   * \param mSq2 Squared mass of second particle in resonance pair.
   */
  double rho                 (const PhaseSpace& ps, const double& mSqAB, const double& mSq1, const double& mSq2) const;
  /** Phase space factor
   * 
   * 2 q / m, where q is the momentum of a resonant particle in the
   * rest frame of the resonant pair, and m is the invariant mass of the resonant pair.
   */
  double rho                 (const PhaseSpace& ps, const double& mSqAB) const;
  /** Zemach tensor.
   */
  double zemach              (const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const;
  double helicity            (const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const;
  double blattWeisskopfPrime (const PhaseSpace& ps, const double& mSqAB) const;
  double blattWeisskopfPrimeP(const PhaseSpace& ps, const double& mSqAB) const;
  double blattWeisskopf      (const PhaseSpace& ps, const double& mSqAB) const;
  double angular             (const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const;

};

}

#endif