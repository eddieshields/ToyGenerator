#include "decay3bodymixing.h"

void Decay3BodyMixing::operator()(Event& ev)
{
  ev.updateMasses();
  ev.pdf = m_amp.ASq( ev );
}