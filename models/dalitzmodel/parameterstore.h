#ifndef TOYGEN_PARAMETERSTORE_H
#define TOYGEN_PARAMETERSTORE_H

#include "parameter.h"
#include "msgservice.h"

#include <vector>
#include <string>

namespace DalitzModel {

class ParameterStore
{
public:
  ParameterStore() = default;
  ~ParameterStore() {};

  void addParameter(Parameter param)
  {
    m_parameters.push_back( std::move(param) );
  }

  bool find(std::string name)
  {
    for (auto& p : m_parameters) {
      if ( name == p.name() ) return true;
    }
    return false;
  }

  Parameter& get(std::string name)
  {
    for (auto& p : m_parameters ) {
      if ( name == p.name() ) return p;
    }
    FATAL("Parameter " << name << " doesn't exist");
    // Cheat for compilation. FATAL line above will exit program 
    // before getting to this point.
    return m_parameters[0];
  }

  std::vector<std::string> names()
  {
    std::vector<std::string> _names;
    for (auto& p : m_parameters) {
      _names.push_back( p.name() );
    }
    return _names;
  }

private:
  std::vector<Parameter> m_parameters;
};

}

extern DalitzModel::ParameterStore gParameterStore;

#endif