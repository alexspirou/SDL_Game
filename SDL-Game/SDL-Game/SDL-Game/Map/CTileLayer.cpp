#include "CTileLayer.h"

CTileLayer::CTileLayer(int tileSize, int rowCount, int colCount,
	std::vector<std::vector<int>> tileMap, std::vector<CTileSet> tileSets):
	m_TileSize{ tileSize }, m_RowCount{ rowCount }, m_ColCount{ colCount },
	m_TileMap{ tileMap }, m_TileSetsList{ tileSets }
{

}

void CTileLayer::draw()
{
}

void CTileLayer::update()
{
}
