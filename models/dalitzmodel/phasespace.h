#ifndef TOYGEN_PHASESPACE_H
#define TOYGEN_PHASESPACE_H

#include <iostream>
#include <cmath>

namespace DalitzModel {

class PhaseSpace
{
public:
  // Constructor/Destructor.
  PhaseSpace(const double& mMother, const double& m1, const double& m2, const double& m3)
  : _mMother( mMother ), _m1( m1 ), _m2( m2 ), _m3( m3 ) {};
  ~PhaseSpace() {};

  // Getters.
  const double m(const int& i) const;
  const double mSq(const int& i) const;

  const double mMother() const { return _mMother; }
  const double m1() const { return _m1; }
  const double m2() const { return _m2; }
  const double m3() const { return _m3; }

  const double mSqMother() const { return _mSqMother; }
  const double mSq1() const { return _mSq1; }
  const double mSq2() const { return _mSq2; }
  const double mSq3() const { return _mSq3; }

  const double mSqSum() const { return _mSqSum; }

  const double mSq12min() const { return std::pow( (_m1 + _m2) , 2 ); }
  const double mSq12max() const { return std::pow( (_mMother - _m3) , 2 ); }
  const double mSq13min() const { return std::pow( (_m1 + _m3) , 2 ); }
  const double mSq13max() const { return std::pow( (_mMother - _m2) , 2 ); }
  const double mSq23min() const { return std::pow( (_m2 + _m3) , 2 ); }
  const double mSq23max() const { return std::pow( (_mMother - _m1) , 2 ); }

  const double mSq13min(const double& mSq12) const;
  const double mSq13max(const double& mSq12) const;
  const double mSq23min(const double& mSq12) const;
  const double mSq23max(const double& mSq12) const;

  const bool contains(const double& mSq12, const double& mSq13) const;
  const bool contains(const double& mSq12, const double& mSq13, const double& mSq23) const;

  const double kallen(const double& x, const double& y, const double& z) const;
private:
  const double _mMother;
  const double _m1;
  const double _m2;
  const double _m3;

  const double _mSqMother = std::pow( _mMother , 2 );
  const double _mSq1 = std::pow( _m1 , 2 );
  const double _mSq2 = std::pow( _m2 , 2 );
  const double _mSq3 = std::pow( _m3 , 2 );

  const double _mSqSum = std::pow( _mMother , 2 ) + std::pow( _m1 , 2 ) + std::pow( _m2 , 2 ) + std::pow( _m3 , 2);

};

}

#endif