#include "eventparam.h"

const double EventParam::eval(Event& ev)
{
  switch (m_type)
  {
  case Param::W:
    return ev.weight;
  case Param::PDF:
    return ev.pdf;
  default:
    FATAL(getName(m_type)+" does not exist.")
    return ev.weight;
  }
}