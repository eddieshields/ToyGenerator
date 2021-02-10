#ifndef DALITZMODEL_CONFIGUREAMPLITUDE_H
#define DALITZMODEL_CONFIGUREAMPLITUDE_H

// DalitzModel.
#include "relbreitwigner.h"
#include "flatte.h"
#include "coefficient.h"
#include "parameter.h"
#include "amplitude.h"
#include "configfile.h"
#include "msgservice.h"

namespace DalitzModel {

class ConfigureAmplitude
{
private:
  ConfigFile m_config;
  Amplitude  m_amp;

  void build_model_from_file();
  void build_phasespace_from_file();
  void build_resonance_from_file(std::string name);
public:
  ConfigureAmplitude() = default;
  ConfigureAmplitude(const std::string cfgfile) :
    m_config( cfgfile )
  {}
  virtual ~ConfigureAmplitude() {}

  // Operators.
  friend std::ostream& operator<<(std::ostream& os, const ConfigureAmplitude& cfgamp)
  {
    return os;
  }
  friend std::istream& operator>>(std::istream& is, ConfigureAmplitude& cfgamp)
  {
    is >> cfgamp.m_config;
    return is;
  }

  void appendRBW(std::string name);
  void appendFlatte(std::string name);

  Amplitude operator()() { build_model_from_file(); return m_amp; }
};

}

#endif