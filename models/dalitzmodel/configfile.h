#ifndef TOYGEN_CONFIGFILE_H
#define TOYGEN_CONFIGFILE_H

#include "msgservice.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <iterator>  

namespace DalitzModel {

class ConfigFile
{
public:
  ConfigFile(const std::string cfgfile );
  ~ConfigFile() {}

  bool find(std::string entry) { if ( m_entries.find(entry) == m_entries.end() ) return false; return true; }
  std::vector<std::string> operator[](std::string entry) { return m_entries[entry]; }
private:
  std::map<std::string,std::vector<std::string>> m_entries;
};

}

#endif