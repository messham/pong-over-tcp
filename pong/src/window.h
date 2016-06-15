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

#define WIN_HEIGHT 300
#define WIN_WIDTH 200

// two instances of window required for multiplayer -- player refers to this instance's user and his/her mouse movements
class Window : public QWidget {
  Q_OBJECT

 public:
  Window();
 
 private:
  QFrame* frame;
  Game* game;
  Player* player; 
  
 protected:
  void mouseMoveEvent(QMouseEvent* event);
  bool eventFilter(QObject* obj, QEvent* event);
};

#endif
