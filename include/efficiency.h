#ifndef TOYGEN_EFFICIENCY_H
#define TOYGEN_EFFICIENCY_H

#include "event.h"
#include "algorithm.h"

class Efficiency : public Algorithm
{
public:
  Efficiency(std::string name) : Algorithm(name) {};
  ~Efficiency() {};

  void operator() (Event& ev);
};

#endif