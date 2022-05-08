#include "CFireBall.h"
#include "../../Core/CGame.h"


CFireBall::CFireBall()
{


}

void CFireBall::load(CLoadParams* params)
{

	m_position = Vector2D(params->getX(), (params->getY()));
	m_Velocity = Vector2D(0, 0);
	m_width = params->getWidth();
	m_height = params->getHeight();
	m_textureID = params->getTextureID();
	m_ObjectID = params->getObjectID();

	if (params->getCollinderBox() != NULL)
		m_ColliderBox = *params->getCollinderBox();

	m_TotalFrames = params->getTotalFrames();
	m_currentRow = params->getCurrentRow();

}

void CFireBall::draw()
{
	CTextureManager::Instance().draw(m_textureID, m_position.m_x, m_position.m_y, m_width, m_height, CGame::Instance().getRenderer());
}
void CFireBall::update(double dt)
{
	m_ColliderBox = { int(m_position.m_x) + m_width/2, int(m_position.m_y + m_height/2), 60, 60 };
	m_position += m_Velocity;

}

void CFireBall::clean()
{

}






