#pragma once
#include <SDL.h>

class ColliderBox
{

public:

	SDL_Rect GetBox() { return m_Box; }

	void SetBox(int x, int y, int w, int h) { m_Box = { x,y,w,h }; }

	SDL_Rect m_Box;

private:


};