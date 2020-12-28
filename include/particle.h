#ifndef TOYGEN_PARTICLE_H
#define TOYGEN_PARTICLE_H

#include "particlestore.h"

// json.
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <string>

#include "TLorentzVector.h"


class Particle
{
public:
  Particle() {};
  ~Particle() {};

  bool& isStable()           { return m_stable; }
  double& time()             { return m_ctau; }
  TLorentzVector& momentum() { return m_p; }
  int& charge()              { return m_q; }
  int& flavour()             { return m_flavour; }

  Particle operator+(Particle& part2);
  Particle operator+=(Particle& part2);
private:
  std::string m_name;
  bool        m_stable;
  double      m_mass;
  double      m_ctau;
  int         m_q;
  int         m_flavour;

  TLorentzVector m_p;
  TLorentzVector m_true_p;
};

#endif