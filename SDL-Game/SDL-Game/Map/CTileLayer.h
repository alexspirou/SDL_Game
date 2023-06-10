#pragma once

#include "ILayer.h"
#include <string>
#include <vector>
#include "../Map/CollisionTile.h"
//Data structure for tiles data
struct CTileSet
{
	int FirstID, LastID;
	int RowCount, ColCount;
	int TileCount, TileSize;
	std::string name, sourcePNG;
};
//This class will be retrieve data from map xml and used them to render the map
class CTileLayer : public ILayer
{
public:
	CTileLayer(int tileSize, int rowCount, int colCount, std::vector<std::vector<int>> tileMap, std::vector<CTileSet> tileSets);
	virtual void draw(int frame);
	virtual void update(int frame);

	inline auto getTileMap() { return m_TileMap; }
	void GetMapColliderIDAndPosition(std::vector<CollisionTile>* destinatioMapTilesID, int frame);

private:

	int m_TileSize;
	int m_RowCount, m_ColCount;
	std::vector<std::vector<int>> m_TileMap;	//Tile map, holds indexes for each png, data from xml
	std::vector<CTileSet> m_vTileSets; //Holds all tilesets that??
	std::vector<CollisionTile>* m_VDestinatioMapTilesIDl;

};

