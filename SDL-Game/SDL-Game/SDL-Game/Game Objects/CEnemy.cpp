#include "CEnemy.h"
#include "../ScreenDimentions.h"
void CEnemy::draw()
{
	CGameObject::drawFrame();
}

void CEnemy::update()
{

	move();
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_TotalFrames));
	m_currentRow = 0;
	CGameObject::update();

}
void CEnemy::clean()
{

}
bool CEnemy::isPLayerNear(std::unique_ptr<CPlayer>& const player)
{
	//TODO : Check if player is near and attack.

	if (player->getPosition().m_x > 200)
	{
		if (player->getPosition().m_y > this->m_position.m_y - this->m_width*2) m_velocity.m_y = 0.5;
		else  m_velocity.m_y = 0;
	}
	return false;
} 

void CEnemy::move()
{
	if (moveRight)
	{
		m_velocity.m_x = 0.5;
		if (m_position.m_x > SCREEN_WIDTH - m_width)
			moveRight = false;
		m_FlipSiderRender = SDL_FLIP_NONE;
	}
	else if (!moveRight)
	{
		m_velocity.m_x = -0.5;
		if (m_position.m_x < 0)
			moveRight = true;
		m_FlipSiderRender = SDL_FLIP_HORIZONTAL;

	}
}
