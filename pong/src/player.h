#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <QApplication>
#include <QCursor>
#include <QFrame>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QObject>

class Player : public QWidget {
  Q_OBJECT

 private:
  int x;
  int y;
  int height;
  int width;
  
 protected:
  void paintEvent(QPaintEvent* event);
  void mouseMoveEvent(QMouseEvent* event);
  
 public:
  Player(int yPos, QWidget* parent);
  void movePlayer(int x);
  
};

#endif
