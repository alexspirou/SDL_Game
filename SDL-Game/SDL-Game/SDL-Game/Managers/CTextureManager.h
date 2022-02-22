#pragma once
#include<SDL.h>
#include <string>
#include <map>
#include <memory>

class CTextureManager
{
public:
	//Delete copy constructor to have a unique object in entire application
	CTextureManager(const CTextureManager&) = delete;
	CTextureManager operator=(const CTextureManager&) = delete;
	//Singleton construction
	static CTextureManager& Instance()
	{
		if (s_Instance == 0){ s_Instance.reset(new CTextureManager()); }
		return *s_Instance;
	}
	//Load image
	bool loadImage(std::string filename, std::string id, SDL_Renderer* pRenderer);
	//Draw static image
	void draw(std::string id, int x, int y, int width, int height,
		SDL_Renderer* renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	//Draw animated image
	void drawFrame(std::string id, int x, int y, int width, int
		height, int currentRow, int currentFrame, SDL_Renderer*
		renderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawTile(std::string tilesetID, int tileSize, int x, int y, int row, int fram, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void clearTextureMap(std::string id);

private:

	CTextureManager() {}
	inline static std::unique_ptr<CTextureManager> s_Instance;
	std::map<std::string, SDL_Texture*> m_TextureMap; //Map for stores the texture ids for each texture that is loaded
};

