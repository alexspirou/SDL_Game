#pragma once
#include "CGameObject.h"
#include "../Factories/CBaseCreator.h"
class CEnemy : public CGameObject
{
public:

	CEnemy() = default;

	virtual void draw();
	virtual void update();
	virtual void clean();
	void test() {}
private:
	void move();
	bool moveRight = true;
};

class CEnemyCreator : public CBaseCreator
{
	// Factory for enemy objects
	virtual CGameObject* createGameObject() const override
	{
		return new CEnemy();
	}
};
