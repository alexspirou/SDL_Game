#include "CGameOver.h"
#include "../ScreenDimentions.h"
#include "../Core/CGame.h"
CGameOver::CGameOver(FontStruct* fontstruct)
:m_FontStruct(fontstruct), m_RightFlag(true), m_xGameOver(0)
{
	m_FontManager.loadFont("Assets/Fonts/GameOverFont.TTF", 20);
}
void CGameOver::update()
{
	moveLeftRight();
}

void CGameOver::render()
{

	std::string gameOverMsg = "GAME OVER";
	m_WidthGameOver = 75 * gameOverMsg.length();
	m_FontManager.renderText(gameOverMsg, new FontStruct(m_xGameOver, 100, m_WidthGameOver, 200, { 255,0,0 }), 1);

	std::string playAgain = "F2. Play Again";
	m_FontManager.renderText(playAgain, new FontStruct(0, SCREEN_HEIGHT - 60, 20 * playAgain.length(), 60, { 255,0,0 }), 1);

	std::string mainMenu = "F10. Main Menu";
	m_FontManager.renderText(mainMenu, new FontStruct(SCREEN_WIDTH/2 - 120, SCREEN_HEIGHT - 60, 20 * mainMenu.length(), 60, { 255,0,0 }), 1);

	std::string exit = "F12. Exit ";
	m_FontManager.renderText(exit, new FontStruct(SCREEN_WIDTH - 20 * exit.length(), SCREEN_HEIGHT - 60, 20 * exit.length(), 60, { 255,0,0 }), 1);

}
void CGameOver::moveLeftRight()
{
	if(m_xGameOver + m_WidthGameOver < SCREEN_WIDTH && m_RightFlag)
		m_xGameOver+=2;
	else if(m_xGameOver >= 0)
	{
		m_xGameOver -=2;
		m_RightFlag = false;
	}
	else
	{
		m_RightFlag = true;
	}

}


//auto mouseEvents = CGame::Instance().getMouseEvents().getMousePosition();

//std::cout << mouseEvents.m_x << std::endl;