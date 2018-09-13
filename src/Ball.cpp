#include "Ball.h"

static const int SPEED = 14;
static const int BALLS = 6;
static const int COUNT = 100;

Ball::Ball() {
  this->boundingBox = ofRectangle((ofGetWidth()/2), ((ofGetHeight()/2) + 50), 15, 15);
  this->color = ofColor(100, 100, 100, 125);
  this->direction = ofRandom(-3, 3);
  this->speed = SPEED;
  this->count = COUNT;
  this->balls = BALLS;
  this->boundry = 100;
  this->serve = false;
  this->transition = false;
}

void Ball::draw() {
  ofSetColor(this->color);
  ofDrawRectangle(this->boundingBox.getX(), this->boundingBox.getY(), this->boundingBox.getWidth(), this->boundingBox.getHeight());
}

void Ball::move() {
  if (!this->serve) {
    //this->boundingBox.setX(ofGetMouseX());
    this->transition = false;
    this->color.set(100, 100, 100);
    this->boundingBox.setX(this->boundingBox.getX() + this->direction);
    this->boundingBox.setY(this->boundingBox.getY() + this->speed);
  }
}

void Ball::bouncePaddle(float dir) {
  this->direction = dir; 
  this->speed = -this->speed;
  this->increaseSpeed();
}

void Ball::bounceTopBottom() {
  this->speed *= -1;
}

void Ball::bounceSides() {
  this->direction *= -1;
}

void Ball::belowBoundry(ofSoundPlayer* sound) {
  if ((this->boundingBox.getY() + this->boundingBox.getHeight()) >= (ofGetHeight() + this->boundry)) {
    sound->play();
    this->setServe();
    this->resetSpeed();
  }
}

void Ball::increaseSpeed() {
  this->speed -= 0.05;
  if (this->speed <= -20) {
    this->speed = -20;
  }
}

ofRectangle* Ball::getBoundingBox() {
  return &this->boundingBox;
}

int Ball::getBalls() {
  return this->balls;
}

void Ball::setServe() {
  this->boundingBox.setX(ofGetWidth() / 2);
  this->boundingBox.setY((ofGetWidth() / 2) + 50);
  this->color.set(0, 0, 0, 0);
  this->direction = ofRandom(-3, 3);
  if (this->speed < 0) {
    this->speed *= -1;
  }
  this->serve = true;
}

void Ball::setServeCount(int level) {
  if (this->serve) {
    this->count--;
    if (this->count <= 0) {
      if (level == 0 || !this->transition) {
        this->balls--;
      }
      this->serve = false;
      this->count = COUNT;
    }
  }
}

void Ball::printCount(ofxCenteredTrueTypeFont* type) {
  if (this->serve) {
    char print[255];
    ofSetColor(125, 125, 125);
    if (this->count > 40) {
      sprintf(print, "Ready");
    } else {
      sprintf(print, "Go");
    }
    type->drawStringCentered(print, (ofGetWidth() / 2), (ofGetHeight() / 2));
  }
}

void Ball::setTransition() {
  this->transition = true;
}

void Ball::resetSpeed() {
  this->speed = SPEED;
}

void Ball::setBalls() {
  this->balls = BALLS;
}

float Ball::printValues() {
  return this->speed;
}
