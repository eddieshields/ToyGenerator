#include "tupling.h"

void Tupling::operator()(Event& ev)
{
  if ( ev.Accept ) ev.updateMasses();

  return;
}