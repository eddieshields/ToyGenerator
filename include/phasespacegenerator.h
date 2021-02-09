#ifndef TOYGEN_PHASESPACEGENERATOR_H
#define TOYGEN_PHASESPACEGENERATOR_H

#include "fourvector.h"
#include "random.h"

#include <cmath>
#include <vector>

#ifdef VECTORIZARION
    using real_t = float;
#else
    using real_t = double;
#endif

/** \class Generator
 * 
 * Class to generate PhaseSpace events based. Based on the ROOT implentation,
 * https://root.cern.ch/doc/master/classTGenPhaseSpace.html.
 * Try to speed it up by making it thread safe and vectorize.
 */
class PhaseSpaceGenerator
{
private:
  int    _nP;
  real_t _TeCmTm;
  real_t _Mass[18];
  real_t _WtMax;
  real_t _Beta[3];

  real_t PDK(real_t a, real_t b, real_t c);
public:
  PhaseSpaceGenerator() = default;
  virtual ~PhaseSpaceGenerator() {}

  real_t Generate(FourVector* _vecs);
  bool SetDecay(FourVector& P, int nP, real_t* mass);
};

#endif