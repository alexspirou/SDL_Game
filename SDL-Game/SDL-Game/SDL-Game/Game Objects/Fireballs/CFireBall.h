#pragma once
#include "../CGameObject.h"
#include "../../Physics/Vector2D.h"
class CFireBall
{
public:
	CFireBall();
	void draw();
	void update(double dt);
	void clean();

	int getWidth() { return m_width; }
	Vector2D m_position;
	Vector2D m_Velocity;

private:

	std::string m_textureID; 
	int m_width;
	int m_height;
};

