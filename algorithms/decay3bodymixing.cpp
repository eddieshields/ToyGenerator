#include "decay3bodymixing.h"

void Decay3BodyMixing::operator()(Event& ev)
{
  ev.updateMasses();
  ev["pid"] = ( ( ev.mother().flavour() == 1 ) ? 421 : -421 );
  ev.pdf = m_amp.ASq( ev );
}