#include <iostream>
#include <utility>

#include "SDL2/SDL.h"
#include "GameEntity.hpp"
#include "ResourceManager.hpp"

using std::pair;

GameEntity::GameEntity(SDL_Renderer* renderer, std::string spritepath){
    m_sprite = new TexturedRectangle(renderer, spritepath);
    m_renderer = renderer;
    m_spritepath = spritepath;
    m_scaledSurface = ResourceManager::GetInstance().GetSurface("assets/blackSurface4K.bmp");
    this->updateSpriteSize(100,100);

    if(!m_sprite){
        throw std::bad_alloc();
    }

    if(!m_renderer){
        throw std::invalid_argument("Renderer is not provided.");
    }
}

GameEntity::~GameEntity(){
    delete m_sprite;
    m_sprite = nullptr;
}

void GameEntity::addCollider(int xOffset, int yOffset, int width, int height){
    std::unique_ptr<Collider2D> collider = std::make_unique<Collider2D>();
    if(!collider){
        throw std::bad_alloc();
    }
    pair<int,int> spritePosition = m_sprite->getPosition();
    int xCollider = spritePosition.first + xOffset;
    int yCollider = spritePosition.second + yOffset;
    collider->setPosition(std::make_pair(xCollider,yCollider));
    collider->setDimensions(std::make_pair(width,height));

    m_colliderComponents.push_back(std::move(collider));
}

void GameEntity::render(){
    SDL_SetRenderDrawColor(m_renderer,0,0,0,255);
    //could draw multiple debug boxes for various collider components
    m_sprite->render();
    for(auto& collider: m_colliderComponents){
        SDL_RenderDrawRect(m_renderer,collider->getCollider());
    }
}

bool GameEntity::isColliding(GameEntity* sprite,size_t collider,size_t collidingWith){
    auto size = m_colliderComponents.size();
    if(collider < size && collidingWith < size){
        Collider2D* s_collider = m_colliderComponents[collider].get();
        Collider2D* s_collidingWith = sprite->m_colliderComponents[collidingWith].get();
        return s_collider->isColliding(s_collidingWith);
    }
    return false;
}

void GameEntity::updatePosition(int x, int y){
    pair<int,int> initPos = m_sprite->getPosition();
    int deltaX = x - initPos.first;
    int deltaY = y - initPos.second;

    m_sprite->setPosition(std::make_pair(x,y));
    for(auto& collider:m_colliderComponents){
        int s_x = collider->getCollider()->x+deltaX;
        int s_y = collider->getCollider()->y +deltaY;
        pair<int,int> position = std::make_pair(s_x,s_y);
        collider->setPosition(position);
    }
}

void GameEntity::updateSpriteSize(int w, int h){
    std::pair<int,int> size = std::make_pair(w,h);
    m_sprite->setDimensions(size);
    m_w = w;
    m_h = h;

    createMask();
}

void GameEntity::updateColliderSize(size_t index, int w, int h){
    std::pair<int,int> size = std::make_pair(w,h);
    m_colliderComponents[index]->setDimensions(size);
}

void GameEntity::createMask(){
    delete m_mask;
    m_mask = new std::vector<int>();

    SDL_Surface* surface = ResourceManager::GetInstance().GetSurface(m_spritepath);
    SDL_Rect scaleRect;
    scaleRect.x = 0;
    scaleRect.y = 0;
    scaleRect.w = m_w;
    scaleRect.h = m_h;
    SDL_BlitScaled(surface,NULL,m_scaledSurface,&scaleRect);

    SDL_LockSurface(m_scaledSurface);
    int colourchannels = m_scaledSurface->pitch/m_scaledSurface->w;
    Uint8* pixels = (Uint8*)m_scaledSurface->pixels;
    SDL_UnlockSurface(m_scaledSurface);
    for(int y = 0; y < m_h; y++){
        for(int x = 0; x < m_w*colourchannels; x+=colourchannels){
            if(pixels[y*(m_w*colourchannels) + x + 3 ] < 50){
                m_mask->push_back(0);
            }
            else{
                m_mask->push_back(1);
            }
        }
    }
}