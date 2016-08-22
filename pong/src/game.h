/*
   game.h

   Simply pong.

   ------------------------------------------

   Copyright 2016 JM Messham and Trevor Stokvis

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

#ifndef _GAME_H_
#define _GAME_H_

#include "player.h"
#include "ball.h"

#define P1YPOS WIN_HEIGHT - (WIN_HEIGHT / 15)
#define P2YPOS WIN_HEIGHT / 15

class Window;

class Game : public QWidget {
  Q_OBJECT

 private:
  Window* window;
  Player* p1;
  Player* p2;
  Ball* ball;
  void checkCollision();

 protected:
  void timerEvent(QTimerEvent *event);
  
 public:
  Game(Window* w, Player* p1, Player* p2);
  void movePlayer(Player* p, int pos);
  

  // stubs
  //void setPlayers(Player p1, Player p2);
  //void setScore();
  //void getScore();
  


};

#endif
