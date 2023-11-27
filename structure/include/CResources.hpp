#ifndef CRESOURCES_HPP
#define CRESOURCES_HPP

#include <string>
#include <SDL2/SDL.h>
#include <utility>

#include "Component.hpp"
#include "CPhysics.hpp"

using std::pair; 
using PColliders = std::vector<std::unique_ptr<Collider>>*;

struct Resources:Component{
public:
    Resources();

    //compiler-generated copy constructor works, shallow copy is desired
    ~Resources();

public:
    GameEntity* m_parent;
    SDL_Rect m_rectangle;
    SDL_Surface* m_surface;
    SDL_Texture* m_texture;
    SDL_Renderer* m_renderer;
    std::vector<int>* m_mask;
    PColliders m_colliderComponents;
    void createMask();
    //used in implemenation of createMask()
    pair<int,int> m_size;

};
#endif