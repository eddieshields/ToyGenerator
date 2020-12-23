#ifndef TOYGEN_AMPLITUDE_H
#define TOYGEN_AMPLITUDE_H

#include "event.h"
#include "algorithm.h"

class Amplitude : public Algorithm
{
public:
  Amplitude(std::string name) : Algorithm(name) {};
  ~Amplitude() {};

  void operator() (Event& ev);
};

#endif