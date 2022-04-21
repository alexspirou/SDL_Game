#include "CPlayerStates.h"
#include "../Core/CGame.h"
#include "../Managers/CTextureManager.h"
#include "../Menu/PauseMenu/CPauseStates.h"
#include "../GameStates/CGameOverState.h"
#include "../ScreenDimentions.h"
#include "../Parser/CStateParser.h"
#include "../Physics/CMath.h"
#include "../Collision/CCollisionDetection.h"

bool CPlayerStates::onEnter()
{
    CStateParser stateParser;
    stateParser.parseState("XML/objects.xml", "STABLEOBJECTS", &m_TexturesIDs, &m_vGameObjects);
    stateParser.parseState("XML/enemies.xml", "ENEMY", &m_TexturesIDs, &m_vEnemies);
    stateParser.parseState<CPlayer>("XML/player.xml", "PLAY", &m_TexturesIDs, NULL, &m_Player);

    CGame::Instance().getSoundManager().loadMusic("backGroundMusic", "D:/repos/SDL_Game/SDL-Game/SDL-Game/SDL-Game/Assets/Music/backGroundMusic.wav");
    CGame::Instance().getSoundManager().playMusic("backGroundMusic", 10);

    return false;
}
void CPlayerStates::update(double dt)
{
    auto isESCpressed = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_ESCAPE);
    auto isZeroPressed = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_0);


    if (isESCpressed)
    {
        CGame::Instance().getStateMachine()->changeState(std::make_unique<CPauseStates>());
    }

    if (isZeroPressed)
    {
        CGame::Instance().getStateMachine()->changeState(std::make_unique<CGameOverState>());
    }
    // Update player
    m_Player->update(dt);

    // Update gameobjects
    for (auto& object : m_vGameObjects){ object->update(dt); }
    // Update all enemies
    for (auto& enemy : m_vEnemies) { enemy->update(dt); }
    // Calculate length with player of all enemies
    for (auto& enemy : m_vEnemies){  calculateLength(m_Player->getCollinder(), enemy->getCollinder()); }
    // Check collision for player and enemies
    for (auto& enemy : m_vEnemies) { isCollision(m_Player->getCollinder(), enemy->getCollinder()); }
    // Check collision for player's fireballs and enemies
    for (auto& enemy : m_vEnemies) 
    { 
        if (isCollision(m_Player->getFireball().getColliderBox(), enemy->getCollinder()))
        {
            // TODO : Do something
        }
    }

    // Check collision for gravity
    if (isCollision(m_Player->feetCollider, CGame::Instance().getMapParser().m_vTilesIDPos))
    {
        m_Player->isFall = false;
    }
    else
    {
        m_Player->isFall = true;
    }

    if(m_Player->feetCollider.y > SCREEN_HEIGHT) { CGame::Instance().getStateMachine()->changeState(std::make_unique<CGameOverState>()); }
    
}
void CPlayerStates::render()
{
    for (auto& object : m_vGameObjects) { object->drawFrame(); }

    m_Player->drawFrame();

    for (auto& enemy : m_vEnemies) { enemy->drawFrame(); }

    for (auto& collisioNTile: CGame::Instance().getMapParser().m_vTilesIDPos)
    {
        CTextureManager::Instance().drawColliderBox(CGame::Instance().getRenderer(), collisioNTile.ColliderBox);
    }

    CGame::Instance().getMap()->draw();

}



bool CPlayerStates::onExit()
{
    std::cout << __FUNCSIG__ << std::endl;

    for (auto& textures : m_TexturesIDs)
    {
        std::cout << textures << std::endl;
        CTextureManager::Instance().clearTextureMap(textures);
    }
    std::cout << "CLEANED SUCCESFULL" << std::endl;
    return false;
}
