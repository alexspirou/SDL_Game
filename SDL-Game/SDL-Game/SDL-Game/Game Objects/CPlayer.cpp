#include "CPlayer.h"
#include "../ScreenDimentions.h"
#include "../Core/CGame.h"
void CPlayer::draw( )
{
	CGameObject::drawFrame();
}

void CPlayer::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % 6));

	/*handleMouseClickEvents();

	handleMouseMotionEvents();*/

	handleKeyBoardEvents();

	CGameObject::update();

}

void CPlayer::clean()
{

}

void CPlayer::handleMouseClickEvents()
{
	auto mouseEvents = CGame::Instance().getMouseEvents();

	auto leftClickPressed = mouseEvents.getMouseStates(mouseEvents.LEFTCLICK);
	auto rightClickPressed = mouseEvents.getMouseStates(mouseEvents.RIGHTCLICK);
	auto middleClickPressed = mouseEvents.getMouseStates(mouseEvents.MIDDLECLICK);

	if (rightClickPressed)
	{
		isPlayerMovingRightInScreen = true;
		m_velocity.m_x = 2;
	}

	if (leftClickPressed)
	{
		isPlayerMovingRightInScreen = false;
		m_velocity.m_x = -2;
	}

	if (middleClickPressed)
	{
		isPlayerMovingRightInScreen = false;
		m_velocity.m_x = 0;
	}
}

void CPlayer::handleMouseMotionEvents()
{
	auto mouseEvents = CGame::Instance().getMouseEvents().getMousePosition();

	m_position = mouseEvents;
}

void CPlayer::handleKeyBoardEvents()
{
	auto moveRight = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_RIGHT);
	auto moveLeft = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_LEFT);
	auto moveUp = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_UP);
	auto moveDown = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_DOWN);
	auto jump = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_SPACE);

	if (moveRight)		m_velocity.m_x =  0.5;		else m_velocity.m_x = 0;
	if (moveLeft)		m_velocity.m_x = -0.5;
	if (moveUp)			m_velocity.m_y = -0.5;		else m_velocity.m_y = 0;
	if (moveDown)		m_velocity.m_y =  0.5;

	int prevPos{};

	//if (jump)
	//{
	//	prevPos = m_position.m_y;
	//	m_position.m_y -= 1;
	//
	//}

	
}
