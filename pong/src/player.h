#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "qtlibs.h"

class Player : public QWidget {
  Q_OBJECT
 public:
  Player(int yPos, QWidget* parent);
  
 private:
  int xPos;
  int yPos;
  int pHeight;
  int pWidth;
  
 protected:
  void paintEvent(QPaintEvent* event);
  void mouseMoveEvent(QMouseEvent* event);
};

#endif
