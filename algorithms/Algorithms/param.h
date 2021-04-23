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
    PID,
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
  static const Param::Type getParamFromString(std::string param);
  static const std::string getName(Param::Type param);

  Param() :
    Algorithm(""),
    m_type(Param::Q)
  {}
  Param(std::string name) :
    Algorithm(name),
    m_type(Param::Q)
  {}
  Param(std::string name, std::string param, int index = 0) :
    Algorithm(name),
    m_type( getParamFromString(param) )
  {}
  ~Param() {};

  void operator()(Event& ev) = 0; 
  //Param operator=(Param& param) { return *this; }
  Param* next;
protected:
  const Param::Type m_type;

};

#endif