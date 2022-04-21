#pragma once
#include "../../Game Objects/CGameObject.h"
#include "../../Game Objects/CLoadParams.h"

class CMenu : public CGameObject
{
public:

	CMenu(void(*callbackFunction)());
	CMenu() = default;
	virtual void draw();
	virtual void update(double dt) override;
	virtual void clean();

private:

	void (*m_callback)();
};

