#ifndef _SERVER_H
#define _SERVER_H
#include "tcpstream.h"
#include "wqueue.h"
#include <queue>
#include <thread>
#include <vector>
#include <mutex>

struct thread_data
{
  int id;
  TCPStream* stream;  
  std::thread t;
};

struct player_coord
{
  int id;
  int coord;
};

class Server {

 private:
  int port;
  const char* ip;
  std::vector<TCPStream*> connections;
  std::thread tAcceptConnections;
  struct thread_data playerThreads[2];
  // std::thread tPlayer1;
  // std::thread tPlayer2;
  std::thread tSendMovements;
  mutex m_mutex;
  wqueue<struct player_coord*>* qPlayerCoords;    
  void acceptConnections();
  void assignId(TCPStream* stream, int workerId);
  void handleConnection(wqueue<WorkItem*>& queue, struct thread_data& td);
  void addConnection(TCPStream* stream);
  void removeConnection(TCPStream* stream);
  void receiveMovements(TCPStream* stream, int workerId);
  void sendMovements(/*something*/);
  bool isRunning;

 public:
  Server(int port, const char* ip);
  ~Server();
  void start();
  void stop();
};

#endif
