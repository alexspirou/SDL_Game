#include "CFireBall.h"
#include "../../Core/CGame.h"
#include "../../Managers/CTextureManager.h"
#include "../../Managers/CSoundManager.h"

CFireBall::CFireBall()
{
	CTextureManager::Instance(). loadImage("D:/repos/SDL_Game/SDL-Game/SDL-Game/SDL-Game/Assets/MainChar/Fireballs/energyFireBall.png","FireBall", CGame::Instance().getRenderer());
	m_textureID = "FireBall";
	m_width = 61;
	m_height = 59;
}

void CFireBall::draw()
{
	std::cout << m_width << m_height << std::endl;
	CTextureManager::Instance().draw(m_textureID, m_position.m_x, m_position.m_y, m_width, m_height, CGame::Instance().getRenderer());
}

void CFireBall::update(double dt)
{
	m_Velocity* dt;
	m_position += m_Velocity;

}

void CFireBall::clean()
{

}



