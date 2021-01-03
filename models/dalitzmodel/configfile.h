#ifndef TOYGEN_CONFIGFILE_H
#define TOYGEN_CONFIGFILE_H

#include "msgservice.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iostream>

namespace DalitzModel {

class ConfigFile
{
public:
  ConfigFile(const std::string cfgfile );
  ~ConfigFile() {}

  template<class T> T read(std::string key) const;
  template<class T> T string_as_T(std::string& s);
  std::vector<std::string> operator[](std::string& entry) { return m_entries[entry]; }
private:
  std::map<std::string,std::vector<std::string>> m_entries;
};

}

#endif