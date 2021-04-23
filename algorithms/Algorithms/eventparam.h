#ifndef TOYGEN_EVENTPARAM_H
#define TOYGEN_EVENTPARAM_H

#include "event.h"
#include "param.h"
#include "types.h"

template<Param::Type P>
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

  inline void operator()(Event& ev) override { ev[m_name] = m_evaluation( ev ); }
private:
  inline real_t m_evaluation(Event& ev) const { return 0; } 
};

template<> inline real_t EventParam<Param::W>::m_evaluation(Event& ev) const
{
  return ev.weight;
}

template<> inline real_t EventParam<Param::PDF>::m_evaluation(Event& ev) const
{
  return ev.pdf;
}

#endif