#include "CGameStateMachine.h"
void CGameStateMachine::update(double dt)
{
	if (!m_gameStates.empty())
	{
		m_gameStates.back()->update(dt);
	}
}
void CGameStateMachine::render()
{
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
		m_gameStates.back()->onExit();
	}
	m_gameStates.push_back(std::move(pState));

	m_gameStates.back()->onEnter();
}
//Change 
void CGameStateMachine::changeStateAndPopPrevious(std::unique_ptr< IGameStates>&& pState)
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
			m_gameStates.pop_back();
		}
	}
}
