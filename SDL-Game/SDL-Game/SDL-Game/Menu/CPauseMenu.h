#pragma once
#include "../Game Objects/CGameObject.h"
#include "../Game Objects/CLoadParams.h"

class CPauseMenu : public CGameObject
{
public:

	CPauseMenu(const CLoadParams pParams, void(*callbackFunction)());
	CPauseMenu(const CLoadParams pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();


private:
	int m_Frame{ 1 };
	void (*m_callback)();




};