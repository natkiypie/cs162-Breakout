#pragma once
#include "ofMain.h"

class GuardTower {
  public:
  GuardTower();
  void draw();
  void move();
  void right();
  void left();
  void up();
  void down();
  void atBoundry();

  private:
  ofColor color;
  float x;
  float y;
  int radius;
  float direction;
  float speed;
  float leftBoundry;
  float rightBoundry;
  float topBoundry;
  float bottomBoundry;
};
