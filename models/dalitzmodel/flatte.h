#ifndef TOYGEN_FLATTE_H
#define TOYGEN_FLATTE_H

// Package.
#include "resonance.h"

namespace DalitzModel {

class Flatte : public Resonance
{
public:
  // Constructor/Destructor.
  Flatte(std::string name, const Coeff& coeff, const int& resA, const int& resB,
         const Parameter& mass, const Parameter& width, const int l, const Parameter& r,
         const Parameter& gam1, const Parameter& gam2, const Parameter& mA2, const Parameter& mB2)
         : Resonance(name, coeff, resA, resB, mass, width, l, r),
         _gam1( gam1.val() ), _gam2( gam2.val() ), _mA2( mA2.val() ), _mB2( mB2.val() )
         {};
  ~Flatte() {};

  //Getters
  const double gamma1() const { return _gam1; }
  const double gamma2() const { return _gam2; }
  const double gammaSq1() const { return std::pow( _gam1 , 2 ); }
  const double gammaSq2() const { return std::pow( _gam2 , 2 ); }

  const double mA2() const { return _mA2; }
  const double mB2() const { return _mB2; }

  const double mSqA2() const { return std::pow( _mA2 , 2 ); }
  const double mSqB2() const { return std::pow( _mB2 , 2 ); }

  const double mGamma() const { return _mass*_width; }

  const double g1(const PhaseSpace& ps, const double& mSqAB) const;
  const double g2(const PhaseSpace& ps, const double& mSqAB) const;

  const double rho1(const PhaseSpace& ps, const double& mSqAB) const;
  const double rho2(const PhaseSpace& ps, const double& mSqAB) const;

  const std::complex< double > propagator(const PhaseSpace& ps, const double& mSqAB ) const;

  Flatte* cnj() const;
  Flatte* copy() const;
private:
  const double _gam1;
  const double _gam2;
  const double _mA2;
  const double _mB2;
};

}

#endif