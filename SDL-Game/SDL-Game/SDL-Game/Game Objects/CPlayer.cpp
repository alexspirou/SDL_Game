#include "CPlayer.h"
#include "../ScreenDimentions.h"
#include "../Core/CGame.h"
CPlayer::CPlayer()
{
	CGame::Instance().getSoundManager().loadSound("jumpSound", "D:/repos/SDL_Game/SDL-Game/SDL-Game/SDL-Game/Assets/Music/jump.wav");
	CGame::Instance().getSoundManager().loadSound("fireBall", "D:/repos/SDL_Game/SDL-Game/SDL-Game/SDL-Game/Assets/MainChar/Sounds/fireBall.wav ");

}
void CPlayer::draw()
{
	m_Fireball.draw();
	CGameObject::drawFrame();
}

void CPlayer::update(double dt)
{
	Vector2D m_RealPosition{ m_position.m_x + 100 , m_position.m_y + 100 };

	m_currentFrame = int(((SDL_GetTicks() / 100) % m_TotalFrames));

	if (!isShooting || m_Fireball.m_position.m_x > SCREEN_WIDTH ||  m_Fireball.m_position.m_x < -m_Fireball.getWidth()) { m_Fireball.m_position = m_RealPosition; isShooting = false; }

	if (!applyGravity())
	{
		handleKeyBoardEvents();
	}

	m_Fireball.update(dt);

	CGameObject::update(dt);
}

void CPlayer::jump()
{
	Vector2D m_RealPosition{ m_position.m_x + 100 , m_position.m_y + 100 };
	m_velocity = 0;
	m_textureID = "mainCharIdle";

	if (isLookingRight) 
	{

		m_velocity.m_x = 5; m_velocity.m_y = -10; 
		m_position = m_position + m_velocity * deltaTime;
		m_velocity = m_velocity + m_Gravity;
		CGame::Instance().getSoundManager().playSound("jumpSound", 60);
	}
	else if (!isLookingRight)
	{
		m_velocity.m_x = -5; m_velocity.m_y = -10; 
		m_position = m_position + m_velocity * deltaTime;
		m_velocity = m_velocity + m_Gravity;
		CGame::Instance().getSoundManager().playSound("jumpSound", 60);

	}
	if (m_RealPosition.m_x < 0)
	{
		applyGravity();
	}
	std::cout << m_position.m_x << std::endl;

	
}

bool CPlayer::applyGravity()
{
	Vector2D m_RealPosition{ m_position.m_x + 100 , m_position.m_y + 100 };
	
	//Here will be change with collision of map that it doesnt fall
	if (m_RealPosition.m_y < 470 )
	{ 
		m_Gravity* deltaTime;
		m_velocity += m_Gravity;
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

	if(isLookingRight) m_Fireball.m_Velocity.m_x= 5;
	else  m_Fireball.m_Velocity.m_x = -5;


	isShooting = true;
	
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
	bool moveUp = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_UP);
	bool moveDown = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_DOWN);
	bool attack1 = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_Q);
	bool attack2 = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_W);
	bool isJumpPressed = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_D);
	
	if		(moveRight)		{  move(15); m_textureID = "mainCharWalkRight";  m_TotalFrames =  8;	}
	else if (moveLeft)		{  move(-15); m_textureID = "mainCharWalkRight"; m_TotalFrames = 8;		}
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
	//std::cout << m_RealPosition.m_x << std::endl;
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

