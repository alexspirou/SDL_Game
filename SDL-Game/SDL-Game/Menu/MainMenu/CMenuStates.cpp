#include "CMenuStates.h"
#include <iostream>

#include "../../Core/CGame.h"
#include "../../Managers/CTextureManager.h"
#include "../../Game Objects/CLoadParams.h"
#include "CMenu.h"

#include "../../ScreenDimentions.h"
//Public functions

bool CMenuStates::onEnter()
{
	loadMenuObjects();
	CGame::Instance().getSoundManager().loadSound("menuChange", "Assets/Music/menuChange.wav");
	CGame::Instance().getSoundManager().loadSound("welcomeToGame", "Assets/Music/welcomeToGame.wav");

	return true;
}

void CMenuStates::update(double dt)
{
	
	UpdateMenuSelection(dt);
}
void CMenuStates::render()
{
	RenderMenuSelection();

}

bool CMenuStates::onExit()
{
	for (auto& menuObject : m_MenuObjects)
	{
		menuObject->clean();
	}

	CTextureManager::Instance().clearTextureMap(m_LoadIDMenuStart);
	CTextureManager::Instance().clearTextureMap(m_LoadIDMenuOptions);
	CTextureManager::Instance().clearTextureMap(m_LoadIDMenuExit);

	CGame::Instance().getSoundManager().clean("menuChange");
	CGame::Instance().getSoundManager().clean("welcomeToGame");

	return true;
}
//Helper private functions

void CMenuStates::MoveMenuPosition()
{
	auto keyboardEvents = CGame::Instance().getKeyboardEvents();
	int menuSoundVolume = 50;

	auto DownArrowIsPressed = keyboardEvents.isKeyDown(SDL_SCANCODE_DOWN);
	if (DownArrowIsPressed)
	{
		CGame::Instance().getSoundManager().playSound("menuChange", menuSoundVolume);

		if (m_MenuPositionInScreen == START)
		{
			m_MenuPositionInScreen = OPTIONS;
		}
		else if (m_MenuPositionInScreen == OPTIONS)
		{
			m_MenuPositionInScreen = EXIT;
		}

	}
	auto UpArrowIsPressed = keyboardEvents.isKeyDown(SDL_SCANCODE_UP);
	if (UpArrowIsPressed)
	{
		CGame::Instance().getSoundManager().playSound("menuChange", menuSoundVolume);

		if (m_MenuPositionInScreen == EXIT)
		{
			m_MenuPositionInScreen = OPTIONS;
		}
		else if (m_MenuPositionInScreen == OPTIONS)
		{
			m_MenuPositionInScreen = START;
		}

	}
	SDL_Delay(80);
}

void CMenuStates::UpdateMenuSelection(double dt)
{
	MoveMenuPosition();

	switch (m_MenuPositionInScreen)
	{
		case START:
			m_MenuObjects[START]->update(dt);
			break;
		case OPTIONS:
			m_MenuObjects[OPTIONS]->update(dt);
			break;
		case EXIT:
			m_MenuObjects[EXIT]->update(dt);
			break;
	}

}

void CMenuStates::RenderMenuSelection()
{
	switch (m_MenuPositionInScreen)
	{
	case START:
		m_MenuObjects[START]->draw();
		break;
	case OPTIONS:
		m_MenuObjects[OPTIONS]->draw();
		break;
	case EXIT:
		m_MenuObjects[EXIT]->draw();
		break;
	}
}



bool CMenuStates::loadMenuObjects()
{
	//Load and initialazation of menu pngs
	auto render = CGame::Instance().getRenderer();

	auto loadStartMenu = CTextureManager::Instance().loadImage("Assets/Menu/menuStart.png", m_LoadIDMenuStart, render);
	auto loadOptionMenu = CTextureManager::Instance().loadImage("Assets/Menu/menuOptions.png", m_LoadIDMenuOptions, render);
	auto loadExitMenu = CTextureManager::Instance().loadImage("Assets/Menu/menuExit.png", m_LoadIDMenuExit, render);

	if (!loadStartMenu || !loadOptionMenu || !loadExitMenu) { return false; }

	int x = SCREEN_WIDTH; int y = SCREEN_HEIGHT;

	auto startMenu = std::make_unique<CMenu>(s_StarGame);
	auto optionsMenu = std::make_unique<CMenu>(s_Options);
	auto exitMenu = std::make_unique<CMenu>(s_ExitGame);
	startMenu->load(new CLoadParams(0, 0, x, y, m_LoadIDMenuStart, 0, "", NULL));
	optionsMenu->load(new CLoadParams(0, 0, x, y, m_LoadIDMenuOptions, 0, "", NULL));
	exitMenu->load(new CLoadParams(0, 0, x, y, m_LoadIDMenuOptions, 0, "", NULL));

	m_MenuObjects.push_back(std::move(startMenu));
	m_MenuObjects.push_back(std::move(optionsMenu));
	m_MenuObjects.push_back(std::move(exitMenu));

	m_FontManager.loadFont("Assets/Fonts/ARCADECLASSIC.ttf", 20);

	return true;
}

//Callbacks

void CMenuStates::s_StarGame()
{
	CGame::Instance().getSoundManager().playSound("welcomeToGame", 50);
	//In the future will change to LevelStates, where the first stage of the game will load
	CGame::Instance().getStateMachine()->changeStateAndPopPrevious(std::make_unique<CPlayerStates>());
}

void CMenuStates::s_ExitGame()
{
	CGame::Instance().quit();
}

void CMenuStates::s_Options()
{
	std::cout << "Options" << std::endl;
}
