#ifndef TOYGEN_D02KSKK_H
#define TOYGEN_D02KSKK_H

#include "event.h"
#include "algorithm.h"
#include "configureamplitude.h"
#include "dalitzamplitude.h"
#include "msgservice.h"

class Decay3Body : public Algorithm
{
public:
  Decay3Body(std::string name, std::string cfgfile) :
    Algorithm(name)
  {
    DalitzModel::ConfigureAmplitude configure( cfgfile );
    configure( m_amp );
  }
  ~Decay3Body() {}

  virtual void operator() (Event& ev);

private:
  DalitzModel::DalitzAmplitude m_amp;
};

#endif