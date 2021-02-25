#ifndef DALITZMODEL_PHASESPACE_H
#define DALITZMODEL_PHASESPACE_H

#include <iostream>
#include <cmath>

namespace DalitzModel {

class PhaseSpace
{
private:
  double m_mMother = {0.};
  double m_m1      = {0.};
  double m_m2      = {0.};
  double m_m3      = {0.};

  double m_mSqMother = {0.};
  double m_mSq1 = {0.};
  double m_mSq2 = {0.};
  double m_mSq3 = {0.};

  double m_mSqSum = {0.};

public:
  // Constructor/Destructor.
  PhaseSpace() = default;
  PhaseSpace(const double& mMother, const double& m1, const double& m2, const double& m3): 
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
  const double m(const int& i) const;
  const double mSq(const int& i) const;

  const double mMother() const { return m_mMother; }
  const double m1() const { return m_m1; }
  const double m2() const { return m_m2; }
  const double m3() const { return m_m3; }

  const double mSqMother() const { return m_mSqMother; }
  const double mSq1() const { return m_mSq1; }
  const double mSq2() const { return m_mSq2; }
  const double mSq3() const { return m_mSq3; }

  const double mSqSum() const { return m_mSqSum; }

  const double mSq12min() const { return std::pow( (m_m1 + m_m2) , 2 ); }
  const double mSq12max() const { return std::pow( (m_mMother - m_m3) , 2 ); }
  const double mSq13min() const { return std::pow( (m_m1 + m_m3) , 2 ); }
  const double mSq13max() const { return std::pow( (m_mMother - m_m2) , 2 ); }
  const double mSq23min() const { return std::pow( (m_m2 + m_m3) , 2 ); }
  const double mSq23max() const { return std::pow( (m_mMother - m_m1) , 2 ); }

  const double mSq13min(const double& mSq12) const;
  const double mSq13max(const double& mSq12) const;
  const double mSq23min(const double& mSq12) const;
  const double mSq23max(const double& mSq12) const;

  const bool contains(const double& mSq12, const double& mSq13) const;
  const bool contains(const double& mSq12, const double& mSq13, const double& mSq23) const;

  const double kallen(const double& x, const double& y, const double& z) const;

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