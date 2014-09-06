#include "ObjectCreater.h"

ObjectCreater::ObjectCreater(void)
{
}

ObjectCreater::~ObjectCreater(void)
{
}

void ObjectCreater::threadedFunction()
{

	addRectangleBar(0);

	int id = 1;
	while(isThreadRunning())
	{
		addBall(id);
		++id;
		
		Sleep(500);

		//delete process
		deleteObjectByLocation();
	}
}

vector<Object*> ObjectCreater::getObjectList()
{
	return m_objects;
}

void ObjectCreater::addBall(int id)
{
	Ball* newBall = new Ball();
		
	newBall->setup(
			ofRandom(ofGetWidth()),
			//ofRandom(ofGetHeight()),
			-100,
			ofRandom(30,70), 
			id,
			SPRING, 
			GRAVITY, 
			FRICTION
	);

	m_objects.push_back(newBall);
}

void ObjectCreater::addRectangleBar(int id)
{
	RectangleBar* bar= new RectangleBar();
	bar->setup(
		ofGetWidth()/2-60,
		ofGetHeight() - 40,
		120,
		20,
		id,
		SPRING * 2, 
		GRAVITY, 
		FRICTION / 2
	);

	m_objects.push_back(bar);
}

void ObjectCreater::deleteObjectByLocation()
{
	vector<Object*>::iterator it = m_objects.begin();
	for(; it != m_objects.end();){
		if( (*it)->isOutOfScreen() == true ){
			delete *it;
			it = m_objects.erase(it);
		}else
		   ++it;
	}
}