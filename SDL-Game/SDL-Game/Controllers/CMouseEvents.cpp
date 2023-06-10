#include "CMouseEvents.h"

CMouseEvents::CMouseEvents() : CInputHandler(),
m_mousePosition(0, 0)
{

}

void CMouseEvents::update()
{

	handleMouseMotionEvents();

	handleMouseClickEvents();

	CInputHandler::update();

}

void CMouseEvents::clean()
{
	CInputHandler::clean();
}

bool CMouseEvents::getMouseStates(unsigned int state)
{
	if (state < 3)
		return m_mouseButtonStates[state];
	//Find a way to secure this function
	std::cout << "Invalid mouse state, please select betwwen 0-2\n";
}

Vector2D CMouseEvents::getMousePosition()
{
	return m_mousePosition;
}

void CMouseEvents::handleMouseMotionEvents()
{
	if (event.type == SDL_MOUSEMOTION)
	{
		m_mousePosition.m_x = event.motion.x;
		m_mousePosition.m_y = event.motion.y;
	}
}

void CMouseEvents::handleMouseClickEvents()
{

	if (event.type == SDL_MOUSEBUTTONDOWN)
	{

		auto pressedMouseButton = event.button.button;

		if (pressedMouseButton == SDL_BUTTON_LEFT) { m_mouseButtonStates[LEFTCLICK] = true;  }
		if (pressedMouseButton == SDL_BUTTON_MIDDLE) { m_mouseButtonStates[MIDDLECLICK] = true; }
		if (pressedMouseButton == SDL_BUTTON_RIGHT) { m_mouseButtonStates[RIGHTCLICK] = true; }
	}

	if (event.type == SDL_MOUSEBUTTONUP)
	{
		auto pressedMouseButton = event.button.button;

		if (pressedMouseButton == SDL_BUTTON_LEFT) { m_mouseButtonStates[LEFTCLICK] = false; }
		if (pressedMouseButton == SDL_BUTTON_MIDDLE) { m_mouseButtonStates[MIDDLECLICK] = false; }
		if (pressedMouseButton == SDL_BUTTON_RIGHT) { m_mouseButtonStates[RIGHTCLICK] = false; }
	}
	
}
