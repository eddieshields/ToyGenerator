#ifndef TOYGEN_THREADS_H
#define TOYGEN_THREADS_H

#include "msgservice.h"
#include "event.h"

#include <thread>
#include <pthread.h>
#include <vector>
#include <future>

#include "TROOT.h"

#ifdef _OPENMP
  #include <omp.h>
#endif

template<typename FUNC>
class Threads 
{
public:
  Threads(FUNC& function,int& nthreads,int& nevents) :
    m_function(function),
    m_nthreads( nthreads )
  {
    m_list.reserve( nevents );
    ROOT::EnableImplicitMT(nthreads);
  }
  ~Threads() {};

  void operator()()
  {
    #ifdef _OPENMP
      omp_set_num_threads(m_nthreads);
      #pragma omp parallel for
      for (int i = 0; i < m_nthreads; i++) {
        int thread = omp_get_thread_num();
        std::vector<Event> tmp = m_function(thread);
      }
    #else
      if ( m_nthreads > 1 ) {
        for (int i = 0; i < m_nthreads; i++) {
          std::future<std::vector<Event>> t = std::async(std::launch::async,m_function,i);
          m_threads.push_back( std::move(t) );
        }
    
        for (int i = 0; i < m_nthreads; i++) {
          std::vector<Event> tmp = m_threads[i].get();
        }
      } else {
        std::vector<Event> tmp = m_function(0);
      }
    #endif
    return;
  }

  std::vector<Event> list() { return m_list; }
private:
  FUNC&                                        m_function;
  const int                                    m_nthreads;
  std::atomic<bool>                            m_complete;
  std::vector<std::future<std::vector<Event>>> m_threads;
  std::vector<Event>                           m_list;
};

#endif