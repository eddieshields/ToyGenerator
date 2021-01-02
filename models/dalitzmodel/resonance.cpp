#include "resonance.h"

using namespace DalitzModel;

bool Resonance::_helicity = false;

std::complex< double > Resonance::evaluate(const PhaseSpace& ps, const double& mSq12, const double& mSq13, const double& mSq23)
{
  if ( !ps.contains(mSq12, mSq13) ) return 0.;
  double mSqAB = M2AB(mSq12, mSq13, mSq23);
  double mSqAC = M2AC(mSq12, mSq13, mSq23);
  double mSqBC = M2BC(mSq12, mSq13, mSq23);

  return _coeff*_norm*propagator(ps, mSqAB)*angular(ps, mSqAB, mSqAC, mSqBC);
}

std::complex< double > Resonance::evaluate(const PhaseSpace& ps, const double& mSq12, const double& mSq13)
{
  double mSq23 = ps.mSqSum() - mSq12 - mSq13;
  return evaluate(ps, mSq12, mSq13, mSq23);
}

std::complex< double > Resonance::evaluateUnormalised(const PhaseSpace& ps, const double& mSq12, const double& mSq13, const double& mSq23)
{
  if ( !ps.contains(mSq12, mSq13) ) return 0.;
  double mSqAB = M2AB(mSq12, mSq13, mSq23);
  double mSqAC = M2AC(mSq12, mSq13, mSq23);
  double mSqBC = M2BC(mSq12, mSq13, mSq23);

  return propagator(ps, mSqAB)*angular(ps, mSqAB, mSqAC, mSqBC);
}

std::complex< double > Resonance::evaluateUnormalised(const PhaseSpace& ps, const double& mSq12, const double& mSq13)
{
  double mSq23 = ps.mSqSum() - mSq12 - mSq13;
  return evaluateUnormalised(ps, mSq12, mSq13, mSq23);
}

void Resonance::setNorm(const PhaseSpace& ps)
{
  double A = 0.;
  double step = (ps.mSq12max() - ps.mSq12min())/1000.;
  for (double mSq12 = ps.mSq12min(); mSq12 < ps.mSq12max(); mSq12 += step) {
    for (double mSq13 = ps.mSq13min(); mSq13 < ps.mSq13max(); mSq13 += step) {
      A += std::norm( evaluateUnormalised(ps, mSq12, mSq13) ) * std::pow( step , 2 );
    }
  }
  _norm = 1./A;
}

const double Resonance::M2AB(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  if ( _noRes == 3 ) return mSq12;
  if ( _noRes == 2 ) return mSq13;
  if ( _noRes == 1 ) return mSq23;
  return 0.;
}

const double Resonance::M2AC(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  if ( _resB == 3 ) return mSq12;
  if ( _resB == 2 ) return mSq13;
  if ( _resB == 1 ) return mSq23;
  return 0.;
}

const double Resonance::M2BC(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  if ( _resA == 3 ) return mSq12;
  if ( _resA == 2 ) return mSq13;
  if ( _resA == 1 ) return mSq23;
  return 0.;
}

inline double Resonance::kallen(const double& x, const double& y, const double& z) const
{
  return std::pow( x , 2 ) + std::pow( y , 2 ) + std::pow( z , 2) - 2*x*y - 2*x*z - 2*y*z;
}

double Resonance::p(const PhaseSpace& ps, const double& mSqAB) const
{
  return std::sqrt( kallen( mSqAB, ps.mSq( _resA ), ps.mSq( _resB ) ) )/( 2*std::sqrt(mSqAB) );
}

double Resonance::q(const PhaseSpace& ps, const double& mSqAB) const
{
  return std::sqrt( kallen( mSqAB, ps.mSqMother(), ps.mSq( _noRes ) ) )/( 2*std::sqrt(mSqAB) );
}

double Resonance::rho(const PhaseSpace& ps, const double& mSqAB) const
{
  return std::sqrt( kallen( mSqAB, ps.mSq( _resA ), ps.mSq( _resB ) ) )/mSqAB;
}

inline double Resonance::zemach(const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const
{
  if ( _l == 0 ) return 1;

  double diffSqMC = ps.mSqMother() - ps.mSq( _noRes );
  double diffSqAB = ps.mSq( _resA ) - ps.mSq( _resB );
  double zemach1 = mSqAC - mSqBC - (diffSqMC*diffSqAB)/mSqAB;

  if ( _l == 1 ) return zemach1;

  double sumSqMC = ps.mSqMother() + ps.mSq( _noRes );
  double sumSqAB = ps.mSq( _resA ) + ps.mSq( _resB );
  double first  = mSqAB - 2*sumSqMC + std::pow( diffSqMC , 2 )/mSqAB;
  double second = mSqAB - 2*sumSqAB + std::pow( diffSqAB , 2 )/mSqAB;
        
  if ( _l == 2 ) return std::pow( zemach1 , 2 ) - (first*second)/3;

  return 0.;
}

inline double Resonance::helicity(const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const
{
  if ( _l == 0 ) return 1.;

  const double& diffSqMC = ps.mSqMother() - ps.mSq( _noRes );
  const double& diffSqAB = ps.mSq( _resA ) - ps.mSq( _resB );
  const double& hel1  = mSqAC - mSqBC - diffSqMC * diffSqAB / mSq();

  if ( _l == 1 ) return hel1;

  const double& sumSqMC = ps.mSqMother()   + ps.mSq( _noRes );
  const double& sumSqAB = ps.mSq( _resA ) + ps.mSq( _resB );
  double first  = mSqAB - 2. * sumSqMC + std::pow( diffSqMC, 2 ) / mSq();
  double second = mSqAB - 2. * sumSqAB + std::pow( diffSqAB, 2 ) / mSq();

  if ( _l == 2 ) return std::pow( hel1, 2 ) - first * second / 3.;

  return 0.;
}

inline double Resonance::blattWeisskopfPrime(const PhaseSpace& ps, const double& mSqAB) const
{
  if ( _l == 0 ) return 1.;

  double q0 = q( ps, mSq() );
  double qm = q( ps, mSqAB );
  double rq0Sq = std::pow( r()*q0 , 2 );
  double rqmSq = std::pow( r()*qm , 2 );

  if ( _l == 1 ) return std::sqrt( ( 1 + rq0Sq )/( 1 + rqmSq ) );
  if ( _l == 2 ) return std::sqrt( ( 9 + 3*rq0Sq + std::pow( rq0Sq , 2 ) )/( 9 + 3*rqmSq + std::pow( rqmSq , 2 ) ) );
  return 0.;
}

inline double Resonance::blattWeisskopfPrimeP(const PhaseSpace& ps, const double& mSqAB) const
{
  if ( _l == 0 ) return 1.;

  double p0 = p( ps, mSq() );
  double pm = p( ps, mSqAB );
  double rp0Sq = std::pow( r()*p0 , 2 );
  double rpmSq = std::pow( r()*pm , 2 );

  if ( _l == 1 ) return std::sqrt( ( 1 + rp0Sq )/( 1 + rpmSq ) );
  if ( _l == 2 ) return std::sqrt( ( 9 + 3*rp0Sq + std::pow( rp0Sq , 2 ) )/( 9 + 3*rpmSq + std::pow( rpmSq , 2 ) ) );
  return 0.;
}

double Resonance::blattWeisskopf(const PhaseSpace& ps, const double& mSqAB) const 
{
  if ( _l == 0 ) return 1.;

  double q0 = q( ps, mSq() );
  double qm = q( ps, mSqAB );
  return std::pow( qm/q0 , _l )*blattWeisskopfPrime(ps, mSqAB);
}

double Resonance::angular(const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const
{
  if ( _helicity ) return helicity(ps, mSqAB, mSqAC, mSqBC)*blattWeisskopfPrimeP(ps, mSqAB)*blattWeisskopfPrime(ps, mSqAB);
  return zemach(ps, mSqAB, mSqAC, mSqBC)*blattWeisskopfPrimeP(ps, mSqAB)*blattWeisskopfPrime(ps, mSqAB);
}

void Resonance::makeCnj()
{
  if ( _isCnj ) return;

  _isCnj = true;
  if ( _resA == 2 ) {
    _resA = _resB;
    _resB = 6 - _resA - _noRes;
  }
  else {
    _resB = _noRes;
    _noRes = 6 - _resA - _resB;
  }
}