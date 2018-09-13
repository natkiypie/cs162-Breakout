#pragma once
#include "ofMain.h"

class Debris {
  public:
    Debris();
    Debris(ofRectangle brick, ofImage* image);
    void initialize();
    void draw();
    void explode();
    bool getStatus();

  private:
    ofRectangle brick;
    ofRectangle* debris;
    ofImage* image;
    ofColor color;
    vector<ofRectangle*> debrisSystem;
    vector<float> velocity, xModifier, acceleration;
    bool complete;
    float speed;
    float damp;
    float alpha;
    float vel[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    float xMod[10] = {-0.7, -0.5, 0, 0.5, 0.7, -0.7, -0.5, 0, 0.5, 0.7};
    float accl[10] = {-1, -4, -4.2, -3, -2, -2.5, -2, -3.9, -3.5, -1.5};
};

