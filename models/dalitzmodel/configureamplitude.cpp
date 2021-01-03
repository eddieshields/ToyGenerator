#include "configureamplitude.h"

using namespace DalitzModel;

DalitzAmplitude ConfigureAmplitude::operator()(DalitzAmplitude& amp)
{
  INFO("Defining the amplitude model from "+m_cfgfile+".");
  std::string name = "resos";
  for (auto& res : m_config[name])
  {
    if ( m_config[res][0] == "CC" ) {
      addFlatte( amp, res, m_config[res] );
    }
    else if ( m_config[res][0] == "RBW" ) {
      addRBW( amp, res, m_config[res] );
    } else {
      WARNING("Don't recognise type "+res+".");
    }
  }
  return amp;
}

DalitzAmplitude ConfigureAmplitude::operator()()
{
  DalitzAmplitude amp;
  return this->operator()(amp);
}

void ConfigureAmplitude::addFlatte(DalitzAmplitude& amp, std::string name, std::vector<std::string> res)
{
  const int resoA    = std::stoi(res[1]);
  const int resoB    = std::stoi(res[2]);
  const int l        = std::stoi(res[3]);
  const Parameter m  = getParameter(amp,res[4]);
  const Parameter w  = getParameter(amp,res[5]);
  const Parameter r  = getParameter(amp,res[6]);
  const Parameter c1 = getParameter(amp,res[7]);
  const Parameter c2 = getParameter(amp,res[8]);
  const Parameter g1 = getParameter(amp,res[9]);
  const Parameter g2 = getParameter(amp,res[10]);
  const Parameter mE = getParameter(amp,res[11]);
  const Parameter mP = getParameter(amp,res[12]);
  const Coeff c(c1,c2);

  Flatte* comp = new Flatte(name,c,resoA,resoB,m,w,l,r,g1,g2,mE,mP);
  amp.addResonance( comp );
}

void ConfigureAmplitude::addRBW(DalitzAmplitude& amp, std::string name, std::vector<std::string> res)
{
  const int resoA    = std::stoi(res[1]);
  const int resoB    = std::stoi(res[2]);
  const int l        = std::stoi(res[3]);
  const Parameter m  = getParameter(amp,res[4]);
  const Parameter w  = getParameter(amp,res[5]);
  const Parameter r  = getParameter(amp,res[6]);
  const Parameter c1 = getParameter(amp,res[7]);
  const Parameter c2 = getParameter(amp,res[8]);
  const Coeff c(c1,c2);

  RelBreitWigner* comp = new RelBreitWigner(name,c,resoA,resoB,m,w,l,r);
  amp.addResonance( comp );
}

Parameter ConfigureAmplitude::getParameter(DalitzAmplitude& amp, std::string name)
{
  if ( amp.parameters().find(name) == amp.parameters().end() )
  {
    std::vector<std::string> assoc = m_config[name];
    if ( assoc.size() < 3 ) {
      const double par = std::stod(assoc[0]);
      Parameter p( par );
      amp.parameters().insert(std::pair<std::string,Parameter>(name,std::move( p )));
    } else {
      const double par = std::stod(assoc[0]);
      const double err = std::stod(assoc[2]);
      Parameter p( par , err );
      amp.parameters().insert(std::pair<std::string,Parameter>(name,std::move( p )));
    }
  }
  return amp.parameters().at(name);
}
