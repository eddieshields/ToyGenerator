#include "threadpool.h"

std::vector< std::thread>           ThreadPool::workers       = std::vector<std::thread>();

std::queue< std::function<void()> > ThreadPool::tasks         = std::queue< std::function<void()> >();

std::mutex                          ThreadPool::queue_mutex   = std::mutex();

std::mutex                          ThreadPool::runtime_mutex = std::mutex();

std::condition_variable             ThreadPool::condition     = std::condition_variable();

bool                                ThreadPool::stop          = false;

int                                 ThreadPool::_nthreads     = 0;

std::map<std::thread::id,int>       ThreadPool::ids           = std::map<std::thread::id,int>();

// the constructor just launches some amount of workers
ThreadPool::ThreadPool(size_t threads)
{
  stop = false;
  if ( workers.size() ) {
    INFO("ThreadPool already is running");
    return;
  }
  INFO("Starting ThreadPool");
  if (!threads) { _nthreads = std::thread::hardware_concurrency(); } else { _nthreads = threads; }
  for(size_t i = 0;i<_nthreads;++i) {
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
    ids.insert( std::pair<std::thread::id,int>{ workers.back().get_id() , workers.size()-1} );
    Random::addThread( workers.back().get_id() , i );
    gEventMemoryManager.addThread( workers.back().get_id() );
  }
}

// the destructor joins all threads
ThreadPool::~ThreadPool()
{
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    stop = true;
  }
  condition.notify_all();
  for(std::thread &worker: workers) {
    ids.erase( worker.get_id() );
    Random::removeThread( worker.get_id() );
    worker.join();
  }

  workers.clear();
  ids.clear();
}


int ThreadPool::ThreadID()
{
  return ids.find( std::this_thread::get_id() )->second;
}

int ThreadPool::nthreads()
{
  return _nthreads;
}
