#pragma once
#include "CGameObject.h"
#include "../Factories/CBaseCreator.h"
class CStableObjects :  public CGameObject
{
public:
	virtual void draw();
	virtual void drawFrame();
	virtual void update();
	virtual void clean();
};

class CStableObjectsCreator : public CBaseCreator
{
	// Inherited via CBaseCreator
	virtual std::unique_ptr<CGameObject> createGameObject() const override
	{
		return std::make_unique<CStableObjects>();
	}
};