#pragma once
#include "CFireBall.h"
class CPlayerFireBall : public CFireBall
{
public:
	CPlayerFireBall();
	virtual void draw();
	virtual void update(double dt);
	virtual void clean();


private:

};

