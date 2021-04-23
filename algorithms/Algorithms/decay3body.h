#ifndef TOYGEN_D02KSKK_H
#define TOYGEN_D02KSKK_H

#include "event.h"
#include "algorithm.h"
#include "configureamplitude.h"
#include "amplitude.h"
#include "msgservice.h"

class Decay3Body : public Algorithm
{
public:
  Decay3Body(std::string name, std::string cfgfile) :
    Algorithm(name)
  {
    DalitzModel::ConfigureAmplitude configure( cfgfile );
    m_amp = configure();
  }
  ~Decay3Body() {}

  void operator() (Event& ev) override final;

  DalitzModel::Amplitude amp() { return m_amp; }
private:
  DalitzModel::Amplitude m_amp;
};

#endif