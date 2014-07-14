#include "Circle.h"

Circle::Circle(void)
{
}

Circle::Circle(ofPoint point)
{
	Circle::setPoint(point);
}

void Circle::setRadius(int radius)
{
	m_radius = radius;
}

int Circle::getRadius(){
	return m_radius;
}

void Circle::setPoint(ofPoint point)
{
	m_Point = point;
}

ofPoint Circle::getPoint()
{
	return m_Point;
}

void Circle::setColor(int r, int g, int b, int a)
{
	m_color_r = r;
	m_color_g = g;
	m_color_b = b;
	m_color_a = a;
}

int Circle::getRedColorIntensity()
{
	return m_color_r;
}

int Circle::getGreenColorIntensity()
{
	return m_color_g;
}

int Circle::getBlueColorIntensity()
{
	return m_color_b;
}

int Circle::getAlphaColorIntensity()
{
	return m_color_a;
}


Circle::~Circle(void)
{
}