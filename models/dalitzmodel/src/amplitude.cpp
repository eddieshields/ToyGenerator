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
  std::vector<complex_t> A;
  const auto n = m_resonances.size();
  A.resize( n );
  // Make vectorizable.
  for (std::size_t i = 0; i < n; ++i) {
    A[i] = m_resonances[i]->evaluate( m_ps , mSq12 , mSq13);
  }
  return std::accumulate(A.begin(),A.end(),complex_t());
}

const complex_t Amplitude::Adir(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  std::vector<complex_t> A;
  const auto n = m_resonances.size();
  A.resize( n );
  // Make vectorizable.
  for (std::size_t i = 0; i < n; ++i) {
    A[i] = m_resonances[i]->evaluate( m_ps , mSq12 , mSq13 , mSq23 );
  }
  return std::accumulate(A.begin(),A.end(),complex_t());
}

const complex_t Amplitude::Abar(const double& mSq12, const double& mSq13) const
{
  std::vector<complex_t> A;
  const auto n = m_resonances.size();
  A.resize( n );
  // Make vectorizable.
  for (std::size_t i = 0; i < n; ++i) {
    A[i] = m_cnjresonances[i]->evaluate( m_ps , mSq12 , mSq13 );
  }
  return std::accumulate(A.begin(),A.end(),complex_t());
}

const complex_t Amplitude::Abar(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  std::vector<complex_t> A;
  const auto n = m_resonances.size();
  A.resize( n );
  // Make vectorizable.
  for (std::size_t i = 0; i < n; ++i) {
    A[i] = m_cnjresonances[i]->evaluate( m_ps , mSq12 , mSq13 , mSq23 );
  }
  return std::accumulate(A.begin(),A.end(),complex_t());
}

const double Amplitude::AdirSq(const double& mSq12, const double& mSq13) const
{
  return std::norm( this->Adir( mSq12, mSq13 ) );
}

const double Amplitude::AdirSq(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( this->Adir( mSq12, mSq13 , mSq23 ) );
}

const double Amplitude::AbarSq(const double& mSq12, const double& mSq13) const
{
  return std::norm( this->Abar( mSq12, mSq13 ) );
}

const double Amplitude::AbarSq(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( this->Abar( mSq12, mSq13, mSq23 ) );
}

const complex_t Amplitude::A1(const double& mSq12, const double& mSq13) const
{
  return ( this->Adir( mSq12 , mSq13 ) + this->Abar( mSq12 , mSq13 ) ) / 2.;
}

const complex_t Amplitude::A1(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return ( this->Adir( mSq12 , mSq13 , mSq23 ) + this->Abar( mSq12 , mSq13 , mSq23 ) ) / 2.;
}

const complex_t Amplitude::A2(const double& mSq12, const double& mSq13) const
{
  return ( this->Adir( mSq12 , mSq13 ) - this->Abar( mSq12 , mSq13 ) ) / 2.;
}


const complex_t Amplitude::A2(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return ( this->Adir( mSq12 , mSq13 , mSq23 ) - this->Abar( mSq12 , mSq13 , mSq23 ) ) / 2.;
}

const double Amplitude::A1Sq(const double& mSq12, const double& mSq13) const
{
  return std::norm( this->A1( mSq12 , mSq13 ) );
}

const double Amplitude::A1Sq(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( this->A1( mSq12 , mSq13 , mSq23 ) );
}

const double Amplitude::A2Sq(const double& mSq12, const double& mSq13) const
{
  return std::norm( this->A2( mSq12 , mSq13 ) );
}

const double Amplitude::A2Sq(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( this->A2( mSq12 , mSq13 , mSq23 ) );
}

// Individual resonances.
const complex_t Amplitude::Adir(std::string name, const double& mSq12, const double& mSq13) const
{
  complex_t A(0.,0.);
  Resonance* res = nullptr;
  res = headDir;
  while ( res != nullptr ) {
    if ( res->name() != name ) continue;
    A += res->evaluate( m_ps , mSq12 , mSq13);
    res = res->next;
  }
  return A;
}

const complex_t Amplitude::Adir(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  complex_t A(0.,0.);
  Resonance* res = nullptr;
  res = headDir;
  while ( res != nullptr ) {
    if ( res->name() != name ) continue;
    A += res->evaluate( m_ps , mSq12 , mSq13 , mSq23 );
    res = res->next;
  }
  return A;
}

const complex_t Amplitude::Abar(std::string name, const double& mSq12, const double& mSq13) const
{
  complex_t A(0.,0.);
  Resonance* res = nullptr;
  res = headCnj;
  while ( res != nullptr ) {
    if ( res->name() != name+"_cnj" ) continue;
    A += res->evaluate( m_ps , mSq12 , mSq13 );
    res = res->next;
  }
  return A;
}

const complex_t Amplitude::Abar(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  complex_t A(0.,0.);
  Resonance* res = nullptr;
  res = headCnj;
  while ( res != nullptr ) {
    if ( res->name() != name+"_cnj" ) continue;
    A += res->evaluate( m_ps , mSq12 , mSq13 );
    res = res->next;
  }
  return A;
}

const double Amplitude::AdirSq(std::string name, const double& mSq12, const double& mSq13) const
{
  return std::norm( this->Adir( name, mSq12, mSq13 ) );
}

const double Amplitude::AdirSq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( this->Adir( name, mSq12, mSq13 , mSq23 ) );
}

const double Amplitude::AbarSq(std::string name, const double& mSq12, const double& mSq13) const
{
  return std::norm( this->Abar( name, mSq12, mSq13 ) );
}

const double Amplitude::AbarSq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( this->Abar( name, mSq12, mSq13, mSq23 ) );
}

const complex_t Amplitude::A1(std::string name, const double& mSq12, const double& mSq13) const
{
  return ( this->Adir( name, mSq12 , mSq13 ) + this->Abar( name, mSq12 , mSq13 ) ) / 2.;
}

const complex_t Amplitude::A1(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return ( this->Adir( name, mSq12 , mSq13 , mSq23 ) + this->Abar( name, mSq12 , mSq13 , mSq23 ) ) / 2.;
}

const complex_t Amplitude::A2(std::string name, const double& mSq12, const double& mSq13) const
{
  return ( this->Adir( name, mSq12 , mSq13 ) - this->Abar( name, mSq12 , mSq13 ) ) / 2.;
}


const complex_t Amplitude::A2(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return ( this->Adir( name, mSq12 , mSq13 , mSq23 ) - this->Abar( name, mSq12 , mSq13 , mSq23 ) ) / 2.;
}

const double Amplitude::A1Sq(std::string name, const double& mSq12, const double& mSq13) const
{
  return std::norm( this->A1( name, mSq12 , mSq13 ) );
}

const double Amplitude::A1Sq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( this->A1( name, mSq12 , mSq13 , mSq23 ) );
}

const double Amplitude::A2Sq(std::string name, const double& mSq12, const double& mSq13) const
{
  return std::norm( this->A2( name, mSq12 , mSq13 ) );
}

const double Amplitude::A2Sq(std::string name, const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( this->A2( name, mSq12 , mSq13 , mSq23 ) );
}