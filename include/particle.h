#ifndef TOYGEN_PARTICLE_H
#define TOYGEN_PARTICLE_H

#include "particlestore.h"

#include <string>

#include "TLorentzVector.h"


class Particle
{
public:
  Particle() {};
  virtual ~Particle() {};

  bool& isStable()           { return m_stable; }
  double& time()             { return m_ctau; }
  double& truetime()         { return m_ctau_true; }
  TLorentzVector& momentum() { return m_p; }
  int& charge()              { return m_q; }
  int& flavour()             { return m_flavour; }

  Particle operator+(Particle& part2);
  Particle operator+=(Particle& part2);
protected:
  std::string m_name;
  bool        m_stable;
  double      m_mass;
  double      m_ctau;
  double      m_ctau_true;
  int         m_q;
  int         m_flavour;

  TLorentzVector m_p;
  TLorentzVector m_true_p;
};

#endif