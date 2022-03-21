#pragma once
#include"ILayer.h"
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
	virtual void draw()
	{
		for (auto& layer : m_vMapLayers)
		{
			layer->draw();
		}
	}
	virtual void update()
	{
		for (auto& layer : m_vMapLayers)
		{
			layer->update();
		}
	}
	std::map<int, std::vector<int>> m_PositionTileIDMap;
	std::vector<ILayer*> getMapLayers() const { return m_vMapLayers; }
	std::vector<ILayer*> m_vMapLayers;

private:

};