#include "CStableObject.h"

void CStableObjects::draw()
{
	CGameObject::draw();
}

void CStableObjects::drawFrame()
{
	if(m_SpawnTime <= SDL_GetTicks()/ 1000)
		CGameObject::drawFrame();
	if (m_SpawnTime + 5 < SDL_GetTicks() / 1000)
	{

		m_bDestroyed = true;
		return;
	}
}

void CStableObjects::update()
{

	m_currentFrame = int(((SDL_GetTicks() / 100) % m_TotalFrames));
}

void CStableObjects::clean()
{
	
}

void CStableObjects::load(CLoadParams* params)
{
	
	CGameObject::load(params);
	m_SpawnTime = params->getSpawnTime();
}
