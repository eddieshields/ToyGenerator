#ifndef TOYGEN_THREADS_H
#define TOYGEN_THREADS_H

#include "msgservice.h"

#include<thread>
#include <pthread.h>
#include <vector>

class Threads 
{
public:
  template<typename FUNC, typename... IN_TYPES>
  Threads(FUNC& function,int& nthreads)
  {
    INFO("Will use "+std::to_string(nthreads)+" threads");
    for (int i = 0; i < nthreads; i++) {
      std::thread t(function);
      m_threads.push_back(std::move(t));
    }
    for (auto &th : m_threads) {
      th.join();
    }
  }
  ~Threads() {};

private:
  std::atomic<bool>        m_complete;
  std::vector<std::thread> m_threads;
};

#endif