#pragma once
#include "CLoadParams.h"
#include <SDL.h>
class IObject
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual void load(CLoadParams* params) = 0;

protected:
	IObject() {}
	virtual ~IObject() {}
};