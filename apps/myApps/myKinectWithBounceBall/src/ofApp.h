#pragma once

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "Ball.h"
#include "ObjectCreater.h"

#define MAX_DEVICES 2
#define MAX_NUMBER_OF_HAND 2

class ofApp : public ofBaseApp{
	ObjectCreater objectCreater;

public:
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);		
	
private:
	void checkCollision();
	void checkCollisionBetweenBalls();
	void checkCollisionFromRectangleBar();

	//kinect
	void checkCollisionFromHandBalls1();
	void handEvent(ofxOpenNIHandEvent & event);
	ofxOpenNI openNIDevice;
	Object* handBall1;
	Object* handBall2;
};
