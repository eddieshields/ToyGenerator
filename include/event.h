#ifndef TOYGEN_EVENT_H
#define TOYGEN_EVENT_H

#include <vector>

#include "TLorentzVector.h"

class Event
{
friend class Generator;
public:
  Event() {};
  ~Event() {};

  double pdf;
  double efficiency;
  bool   accept;
private:
  std::vector<TLorentzVector*> m_p;
  std::vector<double>          m_v;
};

#endif