#pragma once
#include "ofMain.h"
#include "ofxCenteredTrueTypeFont.h"

class Gamestate {

  public:
    Gamestate();
    void title(ofxCenteredTrueTypeFont* type);
    void subTitle(ofxCenteredTrueTypeFont* type);
    void transition(int level, ofxCenteredTrueTypeFont* type);
    void lose(ofxCenteredTrueTypeFont* type);
    void win(ofxCenteredTrueTypeFont* type);

  private:
    int x;
    int y;
    int offset;
    ofColor color;
};
