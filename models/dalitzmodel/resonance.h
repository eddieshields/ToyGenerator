#ifndef TOYGEN_RESONANCE_H
#define TOYGEN_RESONANCE_H

// Package.
#include "coefficient.h"
#include "phasespace.h"
#include "parameter.h"
#include "angular.h"
#include "msgservice.h"

// SL.
#include <iostream>
#include <vector>
#include <complex>
#include <string>

namespace DalitzModel {

class Resonance
{
public:
  // Constructor/Destructor.
  Resonance(std::string name, const Coeff coeff, const int& resA, const int& resB,
            const Parameter& mass, const Parameter& width, const int l, const Parameter& r)
            : _name( name ), _coeff( coeff ), _resA( resA ), _resB ( resB ), _mass( mass ), _width( width ), _l( l ), _r( r ), next( nullptr )
            {};
  virtual ~Resonance() {};

  Resonance* next;

  // Name.
  std::string name() { return _name; }

  // Evaluate.
  std::complex< double > evaluate(const PhaseSpace& ps, const double& mSq12, const double& mSq13);
  std::complex< double > evaluate(const PhaseSpace& ps, const double& mSq12, const double& mSq13, const double& mSq23);

  // Propogator.
  virtual const std::complex< double > propagator(const PhaseSpace& ps, const double& mSqAB ) const = 0;

  // Normalize.
  void setNorm(const PhaseSpace& ps);
  // Getters.
  const Parameter mass()  const { return _mass;  }
  const Parameter m()     const { return _mass;  }
  const double mSq()      const { return _mSq;   }
  const Parameter width() const { return _width; }
  const int l()           const { return _l;     }
  const Parameter r()     const { return _r;     }

  const double M2AB(const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double M2AC(const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double M2BC(const double& mSq12, const double& mSq13, const double& mSq23) const;

  // Methods.
  double kallen(const double& x, const double& y, const double& z) const;
  double q(const PhaseSpace& ps, const double& mSqAB) const;
  double p(const PhaseSpace& ps, const double& mSqAB) const;
  double rho(const PhaseSpace& ps, const double& mSqAB) const;
  double zemach(const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const;
  double helicity(const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const;
  double blattWeisskopfPrime(const PhaseSpace& ps, const double& mSqAB) const;
  double blattWeisskopfPrimeP(const PhaseSpace& ps, const double& mSqAB) const;
  double blattWeisskopf(const PhaseSpace& ps, const double& mSqAB) const;
  double angular(const PhaseSpace& ps, const double& mSqAB, const double& mSqAC, const double& mSqBC) const;

  static void isHelicity() { _helicity = true; }
  static void isZemach()   { _helicity = false; }

  // Conjugate.
  virtual Resonance* cnj() const = 0;

  // Copy.
  virtual Resonance* copy() const = 0;

protected:
  std::string _name;
  std::complex< double > evaluateUnormalised(const PhaseSpace& ps, const double& mSq12, const double& mSq13);
  std::complex< double > evaluateUnormalised(const PhaseSpace& ps, const double& mSq12, const double& mSq13, const double& mSq23);
  // Particle indices.
  int _resA;
  int _resB;
  int _noRes = 6 - _resA - _resB;

  // Basic resonance parameters.
  double _norm = {1.};
  Coeff _coeff;
  const Parameter _mass;
  const double _mSq = (_mass * _mass);
  const Parameter _width;
  const int _l;
  const Parameter _r;
  static bool _helicity;

  // Conjugate.
  void makeCnj();
  bool _isCnj = {false};
};

}

#endif