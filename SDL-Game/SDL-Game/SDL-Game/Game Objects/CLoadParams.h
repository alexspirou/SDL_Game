#pragma once

#include <string>
//A structure that holds object's x,y,width,height and texture id
struct CLoadParams
{

public:

	CLoadParams(int x, int y, int width, int height, std::string textureID)
		:prm_x(x), prm_y(y), prm_Width(width), prm_Height(height), prm_TextureID(textureID) {}
	
	int getX() { return prm_x; }
	int getY() { return prm_y; }
	int getWidth() { return prm_Width; }
	int getHeight() { return prm_Height; }
	std::string getTextureID() { return prm_TextureID; }

private:

	int prm_x, prm_y;

	int prm_Height, prm_Width;

	std::string prm_TextureID;
};