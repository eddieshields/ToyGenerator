#ifndef TOYGEN_PARTICLE_H
#define TOYGEN_PARTICLE_H

#include "particlestore.h"

// json.
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <string>

#include "TLorentzVector.h"

extern ParticleStore gParticleStore;

class Particle
{
public:
  Particle() :
    m_mass( 0. ),
    m_ctau( 0. )
  {}
  Particle(std::string name) :
    m_mass( gParticleStore(name,"mass") ),
    m_ctau( gParticleStore(name,"ctau") )
  {}
  ~Particle() {};

  bool isStable() { return m_stable; }
  TLorentzVector& momentum() { return m_p; }

  std::string m_name;

  const double m_mass;
  const double m_ctau;
  TLorentzVector m_p;
  TLorentzVector m_true_p;

  bool m_stable;
  unsigned int m_flavour;

};

#endif