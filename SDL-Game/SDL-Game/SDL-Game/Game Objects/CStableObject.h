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
	virtual void load(CLoadParams* params) override;
	int m_SpawnTime = 0;
	
private:

};

class CStableObjectsCreator : public CBaseCreator
{
	// Inherited via CBaseCreator
	virtual CGameObject* createGameObject() const override
	{
		return new CStableObjects();
	}
};