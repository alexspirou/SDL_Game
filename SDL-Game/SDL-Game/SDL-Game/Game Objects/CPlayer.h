#pragma once
#include "CGameObject.h"
#include "../Factories/CBaseCreator.h"
#include "../Helper/CTimer.h"
#include "../Game Objects/Fireballs/CFireBall.h"
#include "../Collision/ColliderBox.h"

class CPlayer : public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer() = default;

	virtual void draw();
	virtual void update(double dt);
	virtual void clean();
	CFireBall& getFireball() { return m_Fireball; }

	bool isFall = false;
private:

	Vector2D m_Gravity;
	Vector2D m_Force;
	double m_Mass;
	int m_TimeTillRevive;
	bool isLookingRight = true;

	CFireBall m_Fireball;
	
	//Input handlers
	void handleMouseClickEvents();
	void handleKeyBoardEvents();

	//Player's abilities
	void move(float velocity);
	void moveUpDown(float velocity);
	void jump();
	bool applyGravity();
	void shootFireBall(); bool isShooting = false;
	void shootingScreenLimitsReuse();
};

class CPlayerCreator : public CBaseCreator
{
	// Inherited via CBaseCreator
	virtual CPlayer* createGameObject() const override
	{
		return new CPlayer();
	}
};