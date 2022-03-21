#ifndef COLLISIONDETECTION_h_
#define COLLISIONDETECTION_h_
#ifdef COLLISIONDETECTION_EXPORTS
#define COLLISIONDETECTION_API 
#else COLLISIONDETECTION_API
#define COLLISIONDETECTION_API 
#endif
#include "ColliderBox.h"
#include <iostream>
#include <algorithm>
#include "../Map/Tile.h"

COLLISIONDETECTION_API inline bool isCollision(ColliderBox& gameObject1, ColliderBox& gameObject2)
{

	if (gameObject1.colliderBox.x + gameObject1.colliderBox.w < gameObject2.colliderBox.x + gameObject2.colliderBox.w || gameObject1.colliderBox.x > gameObject2.colliderBox.x + gameObject2.colliderBox.w ||
		gameObject1.colliderBox.y + gameObject1.colliderBox.h < gameObject2.colliderBox.y || gameObject1.colliderBox.y > gameObject2.colliderBox.y + gameObject2.colliderBox.h)
	{
		return false;
	}
	else
	{
		//std::cout << "Collision " << std::endl;
		return true;
	}
}
COLLISIONDETECTION_API inline bool isCollision(ColliderBox& gameObject1, std::vector<Tile> vTiles)
{
	bool collisionFlag = false;
	std::vector<int> vTileIndeces;

	for (int i = 0; i < vTiles.size(); i++)
	{
		if (vTiles[i].ID == 10)
		{
			vTileIndeces.push_back(i);
		}
	}

	for (auto& tileIndex : vTileIndeces)
	{
		if (gameObject1.colliderBox.x + gameObject1.colliderBox.w < vTiles[tileIndex].x + 16 || gameObject1.colliderBox.x >  vTiles[tileIndex].x + 16 ||
			gameObject1.colliderBox.y + gameObject1.colliderBox.h < vTiles[tileIndex].y|| gameObject1.colliderBox.y> vTiles[tileIndex].y + 32)
		{
			continue;
		}
		else
		{
			std::cout << "Collision tile" << vTiles[tileIndex].ID << std::endl;
			return true;
		}
	}

	return false;
}


#endif