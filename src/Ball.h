#pragma once
#include "ofMain.h"
#include "ofxCenteredTrueTypeFont.h"


class Ball {

  public:
    Ball();
    void draw();
    void move();
    void bouncePaddle(float direction);
    void bounceTopBottom();
    void bounceSides();
    void belowBoundry(ofSoundPlayer* sound);
    void increaseSpeed();
    ofRectangle* getBoundingBox();
    int getBalls();
    void setServe();
    void setServeCount(int level);
    void setTransition();
    void resetSpeed();
    void setBalls();

    void printCount(ofxCenteredTrueTypeFont* type);

    float printValues();

  private:
    ofRectangle boundingBox;
    ofColor color;
    float direction;
    float speed;
    int count;
    int balls;
    int boundry;
    bool serve;
    bool transition;
};
