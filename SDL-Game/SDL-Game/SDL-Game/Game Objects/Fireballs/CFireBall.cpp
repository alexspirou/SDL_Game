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
	CTextureManager::Instance().draw(m_textureID, m_position.m_x, m_position.m_y, m_width, m_height, CGame::Instance().getRenderer());
}
void CFireBall::update(double dt)
{
	m_ColliderBox.m_Box = { int(m_position.m_x) + m_width/2, int(m_position.m_y + m_height/2), 61, 59 };
	m_position += m_Velocity;

}

void CFireBall::clean()
{

}





