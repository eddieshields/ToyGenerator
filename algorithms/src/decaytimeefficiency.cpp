#include "decaytimeefficiency.h"

void DecayTimeEfficiency::operator()(Event& ev)
{
  real_t eff = m_acceptance->GetBinContent( m_acceptance->FindBin( ev.mother().time() ) );
  if ( eff > Random::flat(0.,m_max) ) {
    ev.Accept = true;
  } else {
    ev.Accept = false;
  }

  return;
}