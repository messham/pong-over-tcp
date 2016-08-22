/*
   ball.h

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

#ifndef _BALL_H_
#define _BALL_H_

#include <QApplication>
#include <QCursor>
#include <QFrame>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QObject>
#include <QGraphicsEllipseItem>
#include <QGraphicsScene>
#include <QGraphicsView>

class Ball : public QWidget {
  Q_OBJECT

 private:
  int x;
  int y;
  int height;
  int width;
  
  int xspeed;
  int yspeed;
  int xdir;
  int ydir;
  int MAX_X_SPEED = 10;

  int startX;
  int startY;
  
 protected:
  void paintEvent(QPaintEvent* event);
  
 public:
  Ball(QWidget* parent);
  void setPos(int x, int y);
  void advance();
  void ballHitPlayer(double perc);
  void ballHitSide();
  void restart(bool startUP);
  int getXPos();
  int getYPos();
  int getHeight();
  int getWidth();
  
};

#endif
