#ifndef DALITZMODEL_CONFIGFILE_H
#define DALITZMODEL_CONFIGFILE_H

// STL.
#include <iostream>
#include <string>
#include <map>
#include <regex>
#include <sstream>
#include <fstream>

// DalitzModel.
#include "msgservice.h"

namespace DalitzModel {

class ConfigFile
{
  enum Section {
    None,
    Resonances,
    Parameters,
    CorrelationMatrix,
    CovarianceMatrix
  };
public:
  ConfigFile() = default;
  ConfigFile(const std::string cfgfile ) 
  { 
    decodeConfigFile( cfgfile );
  }
  virtual ~ConfigFile() {}

  bool find(std::string key);
  std::string get(std::string key);
  template<typename T>
  T get(std::string key)
  {
    T out;
    if ( m_entries.find(key) == m_entries.end() ) {
      WARNING(key << " not found!");
      return out;
    }
  
    // Pass string into object;
    std::string str = m_entries[key];
    std::istringstream is(str);
    is >> out;
    return out;
  }

  // Operators.
  friend std::ostream& operator<<(std::ostream& os, const ConfigFile& config)
  {
    // Start on new line:
    os << "Config file = \n";
    // Loop over all entries.
    for (auto& entry : config.m_entries) {
      os << entry.first << " : " << entry.second << "\n";
    }
    return os;
  }
  friend std::istream& operator>>(std::istream& is, ConfigFile& config)
  {
    std::string file;;
    is >> file;
    config.decodeConfigFile( file );
    return is;
  }

private:
  void decodeConfigFile(const std::string cfgfile);

  void decodeResonances       (const std::string line);
  void decodeParameters       (const std::string line);
  void decodeCorrelationMatrix(const std::string line);
  void decodeCovarianceMatrix (const std::string line);

  bool is_empty(std::ifstream& file);

  void addEntry(const std::string line);

  std::map<std::string,std::string> m_entries;
};

}

#endif