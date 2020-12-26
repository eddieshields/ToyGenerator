#ifndef TOYGEN_THREADS_H
#define TOYGEN_THREADS_H

#include "msgservice.h"
#include "event.h"

#include<thread>
#include <pthread.h>
#include <vector>
#include <future>

 #include "TROOT.h"

class Threads 
{
public:
  template<typename FUNC, typename... IN_TYPES>
  Threads(FUNC& function,int& nthreads)
  {
    ROOT::EnableImplicitMT(nthreads);
    INFO("Will use "+std::to_string(nthreads)+" threads");
    for (int i = 0; i < nthreads; i++) {
      std::future<std::vector<Event>> t = std::async(std::launch::async,function,i);
      m_threads.push_back( std::move(t) );
    }

    for (int i = 0; i < nthreads; i++) {
      std::vector<Event> tmp = m_threads[i].get();
      for (int j = 0; j < tmp.size(); j++) {
        Event e = tmp[j];
        m_list.push_back(std::move(e));
      }
    }

  }
  ~Threads() {};

  std::vector<Event> list() { return m_list; }
private:
  std::atomic<bool>                            m_complete;
  std::vector<std::future<std::vector<Event>>> m_threads;
  std::vector<Event>                           m_list;
};

#endif