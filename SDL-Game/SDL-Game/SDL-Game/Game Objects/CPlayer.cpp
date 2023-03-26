#include "CPlayer.h"
#include "../ScreenDimentions.h"
#include "../Core/CGame.h"
#include "../Managers/CTextureManager.h"
#include "../Parser/CStateParser.h"


CPlayer::CPlayer() :
	m_Gravity{0, 2.9}, m_Force{0, 0}, m_Mass{1} // TODO : Move them to XML
{
	CGame::Instance().getSoundManager().loadSound("jumpSound", "Assets/Music/jump.wav");
	CGame::Instance().getSoundManager().loadSound("fireBall", "Assets/MainChar/Sounds/fireBall.wav ");
	feetCollider = { 0,0,0,0 };
	CStateParser stateParser;

	stateParser.parseState("XML/playerFireBalls.xml", "CPLAYERFIREBALLS", &m_vTexturedIDs, &m_Fireball);

}
void CPlayer::drawFrame()
{
	Vector2D m_RealPosition{ m_position.m_x + 100 , m_position.m_y + 100 };
	
	if(m_Fireball[m_FireballIndex]->m_position.m_x > m_RealPosition.m_x ) m_Fireball[m_FireballIndex]->draw();
	//CTextureManager::Instance().drawColliderBox(CGame::Instance().getRenderer(), feetCollider);

	std::cout <<  "Fireball : " << m_Fireball[m_FireballIndex]->m_position.m_x << std::endl;
	std::cout << "Player : " << m_RealPosition.m_x << std::endl;

	CGameObject::drawFrame();
}

void CPlayer::update(double dt)
{
	Vector2D m_RealPosition{ m_position.m_x + 100 , m_position.m_y + 100 };


	if (!isShooting || m_Fireball[m_FireballIndex]->m_position.m_x > SCREEN_WIDTH ||  m_Fireball[m_FireballIndex]->m_position.m_x < -m_Fireball[m_FireballIndex]->getWidth()) 
	{ 
		m_Fireball[m_FireballIndex]->m_position = m_RealPosition;

		isShooting = false; 
	}
	std::cout << "Player Update : " << m_RealPosition.m_x << std::endl;

	if (!applyGravity())
	{
		handleKeyBoardEvents();
	}
	else
	{
		bool moveRight = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_RIGHT);
		bool moveLeft = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_LEFT);

		if(moveRight && !isLookingRight) move(10);
		if (moveLeft && isLookingRight) move(-10);

	}
	m_Fireball[m_FireballIndex]->update(deltaTime);
	
	m_Force += m_Gravity;
	m_Force  = (m_Force / m_Mass )* dt;	

	updateAbilitiesCouldDowns();

	CGameObject::update(dt);
	// Update feet collider
	feetCollider = { m_ColliderBox.x, m_ColliderBox.y + m_ColliderBox.h, 40, 10 };


}

// Private Functions

void CPlayer::jump()
{
	m_velocity = 0;
	m_textureID = "mainCharIdle";

	if (isLookingRight) 
	{
		m_velocity.m_x = 5; 
		m_velocity.m_y = -10;
		m_position = m_position + m_velocity * deltaTime;
		m_velocity = m_velocity + m_Gravity;

		CGame::Instance().getSoundManager().playSound("jumpSound", 40);
	}
	else if (!isLookingRight)
	{
		m_velocity.m_x = -5;
		m_velocity.m_y = -10;
		m_position = m_position + m_velocity * deltaTime;
		m_velocity = m_velocity + m_Gravity;

		CGame::Instance().getSoundManager().playSound("jumpSound", 40);
	}
}
bool CPlayer::applyGravity()
{
	if (isFall)
	{ 
		m_Gravity.m_y = 2;
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
	if(m_Fireball[m_FireballIndex]->m_position.m_x == m_RealPosition.m_x)
		CGame::Instance().getSoundManager().playSound("fireBall", 15);

	if(isLookingRight) m_Fireball[m_FireballIndex]->m_Velocity.m_x = 40 * deltaTime;
	else  m_Fireball[m_FireballIndex]->m_Velocity.m_x = -40 * deltaTime;

	isShooting = true;
	
}

void CPlayer::attack1()
{
	
	if (isQHasCoulDown)
	{
		m_FireballIndex = 0;
		shootFireBall();
		move(0);
		m_textureID = "mainCharAttack1";
		m_TotalFrames = 8;

		// Coulddown
		m_Timer.start();
		m_QCoulDown = m_Timer.getTicks();
		isQHasCoulDown = false;
	}
	else
	{
		std::cout << "NO CD FOR Q " << std::endl;
	}

}

void CPlayer::attack2()
{

	m_FireballIndex = 1; 
	move(0);
	shootFireBall(); 
	m_textureID = "mainCharAttack2";
	m_TotalFrames = 8;
}

//void CPlayer::handleMouseMotionEvents()
//{
//	auto mouseEvents = CGame::Instance().getMouseEvents().getMousePosition();
//
//	m_position = mouseEvents;
//}

void CPlayer::updateAbilitiesCouldDowns()
{
	if (m_Timer.getTicks() > m_QCoulDown + 3000) { isQHasCoulDown = true; m_Timer.stop(); }

	if (m_Timer.getTicks() > m_WCoulDown + 3000) { isWHasCoulDown = true; m_Timer.stop(); }

}

void CPlayer::handleKeyBoardEvents()
{
	//Change this to switch statements

	bool moveRight = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_RIGHT);
	bool moveLeft = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_LEFT);
	bool moveUp = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_UP);
	bool moveDown = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_DOWN);
	bool isPressingQ = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_Q);
	bool isPressingW = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_W);
	bool isJumpPressed = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_D);
	
	if (moveRight) { move(20); m_textureID = "mainCharWalkRight";  m_TotalFrames = 8; }
	else if (moveLeft) { move(-20); m_textureID = "mainCharWalkRight"; m_TotalFrames = 8; }
	else if (isJumpPressed) {
		jump(); std::cout << "jump" << std::endl;
	}
	else if (moveUp) { moveUpDown(-10); m_textureID = "mainCharIdle"; m_TotalFrames = 8; }
	else if (moveDown) { moveUpDown(10); m_textureID = "mainCharIdle"; m_TotalFrames = 8; }
	else if (isPressingQ) { attack1();  }
	else if (isPressingW)	{  attack2(); }
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

	if (m_RealPosition.m_x >= 0  && velocity < 0 && !isFall)
	{
		isLookingRight = false;
		m_FlipSiderRender = SDL_FLIP_HORIZONTAL;
		m_velocity.m_x = velocity * deltaTime;
		m_velocity.m_y = 0;
	}
	else if (velocity > 0 && !isFall)
	{
		isLookingRight = true;
		m_FlipSiderRender = SDL_FLIP_NONE;
		m_velocity.m_x = velocity * deltaTime;
		m_velocity.m_y = 0;

	}
	else if(!isFall)
	{
		m_velocity = 0;
	}

	// Moving whlie is junping
	else if (m_RealPosition.m_x >= 0 && velocity < 0 &&  isFall)
	{
		isLookingRight = false;
		m_FlipSiderRender = SDL_FLIP_HORIZONTAL;
		m_velocity.m_x = velocity * deltaTime;
	}
	else if (velocity > 0 && isFall)
	{
		isLookingRight = true;
		m_FlipSiderRender = SDL_FLIP_NONE;
		m_velocity.m_x = velocity * deltaTime;

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
