#include "ofApp.h"

#define MAX_RADIUS 100
#define MIN_RADIUS 10

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(50,50,50);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	Circle * circle;
	for(int i=0;i<circles.size();i++) {
		circle = circles[i];
		ofSetColor(circle->getRedColorIntensity(), circle->getGreenColorIntensity(), circle->getBlueColorIntensity(), circle->getAlphaColorIntensity());
		ofCircle(circle->getPoint(), circle->getRadius());
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
	//mousePoint.x = x;
	//mousePoint.y = y;

	Circle* circle;
	int r;
	int g;
	int b;
	int a;

	if (button==0) {
		circle = new Circle(ofPoint(x,y));
		circle->setRadius(rand() % (MAX_RADIUS - MIN_RADIUS) + MIN_RADIUS);

		r = rand() % 255;
		g = rand() % 255;
		b = rand() % 255;
		a = rand() % 255;
		circle->setColor(r, g, b, a);
		circles.push_back(circle);
	} else if (button==2) {
		//circles.pop_back();
		if (circles.size() == 0)
			return;

		circles.erase(circles.begin()+getShortestDistanceCircleIndexFromPoint(x, y));
	}
	
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

int ofApp::getShortestDistanceCircleIndexFromPoint(int x, int y)
{
	int shortestDistanceCircleIndex = 0;
	Circle* shortestDistanceCircle = circles[0];
	Circle* currentCircle = NULL;

	ofPoint clickPoint = ofPoint(x, y);	

	ofPoint distancePoint = shortestDistanceCircle->getPoint() - clickPoint;
	int shortestDistance = sqrt(distancePoint.x * distancePoint.x + distancePoint.y * distancePoint.y);  
	int currentDistance = shortestDistance;

	for(int i=1;i<circles.size();i++) {
		distancePoint = circles[i]->getPoint() - clickPoint;
		currentDistance = sqrt(distancePoint.x * distancePoint.x + distancePoint.y * distancePoint.y);  
		cout << "distance[" <<i<<"] : " << currentDistance << endl;
		if (currentDistance < shortestDistance) {
			shortestDistanceCircleIndex = i;
			shortestDistance = currentDistance;
			shortestDistanceCircle = currentCircle;
		}
	}

	return shortestDistanceCircleIndex;
}