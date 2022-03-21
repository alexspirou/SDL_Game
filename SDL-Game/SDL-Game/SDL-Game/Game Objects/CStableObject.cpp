#include "CStableObject.h"

void CStableObject::draw()
{
	CStableObject::draw();
}

void CStableObject::drawFrame()
{
	CGameObject::drawFrame();
}

void CStableObject::update(double dt)
{

	m_currentFrame = int(((SDL_GetTicks() / 100) % m_TotalFrames));

	if (m_TotalFrames == 8)
	{
		m_currentRow = 1;
	}
	CGameObject::update(dt);
}

void CStableObject::clean()
{
	
}
