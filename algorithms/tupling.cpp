#include "tupling.h"

void Tupling::operator()(Event& ev)
{
  if ( !ev.Accept ) return;
  //ev.updateMasses();

  
  for (auto& v : m_variables) {
    ev[getName(v)] = getVariable(v,ev);
  }
  
  /*
  for (int i = 0; i < ev.m_particles.size(); i++) {
    ev.m_v[std::to_string(i)+"_PX"] = ev.m_particles[i].momentum().Px();
    ev.m_v[std::to_string(i)+"_PY"] = ev.m_particles[i].momentum().Py();
    ev.m_v[std::to_string(i)+"_PZ"] = ev.m_particles[i].momentum().Pz();
    ev.m_v[std::to_string(i)+"_E"] = ev.m_particles[i].momentum().E();
    ev.m_v[std::to_string(i)+"_PT"] = ev.m_particles[i].momentum().Pt();
    ev.m_v[std::to_string(i)+"_P"] = ev.m_particles[i].momentum().P();
  }
  */

  return;
}

const double Tupling::getVariable(Tupling::ParamType& _type, Event& ev)
{
  switch (_type)
  {
  case Tupling::Weight:
    return ev.weight;
  case Tupling::Pdf:
    return ev.pdf;
  case Tupling::T:
    return ev.mother().time();
  case Tupling::Q:
    return ev.daughter(1).charge();
  default:
    break;
  }
}

const std::string Tupling::getName(Tupling::ParamType& _type)
{
  switch (_type)
  {
  case Tupling::Weight:
    return "weight";
  case Tupling::Pdf:
    return "pdf";
  case Tupling::T:
    return "t";
  case Tupling::Q:
    return "K_q";
  default:
    break;
  }
}

const Tupling::ParamType Tupling::getParamFromString(std::string name)
{
  if ( name == "weight" ) {
    return Tupling::Weight;
  } else if ( name == "pdf" ) {
    return Tupling::Pdf;
  } else if ( name == "t" ) {
    return Tupling::T;
  } else if ( name == "K_q" ) {
    return Tupling::Q;
  } else {
    WARNING("Unknown parameter type "+name);
    return Tupling::Weight;
  }
}