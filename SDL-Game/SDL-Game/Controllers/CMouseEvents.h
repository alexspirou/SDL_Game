#pragma once
#include "CInputHandler.h"
#include "../Physics/Vector2D.h"

class CMouseEvents : public CInputHandler
{
public:
	CMouseEvents();

	void update();

	void clean();

	bool getMouseStates(unsigned int state);

	Vector2D getMousePosition();

	enum mouseButtons { LEFTCLICK = 0, MIDDLECLICK = 1, RIGHTCLICK = 2 };

private:

	void handleMouseMotionEvents();

	void handleMouseClickEvents();

	std::vector<bool> m_mouseButtonStates{ 0,0,0 };

	Vector2D m_mousePosition;

};

