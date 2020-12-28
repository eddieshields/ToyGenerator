#ifndef TOYGEN_TUPLING_H
#define TOYGEN_TUPLING_H

#include "event.h"
#include "algorithm.h"
#include "msgservice.h"
#include "param.h"
#include "descriptor.h"

#include <vector>
#include <map>
#include <string>

class Tupling : public Algorithm
{
public: 
  Tupling(std::string name) : 
    Algorithm(name)
  {}
  ~Tupling() {}

  virtual void operator() (Event& ev);

  void addMomentum();
  void addCharge();
  void addParam(Param* param);
  void addParam(Param& param);
  void printParams();

  std::vector<std::string> getVariables();

private:
  void addParamToList(Param& param) { addParamToList(&param); }
  void addParamToList(Param* param);
  std::vector<Param> m_variables;

  Param* head = {nullptr};
  Param* tail = {nullptr};
};

#endif