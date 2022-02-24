#pragma once
#include "CGameObject.h"
#include "../Factories/CBaseCreator.h"


class CPlayer : public CGameObject
{
public:
	CPlayer();
	virtual ~CPlayer() = default;

	virtual void draw();
	virtual void update();
	virtual void clean();
	void manageSounds(int sound);
private:

	void handleMouseClickEvents();

	void handleMouseMotionEvents();

	void handleKeyBoardEvents();

	bool isLookingRight = true;

};


class CPlayerCreator : public CBaseCreator
{
	// Inherited via CBaseCreator
	virtual CGameObject* createGameObject() const override
	{
		return new CPlayer();
	}
};