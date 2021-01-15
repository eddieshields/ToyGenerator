#include "configureamplitude.h"

using namespace DalitzModel;

DalitzAmplitude ConfigureAmplitude::operator()(DalitzAmplitude& amp)
{
  INFO("Defining the amplitude model from "+m_cfgfile+".");

  // Define the parameters and put them in a store so they can be accessed and configured.
  defineParameters();

  if ( m_random ) {
    // If define apply covariance matrix to parameters.
    CorrelationUtils::CovarianceMatrix cov;
    bool definedCorrelation = false;
    if ( m_config.existsCovarianceMatrix() ) {
      INFO("Covariance matrix has been defined.");
      CorrelationUtils::CorrelationMatrix cor = m_config.Correlation();
      std::vector<double> errors;
      for (auto& name : cor.names()) {
        errors.push_back( gParameterStore.get(name).error() );
      }
      TMatrixDSym matrix = cor.matrix();
      cov = CorrelationUtils::CovarianceMatrix(cor.names(),matrix);
      definedCorrelation = true;
    } else if ( m_config.existsCorrelationMatrix() ) {
      INFO("Correlation matrix has been defined.");
      cov = m_config.Covariance();
      definedCorrelation = true;
    }
  
    // Add correlation if it is defined.
    if ( definedCorrelation ) addCorrelation(cov);
  }
  // Define resonances last after all configuration has taken place.
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

  if ( m_polar ) {
    Coeff::setPolar();
  }
  return amp;
}

DalitzAmplitude ConfigureAmplitude::operator()()
{
  DalitzAmplitude amp;
  return this->operator()(amp);
}

DalitzMixing ConfigureAmplitude::operator()(DalitzMixing& amp)
{

  this->operator()(amp.amplitude());
  setMixing( amp );
  return amp;
;}

void ConfigureAmplitude::addFlatte(DalitzAmplitude& amp, std::string name, std::vector<std::string> res)
{
  // Set Parameter
  const int resoA    = std::stoi(res[1]);
  const int resoB    = std::stoi(res[2]);
  const int l        = std::stoi(res[3]);
  const int noRes    = 6 - resoA - resoB;
  const Parameter m  = getParameter(res[4]);
  const Parameter w  = getParameter(res[5]);
  const Parameter r  = getParameter(res[6]);
  const Parameter c1 = getParameter(res[7]);
  const Parameter c2 = getParameter(res[8]);
  const Parameter g1 = getParameter(res[9]);
  const Parameter g2 = getParameter(res[10]);
  const Parameter mE = getParameter(res[11]);
  const Parameter mP = getParameter(res[12]);
  const Coeff c(c1,c2);

  Flatte* comp = new Flatte(name,c,resoA,resoB,m,w,l,r,g1,g2,mE,mP);
  amp.addDirResonance( comp );
  if ( resoA == 2 ) {
    Flatte* compCnj = new Flatte(name,c,resoB,resoA,m,w,l,r,g1,g2,mE,mP);
    amp.addCnjResonance( compCnj );
  } else {
    Flatte* compCnj = new Flatte(name,c,resoA,noRes,m,w,l,r,g1,g2,mE,mP);
    amp.addCnjResonance( compCnj );
  }
}

void ConfigureAmplitude::addRBW(DalitzAmplitude& amp, std::string name, std::vector<std::string> res)
{
  const int resoA     = std::stoi(res[1]);
  const int resoB     = std::stoi(res[2]);
  const int noRes     = 6 - resoA - resoB;
  const int l         = std::stoi(res[3]);
  const Parameter m  = getParameter(res[4]);
  const Parameter w  = getParameter(res[5]);
  const Parameter r  = getParameter(res[6]);
  const Parameter c1 = getParameter(res[7]);
  const Parameter c2 = getParameter(res[8]);
  const Coeff c(c1,c2);

  RelBreitWigner* comp = new RelBreitWigner(name,c,resoA,resoB,m,w,l,r);
  amp.addDirResonance( comp );
  if ( resoA == 2 ) {
    RelBreitWigner* compCnj = new RelBreitWigner(name,c,resoB,resoA,m,w,l,r);
    amp.addCnjResonance( compCnj );
  } else {
    RelBreitWigner* compCnj = new RelBreitWigner(name,c,resoA,noRes,m,w,l,r);
    amp.addCnjResonance( compCnj );
  }
}

void ConfigureAmplitude::setMixing(DalitzMixing& amp)
{
  if ( m_config.find("x") ) amp.setX( std::stod(m_config["x"][0]) );
  if ( m_config.find("y") ) amp.setY( std::stod(m_config["y"][0]) );
  if ( m_config.find("p") ) amp.setP( std::stod(m_config["p"][0]) );
  if ( m_config.find("q") ) amp.setQ( std::stod(m_config["q"][0]) ); 
  return;
}

void ConfigureAmplitude::defineParameters()
{
  std::map<std::string,std::vector<std::string>> params = m_config.parameters();

  for (auto& p : params) {
    std::string name = p.first;
    std::vector<std::string> assoc = p.second;
    if ( assoc.size() < 3 ) {
      const double par = std::stod(assoc[0]);
      Parameter p( name , par );
      gParameterStore.addParameter( p );
    } else {
      const double par = std::stod(assoc[0]);
      const double err = std::stod(assoc[2]);
      Parameter p( name , par , err );
      gParameterStore.addParameter( p );
    }
  }
  return;
}

Parameter& ConfigureAmplitude::getParameter(std::string name)
{
  return gParameterStore.get(name);
}

void ConfigureAmplitude::addCorrelation(CorrelationUtils::CovarianceMatrix& cov)
{
  std::vector<double> values, errors;
  for (auto& name : cov.names() ) {
    values.push_back( gParameterStore.get(name).value() );
    values.push_back( gParameterStore.get(name).error() );
  }
  std::vector<double> new_values = CorrelationUtils::VaryWithinErrors(values,errors,cov());

  int i = 0;
  for (auto& name : cov.names() ) {
    gParameterStore.get(name).setVal( new_values[i] );
    i++;
  }

  for (auto& name : gParameterStore.names() ) {
    for (auto& used_name : cov.names() ) {
      if ( name == used_name ) continue;
      gParameterStore.get(name).setRandom();
    }
  }
  return;
}
