#ifndef TOYGEN_PYALGORITHM_H
#define TOYGEN_PYALGORITHM_H

#include "event.h"
#include "algorithm.h"

#include <functional>

class PyAlgorithm : public Algorithm
{
public:
  PyAlgorithm(std::string name,std::function<void(Event&)>& func) : 
    Algorithm(name),
    m_func( func )
  {
    Event ev;
    m_func(ev);
  }
  ~PyAlgorithm() {}

  virtual void operator()(Event& ev) { INFO("IN OPERATOR"); m_func(ev); } 

private:
  std::function<void(Event&)>& m_func;
};

#endif