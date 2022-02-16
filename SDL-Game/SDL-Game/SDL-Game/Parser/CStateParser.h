#pragma once
#include <iostream>
#include <vector>
#include <memory>

#include "../__TinyXML/tinyxml.h"
#include "../Game Objects/CGameObject.h"

class GameObject;
class CStateParser
{
public:
	bool parseState(const char* stateFile, std::string stateID, std::vector<std::unique_ptr<CGameObject>>* pObjects, std::vector<std::string>* pTextureIDs);

private:
	void parseObjects(TiXmlElement* pStateRoot, std::vector<std::unique_ptr<CGameObject>>* pObjects);

	void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs);
};

