#ifndef TOYGEN_EVENT_H
#define TOYGEN_EVENT_H

#include "particle.h"

#include <vector>
#include <map>
#include <string>
/*
TODO:
  Have event include particle classes that can be dealt with seprately.
  This class should deal with the event as a while and have access to daughter particles.
*/
class Event
{
friend class Generator;
public:
  Event() {};
  ~Event() {};

  double pdf;
  double efficiency;
  bool   Accept;

  double    operator[](std::string name) { return m_v[name]; }
  Particle& operator()(std::string name) { return m_particles[name]; }
private:
  std::map<std::string,Particle> m_particles;
  std::map<std::string,double>   m_v;
};

#endif