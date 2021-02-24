#ifndef DALITZMODEL_FLATTE_H
#define DALITZMODEL_FLATTE_H

// DalitzModel.
#include "resonance.h"
#include "msgservice.h"

namespace DalitzModel {
  namespace LineShape {

using complex_t = std::complex<double>;

class Flatte : public Resonance
{
// Define different types of parameterisations that could be used.
enum Parameterisation {
  None,
  BaBar2005,
  BaBar2008,
  BaBar2010,
};
private:
  Parameter m_gamma1;
  Parameter m_gamma2;
  Parameter m_m02a;
  Parameter m_m02b;

  double m_gamma1Sq;
  double m_gamma2Sq;
  double m_m02aSq;
  double m_m02bSq;

  static Parameterisation m_parameterisation; 
public:
  Flatte() = default;
  Flatte(std::string& name, const Coefficient& coeff,
            const int& resoA, const int& resoB,
            const Parameter& mass, const Parameter& width,
            const int& l, const Parameter& r,
            const Parameter& gamma1, const Parameter& gamma2,
            const Parameter& m02a, const Parameter& m02b) :
    Resonance( name , coeff , resoA , resoB , mass , width , l , r ),
    m_gamma1( gamma1 ),
    m_gamma2( gamma2 ),
    m_m02a( m02a ),
    m_m02b( m02b )
  {
    m_gamma1Sq = m_gamma1 * m_gamma1;
    m_gamma2Sq = m_gamma2 * m_gamma2;
    m_m02aSq = m_m02a * m_m02a;
    m_m02bSq = m_m02b * m_m02b;
  }
  Flatte(std::string& name, const double& coeff1, const double& coeff2,
            const int& resoA, const int& resoB,
            const double& mass, const double& width,
            const int& l, const double& r,
            const double& gamma1, const double& gamma2,
            const double& m02a, const double& m02b) :
    Resonance( name , coeff1 , coeff2 , resoA , resoB , mass , width , l , r ),
    m_gamma1( gamma1 ),
    m_gamma2( gamma2 ),
    m_m02a( m02a ),
    m_m02b( m02b )
  {
    m_gamma1Sq = m_gamma1 * m_gamma1;
    m_gamma2Sq = m_gamma2 * m_gamma2;
    m_m02aSq = m_m02a * m_m02a;
    m_m02bSq = m_m02b * m_m02b;
  }
  Flatte(const Flatte& other) :
    Resonance( other ),
    m_gamma1( other.m_gamma1 ),
    m_gamma2( other.m_gamma2 ),
    m_m02a( other.m_m02a ),
    m_m02b( other.m_m02b )
  {}
  virtual ~Flatte() {}

  virtual const complex_t propagator(const PhaseSpace& ps, const double& mSqAB) const;

  const complex_t babar2005_propagator(const PhaseSpace& ps, const double& mSqAB) const;
  const complex_t babar2008_propagator(const PhaseSpace& ps, const double& mSqAB) const;
  const complex_t babar2010_propagator(const PhaseSpace& ps, const double& mSqAB) const;

  Flatte* copy() const;

  Parameter gamma1() const { return m_gamma1; }
  Parameter gamma2() const { return m_gamma2; }
  Parameter m02a()   const { return m_m02a; }
  Parameter m02b()   const { return m_m02b; }

  double gamma1Sq()  const { return m_gamma1Sq; }
  double gamma2Sq()  const { return m_gamma2Sq; }
  double m02aSq()    const { return m_m02aSq; }
  double m02bSq()    const { return m_m02bSq; }

  static void SetParameterisation(std::string parameterisation);
};

  } // namespace LineShape
} // namespace DalitzModel

#endif