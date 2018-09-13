#pragma once
#include "ofMain.h"
#include "ofxCenteredTrueTypeFont.h"

class Scoreboard {
  
  public:
    Scoreboard();
    void drawBalls(int balls);
    void printBalls(ofxCenteredTrueTypeFont* type);
    void printStage(ofxCenteredTrueTypeFont* type, int stage);
    void printScore(ofxCenteredTrueTypeFont* type);
    void drawWorth(ofRectangle brickBoundingBox, int worth, ofxCenteredTrueTypeFont* type);
    int getScore();
    void setScore(int score);

  private:
    int score;
    int y;
    int x;
    int xOffsetOne;
    int xOffsetTwo;
    ofColor color;
};
