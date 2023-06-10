#pragma once
#include"ILayer.h"
#include "CollisionTile.h"
#include <vector>
#include <memory>
class CGameMap
{
public:
	CGameMap(std::vector<ILayer*> vecLayer)
	{
		m_vMapLayers = std::move(vecLayer);
	}
	CGameMap() = default;
	//Draw all layers from vector
	void draw(int frame)
	{
		for (auto& layer : m_vMapLayers)
		{
			layer->draw(frame);
		}
	}
	void update(int frame)
	{
		for (auto& layer : m_vMapLayers)
		{
			layer->update(frame);
		}
	}
	void GetMapColliderIDAndPosition(int frame)
	{
		for (auto& layer : m_vMapLayers)
		{
			layer->GetMapColliderIDAndPosition(&m_vTilesIDPos, frame);
		}
	}
	inline auto getTilesIDPos() { return m_vTilesIDPos; }

	std::vector<ILayer*> getMapLayers() const { return m_vMapLayers; }
	std::vector<ILayer*> m_vMapLayers;

private:

	std::vector<CollisionTile> m_vTilesIDPos;

};