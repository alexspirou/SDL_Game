#include "CMenuStates.h"
#include <iostream>

#include "../Core/CGame.h"
#include "../Managers/CTextureManager.h"
#include "../Game Objects/CLoadParams.h"
#include "../Menu/CMenu.h"

#include "../ScreenDimentions.h"
//Public functions

bool CMenuStates::onEnter()
{
    loadMenuObjects();
    auto render = CGame::Instance().getRenderer();
    auto loadAnimatePlayer = CTextureManager::Instance().loadImage("Assets/enemySheet.png", "enemy", render);

    CLoadParams enemy1Params(0, 500, 48, 48, "enemy");
    m_PlayerForMenu.reset(new CEnemy(enemy1Params));

    return true;
}

void CMenuStates::update()
{
    m_PlayerForMenu->update();

    MoveMenuPosition();

    updateMenuDependTheMenuPosition();
}
void CMenuStates::render()
{
    m_PlayerForMenu->drawFrame();

    renderMenuDependTheMenuPosition();

}

bool CMenuStates::onExit()
{
    for (auto& menuObject : m_vGameObjects)
    {
        menuObject->clean();
    }

    CTextureManager::Instance().clearTextureMap(m_LoadIDMenuStart);
    CTextureManager::Instance().clearTextureMap(m_LoadIDMenuOptions);
    CTextureManager::Instance().clearTextureMap(m_LoadIDMenuExit);
    CTextureManager::Instance().clearTextureMap("enemy");

    return true;
}
//Helper private functions

void CMenuStates::MoveMenuPosition()
{
    auto keyboardEvents = CGame::Instance().getKeyboardEvents();

    auto DownArrowIsPressed = keyboardEvents.isKeyDown(SDL_SCANCODE_DOWN);
    if (DownArrowIsPressed)
    {
        if      (m_MenuPositionInScreen == Menu::START)     { m_MenuPositionInScreen = Menu::OPTIONS; }
        else if (m_MenuPositionInScreen == Menu::OPTIONS)   { m_MenuPositionInScreen = Menu::EXIT; }

    }
    auto UpArrowIsPressed = keyboardEvents.isKeyDown(SDL_SCANCODE_UP);
    if (UpArrowIsPressed)
    {
        if      (m_MenuPositionInScreen == Menu::EXIT)       { m_MenuPositionInScreen = Menu::OPTIONS; }
        else if (m_MenuPositionInScreen == Menu::OPTIONS)    { m_MenuPositionInScreen = Menu::START; }

    }
    SDL_Delay(80);
}

void CMenuStates::updateMenuDependTheMenuPosition()
{
    if      (m_MenuPositionInScreen == Menu::START)          m_vGameObjects[START]->update();
    else if (m_MenuPositionInScreen == Menu::OPTIONS)        m_vGameObjects[OPTIONS]->update();
    else if (m_MenuPositionInScreen == Menu::EXIT)           m_vGameObjects[EXIT]->update();
}

void CMenuStates::renderMenuDependTheMenuPosition()
{
    if      (m_MenuPositionInScreen == Menu::START)         m_vGameObjects[START]->draw();
    else if (m_MenuPositionInScreen == Menu::OPTIONS)       m_vGameObjects[OPTIONS]->draw();
    else if (m_MenuPositionInScreen == Menu::EXIT)          m_vGameObjects[EXIT]->draw();
}



bool CMenuStates::loadMenuObjects()
{
    //Load and initialasation of menu pngs
    auto render = CGame::Instance().getRenderer();
    auto loadStartMenu = CTextureManager::Instance().loadImage("Assets/Menu/menuStart.png", m_LoadIDMenuStart, render);
    auto loadOptionMenu = CTextureManager::Instance().loadImage("Assets/Menu/menuOptions.png", m_LoadIDMenuOptions, render);
    auto loadExitMenu = CTextureManager::Instance().loadImage("Assets/Menu/menuExit.png", m_LoadIDMenuExit, render);

    if (!loadStartMenu || !loadOptionMenu || !loadExitMenu) { return false; }

    int x = SCREEN_WIDTH; int y = SCREEN_HEIGHT;
    CLoadParams  startMenuParams =  { 0, 0, x, y ,m_LoadIDMenuStart };
    CLoadParams  optionsMenuParams = { 0, 0, x, y ,m_LoadIDMenuOptions };
    CLoadParams  exietMenuParams = { 0, 0, x, y ,m_LoadIDMenuExit };

    auto startMenu = std::make_unique<CMenu>(startMenuParams, s_StarGame);
    auto optionsMenu = std::make_unique<CMenu>(optionsMenuParams, s_Options);
    auto exitMenu = std::make_unique<CMenu>(exietMenuParams, s_ExitGame);

    m_vGameObjects.push_back(std::move(startMenu));
    m_vGameObjects.push_back(std::move(optionsMenu));
    m_vGameObjects.push_back(std::move(exitMenu));

    m_FontManager.loadFont("Assets/Fonts/ARCADECLASSIC.ttf", 20);

    return true;
}

//Callbacks

void CMenuStates::s_StarGame()
{
    std::cout << "Play button clicked\n";
    //In the future will change to LevelStates, where the first stage of the game will load
    CGame::Instance().getStateMachine()->changeState(std::make_unique<CPlayerStates>());
}

void CMenuStates::s_ExitGame()
{
    std::cout << "EXIT GAME " << std::endl;
    CGame::Instance().quit();
}

void CMenuStates::s_Options()
{
    std::cout << "Options" << std::endl;
}
