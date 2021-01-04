#include "configfile.h"

using namespace DalitzModel;

ConfigFile::ConfigFile(const std::string cfgfile)
{
  std::ifstream ifs(cfgfile);

  std::string line;
  while (std::getline(ifs, line)) {
    if (line.empty() || line.at(0) == '#') {
      continue;
    }
    std::istringstream iss(line);
    std::vector<std::string> results(std::istream_iterator<std::string>{iss},std::istream_iterator<std::string>());
    std::vector<std::string> associations;
    associations.insert(associations.end(),results.begin()+2,results.end());
    m_entries[results[0]] = std::move( associations );
  }
}