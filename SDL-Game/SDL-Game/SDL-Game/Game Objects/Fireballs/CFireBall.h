#pragma once
#include <string>
#include "../../Physics/Vector2D.h"
#include "../../Collision/ColliderBox.h"

class CFireBall
{
public:
	CFireBall();
	void draw();
	void update(double dt);
	void clean();

	int getWidth() { return m_width; }
	int getHeight() { return m_height; }
	//bool isCollision(CGameObject* p);
	ColliderBox& getColliderBox() { return m_ColliderBox; }

	Vector2D m_position;
	Vector2D m_Velocity;
private:
	ColliderBox m_ColliderBox;

	std::string m_textureID; 
	int m_width;
	int m_height;
};

