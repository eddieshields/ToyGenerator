#ifndef TOYGEN_PARTICLEPARAM_H
#define TOYGEN_PARTICLEPARAM_H

#include "event.h"
#include "particle.h"
#include "param.h"
#include "types.h"

template<Param::Type P>
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

  inline void operator()(Event& ev) override { ev[m_name] = m_evaluation( ev.particle(m_particle_index)); }
protected:
  const int                        m_particle_index;
  inline real_t m_evaluation(Particle& particle) const { return 0; }  
};

template<> inline real_t ParticleParam<Param::PID>::m_evaluation(Particle& particle) const
{
  return particle.pid();
}

template<> inline real_t ParticleParam<Param::Q>::m_evaluation(Particle& particle) const
{
  return particle.charge();
}

template<> inline real_t ParticleParam<Param::T>::m_evaluation(Particle& particle) const
{
  return particle.time();
}

template<> inline real_t ParticleParam<Param::M>::m_evaluation(Particle& particle) const
{
  return particle.momentum().M();
}

template<> inline real_t ParticleParam<Param::MSq>::m_evaluation(Particle& particle) const
{
  return particle.momentum().M2();
}

template<> inline real_t ParticleParam<Param::PX>::m_evaluation(Particle& particle) const
{
  return particle.momentum().Px();
}

template<> inline real_t ParticleParam<Param::PY>::m_evaluation(Particle& particle) const
{
  return particle.momentum().Py();
}

template<> inline real_t ParticleParam<Param::PZ>::m_evaluation(Particle& particle) const
{
  return particle.momentum().Pz();
}

template<> inline real_t ParticleParam<Param::PT>::m_evaluation(Particle& particle) const
{
  return particle.momentum().Pt();
}

template<> inline real_t ParticleParam<Param::P>::m_evaluation(Particle& particle) const
{
  return particle.momentum().P();
}

template<> inline real_t ParticleParam<Param::E>::m_evaluation(Particle& particle) const
{
  return particle.momentum().E();
}

#endif