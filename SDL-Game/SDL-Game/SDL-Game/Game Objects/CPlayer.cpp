#include "CPlayer.h"
#include "../ScreenDimentions.h"
#include "../Core/CGame.h"
void CPlayer::draw( )
{
	CGameObject::drawFrame();
}

void CPlayer::update()
{
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_TotalFrames));

	handleKeyBoardEvents();

	CGameObject::update();

}

void CPlayer::clean()
{

}


void CPlayer::handleMouseMotionEvents()
{
	auto mouseEvents = CGame::Instance().getMouseEvents().getMousePosition();

	m_position = mouseEvents;
}

void CPlayer::handleKeyBoardEvents()
{
	bool moveRight = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_RIGHT);
	bool moveLeft = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_LEFT);
	bool jump = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_SPACE);

	if		(moveRight) { m_velocity.m_x = 0.5; m_textureID = "mainCharWalkRight"; }
	else if (moveLeft)  { m_velocity.m_x = -0.5; m_textureID = "mainCharWalkLeft";}
	else if (moveLeft) { m_velocity.m_y = 1; m_textureID = "mainCharWalkLeft"; }

	else
	{
		m_textureID = "mainCharIdle";
		m_velocity.m_x = 0;
		m_velocity.m_y = 0;
	}



	//if (jump)
	//{
	//	prevPos = m_position.m_y;
	//	m_position.m_y -= 1;
	//
	//}

	
}
