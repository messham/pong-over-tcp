#ifndef __test_wqclass_h__
#define __test_wqclass_h__

#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>

using namespace std;

template <typename T> class wqclass
{
private:
  list<T> m_queue;
  mutex  m_mutex;
  condition_variable m_condv; 

public:
  wqclass(){}
  ~wqclass(){}

  //   wqclass& operator= (const wqclass& o) {
  //   if (this != &o)
  //     {
  //       std::lock(m_mutex, o.m_mutex);
  //       std::lock_guard<std::mutex> lhs_lk(m_mutex, std::adopt_lock);
  //       std::lock_guard<std::mutex> rhs_lk(o.m_mutex, std::adopt_lock);
  //       m_queue = o.m_queue;
  //       m_condv = o.m_condv;
  //     }
  //   return *this;
  // }
};

#endif
