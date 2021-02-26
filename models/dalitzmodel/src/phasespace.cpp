#include "phasespace.h"

using namespace DalitzModel;

const real_t PhaseSpace::m(const int& i) const
{
  if ( i == 0 ) return m_mMother;
  if ( i == 1 ) return m_m1;
  if ( i == 2 ) return m_m2;
  if ( i == 3 ) return m_m3;
  return 0.;
}

const real_t PhaseSpace::mSq(const int& i) const
{
  if ( i == 0 ) return m_mSqMother;
  if ( i == 1 ) return m_mSq1;
  if ( i == 2 ) return m_mSq2;
  if ( i == 3 ) return m_mSq3;
  return 0.;
}

const real_t PhaseSpace::mSq13min(const real_t& mSq12 ) const
{
  real_t first  = std::pow( m_mSqMother + m_mSq1 - m_mSq2 - m_mSq3, 2 );
  real_t second = std::sqrt( kallen( mSq12, m_mSq1     , m_mSq2 ) );
  real_t third  = std::sqrt( kallen( mSq12, m_mSqMother, m_mSq3 ) );

  return ( first - std::pow( second + third, 2 ) ) / ( 4. * mSq12 );
}


const real_t PhaseSpace::mSq13max(const real_t& mSq12 ) const
{
  real_t first  = std::pow( m_mSqMother + m_mSq1 - m_mSq2 - m_mSq3, 2 );
  real_t second = std::sqrt( kallen( mSq12, m_mSq1     , m_mSq2 ) );
  real_t third  = std::sqrt( kallen( mSq12, m_mSqMother, m_mSq3 ) );

  return ( first - std::pow( second - third, 2 ) ) / ( 4. * mSq12 );
}

const real_t PhaseSpace::mSq23min( const real_t& mSq12 ) const
{
  real_t first  = std::pow( m_mSqMother - m_mSq1 + m_mSq2 - m_mSq3, 2 );
  real_t second = std::sqrt( kallen( mSq12, m_mSq1     , m_mSq2 ) );
  real_t third  = std::sqrt( kallen( mSq12, m_mSqMother, m_mSq3 ) );

  return ( first - std::pow( second + third, 2 ) ) / ( 4. * mSq12 );
}

const real_t PhaseSpace::mSq23max( const real_t& mSq12 ) const
{
  real_t first  = std::pow( m_mSqMother - m_mSq1 + m_mSq2 - m_mSq3, 2 );
  real_t second = std::sqrt( kallen( mSq12, m_mSq1     , m_mSq2 ) );
  real_t third  = std::sqrt( kallen( mSq12, m_mSqMother, m_mSq3 ) );

  return ( first - std::pow( second - third, 2 ) ) / ( 4. * mSq12 );
}

const bool PhaseSpace::contains( const real_t& mSq12, const real_t& mSq13 ) const
{
  const real_t& mSq23 = m_mSqSum - mSq12 - mSq13;

  return ( ( mSq13 > mSq13min( mSq12 ) ) && ( mSq13 < mSq13max( mSq12 ) ) &&
           ( mSq23 > mSq23min( mSq12 ) ) && ( mSq23 < mSq23max( mSq12 ) ) );
}

const bool PhaseSpace::contains(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
    if ( ( mSq12min()      < mSq12 && mSq12 < mSq12max() ) 
      && ( mSq13min(mSq12) < mSq13 && mSq13 < mSq13max(mSq12) ) 
      && ( mSq23min(mSq12) < mSq23 && mSq23 < mSq23max(mSq12) ) ) return true;
    return false;
}

const real_t PhaseSpace::kallen( const real_t& x, const real_t& y, const real_t& z ) const
{
  real_t result = 0.;
  result += std::pow( x, 2 );
  result += std::pow( y, 2 );
  result += std::pow( z, 2 );
  result -= 2. * x * y;
  result -= 2. * x * z;
  result -= 2. * y * z;

  return result;
}
