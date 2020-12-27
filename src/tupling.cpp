#include "tupling.h"

void Tupling::operator()(Event& ev)
{
  if ( !ev.Accept ) return;
  ev.updateMasses();

  /*
  for (int i = 0; i < ev.m_particles.size(); i++) {
    ev.m_v[std::to_string(i)+"_PX"] = ev.m_particles[i].momentum().Px();
    ev.m_v[std::to_string(i)+"_PY"] = ev.m_particles[i].momentum().Py();
    ev.m_v[std::to_string(i)+"_PZ"] = ev.m_particles[i].momentum().Pz();
    ev.m_v[std::to_string(i)+"_E"] = ev.m_particles[i].momentum().E();
    ev.m_v[std::to_string(i)+"_PT"] = ev.m_particles[i].momentum().Pt();
    ev.m_v[std::to_string(i)+"_P"] = ev.m_particles[i].momentum().P();
  }
  */

  return;
}