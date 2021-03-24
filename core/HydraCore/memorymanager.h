#ifndef TOYGEN_MEMORYMANAGER_H
#define TOYGEN_MEMORYMANAGER_H

#include <cstddef>
#include <map>
#include <thread>
#include <new>
#include <mutex>

#include "msgservice.h"
#include "concurrentqueue.h"

#define POOLSIZE 32

class IMemoryManager
{
public:
  IMemoryManager() = default;
  virtual ~IMemoryManager() {}

  virtual void* allocate(size_t) = 0;
  virtual void  free(void*) = 0;
};

template<class T>
class MemoryManager : public IMemoryManager
{
private:
  /**
   * Use ConcuuretnQueue as the memory pool.
   * This has the advantage of being able to be accessed by any thread at any time with no locks.
   * The principle is to store the memory in the queue and then release it when it is needed.
   * When the pbject is destroyed, the memory is returned to the queue.
   */
  moodycamel::ConcurrentQueue<T*> m_pool;

public:
  MemoryManager() = default;
  ~MemoryManager() {}


  // Assign enough memory for
  void expandPool()
  {
    //T** t = reinterpret_cast<T**>( new char[1500*sizeof(T)] );
    //bool success = m_pool.enqueue_bulk(t,1500);
    T* t = ::new T();
    bool success = m_pool.enqueue( t );
    if ( !success ) {
      FATAL("Not enough memory!");
    }
    return;
  }

  inline void* allocate(size_t size)
  {

    T* free;
    // Check if enough memory exists.
    bool available = m_pool.try_dequeue( free );
    // If there is no memory left in the queue then expand the queue and retry.
    if ( !available ) {
      expandPool();
      // Try again.
      INFO("Looking for more memory");
      allocate(size);
    }

    return free;
  }

  inline void* allocate_array(size_t size)
  {
    T* free;
    bool available = m_pool.try_dequeue_bulk( free , size/sizeof(T*) );
    // If there is no memory left in the queue then expand the queue and retry.
    if ( !available ) {
      expandPool();
      allocate(size);
    }
    return free;
  }

  inline void free(void* deleted)
  {
    m_pool.enqueue( reinterpret_cast<T*>( deleted ) );
  }
};

#endif