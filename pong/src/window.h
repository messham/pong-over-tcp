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
