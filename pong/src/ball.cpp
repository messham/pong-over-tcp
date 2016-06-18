#include "ball.h"
#include <iostream>
// constructor
// ball starts middle of window traveling towards p1
Ball::Ball(QWidget* parent) : QWidget(parent) {
  // set background colour
  QPalette palette(Ball::palette());
  palette.setColor(QPalette::Background, Qt::white);
  setAutoFillBackground(true);
  setPalette(palette);

  // set size and initial position
  height = parent->height() / 20;
  width = height;
  resize(width, height);
  startX = (parent->width() / 2) - (width / 2);
  x = startX;
  startY = (parent->height() / 2) - (height / 2);
  y = startY;
  setPos(x, y);
  xspeed = 0;
  xdir = 1;
  yspeed = 1;
  ydir = 1;

}

void Ball::setPos(int x, int y) {
  this->move(x, y);
}

void Ball::paintEvent(QPaintEvent* event) {

}

//returns the x-coordinate of the ball
int Ball::getXPos() {
   return x;
}

// returns the y-coordinate of the ball
int Ball::getYPos() {
    return y;
}

int Ball::getHeight() {
  return height;
}

int Ball::getWidth() {
  return width;
}

//moves ball by xspeed and yspeed;
void Ball::advance() {
    y += ydir*yspeed;
    x += xdir*xspeed;
    setPos(x,y);
}

// handles action when a ball hits a player
// pre: recieves the position on the player the ball was hit and the width of the player
// post: if the ball was hit at either edges xspeed is higher than hit at senter

void Ball::ballHitPlayer(double perc) {
  ydir = ydir * -1;
  double newSpeed = 0.0;

  if (perc < 0.5) {
    xdir = 1;

    if (xspeed < MAX_X_SPEED) {
        newSpeed = 2*(0.5 - perc) * (double) MAX_X_SPEED;
      }
    else newSpeed = 2*(0.5 - perc) * (double) xspeed;

    xspeed = (int) newSpeed;


  } else {
    xdir = -1;
    if (xspeed < MAX_X_SPEED) {
        newSpeed = 2*(perc - 0.5) * (double) MAX_X_SPEED; }
    else newSpeed = 2*(perc - 0.5) * (double) xspeed + (double) xspeed;

    xspeed = (int) newSpeed;


  }

  
}

// handles action when a ball hits the side of the window
void Ball::ballHitSide() {
  xdir = xdir*-1;
}

// starts the ball back in the middle, if startUP is true the ball moves up to start
void Ball::restart(bool startUP) {
  x = startX;
  y = startY;
  setPos(x, y);
  xspeed = 0;
  xdir = 1;
  yspeed = 5;
  if (startUP) ydir = -1;
  else ydir = 1;
}
