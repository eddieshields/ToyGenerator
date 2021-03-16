#ifndef TOYGEN_EVTGENAMPLITUDE_H
#define TOYGEN_EVTGENAMPLITUDE_H

#include "algorithm.h"
#include "event.h"

// EvtGen
#include "EvtGenModels/EvtPto3P.hh"

class EvtGenAmplitude : public Algorithm
{
public:
  EvtGenAmplitude(std::string name) :
    Algorithm( name )
  {}
  EvtGenAmplitude(std::string name, std::string decfile) :
    Algorithm( name ),
    m_decfile( decfile )
  {
    configureDecFile( m_decfile );
  }
  ~EvtGenAmplitude() {}

  void setDecFile(std::string decfile)
  {
    m_decfile = decfile;
    configureDecFile( m_decfile );
  }
  
  void configureDecFile(std::string decfile)
  {
    return;
  }

  virtual void operator()(Event& ev)
  {
    return;
  }

private:
  std::string m_decfile;
  EvtPto3P    m_decay;
};


#endif