#pragma once
#include <SDL.h>

//Standar includes
#include <string>
#include <memory>
#include <vector>
#include <iostream>

//Games classes
#include "../Game Objects/CPlayer.h"
#include "../Game Objects/CGameObject.h"
#include "../Game Objects/CEnemy.h"
//Map
#include "../Map/CGameMap.h"
#include "../Parser/CMapParser.h"
//Input handlers
#include "../Controllers/CKeyBoardEvents.h"
#include "../Controllers/CMouseEvents.h"

//Game States
#include "../GameStates/CPlayerStates.h"
#include "../GameStates/CGameStateMachine.h"


//Factories
#include "../Factories/CGameObjectFactory.h"

class CGame
{
public:

	
	//Delete copy constructor to avoid copying singleton
	CGame(const CGame&) = delete;
	CGame & operator=(const CGame&) = delete;

	//Singleton construction
	static CGame& Instance()
	{
		if (s_Instance == NULL) s_Instance.reset(new CGame());
		else { return *s_Instance; }
	}


	bool init(const char* iTitle, int xPos, int yPos, int width, int height, bool foolscreen);

	void render();

	void update();

	void handleEvents();

	void clean();

	void quit();

	inline auto getRenderer()					{ return m_pRenderer; }
	inline const bool isRunning()				{ return m_bRunning; }
	inline auto &getMouseEvents()				{ return mouseEvents; }
	inline auto &getKeyboardEvents()			{ return m_KeyboardEvents; }
	inline auto &getStateMachine()				{ return m_GameStateMachine; }
	inline auto& getObjectFactory()				{ return m_ObjectFactory; }
	inline auto& getMap()						{ return m_GameMap; }
private:
	~CGame()
	{
		std::cout << __FUNCSIG__ << std::endl;
	}

	CGame()
	{
		std::cout << __FUNCSIG__ << std::endl;
	}

	//Private members

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;

	CMouseEvents mouseEvents;
	CKeyboardEvents m_KeyboardEvents;
	CGameObjectFactory m_ObjectFactory;
	CMapParser m_MapParser;
	CGameMap* m_GameMap;

	std::unique_ptr<CGameStateMachine> m_GameStateMachine;

	struct Deleter
	{
		void operator()(CGame* p)
		{
			delete p;
		}
	};
	//Static variable for singleton
	inline static std::unique_ptr<CGame, Deleter> s_Instance{};
};

