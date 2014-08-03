#pragma once
#include "ofThread.h"
#include "Ball.h"

#define SPRING 0.05
#define GRAVITY 0.03
#define FRICTION -0.9
	
class BallCreater  : public ofThread
{
public:
	BallCreater(void);
	~BallCreater(void);
	vector<Ball*> getBallList();
	void destroyRequest(Ball* ball);

private:
	vector<Ball*> m_balls;
	void threadedFunction();
};

