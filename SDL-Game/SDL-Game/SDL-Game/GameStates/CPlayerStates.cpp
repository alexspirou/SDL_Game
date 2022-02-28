#include "CPlayerStates.h"
#include "../Core/CGame.h"
#include "../Managers/CTextureManager.h"
#include "../Menu/PauseMenu/CPauseStates.h"
#include "../ScreenDimentions.h"
#include "../Parser/CStateParser.h"

void CPlayerStates::update()
{
    auto isESCpressed = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_ESCAPE);
    if (isESCpressed)
    {
        //TODO Here change state for pause game
        CGame::Instance().getStateMachine()->changeState(std::make_unique<CPauseStates>());
        std::cout << sizeof(CGame::Instance().getStateMachine()) / 4 << std::endl;
    }
   // Update gameobjects
    for (auto& object : m_vGameObjects)
    {
        object->update();
    }

    m_Player->update();

    for (auto& enemy : m_vEnemies)
    {
        enemy->update();
        //enemy->isPLayerNear(std::move(m_vPlayer[0]));
    }
   
}

void CPlayerStates::render()
{
    for (auto& object : m_vGameObjects)
    {
        object->drawFrame();
        //std::cout << typeid(object).name() << std::endl;
    }

    m_Player->drawFrame();
    //std::cout << typeid(player).name() << std::endl;

    for (auto& enemy : m_vEnemies)
    {
        enemy->drawFrame();
       // std::cout << typeid(enemy).name() << std::endl;
        enemy->isPLayerNear((m_Player));
    }
    CGame::Instance().getMap()->draw();

}

bool CPlayerStates::onEnter()
{
    std::cout << sizeof(CGame::Instance().getStateMachine()) / 4 << std::endl;

    CStateParser stateParser;

    stateParser.parseState("XML/test.xml", "STABLEOBJECTS", &m_TexturesIDs, &m_vGameObjects);
    stateParser.parseState("XML/test.xml", "ENEMY", &m_TexturesIDs, &m_vEnemies);
    std::vector<std::unique_ptr<CPlayer>> vTempPlayer;
    stateParser.parseState<CPlayer>("XML/test.xml", "PLAY", &m_TexturesIDs, &vTempPlayer);
    m_Player = std::move(vTempPlayer[0]);

    return false;
}

bool CPlayerStates::onExit()
{
    std::cout << __FUNCSIG__ << std::endl;

    for(auto& textures: m_TexturesIDs)
        CTextureManager::Instance().clearTextureMap(textures);
    std::cout << "CLEANED SUCCESFULL" << std::endl;
    return false;
}
