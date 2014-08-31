#include "RectangleBar.h"

RectangleBar::RectangleBar(void)
{
}

RectangleBar::~RectangleBar(void)
{
}

void RectangleBar::setup(float xin, float yin, float widthin, float heightin, int idin, float springin, float graivityin, float frictionin)
{		
	m_isOutOfScreen = false;

	vx = 0;
	vy = 0;

	x = xin;
	y = yin;
	
	m_width = widthin;
	m_height = heightin;

	id = idin;
	
	spring = springin;
	gravity = graivityin;
	friction = frictionin;	

	width = ofGetWidth();
	height= ofGetHeight();
}

void RectangleBar::move()
{

}

void RectangleBar::moveLeft()
{
	if (x > 0) {
		x-=70;
    }
}

void RectangleBar::moveRight()
{
	if (x + m_width < width) {
		x+=70;
    }
}

void RectangleBar::display()
{
	ofSetColor(0,0,0);
	ofRect(x, y, m_width, m_height);	
	ofSetColor(255, 255, 255);	
}