#include "Object.h"


Object::Object(void)
{
}


Object::~Object(void)
{
}

void Object::setup(float xin, float yin, float din, int idin, float springin, float graivityin, float frictionin)
{		
	m_isOutOfScreen = false;

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

void Object::move()
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

void Object::display()
{
	ofSetColor(color);
	ofCircle(x, y, diameter/2);
}

bool Object::isOutOfScreen() {
	return m_isOutOfScreen;
}