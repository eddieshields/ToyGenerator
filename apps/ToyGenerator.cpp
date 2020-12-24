#include "event.h"
#include "generator.h"
#include "efficiency.h"
#include "amplitude.h"
#include "sequence.h"
#include "algorithm.h"

#include <iostream>

int main()
{

  Event ev;
  Generator gen("Generator",1.9,0.4,0.4,0.5);
  Efficiency eff("Efficiency");
  Efficiency eff1("Efficiency1");
  Efficiency eff2("Efficiency2");
  Efficiency eff3("Efficiency3");
  Amplitude amp("Amplitude");

  Sequence flow(eff,eff1,eff2,amp,eff3);

  Algorithm* head = flow.head;
  head->operator()(ev);
  /*
  while ( head != nullptr ) {
      head->operator()(ev);
  }
  */
  std::cout << "Pdf = " << ev.pdf << std::endl;
  return 0;
}