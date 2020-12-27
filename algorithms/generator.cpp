#include "generator.h"

void Generator::operator()(Event& ev)
{
  // Need to add multithreaded support so we dont need new TGen in each loop.
  // Generate event.
  TGenPhaseSpace phsp(m_phsp);
  phsp.Generate();

  for (int i = 0; i < m_daughters.size(); i++) {
    ev.m_particles.push_back( Particle() );
    ev.m_particles[i].m_p = *phsp.GetDecay(i);
  }

  
  ev.mother().time() = Random::exponential();
  
  if (rand() % 2) {
    ev.daughter(1).charge() = 1;
  } else {
    ev.daughter(1).charge() = -1;
  }
  
  return;
}