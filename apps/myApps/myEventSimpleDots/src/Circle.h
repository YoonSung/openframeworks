#pragma once
#include "ofMain.h"

class Circle
{
public:
	Circle(void);
	Circle(ofPoint point);
	~Circle(void);

private:
	ofPoint m_Point;
	int m_radius;
	int m_color_r;
	int m_color_g;
	int m_color_b;
	int m_color_a;
public:
	void setPoint(ofPoint point);
	ofPoint getPoint();
	void setRadius(int radius);
	void setColor(int r, int g, int b, int a);
	int getRedColorIntensity();
	int getGreenColorIntensity();
	int getBlueColorIntensity();
	int getAlphaColorIntensity();
	int getRadius();
};