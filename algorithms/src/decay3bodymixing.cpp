#include "decay3bodymixing.h"

void Decay3BodyMixing::operator()(Event& ev)
{
  // Update masses to get dalitz variables.
  ev.updateMasses();
  /**
   * The amplitude when mixing is involved is calculated as.
   * For D0
   *   A = | gp(t)*Adir + gm(t)*p/q*Abar |^2
   * For D0bar
   *   A = | gm(t)*p/q*Adir + gp(t)*Abar |^2
   * 
   * where
   * gp(t) = cosh( z * t/2 )
   * gm(t) = sinh( z * t/2 )
   * 
   * and z = - ( y + ix )
   * 
   * Not that the lifetimes are normalized to 1. So the Gamma terms are not needed.
   */
  if ( ev.mother().flavour() == 1 ) {
    ev.pdf = std::norm( gp( ev.mother().time() ) * m_amp.Adir( ev["mSq12"] , ev["mSq13"] , ev["mSq23"] ) + gm( ev.mother().time() ) * ( q()/p() ) * m_amp.Abar(  ev["mSq12"] , ev["mSq13"] , ev["mSq23"] ) );
  } else {
    ev.pdf = std::norm( gm( ev.mother().time() ) * ( p()/q() ) * m_amp.Adir( ev["mSq12"] , ev["mSq13"] , ev["mSq23"] ) + gp( ev.mother().time() ) * m_amp.Abar(  ev["mSq12"] , ev["mSq13"] , ev["mSq23"] ) );
  }
  return;
}

const complex_t Decay3BodyMixing::gp(const real_t& t)
{
  return std::cosh( z() * ( t/2 ) );
}

const complex_t Decay3BodyMixing::gm(const real_t& t)
{
  return std::sinh( z() * ( t/2 ) );
}