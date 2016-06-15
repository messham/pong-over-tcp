#include "window.h"
#include "game.h"
#include "player.h"

//delete me
#include <iostream>
using namespace std;
//

#define WIN_HEIGHT 300
#define WIN_WIDTH 200

Window::Window() {

  // set colour
  QPalette palette(Window::palette());
  palette.setColor(QPalette::Background, Qt::black);
  palette.setColor(QPalette::Foreground, Qt::white);
  setAutoFillBackground(true);
  setPalette(palette);

  // set size, frame and cursor
  width = WIN_WIDTH;
  height = WIN_HEIGHT;
  setFixedSize(width, height);
  frame = new QFrame(this);
  frame->setFrameStyle(QFrame::Box);	
  frame->setFixedSize(width, height);
  frame->setPalette(palette);
  frame->setMouseTracking(true);
  setCursor(Qt::BlankCursor);

  // game init
  player = new Player(P1YPOS, this);
  Player* player2 = new Player(P2YPOS, this);
  game = new Game(this, player, player2);

  setMouseTracking(true);
}

int Window::getWidth() {
  return width;
}

int Window::getHeight() {
  return height;
}

void Window::mouseMoveEvent(QMouseEvent* event) {
  game->movePlayer(player, event->x());
}
