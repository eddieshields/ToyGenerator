#ifndef TOYGEN_EVENTPARAM_H
#define TOYGEN_EVENTPARAM_H

#include "event.h"
#include "param.h"
#include "types.h"

class EventParam : public Param
{
public:
  EventParam() :
    Param()
  {}
  EventParam(std::string name, std::string param) :
    Param( name , param  , -1 )
  {}
  ~EventParam() {}

  virtual void operator()(Event& ev) { ev[m_name] = eval( ev ); }
private:
  const real_t eval(Event& ev);
};

#endif