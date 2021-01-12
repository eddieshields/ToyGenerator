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

  void setX(double x) { m_amp.setX( x ); }
  void setY(double y) { m_amp.setY( y ); }
  void setP(double p) { m_amp.setP( p ); }
  void setQ(double q) { m_amp.setQ( q ); }

  virtual void operator() (Event& ev);
private:
  DalitzModel::DalitzMixing m_amp;
};

#endif