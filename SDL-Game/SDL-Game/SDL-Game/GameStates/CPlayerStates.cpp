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
    }
    for (auto& object : m_vGameObjects)
    {
        object->update();
    }
}

void CPlayerStates::render()
{
    for (auto& object : m_vGameObjects)
    {
        object->drawFrame();
    }

}

bool CPlayerStates::onEnter()
{

    CStateParser stateParser;
    stateParser.parseState("XML/test.xml", "STABLEOBJECTS", &m_vGameObjects, &m_TexturesIDs);
     stateParser.parseState("XML/test.xml", "PLAY", &m_vGameObjects , &m_TexturesIDs);
     stateParser.parseState("XML/test.xml", "ENEMY", &m_vGameObjects, &m_TexturesIDs);

    return false;
}

bool CPlayerStates::onExit()
{
    std::cout << __FUNCSIG__ << std::endl;

    CTextureManager::Instance().clearTextureMap("mainChar");

    return false;
}
