#include "CMapParser.h"

bool CMapParser::parseMap(std::string mapXMLPath, std::string  id)
{
	
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile(mapXMLPath))
	{
		std::cerr << xmlDoc.ErrorDesc() << "\n";
		return false;
	}
	
	TiXmlElement* pRoot = xmlDoc.RootElement();  TiXmlElement* tileSetXMLElement =NULL; TiXmlElement* layerXMLElement = NULL;
	std::vector<CTileSet> vTileSets;

	std::vector<CTileSet> m_vTileSets; 
	std::vector<std::unique_ptr<CTileLayer>> vTileLayers;
	int tileRows, tileCols, tileSize;
	pRoot->Attribute("width", &tileCols);
	pRoot->Attribute("height", &tileRows);
	pRoot->Attribute("tilewidth", &tileSize);

	CGameMap* gameMap = new CGameMap();

	for (TiXmlElement* currentXMLElement = pRoot->FirstChildElement(); currentXMLElement != NULL; currentXMLElement = currentXMLElement->NextSiblingElement())
	{
		auto xmlID = currentXMLElement->Value();
		if (xmlID == std::string("tileset"))
		{
			tileSetXMLElement = currentXMLElement;
			vTileSets.push_back(parseTileSet(tileSetXMLElement));
		}
		else if (xmlID == std::string("layer"))
		{
			layerXMLElement = currentXMLElement;
			gameMap->m_vMapLayers.push_back((parseData(layerXMLElement, vTileSets, 32, tileRows, tileCols, &m_TilesIDPos)));
		}
	}
	m_MapDict[id] = gameMap;

	return true;
}

CTileSet CMapParser::parseTileSet(TiXmlElement* xmlTileSate)
{
	CTileSet tempTileset;
	tempTileset.name = xmlTileSate->Attribute("name");
	
	xmlTileSate->Attribute("tilecount", &tempTileset.TileCount);
	xmlTileSate->Attribute("columns", &tempTileset.ColCount);
	tempTileset.RowCount = (tempTileset.ColCount / tempTileset.ColCount);

	xmlTileSate->Attribute("firstgid", &tempTileset.FirstID);
	tempTileset.LastID = (tempTileset.FirstID + tempTileset.ColCount) - 1;

	TiXmlElement* xmlImageSource = xmlTileSate->FirstChildElement();
	tempTileset.sourcePNG = xmlImageSource->Attribute("source");

	return tempTileset;
}

CTileLayer* CMapParser::parseData(TiXmlElement* xmlData, std::vector<CTileSet> tileSet, int tileSize, int rows, int cols, std::vector<Tile>* tilesIDpos)
{

	TiXmlElement* dataXMLElement = NULL;
	for (TiXmlElement* currentXMLElement = xmlData->FirstChildElement(); currentXMLElement != NULL; currentXMLElement = currentXMLElement->NextSiblingElement())
	{
		auto xmlID = currentXMLElement->Value();
		if (xmlID == std::string("data"))
		{
			dataXMLElement = currentXMLElement;
		}
	}
	//Parse data element and get map data here
	std::string mapData(dataXMLElement->GetText());
	std::istringstream matrixStream(mapData);
	std::string pixelID;

	std::vector<std::vector<int>> oDataMap(rows, std::vector<int>(cols));
	int row = 0; int col = 0;
	for (int i = 0; i < cols*rows; i++)
	{
		if (col / cols == 1) { row++; col = 0; }

		std::getline(matrixStream, pixelID, ',');
		std::stringstream streamPixelID(pixelID);
		streamPixelID >> oDataMap[row][col];
		col++;
		if (!matrixStream.good())
			break;
	}
	return (new CTileLayer(tileSize, rows, cols, oDataMap, tileSet, tilesIDpos));
}
