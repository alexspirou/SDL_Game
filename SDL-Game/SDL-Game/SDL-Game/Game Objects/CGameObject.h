#pragma once
#include <SDL.h>
#include <string>
#include <memory>

#include "IObject.h"
#include "CLoadParams.h"
#include "../Physics/Vector2D.h"
#include "../Controllers/CMouseEvents.h"

class CGameObject : public IObject
{
public:
	CGameObject();
	virtual void drawFrame();
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void load(CLoadParams params);
protected:
	std::string m_textureID;

	int m_currentFrame;
	int m_currentRow;

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	CMouseEvents m_mouseEvents;
	int m_width; int m_height;

	bool isPlayerMovingRightInScreen = true;
};
