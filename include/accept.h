#ifndef TOYGEN_ACCEPT_H
#define TOYGEN_ACCEPT_H

#include "event.h"
#include "algorithm.h"

class Accept : public Algorithm
{
public:
  Accept(std::string name) : Algorithm(name) {}
  ~Accept() {}

  virtual void operator() (Event& ev);
};

#endif