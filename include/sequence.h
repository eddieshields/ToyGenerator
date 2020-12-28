#ifndef TOYGEN_SEQUENCE_H
#define TOYGEN_SEQUENCE_H

#include "algorithm.h"
#include "msgservice.h"

#include <iostream>

//extern AlgorithmStore gAlgorithmStore;

class Sequence
{
public:
  Sequence() = default;
  ~Sequence() {};

  template <typename IN_TYPE>
  void addAlgorithm(IN_TYPE& input)
  {
    Algorithm* tmp = nullptr ;
    tmp = &input;
    tmp->next=nullptr ;
    if ( head == nullptr ) {
      head=tmp;
      tail=tmp;
      tmp=nullptr ;
    } else {
      tail->next=tmp;
      tail=tmp;
    }
  }

  void printAlgorithmSequence()
  {
    std::string alg_str = "Sequence = ";
    Algorithm* tmp = nullptr;
    tmp = head;
    while ( tmp != nullptr ){
      alg_str += tmp->name()+", ";
			tmp=tmp->next;
		}
    alg_str.replace(alg_str.size()-2,2,"");
    INFO(alg_str);
    return;
  }
  
  Algorithm* head;
  Algorithm* tail;

  void operator=(const Sequence& other) 
  {
    head = other.head;
  }
};

#endif