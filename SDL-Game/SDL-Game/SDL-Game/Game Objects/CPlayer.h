#pragma once
#include "CGameObject.h"
#include "../Factories/CBaseCreator.h"
#include "../Helper/CTimer.h"
#include "../Game Objects/Fireballs/CFireBall.h"

class CPlayer : public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer() = default;

	virtual void draw();
	virtual void update(double dt);
	virtual void clean();

	int getWidth() { return (m_width/m_TotalFrames) - 100; }
private:
	Vector2D m_Gravity{ 0, 1 };

	bool isLookingRight = true;

	CFireBall m_Fireball;

	void manageSounds(int sound);

	void handleMouseClickEvents();

	void handleMouseMotionEvents();

	void handleKeyBoardEvents();

	//Player's abilities

	void move(float velocity);
	void moveUpDown(float velocity);
	void jump();
	bool applyGravity();
	void shootFireBall(); bool isShooting = false;

};


class CPlayerCreator : public CBaseCreator
{
	// Inherited via CBaseCreator
	virtual CPlayer* createGameObject() const override
	{
		return new CPlayer();
	}
};