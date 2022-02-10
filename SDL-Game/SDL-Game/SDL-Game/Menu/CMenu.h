#pragma once
#include "../Game Objects/CGameObject.h"
#include "../Game Objects/CLoadParams.h"

class CMenu : public CGameObject
{
public:

	CMenu(const CLoadParams pParams, void(*callbackFunction)());
	CMenu(const CLoadParams pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();


private:

	void (*m_callback)();




};

