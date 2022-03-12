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
	virtual void update(double dt);
	virtual void clean();
	virtual void load(CLoadParams* params) override;
	virtual Vector2D getPosition() { return m_position; }
	virtual std::string getTextureID() { return m_textureID; }

protected:
	std::string m_textureID;

	int m_currentFrame;
	int m_currentRow;
	
	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	int m_TotalFrames;

	CMouseEvents m_mouseEvents;
	int m_width; int m_height;
	SDL_RendererFlip m_FlipSiderRender;
	bool isPlayerMovingRightInScreen = true;
	double deltaTime;

	bool m_bDestroyed = false;
};

