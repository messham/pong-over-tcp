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
#include <mutex>
#include "server.h"
#include "wqueue.h"
#include "tcpacceptor.h"

#include <iostream>
using namespace std;

void Server::assignId(TCPStream* stream, int workerId) {
  int id = ntohl(workerId);
  stream->send((const char*) &id, sizeof(int));
}

void Server::handleConnection(wqueue<WorkItem*>& queue, int workerId) {
  // Remove 1 item at a time and process it. Blocks until an item 
  // is placed on the queue.
  
  while(isRunning) {
    WorkItem* item = queue.remove();
    TCPStream* stream = item->getStream();
    // Echo coordinates back the client until the connection is 
    // closed
    printf("new player has arrived\n");
    assignId(stream, workerId);
    int input;
    ssize_t len;
    while ((len = stream->receive((char*)&input, sizeof(input))) > 0 && isRunning){
      int coord = ntohl(input);
      stream->send((const char*) &coord, sizeof(int));
      printf("thread %d echoed '%d' back to the client\n", workerId, coord);  
    }
    printf("a player has left\n");
    
    delete item; 
  }
}

void Server::acceptConnections() {
  // create queue and consumer threads
  wqueue<WorkItem*> queue;

  // tPlayer1.id = 1;
  // tPlayer1.t = std::thread(&Server::handleConnection, this, std::ref(queue), 1);
  // tPlayer2.id = 2;
  // tPlayer2.t = std::thread(&Server::handleConnection, this, std::ref(queue), 2);
  
  tPlayer1 = std::thread(&Server::handleConnection, this, std::ref(queue), 1);
  tPlayer2 = std::thread(&Server::handleConnection, this, std::ref(queue), 2);

  WorkItem* item;
  TCPStream* stream = NULL;
  TCPAcceptor* acceptor = new TCPAcceptor(port, ip);
  if (acceptor->start() == 0) {
    while (isRunning) { // accept connections until there are two players
      stream = acceptor->accept(); // blocks thread until connection received
      if (!stream) {
	printf("Could not accept a connection\n");
	continue;
      }
      item = new WorkItem(stream);
      if (!item) {
	printf("Could not create work item a connection\n");
	continue;
      }
      queue.add(item);
    }
  }

}

Server::Server(int port, const char* ip) {
  ids.push(1);
  ids.push(2);
  this->port = port;
  this->ip = ip;
  isRunning = false;
}

Server::~Server() {
  stop();
}

void Server::start() {
  isRunning = true;  
  tAccept = std::thread(&Server::acceptConnections, this);
}

void Server::stop() {
  isRunning = false;
  // if (tPlayer1.t.joinable()) tPlayer1.t.detach();
  // if (tPlayer2.t.joinable()) tPlayer2.t.detach();
  if (tPlayer1.joinable()) tPlayer1.detach();
  if (tPlayer2.joinable()) tPlayer2.detach();  
  if (tAccept.joinable()) tAccept.detach();
}

