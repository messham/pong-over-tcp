#include "ball.h"

// constructor
// ball starts middle of window traveling towards p1
Ball::Ball(QWidget* parent) : QWidget(parent) {
  // set background colour
  QPalette palette(Ball::palette());
  palette.setColor(QPalette::Background, Qt::white);
  setAutoFillBackground(true);
  setPalette(palette);

  // set size and initial position
  height = parent->height() / 20;
  width = height;
  resize(width, height);
  x = (parent->width() / 2) - (width / 2);
  y = (parent->height() / 2) - (height / 2);
  setPos(x, y);
}

void Ball::setPos(int x, int y) {
  this->move(x, y);
}

void Ball::paintEvent(QPaintEvent* event) {

}
