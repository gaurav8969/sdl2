#include "Cross.hpp"
#include "Constants.hpp"

void Cross::draw(SDL_Renderer* renderer, int x, int y){
    SDL_SetRenderDrawColor(renderer,CROSS_COLOUR.x,CROSS_COLOUR.y,CROSS_COLOUR.z,SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, x,y,x+CROSS_SIZE, y+CROSS_SIZE);
    SDL_RenderDrawLine(renderer, x,y+CROSS_SIZE, x+CROSS_SIZE, y);
}