#pragma once
#include <SDL.h>

#include <vector>
#include <iostream>
#include <memory>



class CInputHandler
{
public:
	CInputHandler() = default;

	void update();

	void clean();

protected:

	SDL_Event event;
};

