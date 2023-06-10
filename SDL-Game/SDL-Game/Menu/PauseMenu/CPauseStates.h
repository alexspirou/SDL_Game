#pragma once
#include "../../GameStates/IGameStates.h"
#include "CPauseMenu.h"
#include <memory>

class CPauseStates : public IGameStates
{
public:
	virtual void update(double dt) override;
	virtual void render() override ;
	virtual bool onEnter()override;
	virtual bool onExit() override;

	virtual std::string getStateID() const override { return m_MenuID; }


private:
	
	std::unique_ptr<CPauseMenu> m_PauseMenu;
	static void s_PauseCallback(int* oCurrentFram); // callback should be static
	const std::string m_MenuID{ "PAUSE MENU" };
};

