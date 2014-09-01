#pragma once
#include "ofThread.h"
#include "Ball.h"
#include "RectangleBar.h"

#define SPRING 0.05
#define GRAVITY 0.03
#define FRICTION -0.9
	
class ObjectCreater  : public ofThread
{
public:
	ObjectCreater(void);
	~ObjectCreater(void);
	vector<Object*> getObjectList();

private:
	vector<Object*> m_objects;
	void threadedFunction();
	void addBall(int id);
	void deleteObjectByLocation();
	void addRectangleBar(int id);
};

