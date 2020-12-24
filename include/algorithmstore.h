#ifndef TOYGEN_ALGORITHMSTORE_H
#define TOYGEN_ALGORITHMSTORE_H

#include "algorithm.h"
#include "msgservice.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>


struct AlgorithmStore
{
  std::map<std::string,Algorithm*> m_algos;

  void setHead(Algorithm* algo) { head = algo; }
  void setHead(std::string name) 
  {
    if (m_algos.find(name) != m_algos.end()) {
      head =  m_algos[name];
      INFO("Setting algorithm head to: "+head->name());
    } else {
      ERROR("Algorithm "+name+" doesn't exists.");
    }
    return;
  }

  void addToStore(Algorithm* algo)
  {
    if (m_algos.find(algo->name()) != m_algos.end()) {
      FATAL("Algorithm "+algo->name()+" already exists. Please give all algorithms a unique name.");
    } else {
      m_algos[algo->name()] = algo;
      DEBUG("Added "+algo->name()+" to store.");
    }
  }

  template<class T>
  void addToStore(T algoT)
  {
    Algorithm* algo = reinterpret_cast<Algorithm*>(&algoT);
    if (m_algos.find(algo->name()) != m_algos.end()) {
      FATAL("Algorithm "+algo->name()+" already exists. Please give all algorithms a unique name.");
    } else {
      m_algos[algo->name()] = algo;
      DEBUG("Added "+algo->name()+" to store.");
    }
  }

  Algorithm* getAlgorithm(std::string name)
  {
    if (m_algos.find(name) != m_algos.end()) {
      return m_algos[name];
    } else {
      ERROR("Algorithm "+name+" doesn't exists.");
    }
    return nullptr;
  }

  Algorithm* head;
};

#endif