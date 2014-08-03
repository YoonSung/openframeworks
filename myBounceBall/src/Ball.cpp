#include "Ball.h"

Ball::Ball(void)
{
	m_isOutOfScreen = false;
}

Ball::~Ball(void)
{
}


void Ball::setup(float xin, float yin, float din, int idin, float springin, float graivityin, float frictionin)
{		
	vx = 0;
	vy = 0;

	x = xin;
	y = yin;
	
	diameter = din;
	id = idin;
	
	spring = springin;
	gravity = graivityin;
	friction = frictionin;	

	width = ofGetWidth();
	height= ofGetHeight();
}

void Ball::move()
{
	vy += gravity;
    x += vx;
    y += vy;
    if (x + diameter/2 > width) {
		x = width - diameter/2;
		vx *= friction; 
    }
    else if (x - diameter/2 < 0) {
		x = diameter/2;
		vx *= friction;
    }

	if (y - diameter/2 > height) {
		m_isOutOfScreen = true;
    }
	/*
    if (y + diameter/2 > height) {
      y = height - diameter/2;
      vy *= friction; 
    } 
	
    else if (y - diameter/2 < 0) {
      y = diameter/2;
      vy *= friction;
    }
	*/
}

void Ball::display()
{
	ofCircle(x, y, diameter/2);
}

bool Ball::isOutOfScreen() {
	return m_isOutOfScreen;
}