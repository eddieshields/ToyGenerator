#include "amplitude.h"

void Amplitude::operator()(Event& ev)
{
  ev.pdf = 1.;

  return;
}