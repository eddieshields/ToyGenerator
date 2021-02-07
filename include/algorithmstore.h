#ifndef TOYGEN_ALGORITHMSTORE_H
#define TOYGEN_ALGORITHMSTORE_H

#include "algorithm.h"
#include "msgservice.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <map>

//#include <boost/any.hpp>

struct AlgorithmStore
{
public: 
  AlgorithmStore() {};
  ~AlgorithmStore() {};

private:
  //std::map<std::string,boost::any>  m_algos;
  std::map<std::string,std::string> m_ptrs;
};

extern AlgorithmStore gAlgorithmStore;

#endif