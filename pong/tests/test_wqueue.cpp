#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include "../src/tcp/server.h"
#include "../src/tcp/wqueue.h"
#include "../src/tcp/tcpacceptor.h"

#include <iostream>
using namespace std;

class myClass {
public:
  myClass() {};
  ~myClass() {};
  // void someThreadFunction(wqueue<WorkItem*>& queue);
  void someThreadFunction(int* i);  
  void startThread();
};

// void myClass::someThreadFunction(wqueue<WorkItem*>& queue) {
//   cout << queue.remove() << endl;
// }

void myClass::someThreadFunction(int* queue) {
  cout << queue[0] << endl;
}

void myClass::startThread() {
  int item;
  wqueue<int*> queue;
  int* foo;
  foo = new int[2];
  foo[0] = 1;
  foo[2] = 2;
  // std::thread t1(&myClass::someThreadFunction, this, std::ref(queue));
  // std::thread t2(&myClass::someThreadFunction, this, std::ref(queue));
  // std::thread t1(&myClass::someThreadFunction, this, &queue);
  // std::thread t2(&myClass::someThreadFunction, this, &queue);
  std::thread t1(&myClass::someThreadFunction, this, foo);
  std::thread t2(&myClass::someThreadFunction, this, foo);  
  
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
