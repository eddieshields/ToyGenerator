#ifndef TOYGEN_SEQUENCE_H
#define TOYGEN_SEQUENCE_H

#include "algorithm.h"
#include "algorithmstore.h"
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
    Algorithm* tmp = NULL;
    tmp = &input;
    tmp->next=NULL;
    if ( head == NULL ) {
      head=tmp;
      tail=tmp;
      tmp=NULL;
    } else {
      tail->next=tmp;
      tail=tmp;
    }
  }

  void printAlgorithmSequence()
  {
    Algorithm* tmp = nullptr;
    tmp = head;
    while ( tmp != NULL ){
				INFO(tmp->name());
				tmp=tmp->next;
			}
    return;
  }
  
  AlgorithmStore gAlgorithmStore;
  Algorithm* head;
  Algorithm* tail;

  void operator=(const Sequence& other) 
  {
    gAlgorithmStore = other.gAlgorithmStore;
    head = other.head;
  }
};

#endif