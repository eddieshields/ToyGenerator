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

  double pdf = {1};
  double efficiency = {1};
  bool   Accept = {false};

  double&    operator[](std::string name) { return m_v[name]; }
  Particle& operator()(int index ) { return m_particles[index]; }

  std::vector<Particle> m_particles;
  //std::map<std::string,Particle> m_particles;
  std::map<std::string,double>   m_v;

  void updateMasses()
  {  
    TLorentzVector m12 = m_particles[0].momentum() + m_particles[1].momentum();
    TLorentzVector m13 = m_particles[0].momentum() + m_particles[2].momentum();
    TLorentzVector m23 = m_particles[1].momentum() + m_particles[2].momentum();
  
    m_v["mSq12"] = m12.M2();
    m_v["mSq13"] = m13.M2();
    m_v["mSq23"] = m23.M2();
  }
};

#endif