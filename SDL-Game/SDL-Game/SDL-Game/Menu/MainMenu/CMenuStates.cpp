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
    CGame::Instance().getSoundManager().loadSound("menuChange","D:/repos/SDL_Game/SDL-Game/SDL-Game/SDL-Game/Assets/Music/menuChange.wav");
    CGame::Instance().getSoundManager().loadSound("welcomeToGame", "D:/repos/SDL_Game/SDL-Game/SDL-Game/SDL-Game/Assets/Music/welcomeToGame.wav");

    return true;
}

void CMenuStates::update(double dt)
{
    MoveMenuPosition();

    updateMenuDependTheMenuPosition(dt);
}
void CMenuStates::render()
{
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
       
        if      (m_MenuPositionInScreen == Menu::START)     { CGame::Instance().getSoundManager().playSound("menuChange", menuSoundVolume); m_MenuPositionInScreen = Menu::OPTIONS; }
        else if (m_MenuPositionInScreen == Menu::OPTIONS)   { CGame::Instance().getSoundManager().playSound("menuChange", menuSoundVolume); m_MenuPositionInScreen = Menu::EXIT; }

    }
    auto UpArrowIsPressed = keyboardEvents.isKeyDown(SDL_SCANCODE_UP);
    if (UpArrowIsPressed)
    {

        if      (m_MenuPositionInScreen == Menu::EXIT)       { CGame::Instance().getSoundManager().playSound("menuChange", menuSoundVolume); m_MenuPositionInScreen = Menu::OPTIONS; }
        else if (m_MenuPositionInScreen == Menu::OPTIONS)    { CGame::Instance().getSoundManager().playSound("menuChange", menuSoundVolume); m_MenuPositionInScreen = Menu::START; }

    }
    SDL_Delay(80);
}

void CMenuStates::updateMenuDependTheMenuPosition(double dt)
{
    if      (m_MenuPositionInScreen == Menu::START)          m_vGameObjects[START]->update(dt);
    else if (m_MenuPositionInScreen == Menu::OPTIONS)        m_vGameObjects[OPTIONS]->update(dt);
    else if (m_MenuPositionInScreen == Menu::EXIT)           m_vGameObjects[EXIT]->update(dt);
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
    CLoadParams  startMenuParams =  { 0, 0, x, y ,m_LoadIDMenuStart,0 ,""};
    CLoadParams  optionsMenuParams = { 0, 0, x, y ,m_LoadIDMenuOptions,0 ,"" };
    CLoadParams  exietMenuParams = { 0, 0, x, y ,m_LoadIDMenuExit,0,"" };

    auto startMenu = std::make_unique<CMenu>(s_StarGame);
    auto optionsMenu = std::make_unique<CMenu>( s_Options);
    auto exitMenu = std::make_unique<CMenu>( s_ExitGame);
    startMenu->load(&startMenuParams);
    optionsMenu->load(&optionsMenuParams);
    exitMenu->load(&exietMenuParams);

    m_vGameObjects.push_back(std::move(startMenu));
    m_vGameObjects.push_back(std::move(optionsMenu));
    m_vGameObjects.push_back(std::move(exitMenu));

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
