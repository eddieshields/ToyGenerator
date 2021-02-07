#include "threadpool.h"

int ThreadPool::_nthreads = 0;

std::map<std::thread::id,int> ThreadPool::ids = std::map<std::thread::id,int>();

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads)
  :   stop(false)
{
  if (!threads) { _nthreads = std::thread::hardware_concurrency(); } else { _nthreads = threads; }
  for(size_t i = 0;i<_nthreads;++i)
    workers.emplace_back(
      [this] {
        while(true)
        {
          std::function<void()> task;
          {
            std::unique_lock<std::mutex> lock(this->queue_mutex);
            this->condition.wait(lock, [this]{ return this->stop || !this->tasks.empty(); });
            if(this->stop && this->tasks.empty())
                return;
            task = std::move(this->tasks.front());
            this->tasks.pop();
          }
          task();
        }
      }
    );
  ids.insert( std::pair{ workers.back().get_id() , workers.size()-1} );
}

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

int ThreadPool::ThreadID()
{
  return ids.find( std::this_thread::get_id() )->second;
}

int ThreadPool::nthreads()
{
  return _nthreads;
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    stop = true;
  }
  condition.notify_all();
  for(std::thread &worker: workers) {
    ids.erase( worker.get_id() );
    worker.join();
  }

  workers.clear();
  ids.clear();
}
