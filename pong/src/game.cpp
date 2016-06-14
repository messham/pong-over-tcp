#include "game.h"
#include "window.h"

//delete me
#include <iostream>
using namespace std;
//

Game::Game(Window* w) {
  window = w;
  // player init
  p1 = new Player(P1YPOS, window);
  p2 = new Player(P2YPOS, window);

  cout << p1->parentWidget()->metaObject()->className() << endl;

  //this->move(xPos, yPos);
  
  // frame->installEventFilter(this);
  // p1->installEventFilter(this);
  // p1->installEventFilter(this);
}
