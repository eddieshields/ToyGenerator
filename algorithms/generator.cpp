#include "generator.h"

void Generator::operator()(Event& ev)
{
  // Need to add multithreaded support so we dont need new TGen in each loop.
  // Generate event.
  TGenPhaseSpace phsp(m_phsp);
  phsp.Generate();

  // Add particles.
  int cnj = 1;
  if ( rand() % 2 ) cnj *= -1;;
  for (int i = 0; i < m_particles.size(); i++) {
    ev.particles().push_back( Particle() );
    ev.particle(i).charge() = m_charges[i] * cnj;
    ev.particle(i).flavour() = m_flavours[i];
    if ( !i ) continue;
    ev.daughter(i).momentum() = *phsp.GetDecay(i-1);
  }

  // Set decay time.
  if ( !ev.mother().charge() ) ev.mother().flavour() = ( Random::integer() ? -1 : 1 );
  ev.mother().isStable() = false;
  ev.mother().time() = Random::exponential();

  return;
}

