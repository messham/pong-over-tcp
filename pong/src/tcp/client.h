#ifndef _CLIENT_H
#define _CLIENT_H

#include "tcpconnector.h"
#include <thread>

class Client {

 private:
  int port;
  const char* ip;
  TCPConnector* connector;
  TCPStream* stream;

 public:
  Client(int port, const char* ip);
  ~Client();

};

#endif
