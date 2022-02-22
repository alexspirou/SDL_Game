#pragma once
#include <string>
#include <vector>
#include <map>

#include "../Map/CGameMap.h"
#include "../Map/CTileLayer.h"

#include "../__TinyXML/tinyxml.h"

class CMapParser
{

public:
	bool parseMap(std::string mapXMLPath, std::string  id);
	inline CGameMap* getMap(std::string id) { return m_MapDict[id]; }
private:
	CTileSet parseTileSet(TiXmlElement* xmlTileSate);
	CTileLayer*  parseData(TiXmlElement* xmlData, std::vector<CTileSet> tileSet, int tileSize, int rows, int cols);

	std::map<std::string, CGameMap*> m_MapDict;
};

