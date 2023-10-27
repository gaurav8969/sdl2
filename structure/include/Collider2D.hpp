#ifndef COLLIDER2D_HPP
#define COLLIDER2D_HPP

#include <utility>
#include "SDL2/SDL.h"

class Collider2D{
    public:
    Collider2D();
    ~Collider2D();

    bool isColliding(const Collider2D *);
    void setPosition(std::pair<int,int>);
    void setDimensions(std::pair<int, int>);
    SDL_Rect* getCollider();

    private:
    SDL_Rect* m_collider;
    SDL_Rect m_intersection;
};

#endif