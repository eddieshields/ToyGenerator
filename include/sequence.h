#ifndef TOYGEN_SEQUENCE_H
#define TOYGEN_SEQUENCE_H

#include "algorithm.h"
#include "algorithmstore.h"


#include <iostream>

class Sequence
{
public:
  Sequence() = default;
  template <typename... IN_TYPES>
  Sequence(IN_TYPES... inputs) 
  {
    addAlgorithm(inputs...);

    printAlgorithmSequence();
  }
  ~Sequence() {};

  template <class IN, class... IN_TYPES>
  void addAlgorithm(IN input, IN_TYPES... inputs)
  {
    gAlgorithmStore.addToStore(input);
    if ( head == nullptr ) {
      head = reinterpret_cast<Algorithm*>(&input);  //gAlgorithmStore.getAlgorithm(input.name());
      gAlgorithmStore.head = head;
    } else {
      Algorithm* tmp = head;
      while ( tmp->next != nullptr ) {
        tmp = tmp->next;
      }
      tmp->next = gAlgorithmStore.getAlgorithm(input.name());
    }
    printAlgorithmSequence();
    addAlgorithm(inputs...);
  }

  template<class IN>
  void addAlgorithm(IN input)
  {
    gAlgorithmStore.addToStore(input);
    if ( head == nullptr ) {
      std::cout << "here" << std::endl;
      head = reinterpret_cast<Algorithm*>(&input);  //gAlgorithmStore.getAlgorithm(input.name());
      gAlgorithmStore.head = head;
    } else {
      Algorithm* tmp = head;
      while ( tmp->next != nullptr ) {
        tmp = tmp->next;
      }
      tmp->next = gAlgorithmStore.getAlgorithm(input.name());
    }

    printAlgorithmSequence();
    return;
  }

  void printAlgorithmSequence()
  {
    std::cout << "Algorithm sequence:" << std::endl; 
    Algorithm* tmp = gAlgorithmStore.head;
    while ( tmp != nullptr ) {
      std::cout << tmp->name() << "," << std::endl;
      tmp = tmp->next;
    }
    return;
  }
  
  AlgorithmStore gAlgorithmStore;
  Algorithm* head;
};

#endif