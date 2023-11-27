#include "SSpriteUpdate.hpp"

//helper function for perfect collisions
//creates alpha masks
void SpriteUpdate::createMask(GameEntity* entity){
    auto& Resource{entity->getComponent<Resources>()};
    auto m_mask{Resource.m_mask};
    delete m_mask;

    m_mask = new std::vector<int>();

    SDL_Surface* m_surface{Resource.m_surface};
    SDL_LockSurface(m_surface);
    int colourchannels = m_surface->pitch/m_surface->w;
    int m_h = m_surface->h;
    int pitch = m_surface->pitch;
    Uint8* pixels = (Uint8*)m_surface->pixels;
    SDL_UnlockSurface(m_surface);

    for(int y = 0; y < m_h; y++){
        for(int x = 0; x < pitch; x+=colourchannels){
            if(pixels[y*(pitch) + x + 3 ] == 0){
                m_mask->push_back(0);
            }
            else{
                m_mask->push_back(1);
            }
        }
    }
}

void SpriteUpdate::updateSize(GameEntity* entity,int w, int h){
    auto& cphysics{entity->getComponent<CPhysics>()};    
    cphysics.m_pos = {w,h};

}