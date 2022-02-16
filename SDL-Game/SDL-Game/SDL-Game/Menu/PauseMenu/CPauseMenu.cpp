#include "CPauseMenu.h"
#include "../../Core/CGame.h"
CPauseMenu::CPauseMenu(void(*callbackFunction)(int*)):
 m_callback(callbackFunction)
{
	m_currentRow = 0;
}
void CPauseMenu::drawFrame()
{
	CGameObject::drawFrame();
}

void CPauseMenu::update()
{
	auto keyboardEvents = CGame::Instance().getKeyboardEvents();

	if (keyboardEvents.isKeyDown(SDL_SCANCODE_SPACE))
	{
		m_callback(&m_currentRow);
	}
	auto DownArrowIsPressed = keyboardEvents.isKeyDown(SDL_SCANCODE_DOWN);
	if (DownArrowIsPressed)
	{
		if		(m_currentRow == PauseMenu::RESTART) { m_currentRow = PauseMenu::OPTIONS; }
		else if (m_currentRow == PauseMenu::OPTIONS) { m_currentRow = PauseMenu::MAINMENU; }
		else if (m_currentRow == PauseMenu::MAINMENU) { m_currentRow = PauseMenu::CANCEL; }

	}
	auto UpArrowIsPressed = keyboardEvents.isKeyDown(SDL_SCANCODE_UP);
	if (UpArrowIsPressed)
	{
		if		(m_currentRow == PauseMenu::CANCEL) { m_currentRow = PauseMenu::MAINMENU; }
		else if (m_currentRow == PauseMenu::MAINMENU) { m_currentRow = PauseMenu::OPTIONS; }
		else if (m_currentRow == PauseMenu::OPTIONS) { m_currentRow = PauseMenu::RESTART; }
		
	}

	m_currentFrame = int(((SDL_GetTicks() / 100) % 1));
	SDL_Delay(75);
}

void CPauseMenu::clean()
{

}
