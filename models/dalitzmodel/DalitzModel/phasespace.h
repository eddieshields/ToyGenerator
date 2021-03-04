#ifndef DALITZMODEL_PHASESPACE_H
#define DALITZMODEL_PHASESPACE_H

#include <iostream>
#include <cmath>

#include "types.h"

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
  const real_t m(const int& i) const;
  const real_t mSq(const int& i) const;

  const real_t mMother() const { return m_mMother; }
  const real_t m1() const { return m_m1; }
  const real_t m2() const { return m_m2; }
  const real_t m3() const { return m_m3; }

  const real_t mSqMother() const { return m_mSqMother; }
  const real_t mSq1() const { return m_mSq1; }
  const real_t mSq2() const { return m_mSq2; }
  const real_t mSq3() const { return m_mSq3; }

  const real_t mSqSum() const { return m_mSqSum; }

  const real_t mSq12min() const { return std::pow( (m_m1 + m_m2) , 2 ); }
  const real_t mSq12max() const { return std::pow( (m_mMother - m_m3) , 2 ); }
  const real_t mSq13min() const { return std::pow( (m_m1 + m_m3) , 2 ); }
  const real_t mSq13max() const { return std::pow( (m_mMother - m_m2) , 2 ); }
  const real_t mSq23min() const { return std::pow( (m_m2 + m_m3) , 2 ); }
  const real_t mSq23max() const { return std::pow( (m_mMother - m_m1) , 2 ); }

  const real_t mSq13min(const real_t& mSq12) const;
  const real_t mSq13max(const real_t& mSq12) const;
  const real_t mSq23min(const real_t& mSq12) const;
  const real_t mSq23max(const real_t& mSq12) const;

  const bool contains(const real_t& mSq12, const real_t& mSq13) const;
  const bool contains(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const;

  const real_t kallen(const real_t& x, const real_t& y, const real_t& z) const;

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