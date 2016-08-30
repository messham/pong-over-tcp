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
#include "server.h"
#include "wqueue.h"
#include "tcpacceptor.h"

#include <iostream>
using namespace std;

void Server::assignId(TCPStream* stream, int workerId) {
  int id = ntohl(workerId);
  stream->send((const char*) &id, sizeof(int));
}

void Server::receiveMovements(TCPStream* stream, int workerId) {
    int input;
    ssize_t len;
    while ((len = stream->receive((char*)&input, sizeof(input))) > 0 && isRunning){
      struct player_coord* pCoord = new player_coord;
      pCoord->id = workerId;
      pCoord->coord = ntohl(input);
      qPlayerCoords->add(pCoord);

    }
}

void Server::sendMovements() {
  while (isRunning) {
    struct player_coord* pCoord = qPlayerCoords->remove();
    for (int i = 0; i < 2; i++) {
      if (playerThreads[i].stream) {
	// build int where 1st byte = id; last 3 bytes = coords
	int coord = pCoord->coord;
	int id_coord = (pCoord->id << 24) | pCoord->coord;
	playerThreads[i].stream->send((const char*) &id_coord, sizeof(int));
	printf("player id %d and coord %d map to integer %d\n", pCoord->id, pCoord->coord, id_coord);
	// printf("sent player %d movement of %d to client\n", pCoord->id, pCoord->coord);
      }
    }
  }
}

void Server::addConnection(TCPStream* stream) {
  connections.push_back(stream);
}

void Server::removeConnection(TCPStream* stream) {
  connections.erase(std::remove(connections.begin(), connections.end(), stream),
		    connections.end());
}

void Server::handleConnection(wqueue<WorkItem*>& queue, struct thread_data& td) {
  // Remove 1 item at a time and process it. Blocks until an item 
  // is placed on the queue.
  while(isRunning) {
    WorkItem* item = queue.remove();
    TCPStream* stream = item->getStream();
    
    printf("new player has arrived\n");
    td.stream = stream;
    assignId(stream, td.id);
    receiveMovements(stream, td.id);
    
    printf("a player has left\n");
    td.stream = NULL;
    delete item; 
  }
}

void Server::acceptConnections() {
  // create queue and consumer threads
  wqueue<WorkItem*> queue(2);
  qPlayerCoords = new wqueue<struct player_coord*>(100);

  for (int i = 0; i < 2; i++) {
    playerThreads[i].id = i + 1;
    playerThreads[i].stream = NULL;
    playerThreads[i].t = std::thread(&Server::handleConnection, this, std::ref(queue), std::ref(playerThreads[i]));
  }  
  tSendMovements = std::thread(&Server::sendMovements, this);

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
  this->port = port;
  this->ip = ip;
  isRunning = false;
}

Server::~Server() {
  stop();
}

void Server::start() {
  isRunning = true;
  tAcceptConnections = std::thread(&Server::acceptConnections, this);
}

void Server::stop() {
  isRunning = false;
  for (auto& td : playerThreads) {
    if (td.t.joinable()) td.t.detach();
  }
  if (tSendMovements.joinable()) tSendMovements.detach();
  if (tAcceptConnections.joinable()) tAcceptConnections.detach();
  delete qPlayerCoords;
}
