#ifndef DALITZMODEL_CLOCK_H
#define DALITZMODEL_CLOCK_H

// DalitzModel.
#include "colours.h"

// STL.
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ctime>

namespace DalitzModel {

using clock_r = std::chrono::time_point<std::chrono::high_resolution_clock>;

/** @brief Clock.
 * 
 * Class to help with timings. Simply call Start() to start the clock and then stop 
 * to stop the clock. Will then print CPU time and real time.
 * 
 * @author Edward Shields
 * @date   22/01/2021
 */
class Clock
{
private:
  static std::clock_t c_start;   
  static std::clock_t c_end;
  static clock_r      t_start;
  static clock_r      t_end;

public:
  /** Start the clock */
  static void Start();
  /** Stop the clock */
  static void Stop();
  /** Print timings.
   * 
   * \param task task that was completed. Will print "Time to task:" then timings. */
  static void Print(std::string task);

};

}  // namespace DalitzModel

#endif