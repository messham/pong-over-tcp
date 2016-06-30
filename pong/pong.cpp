/*
   pong.cpp

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

#include <QApplication>
#include "src/window.h"
#include "src/tcp/client.h"
#include "src/tcp/server.h"

#include <iostream>
#include <thread>
using namespace std;

int main(int argc, char **argv)
{
  if (argc > 2 || (string(argv[1]) != "1" && string(argv[1]) != "2")) {
    printf("usage: %s <number of players>(default: 1 player)", argv[0]);
    exit(1);
  }

  if (string(argv[1]) == "2") { // multiplayer
    // try connecting client to inputted port/ip,
    // if no server there try creating new server with
    // given port/ip
    Server* server;
    Client* client;
    while (!client) {
      cout << "Please enter port and ip of server to connect to (default: port 8000 ip localhost)" << endl;
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
	cout << "Could not connect to server. Start one at given port/ip? (Y/N)";
	cin >> ans;
	if (ans == "N" || ans == "n") return 0;
	else {
	  server = new Server(port, ip);
	  server->start();
	  client = new Client(port, ip);
	  cout << "Connecting to port: " << port <<  ", server: " << tmpip << endl;
	}
	  
      }
    }  
  }
  else if (string(argv[1]) == "1") { //singleplayer
    // set ai
  }
  
  QApplication app (argc, argv);
  Window window;
  // place players, ball on window
  window.show();
  return app.exec();
  // TODO: close threads upon exiting app
}
