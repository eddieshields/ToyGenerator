#ifndef TOYGEN_EVENTPARAM_H
#define TOYGEN_EVENTPARAM_H

#include "event.h"
#include "param.h"

class EventParam : public Param
{
public:
  /*
  enum EventType {
    W,
    PDF,
  };
  */
  EventParam() :
    Param()
  {}
  EventParam(std::string name, std::string param) :
    Param( name , param  , -1 )
  {}
  ~EventParam() {}

  virtual void operator()(Event& ev) { ev[m_name] = eval( ev ); }
private:
  const double eval(Event& ev);
};

#endif