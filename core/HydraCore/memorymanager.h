#ifndef TOYGEN_MEMORYMANAGER_H
#define TOYGEN_MEMORYMANAGER_H

#include <cstddef>
#include <map>
#include <thread>
#include <new>

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
  moodycamel::ConcurrentQueue<T*> m_queue;

public:
  MemoryManager() = default;
  ~MemoryManager() {}

  inline void expandPool()
  {
    // TODO: Fix bug that won't allow bulk allocation.
    try {
    T* n = ::new T();
    m_queue.enqueue( n );
    } catch (std::bad_alloc& badAlloc) {
      FATAL("Not enough memory: " << badAlloc.what());
    }
  }

  // Add overlaods for arrays.

  inline void* allocate(size_t size)
  {
    T* free;
    bool success = m_queue.try_dequeue( free );
    if ( !success ) {
      expandPool();
      return allocate( size );
    }
    return free;
  }

  inline void free(void* deleted)
  {
    // Pass memory to back of queue.
    m_queue.enqueue( reinterpret_cast<T*>( deleted ) );
  }
};

#endif