#include <QApplication>
#include <QCursor>
#include <QFrame>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>


//delete me
#include <iostream>
using namespace std;
//

#define WIN_HEIGHT 300
#define WIN_WIDTH 200
#define P1YPOS WIN_HEIGHT / 15
#define P2YPOS WIN_HEIGHT - (WIN_HEIGHT / 15)

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



Player::Player(int yPos, QWidget* parent) : QWidget(parent){
  // set background colour
  QPalette palette(Player::palette());
  palette.setColor(QPalette::Background, Qt::white);
  setAutoFillBackground(true);
  setPalette(palette);


  pHeight = parent->height() / 20;
  pWidth = parent->width() / 5;
  xPos = (WIN_WIDTH / 2) - (pWidth / 2);
  yPos = yPos - (pHeight / 2);
  this->resize(pWidth, pHeight);
  this->yPos = yPos;
  this->move(xPos, yPos);

  setMouseTracking(true);
}

#include "pong.moc"

void Player::mouseMoveEvent(QMouseEvent* event) {
  //this->move(this->parentWidget()->mapFromGlobal(QCursor::pos()));
  // if (event->buttons()) {
  //   this->move(event->pos());
  // }
}

void Player::paintEvent(QPaintEvent* event) {
    QRect rect = event->rect();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(Qt::white);
    painter.drawRect(rect);
    // painter.translate
  

  


}

class MouseMoveEater : public QObject {

protected:
  bool eventFilter(QObject* obj, QEvent* event);
};




class Window : public QWidget {
 
public:
  Window();
 
  // stubs
  //void setPlayers(Player p1, Player p2);
  //void setScore();
  //void getScore();

private:
  QFrame* frame;
  Player* p1;
  Player* p2;

protected:
  void mouseMoveEvent(QMouseEvent* event);
  bool eventFilter(QObject* obj, QEvent* event);
  
};



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
  
  // player init
  p1 = new Player(P1YPOS, this);
  p2 = new Player(P2YPOS, this);

  cout << p1->parentWidget()->metaObject()->className() << endl;

  frame->installEventFilter(this);
  p1->installEventFilter(this);
  p1->installEventFilter(this);

  setMouseTracking(true);
}

bool Window::eventFilter(QObject* obj, QEvent* event) {
  if (event->type() == QEvent::MouseMove) return true;
  return QObject::eventFilter(obj, event);
}

void Window::mouseMoveEvent(QMouseEvent* event) {
  p1->move(p1->mapToGlobal(QCursor::pos()));
  // if (event->buttons()) {
  //   this->move(event->pos());
  // }
}


//NOTE: copy constructors are disabled in the Qt Object Model; must use pointers

int main(int argc, char **argv)
{
 QApplication app (argc, argv);
 Window window;
 // Player p1 (P1YPOS, &window);
 // Player p2 (P2YPOS, &window);
 QWidget ball;
 // place players, ball on window
 window.show();
 return app.exec();
}
