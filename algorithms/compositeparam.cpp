#include "compositeparam.h"

void CompositeParam::operator()(Event& ev)
{
  Particle part;
  for (auto& i : m_particles_indices) {
    part += ev.particle(i);
  }
  eval(part);
}