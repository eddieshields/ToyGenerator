#ifndef TOYGEN_DALITZAMPLITUDE_H
#define TOYGEN_DALITZAMPLITUDE_H

#include "resonance.h"
#include "phasespace.h"
#include "descriptor.h"
#include "particlestore.h"
#include "msgservice.h"

#include <complex>
#include <vector>

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

  void addResonance(Resonance* res);
  void printResonances();
  std::map<std::string,Parameter>& parameters() { return m_parameters; }
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