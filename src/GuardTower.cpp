#include "GuardTower.h"

GuardTower::GuardTower() {
  this->color = ofColor(255, 255, 0, 20);
  this->x = ofRandom(0, ofGetWidth());
  this->y = (ofGetHeight() + ofRandom(-480, 480));
  this->radius = 150;
  this->direction = ofRandom(-5, 5);
  this->speed = ofRandom(2, 6);
  this->leftBoundry = -600;
  this->rightBoundry = (ofGetWidth() + 600);
  this->topBoundry = -600;
  this->bottomBoundry = (ofGetHeight() + 600);
}

void GuardTower::draw() {
  ofPushMatrix();
  ofTranslate(this->x, this->y);
  ofSetColor(this->color);
  ofSetCircleResolution(80);
  ofDrawCircle(0, 0, this->radius);
  ofPopMatrix();
}

void GuardTower::move() {
  this->x += this->direction;
  this->y += this->speed;
}

void GuardTower::atBoundry() {
  if (this->x < this->leftBoundry || this->x > this->rightBoundry) {
    this->direction *= -1;
  } else if (this->y < this->topBoundry || this->y > this->bottomBoundry) {
    this->speed *= -1;
  }
}
