#include "relbreitwigner.h"

using namespace DalitzModel;

const double RelBreitWigner::runningWidth(const PhaseSpace& ps, const double& mSqAB) const
{
    return width()*( rho( ps, mSqAB )/rho( ps, mSq() ) )*std::pow( blattWeisskopf(ps, mSqAB) , 2 );
}

const std::complex< double > RelBreitWigner::propagator(const PhaseSpace& ps, const double& mSqAB) const
{
    const std::complex< double > I( 0., 1. );

    return 1./( mSq() - mSqAB - m()*I*runningWidth(ps, mSqAB) );
}

RelBreitWigner* RelBreitWigner::cnj() const
{
  RelBreitWigner* res = new RelBreitWigner( *this );
  res->makeCnj();
  return res;
}

RelBreitWigner* RelBreitWigner::copy() const
{
  return new RelBreitWigner( *this );
}