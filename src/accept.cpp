#include "accept.h"

void Accept::operator()(Event& ev)
{
  ev.Accept = true;

  return;
}