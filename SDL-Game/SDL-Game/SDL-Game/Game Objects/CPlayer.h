#pragma once
#include "CGameObject.h"
#include "../Factories/CBaseCreator.h"


class CPlayer : public CGameObject
{
public:
	CPlayer() = default;
	virtual ~CPlayer() = default;

	virtual void draw();
	virtual void update();
	virtual void clean();
	enum playerStand { IDLE = 0, WALKING = 1 };
private:

	void handleMouseClickEvents();

	void handleMouseMotionEvents();

	void handleKeyBoardEvents();
};


class CPlayerCreator : public CBaseCreator
{
	// Inherited via CBaseCreator
	virtual CGameObject* createGameObject() const override
	{
		return new CPlayer();
	}
};