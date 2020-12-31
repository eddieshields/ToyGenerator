#ifndef TOYGEN_PARAM_H
#define TOYGEN_PARAM_H

#include "event.h"
#include "algorithm.h"
#include "particle.h"
#include "msgservice.h"

class Param : public Algorithm
{
public:
  enum Type {
    W,
    PDF,
    Q,
    T,     //Time.
    M,     //Mass.
    MSq,   //Mass squared.
    PX,    //Px.
    PY,    //Py.
    PZ,    //Pz.
    PT,    //Pt.
    P,     //Momentum.
    E      //Energy.
  };
  Param() :
    Algorithm(""),
    m_type(Param::Q),
    m_particle_index(-1)
  {}
  Param(std::string name) :
    Algorithm(name),
    m_type(Param::Q),
    m_particle_index(-1)
  {}
  Param(std::string name, std::string param, int index = 0) :
    Algorithm(name),
    m_type( getParamFromString(param) ),
    m_particle_index( index )
  {}
  ~Param() {};

  virtual void operator()(Event& ev) { ev[m_name] = eval( ev.particle(m_particle_index)); }
  Param operator=(Param& param) { return *this; }
  Param* next;
protected:
  const Param::Type m_type;
  const int         m_particle_index;

  const double      eval(Particle& part);
  const Param::Type getParamFromString(std::string param);
  const std::string getName(Param::Type param);
};

#endif