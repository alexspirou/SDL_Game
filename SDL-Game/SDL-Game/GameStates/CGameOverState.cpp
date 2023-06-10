#include "CGameOverState.h"
#include "../Parser/CStateParser.h"
#include "../Managers/CTextureManager.h"
#include "../ScreenDimentions.h"
#include "../Menu/MainMenu/CMenuStates.h"

bool CGameOverState::onEnter()
{

    m_GameOver.reset(new CGameOver(new FontStruct(0, 100, 75, 250, { 128,0,128 })));
    return false;
}
void CGameOverState::update(double dt)
{
    m_GameOver->update();
    auto isF2Pressed = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_F2);
    auto isF10Pressed = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_F10);
    auto isF12Pressed = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_F12);

    if (isF2Pressed)
    {
        CGame::Instance().getStateMachine()->changeState(std::make_unique<CPlayerStates>());
    }
    else if(isF10Pressed)
    {
        CGame::Instance().getStateMachine()->changeState(std::make_unique<CMenuStates>());
    }
    else if (isF12Pressed)
    {
        CGame::Instance().quit();
    }
}

void CGameOverState::render()
{
    m_GameOver->render();
}

bool CGameOverState::onExit()
{
    // Clean textures 
    return false;
}
