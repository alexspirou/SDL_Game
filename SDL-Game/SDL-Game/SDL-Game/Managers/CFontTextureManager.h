#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>
static TTF_Font* font = NULL;
struct FontStruct
{
    FontStruct(int x, int y, int w, int h, SDL_Color color) : x{ x }, y{ y }, w{ w }, h{ h }, color{ color } { }
    int x, y, w, h;
    SDL_Color color;
};
class CFontTextureManager
{

public:
    CFontTextureManager();
    bool loadFont(const char* path, int fontSize);
    void renderText(std::string textToRender, FontStruct fontStruct, int side);
    void renderScore(int score, SDL_Color colour);
private:
    TTF_Font* font;
    SDL_Color wht = { 180,0,0 };
    SDL_Surface* message;
    SDL_Texture* texture;
    int counter = 0;
};

