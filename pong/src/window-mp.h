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

#include <iostream>
using namespace std;

class WindowMP : public Window {
public:
  WindowMP(Client* client, Server* server) : Window()  {
    // game init
    this->client = client;
    this->server = server;
    player = new Player(P1YPOS, this);
    Player* player2 = new Player(P2YPOS, this);
    game = new Game(this, player, player2);
  }
  
  void mouseMoveEvent(QMouseEvent* event) {
    // currently just sends coords and doesn't move player
    client->sendCoords(event->x());
    
    // uncomment below to move payer and not send coords
    /* game->movePlayer(player, event->x()); */
    /* cout << event->x() << endl; */
    // send coords to server
  }
};
