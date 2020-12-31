#ifndef TOYGEN_TUPLING_H
#define TOYGEN_TUPLING_H

#include "event.h"
#include "algorithm.h"
#include "msgservice.h"
#include "param.h"
#include "particleparam.h"
#include "compositeparam.h"
#include "eventparam.h"
#include "descriptor.h"

#include <vector>
#include <map>
#include <string>

class Tupling : public Algorithm
{
public: 
  Tupling(std::string name) : 
    Algorithm(name),
    head(nullptr),
    tail(nullptr)
  {}
  ~Tupling() {}

  virtual void operator() (Event& ev);

  void addMomentum();
  void addMass();
  void addTime();
  void addCharge();
  void addEventInfo();
  void addParam(Param* param);
  void addParam(Param& param);
  void printParams();

  std::vector<std::string> getVariables();

  void addCompositeMass();
  void addCompositeMass(int index1, int index2);

private:
  void addParamToList(Param* param);
  std::vector<Param*> m_variables;

  Param* head = {nullptr};
  Param* tail = {nullptr};
};

#endif