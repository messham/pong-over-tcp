#include "window.h"
#include "game.h"

//delete me
#include <iostream>
using namespace std;
//

Window::Window() {

  // colour init
  QPalette palette(Window::palette());
  palette.setColor(QPalette::Background, Qt::black);
  palette.setColor(QPalette::Foreground, Qt::white);
  setAutoFillBackground(true);
  setPalette(palette);

  // window + frame init
  setFixedSize(WIN_WIDTH, WIN_HEIGHT);
  frame = new QFrame(this);
  frame->setFrameStyle(QFrame::Box);	
  frame->setFixedSize(WIN_WIDTH - 5,WIN_HEIGHT - 5);
  frame->setPalette(palette);
  
  setMouseTracking(true);
}

bool Window::eventFilter(QObject* obj, QEvent* event) {
  if (event->type() == QEvent::MouseMove) return true;
  return QObject::eventFilter(obj, event);
}

void Window::mouseMoveEvent(QMouseEvent* event) {
  //p1->move(p1->mapToGlobal(QCursor::pos()));
  // if (event->buttons()) {
  //   this->move(event->pos());
  // }
}
