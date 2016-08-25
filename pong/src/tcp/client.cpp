/*
   client.cpp

   Test client for the tcpsockets classes. 

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
#include <string>
#include "client.h"

#include <iostream>

Client::Client(int port, const char* ip) {
  this->port = port;
  this->ip = ip;
  connector = new TCPConnector();
  stream = connector->connect(ip, port);
  

  if (!stream) {
    throw std::invalid_argument("Client::Client - stream failed to connect to given port and ip");
  }


  int len;
  string message;
  char line[256];
  if (stream) {
    // message = "Is there life on Mars?";
    // stream->send(message.c_str(), message.size());
    // printf("sent - %s\n", message.c_str());
    // len = stream->receive(line, sizeof(line));
    // line[len] = 0;
    // printf("client received - %s\n", line); //BLOCKING??
  }
}

Client::~Client() {
  delete connector;
  delete stream;
}

void Client::sendCoords(int x) {
  
  if (!stream) {
    printf("sendCoords::No connection to server!");
    return;
  }
  int coord = htonl(x);
  stream->send((const char*) &coord, sizeof(int));
  printf("client sent - %d\n", x);
}

int Client::receiveCoords() {
  if (!stream) {
    printf("receiveCoords::No connection to server!");
    return -1; 
  }

  ssize_t len;
  int recv;
  len = stream->receive((char*)&recv, sizeof(recv));
  return recv;
}
