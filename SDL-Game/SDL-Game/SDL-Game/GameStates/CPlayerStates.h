#pragma once
#include "IGameStates.h"
#include "../Game Objects/CPlayer.h"
#include <memory>
class CPlayerStates : public IGameStates
{
public:
	virtual ~CPlayerStates() = default;
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const { return m_playID; }

private:
	const std::string m_playID{"PLAY"};

	std::vector<std::unique_ptr<CGameObject>> m_vGameObjects;
	std::vector < std::unique_ptr<CGameObject>> m_StableObjects;

	std::vector<std::string> m_TexturesIDs;

	std::unique_ptr<CGameObject> m_BackGround;


};

