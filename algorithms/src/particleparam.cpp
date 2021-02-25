#include "particleparam.h"

const real_t ParticleParam::eval(Particle& part)
{
  
  switch (m_type)
  {
  case Param::Q:
    return part.charge();
  case Param::T:
    return part.time();
  case Param::M:
    return part.momentum().M();
  case Param::MSq:
    return part.momentum().M2();
  case Param::PX:
    return part.momentum().Px();
  case Param::PY:
    return part.momentum().Py();
  case Param::PZ:
    return part.momentum().Pz();
  case Param::PT:
    return part.momentum().Pt();
  case Param::P:
    return part.momentum().P();
  case Param::E:
    return part.momentum().E();
  default:
    FATAL(getName(m_type)+" does not exist.")
    return part.momentum().M();
  }
}