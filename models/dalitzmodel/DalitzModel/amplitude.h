#ifndef DALITZMODEL_AMPLITUDE_H
#define DALITZMODEL_AMPLITUDE_H

// STL.
#include <iostream>
#include <vector>
#include <memory>

// DalitzModel.
#include "resonance.h"
#include "phasespace.h"
#include "msgservice.h"

namespace DalitzModel {

using complex_t = std::complex<double>;

class Amplitude
{
private:
  std::vector<Resonance*> m_resonances;
  std::vector<Resonance*> m_cnjresonances;

  // Linked list of resonances.
  Resonance* headDir = {nullptr};
  Resonance* tailDir = {nullptr};
  Resonance* headCnj = {nullptr};
  Resonance* tailCnj = {nullptr};
  void addDirResonanceToList(Resonance* res);
  void addCnjResonanceToList(Resonance* res);

  PhaseSpace m_ps;
public:
  Amplitude() = default;
  Amplitude(PhaseSpace& ps) :
    m_ps( ps )
  {}
  virtual ~Amplitude() {}

  void setPhaseSpace(PhaseSpace& ps);
  void addResonance(Resonance* reso);

  const int size() const { return m_resonances.size(); }
  const int cnj_size() const { return m_cnjresonances.size(); }
  PhaseSpace& phasespace() { return m_ps; }
  PhaseSpace& ps()         { return m_ps; }

  bool       find(std::string res);
  Resonance* get (std::string res);

  // Operators.
  friend std::ostream& operator<<(std::ostream& os, const Amplitude& amp)
  {
    std::string out = "Resonances = \n";
    os << out;
    Resonance* res = nullptr;
    res = amp.headDir;
    while ( res != nullptr ) {
      os << *res << "\n";
      res = res->next;
    }
    return os;
  }

  const complex_t Adir  (const double& mSq12, const double& mSq13) const ;
  const complex_t Adir  (const double& mSq12, const double& mSq13, const double& mSq23) const;
  const complex_t Abar  (const double& mSq12, const double& mSq13) const ;
  const complex_t Abar  (const double& mSq12, const double& mSq13, const double& mSq23) const;

  const double    AdirSq(const double& mSq12, const double& mSq13) const;
  const double    AdirSq(const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double    AbarSq(const double& mSq12, const double& mSq13) const;
  const double    AbarSq(const double& mSq12, const double& mSq13, const double& mSq23) const;

  const complex_t A1    (const double& mSq12, const double& mSq13) const ;
  const complex_t A1    (const double& mSq12, const double& mSq13, const double& mSq23) const;
  const complex_t A2    (const double& mSq12, const double& mSq13) const ;
  const complex_t A2    (const double& mSq12, const double& mSq13, const double& mSq23) const;

  const double    A1Sq  (const double& mSq12, const double& mSq13) const;
  const double    A1Sq  (const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double    A2Sq  (const double& mSq12, const double& mSq13) const;
  const double    A2Sq  (const double& mSq12, const double& mSq13, const double& mSq23) const;

  // Individual resonances.
  const complex_t Adir  (std::string name, const double& mSq12, const double& mSq13) const ;
  const complex_t Adir  (std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;
  const complex_t Abar  (std::string name, const double& mSq12, const double& mSq13) const ;
  const complex_t Abar  (std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;

  const double    AdirSq(std::string name, const double& mSq12, const double& mSq13) const;
  const double    AdirSq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double    AbarSq(std::string name, const double& mSq12, const double& mSq13) const;
  const double    AbarSq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;

  const complex_t A1    (std::string name, const double& mSq12, const double& mSq13) const ;
  const complex_t A1    (std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;
  const complex_t A2    (std::string name, const double& mSq12, const double& mSq13) const ;
  const complex_t A2    (std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;

  const double    A1Sq  (std::string name, const double& mSq12, const double& mSq13) const;
  const double    A1Sq  (std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;
  const double    A2Sq  (std::string name, const double& mSq12, const double& mSq13) const;
  const double    A2Sq  (std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const;
};

} // namespace DalitzModel

#endif