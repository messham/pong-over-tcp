#ifndef _CLIENT_H
#define _CLIENT_H

#include "tcpconnector.h"
#include <thread>

class Client {

 private:
  int id;
  int port;
  const char* ip;
  TCPConnector* connector;
  TCPStream* stream;
  int receiveId();
  // std::thread tReceiver;
  // void startReceiving();
  // void stopReceiving();
  
 public:
  Client(int port, const char* ip);
  ~Client();
  int getId();
  void sendCoords(int x);
  struct player_coord receiveCoords();

};

#endif
