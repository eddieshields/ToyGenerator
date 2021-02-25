#include "flatte.h"

using namespace DalitzModel::LineShape;

const complex_t Flatte::propagator(const PhaseSpace& ps, const double& mSqAB) const
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
  const std::complex< double > I( 0., 1. );

  const double mGamma0 = mass() * width();

  const double rho10 = rho( ps, mSq() , ps.mSq( m_resoA ) , ps.mSq( m_resoB ) );
  const double rho1  = rho( ps, mSqAB , ps.mSq( m_resoA ) , ps.mSq( m_resoB ) );
  const double g1    = gamma1Sq() * rho1 / rho10;

  const double rho20 = std::sqrt( kallen( mSq(), m02aSq(), m02bSq() ) ) / mSqAB;
  const double rho2  = std::sqrt( kallen( mSqAB, m02aSq(), m02bSq() ) ) / mSqAB;
  const double g2    = gamma2Sq() * rho2 / rho20;
  
  complex_t out = mGamma0 * gamma1Sq() / ( mSq() - mSqAB - I * mGamma0 * ( g1 + g2 ) * std::pow( blattWeisskopf( ps, mSqAB ), 2 ) );

  return out;
}

const complex_t Flatte::babar2005_propagator(const PhaseSpace& ps, const double& mSqAB) const
{
  const std::complex< double > I( 0., 1. );
  const double rho1  = rho( ps, mSqAB , ps.mSq( m_resoA ) , ps.mSq( m_resoB ) );
  const double rho2  = std::sqrt( kallen( mSqAB, m02aSq(), m02bSq() ) ) / mSqAB;

  return 1. / mSq() - mSqAB - I * ( rho1 * gamma1Sq() + rho2 * gamma2Sq() );
}

const complex_t Flatte::babar2008_propagator(const PhaseSpace& ps, const double& mSqAB) const
{
  const std::complex< double > I( 0., 1. );
  const double rho1  = rho( ps, mSqAB , ps.mSq( m_resoA ) , ps.mSq( m_resoB ) );
  const double rho2  = rho( ps, mSqAB, m02aSq(), m02bSq() );

  return gamma2() / mSq() - mSqAB - I * ( rho1 * gamma1Sq() + rho2 * gamma2Sq() );
}

const complex_t Flatte::babar2010_propagator(const PhaseSpace& ps, const double& mSqAB) const
{
  const std::complex< double > I( 0., 1. );
  const double rho2  = rho( ps, mSqAB , ps.mSq( m_resoA ) , ps.mSq( m_resoB ) );
  const double rho1  = std::sqrt( kallen( mSqAB, this->m02aSq(), this->m02bSq() ) ) / mSqAB;

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