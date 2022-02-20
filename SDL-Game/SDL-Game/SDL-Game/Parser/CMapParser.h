#pragma once
#include <string>
#include <vector>

#include "../Map/CGameMap.h"
#include "../Map/CTileLayer.h"

#include "../__TinyXML/tinyxml.h"

class CMapParser
{

public:
	bool parseMap(std::string mapXMLPath, std::vector<std::vector<int>>* oTileMap);


private:
	void parseTileSet(TiXmlElement* xmlTileSate, CTileSet* tileSet);
	void parseData(TiXmlElement* xmlData, std::vector<std::vector<int>>* oTileMap);
};

