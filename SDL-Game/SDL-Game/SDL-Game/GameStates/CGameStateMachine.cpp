#include "CGameStateMachine.h"
void CGameStateMachine::update()
{
	//Update objects of chosen state
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update();
	}
}
void CGameStateMachine::render()
{

	//Render chosen states objects
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->render();
	}

}
//Add a new state
void CGameStateMachine::pushState(std::unique_ptr<IGameStates>&& pState)
{
	m_gameStates.push_back(std::move(pState));
	m_gameStates.back()->onEnter();
}

//Change 
void CGameStateMachine::changeState(std::unique_ptr< IGameStates>&& pState)
{
	if (!m_gameStates.empty())
	{
		auto prevID = m_gameStates.back()->getStateID(); auto changedId = pState->getStateID();

		if (prevID == changedId)
		{
			return; //Do nothing
		}
		else
		{
			std::cout << "Changed" << std::endl;
			m_gameStates.back()->onExit();
			m_gameStates.pop_back();
		}
	}
	m_gameStates.push_back(std::move(pState));

	m_gameStates.back()->onEnter();
}

void CGameStateMachine::popState()
{
	if (!m_gameStates.empty())
	{
		if (m_gameStates.back()->onExit())
		{
			std::cout << "POP called; " << std::endl;

			m_gameStates.pop_back();
		}
	}
}
