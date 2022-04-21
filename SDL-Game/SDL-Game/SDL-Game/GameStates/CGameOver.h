#pragma once
#include "../Game Objects/CGameObject.h"
#include "../Managers/CFontTextureManager.h"

class CGameOver
{
public:

	CGameOver(FontStruct* fontstruct);
	CGameOver() = default;
	void update();
	void render();
	void moveLeftRight();

private:

	CFontTextureManager m_FontManager;
	FontStruct* m_FontStruct;
	bool m_RightFlag;
	int m_xGameOver;
	int m_WidthGameOver;
};

