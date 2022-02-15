#pragma once
#include "CGameObject.h"
class CEnemy : public CGameObject
{
public:

	CEnemy() = default;

	virtual void draw();
	virtual void update();
	virtual void clean();

private:

};

