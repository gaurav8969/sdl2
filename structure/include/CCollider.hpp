#ifndef COLLIDER2D_HPP
#define COLLIDER2D_HPP

#include <utility>
#include <vector>
#include <memory>

#include "SDL2/SDL.h"
#include "Component.hpp"

using std::pair;

struct Collider;

struct Collider:Component{
public:
    Collider();
    ~Collider()=default;

    void updateColliderSize(int w,int h);

public:    
    SDL_Rect colliderRect;
};

#endif