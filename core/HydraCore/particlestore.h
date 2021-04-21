#ifndef TOYGEN_PARTICLESTORE_H
#define TOYGEN_PARTICLESTORE_H

#include "msgservice.h"
#include "types.h"

#include "TDatabasePDG.h"
#include "TParticlePDG.h"

#include <string>
#include <fstream>

struct ParticleStore {
private:
  TDatabasePDG m_pdg;
public:
  ParticleStore() :
    m_pdg()
  {}
  ~ParticleStore() {}

  TParticlePDG* operator()(std::string name) { checkExists( name ); return m_pdg.GetParticle(name.c_str()); }
  bool checkExists(std::string name)
  { 
    if ( m_pdg.GetParticle(name.c_str()) == nullptr ) {
      FATAL("Particle " << name << " is not recognised!");
      return false; 
    }
    return true;
  }
};

extern ParticleStore gParticleStore;

#endif