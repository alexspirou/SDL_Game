#include "CPlayerStates.h"
#include "../Core/CGame.h"
#include "../Managers/CTextureManager.h"
#include "../Menu/PauseMenu/CPauseStates.h"
void CPlayerStates::update()
{
    m_Player->update();
    auto isESCpressed = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_ESCAPE);
    if (isESCpressed)
    {
        //TODO Here change state for pause game
        CGame::Instance().getStateMachine()->changeState(std::make_unique<CPauseStates>());
    }
}

void CPlayerStates::render()
{
    m_Player->drawFrame();
}

bool CPlayerStates::onEnter()
{
    //Load png for player
    auto render = CGame::Instance().getRenderer();
    CTextureManager::Instance().loadImage("Assets/mainCharSheet.png", "mainChar", render);
    CLoadParams playerParams(250, 100, 48, 48, "mainChar");

    //Create a player object
    m_Player = std::unique_ptr<CPlayer>(new CPlayer());
    m_Player->load(playerParams);

    return false;
}

bool CPlayerStates::onExit()
{
    std::cout << __FUNCSIG__ << std::endl;
    m_Player->clean();

    CTextureManager::Instance().clearTextureMap("mainChar");

    return false;
}
