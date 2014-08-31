#pragma once
#include "Object.h"

class RectangleBar
: public Object
{
public:
	RectangleBar(void);
	~RectangleBar(void);

	void setup(float xin, float yin, float widthin, float heightin, int idin, float springin, float graivityin, float frictionin);
	void moveLeft();
	void moveRight();

	virtual void move();
	virtual void display();
	int m_width;
	int m_height;
};

