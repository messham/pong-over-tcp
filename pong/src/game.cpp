#include "game.h"

Game::Game() {
  // player init
  p1 = new Player(P1YPOS, window);
  p2 = new Player(P2YPOS, window);

  //cout << p1->parentWidget()->metaObject()->className() << endl;

  // frame->installEventFilter(this);
  // p1->installEventFilter(this);
  // p1->installEventFilter(this);
}
