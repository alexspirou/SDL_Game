#include "CEnemy.h"
#include "../ScreenDimentions.h"
#include "../Core/CGame.h"
CEnemy::CEnemy()
{
	CGame::Instance().getSoundManager().loadSound("fuckOff", "D:/repos/SDL_Game/SDL-Game/SDL-Game/SDL-Game/Assets/Music/gamath.wav");
}
void CEnemy::draw()
{
	CGameObject::drawFrame();
}

void CEnemy::update(double dt)
{

	move();
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_TotalFrames));
	m_currentRow = 0;

	CGameObject::update(dt);

}
void CEnemy::clean()
{

}
bool CEnemy::isPLayerNear(CPlayer* const player)
{
	//TODO : Check if player is near and attack.
	if (player->getPosition().m_y > this->m_position.m_y - this->m_width * 2) m_velocity.m_y = 0.2 * deltaTime;
	else { m_velocity.m_y = 0; }
	if (player->getPosition().m_x == this->m_position.m_x - this->m_width - player->getWidth())
	{
		CGame::Instance().getSoundManager().playSound("fuckOff", 50);
	}
	return false;
} 

void CEnemy::move()
{
	if (moveRight)
	{
		m_velocity.m_x = 0.1 * deltaTime;
		if (m_position.m_x > SCREEN_WIDTH - m_width)
			moveRight = false;
		m_FlipSiderRender = SDL_FLIP_NONE;
	}
	else if (!moveRight)
	{
		m_velocity.m_x = -0.1 * deltaTime;
		if (m_position.m_x < 0)
			moveRight = true;
		m_FlipSiderRender = SDL_FLIP_HORIZONTAL;

	}
}
