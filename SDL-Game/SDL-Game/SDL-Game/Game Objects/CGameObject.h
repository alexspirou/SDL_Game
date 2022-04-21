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
	virtual void draw()override;
	virtual void drawFrame();
	virtual void update(double dt)override;
	virtual void clean()override;
	virtual void load(CLoadParams* params) override;
	virtual Vector2D getPosition() { return m_position; }
	virtual std::string getTextureID() { return m_textureID; }
	std::string getObjectID() { return m_ObjectID; }
	inline ColliderBox& getCollinder() { return m_ColliderBox; }
	int getWidth() { return m_width; }
	int getHeight() { return m_height; }


protected:
	std::string m_textureID;
	std::string m_ObjectID;
	ColliderBox m_ColliderBox;

	double m_SpawnTime;
	double deltaTime;

	int m_currentFrame;
	int m_currentRow;
	int m_width; 
	int m_height;

	Vector2D m_position;
	Vector2D m_velocity;
	Vector2D m_acceleration;

	int m_TotalFrames;

	CMouseEvents m_mouseEvents;

	SDL_RendererFlip m_FlipSiderRender;
	bool isPlayerMovingRightInScreen = true;

	bool m_bDestroyed = false;
};

