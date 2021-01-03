#include "dalitzamplitude.h"

using namespace DalitzModel;

const std::complex<double> DalitzAmplitude::Adir(const double& mSq12, const double& mSq13) const
{
  std::complex<double> A(0.,0.);
  Resonance* res = nullptr;
  res = head;
  while ( res != nullptr ) {
    A += res->evaluate( _ps , mSq12 , mSq13 );
    res = res->next;
  }
  return A;
}

const std::complex<double> DalitzAmplitude::Adir(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  std::complex<double> A(0.,0.);
  Resonance* res = nullptr;
  res = head;
  while ( res != nullptr ) {
    A += res->evaluate( _ps , mSq12 , mSq13 , mSq23 );
    res = res->next;
  }
  return A;
}

const std::complex<double> DalitzAmplitude::Abar(const double& mSq12, const double& mSq13) const
{
  std::complex<double> A(0.,0.);
  Resonance* res = nullptr;
  res = head;
  while ( res != nullptr ) {
    A += res->evaluate( _ps , mSq13 , mSq12 );
    res = res->next;
  }
  return A;
}

const std::complex<double> DalitzAmplitude::Abar(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  std::complex<double> A(0.,0.);
  Resonance* res = nullptr;
  res = head;
  while ( res != nullptr ) {
    A += res->evaluate( _ps , mSq13 , mSq12 , mSq23 );
    res = res->next;
  }
  return A;
}

const double DalitzAmplitude::AdirSq(const double& mSq12, const double& mSq13) const
{
  return std::norm( Adir( mSq12, mSq13 ) );
}

const double DalitzAmplitude::AdirSq(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( Adir( mSq12, mSq13 , mSq23 ) );
}

const double DalitzAmplitude::AbarSq(const double& mSq12, const double& mSq13) const
{
  return std::norm( Abar( mSq12, mSq13 ) );
}

const double DalitzAmplitude::AbarSq(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  return std::norm( Abar( mSq12, mSq13, mSq23 ) );
}

void DalitzAmplitude::addResonance(Resonance* res)
{
  m_resonances.push_back( std::move(static_cast<Resonance*>(res)) );
  addResonanceToList(m_resonances[m_resonances.size()-1]);
}

void DalitzAmplitude::addResonanceToList(Resonance* res)
{
  Resonance* tmp = nullptr;
  tmp = res;
  tmp->next=nullptr;
  if ( head == nullptr ) {
    head=tmp;
    tail=tmp;
    tmp=nullptr;
  } else {
    tail->next=tmp;
    tail=tmp;
  }
  return;
}

void DalitzAmplitude::printResonances()
{
  std::string param_str = "Resonances = ";
  Resonance* tmp = nullptr;
  tmp = head;
  while ( tmp != NULL ){
    param_str += tmp->name()+", ";
		tmp=tmp->next;
	}
  param_str.replace(param_str.size()-2,2,"");
  INFO(param_str);
  return;
}