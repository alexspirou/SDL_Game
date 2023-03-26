#include "CEnemy.h"
#include "../ScreenDimentions.h"
#include "../Core/CGame.h"
CEnemy::CEnemy()
{
}
void CEnemy::draw()
{

	CGameObject::drawFrame();
}

void CEnemy::update(double dt)
{

	m_currentFrame = int(((SDL_GetTicks() / 100) % m_TotalFrames));

	m_FlipSiderRender = SDL_FLIP_HORIZONTAL;
	move(-10);
	CGameObject::update(dt);

}

void CEnemy::move(double velocity)
{
	if (moveRight)
	{
		m_velocity.m_x = velocity * deltaTime;
		if (m_ColliderBox.x> SCREEN_WIDTH - m_ColliderBox.w)
			moveRight = false;
		m_FlipSiderRender = SDL_FLIP_NONE;
	}
	else if (!moveRight)
	{
		m_velocity.m_x = -velocity * deltaTime;
		if (m_ColliderBox.x < 0)
			moveRight = true;
		m_FlipSiderRender = SDL_FLIP_HORIZONTAL;

	}
	std::cout << m_ColliderBox.x << std::endl;
}
void CEnemy::clean()
{

}


