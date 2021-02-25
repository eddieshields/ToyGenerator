#ifndef TOYGEN_CUSTOMPARAM_H
#define TOYGEN_CUSTOMPARAM_H

#include "event.h"
#include "param.h"

#include <functional>

class CustomParam : public Param
{
public: 
  CustomParam() :
    Param("")
  {}
  CustomParam(std::string name) :
    Param(name)
  {}
  CustomParam(std::string name, std::function<const double(Event&)> func) :
    Param( name ),
    m_func( func )
  {}
  ~CustomParam() {};

  virtual void operator() (Event& ev) { ev[m_name] = m_func(ev); }

private:
  std::function<const double(Event&)> m_func;
};

#endif