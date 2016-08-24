#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include <mutex>
#include "../src/tcp/client.cpp" 
#include "../src/tcp/tcpacceptor.cpp"
#include "../src/tcp/server.cpp" 
#include "../src/tcp/tcpstream.cpp"
#include "../src/tcp/tcpconnector.cpp"


#include "test_wqclass.h"

#include <iostream>
//using namespace std;

class myClass {

  int ip = 8000;
  const char* port = "localhost";
  wqueue<WorkItem*> queue;
  
public:
  myClass() {};
  ~myClass() {};
  void qAcceptConnections(wqueue<WorkItem*>& queue);
  void qHandleConnection(wqueue<WorkItem*>& queue);
  void qClient();    
  void startThreads();
};

void myClass::qAcceptConnections(wqueue<WorkItem*>& queue) {
  WorkItem* item;
  TCPAcceptor* acceptor = new TCPAcceptor(ip);
  if (acceptor->start() == 0) {
    while (1) {
      TCPStream* stream = acceptor->accept(); // blocks this thread until new connection
      // printf("A client has connected");
      item = new WorkItem(stream);
      queue.add(item);
    }
  }
}

void myClass::qHandleConnection(wqueue<WorkItem*>& queue) {
  for (;;) {
    WorkItem* item = queue.remove();
    printf("Received connection from ip\n");
    TCPStream* stream = item->getStream();
    while (true) {
      int recv;
      ssize_t len;
      while ((len = stream->receive((char*)&recv, sizeof(recv))) > 0 ){
	int coord = ntohl(recv);
	stream->send((const char*) &coord, sizeof(int));
	printf("some thread, echoed '%d' back to the client\n", coord);    		
      }
    }
  }
}

void myClass::qClient() {
  Client* p1 = new Client(ip, port);
  p1->sendCoords(11);
}

void myClass::startThreads() {

  // wqclass<int*> wq;

  std::thread t1(&myClass::qAcceptConnections, this, std::ref(queue));    
  std::thread t2(&myClass::qHandleConnection, this, std::ref(queue));
  std::thread t3(&myClass::qHandleConnection, this, std::ref(queue));
  std::thread t4(&myClass::qHandleConnection, this, std::ref(queue));    
  std::thread t5(&myClass::qClient, this);  
  std::thread t6(&myClass::qClient, this);

  sleep(5);

  std::thread t7(&myClass::qClient, this);   
  
  
  // std::thread t1(&myClass::someThreadFunction, this, &queue);
  // std::thread t2(&myClass::someThreadFunction, this, &queue);
  // std::thread t1(&myClass::someThreadFunction, this, std::ref(wq));
  // std::thread t2(&myClass::someThreadFunction, this, std::ref(wq));
  
  //sleep(10);
  //item = 1;
  //queue.add(item);
  t1.join();
    cout << "havent' joined shit\n" << endl;
  t2.join();
  t3.join();
  t4.join();
  t5.join();
}

int main() {
  myClass c;
  c.startThreads();
  return 0;
}
