#pragma once
#include "CGameObject.h"
#include "../Factories/CBaseCreator.h"
#include "../Helper/CTimer.h"
#include "../Game Objects/Fireballs/CPlayerFireBall.h"
#include "../Collision/ColliderBox.h"

class CPlayer : public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer() = default;

	virtual void drawFrame();
	virtual void update(double dt);
	virtual void clean();
	auto getFireball() { return m_Fireball[m_FireballIndex].get(); }
	void setPositionX(int x) { m_position.m_x = x; }
	bool isFall = false;
	ColliderBox feetCollider;
private:

	Vector2D m_Gravity;
	Vector2D m_Force;
	std::vector<std::string> m_vTexturedIDs;
	double m_Mass;
	int m_TimeTillRevive;
	bool isLookingRight = true;

	std::vector<std::unique_ptr<CPlayerFireBall>> m_Fireball;
	int m_FireballIndex{ 0 };
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