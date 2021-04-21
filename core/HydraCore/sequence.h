#ifndef TOYGEN_SEQUENCE_H
#define TOYGEN_SEQUENCE_H

#include "algorithm.h"
#include "msgservice.h"

#include <iostream>

class Sequence
{
private:
  std::vector<Algorithm*> m_algorithms;

public:
  Sequence() = default;
  Sequence(Sequence& other) :
    m_algorithms( other.m_algorithms )
  {}
  ~Sequence() {};

  template <typename IN_TYPE>
  void addAlgorithm(IN_TYPE& input)
  {
    m_algorithms.push_back( static_cast<Algorithm*>(&input) );
  }

  void printAlgorithmSequence()
  {
    std::string alg_str = "Sequence = ";
    for (auto algo : m_algorithms ) {
      alg_str += algo->name()+", ";
		}
    alg_str.replace(alg_str.size()-2,2,"");
    INFO(alg_str);
    return;
  }

  inline const std::vector<Algorithm*>& operator()() const { return m_algorithms; }
};

extern Sequence gSequence;

#endif