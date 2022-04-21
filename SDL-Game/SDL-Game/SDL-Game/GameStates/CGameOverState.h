#pragma once
#include "IGameStates.h"
#include "CGameOver.h"
class CGameOverState : public IGameStates
{
public:
	virtual ~CGameOverState() = default;
	virtual void update(double dt) override;
	virtual void render() override;
	virtual bool onEnter() override;
	virtual bool onExit() override;

	virtual std::string getStateID() const override { return m_GameOverStateID; }

private:

	std::string m_GameOverStateID = "GAMEOVER";
	std::unique_ptr<CGameOver> m_GameOver;
};

