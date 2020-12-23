#include "efficiency.h"

void Efficiency::operator()(Event& ev)
{
  ev.efficiency = 1.;

  return;
}