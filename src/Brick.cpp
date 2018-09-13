#include "Brick.h"

Brick::Brick(int x, int y, int width, int height, ofColor color, ofImage* image, Type type, int resistance, int worth) {
  this->boundingBox = new ofRectangle(x, y, width, height);
  this->color = color;
  this->image = image;
  this->type = type;
  this->resistance = resistance;
  this->worth = worth;
  this->condition = FIRST;
  this->degree = 0;
  this->alpha = 255;
  this->bump = 0;
  this->bumpVelocity = 1;
  this->bumpMax = 6;
  this->collision = false;
  this->bumpStart = false;
  this->bumpStop = false;
  this->animation = false;
}

void Brick::draw() {
  ofPushMatrix();
  ofTranslate(this->boundingBox->getX(), this->boundingBox->getY());
  ofRotateDeg(this->degree);
  ofSetColor(this->color, this->alpha);
  this->image->draw(0, 0, this->boundingBox->getWidth(), this->boundingBox->getHeight());
  ofPopMatrix();
}

void Brick::setBump() {
  if (!this->type == A) {
    if (this->resistance > 0) { 
      this->bumpStart = true;
    }
  } else {
    this->bumpStart = true;
  }
}

void Brick::bumpUp() {
  if (this->bumpStart) {
    this->boundingBox->setY(this->boundingBox->getY() + this->bump);
    this->bump -= this->bumpVelocity;
    if (this->bump <= -this->bumpMax) {
      this->bump = 0;
      this->bumpStop = true;
      this->bumpStart = false;
    }
  }
}

void Brick::bumpDown() {
  if (this->bumpStop) {
    this->boundingBox->setY(this->boundingBox->getY() + this->bump);
    this->bump += this->bumpVelocity;
    if (this->bump >= this->bumpMax) {
      this->bumpStop = false;
      this->bump = 0;
    }
  }
}

void Brick::backupBumpCheck() {
  if (this->bump >= this->bumpMax) {
    this->bumpStop = false;
    this->bump = 0;
    this->bumpVelocity = 0;
  }
}

void Brick::playAnimation() {
  if (this->type == A) {
    this->fade();
  } else if (this->type == B) {
    this->hinge();
  } else if (this->type == C) {
    this->drop();
  } else if (this->type == D) {
    this->disappear();
  }
  this->animation = true;
}

void Brick::fade() {
  this->alpha -= 8;
  if (this->alpha <= 0) {
    this->condition = FOURTH;
  }
}

void Brick::hinge() {
  this->degree += 2;
  if (this->degree >= 70) {
    this->degree = 70;
    this->alpha -= 4;
    this->boundingBox->setY(this->boundingBox->getY() + 12);
    if (this->boundingBox->getY() >= (ofGetHeight() - (ofGetHeight() / 4))) {
      this->condition = FOURTH;
    }
  }
}

void Brick::drop() {
  this->boundingBox->setY(this->boundingBox->getY() + 12);
  if (this->boundingBox->getY() >= ofGetHeight()) {
    this->condition = FOURTH;
  }
}

void Brick::disappear() {
  this->color.set(0, 0, 0, 0);
}

ofRectangle Brick::getBoundingBox() {
  return *this->boundingBox;
}

Type Brick::getType() {
  return this->type;
}

int Brick::getWorth() {
  return this->worth;
}

int Brick::getResistance() {
  return this->resistance;
}

Condition Brick::getCondition() {
  return this->condition;
}

bool Brick::getBumpStop() {
  return this->bumpStop;
}

bool Brick::getAnimation() {
  return this->animation;
}

void Brick::setResistance() {
  this->resistance--;
  if (this->resistance == 0) {
    this->condition = SECOND;
  }
}

void Brick::setCondition(Condition condition) {
  this->condition = condition;
}

void Brick::setBrightness() {
  if (this->type == B) {
    this->color.setBrightness(this->color.getBrightness() + 30);
  } else if (this->type == C || this->type == D) {
    this->color.setBrightness(this->color.getBrightness() + 30);
  }
}

int Brick::printValues() {
  return this->resistance;
}
