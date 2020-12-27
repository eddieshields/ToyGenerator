#ifndef TOYGEN_TUPLING_H
#define TOYGEN_TUPLING_H

#include "event.h"
#include "algorithm.h"
#include "msgservice.h"

#include <vector>
#include <string>

class Tupling : public Algorithm
{
public:
  enum ParamType {
    Pdf,       //Pdf value.
    Weight,    //Weight.
    T,         //Time.
    Q,         //Charge.
	};
  Tupling(std::string name) : Algorithm(name) {}
  ~Tupling() {}

  virtual void operator() (Event& ev);

  const double getVariable(Tupling::ParamType& _type, Event& ev);
  const std::string getName(Tupling::ParamType& _type);
  const Tupling::ParamType getParamFromString(std::string name);
  void setVariables(std::vector<std::string> variables)
  {
    for (auto& v : variables) {
      ParamType p = getParamFromString(v);
      m_variables.push_back( p );
    }

    std::string vars = "Variables = ";
    for (auto& p : m_variables) {
      vars += getName(p)+", ";
    }
    vars.replace(vars.size()-2,2,"");
    INFO(vars);
  }

private:
  std::vector<Tupling::ParamType> m_variables;
};

#endif