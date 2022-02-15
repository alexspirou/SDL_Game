#include "CPauseStates.h"
#include "../../Core/CGame.h"
#include "../../ScreenDimentions.h"
#include "../../Managers/CTextureManager.h"
#include "../../Game Objects/CLoadParams.h"
#include "../MainMenu/CMenuStates.h"

bool CPauseStates::onEnter()
{
    //Load and initialasation of menu pngs
    auto render = CGame::Instance().getRenderer();
    auto pauseMenu = CTextureManager::Instance().loadImage("Assets/PauseMenu/pauseMenusR.png", "pauseMenusR", render);

    if (!pauseMenu) { return false; }

    int x = SCREEN_WIDTH; int y = SCREEN_HEIGHT;
    CLoadParams  pauseMenuParams = { 0, 0, x, y ,"pauseMenusR" };

    m_PauseMenu.reset(new CPauseMenu(s_PauseCallback));
    m_PauseMenu->load(pauseMenuParams);

    return true;
}

void CPauseStates::update()
{
    m_PauseMenu->update();
}

void CPauseStates::render()
{
    m_PauseMenu->drawFrame();
}
bool CPauseStates::onExit()
{
    return true;
}

void CPauseStates::s_PauseCallback(int* oCurrentFram)
{
    switch (*oCurrentFram)
    {
    case CPauseMenu::RESTART:
        CGame::Instance().getStateMachine()->changeStateAndPopPrevious(std::make_unique<CPlayerStates>());
        break;
    case CPauseMenu::OPTIONS:
        //Create options, like sound etc..
        std::cout << "OPTIONS PAUSE" << std::endl;
        break;
    case CPauseMenu::MAINMENU:
        CGame::Instance().getStateMachine()->changeStateAndPopPrevious(std::make_unique<CMenuStates>());
        break;
    case CPauseMenu::CANCEL:
        CGame::Instance().getStateMachine()->popState();
        break;
    default: //Optional
        std::cout << "No choice in pause menu, check switch statements" << std::endl;
    }
 
}
