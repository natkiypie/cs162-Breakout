#pragma once
#include "ofMain.h"

enum Type {A, B, C, D};
enum Condition {FIRST, SECOND, THIRD, FOURTH};

class Brick {

  public:
    Brick();
    Brick(int x, int y, int width, int height, ofColor color, ofImage* image, Type type, int resistance, int worth);
    void draw();
    void setBump();
    void bumpUp();
    void bumpDown();
    void backupBumpCheck();
    void playAnimation();
    void fade();
    void hinge();
    void drop();
    void disappear();
    ofRectangle getBoundingBox();
    Type getType();
    int getWorth();
    int getResistance();
    Condition getCondition();
    bool getBumpStop();
    bool getAnimation();
    void setResistance();
    void setCondition(Condition condition);
    void setBrightness();

    int printValues();

  private:
    ofRectangle* boundingBox, thisBoundingBox;
    ofColor color;
    ofImage* image;
    Type type;
    int resistance;
    int worth;
    Condition condition;
    float degree;
    float alpha;
    float bump;
    float bumpVelocity;
    float bumpMax;
    bool collision;
    bool bumpStart;
    bool bumpStop;
    bool animation;
};
