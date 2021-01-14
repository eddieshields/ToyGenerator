#ifndef TOYGEN_CONFIGUREAMPLITUDE_H
#define TOYGEN_CONFIGUREAMPLITUDE_H

#include "flatte.h"
#include "relbreitwigner.h"
#include "parameter.h"
#include "coefficient.h"
#include "resonance.h"
#include "dalitzamplitude.h"
#include "dalitzmixing.h"
#include "msgservice.h"
#include "configfile.h"
#include "parameterstore.h"
#include "correlationutils.h"

#include "string.h"
#include <fstream>
#include <sstream>

namespace DalitzModel {

class DalitzAmplitude;

class ConfigureAmplitude
{
public:
  ConfigureAmplitude(std::string cfgfile) : 
    m_config( cfgfile ),
    m_cfgfile( cfgfile )
  {}
  ~ConfigureAmplitude() {}

  void addFlatte(DalitzAmplitude& amp, std::string name, std::vector<std::string> res);
  void addRBW   (DalitzAmplitude& amp, std::string name, std::vector<std::string> res);

  void addCorrelation(CorrelationUtils::CovarianceMatrix& cov);

  void setMixing(DalitzMixing& amp);

  DalitzAmplitude operator()(DalitzAmplitude& amp);
  DalitzAmplitude operator()();

  DalitzMixing    operator()(DalitzMixing& amp);
private:
  ConfigFile  m_config;
  std::string m_cfgfile;

  Parameter getParameter(DalitzAmplitude& amp, std::string name);
};

}

#endif