#include "CMenu.h"
#include "../Core/CGame.h"
CMenu::CMenu(const CLoadParams pParams, void(*callbackFunction)())
	:CGameObject(pParams), m_callback(callbackFunction)
{

}
CMenu::CMenu(const CLoadParams pParams)
	: CGameObject(pParams) 
{
	
}
void CMenu::draw()
{

	CGameObject::draw(); // use the base class drawing

}
void CMenu::update()
{
	auto keyboardEvents = CGame::Instance().getKeyboardEvents();

	if (keyboardEvents.isKeyDown(SDL_SCANCODE_SPACE))
	{
		m_callback();
	}

}

void CMenu::clean()
{
	CGameObject::clean();
}
