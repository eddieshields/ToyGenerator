#include "resonance.h"

using namespace DalitzModel;

Resonance* Resonance::cnj_copy() const
{
  Resonance* reso = this->copy();
  if ( this->m_resoA == 2 ) {
    reso->m_resoA = this->m_resoB;
    reso->m_resoB = this->m_resoA;
  }  else {
    int noRes = 6 - this->m_resoA - this->m_resoB;
    reso->m_resoA = this->m_resoA;
    reso->m_resoB = noRes;
  }
  reso->m_name = this->m_name + "_cnj";
  return reso;
}

const complex_t Resonance::evaluate(const PhaseSpace& ps, const double& mSq12, const double& mSq13, const double& mSq23)
{
  if ( !ps.contains(mSq12, mSq13) ) return 0.;
  double mSqAB = M2AB(mSq12, mSq13, mSq23);
  double mSqAC = M2AC(mSq12, mSq13, mSq23);
  double mSqBC = M2BC(mSq12, mSq13, mSq23);
  return m_coeff * propagator( ps , mSqAB ) * angular( ps , mSqAB , mSqAC , mSqBC);
}

const complex_t Resonance::evaluate(const PhaseSpace& ps, const double& mSq12, const double& mSq13)
{
  double mSq23 = ps.mSqSum() - mSq12 - mSq13;
  return evaluate(ps, mSq12, mSq13, mSq23);
}

const double Resonance::M2AB(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  if ( m_noRes == 3 ) return mSq12;
  if ( m_noRes == 2 ) return mSq13;
  if ( m_noRes == 1 ) return mSq23;
  return 0.;
}

const double Resonance::M2AC(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  if ( m_resoB == 3 ) return mSq12;
  if ( m_resoB == 2 ) return mSq13;
  if ( m_resoB == 1 ) return mSq23;
  return 0.;
}

const double Resonance::M2BC(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  if ( m_resoA == 3 ) return mSq12;
  if ( m_resoA == 2 ) return mSq13;
  if ( m_resoA == 1 ) return mSq23;
  return 0.;
}

inline double Resonance::kallen(const double& x, const double& y, const double& z) const
{
  return std::pow( x , 2 ) + std::pow( y , 2 ) + std::pow( z , 2) - 2*x*y - 2*x*z - 2*y*z;
}

double Resonance::q(const PhaseSpace& ps, const double& mSqAB) const
{
  return std::sqrt( this->kallen( mSqAB, ps.mSq( m_resoA ), ps.mSq( m_resoB ) ) )/( 2*std::sqrt(mSqAB) );
}

double Resonance::p(const PhaseSpace& ps, const double& mSqAB) const
{
  return std::sqrt( this->kallen( mSqAB, ps.mSqMother(), ps.mSq( m_noRes ) ) )/( 2*std::sqrt(mSqAB) );
}

double Resonance::rho(const PhaseSpace& ps, const double& mSqAB, const double& mSq1, const double& mSq2) const
{
  return std::sqrt( this->kallen( mSqAB, mSq1 , mSq2 ) )/mSqAB;
}

double Resonance::rho(const PhaseSpace& ps, const double& mSqAB) const
{
  return std::sqrt( this->kallen( mSqAB, ps.mSq( m_resoA ) , ps.mSq( m_resoB ) ) )/mSqAB;
}

inline double Resonance::zemach( const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC ) const
{
  if ( m_l == 0 ) return 1.;

  // Squared mass differences that some terms depend on.
  const double diffSqMC = ps.mSqMother()    - ps.mSq( m_noRes );
  const double diffSqAB = ps.mSq( m_resoA ) - ps.mSq( m_resoB );

  // Zemach tensor for l = 1.
  const double zemach1  = mSqAC - mSqBC - diffSqMC * diffSqAB / mSqAB;

  if ( m_l == 1 ) return zemach1;

  if ( m_l == 2 ) {
    // Squared mass sums that some terms depend on.
    const double sumSqMC = ps.mSqMother()    + ps.mSq( m_noRes );
    const double sumSqAB = ps.mSq( m_resoA ) + ps.mSq( m_resoB );

    double first  = mSqAB - 2. * sumSqMC + std::pow( diffSqMC, 2 ) / mSqAB;
    double second = mSqAB - 2. * sumSqAB + std::pow( diffSqAB, 2 ) / mSqAB;

    return std::pow( zemach1, 2 ) - first * second / 3.;
  }
  return 0.;
}


inline double Resonance::helicity( const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC ) const
{
  if ( m_l == 0 ) return 1.;

  // Squared mass differences that some terms depend on.
  const double diffSqMC = ps.mSqMother()    - ps.mSq( m_noRes );
  const double diffSqAB = ps.mSq( m_resoA ) - ps.mSq( m_resoB );

  // Zemach tensor for l = 1.
  const double hel1  = mSqAC - mSqBC - diffSqMC * diffSqAB / mSq();

  if ( m_l == 1 ) return hel1;

  if ( m_l == 2 ) {
    // Squared mass sums that some terms depend on.
    const double& sumSqMC = ps.mSqMother()    + ps.mSq( m_noRes );
    const double& sumSqAB = ps.mSq( m_resoA ) + ps.mSq( m_resoB );

    double first  = mSqAB - 2. * sumSqMC + std::pow( diffSqMC, 2 ) / mSq();
    double second = mSqAB - 2. * sumSqAB + std::pow( diffSqAB, 2 ) / mSq();

    return std::pow( hel1, 2 ) - first * second / 3.;
  }
  return 0.;
}

inline double Resonance::blattWeisskopfPrime(const PhaseSpace& ps, const double& mSqAB) const
{
  if ( m_l == 0 ) return 1.;

  double q0 = this->q( ps, mSq() );
  double qm = this->q( ps, mSqAB );
  double rq0Sq = std::pow( r()*q0 , 2 );
  double rqmSq = std::pow( r()*qm , 2 );

  if ( m_l == 1 ) return std::sqrt( ( 1 + rq0Sq )/( 1 + rqmSq ) );
  if ( m_l == 2 ) return std::sqrt( ( 9 + 3*rq0Sq + std::pow( rq0Sq , 2 ) )/( 9 + 3*rqmSq + std::pow( rqmSq , 2 ) ) );
  return 1.;
}

inline double Resonance::blattWeisskopfPrimeP(const PhaseSpace& ps, const double& mSqAB) const
{
  if ( m_l == 0 ) return 1.;

  double p0 = this->p( ps, this->mSq() );
  double pm = this->p( ps, mSqAB       );
  double rp0Sq = std::pow( r()*p0 , 2 );
  double rpmSq = std::pow( r()*pm , 2 );

  if ( m_l == 1 ) return std::sqrt( ( 1 + rp0Sq )/( 1 + rpmSq ) );
  if ( m_l == 2 ) return std::sqrt( ( 9 + 3*rp0Sq + std::pow( rp0Sq , 2 ) )/( 9 + 3*rpmSq + std::pow( rpmSq , 2 ) ) );
  return 0.;
}

double Resonance::blattWeisskopf(const PhaseSpace& ps, const double& mSqAB) const 
{
  if ( m_l == 0 ) return 1.;

  double qm = this->q( ps, mSqAB );
  double rqmSq = std::pow( r()*qm , 2 );

  if ( m_l == 1 ) return std::sqrt( ( 2 * rqmSq )/( 1 + rqmSq ) );
  if ( m_l == 2 ) return std::sqrt( ( 13 * std::pow( rqmSq , 2 ) )/( 9 + 3*rqmSq + std::pow( rqmSq , 2 ) ) );
  return 0.;
}

double Resonance::angular(const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const
{
  if ( m_helicity ) return this->helicity(ps, mSqAB, mSqAC, mSqBC) * this->blattWeisskopfPrime(ps, mSqAB);
  return this->zemach(ps, mSqAB, mSqAC, mSqBC) * this->blattWeisskopfPrime(ps, mSqAB);
}