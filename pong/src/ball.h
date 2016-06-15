#ifndef _BALL_H_
#define _BALL_H_

#include <QApplication>
#include <QCursor>
#include <QFrame>
#include <QPainter>
#include <QPaintEvent>
#include <QPushButton>
#include <QObject>

class Ball : public QWidget {
  Q_OBJECT

 private:
  int x;
  int y;
  int height;
  int width;
  
 protected:
  void paintEvent(QPaintEvent* event);
  
 public:
  Ball(QWidget* parent);
  
};

#endif
