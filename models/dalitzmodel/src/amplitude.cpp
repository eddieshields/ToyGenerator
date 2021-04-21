#include "amplitude.h"

using namespace DalitzModel;

void Amplitude::setPhaseSpace(PhaseSpace& ps)
{
  m_ps = ps;
}

void Amplitude::addResonance(Resonance* reso)
{
  m_resonances.push_back( std::move( reso ) );
  addDirResonanceToList( m_resonances[m_resonances.size()-1] );
  // Make conjugate copy of the resonance.
  Resonance* resoCnj = m_resonances[m_resonances.size()-1]->cnj_copy();
  m_cnjresonances.push_back( std::move( resoCnj ) );
  addCnjResonanceToList( m_cnjresonances[m_cnjresonances.size()-1] );
}

void Amplitude::addDirResonanceToList(Resonance* res)
{
  Resonance* tmp = nullptr;
  tmp = res;
  tmp->next=nullptr;
  if ( headDir == nullptr ) {
    headDir = tmp;
    tailDir = tmp;
    tmp=nullptr;
  } else {
    tailDir->next=tmp;
    tailDir=tmp;
  }
  return;
}

void Amplitude::addCnjResonanceToList(Resonance* res)
{
  Resonance* tmp = nullptr;
  tmp = res;
  tmp->next=nullptr;
  if ( headCnj == nullptr ) {
    headCnj=tmp;
    tailCnj=tmp;
    tmp=nullptr;
  } else {
    tailCnj->next=tmp;
    tailCnj=tmp;
  }
  return;
}

bool Amplitude::find(std::string res) const
{
  for (auto r : m_resonances) {
    if ( r->name() == res) return true;
  }
  for (auto r : m_cnjresonances) {
    if ( r->name() == res) return true;
  }
  return false;
}

Resonance* Amplitude::get(std::string res) const
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

const real_t Amplitude::getMax() const
{
  int nsteps = 1000;
  real_t mSq12Step = ( m_ps.mSq12max() - m_ps.mSq12min() ) / nsteps;
  real_t mSq13Step = ( m_ps.mSq13max() - m_ps.mSq13min() ) / nsteps;
  real_t maxPdf = 0;
  for (real_t mSq12 = m_ps.mSq12min(); mSq12 < m_ps.mSq12max(); mSq12 += mSq12Step) {
    for (real_t mSq13 = m_ps.mSq13min(); mSq13 < m_ps.mSq13max(); mSq13 += mSq13Step) {
      real_t a = AdirSq( mSq12 , mSq13 );
      if ( a > maxPdf ) maxPdf = a;
    }
  }
  return maxPdf;
}

const complex_t Amplitude::Adir(const real_t& mSq12, const real_t& mSq13) const
{
  complex_t A(0.,0.);
  for (const auto& res : m_resonances) {
    A += res->evaluate( m_ps , mSq12 , mSq13 );
  }
  return A;
}

const complex_t Amplitude::Adir(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  complex_t A(0.,0.);
  for (const auto& res : m_resonances) {
    A += res->evaluate( m_ps , mSq12 , mSq13 , mSq23 );
  }
  return A;
}

const complex_t Amplitude::Abar(const real_t& mSq12, const real_t& mSq13) const
{
  complex_t A(0.,0.);
  for (const auto& res : m_cnjresonances) {
    A += res->evaluate( m_ps , mSq12 , mSq13 );
  }
  return A;
}

const complex_t Amplitude::Abar(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  complex_t A(0.,0.);
  for (const auto& res : m_cnjresonances) {
    A += res->evaluate( m_ps , mSq12 , mSq13 , mSq23 );
  }
  return A;
}

const real_t Amplitude::AdirSq(const real_t& mSq12, const real_t& mSq13) const
{
  return std::norm( this->Adir( mSq12, mSq13 ) );
}

const real_t Amplitude::AdirSq(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return std::norm( this->Adir( mSq12, mSq13 , mSq23 ) );
}

const real_t Amplitude::AbarSq(const real_t& mSq12, const real_t& mSq13) const
{
  return std::norm( this->Abar( mSq12, mSq13 ) );
}

const real_t Amplitude::AbarSq(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return std::norm( this->Abar( mSq12, mSq13, mSq23 ) );
}

const complex_t Amplitude::A1(const real_t& mSq12, const real_t& mSq13) const
{
  return ( this->Adir( mSq12 , mSq13 ) + this->Abar( mSq12 , mSq13 ) ) / (real_t)2.;
}

const complex_t Amplitude::A1(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return ( this->Adir( mSq12 , mSq13 , mSq23 ) + this->Abar( mSq12 , mSq13 , mSq23 ) ) / (real_t)2.;
}

const complex_t Amplitude::A2(const real_t& mSq12, const real_t& mSq13) const
{
  return ( this->Adir( mSq12 , mSq13 ) - this->Abar( mSq12 , mSq13 ) ) / (real_t)2.;
}


const complex_t Amplitude::A2(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return ( this->Adir( mSq12 , mSq13 , mSq23 ) - this->Abar( mSq12 , mSq13 , mSq23 ) ) / (real_t)2.;
}

const real_t Amplitude::A1Sq(const real_t& mSq12, const real_t& mSq13) const
{
  return std::norm( this->A1( mSq12 , mSq13 ) );
}

const real_t Amplitude::A1Sq(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return std::norm( this->A1( mSq12 , mSq13 , mSq23 ) );
}

const real_t Amplitude::A2Sq(const real_t& mSq12, const real_t& mSq13) const
{
  return std::norm( this->A2( mSq12 , mSq13 ) );
}

const real_t Amplitude::A2Sq(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return std::norm( this->A2( mSq12 , mSq13 , mSq23 ) );
}

const real_t Amplitude::ASq(const real_t& mSq12, const real_t& mSq13) const
{
  return ( this->AdirSq( mSq12 , mSq13 ) + this->AbarSq( mSq12 , mSq13 ) ) / (real_t)2.;
}
const real_t Amplitude::ASq(const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return ( this->AdirSq( mSq12 , mSq13 ) + this->AbarSq( mSq12 , mSq13 , mSq23 ) ) / (real_t)2.;
}

// Individual resonances.
const complex_t Amplitude::Adir(std::string name, const real_t& mSq12, const real_t& mSq13) const
{
  return get( name )->evaluate( m_ps , mSq12 , mSq13 );
}

const complex_t Amplitude::Adir(std::string name, const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return get( name )->evaluate( m_ps , mSq12 , mSq13 , mSq23 );
}

const complex_t Amplitude::Abar(std::string name, const real_t& mSq12, const real_t& mSq13) const
{
  return get( name+"_cnj" )->evaluate( m_ps , mSq12 , mSq13 );
}

const complex_t Amplitude::Abar(std::string name, const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return get( name+"_cnj" )->evaluate( m_ps , mSq12 , mSq13 , mSq23 );
}

const real_t Amplitude::AdirSq(std::string name, const real_t& mSq12, const real_t& mSq13) const
{
  return std::norm( this->Adir( name, mSq12, mSq13 ) );
}

const real_t Amplitude::AdirSq(std::string name, const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return std::norm( this->Adir( name, mSq12, mSq13 , mSq23 ) );
}

const real_t Amplitude::AbarSq(std::string name, const real_t& mSq12, const real_t& mSq13) const
{
  return std::norm( this->Abar( name, mSq12, mSq13 ) );
}

const real_t Amplitude::AbarSq(std::string name, const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return std::norm( this->Abar( name, mSq12, mSq13, mSq23 ) );
}

const complex_t Amplitude::A1(std::string name, const real_t& mSq12, const real_t& mSq13) const
{
  return ( this->Adir( name, mSq12 , mSq13 ) + this->Abar( name, mSq12 , mSq13 ) ) / (real_t)2.;
}

const complex_t Amplitude::A1(std::string name, const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return ( this->Adir( name, mSq12 , mSq13 , mSq23 ) + this->Abar( name, mSq12 , mSq13 , mSq23 ) ) / (real_t)2.;
}

const complex_t Amplitude::A2(std::string name, const real_t& mSq12, const real_t& mSq13) const
{
  return ( this->Adir( name, mSq12 , mSq13 ) - this->Abar( name, mSq12 , mSq13 ) ) / (real_t)2.;
}


const complex_t Amplitude::A2(std::string name, const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return ( this->Adir( name, mSq12 , mSq13 , mSq23 ) - this->Abar( name, mSq12 , mSq13 , mSq23 ) ) / (real_t)2.;
}

const real_t Amplitude::A1Sq(std::string name, const real_t& mSq12, const real_t& mSq13) const
{
  return std::norm( this->A1( name, mSq12 , mSq13 ) );
}

const real_t Amplitude::A1Sq(std::string name, const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return std::norm( this->A1( name, mSq12 , mSq13 , mSq23 ) );
}

const real_t Amplitude::A2Sq(std::string name, const real_t& mSq12, const real_t& mSq13) const
{
  return std::norm( this->A2( name, mSq12 , mSq13 ) );
}

const real_t Amplitude::A2Sq(std::string name, const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return std::norm( this->A2( name, mSq12 , mSq13 , mSq23 ) );
}

const real_t Amplitude::ASq(std::string name, const real_t& mSq12, const real_t& mSq13) const
{
  return ( this->AdirSq( name , mSq12 , mSq13 ) + this->AbarSq( name , mSq12 , mSq13 ) ) / (real_t)2.;
}
const real_t Amplitude::ASq(std::string name, const real_t& mSq12, const real_t& mSq13, const real_t& mSq23) const
{
  return ( this->AdirSq( name , mSq12 , mSq13 ) + this->AbarSq( name , mSq12 , mSq13 , mSq23 ) ) / (real_t)2.;
}