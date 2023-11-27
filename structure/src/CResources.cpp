#include<algorithm>
#include<iostream>

#include "CResources.hpp"
#include "ResourceManager.hpp"
#include "GameEntity.hpp"

Resources::~Resources(){
    SDL_DestroyTexture(m_texture);
}
