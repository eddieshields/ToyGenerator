#include "configfile.h"

using namespace DalitzModel;


std::string ConfigFile::get(std::string key)
{
  std::string out;
  if ( m_entries.find(key) == m_entries.end() ) {
    WARNING(key << " not found!");
    return out;
  }

  // Pass string into object;
  out = m_entries[key];
  return out;
}

void ConfigFile::decodeConfigFile(const std::string cfgfile)
{
  std::ifstream ifs(cfgfile);
  if ( is_empty( ifs ) ) FATAL( cfgfile << " not found!" );
  INFO("Will configure model from " << cfgfile); 
  std::string line;
  ConfigFile::Section section = ConfigFile::None;
  while (std::getline(ifs, line)) {
    if (line.empty() || line.at(0) == '#') {
      continue;
    }

    if ( line == "Resonances" ) {
      section = ConfigFile::Resonances;
      continue;
    } else if ( line == "Parameters" ) {
      section = ConfigFile::Parameters;
      continue;
    } else if ( line == "CorrelationMatrix" ) {
      section = ConfigFile::CorrelationMatrix;
      continue;
    } else if ( line == "CovarianceMatrix" ) {
      section = ConfigFile::CovarianceMatrix;
      continue;
    } else {
      switch(section)
      {
      case ConfigFile::Resonances:
        decodeResonances( line );
        continue;
      case ConfigFile::Parameters:
        decodeParameters( line );
        continue;
      case ConfigFile::CorrelationMatrix:
        decodeCorrelationMatrix( line );
        continue;
      case ConfigFile::CovarianceMatrix:
        decodeCovarianceMatrix( line );
        continue;
      default:
        continue;
      }
    }
  }
}

void ConfigFile::addEntry(const std::string line)
{
  // Entry to go into map;
  std::pair<std::string,std::string> entry;

  // Add key to entry.
  std::stringstream ss(line);
  ss >> entry.first;

  // Get value corresponding to key.
  std::string value = line;
  int key_pos = value.find("=");
  if ( key_pos != std::string::npos ) {
    value.replace(0,key_pos+1,"");
  } else {
    key_pos = value.find(":");
    if ( key_pos != std::string::npos ) {
      value.replace(0,key_pos+1,"");
    }
  }

  // Remove leading and trailing white space.
  std::regex_replace(value, std::regex("^ +| +$|( ) +"), "$1");

  // Add line to entry.
  entry.second = value;

  // Add to entries.
  m_entries.insert( entry );
}

void ConfigFile::decodeResonances(const std::string line)
{
  addEntry( line );
  return;
}

void ConfigFile::decodeParameters(const std::string line)
{
  addEntry( line );
  return;
}

void ConfigFile::decodeCorrelationMatrix(const std::string line)
{
  return;
}

void ConfigFile::decodeCovarianceMatrix(const std::string line)
{
  return;
}

bool ConfigFile::is_empty(std::ifstream& file)
{
  return file.peek() == std::ifstream::traits_type::eof();
}