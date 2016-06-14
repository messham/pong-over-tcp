#include "player.h"

Player::Player(int yPos, QWidget* parent) : QWidget(parent){
  // set background colour
  QPalette palette(Player::palette());
  palette.setColor(QPalette::Background, Qt::white);
  setAutoFillBackground(true);
  setPalette(palette);

  // TODO: move this to game class
  pHeight = parent->height() / 20;
  pWidth = parent->width() / 5;
  xPos = (WIN_WIDTH / 2) - (pWidth / 2);
  yPos = yPos - (pHeight / 2);
  this->resize(pWidth, pHeight);
  this->yPos = yPos;
  this->move(xPos, yPos);

  setMouseTracking(true);
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
