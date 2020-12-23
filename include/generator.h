#ifndef TOYGEN_GENERATOR_H
#define TOYGEN_GENERATOR_H

#include "event.h"
#include "algorithm.h"

#include "TGenPhaseSpace.h"
#include "TLorentzVector.h"

class Generator : public Algorithm
{
public:
  Generator(std::string name, const double mM, const double m1, const double m2, const double m3) :
  Algorithm(name),
  m_phsp()
  {
    TLorentzVector mother(0.,0.,0.,mM);
    std::vector<double> daughters = {m1,m2,m3};
    m_phsp.SetDecay(mother,daughters.size(),daughters.data());
  }
  ~Generator() {}
  void operator() (Event& ev);

private:
  TGenPhaseSpace m_phsp;
};

#endif