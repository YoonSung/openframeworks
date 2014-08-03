#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {	
	
	ballCreater.startThread(true);

	ofSetFrameRate(60);
	ofBackground(100,100,100);
	ofSetVerticalSync(true);
	ofEnableSmoothing();
}

//--------------------------------------------------------------
void ofApp::update(){

	vector<Ball*> balls = ballCreater.getBallList();
	for(int i=0;i<balls.size();i++) {
		balls[i]->move();
	}
	checkCollision();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(100,100,100);

	vector<Ball*> balls = ballCreater.getBallList();
	for(int i=0;i<balls.size();i++) {
		ofColor(255,255,255,100);
		
		balls[i]->display();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::exit() {
	ballCreater.stopThread();
}

//
void ofApp::checkCollision(void) {

	vector<Ball*> balls = ballCreater.getBallList();

	for(int i=0;i<balls.size();i++) {
		for(int j=i+1;j<balls.size();j++) {
			float dx = balls[j]->x - balls[i]->x;
			float dy = balls[j]->y - balls[i]->y;
			float distance = ofDist(balls[i]->x,balls[i]->y,balls[j]->x,balls[j]->y);
			float minDist = balls[j]->diameter/2 + balls[i]->diameter/2;
			if (distance < minDist) {
				float angle = atan2(dy,dx);
				float targetX = balls[i]->x + cos(angle) * minDist;
				float targetY = balls[i]->y + sin(angle) * minDist;
				float ax = (targetX - balls[j]->x) * SPRING;
				float ay = (targetY - balls[j]->y) * SPRING;
				balls[i]->vx -= ax;
				balls[i]->vy -= ay;
				balls[j]->vx += ax;
				balls[j]->vy += ay;
			}
		}
	}
}