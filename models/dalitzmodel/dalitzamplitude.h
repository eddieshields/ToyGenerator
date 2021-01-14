#ifndef TOYGEN_DALITZAMPLITUDE_H
#define TOYGEN_DALITZAMPLITUDE_H

#include "resonance.h"
#include "phasespace.h"
#include "descriptor.h"
#include "particlestore.h"
#include "msgservice.h"

#include <complex>
#include <vector>
#include <map>

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

  const std::complex<double> A1    (const double& mSq12, const double& mSq13) const ;
  const std::complex<double> A1    (const double& mSq12, const double& mSq13, const double& mSq23) const;
  const std::complex<double> A2    (const double& mSq12, const double& mSq13) const ;
  const std::complex<double> A2    (const double& mSq12, const double& mSq13, const double& mSq23) const;

  const double               A1Sq  (const double& mSq12, const double& mSq13) const;
  const double               A1Sq  (const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double               A2Sq  (const double& mSq12, const double& mSq13) const;
  const double               A2Sq  (const double& mSq12, const double& mSq13, const double& mSq23) const;

  void addDirResonance(Resonance* res);
  void addCnjResonance(Resonance* res);
  void printResonances();
  PhaseSpace& phasespace() { return _ps; }
private:
  PhaseSpace _ps;
  void addDirResonanceToList(Resonance* res);
  void addCnjResonanceToList(Resonance* res);
  std::vector<Resonance*> m_dirresonances;
  std::vector<Resonance*> m_cnjresonances;
  std::map<std::string,Parameter> m_parameters;

  Resonance* headDir = {nullptr};
  Resonance* tailDir = {nullptr};

  Resonance* headCnj = {nullptr};
  Resonance* tailCnj = {nullptr};
};

}

#endif