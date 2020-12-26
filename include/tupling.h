#ifndef TOYGEN_TUPLING_H
#define TOYGEN_TUPLING_H

#include "event.h"
#include "algorithm.h"

class Tupling : public Algorithm
{
public:
  Tupling(std::string name) : Algorithm(name) {}
  ~Tupling() {}

  virtual void operator() (Event& ev);

};

#endif