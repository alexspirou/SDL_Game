#pragma once
#include "../../Game Objects/CGameObject.h"
#include "../../Game Objects/CLoadParams.h"

class CPauseMenu : public CGameObject
{
public:

	CPauseMenu(void(*callbackFunction)(int*));
	CPauseMenu();
	virtual void drawFrame();
	virtual void update(double dt);
	virtual void clean();
	enum PauseMenu { RESTART = 0, OPTIONS = 1, MAINMENU = 2, CANCEL = 3 };

private:
	int m_Frame{ 1 };
	void (*m_callback)(int* currentRow);
};