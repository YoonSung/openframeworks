#ifndef _TEST_APP
#define _TEST_APP

#include "ofMain.h"
#include "ofxTuioClient.h"
#include "Ball.h"

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

	ofxTuioClient myTuio;
	
	void touchDown(ofTouchEventArgs & touch);
	void touchUp(ofTouchEventArgs & touch);
	void touchMoved(ofTouchEventArgs & touch);
	
	// ball을 관리하기 위한 list와 idx 선언
	std::array<Ball*, BALL_NUMBER> ballList;
	unsigned int ballIdx;
};

#endif
