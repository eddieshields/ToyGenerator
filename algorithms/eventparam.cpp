#include "eventparam.h"

const double EventParam::eval(Event& ev)
{
  switch (m_type)
  {
  case Type::W:
    return ev.weight;
  case Type::PDF:
    return ev.pdf;
  default:
    FATAL(getName(m_type)+" does not exist.")
    return ev.weight;
  }
}