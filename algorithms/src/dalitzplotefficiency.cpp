#include "dalitzplotefficiency.h"

void DalitzPlotEfficiency::operator()(Event& ev)
{
  real_t eff = m_acceptance->FindBin( m_acceptance->FindBin( ev[m_mSqAB] , ev[m_mSqAC] ) );
  if ( eff > Random::flat(0.,m_max) ) {
    ev.Accept = true;
  } else {
    ev.Accept = false;
  }

  return;
}