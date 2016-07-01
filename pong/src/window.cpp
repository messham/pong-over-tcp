/*
   window.cpp

   Simply pong.

   ------------------------------------------

   Copyright 2016 JM Messham

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

#include "window.h"
#include "game.h"
#include "player.h"

//delete me
#include <iostream>
using namespace std;
//


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

  setMouseTracking(true);
}

Window::Window(Client* client) {
  Window();
  this->client = client;
}

int Window::getWidth() {
  return width;
}

int Window::getHeight() {
  return height;
}

void Window::mouseMoveEvent(QMouseEvent* event) {}



