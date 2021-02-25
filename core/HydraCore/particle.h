#ifndef TOYGEN_PARTICLE_H
#define TOYGEN_PARTICLE_H

#include "particlestore.h"
#include "fourvector.h"
#include "types.h"

#include <string>


class Particle
{
public:
  Particle() {};
  virtual ~Particle() {};

  bool&            isStable()     { return m_stable; }
  real_t&          time()         { return m_ctau; }
  real_t&          truetime()     { return m_true_ctau; }
  FourVector&      momentum()     { return m_p; }
  int&             charge()       { return m_q; }
  int&             flavour()      { return m_flavour; }

  void SetMomentum(FourVector& p) { m_p = std::move(p); }

  Particle operator+ (Particle& part2);
  Particle operator+=(Particle& part2);
protected:
  std::string m_name;
  bool        m_stable;
  real_t      m_mass;
  real_t      m_ctau;
  real_t      m_true_ctau;
  int         m_q;
  int         m_flavour;

  FourVector  m_p;
};

#endif