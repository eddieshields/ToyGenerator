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

  bool& isStable()           { return m_stable; }
  double& time()             { return m_ctau; }
  TLorentzVector& momentum() { return m_p; }
  int& charge()              { return m_q; }
  int& flavour()             { return m_flavour; }

  std::string m_name;

  bool m_stable;
  double m_mass;
  double m_ctau;
  int    m_q;
  int    m_flavour;

  TLorentzVector m_p;
  TLorentzVector m_true_p;
};

#endif