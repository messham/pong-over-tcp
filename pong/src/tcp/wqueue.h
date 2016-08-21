/*
  wqueue.h

  Worker thread queue based on the Standard C++ library list
  template class.

  ------------------------------------------

  Copyright @ 2013 [Vic Hargrave - http://vichargrave.com]
  Modified work Copyright 2016 JM Messham

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/

// code adapted to use c++11 thread, mutex, cv

#ifndef __wqueue_h__
#define __wqueue_h__

#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>

using namespace std;

class WorkItem {
    TCPStream* m_stream;
 
  public:
    WorkItem(TCPStream* stream) : m_stream(stream) {}
    ~WorkItem() { delete m_stream; }
 
    TCPStream* getStream() { return m_stream; }
};

template <typename T> class wqueue
{
private:
  list<T> m_queue;
  mutex  m_mutex;
  condition_variable m_condv; 

public:
  wqueue() {}
  
  ~wqueue() {}
  
  wqueue(wqueue&& o) = default;
  
  void add(T item) {
    m_mutex.lock();
    m_queue.push_back(item);
    m_condv.notify_one();
    m_mutex.unlock();
  }
  
  T remove() {
    unique_lock<mutex> lk(m_mutex);
    m_mutex.lock();
    while (m_queue.size() == 0) {
      m_condv.wait(lk);
    }
    T item = m_queue.front();
    m_queue.pop_front();
    m_mutex.unlock();
    return item;
  }
  
  int size() {
    m_mutex.lock();
    int size = m_queue.size();
    m_mutex.unlock();
    return size;
  }

  /* wqueue& operator= (const wqueue& o) { */
  /*   if (this != &o) */
  /*     { */
  /*       std::lock(m_mutex, o.m_mutex); */
  /*       std::lock_guard<std::mutex> lhs_lk(m_mutex, std::adopt_lock); */
  /*       std::lock_guard<std::mutex> rhs_lk(o.m_mutex, std::adopt_lock); */
  /*       field1 = o.field1; */
  /*       field2 = o.field2; */
  /*     } */
  /*   return *this; */
  /* } */
};

#endif
