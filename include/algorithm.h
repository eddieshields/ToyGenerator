#ifndef TOYGEN_ALGORITHM_H
#define TOYGEN_ALGORITHM_H

#include "event.h"

#include <string>

struct Algorithm
{
  Algorithm () = default;
  Algorithm(std::string name) { m_name = name; }
  virtual ~Algorithm() {};
  
  virtual void operator() (Event& ev) = 0;
  Algorithm* next = {nullptr};

  std::string m_name;
  std::string name() { return m_name; }
};

#endif
