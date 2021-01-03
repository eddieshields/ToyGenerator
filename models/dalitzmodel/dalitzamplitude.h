#ifndef TOYGEN_DALITZAMPLITUDE_H
#define TOYGEN_DALITZAMPLITUDE_H

#include "resonance.h"
#include "phasespace.h"
#include "descriptor.h"
#include "particlestore.h"
#include "msgservice.h"

#include <complex>
#include <vector>

#include <omp.h>

namespace DalitzModel {

class DalitzAmplitude
{
public:
  DalitzAmplitude() :
    _ps( gDescriptor.getParticleMass(0) , gDescriptor.getParticleMass(1) , gDescriptor.getParticleMass(2) , gDescriptor.getParticleMass(3) )
  {}
  ~DalitzAmplitude() {}

  const std::complex<double> Adir  (const double& mSq12, const double& mSq13) const ;
  const std::complex<double> Adir  (const double& mSq12, const double& mSq13, const double& mSq23) const;
  const std::complex<double> Abar  (const double& mSq12, const double& mSq13) const ;
  const std::complex<double> Abar  (const double& mSq12, const double& mSq13, const double& mSq23) const;

  const double               AdirSq(const double& mSq12, const double& mSq13) const;
  const double               AdirSq(const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double               AbarSq(const double& mSq12, const double& mSq13) const;
  const double               AbarSq(const double& mSq12, const double& mSq13, const double& mSq23) const;

  void test() { for (int i = 0; i < m_resonances.size(); i++) { double a =std::norm(  m_resonances[i]->evaluate(_ps,1.1,1.1) ); INFO("TEST = "+std::to_string(a)); } }

  void addResonance(Resonance* res);
  void printResonances();
  PhaseSpace& phasespace() { return _ps; }
  std::map<std::string,Parameter>& parameters() { return m_parameters; }
  std::vector<Resonance*>& resonances() { return m_resonances; }
private:
  PhaseSpace _ps;
  void addResonanceToList(Resonance* res);
  std::vector<Resonance*> m_resonances;
  std::map<std::string,Parameter> m_parameters;

  Resonance* head = {nullptr};
  Resonance* tail = {nullptr};
};

}

#endif