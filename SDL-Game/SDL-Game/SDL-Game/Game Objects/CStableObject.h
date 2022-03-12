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
	virtual void load(CLoadParams* params) override;
	int m_SpawnTime = 0;
	
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