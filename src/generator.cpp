#include "generator.h"

void Generator::operator()(Event& ev)
{
  // Generate event.
  m_phsp.Generate();

  // 
  unsigned int SIZE = ev.m_p.size();
  for (unsigned int i = 0; i < SIZE; i++) {
    ev.m_p[i] = m_phsp.GetDecay(0);
  }

  return;
}