#ifndef TOYGEN_ACCEPT_H
#define TOYGEN_ACCEPT_H

#include "event.h"
#include "algorithm.h"
#include "random.h"
#include "types.h"

class Accept : public Algorithm
{
public:
  Accept(std::string name) : Algorithm(name) {}
  ~Accept() {}

  void operator() (Event& ev) override final;

  void setMaxPdf(const real_t maxPdf) { m_maxPdf = maxPdf; }

private:
  real_t m_maxPdf = {1.};
};

#endif