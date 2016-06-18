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
