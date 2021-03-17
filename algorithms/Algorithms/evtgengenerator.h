#ifndef TOYGEN_EVTGENGENERATOR_H
#define TOYGEN_EVTGENGENERATOR_H

#include "algorithm.h"
#include "event.h"
#include "descriptor.h"
#include "fourvector.h"

// EvtGen
#include "EvtGen/EvtGen.hh"
#include "EvtGenBase/EvtSimpleRandomEngine.hh"
#include "EvtGenBase/EvtVector4R.hh"
#include "EvtGenBase/EvtParticleFactory.hh"
#include "EvtGenBase/EvtPDL.hh"
#include "EvtGenBase/EvtParticle.hh"


class EvtGenGenerator : public Algorithm
{
public:
  EvtGenGenerator(std::string name, std::string decfile) :
    Algorithm( name ),
    m_eng( new EvtSimpleRandomEngine() ),
    m_radCorrEngine( 0 ),
    m_generator( decfile , "/afs/cern.ch/user/e/eshields/cernbox/ToyGenerator/EvtGen/share/evt.pdl" ,
                 m_eng, m_radCorrEngine, &m_extraModels)
  {
    configureDecFile( m_decfile );
  }
  ~EvtGenGenerator() {}

  void setDecFile(std::string decfile)
  {
    m_decfile = decfile;
    configureDecFile( m_decfile );
  }
  
  void configureDecFile(std::string decfile)
  {
    std::string mother = gDescriptor.getParticles()[0];
    EvtId id = EvtPDL::getId( mother );

    EvtVector4R p_init( EvtPDL::getMass( id ), 0.0, 0.0, 0.0 );
    EvtParticle* m_mother = EvtParticleFactory::particleFactory( id, p_init );
    m_mother->setDiagonalSpinDensity();
    return;
  }

  virtual void operator()(Event& ev)
  {
    m_generator.generateDecay( m_mother );
    for (int i = 1; i < 3; i++) {
      EvtVector4R p = m_mother->getDaug( i-1 )->getP4Lab();
      FourVector p4( p.get(0) , p.get(1) , p.get(2) , p.get(3) );
      ev.daughter(i).SetMomentum( p4 );
    }
    return;
  }

private:
  std::string              m_decfile;
  EvtGen                   m_generator;
  EvtRandomEngine*         m_eng;
  EvtAbsRadCorr*           m_radCorrEngine;
  std::list<EvtDecayBase*> m_extraModels;

  EvtParticle*             m_mother;
};


#endif