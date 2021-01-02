#include "phasespace.h"

using namespace DalitzModel;

const double PhaseSpace::m(const int& i) const
{
  if ( i == 0 ) return _mMother;
  if ( i == 1 ) return _m1;
  if ( i == 2 ) return _m2;
  if ( i == 3 ) return _m3;
  return 0.;
}

const double PhaseSpace::mSq(const int& i) const
{
  if ( i == 0 ) return _mSqMother;
  if ( i == 1 ) return _mSq1;
  if ( i == 2 ) return _mSq2;
  if ( i == 3 ) return _mSq3;
  return 0.;
}

const double PhaseSpace::mSq13min(const double& mSq12 ) const
{
  double first  = std::pow( _mSqMother + _mSq1 - _mSq2 - _mSq3, 2 );
  double second = std::sqrt( kallen( mSq12, _mSq1     , _mSq2 ) );
  double third  = std::sqrt( kallen( mSq12, _mSqMother, _mSq3 ) );

  return ( first - std::pow( second + third, 2 ) ) / ( 4. * mSq12 );
}


const double PhaseSpace::mSq13max(const double& mSq12 ) const
{
  double first  = std::pow( _mSqMother + _mSq1 - _mSq2 - _mSq3, 2 );
  double second = std::sqrt( kallen( mSq12, _mSq1     , _mSq2 ) );
  double third  = std::sqrt( kallen( mSq12, _mSqMother, _mSq3 ) );

  return ( first - std::pow( second - third, 2 ) ) / ( 4. * mSq12 );
}

const double PhaseSpace::mSq23min( const double& mSq12 ) const
{
  double first  = std::pow( _mSqMother - _mSq1 + _mSq2 - _mSq3, 2 );
  double second = std::sqrt( kallen( mSq12, _mSq1     , _mSq2 ) );
  double third  = std::sqrt( kallen( mSq12, _mSqMother, _mSq3 ) );

  return ( first - std::pow( second + third, 2 ) ) / ( 4. * mSq12 );
}

const double PhaseSpace::mSq23max( const double& mSq12 ) const
{
  double first  = std::pow( _mSqMother - _mSq1 + _mSq2 - _mSq3, 2 );
  double second = std::sqrt( kallen( mSq12, _mSq1     , _mSq2 ) );
  double third  = std::sqrt( kallen( mSq12, _mSqMother, _mSq3 ) );

  return ( first - std::pow( second - third, 2 ) ) / ( 4. * mSq12 );
}

const bool PhaseSpace::contains( const double& mSq12, const double& mSq13 ) const
{
  const double& mSq23 = _mSqSum - mSq12 - mSq13;

  return ( mSq13 > mSq13min( mSq12 ) ) && ( mSq13 < mSq13max( mSq12 ) ) &&
         ( mSq23 > mSq23min( mSq12 ) ) && ( mSq23 < mSq23max( mSq12 ) );
}

const bool PhaseSpace::contains(const double& mSq12, const double& mSq13, const double& mSq23) const
{
    if ( ( mSq12min()      < mSq12 && mSq12 < mSq12max() ) 
      && ( mSq13min(mSq12) < mSq13 && mSq13 < mSq13max(mSq12) ) 
      && ( mSq23min(mSq12) < mSq23 && mSq23 < mSq23max(mSq12) ) ) return true;
    return false;
}

const double PhaseSpace::kallen( const double& x, const double& y, const double& z ) const
{
  double result = 0.;
  result += std::pow( x, 2 );
  result += std::pow( y, 2 );
  result += std::pow( z, 2 );
  result -= 2. * x * y;
  result -= 2. * x * z;
  result -= 2. * y * z;

  return result;
}