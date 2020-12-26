#ifndef TOYGEN_CLOCK_H
#define TOYGEN_CLOCK_H

// Package.
#include "msgservice.h"

// SL.
#include <iostream>
#include <string>

// ROOT.
#include "TStopwatch.h"


class Clock
{
public:
  /** Start the clock. */
  static void Start() { m_clock->Reset(); m_clock->Start(); }
  /** Stop the clock. */
  static void Stop()  { m_clock->Stop();  }
  /** Reset the clock. */
  static void Reset() { m_clock->Reset(); }

  /** Print " Time to \param:". */
  static void Print(std::string task = "") {
    INFO("Time to "+task+":");
    INFO("Real time = "+std::to_string(m_clock->RealTime()));
    INFO("CPU time = "+std::to_string(m_clock->CpuTime()));
    /*
    if ( task != "" ) std::cout << "Time to " << task << std::endl;
    std::cout << "Real time = " << m_clock->RealTime() << std::endl;
    std::cout << "Cpu time =  " << m_clock->CpuTime()  << std::endl;
    */
  }

private:
  static TStopwatch* m_clock;
};

#endif