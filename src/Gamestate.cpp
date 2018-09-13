#include "Gamestate.h"

Gamestate::Gamestate() {
  this->x = (ofGetWidth() / 2);
  this->y = (ofGetHeight() / 3);
  this->offset = 200;
  this->color = ofColor(175, 175, 175);
}

void Gamestate::title(ofxCenteredTrueTypeFont* type) {
  ofPushMatrix();
  ofTranslate(this->x, this->y);
  char print[255];
  int rand = ofRandom(0, 100);
  if (rand < 50) {
    ofSetColor(100, 0, 0);
  } else if (rand > 50) {
    ofSetColor(0, 0, 100);
  }
  sprintf(print, "BREAKOUT");
  type->drawStringCentered(print, 0, 0);
  ofPopMatrix();
}

void Gamestate::subTitle(ofxCenteredTrueTypeFont* type) {
  ofPushMatrix();
  ofTranslate(this->x, (this->y + this->offset));
  char print[255];
  int rand = ofRandom(0, 100);
  if (rand < 50) {
    ofSetColor(100, 0, 0);
  } else if (rand > 50) {
    ofSetColor(0, 0, 100);
  }
  sprintf(print, "press space to start");
  type->drawStringCentered(print, 0, 0);
  ofPopMatrix();
}

void Gamestate::transition(int level, ofxCenteredTrueTypeFont* type) {
  ofPushMatrix();
  ofTranslate(this->x, this->y);
  char print[255];
  ofSetColor(this->color);
  sprintf(print, "Level 0%d", (level + 1));
  type->drawStringCentered(print, 0, 0);
  ofPopMatrix();
}

void Gamestate::lose(ofxCenteredTrueTypeFont* type) {
  ofPushMatrix();
  ofTranslate(this->x, this->y);
  char print[255];
  ofSetColor(this->color);
  sprintf(print, "Game Over");
  type->drawStringCentered(print, 0, 0);
  ofPopMatrix();
}

void Gamestate::win(ofxCenteredTrueTypeFont* type) {
  ofPushMatrix();
  ofTranslate(this->x, this->y);
  char print[255];
  ofSetColor(this->color);
  sprintf(print, "Winner!");
  type->drawStringCentered(print, 0, 0);
  ofPopMatrix();
}
