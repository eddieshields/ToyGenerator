#include "generator.h"

void Generator::operator()(Event& ev)
{
  // Generate event.
  m_phsp.Generate();

  // 
  for (int i = 0; i < m_daughters.size(); i++) {
    TLorentzVector* vec = m_phsp.GetDecay(i);
    ev.m_particles[i].m_p = *vec;
  }

  return;
}