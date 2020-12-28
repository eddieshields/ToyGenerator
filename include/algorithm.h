#ifndef TOYGEN_ALGORITHM_H
#define TOYGEN_ALGORITHM_H

#include "event.h"

#include <string>

struct Algorithm
{
  Algorithm() : m_name("") {}
  Algorithm(std::string name) :
    m_name(name)
  {}
  virtual ~Algorithm() {};
  
  virtual void operator() (Event& ev) = 0;
  Algorithm* next = {nullptr};

  const std::string m_name;
  const std::string name() { return m_name; }
};

#endif
