#include "compositeparam.h"

void CompositeParam::operator()(Event& ev)
{
  Particle part = ev.particle(m_particle_index);
  for (auto& i : m_particles_indices) {
    part += ev.particle(i);
  }
  eval(part);
}