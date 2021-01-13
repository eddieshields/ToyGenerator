#ifndef TOYGEN_PARAM_H
#define TOYGEN_PARAM_H

#include "event.h"
#include "particle.h"
#include "msgservice.h"

class Param
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
    m_name(""),
    m_type(Param::Q)
  {}
  Param(std::string name) :
    m_name(name),
    m_type(Param::Q)
  {}
  Param(std::string name, std::string param, int index = 0) :
    m_name(name),
    m_type( getParamFromString(param) )
  {}
  ~Param() {};

  virtual void operator()(Event& ev) = 0; 
  //Param operator=(Param& param) { return *this; }
  Param* next;

  const std::string name() { return m_name; }
protected:
  const std::string m_name;

  const Param::Type m_type;

  const Param::Type getParamFromString(std::string param);
  const std::string getName(Param::Type param);
};

#endif