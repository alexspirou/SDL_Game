#include "CGameObject.h"
#include "../Managers/CTextureManager.h"
#include "../Core/CGame.h"
#include "../Collision/CCollisionDetection.h"
CGameObject::CGameObject() : IObject()
{
}
void CGameObject::load(CLoadParams* params)
{
	m_position = Vector2D(params->getX(),(params->getY()));
    m_velocity = Vector2D(0, 0);
	m_acceleration = Vector2D(0, 0);

	m_SpawnTime = params->getSpawnTime();

	m_width = params->getWidth();
	m_height = params->getHeight();
	m_textureID = params->getTextureID();
	m_ObjectID = params->getObjectID();

	if(params->getCollinderBox()!=NULL)
		m_ColliderBox = *params->getCollinderBox();

	m_TotalFrames = params->getTotalFrames();
	m_FlipSiderRender = SDL_FLIP_NONE;
	m_currentRow = params->getCurrentRow();

	
}
void CGameObject::drawFrame()
{

	//CTextureManager::Instance().drawColliderBox(CGame::Instance().getRenderer(), m_ColliderBox);
	CTextureManager::Instance().drawFrame(m_textureID, m_position.m_x, m_position.m_y, m_width, m_height, m_currentRow, m_currentFrame, CGame::Instance().getRenderer(), m_FlipSiderRender);
}

void CGameObject::draw()
{
	CTextureManager::Instance().draw(m_textureID, m_position.m_x, m_position.m_y, m_width, m_height, CGame::Instance().getRenderer());
}

void CGameObject::update(double dt)
{
	deltaTime = dt;

	// Adding accelaration to velocity because we dont want to have the max speed instantaneously
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_TotalFrames));

	// Adding velocity to position, velocity could be a float so the object move slower than 1
	m_position += m_velocity;

	// Update collider's position along with object's position
	m_ColliderBox =
	{
		static_cast<int>(((m_position.m_x) + m_width / 2)) - m_ColliderBox.w / 2,
		static_cast<int>((m_position.m_y)) + m_height / 2 - m_ColliderBox.h / 2,
		static_cast<int>((m_ColliderBox.w)),
		static_cast<int>((m_ColliderBox.h))
	};

}
void CGameObject::clean()
{

}

