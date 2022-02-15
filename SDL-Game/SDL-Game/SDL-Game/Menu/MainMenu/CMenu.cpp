#include "CMenu.h"
#include "../../Core/CGame.h"
CMenu::CMenu(void(*callbackFunction)())
:m_callback(callbackFunction)
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
