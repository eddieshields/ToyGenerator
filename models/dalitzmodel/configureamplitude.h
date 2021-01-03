#ifndef TOYGEN_CONFIGUREAMPLITUDE_H
#define TOYGEN_CONFIGUREAMPLITUDE_H

#include "flatte.h"
#include "relbreitwigner.h"
#include "parameter.h"
#include "coefficient.h"
#include "resonance.h"
#include "dalitzamplitude.h"
#include "msgservice.h"
#include "configfile.h"

// json.
#include "nlohmann/json.hpp"
using json = nlohmann::json;

#include "string.h"
#include <fstream>
#include <sstream>

namespace DalitzModel {

class DalitzAmplitude;

class ConfigureAmplitude
{
public:
  ConfigureAmplitude(std::string cfgfile);
  ~ConfigureAmplitude() {}

  void addFlatte(std::string name, std::vector<std::string> res);
  void addRBW   (std::string name, std::vector<std::string> res);

  Parameter getParameter(std::string name);

  DalitzAmplitude& amplitude() { return m_amp; }
private:
  ConfigFile m_config;

  DalitzAmplitude m_amp;
};

}

#endif