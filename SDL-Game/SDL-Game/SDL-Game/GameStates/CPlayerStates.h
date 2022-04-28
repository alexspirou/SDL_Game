#pragma once
#include "IGameStates.h"
#include "../Game Objects/CPlayer.h"
#include "../Game Objects/CEnemy.h"
#include "../Game Objects/CStableObject.h"

#include <memory>
class CPlayerStates : public IGameStates
{
public:
	virtual ~CPlayerStates() = default;
	virtual void update(double dt);
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_playID; }

private:

	const std::string m_playID{"PLAY"};
	std::vector<std::unique_ptr<CStableObject>> m_vGameObjects;
	std::unique_ptr<CPlayer> m_Player;
	std::vector<std::unique_ptr<CEnemy>> m_vEnemies;
	std::vector<std::string> m_TexturesIDs;
	std::unique_ptr<CGameObject> m_BackGround;
	int m_MapFrame = 0;
};

