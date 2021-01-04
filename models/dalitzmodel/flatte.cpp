#include "flatte.h"

using namespace DalitzModel;

const double Flatte::g1(const PhaseSpace& ps, const double& mSqAB) const
{
  return gammaSq1()*( rho1(ps, mSqAB)/rho1(ps, mSq() ) );
}

const double Flatte::g2(const PhaseSpace& ps, const double& mSqAB) const
{
  return gammaSq2()*( rho2(ps, mSqAB)/rho2(ps, mSq() ) );
}

const double Flatte::rho1(const PhaseSpace& ps, const double& mSqAB) const
{
  return rho(ps, mSqAB);
}

const double Flatte::rho2(const PhaseSpace& ps, const double& mSqAB) const
{
  return std::sqrt( kallen( mSqAB, mSqA2(), mSqB2() ) )/mSqAB;
}

const std::complex< double > Flatte::propagator(const PhaseSpace& ps, const double& mSqAB) const
{
  const std::complex< double > I( 0., 1. );

  return ( gammaSq1()*mGamma() )/( mSq() - mSqAB - m()*width()*I*( g1(ps, mSqAB) + g2(ps, mSqAB) ) );
}

Flatte* Flatte::cnj() const
{
  Flatte* res = new Flatte( *this );
  res->makeCnj();
  return res;
}

Flatte* Flatte::copy() const
{
  return new Flatte( *this );
}