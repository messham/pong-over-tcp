#include "game.h"
#include "window.h"

//delete me
#include <iostream>
using namespace std;
//

Game::Game(Window* w, Player* p1, Player* p2) {
  window = w;
  // player init
  this->p1 = p1;
  this->p2 = p2;
  ball = new Ball(window);
  cout << p1->parentWidget()->metaObject()->className() << endl;
}

// move player along x axis within game window
void Game::movePlayer(Player* p, int pos) {
  int rightPos = window->getWidth() - p->getWidth();
  if (pos > rightPos)
    p->setPos(rightPos);
  else
    p->setPos(pos);
}
