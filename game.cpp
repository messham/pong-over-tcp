#include "game.h"
#include "window.h"

//delete me
#include <iostream>
#include <time.h>
using namespace std;
//

Game::Game(Window* w, Player* p1, Player* p2) {
  window = w;
  // player init
  this->p1 = p1;
  this->p2 = p2;
  ball = new Ball(window);

  cout << p1->parentWidget()->metaObject()->className() << endl;

  startTimer(15);
  ball->restart(true);
}

// move player along x axis within game window
void Game::movePlayer(Player* p, int pos) {
  int rightPos = window->getWidth() - p->getWidth();
  if (pos > rightPos)
    p->setPos(rightPos);
  else
    p->setPos(pos);
}

// pushes the ball forward, if a collision occurs informs ball
void Game::timerEvent(QTimerEvent *event) {
  ball->advance();

  // added code so that player 2 always follows the ball, for testing purposes
  if (ball->getXPos() < ball->getWidth()) p2->setPos(ball->getXPos());
  else p2->setPos(ball->getXPos()-ball->getWidth() + 7);

   checkCollision();

}

//checks to see if the ball has collided with either player, hit the side of the screen
//   or if a player has scored
void Game::checkCollision() {

  // ball hits player1 (bottom)
  if (ball->getXPos()+ ball->getWidth() >= p1->getXPos() && ball->getXPos() <= p1->getXPos() + p1->getWidth() && ball->getYPos() == (p1->getYPos() -  p1->getHeight())) {
      int numerator = p1->getXPos() + p1->getWidth() - ball->getXPos();
      int denomenator =  ball->getWidth() + p1->getWidth();
      ball->ballHitPlayer((double) numerator / (double) denomenator);
  }

  // ball hits player2 (top)
  if (ball->getXPos() >= p2->getXPos() - ball->getWidth() && ball->getXPos() <= p2->getXPos() + p2->getWidth() && (ball->getYPos() - ball->getHeight()) == p2->getYPos()) {
      int numerator = p2->getXPos() + p2->getWidth() - ball->getXPos();
      int denomenator =  ball->getWidth() + p2->getWidth();
      ball->ballHitPlayer(1.0 - (double) numerator / (double) denomenator);
}

  if (ball->getXPos() <= 0 || ball->getXPos()+ball->getWidth() >= window->getWidth()) {
    ball->ballHitSide();
  }

  // if the ball goes of the bottom/top of the screen the ball starts back at the center, ball goes toward the person who was scored on
  if (ball->getYPos() > window->getHeight() + ball->getHeight()) ball->restart(false);
  if (ball->getYPos() < 0 - ball->getHeight()) ball->restart(true);
  }



