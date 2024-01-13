#include "Circle.hpp"
#include "Constants.hpp"

void Circle::draw(SDL_Renderer* renderer, int cornerX, int cornerY){
    SDL_SetRenderDrawColor(renderer,CIRCLE_COLOUR.x,CIRCLE_COLOUR.y,CIRCLE_COLOUR.z,SDL_ALPHA_OPAQUE);

    int centreX = cornerX + CIRCLE_RADIUS;
    int centreY = cornerY + CIRCLE_RADIUS;

    const int32_t diameter = (CIRCLE_RADIUS * 2);
    int32_t x = (CIRCLE_RADIUS - 1);
    int32_t y = 0;
    int32_t dx = 1;
    int32_t dy = 1;
    int32_t error = (dx - diameter);

    while (x >= y){
        //  Each of the following renders an octant of the circle
        
        //first octant
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        //reflections in the other 7 octants
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += dy;
            dy += 2;
        }

        if (error > 0)
        {
            --x;
            dx += 2;
            error += (dx - diameter);
        }
   }
}