#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "qtlibs.h"

#define WIN_HEIGHT 300
#define WIN_WIDTH 200

class Window : public QWidget {
  Q_OBJECT

 public:
  Window();
 
  // stubs
  //void setPlayers(Player p1, Player p2);
  //void setScore();
  //void getScore();

 private:
  QFrame* frame;
  
 protected:
  void mouseMoveEvent(QMouseEvent* event);
  bool eventFilter(QObject* obj, QEvent* event);
};

#endif
