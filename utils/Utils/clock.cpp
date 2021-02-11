#include "clock.h"

void Clock::Start()
{
  c_start = std::clock();
  t_start = std::chrono::high_resolution_clock::now();
  
}

void Clock::Stop()
{
  c_end = std::clock();
  t_end = std::chrono::high_resolution_clock::now();
}

void Clock::Print(std::string task)
{
  std::chrono::duration<double> diff = t_end - t_start;
  std::cout << GREEN << "Time to " << task << ":\n"
            << std::fixed << std::setprecision(5) << "CPU time  :"
            << " " << (float)(c_end - c_start) / CLOCKS_PER_SEC << " s\n"
            << std::fixed << std::setprecision(5) << "Real time :"
            << " " << diff.count() << " s"
            << RESET << std::endl;
}

// Initiliaze static variables.
std::clock_t Clock::c_start = std::clock();

std::clock_t Clock::c_end   = std::clock();

clock_r Clock::t_start      = std::chrono::high_resolution_clock::now();

clock_r Clock::t_end        = std::chrono::high_resolution_clock::now();