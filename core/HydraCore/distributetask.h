#ifndef TOYGEN_DISTRIBUTETASK_H
#define TOYGEN_DISTRIBUTETASK_H

#include "threadpool.h"
#include "msgservice.h"
#include "event.h"

#include <thread>
#include <pthread.h>
#include <vector>
#include <future>
#include <memory>

#include "TROOT.h"

/** \class DistributeTask
 * 
 *  Takes a function in and distributes the task to a threapool.
 *  Gets return from functions in threads and places them into 
 *  a vector that gets returned.
 * 
 *  @author Edward Shields
 *  @date 12/02/2021
 */
class DistributeTask 
{
public:
  DistributeTask() : 
    m_pool( std::thread::hardware_concurrency() ),
    m_nthreads( std::thread::hardware_concurrency() )
  {}
  DistributeTask(int& nthreads) :
    m_pool( nthreads ),
    m_nthreads( nthreads )
  {
    //m_list.reserve( nevents );
    ROOT::EnableImplicitMT(nthreads);
  }
  ~DistributeTask() {};

  template<class F, class... Args>
  void submit(F&& f, Args&&... args)
  {
    INFO("Submitting tasks to Thread pool");
    std::vector<std::future<void>> thread_futures;
    for (int i = 0; i < m_nthreads; i++) {
      auto out = m_pool.submit(f,args...);
      thread_futures.push_back( std::move( out ) );
    }
  }

  void get()
  {
    //for (int i = 0; i < m_nthreads; i++) {
    //  thread_futures[i].get();
    //}
  }

private:
  ThreadPool         m_pool;
  const int          m_nthreads;
};

#endif