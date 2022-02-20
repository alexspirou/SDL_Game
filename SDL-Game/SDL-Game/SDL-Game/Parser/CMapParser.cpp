#include "CMapParser.h"

bool CMapParser::parseMap(std::string mapXMLPath, std::vector<std::vector<int>>* oTileMap)
{
	
	TiXmlDocument xmlDoc;
	if (!xmlDoc.LoadFile(mapXMLPath))
	{
		std::cerr << xmlDoc.ErrorDesc() << "\n";
		return false;
	}
	CTileSet tileset{};
	TiXmlElement* pRoot = xmlDoc.RootElement();

	TiXmlElement* tileSetXMLElement =NULL;
	TiXmlElement* layerXMLElement = NULL;

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		auto xmlID = e->Value();
		if (xmlID == std::string("tileset"))
		{
			tileSetXMLElement = e;
		}
		else if (xmlID == std::string("layer"))
		{
			layerXMLElement = e;
		}

	}
	parseTileSet(tileSetXMLElement, &tileset);

	TiXmlElement* dataXMLElement = NULL;
	for (TiXmlElement* e = layerXMLElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
	{
		auto xmlID = e->Value();
		if (xmlID == std::string("data"))
		{
			dataXMLElement = e;
		}
	}

	//Parse data element and get map data here
	std::string mapData(dataXMLElement->GetText());
	std::istringstream matrixStream(mapData);
	std::string pixelID;
	 oTileMap->resize(tileset.RowCount, std::vector<int>(tileset.ColCount));
	for (int row = 0; row < tileset.RowCount; row++)
	{
		for (int col = 0; col < tileset.ColCount; col++)
		{
			std::getline(matrixStream, pixelID, ',');
			std::stringstream streamPixelID(pixelID);
			streamPixelID >> (* oTileMap)[row][col];
			if (!matrixStream.good())
				break;
		}
	}


	return true;
}

void CMapParser::parseTileSet(TiXmlElement* xmlTileSate, CTileSet* tileSet)
{

	tileSet->name = xmlTileSate->Attribute("name");
	
	//xmlTileSate->Attribute("tilewidth", &tileSet->FirstID);
	//xmlTileSate->Attribute("tileheight", &tileSet->FirstID);

	xmlTileSate->Attribute("tilecount", &tileSet->TileCount);
	xmlTileSate->Attribute("columns", &tileSet->ColCount);
	tileSet->RowCount = (tileSet->ColCount / tileSet->ColCount);

	xmlTileSate->Attribute("firstgid", &tileSet->FirstID);
	tileSet->LastID = (tileSet->FirstID + tileSet->ColCount) - 1;

	TiXmlElement* xmlImageSource = xmlTileSate->FirstChildElement();
	tileSet->sourcePNG = xmlImageSource->Attribute("source");
}

void CMapParser::parseData(TiXmlElement* xmlData, std::vector<std::vector<int>>* oTileMap)
{


}
