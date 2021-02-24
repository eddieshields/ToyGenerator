#include "parameter.h"

using namespace DalitzModel;

std::vector<Parameter*> Parameter::m_parameters = std::vector<Parameter*>();

Uncertainty Parameter::ParameterUncertaintyType::Type = Uncertainty::Fixed;

bool Parameter::m_random = false;

void Parameter::SetRandom(bool flag)
{
  m_random = flag;
  for (auto p : Parameter::m_parameters) {
    if ( Parameter::m_random ) p->m_state = p->m_value + p->m_error;
    else p->m_state = p->m_value;
  }
}
