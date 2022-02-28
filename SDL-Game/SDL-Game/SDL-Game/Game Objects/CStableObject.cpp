#include "CStableObject.h"

void CStableObject::draw()
{
	CStableObject::draw();
}

void CStableObject::drawFrame()
{
	if(m_SpawnTime <= SDL_GetTicks()/ 1000)
		CGameObject::drawFrame();
}

void CStableObject::update()
{

	m_currentFrame = int(((SDL_GetTicks() / 100) % m_TotalFrames));

	if (m_TotalFrames == 8)
	{
		m_currentRow = 1;
	}
	CGameObject::update();
}

void CStableObject::clean()
{
	
}

void CStableObject::load(CLoadParams* params)
{
	CGameObject::load(params);
	m_SpawnTime = params->getSpawnTime();
}
