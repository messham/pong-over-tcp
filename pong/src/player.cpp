/*
   player.cpp

   Simply pong.

   ------------------------------------------

   Copyright 2016 JM Messham and Trevor Stokvis

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "player.h"

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

int Player::getXPos() {
  return x;
}

int Player::getYPos() {
  return y;
}

void Player::setPos(int xpos) {
  x = xpos;
  this->move(x, y);
}

int Player::getWidth() {
  return width;
}

int Player::getHeight() {
  return height;
}

int Player::getPos() {
  return 0;  //stub
}

void Player::mouseMoveEvent(QMouseEvent* event) {
  //this->move(this->parentWidget()->mapFromGlobal(QCursor::pos()));
  // if (event->buttons()) {
  //   this->move(event->pos());
  // }
}

void Player::paintEvent(QPaintEvent* event) {
    // QRect rect = event->rect();
    // QPainter painter(this);
    // painter.setRenderHint(QPainter::Antialiasing);
    // painter.setBrush(Qt::white);
    // painter.drawRect(rect);
}
