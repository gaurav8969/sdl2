#ifndef TEXT_HPP
#define TEXT_HPP

#include "SDL2/SDL.h"
#include <SDL2/SDL_ttf.h>

class Text{

public:
    Text(SDL_Renderer* renderer, int shape);
    void render();
private:
    bool isFilled;
    SDL_Renderer* renderer;
    TTF_Font* ourFont;
    SDL_Texture* textureText;
    SDL_Rect rectangle = {150,450,500,200};
};

#endif