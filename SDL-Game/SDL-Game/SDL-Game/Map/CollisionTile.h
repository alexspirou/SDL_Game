#pragma once
#include "../Collision/ColliderBox.h"

struct CollisionTile
{
	inline CollisionTile(int ID, int x, int y) : ID{ ID }, x{ x }, y{ y }
	{
		ColliderBox = { x, y, 16, 14 };
	}

	int ID, x, y; // Add tile size 

	ColliderBox ColliderBox{};
};