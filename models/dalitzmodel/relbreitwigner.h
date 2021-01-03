#ifndef TOYGEN_RELBREITWIGNER_H
#define TOYGEN_RELBREITWIGNER_H

#include "resonance.h"

namespace DalitzModel {

class RelBreitWigner :public Resonance
{
public:
  // Constructor/Destructor.
  RelBreitWigner(std::string name, const Coeff& coeff, const int& resA, const int& resB,
                 const Parameter& mass, const Parameter& width, const int l, const Parameter& r)
                 : Resonance(name, coeff, resA, resB, mass, width, l, r)
                 {}
  ~RelBreitWigner() {};

  const std::complex< double > propagator(const PhaseSpace& ps, const double& mSqAB ) const;
  const double runningWidth(const PhaseSpace& ps, const double& mSqAB) const;

  RelBreitWigner* cnj() const;

  RelBreitWigner* copy() const;
};

}

#endif