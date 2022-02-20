#include "CGameObject.h"
#include "../Managers/CTextureManager.h"
#include "../Core/CGame.h"
CGameObject::CGameObject() : IObject()
{

}
void CGameObject::load(CLoadParams* params)
{
	//Check if they assigned correctly

	m_position = Vector2D(params->getX(),(params->getY()));
    m_velocity = Vector2D(0, 0);
	m_acceleration = Vector2D(0, 0);

	m_width = params->getWidth();
	m_height = params->getHeight();
	m_textureID = params->getTextureID();

	m_TotalFrames = params->getTotalFrames();

	m_FlipSiderRender = SDL_FLIP_NONE;
	m_currentRow = params->getCurrentRow();
}
void CGameObject::drawFrame()
{
	CTextureManager::Instance().drawFrame(m_textureID, m_position.m_x, m_position.m_y, m_width, m_height, m_currentRow, m_currentFrame, CGame::Instance().getRenderer(), m_FlipSiderRender);
}

void CGameObject::draw()
{
	CTextureManager::Instance().draw(m_textureID, m_position.m_x, m_position.m_y, m_width, m_height, CGame::Instance().getRenderer());

}

void CGameObject::update()
{
	 //Change 100 to variable

	//Adding accelaration to velocity because we dont want to have the max speed instantaneously
	m_velocity += m_acceleration;
	//Adding velocity to position, velocity could be a float so the object move slower than 1
	m_position += m_velocity;
}

void CGameObject::clean()
{

}

