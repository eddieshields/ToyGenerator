#include "configureamplitude.h"

using namespace DalitzModel;

ConfigureAmplitude::ConfigureAmplitude(const std::string cfgfile) :
  m_config( cfgfile )
{
  INFO("Defining the amplitude model from "+cfgfile+".");
  std::string name = "resos";
  for (auto& res : m_config[name])
  {
    if ( m_config[res][0] == "CC" ) {
      addFlatte( res, m_config[res] );
    }
    else if ( m_config[res][0] == "RBW" ) {
      addRBW( res, m_config[res] );
    } else {
      WARNING("Don't recognise type "+res+".");
    }
  }
}

void ConfigureAmplitude::addFlatte(std::string name, std::vector<std::string> res)
{
  const int resoA = std::stoi(res[1]);
  const int resoB = std::stoi(res[2]);
  const int l     = std::stoi(res[3]);
  const Parameter m = getParameter(res[4]);
  const Parameter w = getParameter(res[5]);
  const Parameter r = getParameter(res[6]);
  const Parameter c1 = getParameter(res[7]);
  const Parameter c2 = getParameter(res[8]);
  const Parameter g1 = getParameter(res[9]);
  const Parameter g2 = getParameter(res[10]);
  const Parameter mE = getParameter(res[11]);
  const Parameter mP = getParameter(res[12]);
  const Coeff c(c1,c2);

  Flatte* comp = new Flatte(name,c,resoA,resoB,m,w,l,r,g1,g2,mE,mP);
  m_amp.addResonance( comp );
}

void ConfigureAmplitude::addRBW(std::string name, std::vector<std::string> res)
{
  const int resoA = std::stoi(res[1]);
  const int resoB = std::stoi(res[2]);
  const int l     = std::stoi(res[3]);
  const Parameter m = getParameter(res[4]);
  const Parameter w = getParameter(res[5]);
  const Parameter r = getParameter(res[6]);
  const Parameter c1 = getParameter(res[7]);
  const Parameter c2 = getParameter(res[8]);
  const Coeff c(c1,c2);

  RelBreitWigner* comp = new RelBreitWigner(name,c,resoA,resoB,m,w,l,r);
  m_amp.addResonance( comp );
}

Parameter ConfigureAmplitude::getParameter(std::string name)
{
  if ( m_amp.parameters().find(name) == m_amp.parameters().end() )
  {
    std::vector<std::string> assoc = m_config[name];
    if ( assoc.size() < 3 ) {
      const double par = std::stod(assoc[0]);
      Parameter p( par );
      m_amp.parameters().insert(std::pair<std::string,Parameter>(name,std::move( p )));
    } else {
      const double par = std::stod(assoc[0]);
      const double err = std::stod(assoc[2]);
      Parameter p( par , err );
      m_amp.parameters().insert(std::pair<std::string,Parameter>(name,std::move( p )));
    }
  }
  return m_amp.parameters().at(name);
}
