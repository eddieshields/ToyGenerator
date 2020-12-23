#include "configuration.h"

/*
template <class IN, class... IN_TYPES>
void Configuration::addAlgorithm(IN input, IN_TYPES... inputs)
{
  if ( head == nullptr ) {
    //head = reinterpret_cast<Algorithm*>(input);
    head = reinterpret_cast<Algorithm*>(&input);
  } else {
    Algorithm* tmp = head;
    while ( tmp->next != nullptr ) {
      tmp = tmp->next;
    }
    tmp->next = reinterpret_cast<Algorithm*>(&input);
  }

  addAlgorithm(inputs...);
}

template<class IN>
void Configuration::addAlgorithm(IN input)
{
  if ( head == nullptr ) {
    head = reinterpret_cast<Algorithm*>(&input);
  } else {
    Algorithm* tmp = head;
    while ( tmp->next != nullptr ) {
      tmp = tmp->next;
    }
    tmp->next = reinterpret_cast<Algorithm*>(&input);
  }
}
*/