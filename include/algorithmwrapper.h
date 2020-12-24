#ifndef TOYGEN_ALGORITHMWRAPPER_H
#define TOYGEN_ALGORITHMWRAPPER_H

#include "algorithm.h"

template<typename T>
class AlgorithmWrapper : public Algorithm
{
public:
  AlgorithmWrapper(std::string name, T func) :
    Algorithm(name),
    m_func( func )
  {}
  ~AlgorithmWrapper() {}

  void operator()(Event& ev) { m_func(ev); }
private:
  T m_func;
}

#endif