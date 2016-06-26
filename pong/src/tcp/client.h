#ifndef _CLIENT_H
#define _CLIENT_H

class Client {

 private:
  int port;
  const char* ip;

 public:
  Client(int port, const char* ip);

};

#endif
