#include "Apple.h"
#include <Arduino.h>
#include "Worm.h"
#include "Frame.h"

void Apple::add(Worm* worm) {
  do {
    x = random(1, 6);
    y = random(1, 6);
  } 
  while (worm->cellReserved(x, y));
}

bool Apple::eat(Worm* worm) {
  if (worm->getHeadX() == x && worm->getHeadY() == y) {
    add(worm);
    return true;
  }
  else {
    return false;
  }
}
int Apple::getX(){
  return x;
}
int Apple::getY(){
  return y;
}
void Apple::draw(Frame* frame) {
  frame->setPixel(x, y, 0, 255, 0);
  
}
