#include "ImageExample.h"

//--------------------------------------------------------------
void ImageExample::setup(){
	ofSetFrameRate(60);
	// Connect
	MyClient.connect(3333);

	ofAddListener(ofEvents().touchDown, this, &ImageExample::touchDown);
	ofAddListener(ofEvents().touchMoved, this, &ImageExample::touchMoved);
	ofAddListener(ofEvents().touchUp, this, &ImageExample::touchUp);

	m_MyImage.loadImage("sally.png");

	// 해제는 어디서 하죠?
	m_OpenGLRenderer = new ofGLRenderer();

	m_ImgPositionX = 100.0;
	m_ImgPositionY = 100.0;
	m_ImgWidth = 200.0;
	m_ImgHeight = 200.0;
	m_ImgRotateAngle = 120.0;
}

//--------------------------------------------------------------
void ImageExample::update(){

}

//--------------------------------------------------------------
void ImageExample::draw(){

 	//MyClient.drawCursors();
 	//MyClient.drawObjects();
	
	m_OpenGLRenderer.pushMatrix();
		m_OpenGLRenderer.translate(m_ImgPositionX, m_ImgPositionY);
		m_OpenGLRenderer.rotateZ(m_ImgRotateAngle);

		m_OpenGLRenderer.draw(m_MyImage, -m_ImgWidth / 2, -m_ImgHeight / 2, 0.0,
				m_ImgWidth, m_ImgHeight,
				0.0, 0.0,
				m_MyImage.getWidth(), m_MyImage.getHeight());

	m_OpenGLRenderer.popMatrix();
}

//--------------------------------------------------------------
void ImageExample::keyPressed(int key){

}

//--------------------------------------------------------------
void ImageExample::keyReleased(int key){

}

//--------------------------------------------------------------
void ImageExample::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ImageExample::mouseDragged(int x, int y, int button){
	m_ImgPositionX = x;
	m_ImgPositionY = y;
}

//--------------------------------------------------------------
void ImageExample::mousePressed(int x, int y, int button){
	m_ImgPositionX = x;
	m_ImgPositionY = y;
}

//--------------------------------------------------------------
void ImageExample::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ImageExample::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ImageExample::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ImageExample::dragEvent(ofDragInfo dragInfo){ 
	
}

void ImageExample::touchDown( ofTouchEventArgs & touch )
{
	TUIO::TuioCursor* cursor1 = nullptr;
	TUIO::TuioCursor* cursor2 = nullptr;
	TUIO::TuioCursor* cursor3 = nullptr;

	// move image
	if ( MyClient.client->getTuioCursors().size() == 1 )
	{
		m_ImgPositionX = touch.x * WINDOW_WIDTH;
		m_ImgPositionY = touch.y * WINDOW_HEIGHT;
	}

	// up scale / down scale
	if ( MyClient.client->getTuioCursors().size() == 2 )
	{
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			default:
				break;
			}
		}

		// 방어코드
		if (cursor1 == nullptr || cursor2 == nullptr)
		{
			return;
		}

		m_ImgWidth = abs( cursor1->getX() - cursor2->getX() ) * WINDOW_WIDTH * 2;
		m_ImgHeight = abs( cursor1->getY() - cursor2->getY() ) * WINDOW_HEIGHT * 2;
	}

	// calc rotate
	if ( MyClient.client->getTuioCursors().size() == 3 )
	{
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			default:
				break;
			}
		}

		// 방어코드
		if (cursor1 == nullptr || cursor2 == nullptr)
		{
			return;
		}
			
		double tempAngle = ( cursor1->getY() - cursor2->getY() ) / ( cursor1->getX() - cursor2->getX() );
		m_ImgRotateAngle = 180.0 * PI * atan(tempAngle);
	}
}

void ImageExample::touchMoved( ofTouchEventArgs & touch )
{
	TUIO::TuioCursor* cursor1 = nullptr;
	TUIO::TuioCursor* cursor2 = nullptr;
	TUIO::TuioCursor* cursor3 = nullptr;

	if ( MyClient.client->getTuioCursors().size() == 1 )
	{
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			if (iter->getCursorID() == 0)
			{
				cursor1 = iter;
			}
		}

		if (cursor1 == nullptr)
		{
			return;
		}

		int movedPositionX = cursor1->getX() * WINDOW_WIDTH * 2;
		int movedPositionY = cursor1->getY() * WINDOW_HEIGHT * 2;

		// if imaged moved too far, return;
		if ( (m_ImgPositionX - movedPositionX) > 10.0 || m_ImgPositionY - movedPositionY > 10.0 )
		{
			return;
		}

		m_ImgPositionX = cursor1->getX() * WINDOW_WIDTH;
		m_ImgPositionY = cursor1->getY() * WINDOW_HEIGHT;
	}

	if ( MyClient.client->getTuioCursors().size() == 2 )
	{
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			default:
				break;
			}
		}

		// 방어코드
		if (cursor1 == nullptr || cursor2 == nullptr)
		{
			return;
		}

		m_ImgWidth = abs( cursor1->getX() - cursor2->getX() ) * WINDOW_WIDTH;
		m_ImgHeight = abs( cursor1->getY() - cursor2->getY() ) * WINDOW_HEIGHT;
	}

	// rotate
	if ( MyClient.client->getTuioCursors().size() == 3 )
	{
		for ( auto *iter : MyClient.client->getTuioCursors() )
		{
			switch ( iter->getCursorID() )
			{
			case 0:
				cursor1 = iter;
				break;
			case 1:
				cursor2 = iter;
				break;
			default:
				break;
			}
		}

		// 방어코드
		if (cursor1 == nullptr || cursor2 == nullptr)
		{
			return;
		}
		// 포인트 1과 2의 기울기를 기준으로 회전시킨다.
		double tempAngle = ( cursor1->getY() - cursor2->getY() ) / ( cursor1->getX() - cursor2->getX() );
		m_ImgRotateAngle = 180.0 * atan(tempAngle) / PI;
	}
}

void ImageExample::touchUp( ofTouchEventArgs & touch )
{

}
