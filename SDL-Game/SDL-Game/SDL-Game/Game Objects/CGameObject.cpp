#include "CGameObject.h"
#include "../Managers/CTextureManager.h"
#include "../Core/CGame.h"
CGameObject::CGameObject(CLoadParams params) : IObject(params),
m_position(params.getX(), params.getY()), m_velocity(0, 0), m_acceleration(0, 0)  //Here because we have only one constructor that takes two args
// We init before body. Another solution is to make it a pointer but this is better
{
	
	m_width = params.getWidth(); m_height = params.getHeight();
	m_textureID = params.getTextureID();

	m_currentRow = 1;
	m_currentFrame = 1;
}

void CGameObject::drawFrame()
{
	CTextureManager::Instance().drawFrame(m_textureID, m_position.m_x, m_position.m_y, m_width, m_height, m_currentRow, m_currentFrame, CGame::Instance().getRenderer());
}

void CGameObject::draw()
{
	CTextureManager::Instance().draw(m_textureID, m_position.m_x, m_position.m_y, m_width, m_height, CGame::Instance().getRenderer());

}

void CGameObject::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

	//Adding accelaration to velocity because we dont want to have the max speed instantaneously
	m_velocity += m_acceleration;
	//Adding velocity to position, velocity could be a float so the object move slower than 1
	m_position += m_velocity;
}

void CGameObject::clean()
{

}
