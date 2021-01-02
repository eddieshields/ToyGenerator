#ifndef TOYGEN_PARTICLEPARAM_H
#define TOYGEN_PARTICLEPARAM_H

#include "event.h"
#include "particle.h"
#include "param.h"

class ParticleParam : public Param
{
public:
  ParticleParam() :
    Param(""),
    m_particle_index(-1)
  {}
  ParticleParam(std::string name) :
    Param(name),
    m_particle_index(-1)
  {}
  ParticleParam(std::string name, std::string param, int index = 0) :
    Param(name,param),
    m_particle_index( index )
  {}
  ~ParticleParam() {};

  virtual void operator()(Event& ev) { ev[m_name] = eval( ev.particle(m_particle_index)); }
protected:
  const int         m_particle_index;
  const double      eval(Particle& part);
};

#endif