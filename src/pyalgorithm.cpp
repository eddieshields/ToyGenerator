#include "pyalgorithm.h"
#include <Python/Python.h>
void PyAlgorithm::operator()(Event& ev)
{
  m_func(ev);
}