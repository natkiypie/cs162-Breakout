#pragma once
#include "ofMain.h"

class Paddle {

  public:
    Paddle();
    void draw();
    void move();
    ofRectangle* getBoundingBox();
    ofRectangle* getBoundingBoxLeft();
    ofRectangle* getBoundingBoxCenter();
    ofRectangle* getBoundingBoxRight();
    void handleDamage();
    void setIsDamaged();

    void drawBoundingBox();

  private:
    ofRectangle boundingBox, left, center, right;
    ofColor color;
    int damage;
    bool isDamaged;
};
