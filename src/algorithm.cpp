#include "algorithm.h"
#include "sequence.h"

Algorithm::Algorithm(std::string name) :
    m_name(name)
  {
    gSequence.AddAlgorithm( this );
  }