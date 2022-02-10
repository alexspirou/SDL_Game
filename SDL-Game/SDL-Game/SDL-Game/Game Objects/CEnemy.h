#pragma once
#include "CGameObject.h"
class CEnemy : public CGameObject
{
public:

	CEnemy(CLoadParams params):CGameObject(params) {}

	virtual void draw();
	virtual void update();
	virtual void clean();

private:

};

