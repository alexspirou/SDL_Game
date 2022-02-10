#include "CPauseMenu.h"
#include "../Core/CGame.h"
CPauseMenu::CPauseMenu(const CLoadParams pParams, void(*callbackFunction)()):
CGameObject(pParams), m_callback(callbackFunction)
{
	m_currentRow = 1;
}

CPauseMenu::CPauseMenu(const CLoadParams pParams):
CGameObject(pParams)
{

}

void CPauseMenu::draw()
{
	CGameObject::drawFrame();
}

void CPauseMenu::update()
{
	

	auto keyboardEvents = CGame::Instance().getKeyboardEvents();

	if (keyboardEvents.isKeyDown(SDL_SCANCODE_SPACE))
	{
		m_callback();
	}

	if (keyboardEvents.isKeyDown(SDL_SCANCODE_DOWN))
	{
		m_currentFrame = 2;
	}
	//TODO : Check why doesn't show the other frames 
	m_currentFrame = int(((SDL_GetTicks() / 100) % 1));

}

void CPauseMenu::clean()
{
}
