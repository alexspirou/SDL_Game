#include "CStableObject.h"

void CStableObjects::draw()
{
	CGameObject::draw();
}

void CStableObjects::drawFrame()
{
	CGameObject::drawFrame();
}

void CStableObjects::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_TotalFrames));
}

void CStableObjects::clean()
{

}
