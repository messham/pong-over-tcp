#ifndef _GAME_H_
#define _GAME_H_

#include "qtlibs.h"
#include "window.h"
#include "player.h"

#define P1YPOS WIN_HEIGHT / 15
#define P2YPOS WIN_HEIGHT - (WIN_HEIGHT / 15)

class Game : public QWidget {
  Q_OBJECT

 public:
  Game();

 private:
  Window* window;
  Player* p1;
  Player* p2;

};

#endif
