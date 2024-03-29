#pragma once
#include "CBaseCreator.h"

class CGameObjectFactory
{

public :

	bool registerTypeID(std::string typeID, CBaseCreator* pCreator)
	{
		auto it = m_creators.find(typeID);
		// if the type is already registered, do nothing
		if (it != m_creators.end())
		{
			std::cout << "SAME OBJECT " << std::endl;
			return false;
		}
		// Assign object to its id
		m_creators[typeID] = pCreator;

		return true;
	}
	template <typename T>
	T* createObjectByID(std::string typeID)
	{
		auto it = m_creators.find(typeID);

		if (it == m_creators.end())
		{
			std::cout << "could not find type: " << typeID << "\n";
			return NULL;
		}
		CBaseCreator* pCreator = it->second;
		return new T();
	}
private:

	// Map of types that will be used
	std::map<std::string, CBaseCreator*> m_creators;

};


