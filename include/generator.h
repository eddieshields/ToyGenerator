#ifndef TOYGEN_GENERATOR_H
#define TOYGEN_GENERATOR_H

#include "event.h"
#include "algorithm.h"
#include "particlestore.h"

#include "TGenPhaseSpace.h"
#include "TLorentzVector.h"

#include <vector>

extern ParticleStore gParticleStore;

class Generator : public Algorithm
{
public:
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
  Generator(std::string name, const double mM, const double m1, const double m2, const double m3) :
    Algorithm(name),
    m_phsp()
  {
    TLorentzVector m_mother(0.,0.,0.,mM);
    std::vector<double> m_daughters = {m1,m2,m3};
    m_phsp.SetDecay(m_mother,m_daughters.size(),m_daughters.data());
  }
  ~Generator() {}
  void operator() (Event& ev);

  template <typename IN_TYPE, typename... IN_TYPES>
  void addToDaughters(IN_TYPE input, IN_TYPES... inputs) { m_daughters.push_back( input ); addToDaughters(inputs...); }
  template <typename IN_TYPE>
  void addToDaughters(IN_TYPE input) { m_daughters.push_back(input); }
  template <typename... IN_TYPES>
  void addToDaughter(std::string daughter, IN_TYPES... daughters) { m_daughters.push_back( gParticleStore(daughter,"mass") ); addToDaughters(daughters...); }
  void addToDaughter(std::string daughter) { m_daughters.push_back( gParticleStore(daughter,"mass") ); }

private:
  TGenPhaseSpace      m_phsp;
  TLorentzVector      m_mother;
  std::vector<double> m_daughters;
};

#endif