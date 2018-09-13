#include "ofApp.h"
#include "Gamestate.h"
#include "Brick.h"
#include "Debris.h"
#include "Paddle.h"
#include "Ball.h"
#include "Scoreboard.h"
#include "GuardTower.h"

static bool rumble; //<---Beta
static bool playStageOneSong; //<---Beta
//static bool playDogSound; //<---Beta
//static bool resetTime; //<---Beta
//static bool playSirenSound; //<---Beta

void ofApp::setup() {
  ofSetBackgroundColor(0, 0, 0);
  ofHideCursor();
  this->initializeSound();

  this->whisper.play();
  this->lovers.play();
  this->glue.play();
  this->night.play();

  this->initializePrint();
  this->initializeBrickColors();
  this->brickWidth = 85;
  this->brickHeight = 40;
  this->brickY = 200;
  this->brickImg.load("image/brickImg.png");
  this->initializeStage();
  this->initializeGuardTowers();
  this->gamestate = new Gamestate();
  this->scoreboard = new Scoreboard();
  this->paddle = new Paddle();
  this->ball = new Ball();
  this->brickCount = 48;
  this->transitionCount = 100;
  this->transition = false;
  this->restartMusic = false;

  this->translateX = 0;
  this->translateY = 0;
}

void ofApp::initializeSound() {
  this->whisper.setMultiPlay(true);
  this->whisper.load("sound/mp3/carelesswhisper.mp3");
  this->lovers.setMultiPlay(true);
  this->lovers.load("sound/mp3/endedaslovers.mp3");
  this->glue.setMultiPlay(true);
  this->glue.load("sound/mp3/glue.mp3");
  this->night.setMultiPlay(true);
  this->night.load("sound/mp3/night.mp3");
  this->paddleSound.setMultiPlay(true);
  this->paddleSound.load("sound/wav/paddle.wav");
  this->wallSound.setMultiPlay(true);
  this->wallSound.load("sound/wav/wall.wav");
  this->lossSound.setMultiPlay(true);
  this->lossSound.load("sound/wav/loss.wav");
  this->brickOneSound.setMultiPlay(true);
  this->brickOneSound.load("sound/wav/brick01.wav");
  this->brickTwoSound.setMultiPlay(true);
  this->brickTwoSound.load("sound/wav/brick02.wav");
  this->digSound.setMultiPlay(true);
  this->digSound.load("sound/wav/dig.wav");
  this->creakSound.setMultiPlay(true);
  this->creakSound.load("sound/wav/creak.wav");
  this->fallingSound.setMultiPlay(true);
  this->fallingSound.load("sound/wav/falling.wav");
  this->explodeSound.setMultiPlay(true);
  this->explodeSound.load("sound/wav/explode.wav");
  this->quakeSound.setMultiPlay(true);
  this->quakeSound.load("sound/wav/quake.wav");
  this->gruntSound.setMultiPlay(true);
  this->gruntSound.load("sound/wav/grunt.wav");
  this->acabSound.setMultiPlay(true);
  this->acabSound.load("sound/wav/acab.wav");
  this->dogSound.setMultiPlay(true);
  this->dogSound.load("sound/wav/dog.wav");
}

void ofApp::initializePrint() {
  this->parklane.load("font/parklane.ttf", 150, true, true, true);
  this->parklaneTwo.load("font/parklane.ttf", 60, true, true, true);
  this->billy.load("font/billy.ttf", 20, true, true, true);
  this->punishment.load("font/punishment.otf", 50, true, true, true);
}

void ofApp::initializeBrickColors() {
  this->brickOneColor = ofColor(255, 255, 255);
  this->brickTwoColor = ofColor(200, 200, 200);
  this->brickThreeColor = ofColor(150, 150, 150);
  this->brickFourColor = ofColor(100, 100, 100);
}

void ofApp::initializeStage() {
  this->buffer = ofBufferFromFile("stage/stage01.txt");
  this->initializeBricks(buffer);
  this->buffer = ofBufferFromFile("stage/stage02.txt");
  this->initializeBricks(buffer);
  this->buffer = ofBufferFromFile("stage/stage03.txt");
  this->initializeBricks(buffer);
}

void ofApp::initializeBricks(ofBuffer buffer) {
  for (auto line: buffer.getLines()) {
    this->data.push_back(line);
  }
  for (unsigned i = 0; i < data.size(); ++i) {
    for (unsigned j = 0; j < data.at(i).size(); ++j) {
      string character = ofToString(data.at(i).at(j));
      if (character == "a") {
        this->brickPosition.push_back(new Brick((j * this->brickWidth), ((i * this->brickHeight) + this->brickY), this->brickWidth, this->brickHeight, this->brickOneColor, &this->brickImg, A, 1, 2));
      } else if (character == "b") {
        this->brickPosition.push_back(new Brick((j * this->brickWidth), ((i * this->brickHeight) + this->brickY), this->brickWidth, this->brickHeight, this->brickTwoColor, &this->brickImg, B, 2, 4));
      } else if (character == "c") {
        this->brickPosition.push_back(new Brick((j * this->brickWidth), ((i * this->brickHeight) + this->brickY), this->brickWidth, this->brickHeight, this->brickThreeColor, &this->brickImg, C, 3, 6));
      } else if (character == "d") {
        this->brickPosition.push_back(new Brick((j * this->brickWidth), ((i * this->brickHeight) + this->brickY), this->brickWidth, this->brickHeight, this->brickFourColor, &this->brickImg, D, 4, 8));
      }
    }
  }
  this->bricks.push_back(brickPosition);
  this->data.clear();
  this->brickPosition.clear();
}

void ofApp::initializeGuardTowers() {
  for (int i = 0; i < 2; ++i) {
    guardTower[i] = new GuardTower();
  }
}

void ofApp::update() {
  if (this->state == TITLE) {
    this->updateTitle();
  } else if (this->state == PLAY) {
    this->updatePlay();
  }
}

void ofApp::draw() {
  if (this->state == TITLE) {
    this->drawTitle();
  } else if (this->state == PLAY) {
    if (this->transition) {
      this->drawTransition();
    } else {
      this->drawPlay();
    }
  } else if (this->state == LOSE) {
    this->gamestate->lose(&this->parklaneTwo);
  } else if (this->state == WIN) {
    this->gamestate->win(&this->parklaneTwo);
  }

  // Print Values

  //ofSetColor(255, 255, 255);
  //ofDrawBitmapString("ds: ", 20, 120);
  //ofDrawBitmapString(ofToString(this->debrisSystem.empty()), 80, 120);
  //for (unsigned i = 0; i < this->bricks.at(this->stage).size(); ++i) {
  //  ofSetColor(255, 255, 255);
  //  ofDrawBitmapString("resist: ", 20, 120);
  //  ofDrawBitmapString(ofToString(this->bricks.at(this->stage).at(i)->printValues()), 80, 120);
  //}
  //for (unsigned i = 0; i < this->debrisSystem.size(); ++i) {
  //  ofSetColor(255, 255, 255);
  //  ofDrawBitmapString("cmplt: ", 20, 120);
  //  ofDrawBitmapString(ofToString(this->debrisSystem.at(i)->getStatus()), 80, 120);
  //}
}

void ofApp::updateTitle() {
  this->updateMusic();
}

void ofApp::updatePlay() {
  //if (!playSirenSound) { //<---Beta
  //  playSirenSound = true;
  //  this->acabSound.play();
  //}
  //if (!resetTime) { //<---Beta
  //  resetTime = true;
  //  ofResetElapsedTimeCounter();
  //}
  //if (ofGetElapsedTimef() > 10) { //<---Beta
  //  if (!playDogSound) {
  //    playDogSound = true;
  //    this->dogSound.play();
  //  }
  //}

  if (this->transition) {
    this->handleTransition();
  }
  this->handleMusic();
  this->handleSoundEffects();
  this->updatePaddle();
  this->updateBall();
  this->updateBricks();
  this->updateDebris();
  this->updateGuardTowers();
}

void ofApp::drawTitle() {
  this->gamestate->title(&this->parklane);
  this->gamestate->subTitle(&this->billy);
  this->drawGuardTowers();
}

void ofApp::drawTransition() {
  this->gamestate->transition(this->stage, &this->parklaneTwo);
}

void ofApp::drawPlay() {
  this->drawScoreboard();
  ofPushMatrix();
  ofTranslate(this->translateX, this->translateY);
  this->drawBricks();
  this->drawPaddle();
  this->drawBall();
  this->drawDebris();
  this->drawGuardTowers();
  ofPopMatrix();
}

void ofApp::updateMusic() {
  this->whisper.setVolume(0.5f);
  this->lovers.setVolume(0.0f);
  this->glue.setVolume(0.0f);
  this->night.setVolume(0.0f);
  this->updateGuardTowers();
}

void ofApp::updatePaddle() {
  this->paddle->move();
  this->handleBrickPaddleCollision();
  this->paddle->handleDamage();
}

void ofApp::updateBall() {
  this->handleBallwallSoundCollision();
  if (this->brickCount > 0) {
    this->ball->belowBoundry(&this->lossSound);
  }
  this->handleBallPaddleCollision();
  if (!this->transition) {
    if (this->ball->getBalls() > 0) {
      if (this->brickCount > 0) {
        this->ball->move();
      }
    } else {
      this->state = LOSE; //<--- Game Over
    }
  }
  this->ball->setServeCount(this->stage);
}

void ofApp::updateBricks() {
  for (unsigned i = 0; i < this->bricks.at(this->stage).size(); ++i) {
    this->bricks.at(this->stage).at(i)->backupBumpCheck();
    this->bricks.at(this->stage).at(i)->bumpUp();
    this->bricks.at(this->stage).at(i)->bumpDown();
  }
  this->handleStageChange();
  this->handleBallBrickCollision();
  this->terminateBricks();
}

void ofApp::updateDebris() {
  for (unsigned i = 0; i < this->debrisSystem.size(); ++i) {
    this->debrisSystem.at(i)->explode();
    if (this->debrisSystem.at(i)->getStatus()) {
      this->debrisSystem.clear();
    }
  }
}

void ofApp::updateGuardTowers() {
  for (int i = 0; i < 2; ++i) {
  this->guardTower[i]->move();
  this->guardTower[i]->atBoundry();
  }
}

void ofApp::drawScoreboard() {
  this->scoreboard->drawBalls(this->ball->getBalls());
  this->scoreboard->printBalls(&this->punishment);
  this->scoreboard->printStage(&this->punishment, this->stage + 1);
  this->scoreboard->printScore(&this->punishment);
  //for (unsigned i = 0; i < this->bricks.at(this->stage).size(); ++i) {
  //  if (this->bricks.at(this->stage).at(i)->getCondition() != FIRST) {
  //    this->scoreboard->drawWorth(this->bricks.at(this->stage).at(i)->getBoundingBox(), this->bricks.at(this->stage).at(i)->getWorth(), &this->punishment);
  //  }
  //}
}

void ofApp::drawBricks() {
  for (unsigned i = 0; i < this->bricks.at(this->stage).size(); ++i) {
    this->bricks.at(this->stage).at(i)->draw();
  }
}

void ofApp::drawPaddle() {
  //this->paddle->drawBoundingBox();
  this->paddle->draw();
}

void ofApp::drawBall() {
  if (this->brickCount > 0) {
    this->ball->draw();
  }
  if (this->ball->getBalls() > 1) {
    this->ball->printCount(&this->punishment);
  }
}

void ofApp::drawDebris() {
  for (unsigned i = 0; i < this->debrisSystem.size(); ++i) {
    this->debrisSystem.at(i)->draw();
  }
}

void ofApp::drawGuardTowers() {
  for (int i = 0; i < 2; ++i) {
    this->guardTower[i]->draw();
  }
}

void ofApp::handleTransition() {
  this->transitionCount--;
  if (this->transitionCount <= 0) {
    this->ball->setTransition();
    this->ball->setServe();
    this->transition = false;
    this->transitionCount = 100;
  }
}

void ofApp::handleMusic() {
  this->whisper.stop();
  if (this->stage == ONE) {
    if (!playStageOneSong) {
      playStageOneSong = true;
      this->restartMusic = true;
    }
    this->setMusicPosition(this->night);
    this->night.setVolume(1.0f);
  } else if (this->stage == TWO) {
    this->night.stop();
    this->setMusicPosition(this->lovers);
    this->lovers.setVolume(1.0f);
  } else if (this->stage == THREE) {
    this->lovers.stop();
    this->setMusicPosition(this->glue);
    this->glue.setVolume(0.5f);
  }
}

void ofApp::setMusicPosition(ofSoundPlayer sound) {
  if (this->restartMusic) {
    sound.setPosition(0.0f);
    this->restartMusic = false;
  }
}

void ofApp::handleSoundEffects() {
  for (unsigned i = 0; i < this->bricks.at(this->stage).size(); ++i) {
    if (this->bricks.at(this->stage).at(i)->getCondition() == THIRD && !this->bricks.at(this->stage).at(i)->getAnimation()) {
      if (this->bricks.at(this->stage).at(i)->getType() == A) {
        this->digSound.play();
      } else if (this->bricks.at(this->stage).at(i)->getType() == B) {
        this->creakSound.play();
      } else if (this->bricks.at(this->stage).at(i)->getType() == C) {
        this->fallingSound.play();
      }
    }
  }
}

void ofApp::handleBallPaddleCollision() {
  if (this->ball->getBoundingBox()->intersects(*this->paddle->getBoundingBoxLeft())) {
    this->paddleSound.play();
    this->ball->bouncePaddle(ofRandom(-3, -8));
  } else if (this->ball->getBoundingBox()->intersects(*this->paddle->getBoundingBoxCenter())) {
    this->paddleSound.play();
    this->ball->bouncePaddle(ofRandom(-2, 2));
  } else if (this->ball->getBoundingBox()->intersects(*this->paddle->getBoundingBoxRight())) {
    this->paddleSound.play();
    this->ball->bouncePaddle(ofRandom(3, 8));
  } 
}

void ofApp::handleBallwallSoundCollision() {
  if ((this->state == TITLE && this->ball->getBoundingBox()->getY() <= 0) || (this->state == TITLE && (this->ball->getBoundingBox()->getY() + this->ball->getBoundingBox()->getHeight()) >= ofGetHeight())) {
    this->ball->bounceTopBottom();
  } else if (this->state != TITLE && this->ball->getBoundingBox()->getY() <= 0) {
    this->wallSound.play();
    this->ball->bounceTopBottom();
  } else if ((this->state == TITLE && this->ball->getBoundingBox()->getX() <= 0) ||(this->state == TITLE && (this->ball->getBoundingBox()->getX() + this->ball->getBoundingBox()->getHeight()) >= ofGetWidth())) {
    this->ball->bounceSides();
  } else if (this->ball->getBoundingBox()->getX() <= 0 || (this->ball->getBoundingBox()->getX() + this->ball->getBoundingBox()->getHeight()) >= ofGetWidth()) {
    this->wallSound.play();
    this->ball->bounceSides();
  }
}

void ofApp::handleBallBrickCollision() {
  for (unsigned i = 0; i < this->bricks.at(this->stage).size(); ++i) {
    if (!this->transition) {
      if (this->ball->getBoundingBox()->intersects(this->bricks.at(this->stage).at(i)->getBoundingBox()) && this->bricks.at(this->stage).at(i)->getCondition() == FIRST) {
        this->ball->bounceTopBottom();
        this->bricks.at(this->stage).at(i)->setResistance();
        this->bricks.at(this->stage).at(i)->setBrightness();
        if ((this->ball->getBoundingBox()->getY() - this->ball->getBoundingBox()->getHeight()) >= this->bricks.at(this->stage).at(i)->getBoundingBox().getY()) {
          //this->bricks.at(this->stage).at(i)->setBump();
          this->brickOneSound.play();
          this->brickTwoSound.play();
        } else {
          this->brickTwoSound.play();
        }
      }
    }
  }
}

void ofApp::handleBrickPaddleCollision() {
  for (unsigned i = 0; i < this->bricks.at(this->stage).size(); ++i) {
    if (this->bricks.at(this->stage).at(i)->getType() == C && this->bricks.at(this->stage).at(i)->getBoundingBox().intersects(*this->paddle->getBoundingBox())) {
      this->gruntSound.play();
      this->scoreboard->setScore(-1); //<--- CLEAN UP
      this->paddle->setIsDamaged();
    }
  }
}

void ofApp::terminateBricks() {
  for (unsigned i = 0; i < this->bricks.at(this->stage).size(); ++i) {
    if (this->bricks.at(this->stage).at(i)->getCondition() == SECOND) {
      this->setScore(this->bricks.at(this->stage).at(i)->getType(), this->bricks.at(this->stage).at(i)->getWorth());
      this->bricks.at(this->stage).at(i)->setCondition(THIRD);
      this->brickCount--;
    } else if (this->bricks.at(this->stage).at(i)->getCondition() == THIRD) {
      this->bricks.at(this->stage).at(i)->playAnimation();
      if (this->bricks.at(this->stage).at(i)->getType() == D) {
        this->handleExplosion(true, this->bricks.at(this->stage).at(i)->getBoundingBox());
        this->bricks.at(this->stage).at(i)->setCondition(FOURTH);
      }
    } 
  }
}

void ofApp::handleExplosion(bool init, ofRectangle brick) {
  if (init) {
    this->debrisSystem.push_back(new Debris(brick, &this->brickImg));
    init = false;
    this->explodeSound.play();
    for (unsigned i = 0; i < this->debrisSystem.size(); ++i) {
      this->debrisSystem.at(i)->initialize();
    }
  }
}

void ofApp::setScore(int type, int worth) {
  for (unsigned i = 0; i < this->bricks.at(this->stage).size(); ++i) {
    if (this->bricks.at(this->stage).at(i)->getCondition() == SECOND) {
      if (this->bricks.at(this->stage).at(i)->getType() == type) {
        this->scoreboard->setScore(worth);
      }
    }
  }
}

void ofApp::handleStageChange() {
  int thisStage = this->stage;
  for (unsigned i = 0; i < this->bricks.at(this->stage).size(); ++i) {
    if (this->bricks.at(this->stage).at(i)->getCondition() == FOURTH && this->debrisSystem.empty()) {
      this->bricks.at(this->stage).erase(this->bricks.at(this->stage).begin() + i);
      //if (this->bricks.at(this->stage).empty()) {
      if (this->brickCount <= 0) { //<---Beta (hell yeah!)
        this->restartMusic = true;
        thisStage++;
        this->brickCount = 48;
        this->stage = static_cast<Stage>(thisStage);
        if (this->stage > 2) {
          this->stage = THREE;
          this->state = WIN;
        }
        this->transition = true;
        this->ball->resetSpeed();
      }
    }
  }
}

void ofApp::keyPressed(int key) {
  if (key == '1') {
    this->transition = true;
    this->stage = ONE;
    this->brickCount = 48;
  } else if (key == '2') {
    this->transition = true;
    this->stage = TWO;
    this->brickCount = 48;
  } if (key == '3') {
    this->transition = true;
    this->stage = THREE;
    this->brickCount = 48;
  }

  if (this->state == TITLE && key == ' ') {
    //this->acabSound.play();
    this->transition = true;
    this->state = PLAY;
  } else if ((this->state == WIN && key == ' ') || (this->state == LOSE && key == ' ')) {
    this->bricks.clear();
    this->initializeStage();
    this->ball->setBalls();
    this->scoreboard->setScore(-this->scoreboard->getScore());
    this->state = TITLE;
  }

  if (key == 'x') { //<---Beta
    this->translateX += ofRandom(-10, 10);
    this->translateY += ofRandom(-10, 10);
    this->testSound();
  }

}

void ofApp::keyReleased(int key) {
  if (key == 'x') { //<---Beta
    this->translateX = 0;
    this->translateY = 0;
  }
}

void ofApp::testSound() { //<---Beta
  if (!rumble) {
    rumble = true;
    this->quakeSound.play();
  }
}
