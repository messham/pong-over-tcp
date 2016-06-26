/*
   window.h

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

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <QApplication>
#include <QCursor>
#include <QFrame>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QObject>

#include "game.h"

// two instances of window required for multiplayer -- player refers to this instance's user and his/her mouse movements
class Window : public QWidget {
  Q_OBJECT

 private:
  Game* game;
  Player* player;   
  QFrame* frame;
  int width;
  int height;
  
 protected:
  void mouseMoveEvent(QMouseEvent* event);
  
 public:
  Window();
  int getWidth();
  int getHeight();
};

#endif
