#include "generator.h"

void Generator::operator()(Event& ev)
{
  // Generate event.
  m_phsp.Generate();

  // 
  for (auto& x : ev.m_particles) {
    if ( !x.second.isStable() ) continue;
    TLorentzVector* p = x.second.momentum();
    p = m_phsp.GetDecay(0);
  }

  return;
}