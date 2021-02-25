#include "flatte.h"

using namespace DalitzModel::LineShape;

const complex_t Flatte::propagator(const PhaseSpace& ps, const real_t& mSqAB) const
{
  // If specific parameterisation is called.
  switch (m_parameterisation)
  {
  case Parameterisation::BaBar2005:
    return babar2005_propagator( ps , mSqAB );
  case Parameterisation::BaBar2008:
    return babar2008_propagator( ps , mSqAB );
  case Parameterisation::BaBar2010:
    return babar2010_propagator( ps , mSqAB);
  default:
    break;
  }
  const complex_t I( 0., 1. );

  const real_t mGamma0 = mass() * width();

  const real_t rho10 = rho( ps, mSq() , ps.mSq( m_resoA ) , ps.mSq( m_resoB ) );
  const real_t rho1  = rho( ps, mSqAB , ps.mSq( m_resoA ) , ps.mSq( m_resoB ) );
  const real_t g1    = gamma1Sq() * rho1 / rho10;

  const real_t rho20 = std::sqrt( kallen( mSq(), m02aSq(), m02bSq() ) ) / mSqAB;
  const real_t rho2  = std::sqrt( kallen( mSqAB, m02aSq(), m02bSq() ) ) / mSqAB;
  const real_t g2    = gamma2Sq() * rho2 / rho20;
  
  complex_t out = mGamma0 * gamma1Sq() / ( mSq() - mSqAB - I * mGamma0 * ( g1 + g2 ) * (real_t)std::pow( blattWeisskopf( ps, mSqAB ), 2 ) );

  return out;
}

const complex_t Flatte::babar2005_propagator(const PhaseSpace& ps, const real_t& mSqAB) const
{
  const std::complex< real_t > I( 0.f , 1.f );
  const real_t rho1  = rho( ps, mSqAB , ps.mSq( m_resoA ) , ps.mSq( m_resoB ) );
  const real_t rho2  = std::sqrt( kallen( mSqAB, m02aSq(), m02bSq() ) ) / mSqAB;

  return 1.f / mSq() - mSqAB - I * ( rho1 * gamma1Sq() + rho2 * gamma2Sq() );
}

const complex_t Flatte::babar2008_propagator(const PhaseSpace& ps, const real_t& mSqAB) const
{
  const complex_t I( 0., 1. );
  const real_t rho1  = rho( ps, mSqAB , ps.mSq( m_resoA ) , ps.mSq( m_resoB ) );
  const real_t rho2  = rho( ps, mSqAB, m02aSq(), m02bSq() );

  return gamma2() / mSq() - mSqAB - I * ( rho1 * gamma1Sq() + rho2 * gamma2Sq() );
}

const complex_t Flatte::babar2010_propagator(const PhaseSpace& ps, const real_t& mSqAB) const
{
  const std::complex< real_t > I( 0., 1. );
  const real_t rho2  = rho( ps, mSqAB , ps.mSq( m_resoA ) , ps.mSq( m_resoB ) );
  const real_t rho1  = std::sqrt( kallen( mSqAB, this->m02aSq(), this->m02bSq() ) ) / mSqAB;

  return this->gamma1() / this->mSq() - mSqAB - I * ( rho1 * this->gamma1Sq() + rho2 * this->gamma2Sq() );
}

void Flatte::SetParameterisation(std::string parameterisation)
{
  if ( parameterisation == "BaBar2005" || parameterisation == "babar2005" ) {
    INFO("Will use BaBar 2005 Flatte parameterisation");
    m_parameterisation = Parameterisation::BaBar2005;
  } else if ( parameterisation == "BaBar2008" || parameterisation == "babar2008" ) {
    INFO("Will use BaBar 2008 Flatte parameterisation");
    m_parameterisation = Parameterisation::BaBar2008;
  } else if ( parameterisation == "BaBar2010" || parameterisation == "babar2010" ) {
    INFO("Will use BaBar 2010 Flatte parameterisation");
    m_parameterisation = Parameterisation::BaBar2010;
  }
  return;
}

Flatte::Parameterisation Flatte::m_parameterisation = Flatte::Parameterisation::None;

Flatte* Flatte::copy() const
{
  return new Flatte(*this);
}