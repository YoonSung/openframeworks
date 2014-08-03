#pragma once

#include "ofMain.h"

class BallCreater;

class Ball
{
public:
	Ball(void);
	~Ball(void);

	void setup(float xin, float yin, float din, int idin, float springin, float graivityin, float frictionin);
		
	void move();
	void display();
	bool isOutOfScreen();
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

