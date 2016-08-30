/*
  wqueue.h

  Worker thread queue based Vic Hargrave's work adapted to utilize
  c++11 thread, mutex, and condition_variable

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
  condition_variable cvIsEmpty;
  condition_variable cvIsFull;
  int numElements;
  // note: unique_lock releases lock when it (lk) is destroyed (no need to call unlock)
  
public:

  wqueue(int numElements) {
    this->numElements = numElements;
  }
  
  ~wqueue() {}
  
  wqueue(wqueue&& o) = default;
  
  void add(T item) {
    unique_lock<mutex> lk(m_mutex);
    while (m_queue.size() == numElements) {
      cvIsFull.wait(lk);
    }
    m_queue.push_back(item);
    cvIsEmpty.notify_one();
  }
  
  T remove() {
    unique_lock<mutex> lk(m_mutex);
    while (m_queue.size() == 0) {
      cvIsEmpty.wait(lk);
    }
    T item = m_queue.front();
    m_queue.pop_front();
    cvIsFull.notify_one();
    return item;
  }
  
  int size() {
    unique_lock<mutex> lk(m_mutex);
    int size = m_queue.size();
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
