#ifndef _GAME_H_
#define _GAME_H_

#include "player.h"

#define P1YPOS WIN_HEIGHT / 15
#define P2YPOS WIN_HEIGHT - (WIN_HEIGHT / 15)

class Window;

class Game : public QWidget {
  Q_OBJECT

 private:
  Window* window;
  Player* p1;
  Player* p2;
  
 public:
  Game(Window* w, Player* p1, Player* p2);
  void movePlayer(Player* p, int pos);

  // stubs
  //void setPlayers(Player p1, Player p2);
  //void setScore();
  //void getScore();
  


};

#endif
