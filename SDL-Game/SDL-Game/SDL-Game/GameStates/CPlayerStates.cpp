#include "CPlayerStates.h"
#include "../Core/CGame.h"
#include "../Managers/CTextureManager.h"
#include "../Menu/PauseMenu/CPauseStates.h"
#include "../ScreenDimentions.h"
#include "../Parser/CStateParser.h"

void CPlayerStates::update()
{
    m_Player->update();
    auto isESCpressed = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_ESCAPE);
    if (isESCpressed)
    {
        //TODO Here change state for pause game
        CGame::Instance().getStateMachine()->changeState(std::make_unique<CPauseStates>());
    }
    m_Fountain->update();
    m_BackGround->update();
}

void CPlayerStates::render()
{
    m_BackGround->draw();
    m_Player->drawFrame();
    m_Fountain->drawFrame();
}

bool CPlayerStates::onEnter()
{

    CStateParser stateParser;
     stateParser.parseState("test.xml", m_playID, &m_GameObjects , &m_TexturesIDList);

    //Load png for player
    auto render = CGame::Instance().getRenderer();
    CTextureManager::Instance().loadImage("Assets/mainCharWalk.png", "mainChar", render);
    CLoadParams playerParams(250, 100, 48, 48, "mainChar");
    CTextureManager::Instance().loadImage("Assets/Fountain.png", "Fountain", render);
    CLoadParams fountainParams(250, SCREEN_HEIGHT - 72, 72, 72, "Fountain");
    CTextureManager::Instance().loadImage("Assets/BackGround.png", "BackGround", render);
    CLoadParams backGround(0, -100, SCREEN_WIDTH, SCREEN_HEIGHT, "BackGround");

    //Create a player object
    m_Player = std::unique_ptr<CPlayer>(new CPlayer());
    m_Player->load(&playerParams);
    m_Fountain = std::unique_ptr<CGameObject>(new CGameObject());
    m_Fountain->load(&fountainParams);
    m_BackGround = std::unique_ptr<CGameObject>(new CGameObject());
    m_BackGround->load(&backGround);

    return false;
    //Fountain
}

bool CPlayerStates::onExit()
{
    std::cout << __FUNCSIG__ << std::endl;
    m_Player->clean();

    CTextureManager::Instance().clearTextureMap("mainChar");

    return false;
}
