#pragma once
#include <SDL.h>

class ColliderBox
{

public:

	ColliderBox() = default;
	ColliderBox(int x, int y, int w, int h) :x(x), y(y), w(w), h(h) 
	{
		colliderBox = { x,y,w,h };
	}

	SDL_Rect colliderBox;
	int x{0}, y{0}, w{0}, h{0};
private:


};