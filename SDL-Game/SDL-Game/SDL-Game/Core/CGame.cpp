#include "CGame.h"
#include "SDL_image.h"
#include <iostream>

#include "../Managers/CTextureManager.h"
#include "../Game Objects/CLoadParams.h"
#include"../Menu/MainMenu/CMenuStates.h"
#include "../Menu/PauseMenu/CPauseStates.h"
#include "../Game Objects/CStableObject.h"
#include "../Game Objects/CEnemy.h"
#include <typeinfo>
#include "../Parser/CMapParser.h"
//Static game variable initilazation
//CGame* CGame::s_Instance = 0;

bool CGame::init(const char* iTitle, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{ 
		std::cout << "SDL init fail\n"; return false;
	}

		//Set window's flag
		int flags = 0;
		//else { flags = SDL_WINDOW_SHOWN; }
		if (fullscreen) flags = SDL_WINDOW_FULLSCREEN;
		else flags = (SDL_WINDOW_SHOWN ); 
		//Create window
		m_pWindow = SDL_CreateWindow(iTitle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);

		if (m_pWindow == NULL) {	std::cout << "Window creation fail\n"; return false; }

		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

		if (m_pRenderer == NULL) { std::cout << "Renderer creation faile\n"; return false; }

		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

		m_bRunning = true;

		//Register objects types from xml
		m_ObjectFactory.registerTypeID("CPlayer", new CPlayerCreator());
		m_ObjectFactory.registerTypeID("CStableObject", new CStableObjectsCreator());
		m_ObjectFactory.registerTypeID("CEnemy", new CEnemyCreator ());


		m_MapParser.parseMap("Assets/Map/darkMap.tmx", "MAP");
		m_GameMap = std::move(m_MapParser.getMap("MAP"));

		//Start main menu		
		m_GameStateMachine.reset(new CGameStateMachine);
		m_GameStateMachine->pushState(std::make_unique<CMenuStates>());

		return true;

}
void CGame::update()
{
	//Update all states
	m_GameStateMachine->update();
}
void CGame::render()
{
	//Render all states
	SDL_RenderClear(m_pRenderer);

	m_GameStateMachine->render();
	

	SDL_RenderPresent(m_pRenderer);
}
void CGame::handleEvents()
{
	mouseEvents.update();

	m_KeyboardEvents.update();

}
//Clean game
void CGame::clean()
{
	std::cout << "Cleaning game\n";

	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}

void CGame::quit()
{
	m_bRunning = false;
}
