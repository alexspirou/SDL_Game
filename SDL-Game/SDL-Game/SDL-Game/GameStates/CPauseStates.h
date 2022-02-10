#pragma once
#include "IGameStates.h"
#include "../Menu/CPauseMenu.h"
#include <memory>

class CPauseStates : public IGameStates
{
public:
	virtual void update() override;
	virtual void render() override ;
	virtual bool onEnter()override;
	virtual bool onExit() override;

	virtual std::string getStateID() const override { return m_MenuID; }


private:
	
	std::unique_ptr<CPauseMenu> m_PauseMenu;
	static void s_PauseCallback();
	const std::string m_MenuID{ "MENU" };
	
};

