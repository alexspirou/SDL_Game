#pragma once
#include"ILayer.h"
#include <vector>
class CGameMap
{
public:

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

	std::vector<ILayer*> getMapLayers() { return m_vMapLayers; }

private:

	std::vector<ILayer*> m_vMapLayers;
};