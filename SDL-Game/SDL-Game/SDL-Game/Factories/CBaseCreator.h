#pragma once
#include <string>
#include <map>
#include <memory>
#include "../Game Objects/CGameObject.h"

class CBaseCreator
{
public:
	virtual CGameObject* createGameObject() const = 0;
	virtual ~CBaseCreator() = default;
};