#include "CTileLayer.h"
#include "../Managers/CTextureManager.h"
#include "../Core/CGame.h"
CTileLayer::CTileLayer(int tileSize, int rowCount, int colCount, std::vector<std::vector<int>> tileMap, std::vector<CTileSet> tileSets, std::vector<Tile>* destinatioMapTilesID)
{
	m_TileSize = tileSize;
	m_RowCount = rowCount; m_ColCount = colCount;
	m_TileMap = std::move(tileMap); m_vTileSets = tileSets;
	for (auto& tileSet : m_vTileSets)
	{
		CTextureManager::Instance().loadImage(tileSet.sourcePNG , tileSet.name, CGame::Instance().getRenderer());
	}
	createMapDestinationTilesID(destinatioMapTilesID);
}

void CTileLayer::draw()
{
	for (auto layerRow = 0; layerRow < m_RowCount; layerRow++)
	{
		for (auto layerCol = 0; layerCol < m_ColCount; layerCol++)
		{
			int currentTileID = m_TileMap[layerRow][layerCol];
			int holdTileID = currentTileID;

			if (currentTileID == 0) continue; //No tile to draw
			else
			{
				int index = 0;
				int tilesetSize = m_vTileSets.size();

				//for (auto& tileset : m_vTileSets)
				//{
				//	//IF is current id is inside first and last id
				//	if (currentTileID > tileset.FirstID && currentTileID < tileset.LastID)
				//	{
				//		currentTileID = currentTileID + tileset.TileCount - tileset.LastID;
				//		break;
				//	}
				//}
				CTileSet tileSet = m_vTileSets[index];
				tileSet.TileSize = 16;
				int rowFromTilePng = currentTileID / tileSet.ColCount;
				int colFromTilePng = currentTileID - rowFromTilePng * tileSet.ColCount - 1;
				//if (currentTileID % tileSet.ColCount == 0)
				//{
				//	rowFromTilePng--;
				//	colFromTilePng = tileSet.ColCount - 1;
				//}
				auto destX = layerCol * tileSet.TileSize; auto destY = layerRow * tileSet.TileSize;

				CTextureManager::Instance().drawTile(tileSet.name, tileSet.TileSize, destX,
					destY, rowFromTilePng, colFromTilePng, CGame::Instance().getRenderer());

			}
		}
	}

}

void CTileLayer::update()
{
}

void CTileLayer::createMapDestinationTilesID(std::vector<Tile>* destinatioMapTilesID)
{

	for (auto layerRow = 0; layerRow < m_RowCount; layerRow++)
	{
		for (auto layerCol = 0; layerCol < m_ColCount; layerCol++)
		{
			int currentTileID = m_TileMap[layerRow][layerCol];
			int holdTileID = currentTileID;

			if (currentTileID == 10)
			{
				int index = 0;
				int tilesetSize = m_vTileSets.size();

				CTileSet tileSet = m_vTileSets[index];
				tileSet.TileSize = 16;
				int rowFromTilePng = currentTileID / tileSet.ColCount;
				int colFromTilePng = currentTileID - rowFromTilePng * tileSet.ColCount - 1;
				auto destX = layerCol * tileSet.TileSize; auto destY = layerRow * tileSet.TileSize;

				Tile tempTile{ currentTileID , destX, destY };
				destinatioMapTilesID->push_back(tempTile);
			}
		}
	}
}


