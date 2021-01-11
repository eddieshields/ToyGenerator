#ifndef TOYGEN_TEMPLATEALGORITHM_H
#define TOYGEN_TEMPLATEALGORITHM_H
// Remember to update the preprocesser directive to the class name.
// This is necessary for a successful compilation.

#include "event.h"
#include "algorithm.h"

// Any algorithm should inherit from the Algorithm class.
class TemplateAlgorithm : public Algorithm
{
public:
  // Every algorithm requires a unique name and the Algorithm base class in initialized by the name.
  TemplateAlgorithm(std::string name) :
    Algorithm( name )
  {}
  ~TemplateAlgorithm() {}

  // The operator is where the action happens. The input is a reference to an event object.
  virtual void operator() (Event& ev)
  {
    // Act on the object in here
    return;
  }
};

#endif