#include "ofMain.h"
#include "Ball.h"
#include <stdlib.h>
#include <math.h>

Ball::Ball(std::array<Ball*, BALL_NUMBER>* ballList, unsigned int idx, float x, float y)
{
	// tuio에서 받은 x, y값은 화면에 대한 백분율값이므로 
	// 화면 크기만큼을 곱해서 해당하는 위치의 픽셀값을 구함
	m_Position.x = x * WINDOW_WIDTH;
	m_Position.y = y * WINDOW_HEIGHT;

	// 맨 처음에 생성될 때 ball의 크기
	m_Radius = 50.0f;

	// 생성될 때는 움직이지 않음 (터치 이벤트가 종료되면 이동)
	m_Velocity.x = 0.0f;
	m_Velocity.y = 0.0f;

	m_BallList = ballList;
	m_Idx = idx;

	// 터치 이벤트가 유지되는 동안 ball의 색을 변화시키기 위해서 사용되는
	// 색 리스트 생성
	m_colorList[0].r = 30;
	m_colorList[0].g = 153;
	m_colorList[0].b = 197;

	m_colorList[1].r = 196;
	m_colorList[1].g = 15;
	m_colorList[1].b = 132;

	m_colorList[2].r = 204;
	m_colorList[2].g = 232;
	m_colorList[2].b = 36;

	m_colorList[3].r = 78;
	m_colorList[3].g = 183;
	m_colorList[3].b = 153;

	m_colorList[4].r = 255;
	m_colorList[4].g = 102;
	m_colorList[4].b = 0;

	m_ColorIdx = 0;
	m_IsChanging = false;
}


Ball::~Ball(void)
{
}

void Ball::init()
{
	// 터치 이벤트가 종료될 때까지 크기와 색 변화를 주기위한 flag 설정
	m_IsChanging = true;
}

void Ball::setVelocity()
{	
	// 임의의 방향으로 속도 부여
	m_Velocity.x = static_cast<float>(rand() ) / (RAND_MAX / 2) - 1.0f;
	m_Velocity.y = static_cast<float>(rand() ) / (RAND_MAX / 2) - 1.0f;
}

void Ball::update()
{
	// 만약 아직 터치 이벤트가 종료되지 않으며 ball의 속성을 변경시킴
	if (m_IsChanging)
		changeBallProperties();

	// 현재 속도만큼 화면에서 이동
	m_Position += m_Velocity;
}

void Ball::draw()
{
	// 화면에 ball을 그림
	// 이때 ball의 색은 현재 ball의 m_ColorIdx에 해당하는 색으로 선택
	// m_ColorIdx는 float형이지만 강제캐스팅을 통해서 소숫점 값은 버리고 계산 - 색 변화 속도와 관련
	ofSetColor(m_colorList[static_cast<unsigned int>(m_ColorIdx) % COLOR_NUMBER]);
	ofCircle(m_Position.x, m_Position.y, m_Radius);
}

void Ball::changeBallProperties()
{
	// ball의 크기 증가
	m_Radius += 0.5;

	// ball의 색 변화
	// idx를 0.1씩 증가시키는 이유는 너무 빠른 색 변화를 막기 위함
	// 1씩 증가시키면 ball의 색이 별 먹은 마리오처럼 보임
	m_ColorIdx += 0.1f;
}

void Ball::stopIncreasing()
{
	m_IsChanging = false;
}

void Ball::checkBoundary()
{
	// ball의 왼쪽 끄트머리가 화면 왼쪽 을 넘어가는지 확인
	// 만약 넘어가는 상황이면 x축 방향의 운동 방향을 반대로 바꾸고
	// ball의 위치는 화면 왼쪽 끝으로 설정
	if (m_Position.x - m_Radius < 0)
	{
		m_Velocity.x *= -1;
		m_Position.x = m_Radius;
	}
	// 위와 같은 작업을 나머지 화면 모서리에 대해서도 진행
	else if (m_Position.x + m_Radius > WINDOW_WIDTH)
	{
		m_Velocity.x *= -1;
		m_Position.x = WINDOW_WIDTH - m_Radius;
	}

	if (m_Position.y - m_Radius < 0)
	{
		m_Velocity.y *= -1;
		m_Position.y = m_Radius;
	}
	else if (m_Position.y + m_Radius > WINDOW_HEIGHT)
	{
		m_Velocity.y *= -1;
		m_Position.y = WINDOW_HEIGHT - m_Radius;
	}
}