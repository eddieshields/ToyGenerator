#include "dalitzamplitude.h"

using namespace DalitzModel;

const std::complex<double> DalitzAmplitude::Adir(const double& mSq12, const double& mSq13) const
{
  std::complex<double> A(0.,0.);
  Resonance* res = nullptr;
  res = headDir;
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
  res = headDir;
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
  res = headCnj;
  while ( res != nullptr ) {
    A += res->evaluate( _ps , mSq12 , mSq13 );
    res = res->next;
  }
  return A;
}

const std::complex<double> DalitzAmplitude::Abar(const double& mSq12, const double& mSq13, const double& mSq23) const
{
  std::complex<double> A(0.,0.);
  Resonance* res = nullptr;
  res = headCnj;
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

void DalitzAmplitude::addDirResonance(Resonance* res)
{
  m_dirresonances.push_back( std::move(static_cast<Resonance*>(res)) );
  addDirResonanceToList(m_dirresonances[m_dirresonances.size()-1]);
}

void DalitzAmplitude::addCnjResonance(Resonance* res)
{
  m_cnjresonances.push_back( std::move(static_cast<Resonance*>(res)) );
  addCnjResonanceToList(m_cnjresonances[m_cnjresonances.size()-1]);
}

void DalitzAmplitude::addDirResonanceToList(Resonance* res)
{
  Resonance* tmp = nullptr;
  tmp = res;
  tmp->next=nullptr;
  if ( headDir == nullptr ) {
    headDir=tmp;
    tailDir=tmp;
    tmp=nullptr;
  } else {
    tailDir->next=tmp;
    tailDir=tmp;
  }
  return;
}

void DalitzAmplitude::addCnjResonanceToList(Resonance* res)
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

void DalitzAmplitude::printResonances()
{
  std::string param_str = "Resonances = ";
  Resonance* tmp = nullptr;
  tmp = headDir;
  while ( tmp != NULL ){
    param_str += tmp->name()+", ";
		tmp=tmp->next;
	}
  param_str.replace(param_str.size()-2,2,"");
  INFO(param_str);
  return;
}