#pragma once
#include "config.h"
#include "array"

class Ball
{
public:
	// ball들을 관리하기 위한 list와 해당 ball의 idx를 인자에 넣은 이유는 충돌체크가 필요한 경우 활용하기 위해
	// x, y값은 생성되는 ball이 화면에 터치된 지점에서 생성되게 하기 위해서 입력
	Ball(std::array<Ball*, BALL_NUMBER>* ballList, unsigned int idx, float x, float y);
	~Ball(void);

	// ball의 크기와 색 변화를 위한 flag 설정
	void init();

	// ball이 움직이는 임의의 속도 부여
	void setVelocity();

	// ball의 움직임과 크기, 색 변화를 적용
	void update();

	// 화면에 ball을 그림
	void draw();

	// ball이 움직이다가 화면 밖으로 나가는지 확인해서
	// 나가지 않도록 속도 변화
	void checkBoundary();

	// ball의 크기를 증가시키고 색을 변화 시킴
	void changeBallProperties();

	// ball의 크기 증가는 멈춤
	void stopIncreasing();

	// get / set functions
	void	setRadius(float radius)		{ m_Radius = radius; }
	float	getRadius()					{ return m_Radius; }
	ofVec3f getPosition()				{ return m_Position; }
	ofVec3f getVelocity()				{ return m_Velocity; }
	void setVelocity(ofVec3f change)	{ m_Velocity = change; }

private:
	unsigned int m_Idx;
	float m_ColorIdx;

	bool m_IsChanging;

	ofVec3f m_Position;
	float m_Radius;

	ofVec3f m_Velocity;

	std::array<Ball*, BALL_NUMBER>* m_BallList;
	std::array<ofColor, COLOR_NUMBER> m_colorList;
};

