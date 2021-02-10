#include "amplitude.h"

using namespace DalitzModel;

void Amplitude::setPhaseSpace(PhaseSpace& ps)
{
  m_ps = ps;
}

void Amplitude::addResonance(Resonance* reso)
{
  m_resonances.push_back( std::move( reso ) );

  // Make conjugate copy of the resonance.
  Resonance* resoCnj = m_resonances[m_resonances.size()-1]->cnj_copy();
  m_cnjresonances.push_back( std::move( resoCnj ) );
}

bool Amplitude::find(std::string res)
{
  for (auto r : m_resonances) {
    if ( r->name() == res) return true;
  }
  for (auto r : m_cnjresonances) {
    if ( r->name() == res) return true;
  }
  return false;
}

Resonance* Amplitude::get(std::string res)
{
  for (auto r : m_resonances) {
    if ( r->name() == res) return r;
  }
  for (auto r : m_cnjresonances) {
    if ( r->name() == res) return r;
  }
  WARNING("Resonance " << res << " not found!");
  return nullptr;
}

const complex_t Amplitude::Adir(const double& mSq12, const double& mSq13) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    A += m_resonances[i]->evaluate( m_ps , mSq12 , mSq13 );
  }
  return A;
}

const complex_t Amplitude::Adir(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    A += m_resonances[i]->evaluate( m_ps , mSq12 , mSq13 , mSq23 );
  }
  return A;
}

const complex_t Amplitude::Abar(const double& mSq12, const double& mSq13) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    A += m_cnjresonances[i]->evaluate( m_ps , mSq12 , mSq13 );
  }
  return A;
}

const complex_t Amplitude::Abar(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    A += m_cnjresonances[i]->evaluate( m_ps , mSq12 , mSq13 , mSq23 );
  }
  return A;
}

const double Amplitude::AdirSq(const double& mSq12, const double& mSq13) const
{
  return std::norm( Adir( mSq12, mSq13 ) );
}

const double Amplitude::AdirSq(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( Adir( mSq12, mSq13 , mSq23 ) );
}

const double Amplitude::AbarSq(const double& mSq12, const double& mSq13) const
{
  return std::norm( Abar( mSq12, mSq13 ) );
}

const double Amplitude::AbarSq(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( Abar( mSq12, mSq13, mSq23 ) );
}

const complex_t Amplitude::A1(const double& mSq12, const double& mSq13) const
{
  return ( Adir( mSq12 , mSq13 ) + Abar( mSq12 , mSq13 ) ) / 2.;
}

const complex_t Amplitude::A1(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return ( Adir( mSq12 , mSq13 , mSq23 ) + Abar( mSq12 , mSq13 , mSq23 ) ) / 2.;
}

const complex_t Amplitude::A2(const double& mSq12, const double& mSq13) const
{
  return ( Adir( mSq12 , mSq13 ) - Abar( mSq12 , mSq13 ) ) / 2.;
}


const complex_t Amplitude::A2(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return ( Adir( mSq12 , mSq13 , mSq23 ) - Abar( mSq12 , mSq13 , mSq23 ) ) / 2.;
}

const double Amplitude::A1Sq(const double& mSq12, const double& mSq13) const
{
  return std::norm( A1( mSq12 , mSq13 ) );
}

const double Amplitude::A1Sq(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( A1( mSq12 , mSq13 , mSq23 ) );
}

const double Amplitude::A2Sq(const double& mSq12, const double& mSq13) const
{
  return std::norm( A2( mSq12 , mSq13 ) );
}

const double Amplitude::A2Sq(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( A2( mSq12 , mSq13 , mSq23 ) );
}

// Individual resonances.
const complex_t Amplitude::Adir(std::string name, const double& mSq12, const double& mSq13) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    if ( m_resonances[i]->name() != name ) continue;
    A += m_resonances[i]->evaluate( m_ps , mSq12 , mSq13 );
  }
  return A;
}

const complex_t Amplitude::Adir(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    if ( m_resonances[i]->name() != name ) continue;
    A += m_resonances[i]->evaluate( m_ps , mSq12 , mSq13 , mSq23 );
  }
  return A;
}

const complex_t Amplitude::Abar(std::string name, const double& mSq12, const double& mSq13) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    if ( m_cnjresonances[i]->name() != name+"_cnj" ) continue;
    A += m_cnjresonances[i]->evaluate( m_ps , mSq12 , mSq13 );
  }
  return A;
}

const complex_t Amplitude::Abar(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  complex_t A(0.,0.);
  for (int i = 0; i < size(); i++) {
    if ( m_cnjresonances[i]->name() != name+"_cnj" ) continue;
    A += m_cnjresonances[i]->evaluate( m_ps , mSq12 , mSq13 , mSq23 );
  }
  return A;
}

const double Amplitude::AdirSq(std::string name, const double& mSq12, const double& mSq13) const
{
  return std::norm( Adir( name, mSq12, mSq13 ) );
}

const double Amplitude::AdirSq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( Adir( name, mSq12, mSq13 , mSq23 ) );
}

const double Amplitude::AbarSq(std::string name, const double& mSq12, const double& mSq13) const
{
  return std::norm( Abar( name, mSq12, mSq13 ) );
}

const double Amplitude::AbarSq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( Abar( name, mSq12, mSq13, mSq23 ) );
}

const complex_t Amplitude::A1(std::string name, const double& mSq12, const double& mSq13) const
{
  return ( Adir( name, mSq12 , mSq13 ) + Abar( name, mSq12 , mSq13 ) ) / 2.;
}

const complex_t Amplitude::A1(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return ( Adir( name, mSq12 , mSq13 , mSq23 ) + Abar( name, mSq12 , mSq13 , mSq23 ) ) / 2.;
}

const complex_t Amplitude::A2(std::string name, const double& mSq12, const double& mSq13) const
{
  return ( Adir( name, mSq12 , mSq13 ) - Abar( name, mSq12 , mSq13 ) ) / 2.;
}


const complex_t Amplitude::A2(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return ( Adir( name, mSq12 , mSq13 , mSq23 ) - Abar( name, mSq12 , mSq13 , mSq23 ) ) / 2.;
}

const double Amplitude::A1Sq(std::string name, const double& mSq12, const double& mSq13) const
{
  return std::norm( A1( name, mSq12 , mSq13 ) );
}

const double Amplitude::A1Sq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( A1( name, mSq12 , mSq13 , mSq23 ) );
}

const double Amplitude::A2Sq(std::string name, const double& mSq12, const double& mSq13) const
{
  return std::norm( A2( name, mSq12 , mSq13 ) );
}

const double Amplitude::A2Sq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( A2( name, mSq12 , mSq13 , mSq23 ) );
}