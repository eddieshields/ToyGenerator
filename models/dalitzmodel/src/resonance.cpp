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
    reso->m_noRes = this->m_resoB;
  }
  reso->m_name = this->m_name + "_cnj";
  return reso;
}

const complex_t Resonance::evaluate(const PhaseSpace& ps, const real_t& mSq12, const real_t& mSq13, const real_t& mSq23)
{
  if ( !ps.contains(mSq12, mSq13) ) return 0.;
  real_t mSqAB = M2AB(mSq12, mSq13, mSq23);
  real_t mSqAC = M2AC(mSq12, mSq13, mSq23);
  real_t mSqBC = M2BC(mSq12, mSq13, mSq23);
  return m_coeff * propagator( ps , mSqAB ) * angular( ps , mSqAB , mSqAC , mSqBC);
}

const complex_t Resonance::evaluate(const PhaseSpace& ps, const real_t& mSq12, const real_t& mSq13)
{
  real_t mSq23 = ps.mSqSum() - mSq12 - mSq13;
  return evaluate(ps, mSq12, mSq13, mSq23);
}

const real_t Resonance::M2AB(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  if ( m_noRes == 3 ) return mSq12;
  if ( m_noRes == 2 ) return mSq13;
  if ( m_noRes == 1 ) return mSq23;
  return 0.;
}

const real_t Resonance::M2AC(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  if ( m_resoB == 3 ) return mSq12;
  if ( m_resoB == 2 ) return mSq13;
  if ( m_resoB == 1 ) return mSq23;
  return 0.;
}

const real_t Resonance::M2BC(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  if ( m_resoA == 3 ) return mSq12;
  if ( m_resoA == 2 ) return mSq13;
  if ( m_resoA == 1 ) return mSq23;
  return 0.;
}

real_t Resonance::kallen(const real_t& x, const real_t& y, const real_t& z) const
{
  return std::pow( x , 2 ) + std::pow( y , 2 ) + std::pow( z , 2) - 2*x*y - 2*x*z - 2*y*z;
}

real_t Resonance::q(const PhaseSpace& ps, const real_t& mSqAB) const
{
  return std::sqrt( this->kallen( mSqAB, ps.mSq( m_resoA ), ps.mSq( m_resoB ) ) )/( 2*std::sqrt(mSqAB) );
}

real_t Resonance::p(const PhaseSpace& ps, const real_t& mSqAB) const
{
  return std::sqrt( this->kallen( mSqAB, ps.mSqMother(), ps.mSq( m_noRes ) ) )/( 2*std::sqrt(mSqAB) );
}

real_t Resonance::rho(const PhaseSpace& ps, const real_t& mSqAB, const real_t& mSq1, const real_t& mSq2) const
{
  return std::sqrt( this->kallen( mSqAB, mSq1 , mSq2 ) )/mSqAB;
}

real_t Resonance::rho(const PhaseSpace& ps, const real_t& mSqAB) const
{
  return std::sqrt( this->kallen( mSqAB, ps.mSq( m_resoA ) , ps.mSq( m_resoB ) ) )/mSqAB;
}

real_t Resonance::zemach( const PhaseSpace& ps, const real_t& mSqAB, const real_t& mSqAC, const real_t& mSqBC ) const
{
  if ( m_l == 0 ) return 1.f;

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
  return 0.f;
}


real_t Resonance::helicity( const PhaseSpace& ps, const real_t& mSqAB, const real_t& mSqAC, const real_t& mSqBC ) const
{
  if ( m_l == 0 ) return 1.f;

  // Squared mass differences that some terms depend on.
  const real_t diffSqMC = ps.mSqMother()    - ps.mSq( m_noRes );
  const real_t diffSqAB = ps.mSq( m_resoA ) - ps.mSq( m_resoB );

  // Zemach tensor for l = 1.
  const real_t hel1  = mSqAC - mSqBC - diffSqMC * diffSqAB / mSq();

  if ( m_l == 1 ) return hel1;

  if ( m_l == 2 ) {
    // Squared mass sums that some terms depend on.
    const real_t& sumSqMC = ps.mSqMother()    + ps.mSq( m_noRes );
    const real_t& sumSqAB = ps.mSq( m_resoA ) + ps.mSq( m_resoB );

    real_t first  = mSqAB - 2. * sumSqMC + std::pow( diffSqMC, 2 ) / mSq();
    real_t second = mSqAB - 2. * sumSqAB + std::pow( diffSqAB, 2 ) / mSq();

    return std::pow( hel1, 2 ) - first * second / 3.f;
  }
  return 0.f;
}

real_t Resonance::blattWeisskopfPrime(const PhaseSpace& ps, const real_t& mSqAB) const
{
  if ( m_l == 0 ) return 1.;

  real_t q0 = this->q( ps, mSq() );
  real_t qm = this->q( ps, mSqAB );
  real_t rq0Sq = std::pow( r()*q0 , 2 );
  real_t rqmSq = std::pow( r()*qm , 2 );

  if ( m_l == 1 ) return std::sqrt( ( 1 + rq0Sq )/( 1 + rqmSq ) );
  if ( m_l == 2 ) return std::sqrt( ( 9 + 3*rq0Sq + std::pow( rq0Sq , 2 ) )/( 9 + 3*rqmSq + std::pow( rqmSq , 2 ) ) );
  return 1.f;
}

real_t Resonance::blattWeisskopfPrimeP(const PhaseSpace& ps, const real_t& mSqAB) const
{
  if ( m_l == 0 ) return 1.f;

  real_t p0 = this->p( ps, this->mSq() );
  real_t pm = this->p( ps, mSqAB       );
  real_t rp0Sq = std::pow( r()*p0 , 2 );
  real_t rpmSq = std::pow( r()*pm , 2 );

  if ( m_l == 1 ) return std::sqrt( ( 1 + rp0Sq )/( 1 + rpmSq ) );
  if ( m_l == 2 ) return std::sqrt( ( 9 + 3*rp0Sq + std::pow( rp0Sq , 2 ) )/( 9 + 3*rpmSq + std::pow( rpmSq , 2 ) ) );
  return 0.f;
}

real_t Resonance::blattWeisskopf(const PhaseSpace& ps, const real_t& mSqAB) const 
{
  if ( m_l == 0 ) return 1.f;

  real_t qm = this->q( ps, mSqAB );
  real_t rqmSq = std::pow( r()*qm , 2 );

  if ( m_l == 1 ) return std::sqrt( ( 2 * rqmSq )/( 1 + rqmSq ) );
  if ( m_l == 2 ) return std::sqrt( ( 13 * std::pow( rqmSq , 2 ) )/( 9 + 3*rqmSq + std::pow( rqmSq , 2 ) ) );
  return 0.f;
}

real_t Resonance::angular(const PhaseSpace& ps, const real_t& mSqAB, const real_t& mSqAC, const real_t& mSqBC) const
{
  if ( m_helicity ) return this->helicity(ps, mSqAB, mSqAC, mSqBC) * this->blattWeisskopfPrime(ps, mSqAB);
  return this->zemach(ps, mSqAB, mSqAC, mSqBC) * this->blattWeisskopfPrime(ps, mSqAB);
}