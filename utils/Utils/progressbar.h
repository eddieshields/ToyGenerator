#ifndef TOYGEN_PROGRESSBAR_H
#define TOYGEN_PROGRESSBAR_H

#include <iostream>
#include <string>
#include <stdexcept>
#include <mutex>

class ProgressBar
{
private:
  int m_max = {100};
  int m_counter = {0};
  int m_barWidth = {70};

  float m_last_progress = {0.};
  int m_last_pos = {0};

  std::mutex m_mutex;
public:
  ProgressBar() = default;
  ProgressBar(const int& max) :
    m_max( max )
  {}
  ~ProgressBar() {}

  inline void setMax(const int& max) { m_max = max; }

  inline void operator++() 
  { 
    // Update counter.
    ++m_counter;
    // Calculate progress and position in bar.
    float progress = (float)m_counter / (float)m_max;
    int pos = m_barWidth * progress;

    if ( pos > m_last_pos || int(progress*100.0) > int(m_last_progress*100.0) ) {
      if ( pos < m_barWidth ) std::cout << "\r[" << std::string(pos,'=') << ">" << std::string(m_barWidth-pos-1,' ') << "] " << int(progress * 100.0) << "% ";
      else std::cout << "\r[" << std::string(pos,'=') << "] " << int(progress * 100.0) << "% ";
      std::cout.flush();
    }
    
    // Update previos positions.
    m_last_pos = pos;
    m_last_progress = progress;

    // New line if reached end.
    if ( progress == (float)1. ) std::cout << std::endl;
    return;
  }

  inline void update()
  { 
    // Update counter.
    ++m_counter;
    // Calculate progress and position in bar.
    float progress = (float)m_counter / (float)m_max;
    int pos = m_barWidth * progress;

    if ( pos > m_last_pos || int(progress*100.0) > int(m_last_progress*100.0) ) {
      if ( pos < m_barWidth ) std::cout << "\r[" << std::string(pos,'=') << ">" << std::string(m_barWidth-pos-1,' ') << "] " << int(progress * 100.0) << "% ";
      else std::cout << "\r[" << std::string(pos,'=') << "] " << int(progress * 100.0) << "% ";
      std::cout.flush();
    }
    
    // Update previos positions.
    m_last_pos = pos;
    m_last_progress = progress;

    // New line if reached end.
    if ( progress == (float)1. ) std::cout << std::endl;
    return;
  }

  inline void critical_update()
  {
    // Put lock around update function.
    m_mutex.lock();
    update();
    m_mutex.unlock();
    return;
  }

};

#endif