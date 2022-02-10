#include "CEnemy.h"
void CEnemy::draw()
{
	CGameObject::drawFrame();
}

void CEnemy::update()
{

	m_acceleration.m_x = 0.02;

	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

	CGameObject::update();

}

void CEnemy::clean()
{

}
