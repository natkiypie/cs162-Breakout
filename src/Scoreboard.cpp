#include "Scoreboard.h"

Scoreboard::Scoreboard() {
  this->score = 0;
  this->y = 75;
  this->x = (ofGetWidth() / 2);
  this->xOffsetOne = 400;
  this->xOffsetTwo = 30;
  this->color = ofColor(125, 125, 125);
}

void Scoreboard::drawBalls(int balls) {
  for (int i = 0; i < (balls - 1); ++i) {
    ofPushMatrix();
    ofTranslate((((ofGetWidth() / 2) - 328)  + (i * 20)), 90);
    ofSetColor(this->color);
    ofDrawRectangle(0, 0, 10, 10);
    ofPopMatrix();
  }
}

void Scoreboard::printBalls(ofxCenteredTrueTypeFont* type) {
  ofPushMatrix();
  ofTranslate((this->x - this->xOffsetOne), this->y);
  char print[255];
  ofSetColor(this->color);
  sprintf(print, "Balls");
  type->drawStringCentered(print, 0, 0);
  ofPopMatrix();
}

void Scoreboard::printStage(ofxCenteredTrueTypeFont* type, int stage) {
  ofPushMatrix();
  ofTranslate(this->x, this->y);
  char print[255];
  ofSetColor(this->color);
  sprintf(print, "Stage 0%d", stage);
  type->drawStringCentered(print, 0, 0);
  ofPopMatrix();
}

void Scoreboard::printScore(ofxCenteredTrueTypeFont* type) {
  ofPushMatrix();
  ofTranslate(((this->x + this->xOffsetOne) - this->xOffsetTwo), this->y);
  char print[255];
  ofSetColor(this->color);
  if (score < 10) {
    sprintf(print, "Score 0%d", this->score);
    type->drawStringCentered(print, 0, 0);
  } else {
    sprintf(print, "Score %d", this->score);
    type->drawStringCentered(print, 0, 0);
  }
  ofPopMatrix();
}

void Scoreboard::drawWorth(ofRectangle brickBoundingBox, int worth, ofxCenteredTrueTypeFont* type) {
  ofPushMatrix();
  ofTranslate(((brickBoundingBox.getX() + (brickBoundingBox.getWidth() / 2)) - 4), ((brickBoundingBox.getY() + brickBoundingBox.getHeight() / 2) + 3));
  char print[255];
  ofSetColor(this->color);
  sprintf(print, "+%d", worth);
  type->drawStringCentered(print, 0, 0);
  ofPopMatrix();
}

int Scoreboard::getScore() {
  return this->score;
}

void Scoreboard::setScore(int score) {
  this->score += score;
}
