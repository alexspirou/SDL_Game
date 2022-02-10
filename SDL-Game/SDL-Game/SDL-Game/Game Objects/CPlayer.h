#pragma once
#include "CGameObject.h"

class CPlayer : public CGameObject
{
public:
	CPlayer(CLoadParams params) :CGameObject(params) {}
	virtual ~CPlayer() = default;

	virtual void draw();
	virtual void update();
	virtual void clean();
private:

	void handleMouseClickEvents();

	void handleMouseMotionEvents();

	void handleKeyBoardEvents();
};

