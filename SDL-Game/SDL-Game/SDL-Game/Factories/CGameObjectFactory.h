#pragma once
#include "CBaseCreator.h"

class CGameObjectFactory
{

public :

	bool registerTypeID(std::string typeID, std::unique_ptr<CBaseCreator> pCreator)
	{
		auto it = m_creators.find(typeID);
		// if the type is already registered, do nothing
		if (it != m_creators.end())
		{
			std::cout << "SAME OBJECT " << std::endl;
			return false;
		}
		//Assign object to its id
		m_creators[typeID] = std::move(pCreator);
		return true;
	}

	std::unique_ptr<CGameObject> createObjectByID(std::string typeID)
	{
		auto it = m_creators.find(typeID);

		if (it == m_creators.end())
		{
			std::cout << "could not find type: " << typeID << "\n";
			return NULL;
		}
		std::unique_ptr<CBaseCreator> pCreator(std::move(it->second));
		
		return pCreator->createGameObject();
	}
private:

	std::map<std::string, std::unique_ptr<CBaseCreator>> m_creators;
};


