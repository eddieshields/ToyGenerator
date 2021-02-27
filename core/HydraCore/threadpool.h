#ifndef TOYGEN_THREADPOOL_H
#define TOYGEN_THREADPOOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <map>

#include "msgservice.h"
#include "random.h"
#include "event.h"

/** ThreadPool holds a pool of threads and excutes jobs in threads.
 * 
 * When a task is submitted to the ThreadPool one of the waiting threads 
 * takes up the task and performs it. If no threads are available the task 
 * will be added to a queue until a task becomes available.
 * 
 * @author Edward Shields
 * @date   12/02/2021
 */
class ThreadPool 
{
public:
  /** Constructor creates the pool of threads. */
  ThreadPool(size_t threads = 0);
  /** Destructor. */
  ~ThreadPool();

  /** Submit a job, then retrieve its return from a future later. */
  template<class F, class... Args>
  auto submit(F&& f, Args&&... args) 
    -> std::future<typename std::result_of<F(Args...)>::type>;
  /** Add a job to the queue then wait for it's return. */
  template<class F, class... Args>
  auto enqueue(F&& f, Args&&... args) 
    -> typename std::result_of<F(Args...)>::type;
  /** Wrap a critical task to make sure there is no conflicts between threads. */    
  template<class F, class... Args>
  auto critical(F&& f, Args&&... args) 
    -> typename std::result_of<F(Args...)>::type;

  /** Static method that returns how many threads are in existance. */
  static int nthreads();

  /** Returns the ID of the current thread. */
  inline static int ThreadID();

private:
  /** Container of threads. */
  static std::vector< std::thread > workers;
  /** Queue for tasks. */
  static std::queue< std::function<void()> > tasks;
  
  /** Queue mutex. */
  static std::mutex queue_mutex;
  /** Runtime mutex. */
  static std::mutex runtime_mutex;
  /** Condition for threads. */
  static std::condition_variable condition;
  /** Stop adding jobs to queue. */
  static bool stop;

  /** Number of threads created. */
  static int _nthreads;

  /** Map between threads and their IDs. */
  static std::map<std::thread::id,int> ids;
};

template<class F, class... Args>
auto ThreadPool::submit(F&& f, Args&&... args) 
  -> std::future<typename std::result_of<F(Args...)>::type>
{
  using return_type = typename std::result_of<F(Args...)>::type;

  auto task = std::make_shared< std::packaged_task<return_type()> >(
    std::bind(std::forward<F>(f), std::forward<Args>(args)...)
  );
        
  std::future<return_type> res = task->get_future();
  {
    std::unique_lock<std::mutex> lock(queue_mutex);  
    
    // don't allow enqueueing after stopping the pool
    if(stop)
      throw std::runtime_error("enqueue on stopped ThreadPool");  
    tasks.emplace([task](){ (*task)(); });
  }
  condition.notify_one();
  return res;
}

// add new work item to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) 
    -> typename std::result_of<F(Args...)>::type
{
  using return_type = typename std::result_of<F(Args...)>::type;

  auto task = std::make_shared< std::packaged_task<return_type()> >(
    std::bind(std::forward<F>(f), std::forward<Args>(args)...)
  );
        
  std::future<return_type> res = task->get_future();
  {
    std::unique_lock<std::mutex> lock(queue_mutex);  
    
    // don't allow enqueueing after stopping the pool
    if(stop)
      throw std::runtime_error("enqueue on stopped ThreadPool");  
    tasks.emplace([task](){ (*task)(); });
  }
  condition.notify_one();
  return res.get();
}

// add new work item to the pool
template<class F, class... Args>
auto ThreadPool::critical(F&& f, Args&&... args) 
    -> typename std::result_of<F(Args...)>::type
{
  std::unique_lock<std::mutex> lock(runtime_mutex);
  return f(args...);
}

#endif