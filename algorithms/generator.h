#ifndef TOYGEN_GENERATOR_H
#define TOYGEN_GENERATOR_H

#include "event.h"
#include "algorithm.h"
#include "particle.h"
#include "particlestore.h"
#include "msgservice.h"
#include "random.h"
#include "descriptor.h"

#include "TGenPhaseSpace.h"
#include "TLorentzVector.h"
#include "TRandom.h"

#include <vector>
#include <random>
#include <sstream>

class Generator : public Algorithm
{
public:
  Generator(std::string name) : Algorithm(name), m_phsp() 
  {
    getDecay();
    TLorentzVector m_mother(0.,0.,0.,gParticleStore(m_particles[0],"mass"));
    for (int i = 1; i < m_particles.size(); i++) {
      addToDaughters(m_particles[i]);
    }
    m_phsp.SetDecay(m_mother,m_daughters.size(),m_daughters.data());
  }
  ~Generator() {}
  virtual void operator() (Event& ev);
  
private:
  TGenPhaseSpace            m_phsp;
  TLorentzVector            m_mother;
  std::vector<double>       m_daughters;
  std::vector<std::string>  m_particles;
  std::vector<int>          m_charges;
  std::vector<int>          m_flavours;
  bool                      m_chcnj;

  void addToDaughters(std::string daughter) { m_daughters.push_back( gParticleStore(daughter,"mass") ); }

  void getDecay()
  {
    m_particles = gDescriptor.getParticles();
    m_charges = gDescriptor.getCharges();
    m_flavours = gDescriptor.getFlavours();
    m_chcnj = gDescriptor.getChargeConjugate();
  }
  
};

#endif