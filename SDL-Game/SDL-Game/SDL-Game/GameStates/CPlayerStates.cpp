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

    //TODO : Create a parser for music
    CGame::Instance().getSoundManager().loadMusic("backGroundMusic", "Assets/Music/backGroundMusic.wav");
    CGame::Instance().getSoundManager().playMusic("backGroundMusic", 10);

    return false;
}
void CPlayerStates::update(double dt)
{
    auto isESCpressed = CGame::Instance().getKeyboardEvents().isKeyDown(SDL_SCANCODE_ESCAPE);
    if (isESCpressed)
    {
        CGame::Instance().getStateMachine()->changeState(std::make_unique<CPauseStates>());
    }

    // Player
    m_Player->update(dt);

    changeMapLevel();

    // GameObjects
    for (auto& object : m_vGameObjects){ object->update(dt); }

    // Enemies
    for (auto& enemy : m_vEnemies) { enemy->update(dt); }
    for (auto& enemy : m_vEnemies){  calculateLength(m_Player->getCollinder(), enemy->getCollinder()); }
    for (auto& enemy : m_vEnemies) { isCollision(m_Player->getCollinder(), enemy->getCollinder()); }

    // Check collision for gravity
    if (isCollision(m_Player->feetCollider, CGame::Instance().getMap()->getTilesIDPos()))
    {
        m_Player->isFall = false;
    }
    else
    {
        m_Player->isFall = true;
    }

    CGame::Instance().getMap()->update(m_MapFrame);

    if (isGameOver()) { CGame::Instance().getStateMachine()->changeState(std::make_unique<CGameOverState>()); }

}
void CPlayerStates::render()
{
    for (auto& object : m_vGameObjects) { object->drawFrame(); }

    m_Player->drawFrame();

    for (auto& enemy : m_vEnemies) { enemy->drawFrame(); }

    for (auto& collisioNTile: CGame::Instance().getMap()->getTilesIDPos())
    {
       CTextureManager::Instance().drawColliderBox(CGame::Instance().getRenderer(), collisioNTile.ColliderBox);
    }
    
    CGame::Instance().getMap()->draw(m_MapFrame);

}

bool CPlayerStates::onExit()
{
    std::cout << __FUNCSIG__ << std::endl;

    CGame::Instance().getMap()->GetMapColliderIDAndPosition(0);

    for (auto& textures : m_TexturesIDs)
    {
        CTextureManager::Instance().clearTextureMap(textures);
    }
    std::cout << "CLEANED SUCCESFULL" << std::endl;
    return false;
}

void CPlayerStates::changeMapLevel()
{
    auto playerIsInEndOfTheMap = m_Player->getCollinder().x - m_Player->getCollinder().w > SCREEN_WIDTH;
    if (playerIsInEndOfTheMap)
    {
        // TODO : Change tiles in map
        m_MapFrame++;
        CGame::Instance().getMap()->GetMapColliderIDAndPosition(m_MapFrame);
        m_Player->setPositionX(-m_Player->getWidth() / 2);
    }
}

bool CPlayerStates::isGameOver()
{

    if (m_Player->feetCollider.y > SCREEN_HEIGHT)
        return true;

    for (auto& enemy : m_vEnemies)
    {
        if (isCollision(m_Player->getFireball()->getColliderBox(), enemy->getCollinder()))
        {
            return true;
        }
    }
    return false;

}
