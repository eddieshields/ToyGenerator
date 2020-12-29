#ifndef TOYGEN_PYALGORITHM_H
#define TOYGEN_PYALGORITHM_H

#include "event.h"
#include "algorithm.h"
#include "pywrapper.h"

class PyAlgorithm : public Algorithm
{
public:
  PyAlgorithm(std::string name, PyObject* p) :
    Algorithm(name),
    pObj( p )
  {}
  ~PyAlgorithm() {}

  virtual void operator() (Event& ev)
  {
    pObj(&ev);
  }

private:
  PyWrapper pObj;
};

#endif