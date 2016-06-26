/*
   server.cpp

   Test server for the tcpsockets classes which handles connections
   iteratively.

   ------------------------------------------

   Original work Copyright © 2013 [Vic Hargrave - http://vichargrave.com]
   Modified work Copyright 2016 JM Messham

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <stdio.h>
#include <stdlib.h>
#include <thread>
#include "server.h"
#include "tcpacceptor.h"

void Server::runServer() {
  TCPStream* stream = NULL;
  TCPAcceptor* acceptor = NULL;
  acceptor = new TCPAcceptor(port, ip);  
  if (acceptor->start() == 0) {
    isRunning = true;    
    while (isRunning) {
      stream = acceptor->accept();
      if (stream != NULL) {
	ssize_t len;
	char line[256];
	while ((len = stream->receive(line, sizeof(line))) > 0) {
	  line[len] = 0;
	  printf("received - %s\n", line);
	  stream->send(line, len);
	}
	delete stream;
      }
    }
  }
}

Server::Server(int port, const char* ip) {
  this->port = port;
  this->ip = ip;
  isRunning = false;
}

Server::~Server() {
  stop();
}

void Server::start() {
  isRunning = true;  
  thread_ = std::thread(&Server::runServer, this);
}

void Server::stop() {
  isRunning = false;
  thread_.join();
}

