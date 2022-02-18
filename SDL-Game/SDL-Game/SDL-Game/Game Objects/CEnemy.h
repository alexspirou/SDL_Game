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
	
private:
	void move();
	bool moveRight = true;
};

class CEnemyCreator : public CBaseCreator
{
	// Inherited via CBaseCreator
	virtual std::unique_ptr<CGameObject> createGameObject() const override
	{
		return std::make_unique<CEnemy>();
	}
};
