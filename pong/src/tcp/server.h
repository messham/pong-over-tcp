#ifndef _SERVER_H
#define _SERVER_H
#include <thread>
class Server {

 private:
  int port;
  const char* ip;
  std::thread thread_;
  void runServer();
  bool isRunning;

 public:
  Server(int port, const char* ip);
  ~Server();
  void start();
  void stop();
};

#endif
