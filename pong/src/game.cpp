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

  cout << p1->parentWidget()->metaObject()->className() << endl;
  //this->move(xPos, yPos);
  
  // frame->installEventFilter(this);
  // p1->installEventFilter(this);
  // p1->installEventFilter(this);
}

void Game::movePlayer(Player* p, int pos) {
  p->setPos(pos);
}
