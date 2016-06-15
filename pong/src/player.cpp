#include "player.h"
#include <QSize>

//delete me
#include <iostream>
using namespace std;
//

Player::Player(int yPos, QWidget* parent) : QWidget(parent){
  // set background colour
  QPalette palette(Player::palette());
  palette.setColor(QPalette::Background, Qt::white);
  setAutoFillBackground(true);
  setPalette(palette);

  // set size and initial position
  height = parent->height() / 20;
  width = parent->width() / 5;
  resize(width, height);
  x = (parent->width() / 2) - (width / 2);
  y = yPos - (height / 2);  
  setPos(x);
}

void Player::setPos(int x) {
  this->move(x, y);
}

int Player::getPos() {
  return 0; //stub
}

void Player::mouseMoveEvent(QMouseEvent* event) {
  //this->move(this->parentWidget()->mapFromGlobal(QCursor::pos()));
  // if (event->buttons()) {
  //   this->move(event->pos());
  // }
}

void Player::paintEvent(QPaintEvent* event) {
    QRect rect = event->rect();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::white);
    painter.drawRect(rect);
    // painter.translate
}
