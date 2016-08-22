#ifndef _SERVER_H
#define _SERVER_H
#include "tcpstream.h"
#include "wqueue.h"
#include <thread>
#include <vector>

class Server {

 private:
  int port;
  const char* ip;
  std::thread tAccept;
  std::thread tPlayer1;
  std::thread tPlayer2;
  std::vector<TCPStream*> clients;
  void acceptConnections();
  void handleConnection(wqueue<WorkItem*>& queue);  
  bool isRunning;

 public:
  Server(int port, const char* ip);
  ~Server();
  void start();
  void stop();
};

#endif
