#ifndef TOYGEN_GENERATOR_H
#define TOYGEN_GENERATOR_H

#include "event.h"
#include "algorithm.h"
#include "particle.h"
#include "particlestore.h"
#include "msgservice.h"
#include "random.h"

#include "TGenPhaseSpace.h"
#include "TLorentzVector.h"

#include <vector>
#include <random>
#include <sstream>

class Generator : public Algorithm
{
public:
  Generator(std::string name) : Algorithm(name), m_phsp() {}
  Generator(std::string name, std::string decay) : 
    Algorithm(name),
    m_phsp()
  {
    decodeDecayDescriptor(decay);
    TLorentzVector m_mother(0.,0.,0.,gParticleStore(m_particles[0],"mass"));
    for (int i = 1; i < m_particles.size(); i++) {
      addToDaughters(m_particles[i]);
    }
    m_phsp.SetDecay(m_mother,m_daughters.size(),m_daughters.data());
  }
  ~Generator() {}
  virtual void operator() (Event& ev);

  /*
  template <typename IN_TYPE, typename... IN_TYPES>
  void addToDaughters(IN_TYPE input, IN_TYPES... inputs) { m_daughters.push_back( input ); addToDaughters(inputs...); }
  template <typename IN_TYPE>
  void addToDaughters(IN_TYPE input) { m_daughters.push_back(input); }
  */
  void setDecay(std::string decay)
  {
    decodeDecayDescriptor(decay);
    TLorentzVector m_mother(0.,0.,0.,gParticleStore(m_particles[0],"mass"));
    for (int i = 1; i < m_particles.size(); i++) {
      addToDaughters(m_particles[i]);
    }
    m_phsp.SetDecay(m_mother,m_daughters.size(),m_daughters.data());
  }
  
private:
  TGenPhaseSpace            m_phsp;
  TLorentzVector            m_mother;
  std::vector<double>       m_daughters;
  std::vector<std::string>  m_particles;
  std::vector<int>          m_charges;
  std::vector<int>          m_flavours;
  bool                      m_chcnj;

  //template <typename... IN_TYPES>
  //void addToDaughters(std::string daughter, IN_TYPES... daughters) { m_daughters.push_back( gParticleStore(daughter,"mass") ); addToDaughters(daughters...); }
  void addToDaughters(std::string daughter) { m_daughters.push_back( gParticleStore(cleanParticle(daughter),"mass") ); }

  void        decodeDecayDescriptor(std::string decay);
  void        printDecayDescriptor();
  void        getMotherName      (std::string decay);
  void        getDaughtersNames  (std::string decay);
  const int   getParticleCharge  (std::string particle);
  const int   getParticleFlavour (std::string particle);
  const bool  getChargedConjugate(std::string decay);
  std::string cleanParticle(std::string particle);

  ParticleStore gParticleStore;
};

  /*
  template <typename... IN_TYPES>
  Generator(std::string name, const double mM, IN_TYPES... inputs) :
    Algorithm(name),
    m_phsp()
  {
    TLorentzVector m_mother(0.,0.,0.,mM);
    addToDaughters(inputs...);
    m_phsp.SetDecay(m_mother,m_daughters.size(),m_daughters.data());
  }
  template<typename... IN_TYPES>
  Generator(std::string name, std::string mother_name, IN_TYPES... daughter_names) :
    Algorithm(name),
    m_phsp()
  {
    TLorentzVector m_mother(0.,0.,0.,gParticleStore(mother_name,"mass"));
    addToDaughters(daughter_names...);
    m_phsp.SetDecay(m_mother,m_daughters.size(),m_daughters.data());
  }
  */

#endif