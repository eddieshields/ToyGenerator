#ifndef TOYGEN_PARTICLE_H
#define TOYGEN_PARTICLE_H

#include "particlestore.h"
#include "fourvector.h"
#include "types.h"

#include <string>


class Particle
{
protected:
  FourVector  m_p;
  std::string m_name;
  real_t      m_mass;
  real_t      m_ctau;
  real_t      m_true_ctau;
  int         m_q;
  int         m_flavour;
  int         m_pid;
  bool        m_stable;
public:
  Particle() {};
  virtual ~Particle() {};

  inline bool&            isStable()     { return m_stable; }
  inline real_t&          time()         { return m_ctau; }
  inline real_t&          truetime()     { return m_true_ctau; }
  inline FourVector&      momentum()     { return m_p; }
  inline int&             charge()       { return m_q; }
  inline int&             flavour()      { return m_flavour; }
  inline int&             pid()          { return m_pid; }

  inline void SetMomentum(FourVector& p) { m_p = std::move(p); }

  Particle operator+ (Particle& part2);
  Particle operator+=(Particle& part2);
};

#endif