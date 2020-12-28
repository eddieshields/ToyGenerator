#ifndef TOYGEN_ACCEPT_H
#define TOYGEN_ACCEPT_H

#include "event.h"
#include "algorithm.h"
#include "random.h"

class Accept : public Algorithm
{
public:
  Accept(std::string name) : Algorithm(name) {}
  ~Accept() {}

  virtual void operator() (Event& ev);

  void setMaxPdf(const double maxPdf) { m_maxPdf = maxPdf; }

private:
  double m_maxPdf = {1.};
};

#endif