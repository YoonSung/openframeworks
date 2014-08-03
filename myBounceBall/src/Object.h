#pragma once
#include "ofMain.h"

class Object
{
public:
	Object(void);
	virtual ~Object(void);

public:
	virtual void setup(float xin, float yin, float din, int idin, float springin, float graivityin, float frictionin);
		
	virtual void move();
	virtual void display();
	virtual bool isOutOfScreen();
public:	
	float x;
	float y;
	float diameter;
	float vx;
	float vy;
	int id;
		
	float spring;
	float gravity;
	float friction;

	float width;
	float height;
	
	bool m_isOutOfScreen;
};

