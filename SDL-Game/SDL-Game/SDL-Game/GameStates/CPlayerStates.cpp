#include "CPlayerStates.h"
#include "../Core/CGame.h"
#include "../Managers/CTextureManager.h"

void CPlayerStates::update()
{
    m_Player->update();
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
