#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(100, 100, 100);
	ofSetVerticalSync(true);
	
	//Connect to Port
	myTuio.connect(3333);
	
	//Assign Global TUIO Callback Functions
	ofAddListener(ofEvents().touchDown, this, &testApp::touchDown);
	ofAddListener(ofEvents().touchUp, this, &testApp::touchUp);
	ofAddListener(ofEvents().touchMoved, this, &testApp::touchMoved);

	ballIdx = 0;

	for (int i = 0; i < BALL_NUMBER; ++i)
	{
		ballList[i] = nullptr;
	}
}

//--------------------------------------------------------------
void testApp::update(){

	// 업데이트할 때마다 각각의 ball들이 화면 밖으로 나가는지 체크하고
	// 현재 속도에 따라서 위치 변화
	for (int i = 0; i < BALL_NUMBER; ++i)
	{
		if (ballList[i] != nullptr)
		{
			ballList[i]->checkBoundary();
			ballList[i]->update();
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	
	//render TUIO Cursors and Objects
	myTuio.drawCursors();
	myTuio.drawObjects();

	// 각각의 ball을 화면에 그림
	for (int i = 0; i < BALL_NUMBER; ++i)
	{
		if (ballList[i] != nullptr)
			ballList[i]->draw();
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}


void testApp::touchDown(ofTouchEventArgs & touch){
	// touch.id는 터치 이벤트가 발생할 때마다 1씩 계속 증가해서 해당 이벤트에 할당
	int tempIdx = touch.id % BALL_NUMBER;

	if (ballList[tempIdx] != nullptr)
	{
		// 만약 모듈러 연산의 결과로 얻어진 idx값에 이미 ball이 있을 경우 삭제
		// 화면의 ball 숫자 일정하게 유지 
		delete ballList[tempIdx];
		ballList[tempIdx] == nullptr;
	}

	// idx에 해당하는 ball 생성
	ballList[tempIdx] = new Ball(&ballList, touch.id, touch.x, touch.y);
	ballList[tempIdx]->init();
}

void testApp::touchUp(ofTouchEventArgs & touch){

	int tempIdx = touch.id % BALL_NUMBER;

	if (ballList[tempIdx] != nullptr)
	{
		// 터치가 종료되면 ball의 크기와 색 변화를 멈추고
		ballList[tempIdx]->stopIncreasing();

		// 임의의 속도를 할당
		ballList[tempIdx]->setVelocity();
	}
}

void testApp::touchMoved(ofTouchEventArgs & touch){
	
}

