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

  inline const complex_t evaluate(const PhaseSpace& ps, const real_t& mSq12, const real_t& mSq13) const
  {
    real_t mSq23 = ps.mSqSum() - mSq12 - mSq13;
    return evaluate(ps, mSq12, mSq13, mSq23);
  }

  inline const complex_t evaluate(const PhaseSpace& ps, const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
  {
    if ( !ps.contains(mSq12, mSq13) ) return (real_t)0.;
    real_t mSqAB = M2AB(mSq12, mSq13, mSq23);
    real_t mSqAC = M2AC(mSq12, mSq13, mSq23);
    real_t mSqBC = M2BC(mSq12, mSq13, mSq23);
    return m_coeff * propagator( ps , mSqAB ) * angular( ps , mSqAB , mSqAC , mSqBC);
  }

  inline const real_t M2AB(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
  {
    switch ( m_noRes )
    {
    case 3:
      return mSq12;
    case 2:
      return mSq13;
    case 1:
      return mSq23;
    default:
      WARNING("noRes (" << m_noRes << ") poorly defined");
    }
    return 0.;
  }

  inline const real_t M2AC(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
  {
    switch ( m_resoB )
    {
    case 3:
      return mSq12;
    case 2:
      return mSq13;
    case 1:
      return mSq23;
    default:
      WARNING("resoB (" << m_resoB << ") poorly defined");
    }
    return 0.;
  }

  inline const real_t M2BC(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
  {
    switch ( m_resoA )
    {
    case 3:
      return mSq12;
    case 2:
      return mSq13;
    case 1:
      return mSq23;
    default:
      WARNING("resoA (" << m_resoA << ") poorly defined");
    }
    return 0.;
  }

  // Methods.
  /** Kallen function.
   * 
   *  Returns lambda( x, y, z ) = x^2 + y^2 + z^2 - 2xy - 2xz - 2yz.
   */
  inline real_t kallen              (const real_t& x, const real_t& y, const real_t& z) const
  {
    return std::pow( x , 2 ) + std::pow( y , 2 ) + std::pow( z , 2) - 2*x*y - 2*x*z - 2*y*z;
  }
  /** Momentum of a resonant particle in the rest frame of the resonant pair.
   */
  inline real_t q                   (const PhaseSpace& ps, const real_t& mSqAB) const
  {
    return std::sqrt( kallen( mSqAB, ps.mSq( m_resoA ), ps.mSq( m_resoB ) ) )/( 2*std::sqrt(mSqAB) );
  }
  /** Momentum of the non-resonant particle in the rest frame of the resonant pair.
   */
  inline real_t p                   (const PhaseSpace& ps, const real_t& mSqAB) const
  {
    return std::sqrt( kallen( mSqAB, ps.mSqMother(), ps.mSq( m_noRes ) ) )/( 2*std::sqrt(mSqAB) );
  }
  /** Phase space factor
   * 
   * 2 q / m, where q is the momentum of a resonant particle in the
   * rest frame of the resonant pair, and m is the invariant mass of the resonant pair.
   * \param mSq1 Squared mass of first particle is resonant pair.
   * \param mSq2 Squared mass of second particle in resonance pair.
   */
  inline real_t rho                 (const PhaseSpace& ps, const real_t& mSqAB, const real_t& mSq1, const real_t& mSq2) const
  {
    return std::sqrt( kallen( mSqAB, mSq1 , mSq2 ) )/mSqAB;
  }
  /** Phase space factor
   * 
   * 2 q / m, where q is the momentum of a resonant particle in the
   * rest frame of the resonant pair, and m is the invariant mass of the resonant pair.
   */
  inline real_t rho                 (const PhaseSpace& ps, const real_t& mSqAB) const
  {
    return std::sqrt( kallen( mSqAB, ps.mSq( m_resoA ) , ps.mSq( m_resoB ) ) )/mSqAB;
  }

  /** Zemach tensor.
   */
  inline real_t zemach              (const PhaseSpace& ps, const real_t& mSqAB, const real_t& mSqAC, const real_t& mSqBC) const
  {
    if ( m_l == 0 ) return (real_t)1.;

    // Squared mass differences that some terms depend on.
    const real_t diffSqMC = ps.mSqMother()    - ps.mSq( m_noRes );
    const real_t diffSqAB = ps.mSq( m_resoA ) - ps.mSq( m_resoB );

    // Zemach tensor for l = 1.
    const real_t zemach1  = mSqAC - mSqBC - diffSqMC * diffSqAB / mSqAB;

    if ( m_l == 1 ) return zemach1;

    if ( m_l == 2 ) {
      // Squared mass sums that some terms depend on.
      const real_t sumSqMC = ps.mSqMother()    + ps.mSq( m_noRes );
      const real_t sumSqAB = ps.mSq( m_resoA ) + ps.mSq( m_resoB );

      real_t first  = mSqAB - 2. * sumSqMC + std::pow( diffSqMC, 2 ) / mSqAB;
      real_t second = mSqAB - 2. * sumSqAB + std::pow( diffSqAB, 2 ) / mSqAB;

      return std::pow( zemach1, 2 ) - first * second / 3.f;
    }
    return (real_t)0.;
  }

  inline real_t helicity            (const PhaseSpace& ps, const real_t& mSqAB, const real_t& mSqAC, const real_t& mSqBC) const
  {
    if ( m_l == 0 ) return (real_t)1.;

    // Squared mass differences that some terms depend on.
    const real_t diffSqMC = ps.mSqMother()    - ps.mSq( m_noRes );
    const real_t diffSqAB = ps.mSq( m_resoA ) - ps.mSq( m_resoB );

    // Zemach tensor for l = 1.
    const real_t hel1  = mSqAC - mSqBC - diffSqMC * diffSqAB / mSq();

    if ( m_l == 1 ) return hel1;

    if ( m_l == 2 ) {
      // Squared mass sums that some terms depend on.
      const real_t sumSqMC = ps.mSqMother()    + ps.mSq( m_noRes );
      const real_t sumSqAB = ps.mSq( m_resoA ) + ps.mSq( m_resoB );

      real_t first  = mSqAB - 2. * sumSqMC + std::pow( diffSqMC, 2 ) / mSq();
      real_t second = mSqAB - 2. * sumSqAB + std::pow( diffSqAB, 2 ) / mSq();

      return std::pow( hel1, 2 ) - first * second / 3.f;
    }
    return (real_t)0.;
  }

  inline real_t blattWeisskopfPrime (const PhaseSpace& ps, const real_t& mSqAB) const
  {
    if ( m_l == 0 ) return (real_t)1.;

    real_t q0 = q( ps, mSq() );
    real_t qm = q( ps, mSqAB );
    real_t rq0Sq = std::pow( r()*q0 , 2 );
    real_t rqmSq = std::pow( r()*qm , 2 );

    if ( m_l == 1 ) return std::sqrt( ( 1 + rq0Sq )/( 1 + rqmSq ) );
    if ( m_l == 2 ) return std::sqrt( ( 9 + 3*rq0Sq + std::pow( rq0Sq , 2 ) )/( 9 + 3*rqmSq + std::pow( rqmSq , 2 ) ) );
    return (real_t)1.;
  }

  inline real_t blattWeisskopfPrimeP(const PhaseSpace& ps, const real_t& mSqAB) const
  {
    if ( m_l == 0 ) return (real_t)1.;

    real_t p0 = p( ps, this->mSq() );
    real_t pm = p( ps, mSqAB       );
    real_t rp0Sq = std::pow( r()*p0 , 2 );
    real_t rpmSq = std::pow( r()*pm , 2 );

    if ( m_l == 1 ) return std::sqrt( ( 1 + rp0Sq )/( 1 + rpmSq ) );
    if ( m_l == 2 ) return std::sqrt( ( 9 + 3*rp0Sq + std::pow( rp0Sq , 2 ) )/( 9 + 3*rpmSq + std::pow( rpmSq , 2 ) ) );
    return (real_t)0.;
  }

  inline real_t blattWeisskopf      (const PhaseSpace& ps, const real_t& mSqAB) const
  {
    if ( m_l == 0 ) return (real_t)1.;

    real_t qm = q( ps, mSqAB );
    real_t rqmSq = std::pow( r()*qm , 2 );

    if ( m_l == 1 ) return std::sqrt( ( 2 * rqmSq )/( 1 + rqmSq ) );
    if ( m_l == 2 ) return std::sqrt( ( 13 * std::pow( rqmSq , 2 ) )/( 9 + 3*rqmSq + std::pow( rqmSq , 2 ) ) );
    return (real_t)0.;
  }

  inline real_t angular             (const PhaseSpace& ps, const real_t& mSqAB, const real_t& mSqAC, const real_t& mSqBC) const
  {
    if ( m_helicity ) return helicity(ps, mSqAB, mSqAC, mSqBC) * blattWeisskopfPrime(ps, mSqAB);
    return zemach(ps, mSqAB, mSqAC, mSqBC) * blattWeisskopfPrime(ps, mSqAB);
  }

};

}

#endif