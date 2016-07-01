/*
   window-sp.h - window subclass for singplayer pong

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

class WindowSP : public Window {
public:
  WindowSP() : Window()  {
    // game init
    client = NULL;
    player = new Player(P1YPOS, this);
    Player* player2 = new Player(P2YPOS, this);
    game = new Game(this, player, player2);
  }
  
  void mouseMoveEvent(QMouseEvent* event) {
    game->movePlayer(player, event->x());
  }
};
