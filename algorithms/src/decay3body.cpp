#include "decay3body.h"

void Decay3Body::operator()(Event& ev)
{
  ev.updateMasses();
  ev.pdf = m_amp.AdirSq( ev["mSq12"] , ev["mSq13"] );
}