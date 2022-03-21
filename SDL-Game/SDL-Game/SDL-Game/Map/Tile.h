#pragma once

struct Tile
{
	Tile(int ID, int x, int y) : ID{ ID }, x{ x }, y{ y }{}

	int ID, x, y;
};