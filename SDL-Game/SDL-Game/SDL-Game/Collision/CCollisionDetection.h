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
#include "../Map/CollisionTile.h"

COLLISIONDETECTION_API inline bool isCollision(ColliderBox& colliderBoxObj1, ColliderBox& colliderBoxObj2)
{

	if (colliderBoxObj1.x + colliderBoxObj1.w < colliderBoxObj2.x + colliderBoxObj2.w || colliderBoxObj1.x > colliderBoxObj2.x + colliderBoxObj2.w ||
		colliderBoxObj1.y + colliderBoxObj1.h < colliderBoxObj2.y || colliderBoxObj1.y > colliderBoxObj2.y + colliderBoxObj2.h)
	{
		return false;
	}
	else
	{
		//std::cout << "Collision " << std::endl;
		return true;
	}
}
COLLISIONDETECTION_API inline bool isCollision(ColliderBox& colliderBoxObj, std::vector<CollisionTile> vTiles)
{
	bool collisionFlag = false;
	std::vector<int> vTileIndeces;

	for (int i = 0; i < vTiles.size(); i++)
	{
		if (vTiles[i].ID == 10 || vTiles[i].ID == 11)
		{
			vTileIndeces.push_back(i);
		}
	}

	for (auto& tileIndex : vTileIndeces)
	{
		if (colliderBoxObj.x + colliderBoxObj.w < vTiles[tileIndex].ColliderBox.x  || colliderBoxObj.x >  vTiles[tileIndex].ColliderBox.x  ||
			colliderBoxObj.y + colliderBoxObj.h < vTiles[tileIndex].ColliderBox.y  || colliderBoxObj.y > vTiles[tileIndex].ColliderBox.y )
		{
			continue;
		}
		else
		{
			return true;
		}
	}

	return false;
}


#endif