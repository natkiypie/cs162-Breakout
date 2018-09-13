#pragma once
#include "ofMain.h"
#include <vector>
#include "Gamestate.h"
#include "Brick.h"
#include "Debris.h"
#include "Paddle.h"
#include "Ball.h"
#include "Scoreboard.h"
#include "GuardTower.h"

enum GameState {TITLE, PLAY, WIN, LOSE}; //<---- add Pause state
enum Stage {ONE, TWO, THREE};

class ofApp : public ofBaseApp {

	public:
		void setup();
    void initializeSound();
    void initializePrint();
    void initializeBrickColors();
    void initializeStage();
    void initializeBricks(ofBuffer buffer);
    void initializeGuardTowers();
		void update();
		void draw();
    void updateTitle();
    void updatePlay();
    void drawTitle();
    void drawTransition();
    void drawPlay();
    void updateMusic();
    void updatePaddle();
    void updateBall();
    void updateBricks();
    void updateDebris();
    void updateGuardTowers();
    void drawScoreboard();
    void drawBricks();
    void drawPaddle();
    void drawBall();
    void drawDebris();
    void drawGuardTowers();
    void handleTransition();
    void handleMusic();
    void setMusicPosition(ofSoundPlayer sound);
    void handleSoundEffects();
    void handleBallPaddleCollision();
    void handleBallwallSoundCollision();
    void handleBallBrickCollision();
    void handleBrickPaddleCollision();
    void terminateBricks();
    void handleExplosion(bool init, ofRectangle brick);
    void setScore(int type, int worth);
    void handleStageChange();
		void keyPressed(int key);

    void testSound();

  private:
    Stage stage;
    GameState state;
    ofSoundPlayer whisper, glue, lovers, night, paddleSound, wallSound, lossSound, brickOneSound, brickTwoSound, digSound, creakSound, fallingSound, explodeSound, quakeSound, gruntSound, acabSound, dogSound;
    ofxCenteredTrueTypeFont parklane, parklaneTwo, billy, punishment;
    ofColor brickOneColor, brickTwoColor, brickThreeColor, brickFourColor;
    int brickWidth;
    int brickHeight;
    int brickY;
    ofImage brickImg;
    ofBuffer buffer;
    vector<string> data;
    vector< vector<Brick*> > bricks;
    vector<Brick*> brickPosition;
    vector<Debris*> debrisSystem;
    Gamestate* gamestate;
    Scoreboard* scoreboard;
    Paddle* paddle;
    Ball* ball;
    int brickCount;
    int transitionCount;
    bool transition;
    bool restartMusic;
    GuardTower* guardTower[2];
    

    int translateX;
    int translateY;

		void keyReleased(int key);
		//void mouseMoved(int x, int y );
		//void mouseDragged(int x, int y, int button);
		//void mousePressed(int x, int y, int button);
		//void mouseReleased(int x, int y, int button);
		//void mouseEntered(int x, int y);
		//void mouseExited(int x, int y);
		//void windowResized(int w, int h);
		//void dragEvent(ofDragInfo dragInfo);
		//void gotMessage(ofMessage msg);
};
