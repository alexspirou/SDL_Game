#pragma once
#include "CGameObject.h"
#include "../Factories/CBaseCreator.h"

class CStableObject :  public CGameObject
{
public:
	virtual void draw();
	virtual void drawFrame();
	virtual void update(double dt);
	virtual void clean();

private:

};

class CStableObjectsCreator : public CBaseCreator
{
	// Inherited via CBaseCreator
	virtual CStableObject* createGameObject() const override
	{
		return new CStableObject();
	}
};