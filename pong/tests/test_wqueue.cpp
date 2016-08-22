#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include "../src/tcp/server.h"
#include "../src/tcp/wqueue.h"
#include "../src/tcp/tcpacceptor.h"

#include "test_wqclass.h"

#include <iostream>
using namespace std;

class myClass {
public:
  myClass() {};
  ~myClass() {};
  // void someThreadFunction(wqueue<WorkItem*>& queue);
  void qRemove(wqueue<int*>& queue);
  void qAdd(wqueue<int*>& queue, int* i);    
  void startThread();
};

void myClass::qRemove(wqueue<int*>& queue) {
  cout << *(queue.remove()) << endl;
}

void myClass::qAdd(wqueue<int*>& queue, int* i) {
  queue.add(i);
}

void myClass::startThread() {
  int item;
  wqueue<int*> queue;

  wqclass<int*> wq;
  
  int* foo;
  foo = new int[2];
  foo[0] = 1;
  foo[2] = 2;

  
  std::thread t1(&myClass::qAdd, this, std::ref(queue), foo);
  std::thread t2(&myClass::qRemove, this, std::ref(queue));
  // std::thread t1(&myClass::someThreadFunction, this, &queue);
  // std::thread t2(&myClass::someThreadFunction, this, &queue);
  // std::thread t1(&myClass::someThreadFunction, this, std::ref(wq));
  // std::thread t2(&myClass::someThreadFunction, this, std::ref(wq));  
  
  //sleep(10);
  //item = 1;
  //queue.add(item);
  t1.join();
  t2.join();
}

int main() {
  myClass c;
  c.startThread();
  return 0;
}
