#include "CPlayer.h"
#include "../ScreenDimentions.h"
#include "../Core/CGame.h"

CPlayer::CPlayer()
{

}
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
void CPlayer::manageSounds(int sound)
{

}
void CPlayer::handleMouseMotionEvents()
{
	auto mouseEvents = CGame::Instance().getMouseEvents().getMousePosition();

	m_position = mouseEvents;
}

void CPlayer::handleKeyBoardEvents()
{
	//Change this to switch statements

	bool moveRight = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_RIGHT);
	bool moveLeft = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_LEFT);
	bool goDown = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_DOWN);
	bool attack1 = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_Q);
	bool attack2 = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_W);
	bool death = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_D);

	if (moveRight) { isLookingRight = true; m_velocity.m_x = 0.5; m_textureID = "mainCharWalkRight"; m_FlipSiderRender = SDL_FLIP_NONE; }
	else if (moveLeft) { isLookingRight = false; m_velocity.m_x = -0.5; m_textureID = "mainCharWalkRight"; m_FlipSiderRender = SDL_FLIP_HORIZONTAL; }
	else if (goDown) { m_textureID = "mainCharFall"; m_TotalFrames = 2; }
	else if (attack1) 
	{
		
		if (isLookingRight) {  m_velocity.m_x = 2; }
		else m_velocity.m_x = -2;
		m_textureID = "mainCharAttack1"; m_TotalFrames = 8; 
	}
	else if (attack2) 
	{ 
		if (isLookingRight) m_velocity.m_x = 2; else m_velocity.m_x = -2;
		m_textureID = "mainCharAttack2"; m_TotalFrames = 8; 
	
	}
	else if (death)
	{
		
		m_textureID = "mainCharDeath"; m_TotalFrames = 8;

	}
	else
	{
		//m_FlipSiderRender = SDL_FLIP_NONE;
		m_textureID = "mainCharIdle";
		m_velocity = 0;
		 m_TotalFrames = 8;
		 m_acceleration = 0;
	}
}
