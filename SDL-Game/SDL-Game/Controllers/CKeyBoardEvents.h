#pragma once
#include "CInputHandler.h"

class CKeyboardEvents : public CInputHandler
{
public:
	CKeyboardEvents() = default;

	void update()
	{
		m_keystates = SDL_GetKeyboardState(0);

		CInputHandler::update();
	}

	void clean()
	{

	}

	bool isKeyDown(SDL_Scancode key)
	{
		if (m_keystates != 0)
		{
			if (m_keystates[key] == 1)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		return false;
	}
private:

	const Uint8* m_keystates;
};