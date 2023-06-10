#include "CFontTextureManager.h"
#include "../Core/CGame.h"
#include "../ScreenDimentions.h"
CFontTextureManager::CFontTextureManager()
{
    TTF_Init();
    if (!TTF_Init) { std::cout << "Faile to init ttf\n"; }
}
bool CFontTextureManager::loadFont(const char* path, int fontSize)
{
    font = TTF_OpenFont(path, fontSize);

    if (font == NULL)
    {
        std::cerr << "Failed the load the font!\n";
        std::cerr << "SDL_TTF Error: " << TTF_GetError() << "\n";
        font = TTF_OpenFont(path, fontSize);
        return false;
    }
    return true;
}

void CFontTextureManager::renderText(std::string textToRender, FontStruct* fontStruct , int side)
{
    //If there was an error in rendering the text
    const char* textToCharPtr = textToRender.c_str();
    message = TTF_RenderText_Solid(font, textToCharPtr, fontStruct->color);

    auto render = CGame::Instance().getRenderer();

    texture = SDL_CreateTextureFromSurface(render, message);

    SDL_Rect dest = { fontStruct->x  , fontStruct->y   , fontStruct->w ,fontStruct->h  };
    SDL_RenderCopyEx(render, texture, 0, &dest, 0, nullptr, SDL_FLIP_NONE);

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(message);
}
void CFontTextureManager::renderScore(int score, SDL_Color colour)
{
    //If there was an error in rendering the text
    auto render = CGame::Instance().getRenderer();

    std::string s = "SCORE : " + std::to_string(score);
    message = TTF_RenderText_Solid(font, s.c_str(), colour);

    texture = SDL_CreateTextureFromSurface(render, message);
    SDL_Rect dest = { SCREEN_WIDTH - message->w, 0 , message->w, message->h };
    /* SDL_RendererFlip flip{};
     SDL_RenderCopyEx(CEngine::m_renderer, texture, 0, &dest, 0, nullptr, flip);*/

     //SDL_DestroyTexture(texture);
     //SDL_FreeSurface(message);

}