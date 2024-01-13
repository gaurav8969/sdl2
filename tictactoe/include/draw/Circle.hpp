#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "SDL2/SDL.h"

class Circle{

public:
    static void draw(SDL_Renderer* renderer, int cornerX, int cornerY);
};
#endif