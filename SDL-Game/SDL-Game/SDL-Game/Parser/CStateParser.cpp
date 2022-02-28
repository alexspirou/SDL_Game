//#include "CStateParser.h"
//#include "../Core/CGame.h"
//#include "../Managers/CTextureManager.h"
//
//bool CStateParser::parseState(const char* stateFile, std::string stateID, std::vector<std::unique_ptr<CGameObject>>* pObjects, std::vector<std::string>* pTextureIDs)
//{
//	// create the XML document
//	TiXmlDocument xmlDoc;
//	// load the state file
//	if (!xmlDoc.LoadFile(stateFile))
//	{
//		std::cerr << xmlDoc.ErrorDesc() << "\n";
//		return false;
//	}
//	// get the root element
//	TiXmlElement* pRoot = xmlDoc.RootElement();
//	// pre declare the states root node
//	TiXmlElement* pStateRoot = 0;
//	// get this states root node and assign it to pStateRoot
//	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
//	{
//		auto xmlID = e->Value();
//		if (xmlID == stateID)
//		{
//			pStateRoot = e;
//		}
//	}
//	// pre declare the texture root
//	TiXmlElement* pTextureRoot = 0;
//	// get the root of the texture elements
//	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=NULL; e = e->NextSiblingElement())
//	{
//		if (e->Value() == std::string("TEXTURES"))
//		{
//			pTextureRoot = e;
//		}
//	}
//	// now parse the textures
//	parseTextures(pTextureRoot, pTextureIDs);
//
//	// pre declare the object root node
//	TiXmlElement* pObjectRoot = 0;
//	// get the root node and assign it to pObjectRoot
//	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=NULL; e = e->NextSiblingElement())
//	{
//		if (e->Value() == std::string("OBJECTS"))
//		{
//			pObjectRoot = e;
//		}
//	}
//	// Return vector with objects
//	parseObjects(pObjectRoot, std::move(pObjects));
//	return true;
//}
//void CStateParser::parseTextures(TiXmlElement* pStateRoot, std::vector<std::string>* pTextureIDs)
//{
//	for (TiXmlElement* dataFromXML = pStateRoot->FirstChildElement(); dataFromXML != NULL; dataFromXML = dataFromXML->NextSiblingElement())
//	{
//		const char*  filenameAttribute = dataFromXML->Attribute("filename");
//		std::string idAttribute = dataFromXML->Attribute("ID");
//		
//		pTextureIDs->push_back(idAttribute); // push into list
//		CTextureManager::Instance().loadImage(filenameAttribute, idAttribute, CGame::Instance().getRenderer());
//	}
//}
//
//void CStateParser::parseObjects(TiXmlElement* pStateRoot,  std::vector<std::unique_ptr<CGameObject>>* pObjects)
//{
//	for (TiXmlElement* e = pStateRoot->FirstChildElement(); e !=NULL; e = e->NextSiblingElement())
//	{
//		int x{}, y{}, width{}, height{}, currentRow{}, numFrames{}, spawnTime, callbackID{}, animSpeed{};
//		
//		e->Attribute("x", &x);
//		e->Attribute("y", &y);
//		e->Attribute("width", &width);
//		e->Attribute("height", &height);
//		e->Attribute("numFrames", &numFrames);
//		e->Attribute("callbackID", &callbackID);
//		e->Attribute("animSpeed", &animSpeed);
//		e->Attribute("currentRow", &currentRow);
//
//		if (e->Attribute("spawnTime", &spawnTime));
//
//
//		std::string textureID = e->Attribute("textureID");
//		std::string s = e->Attribute("type");
//		if ( s== "CEnemy")
//		{
//			std::cout << "CEnemy " << std::endl;
//		}
//		CGameObject* pGameObject = CGame::Instance().getObjectFactory().createObjectByID(e->Attribute("type"));
//		pGameObject->load(new CLoadParams (x, y, width, height, textureID, numFrames, currentRow, spawnTime, callbackID, animSpeed));
//
//		auto takewOwnershipPtr = std::unique_ptr<CGameObject>{ std::exchange(pGameObject, nullptr) };
//
//		//return objects
//		pObjects->push_back(std::move(takewOwnershipPtr));
//	}
//}