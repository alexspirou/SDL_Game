#pragma once

#include <string>
//A structure that holds object's x,y,width,height and texture id
struct CLoadParams
{

public:

	CLoadParams(int x, int y, int width, int height, std::string textureID, int TotalFrames, int currentRow = 0 , int spawnTime = 0, int callBackID = 0, int animSpeed = 0)
		:m_x(x), m_y(y), m_Width(width), m_Height(height), m_TextureID(textureID), m_TotalFrames(TotalFrames), m_SpawnTime(spawnTime), m_CurrentRow(currentRow),
		m_CallBackID(callBackID), m_AnimeSpeed(animSpeed)
	{
	}
	
	int getX() { return m_x; }
	int getY() { return m_y; }
	int getWidth() { return m_Width; }
	int getHeight() { return m_Height; }
	int getTotalFrames() { return m_TotalFrames; }
	int getCurrentRow() { return m_CurrentRow; }
	int getSpawnTime() { return m_SpawnTime; }
	std::string getTextureID() { return m_TextureID; }

	void setTextureID(std::string changeID) { m_TextureID = changeID; }

private:

	int m_x, m_y;
	int m_Height, m_Width;
	int m_CallBackID, m_AnimeSpeed;
	int m_TotalFrames; 
	int m_CurrentRow;
	int m_SpawnTime;
	std::string m_TextureID;
};