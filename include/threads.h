#ifndef TOYGEN_THREADS_H
#define TOYGEN_THREADS_H

#include "msgservice.h"
#include "event.h"
#include "threadpool.h"

#include <thread>
#include <pthread.h>
#include <vector>
#include <future>

#include "TROOT.h"

template<typename FUNC>
class Threads 
{
public:
  Threads(FUNC& function,int& nthreads,int& nevents) :
    m_function(function),
    m_nthreads( nthreads ),
    m_pool( nthreads )
  {
    m_list.reserve( nevents );
    ROOT::EnableImplicitMT(nthreads);
  }
  ~Threads() {};

  void operator()()
  {
    //m_function();
    /*
    for (int i = 0; i < m_nthreads; i++) {
      std::future<std::vector<Event>> t = m_pool.submit(m_function,i);
      m_threads.push_back( std::move(t) );
    }

    for (int i = 0; i < m_nthreads; i++) {
      std::vector<Event> tmp = m_threads[i].get();
    }
    */
    return;
  }

  std::vector<Event> list() { return m_list; }
private:
  ThreadPool                                   m_pool;
  FUNC&                                        m_function;
  const int                                    m_nthreads;
  std::atomic<bool>                            m_complete;
  std::vector<std::future<std::vector<Event>>> m_threads;
  std::vector<Event>                           m_list;
};

#endif