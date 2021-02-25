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

#include <any>
#include <map>

namespace DalitzModel {

class ConfigureAmplitude
{
private:
  std::map<std::string,std::any> m_objects;
  ConfigFile m_config;
  Amplitude  m_amp;

  void build_model_from_file();
  void build_phasespace_from_file();
  void build_resonance_from_file(std::string name);
  void set_properties_from_file();

  bool find(std::string key)
  {
    if ( m_config.find(key) ) return true;
    return false;
  }
  template<typename T=std::string>
  T get(std::string key)
  {
    // If it is not already stored get the object.
    if ( m_objects.find(key) == m_objects.end() ) {
      // Get object from configuration file.
      std::any object = m_config.get<T>(key);
      // Add to memory
      m_objects.insert( std::pair<std::string,std::any>{ key , std::move(object) } );
    }
    // Return the object from class memory.
    return std::any_cast<T>( m_objects[key] );
  }
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