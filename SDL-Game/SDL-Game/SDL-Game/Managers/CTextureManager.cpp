#include "CTextureManager.h"
#include "SDL_image.h"
#include <iostream>
//Define static member

bool CTextureManager::loadImage(const char* filename, std::string id, SDL_Renderer* pRenderer)
{
	SDL_Surface* pTempSurface = IMG_Load(filename);
	if (pTempSurface) { std::cout << "Image Load : "; std::cout << filename << std::endl; }
	else { std::cout << "Image not load\n"; }

	SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);
	SDL_FreeSurface(pTempSurface);
	
	if (!pTexture){ return false; }

	m_TextureMap[id] = pTexture;
	return true;
}

void CTextureManager::draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
	SDL_Rect srcRect{}; SDL_Rect destRect{};
	destRect.x = x;
	destRect.y = y;
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	SDL_RenderCopyEx(pRenderer, m_TextureMap[id], NULL,
		&destRect, 0, 0, flip);

}
void CTextureManager::drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame, 
	SDL_Renderer* pRenderer, SDL_RendererFlip flip )
{
	SDL_Rect srcRect{}; SDL_Rect destRect{};
	srcRect.x = width * currentFrame;
	srcRect.y = height * (currentRow);
	srcRect.w = destRect.w = width;
	srcRect.h = destRect.h = height;
	destRect.x = x;
	destRect.y = y;
	SDL_RenderCopyEx(pRenderer, m_TextureMap[id], &srcRect,
		&destRect, 0, 0, flip);
}

void CTextureManager::clearTextureMap(std::string id)
{
	SDL_DestroyTexture(m_TextureMap.find(id)->second);
	m_TextureMap.erase(id);
}
