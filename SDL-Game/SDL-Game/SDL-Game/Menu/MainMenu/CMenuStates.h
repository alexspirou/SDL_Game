#pragma once
#include "../../GameStates/IGameStates.h"
#include "../../Game Objects/CGameObject.h"
#include "../../Managers/CFontTextureManager.h"
#include "../../Game Objects/CEnemy.h"

//Create Render and update menu objects
class CMenuStates : public IGameStates
{
public:

	virtual ~CMenuStates() = default;

	virtual void update(double dt);
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	
	virtual std::string getStateID() const { return s_menuID; }

private:

	//Functions
	
	//Load and initialasation of menu pngs
	bool loadMenuObjects();
	//Changes menu pngs with up/down arrows
	void MoveMenuPosition();

	void renderMenuDependTheMenuPosition();
	void updateMenuDependTheMenuPosition(double dt);

	int m_MenuPositionInScreen = 0;

	//Game Objects

	std::vector<std::unique_ptr<CGameObject>> m_vGameObjects;
	std::unique_ptr<CEnemy> m_PlayerForMenu;

	CFontTextureManager m_FontManager;

	// call back functions for menu items
	static void s_StarGame();
	static void s_ExitGame();
	static void s_Options();

	std::string m_LoadIDMenuStart = "start";
	std::string m_LoadIDMenuOptions = "options";
	std::string m_LoadIDMenuExit = "exit";
	enum Menu
	{
		START = 0,
		OPTIONS = 1,
		EXIT= 2
	};
	bool loadStartMenu;
	const std::string s_menuID {"MENU"};
	enum mouse { MOUSE_OUT = 0, MOUSE_OVER = 1 };
};


