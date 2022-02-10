#include "CGame.h"
#include "SDL_image.h"
#include <iostream>

#include "../Managers/CTextureManager.h"
#include "../Game Objects/CLoadParams.h"
#include"../GameStates/CMenuStates.h"
#include "../GameStates/CPauseStates.h"

#include <typeinfo>
//Static game variable initilazation
//CGame* CGame::s_Instance = 0;

bool CGame::init(const char* iTitle, int xPos, int yPos, int width, int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { std::cout << "SDL init fail\n"; return false; }
		std::cout<< "SDL init success\n";

		//Set window's flag
		int flags = 0;
		if (fullscreen) { flags = SDL_WINDOW_FULLSCREEN; }
		else { flags = SDL_WINDOW_SHOWN; }
		//Create window
		m_pWindow = SDL_CreateWindow(iTitle, xPos, yPos, width, height, flags);

		if (m_pWindow == NULL) {	std::cout << "Window creation fail\n"; return false; }

		std::cout << "Window creation success\n";
		m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

		if (m_pRenderer == NULL) { std::cout << "Renderer creation faile\n"; return false; }


		std::cout << "Renderer creation success\n";
		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

		std::cout << "Init success\n";
		m_bRunning = true;


		//Menu function

		m_GameStateMachine.reset(new CGameStateMachine);

		//m_GameStateMachine->pushState(std::unique_ptr<CMenuStates>(new CMenuStates));



		loadObjects();
		
		allocateObjects();

		addObjectsInVector();

		std::cout << "\n" << typeid(m_Player).name() << '\n';

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

	if (m_KeyboardEvents.isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		//TODO Here change state for pause game

		m_GameStateMachine->changeState(std::make_unique<CPauseStates>());
	}

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

void CGame::loadObjects()
{
	CTextureManager& TextureLoader = CTextureManager::Instance();

	TextureLoader.loadImage("Assets/enemySheet.png", "enemy", CGame::m_pRenderer);
	TextureLoader.loadImage("Assets/mainCharSheet.png", "mainChar", CGame::m_pRenderer);

}

void CGame::allocateObjects()
{
	CLoadParams playerParams(250, 100, 48, 48, "mainChar");
	CLoadParams enemy1Params(400, 100, 48, 48, "enemy");
	CLoadParams enemy2Params(300, 100, 48, 48, "enemy");
	CLoadParams enemy3Params(180, 100, 48, 48, "enemy");

	m_Player.reset(new CPlayer(playerParams));
	m_enemy1.reset(new CEnemy(enemy1Params));
	m_enemy2.reset(new CEnemy(enemy2Params));
	m_enemy3.reset(new CEnemy(enemy3Params));
}

void CGame::addObjectsInVector()
{
	m_GameObjects.push_back(std::move(m_Player));
	m_GameObjects.push_back(std::move(m_enemy1));
	m_GameObjects.push_back(std::move(m_enemy2));
	m_GameObjects.push_back(std::move(m_enemy3));
}
