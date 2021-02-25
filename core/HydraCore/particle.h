#ifndef TOYGEN_PARTICLE_H
#define TOYGEN_PARTICLE_H

#include "particlestore.h"
#include "fourvector.h"

#include <string>

#include "TLorentzVector.h"


class Particle
{
public:
  Particle() {};
  virtual ~Particle() {};

  bool&            isStable()     { return m_stable; }
  double&          time()         { return m_ctau; }
  double&          truetime()     { return m_true_ctau; }
  TLorentzVector&  momentum()     { return m_p; }
  FourVector&      new_momentum() { return m_n_p; }
  int&             charge()       { return m_q; }
  int&             flavour()      { return m_flavour; }

  void SetMomentum(FourVector p) { m_n_p = std::move(p); }

  Particle operator+ (Particle& part2);
  Particle operator+=(Particle& part2);
protected:
  std::string m_name;
  bool        m_stable;
  double      m_mass;
  double      m_ctau;
  double      m_true_ctau;
  int         m_q;
  int         m_flavour;

  FourVector     m_n_p;
  TLorentzVector m_p;
  TLorentzVector m_true_p;
};

#endif