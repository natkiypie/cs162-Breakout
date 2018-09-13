#include "Debris.h"

Debris::Debris(ofRectangle brick, ofImage* image) {
  this->brick = brick;
  this->damp = -0.5;
  this->speed = 0.8;
  this->alpha = 255;
  this->complete = false;
  this->image = image;
  this->color = ofColor(200, 200, 200);
}

void Debris::initialize() {
  for (int k = 0; k < 10; ++k) {
    this->velocity.push_back(vel[k]);
    this->xModifier.push_back(xMod[k]);
    this->acceleration.push_back(accl[k]);
  }
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 5; ++j) {
      this->debris = new ofRectangle(((j * 17) + this->brick.getX()), ((i * 20) + this->brick.getY()), 17, 20);
      this->debrisSystem.push_back(debris);
    }
  }
}

void Debris::draw() {
  for (unsigned i = 0; i < this->debrisSystem.size(); ++i) {
    ofSetColor(this->color);
    ofDrawRectangle(*this->debrisSystem.at(i));
    this->image->draw(*this->debrisSystem.at(i));
  }
}

void Debris::explode() {
  for (unsigned i = 0; i < this->debrisSystem.size(); ++i) {
    this->debrisSystem.at(i)->setX(this->debrisSystem.at(i)->getX() + this->xModifier.at(i));
    this->debrisSystem.at(i)->setY(this->debrisSystem.at(i)->getY() + this->velocity.at(i));
    this->velocity.at(i) += this->acceleration.at(i);
    this->acceleration.at(i) += speed;
    if (this->acceleration.at(i) >= speed) {
      this->acceleration.at(i) = speed;
    }
    if ((this->debrisSystem.at(i)->getY() + this->debrisSystem.at(i)->getHeight()) >= ofGetHeight()) {
      this->debrisSystem.at(i)->setY(this->debrisSystem.at(i)->getY() - this->debrisSystem.at(i)->getHeight());
      this->velocity.at(i) *= this->damp;
    }
  }
  this->alpha -= 3;
  if (this->alpha <= 0) {
    this->debrisSystem.clear();
    this->velocity.clear();
    this->xModifier.clear();
    this->acceleration.clear();
    this->complete = true;
  }
}

bool Debris::getStatus() {
  return this->complete;
}
