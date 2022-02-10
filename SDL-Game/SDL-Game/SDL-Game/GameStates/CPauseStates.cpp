#include "CPauseStates.h"
#include "../Core/CGame.h"
#include "../ScreenDimentions.h"
#include "../Managers/CTextureManager.h"
#include "../Game Objects/CLoadParams.h"

bool CPauseStates::onEnter()
{
    //Load and initialasation of menu pngs
    auto render = CGame::Instance().getRenderer();
    auto pauseMenu = CTextureManager::Instance().loadImage("Assets/PauseMenu/pauseMenu.png", "pauseMenu", render);

    if (!pauseMenu) { return false; }

    int x = SCREEN_WIDTH * 4; int y = SCREEN_HEIGHT;
    CLoadParams  startMenuParams = { 0, 0, x, y ,"pauseMenu" };

    m_PauseMenu.reset(new CPauseMenu(startMenuParams, s_PauseCallback));

    return true;
}

void CPauseStates::update()
{
    m_PauseMenu->update();
}

void CPauseStates::render()
{
    m_PauseMenu->draw();
}
bool CPauseStates::onExit()
{
    return true;
}

void CPauseStates::s_PauseCallback()
{
    //TODO : Here write the logic, if 1st col is pressed do someting etc..
    //TODO : check why the main player doens't show after popback

    CGame::Instance().getStateMachine()->popState();
   

}

