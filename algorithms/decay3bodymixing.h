#ifndef TOYGEN_DECAY3BODYMIXING_H
#define TOYGEN_DECAY3BODYMIXING_H

#include "event.h"
#include "algorithm.h"
#include "dalitzmixing.h"
#include "configureamplitude.h"
#include "dalitzamplitude.h"

class Decay3BodyMixing : public Algorithm
{
public:
  Decay3BodyMixing(std::string name, std::string cfgfile) :
    Algorithm( name )
  {
    DalitzModel::ConfigureAmplitude configure( cfgfile );
    configure( m_amp );
  } 
  ~Decay3BodyMixing() {}

  DalitzModel::DalitzMixing& amp() { return m_amp; }

  virtual void operator() (Event& ev);
private:
  DalitzModel::DalitzMixing m_amp;
};

#endif