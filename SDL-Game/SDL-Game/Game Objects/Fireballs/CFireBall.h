#pragma once
#include <string>
#include "../../Physics/Vector2D.h"
#include "../../Collision/ColliderBox.h"
#include "../IObject.h"
#include "../../Managers/CTextureManager.h"
#include "../../Managers/CSoundManager.h"
#include "../../Factories/CBaseCreator.h"

class CFireBall : public IObject
{
public:
	CFireBall();
	virtual void draw();
	virtual void update(double dt);
	virtual void clean();
	virtual void load(CLoadParams* params);

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }

	ColliderBox& getColliderBox() { return m_ColliderBox; }
	Vector2D m_position;
	Vector2D m_Velocity;

protected:

	ColliderBox m_ColliderBox;
	std::string m_textureID; 
	std::string m_ObjectID;
	int m_width;
	int m_height;
	int m_TotalFrames;
	int m_currentRow;
};

class CFireBallCreator : public CBaseCreator
{
	// Inherited via CBaseCreator
	virtual CFireBall* createGameObject() const override
	{
		return new CFireBall();
	}
};