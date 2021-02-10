#include "dalitzmixing.h"

using namespace DalitzModel;

const std::complex<double> DalitzMixing::A(Event& ev)
{
  return A( ev.mother().flavour() , ev.mother().truetime() , ev["mSq12"] , ev["mSq13"] , ev["mSq23"] );
}

const std::complex<double> DalitzMixing::A(const int& flav, const double& t, const double& mSq12, const double& mSq13)
{
  if ( flav == 1 ) {
    return gp( t ) * m_amp.Adir( mSq12 , mSq13 ) + gm( t ) * ( q()/p() ) * m_amp.Abar(  mSq12 , mSq13 );
  } else {
    return gm( t ) * ( p()/q() ) * m_amp.Adir( mSq12 , mSq13 ) + gp( t ) * m_amp.Abar(  mSq12 , mSq13 );
  }
}

const std::complex<double> DalitzMixing::A(const int& flav, const double& t, const double& mSq12, const double& mSq13, const double& mSq23)
{
  if ( flav == 1 ) {
    return gp( t ) * m_amp.Adir( mSq12 , mSq13 , mSq23 ) + gm( t ) * ( q()/p() ) * m_amp.Abar(  mSq12 , mSq13 , mSq23 );
  } else {
    return gm( t ) * ( p()/q() ) * m_amp.Adir( mSq12 , mSq13 , mSq23 ) + gp( t ) * m_amp.Abar(  mSq12 , mSq13 , mSq23 );
  }
}

const double DalitzMixing::ASq(Event& ev)
{
  return std::norm( A(ev) );
}

const double DalitzMixing::ASq(const int& flav, const double& t, const double& mSq12, const double& mSq13)
{
  return std::norm( A( flav , t , mSq12 , mSq13 ) );
}

const double DalitzMixing::ASq(const int& flav, const double& t, const double& mSq12, const double& mSq13, const double& mSq23)
{
  return std::norm( A( flav , t , mSq12 , mSq13 , mSq23 ) );
}

const std::complex<double> DalitzMixing::gp(const double& t)
{
  std::complex<double> I(0,1);
  return std::cos( - I * z() * ( t/2 ) );
}

const std::complex<double> DalitzMixing::gm(const double& t)
{
  std::complex<double> I(0,1);
  return std::sin( - I * z() * ( t/2 ) );
}