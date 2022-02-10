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
	const std::string m_playID{"PLAYER"};
	std::unique_ptr<CPlayer> m_Player;
};

