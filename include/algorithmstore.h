#ifndef TOYGEN_ALGORITHMSTORE_H
#define TOYGEN_ALGORITHMSTORE_H

#include "algorithm.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>


struct AlgorithmStore
{
  std::map<std::string,Algorithm*> m_algos;

  void addToStore(Algorithm* algo)
  {
    if (m_algos.find(algo->name()) != m_algos.end()) {
      std::cout << "Algorithm " << algo->name() << " already exists. Please give all algorithms a unique name" << std::endl;
      exit(EXIT_FAILURE);
    } else {
      m_algos[algo->name()] = algo;
      std::cout << "Added " << algo->name() << " to store" << std::endl;
    }
  }

  template<class T>
  void addToStore(T algoT)
  {
    Algorithm* algo = reinterpret_cast<Algorithm*>(&algoT);
    if (m_algos.find(algo->name()) != m_algos.end()) {
      std::cout << "Algorithm " << algo->name() << " already exists. Please give all algorithms a unique name" << std::endl;
      exit(EXIT_FAILURE);
    } else {
      m_algos[algo->name()] = algo;
      std::cout << "Added " << algo->name() << " to store" << std::endl;
    }
  }

  Algorithm* getAlgorithm(std::string name)
  {
    if (m_algos.find(name) != m_algos.end()) {
      return m_algos[name];
    } else {
      std::cout << "Algorithm " << name << " doesn't exists." << std::endl;
    }
    return nullptr;
  }

  Algorithm* head;
};

#endif