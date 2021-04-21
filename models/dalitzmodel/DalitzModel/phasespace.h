#ifndef DALITZMODEL_PHASESPACE_H
#define DALITZMODEL_PHASESPACE_H

#include <iostream>
#include <cmath>

#include "types.h"
#include "msgservice.h"

namespace DalitzModel {

class PhaseSpace
{
private:
  real_t m_mMother = {0.};
  real_t m_m1      = {0.};
  real_t m_m2      = {0.};
  real_t m_m3      = {0.};

  real_t m_mSqMother = {0.};
  real_t m_mSq1 = {0.};
  real_t m_mSq2 = {0.};
  real_t m_mSq3 = {0.};

  real_t m_mSqSum = {0.};

public:
  // Constructor/Destructor.
  PhaseSpace() = default;
  PhaseSpace(const real_t& mMother, const real_t& m1, const real_t& m2, const real_t& m3): 
    m_mMother( mMother ),
    m_m1( m1 ),
    m_m2( m2 ),
    m_m3( m3 )
  {
    m_mSqMother = std::pow( m_mMother , 2 );
    m_mSq1 = std::pow( m_m1 , 2 );
    m_mSq2 = std::pow( m_m2 , 2 );
    m_mSq3 = std::pow( m_m3 , 2 );

    m_mSqSum = std::pow( m_mMother , 2 ) + std::pow( m_m1 , 2 ) + std::pow( m_m2 , 2 ) + std::pow( m_m3 , 2);
  }
  PhaseSpace(const PhaseSpace& other) :
    m_mMother( other.m_mMother ),
    m_m1( other.m_m1 ),
    m_m2( other.m_m2 ),
    m_m3( other.m_m3 )
  {
    m_mSqMother = std::pow( m_mMother , 2 );
    m_mSq1 = std::pow( m_m1 , 2 );
    m_mSq2 = std::pow( m_m2 , 2 );
    m_mSq3 = std::pow( m_m3 , 2 );

    m_mSqSum = std::pow( m_mMother , 2 ) + std::pow( m_m1 , 2 ) + std::pow( m_m2 , 2 ) + std::pow( m_m3 , 2);
  }
  virtual ~PhaseSpace() {};

  // Getters.
  inline const real_t m(const int& i) const
  {
    switch (i)
    {
    case 0:
      return m_mMother;
    case 1:
      return m_m1;
    case 2:
      return m_m2;
    case 3:
      return m_m3;
    default:
      WARNING("Requested particle " << i << ", only 4 particles.");
    }
    return 0.;
  }

  inline const real_t mSq(const int& i) const
  {
    switch (i)
    {
    case 0:
      return m_mSqMother;
    case 1:
      return m_mSq1;
    case 2:
      return m_mSq2;
    case 3:
      return m_mSq3;
    default:
      WARNING("Requested particle " << i << ", only 4 particles.");
    }
    return 0.;
  }

  inline const real_t mMother() const { return m_mMother; }
  inline const real_t m1() const { return m_m1; }
  inline const real_t m2() const { return m_m2; }
  inline const real_t m3() const { return m_m3; }

  inline const real_t mSqMother() const { return m_mSqMother; }
  inline const real_t mSq1() const { return m_mSq1; }
  inline const real_t mSq2() const { return m_mSq2; }
  inline const real_t mSq3() const { return m_mSq3; }

  inline const real_t mSqSum() const { return m_mSqSum; }

  inline const real_t mSq12min() const { return std::pow( (m_m1 + m_m2) , 2 ); }
  inline const real_t mSq12max() const { return std::pow( (m_mMother - m_m3) , 2 ); }
  inline const real_t mSq13min() const { return std::pow( (m_m1 + m_m3) , 2 ); }
  inline const real_t mSq13max() const { return std::pow( (m_mMother - m_m2) , 2 ); }
  inline const real_t mSq23min() const { return std::pow( (m_m2 + m_m3) , 2 ); }
  inline const real_t mSq23max() const { return std::pow( (m_mMother - m_m1) , 2 ); }

  inline const real_t mSq13min(const real_t& mSq12) const
  {
    real_t first  = std::pow( m_mSqMother + m_mSq1 - m_mSq2 - m_mSq3, 2 );
    real_t second = std::sqrt( kallen( mSq12, m_mSq1     , m_mSq2 ) );
    real_t third  = std::sqrt( kallen( mSq12, m_mSqMother, m_mSq3 ) );

    return ( first - std::pow( second + third, 2 ) ) / ( 4. * mSq12 );
  }

  inline const real_t mSq13max(const real_t& mSq12) const
  {
    real_t first  = std::pow( m_mSqMother + m_mSq1 - m_mSq2 - m_mSq3, 2 );
    real_t second = std::sqrt( kallen( mSq12, m_mSq1     , m_mSq2 ) );
    real_t third  = std::sqrt( kallen( mSq12, m_mSqMother, m_mSq3 ) );

    return ( first - std::pow( second - third, 2 ) ) / ( 4. * mSq12 );
  }

  inline const real_t mSq23min(const real_t& mSq12) const
  {
    real_t first  = std::pow( m_mSqMother - m_mSq1 + m_mSq2 - m_mSq3, 2 );
    real_t second = std::sqrt( kallen( mSq12, m_mSq1     , m_mSq2 ) );
    real_t third  = std::sqrt( kallen( mSq12, m_mSqMother, m_mSq3 ) );

    return ( first - std::pow( second + third, 2 ) ) / ( 4. * mSq12 );
  }

  inline const real_t mSq23max(const real_t& mSq12) const
  {
    real_t first  = std::pow( m_mSqMother - m_mSq1 + m_mSq2 - m_mSq3, 2 );
    real_t second = std::sqrt( kallen( mSq12, m_mSq1     , m_mSq2 ) );
    real_t third  = std::sqrt( kallen( mSq12, m_mSqMother, m_mSq3 ) );

    return ( first - std::pow( second - third, 2 ) ) / ( 4. * mSq12 );
  }

  inline const bool contains(const real_t& mSq12, const real_t& mSq13) const
  {
    const real_t& mSq23 = m_mSqSum - mSq12 - mSq13;

    return ( ( mSq13 > mSq13min( mSq12 ) ) && ( mSq13 < mSq13max( mSq12 ) ) &&
             ( mSq23 > mSq23min( mSq12 ) ) && ( mSq23 < mSq23max( mSq12 ) ) );
  }

  inline const bool contains(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
  {
      if ( ( mSq12min()      < mSq12 && mSq12 < mSq12max() ) 
        && ( mSq13min(mSq12) < mSq13 && mSq13 < mSq13max(mSq12) ) 
        && ( mSq23min(mSq12) < mSq23 && mSq23 < mSq23max(mSq12) ) ) return true;
      return false;
  }

  inline const real_t kallen(const real_t& x, const real_t& y, const real_t& z) const
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

  // Operators.
  friend std::ostream& operator<<(std::ostream& os, const PhaseSpace& ps)
  {
    os << "mMother " << ps.m_mMother << "\n";
    os << "m1 " << ps.m_m1 << "\n";
    os << "m2 " << ps.m_m2 << "\n";
    os << "m3 " << ps.m_m3;
    return os;
  }
};

} // DalitzModel

#endif