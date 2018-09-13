#include "Paddle.h"

Paddle::Paddle() {
  this->boundingBox = ofRectangle((ofGetWidth() / 2), (ofGetHeight() - 200), 85, 15);
  this->color = ofColor(80, 80, 80);
  this->damage = 15;
  this->isDamaged = false;
}

void Paddle::draw() {
  ofSetColor(this->color);
  ofDrawRectangle((ofGetMouseX() - (this->boundingBox.getWidth() / 2)), this->boundingBox.getY(), this->boundingBox.getWidth(), this->boundingBox.getHeight());
}

void Paddle::move() {
  this->boundingBox.setX(ofGetMouseX() - (this->boundingBox.getWidth() / 2));
}

ofRectangle* Paddle::getBoundingBox() {
  return &this->boundingBox;
}

ofRectangle* Paddle::getBoundingBoxLeft() {
  left = ofRectangle(this->boundingBox.getX(), this->boundingBox.getY(), (this->boundingBox.getWidth() - ((this->boundingBox.getWidth() / 3) * 2)), this->boundingBox.getHeight());
  return &left;
}

ofRectangle* Paddle::getBoundingBoxCenter() {
  center = ofRectangle(this->boundingBox.getX() + (this->boundingBox.getWidth() / 3), this->boundingBox.getY(), (this->boundingBox.getWidth() - ((this->boundingBox.getWidth() / 3) * 2)), this->boundingBox.getHeight());
  return &center;
}

ofRectangle* Paddle::getBoundingBoxRight() {
  right = ofRectangle((this->boundingBox.getX() + ((this->boundingBox.getWidth() / 3) * 2)), this->boundingBox.getY(), (this->boundingBox.getWidth() - ((this->boundingBox.getWidth() / 3) * 2)), this->boundingBox.getHeight());
  return &right;
}

void Paddle::handleDamage() {
  if (this->isDamaged) {
    this->color.set(80, 0, 0);
    this->damage--;
    if (this->damage<= 0) {
      this->color.set(80, 80, 80);
      this->damage = 15;
      this->isDamaged = false;
    }
  }
}

void Paddle::setIsDamaged() {
  this->isDamaged = true;
}

void Paddle::drawBoundingBox() {
  ofSetColor(255, 0, 0);
  ofDrawRectangle(this->left);
  ofDrawRectangle(this->center);
  ofDrawRectangle(this->right);
}
