#pragma once
#include "CollisionTile.h"
#include <vector>
class ILayer
{
public:

	virtual void draw(int frame) = 0;
	virtual void update(int frame) = 0;
	virtual void GetMapColliderIDAndPosition(std::vector<CollisionTile>* destinatioMapTilesID, int frame) =0;

	virtual ~ILayer() = default;

};

