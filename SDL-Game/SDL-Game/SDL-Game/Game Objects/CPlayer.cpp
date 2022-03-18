#include "CPlayer.h"
#include "../ScreenDimentions.h"
#include "../Core/CGame.h"
#include "../Managers/CTextureManager.h"
CPlayer::CPlayer() :
	m_Gravity{0, 2.6}, m_Force{0, 0}, m_Mass{1}
{
	CGame::Instance().getSoundManager().loadSound("jumpSound", "D:/repos/SDL_Game/SDL-Game/SDL-Game/SDL-Game/Assets/Music/jump.wav");
	CGame::Instance().getSoundManager().loadSound("fireBall", "D:/repos/SDL_Game/SDL-Game/SDL-Game/SDL-Game/Assets/MainChar/Sounds/fireBall.wav ");
	auto loadStartMenu = CTextureManager::Instance().loadImage("Assets/colliderBox.png", "colliderBox", CGame::Instance().getRenderer());

}
void CPlayer::draw()
{
	m_Fireball.draw();
	CTextureManager::Instance().draw("colliderBox", m_ColliderBox.m_Box.x, m_ColliderBox.m_Box.y, m_ColliderBox.m_Box.w, m_ColliderBox.m_Box.h, CGame::Instance().getRenderer());
	CGameObject::drawFrame();
}

void CPlayer::update(double dt)
{
	Vector2D m_RealPosition{ m_position.m_x + 100 , m_position.m_y + 100 };


	if (!isShooting || m_Fireball.m_position.m_x > SCREEN_WIDTH ||  m_Fireball.m_position.m_x < -m_Fireball.getWidth()) { m_Fireball.m_position = m_RealPosition; isShooting = false; }

	if (!applyGravity())
	{
		handleKeyBoardEvents();
	}

	m_Fireball.update(deltaTime);
	

	m_Force += m_Gravity;
	m_Force  = (m_Force / m_Mass )* dt;	
	m_position += m_velocity;

	m_ColliderBox.m_Box = { int((m_position.m_x) + m_width/2) -20 , int(m_position.m_y) + m_height / 2 -25, 40, 75 };


	CGameObject::update(dt);
}



// Private Functions

void CPlayer::jump()
{
	Vector2D m_RealPosition{ m_position.m_x + 100 , m_position.m_y + 100 };
	m_velocity = 0;
	m_textureID = "mainCharIdle";

	if (isLookingRight) 
	{
		m_velocity.m_x = 4 ; m_velocity.m_y = -10;
		m_position = m_position + m_velocity * deltaTime;
		m_velocity = m_velocity + m_Gravity;
		CGame::Instance().getSoundManager().playSound("jumpSound", 40);
	}
	else if (!isLookingRight)
	{
		m_velocity.m_x = -4; m_velocity.m_y = -10;
		m_position = m_position + m_velocity * deltaTime;
		m_velocity = m_velocity + m_Gravity;
		CGame::Instance().getSoundManager().playSound("jumpSound", 40);

	}
	if (m_RealPosition.m_x < 0)
	{
		applyGravity();
	}
	
}

bool CPlayer::applyGravity()
{
	Vector2D m_RealPosition{ m_position.m_x + 100 , m_position.m_y + 100 };
	
	//Here will be change with collision of map that it doesnt fall
	if (m_RealPosition.m_y < 470 )
	{ 
		m_velocity = m_velocity + m_Gravity  * deltaTime;
		m_position = m_position + m_velocity * deltaTime; 
		return true;
	}
	else
	{
		m_velocity.m_y = 0;
		return false;
	}
}

void CPlayer::shootFireBall()
{
	Vector2D m_RealPosition{ m_position.m_x + 100 , m_position.m_y + 100 };
	//Add operator overloading for comparison
	if(m_Fireball.m_position.m_x == m_RealPosition.m_x) CGame::Instance().getSoundManager().playSound("fireBall", 30);

	if(isLookingRight) m_Fireball.m_Velocity.m_x = 40 * deltaTime;
	else  m_Fireball.m_Velocity.m_x = -40 * deltaTime;


	isShooting = true;
	
}


//void CPlayer::handleMouseMotionEvents()
//{
//	auto mouseEvents = CGame::Instance().getMouseEvents().getMousePosition();
//
//	m_position = mouseEvents;
//}

void CPlayer::handleKeyBoardEvents()
{
	//Change this to switch statements

	bool moveRight = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_RIGHT);
	bool moveLeft = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_LEFT);
	bool moveUp = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_UP);
	bool moveDown = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_DOWN);
	bool attack1 = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_Q);
	bool attack2 = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_W);
	bool isJumpPressed = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_D);
	
	if		(moveRight)		{  move(3); m_textureID = "mainCharWalkRight";  m_TotalFrames =  8;	}
	else if (moveLeft)		{  move(-3); m_textureID = "mainCharWalkRight"; m_TotalFrames = 8;		}
	else if (moveUp)		{  moveUpDown(-10); m_textureID = "mainCharIdle"; m_TotalFrames = 8;	}
	else if (moveDown)		{  moveUpDown(10); m_textureID = "mainCharIdle"; m_TotalFrames = 8;		}
	else if (attack1)		{  shootFireBall(); move(0); m_textureID = "mainCharAttack1"; m_TotalFrames = 8; }
	else if (attack2)		{  move(0);  m_textureID = "mainCharAttack2"; m_TotalFrames = 8;		}
	else if (isJumpPressed) {  jump();																}
	else
	{
		m_textureID = "mainCharIdle";
		m_velocity.m_x = 0;
		m_TotalFrames = 8;
		m_acceleration = 0;
	}
}
void CPlayer::move(float velocity)
{
	Vector2D m_RealPosition{ m_position.m_x + 100 , m_position.m_y + 100 };
	m_velocity = 0;

	if (m_RealPosition.m_x >= 0  && velocity < 0)
	{
		isLookingRight = false;
		m_FlipSiderRender = SDL_FLIP_HORIZONTAL;
		m_velocity.m_x = velocity * deltaTime;
		m_velocity.m_y = 0;

	}
	else if (velocity > 0)
	{
		isLookingRight = true;
		m_FlipSiderRender = SDL_FLIP_NONE;
		m_velocity.m_x = velocity * deltaTime;
		m_velocity.m_y = 0;

	}
	else 
	{
		
		m_velocity = 0;

	}
}

void CPlayer::moveUpDown(float velocity)
{
	Vector2D m_RealPosition{ m_position.m_x + 100 , m_position.m_y + 100 };
	m_velocity = 0;

	if (m_RealPosition.m_y < 474  && velocity > 0)
	{
		m_velocity.m_y = velocity * deltaTime;
		m_velocity.m_x = 0;
	}
	else if (m_RealPosition.m_y > 0  && velocity < 0)
	{
		m_velocity.m_y = velocity * deltaTime;
		m_velocity.m_x = 0;

	}
}
void CPlayer::clean()
{

}
