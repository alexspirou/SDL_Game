#pragma once
#include "CGameObject.h"
#include "../Factories/CBaseCreator.h"
#include "../Helper/CTimer.h"

class CPlayer : public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer() = default;

	virtual void draw();
	virtual void update();
	virtual void clean();
private:

	void manageSounds(int sound);

	void handleMouseClickEvents();

	void handleMouseMotionEvents();

	void handleKeyBoardEvents();

	bool isLookingRight = true;
	CTimer timer;
};


class CPlayerCreator : public CBaseCreator
{
	// Inherited via CBaseCreator
	virtual CPlayer* createGameObject() const override
	{
		return new CPlayer();
	}
};