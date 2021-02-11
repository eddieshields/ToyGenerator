#ifndef TOYGEN_THREADS_H
#define TOYGEN_THREADS_H

#include "threadpool.h"
#include "msgservice.h"
#include "event.h"

#include <thread>
#include <pthread.h>
#include <vector>
#include <future>
#include <memory>

#include "TROOT.h"

/** \class Threads
 * 
 *  Takes a function in and distributes the task to a threapool.
 *  Gets return from functions in threads and places them into 
 *  a vector that gets returned.
 * 
 *  @author Edward Shields
 *  @dat 09/02/2021
 */
class Threads 
{
public:
  Threads(int& nthreads,int& nevents) :
    m_nthreads( nthreads ),
    m_pool( nthreads )
  {
    m_list.reserve( nevents );
    ROOT::EnableImplicitMT(nthreads);
  }
  ~Threads() {};

  template<class F, class... Args>
  auto operator()(F&& f, Args&&... args) -> typename std::result_of<F(Args...)>::type
  {
    INFO("Submitting tasks to Thread pool");
    // Need to generalise this class for template output.
    std::vector<std::future<std::vector<Event>>> thread_futures;
    for (int i = 0; i < m_nthreads; i++) {
      std::future<std::vector<Event>> out = m_pool.submit(f,args...);
      thread_futures.push_back( std::move( out ) );
    }
    for (int i = 0; i < m_nthreads; i++) {
      std::vector<Event> tmp = thread_futures[i].get();
      m_list.insert(m_list.end(),tmp.begin(),tmp.end());
    }
    return m_list;
  }

  std::vector<Event> list() { return m_list; }
private:
  ThreadPool         m_pool;
  const int          m_nthreads;
  std::vector<Event> m_list;
};

#endif