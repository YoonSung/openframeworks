#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {	
	
	objectCreater.startThread(true);

	ofSetFrameRate(60);
	//ofBackground(100,100,100);
	ofSetVerticalSync(true);
	ofEnableSmoothing();

	//************************kinnect
	openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    
    // setup the hand generator
    openNIDevice.addHandsGenerator();
    
    // add all focus gestures (ie., wave, click, raise arm)
    openNIDevice.addAllHandFocusGestures();
    openNIDevice.setMaxNumHands(MAX_NUMBER_OF_HAND);
    
    openNIDevice.start();

	// hand event를 담당하는 리스너 등록
	ofAddListener(openNIDevice.handEvent, this, &ofApp::handEvent);

	handBall1 = new Ball();
	handBall1->setup(
			0,
			0,
			50, 
			0,
			SPRING, 
			GRAVITY, 
			FRICTION
	);
	handBall1->color = ofColor(255, 0, 0);

	/*
	handBall2 = new Ball();
	handBall2->setup(
			0,
			0,
			50, 
			0,
			SPRING, 
			GRAVITY, 
			FRICTION
	);
	handBall2->color = ofColor(0, 255, 0);
	*/

	handBall2 = objectCreater.getObjectList()[0];
}

//--------------------------------------------------------------
void ofApp::update(){

	//kinect update
	openNIDevice.update();

	vector<Object*> objects = objectCreater.getObjectList();
	for(int i=0;i<objects.size();i++) {
		objects[i]->move();
	}
	checkCollision();
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofPushMatrix();
		// draw debug (ie., image, depth, skeleton)
		//openNIDevice.drawDebug();
		openNIDevice.drawDepth();
    ofPopMatrix();

	int numHands = openNIDevice.getNumTrackedHands();
    printf("numHands = %d\n", numHands);
    // iterate through users
    for (int i = 0; i < numHands; i++){
        
        // get a reference to this user
        ofxOpenNIHand & hand = openNIDevice.getTrackedHand(i);
        
        // get hand position
        ofPoint & handPosition = hand.getPosition();
		Object* targetHandBall = nullptr;
		

		if ( i % 2 == 1 ) {
			targetHandBall = handBall1;
		} else {
			targetHandBall = handBall2;
		}

		if ( i == 1 ) {
			ofxOpenNIHand & hand1 = openNIDevice.getTrackedHand(0);
			ofxOpenNIHand & hand2 = openNIDevice.getTrackedHand(1);
			ofPoint & hand1Position = hand1.getPosition();
			ofPoint & hand2Position = hand2.getPosition();

			float distance = ofDist(hand1Position.x,hand1Position.y,hand2Position.x, hand2Position.y);

			printf("distance : %f\n", distance);
			if (distance < 65.0) {
				vector<Object*> objects = objectCreater.getObjectList();

				for(int i=1;i<objects.size();i++) {
					objects[i]->color = ofColor(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));
				}
			}
		}

		targetHandBall->x = handPosition.x;
		targetHandBall->y = handPosition.y;
    }
    ofPopMatrix();

	vector<Object*> objects = objectCreater.getObjectList();
	for(int i=0;i<objects.size();i++) {
		objects[i]->display();
	}

	handBall1->display();
	handBall2->display();
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
	checkCollisionFromHandBalls1();
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

void ofApp::checkCollisionFromHandBalls1()
{
	vector<Object*> objects = objectCreater.getObjectList();
	
	for(int i=1;i<objects.size();i++) {
		float dx = handBall1->x - objects[i]->x;
		float dy = handBall1->y - objects[i]->y;
		float distance = ofDist(objects[i]->x,objects[i]->y,handBall1->x,handBall1->y);
		float minDist = handBall1->diameter/2 + objects[i]->diameter/2;
		if (distance < minDist) {
			objects[i]->y = 1000;
		}
	}
}

void ofApp::handEvent(ofxOpenNIHandEvent & event)
{
	if (event.handStatus == HAND_TRACKING_STARTED)
	{
		printf("HAND_TRACKING_STARTED!!");
	}
}