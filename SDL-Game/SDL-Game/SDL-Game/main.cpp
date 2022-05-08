#include<SDL.h>
#include "ScreenDimentions.h"

#include "Core/CGame.h"
#include <iostream>

const int FPS = 40;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* args[])
{
	CGame &theGame = CGame::Instance();

	Uint32 frameStart, frameTime; 
	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	double deltaTime = 0;

	CGame::Instance().init("SDL Game", SCREEN_WIDTH, SCREEN_HEIGHT, false);
	while (CGame::Instance().isRunning())
	{
		frameStart = SDL_GetTicks();
		LAST = NOW;
		NOW = SDL_GetPerformanceCounter();
		deltaTime = (double)((NOW - LAST) * 10/(double)SDL_GetPerformanceFrequency());

		SDL_ShowCursor(SDL_DISABLE);
		CGame::Instance().render();
		CGame::Instance().update(deltaTime);
		CGame::Instance().handleEvents();

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}

	return 0;
}
