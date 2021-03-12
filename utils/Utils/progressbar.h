#ifndef TOYGEN_PROGRESSBAR_H
#define TOYGEN_PROGRESSBAR_H

#include "colours.h"
#include "types.h"

#include <iostream>
#include <chrono>

class ProgressBar
{
private:
  int m_max;
  int m_counter = {0};
  int m_barWidth = {70};

public:
  ProgressBar()
  {
    std::system("setterm -cursor off");   
  }
  ProgressBar(const int& max) :
    m_max( max )
  {
    std::system("setterm -cursor off");
  }
  ~ProgressBar()
  {
    system("setterm -cursor on");
  }

  inline void setMax(const int& max) { m_max = max; }

  inline void operator++() 
  { 
    ++m_counter;
    real_t progress = (real_t)m_counter / (real_t)m_max;

    std::cout << "[";
    int pos = m_barWidth * progress;
    for (int i = 0; i < m_barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << "% \r";
    std::cout.flush();

    if ( progress == (real_t)1. ) std::cout << std::endl;
  }

  inline void update(const int& counter)
  {
    real_t progress = (real_t)m_counter / (real_t)m_max;

    std::cout << "[";
    int pos = m_barWidth * progress;
    for (int i = 0; i < m_barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << "% \r";
    std::cout.flush();

    if ( progress == (real_t)1. ) std::cout << std::endl;
  }

  inline void update()
  {
    real_t progress = (real_t)m_counter / (real_t)m_max;

    std::cout << "[";
    int pos = m_barWidth * progress;
    for (int i = 0; i < m_barWidth; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << "% \r";
    std::cout.flush();

    if ( progress == (real_t)1. ) std::cout << std::endl;
  }

};

#endif