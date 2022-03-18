#pragma once
#include "CGameObject.h"
#include "../Factories/CBaseCreator.h"
#include "../Game Objects/CPlayer.h"
class CEnemy : public CGameObject
{
public:

	CEnemy();

	virtual void draw();
	virtual void update(double dt);
	virtual void clean();
	void move(double velocity);

private:
	bool moveRight = true;
	bool isNear = false;
};

class CEnemyCreator : public CBaseCreator
{
	// Factory for enemy objects
	virtual CEnemy* createGameObject() const override
	{
		return new CEnemy();
	}
};
