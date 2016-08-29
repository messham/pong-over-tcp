#ifndef _SERVER_H
#define _SERVER_H
#include "tcpstream.h"
#include "wqueue.h"
#include <queue>
#include <thread>
#include <vector>

struct player_coord
{
  int id;
  int coord;
};

struct worker_thread
{
  int id;
  std::thread t;  
};

class Server {

 private:
  int port;
  const char* ip;
  std::queue<int> ids;
  std::thread tAccept;
  // struct worker_thread tPlayer1;
  // struct worker_thread tPlayer2;
  std::thread tPlayer1;
  std::thread tPlayer2;
  wqueue<int*> qPlayerCoords;    
  void acceptConnections();
  void assignId(TCPStream* stream, int workerId);
  void handleConnection(wqueue<WorkItem*>& queue, int workerId);
  bool isRunning;

 public:
  Server(int port, const char* ip);
  ~Server();
  void start();
  void stop();
};

#endif
