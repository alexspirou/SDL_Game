#include "../Controllers/CInputHandler.h"
#include "../Core/CGame.h"

void CInputHandler::update()
{

	if (SDL_PollEvent(&event))
	{

		if (event.type == SDL_QUIT)
		{
			CGame::Instance().quit();
		}
	}
}

void CInputHandler::clean()
{
}
