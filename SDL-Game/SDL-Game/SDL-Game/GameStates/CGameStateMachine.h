#pragma once
#include "IGameStates.h"
#include <vector>
#include <memory>
class CGameStateMachine
{
public:

	void update(double dt);

	void render();

	//Push a new state
	void pushState(std::unique_ptr<IGameStates>&& pState);
	//Change a state, for example menustate to gameplay
	void changeState(std::unique_ptr<IGameStates>&& pState);
	//Change a state and remove previous
	void changeStateAndPopPrevious(std::unique_ptr<IGameStates>&& pState);

	//Remove a state
	void popState();
	
private:
	std::vector<std::unique_ptr<IGameStates>> m_gameStates;
};

