#include "BallCreater.h"

BallCreater::BallCreater(void)
{
}


BallCreater::~BallCreater(void)
{
}

void BallCreater::threadedFunction()
{

	Ball* newBall;
	int id = 0;
	while(isThreadRunning())
	{
		newBall = new Ball();
		
		newBall->setup(
				ofRandom(ofGetWidth()),
				//ofRandom(ofGetHeight()),
				-500,
				ofRandom(30,70), 
				m_balls.size(), 
				//id,
				SPRING, 
				GRAVITY, 
				FRICTION
		);

		m_balls.push_back(newBall);
		//cout << m_balls.size() << endl;

		++id;
		Sleep(200);


		//delete process
		vector<Ball*>::iterator it = m_balls.begin();
		for(; it != m_balls.end();){
			if( (*it)->isOutOfScreen() == true ){
				delete *it;
				it = m_balls.erase(it);
			}else
			   ++it;
		}
	}
}

vector<Ball*> BallCreater::getBallList()
{
	return m_balls;
}

void BallCreater::destroyRequest(Ball* ball)
{
	//m_balls.erase(m_balls.begin() + ball->id);

	//printf("size : %d   |    index : %d\n", m_balls.size(), ball->id);
	//printf("begin : %x  |    index : %x\n", (m_balls.begin() + ball->id), (m_balls[ball->id]));
	//m_balls.erase(m_balls.begin() + ball->id);
	
	//delete m_balls[ball->id];
	//particlePointers.erase( particlePointers.begin()+1 );
}