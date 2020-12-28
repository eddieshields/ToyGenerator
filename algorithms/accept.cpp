#include "accept.h"

void Accept::operator()(Event& ev)
{
  if ( ev.pdf > Random::flat(0.,m_maxPdf) ) {
    ev.Accept = true;
  } else {
    ev.Accept = false;
  }
  return;
}