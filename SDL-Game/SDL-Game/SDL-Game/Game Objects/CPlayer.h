#pragma once
#include "CGameObject.h"
//#include "../Factories/CBaseCreator.h"
//
//class CPlayerCreator : public CBaseCreator
//{
//	// Inherited via CBaseCreator
//	virtual std::unique_ptr<CGameObject> createGameObject() const override
//	{
//		return std::make_unique<CPlayer>();
//	}
//};
class CPlayer : public CGameObject
{
public:
	CPlayer() {}
	virtual ~CPlayer() = default;

	virtual void draw();
	virtual void update();
	virtual void clean();
	
private:

	void handleMouseClickEvents();

	void handleMouseMotionEvents();

	void handleKeyBoardEvents();
};

