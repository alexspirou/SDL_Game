#pragma once
#include "IGameStates.h"
#include "../Game Objects/CPlayer.h"
#include "../Game Objects/CEnemy.h"
#include "../Game Objects/CStableObject.h"

#include <memory>
class CPlayerStates : public IGameStates
{
public:
	virtual ~CPlayerStates() = default;
	virtual void update(double dt);
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();

	virtual std::string getStateID() const { return m_playID; }

private:

	double calculateLength(ColliderBox* gameObject1, ColliderBox* gameObject2)
	{
		double distance = sqrt(((gameObject1->m_Box.x - gameObject2->m_Box.x) * (gameObject1->m_Box.x - gameObject2->m_Box.x)) + ((gameObject1->m_Box.y - gameObject2->m_Box.y) * (gameObject1->m_Box.y - gameObject2->m_Box.y)));

		return distance;
	}
	bool isCollision(ColliderBox* gameObject1, ColliderBox* gameObject2)
	{
		if (gameObject1->m_Box.x + gameObject1->m_Box.w < gameObject2->m_Box.x || gameObject1->m_Box.x > gameObject2->m_Box.x + gameObject2->m_Box.w ||
			gameObject1->m_Box.y + gameObject1->m_Box.h < gameObject2->m_Box.y || gameObject1->m_Box.y> gameObject2->m_Box.y + gameObject2->m_Box.h)
		{
			return false;
		}
		else
		{
			std::cout << "Collision " << std::endl;
			return true;
		}
	}
	const std::string m_playID{"PLAY"};
	std::vector<std::unique_ptr<CStableObject>> m_vGameObjects;
	std::unique_ptr<CPlayer> m_Player;
	std::vector<std::unique_ptr<CEnemy>> m_vEnemies;
	std::vector<std::string> m_TexturesIDs;
	std::unique_ptr<CGameObject> m_BackGround;
};

