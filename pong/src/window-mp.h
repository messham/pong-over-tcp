/*
   window-mp.h - window subclass for multiplater pong

   Simply pong.

   ------------------------------------------

   Copyright 2016 JM Messham

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

#include "window.h"
#include <stdexcept>
#include <thread>
#include <iostream>

class WindowMP : public Window {
private:
  Player* player2;
  std::thread tReceiver;
  bool clientIsConnected = false;

  void streamCoords() {
    while (clientIsConnected) {
      int coords = client->receiveCoords();
      printf("client received - %d\n", coords);      
      // do something with coords
      game->movePlayer(player, coords);
    }
  }
  
  void startReceiving() {
    clientIsConnected = true;
    tReceiver = std::thread(&WindowMP::streamCoords, this);    
  }
  
  void stopReceiving() {
    clientIsConnected = false;
    sleep(1); //ensure thread has completed before joining
    if (tReceiver.joinable()) tReceiver.detach();
  }

public:
  WindowMP() : Window()  {
    // game init
    client = NULL;
    server = NULL;
    
    // try connecting client to inputted port/ip,
    // if no server there try creating new server with
    // given port/ip
    while (!client) {
      cout << "Please enter port and ip of server to connect to "
	   << "(default: port 8000 ip localhost)" << endl;
      string tmpport;
      int port;
      cout << "port: ";
      getline(cin, tmpport);
      if (tmpport.empty()) port = 8000;
      else port = atoi(tmpport.c_str());
    
      string tmpip;
      cout << "ip: ";
      getline(cin, tmpip);
      if (tmpip.empty()) tmpip = "localhost";
      const char* ip = tmpip.c_str();
      
      try {
	client = new Client(port, ip);   
      }
      catch (exception e){
	string ans;
	while (!server) {
	  cout << "Could not connect to server. Start one at given port/ip? (Y/N): ";
	  getline(cin, ans);
	  if (ans == "N" || ans == "n")
	    throw std::invalid_argument("No server to join. Exiting.\n");
	  else if (ans == "Y" || ans == "y")  {
	    server = new Server(port, ip);
	    server->start();
	    client = new Client(port, ip); 
	    cout << "Connecting to port: " << port <<  ", server: " << tmpip << endl;
	  }
	} 
      }
    }
    player = new Player(P1YPOS, this);
    player2 = new Player(P2YPOS, this);
    game = new Game(this, player, player2);
    startReceiving();
  }
  
  void mouseMoveEvent(QMouseEvent* event) {
    // send mouse coords to server
    client->sendCoords(event->x());
  }

  ~WindowMP() {
    stopReceiving();    
    delete client;
    delete server;
    delete player;
    delete player2;
    delete game;
  }
};
