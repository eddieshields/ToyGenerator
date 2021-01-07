#include "pyalgorithm.h"

void PyAlgorithm::operator()(Event& ev)
{
  m_func(ev);
}