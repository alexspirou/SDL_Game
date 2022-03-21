#pragma once
#include <iostream>
#include <vector>
#include <memory>

#include "../__TinyXML/tinyxml.h"
#include "../Game Objects/CGameObject.h"
#include "../Core/CGame.h"
#include "../Managers/CTextureManager.h"

class GameObject;
class CStateParser
{
public:
	template<typename T>
	inline bool parseState(const char* stateFile, std::string stateID, std::vector<std::string>* pTextureIDs, std::vector<std::unique_ptr<T>>* vObjects = NULL, std::unique_ptr<T>* pObject = NULL)
	{
		// create the XML document
		TiXmlDocument xmlDoc;
		// load the state file
		if (!xmlDoc.LoadFile(stateFile))
		{
			std::cerr << xmlDoc.ErrorDesc() << "\n";
			return false;
		}
		// get the root element
		TiXmlElement* pRoot = xmlDoc.RootElement();
		// pre declare the states root node
		TiXmlElement* pStateRoot = 0;
		// get this states root node and assign it to pStateRoot
		for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			auto xmlID = e->Value();
			if (xmlID == stateID)
			{
				pStateRoot = e;
			}
		}
		// pre declare the texture root
		TiXmlElement* pTextureRoot = 0;
		// get the root of the texture elements
		for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			if (e->Value() == std::string("TEXTURES"))
			{
				pTextureRoot = e;
			}
		}
		// now parse the textures
		parseTextures(pTextureRoot, pTextureIDs);

		// pre declare the object root node
		TiXmlElement* pObjectRoot = 0;
		// get the root node and assign it to pObjectRoot
		for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			if (e->Value() == std::string("OBJECTS"))
			{
				pObjectRoot = e;
			}
		}
		// Return vector with objects
		
		if(vObjects)parseObjects<T>(pObjectRoot, std::move(vObjects));
		else if(pObject) parseObjects<T>(pObjectRoot,NULL, pObject);

		return true;
	}


private:

	inline void parseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs)
	{
		for (TiXmlElement* dataFromXML = pStateRoot->FirstChildElement(); dataFromXML != NULL; dataFromXML = dataFromXML->NextSiblingElement())
		{
			const char* filenameAttribute = dataFromXML->Attribute("filename");
			std::string idAttribute = dataFromXML->Attribute("ID");

			pTextureIDs->push_back(idAttribute); // push into list
			CTextureManager::Instance().loadImage(filenameAttribute, idAttribute, CGame::Instance().getRenderer());
		}
	}
	template<typename T>
	inline void parseObjects(TiXmlElement* pStateRoot, std::vector<std::unique_ptr<T>>* vObjects = NULL, std::unique_ptr<T>* pObject = NULL)
	{
		auto getValuesPerComma = [&](std::string stringForTrimming, std::vector<int>* vValues, int size )
		{
			std::istringstream streamCollinderBox(stringForTrimming);
			std::string colliderBoxValue;
			vValues->resize(size);
			for (auto i = 0; i < size; i++)
			{
				std::getline(streamCollinderBox, colliderBoxValue, ',');
				std::stringstream streamPixelID(colliderBoxValue);
				streamPixelID >> vValues->at(i);
			}
		};

		for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
		{
			int x{}, y{}, width{}, height{}, currentRow{}, numFrames{}, spawnTime, callbackID{}, animSpeed{};
			
			std::string textureID = e->Attribute("textureID");
			std::string objectID = e->Attribute("objectID");
			
			e->Attribute("x", &x);
			e->Attribute("y", &y);
			e->Attribute("width", &width);
			e->Attribute("height", &height);
			e->Attribute("numFrames", &numFrames);
			e->Attribute("callbackID", &callbackID);
			e->Attribute("animSpeed", &animSpeed);
			e->Attribute("currentRow", &currentRow);
			e->Attribute("spawnTime", &spawnTime);

			std::string sColliderBox = e->Attribute("colliderBox");
			std::vector<int> tmpVecCollinderBox(4);
			getValuesPerComma(sColliderBox, &tmpVecCollinderBox, 4);

			ColliderBox tempColliderBox{ tmpVecCollinderBox[0],tmpVecCollinderBox[1],tmpVecCollinderBox[2],tmpVecCollinderBox[3] };

			T* pGameObject = CGame::Instance().getObjectFactory().createObjectByID<T>(e->Attribute("type"));

			pGameObject->load(new CLoadParams(x, y, width, height, textureID, numFrames, objectID, &tempColliderBox, currentRow, spawnTime, callbackID, animSpeed));

			auto takewOwnershipPtr = std::unique_ptr<T>{ std::exchange(pGameObject, nullptr) };

			//return objects
			if (vObjects)vObjects->push_back(std::move(takewOwnershipPtr));

			else if (pObject) *pObject = std::move(takewOwnershipPtr);

		}
	}
};

