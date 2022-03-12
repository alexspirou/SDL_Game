#include "CPlayerStates.h"
#include "../Core/CGame.h"
#include "../Managers/CTextureManager.h"
#include "../Menu/PauseMenu/CPauseStates.h"
#include "../ScreenDimentions.h"
#include "../Parser/CStateParser.h"

void CPlayerStates::update(double dt)
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
        object->update(dt);
    }

    m_Player->update(dt);

    for (auto& enemy : m_vEnemies)
    {
        enemy->update(dt);
    }
}
void CPlayerStates::render()
{
    for (auto& object : m_vGameObjects)
    {
        object->drawFrame();
    }

    m_Player->draw();

    for (auto& enemy : m_vEnemies)
    {
        enemy->drawFrame();
        enemy->isPLayerNear(m_Player.get());
    }
    CGame::Instance().getMap()->draw();

}

bool CPlayerStates::onEnter()
{
    std::cout << sizeof(CGame::Instance().getStateMachine()) / 4 << std::endl;

    CStateParser stateParser;
    stateParser.parseState("XML/test.xml", "STABLEOBJECTS", &m_TexturesIDs, &m_vGameObjects);
    stateParser.parseState("XML/test.xml", "ENEMY", &m_TexturesIDs, &m_vEnemies);
    stateParser.parseState<CPlayer>("XML/test.xml", "PLAY", &m_TexturesIDs, NULL, &m_Player);


    CGame::Instance().getSoundManager().loadMusic("backGroundMusic","D:/repos/SDL_Game/SDL-Game/SDL-Game/SDL-Game/Assets/Music/backGroundMusic.wav");
    CGame::Instance().getSoundManager().playMusic("backGroundMusic", 40);

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
