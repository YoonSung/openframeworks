#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {	
	
	objectCreater.startThread(true);

	ofSetFrameRate(60);
	ofBackground(100,100,100);
	ofSetVerticalSync(true);
	ofEnableSmoothing();
}

//--------------------------------------------------------------
void ofApp::update(){

	vector<Object*> objects = objectCreater.getObjectList();
	for(int i=0;i<objects.size();i++) {
		objects[i]->move();
	}
	checkCollision();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(100,100,100);

	vector<Object*> objects = objectCreater.getObjectList();
	for(int i=0;i<objects.size();i++) {
		ofColor(255,255,255,100);
		
		objects[i]->display();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	RectangleBar* bar = (RectangleBar*)objectCreater.getObjectList()[0];

	if (key == 356)
		bar->moveLeft();
	else if (key == 358)
		bar->moveRight();
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
	objectCreater.stopThread();
}

//
void ofApp::checkCollision(void) {
	checkCollisionBetweenBalls();
	checkCollisionFromRectangleBar();
}

void ofApp::checkCollisionBetweenBalls()
{
	vector<Object*> objects = objectCreater.getObjectList();

	for(int i=1;i<objects.size();i++) {
		for(int j=i+1;j<objects.size();j++) {
			float dx = objects[j]->x - objects[i]->x;
			float dy = objects[j]->y - objects[i]->y;
			float distance = ofDist(objects[i]->x,objects[i]->y,objects[j]->x,objects[j]->y);
			float minDist = objects[j]->diameter/2 + objects[i]->diameter/2;
			if (distance < minDist) {
				float angle = atan2(dy,dx);
				float targetX = objects[i]->x + cos(angle) * minDist;
				float targetY = objects[i]->y + sin(angle) * minDist;
				float ax = (targetX - objects[j]->x) * SPRING;
				float ay = (targetY - objects[j]->y) * SPRING;
				objects[i]->vx -= ax;
				objects[i]->vy -= ay;
				objects[j]->vx += ax;
				objects[j]->vy += ay;
			}
		}
	}
}

void ofApp::checkCollisionFromRectangleBar()
{
	vector<Object*> objects = objectCreater.getObjectList();

	//printf("size : %d\n", objects.size());
	if (objects.size() == 0)
		return;

	//RectangleBar* bar = (RectangleBar*)objects[0];
	RectangleBar* bar = (RectangleBar*)objects[0];

	float barX = bar->x;
	float barY = bar->y;

	float barWidth = bar->m_width;
	float barHeight = bar->m_height;

	for(int i=1;i<objects.size();i++) {
		float dx = objects[i]->x;
		float dr = objects[i]->diameter;
		float dy = objects[i]->y;

		if ( (dy+dr/2 >= barY) && (dy+dr/2 <= barY + 20) ) {
			if (barX - dr/2 < dx && dx < barX + barWidth + dr/2) {
				objects[i]->vx *= -2;
				objects[i]->vy *= -2;
			}
		}
		
	}
}