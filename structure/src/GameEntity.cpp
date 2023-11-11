#include <iostream>
#include <utility>
#include <exception>
#include <cstdio>
#include "stdlib.h"

#include "SDL2/SDL.h"
#include "GameEntity.hpp"
#include "ResourceManager.hpp"

using std::pair;

GameEntity::GameEntity(SDL_Renderer* renderer, std::string spritepath){
    m_sprite = new TexturedRectangle(renderer, spritepath);
    m_surface = ResourceManager::GetInstance().GetSurface(spritepath);
    m_renderer = renderer;

    m_mask = nullptr;
    this->addCollider(0,0,100,100);
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
    delete m_mask;
    m_mask = nullptr;
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

bool GameEntity::isColliding(GameEntity* sprite,size_t m_collider,size_t collider, bool isPixelPerfect){
    auto m_size = m_colliderComponents.size();
    auto size = sprite->m_colliderComponents.size();
    if(m_collider < m_size && collider < size){
        Collider2D* pm_collider = m_colliderComponents[m_collider].get();
        Collider2D* p_collider = sprite->m_colliderComponents[collider].get();
        SDL_Rect* m_collidingRect = pm_collider->getCollider();
        SDL_Rect* collidingRect = p_collider->getCollider();
        SDL_Rect* m_outline = m_colliderComponents[0].get()->getCollider();
        SDL_Rect* outline = sprite->m_colliderComponents[0].get()->getCollider();

        bool isColliding = SDL_IntersectRect(m_collidingRect,collidingRect,&m_intersection);
        
        if(isPixelPerfect && isColliding){
            //first assume there's no pixel perfect collision
            isColliding = false;
            //the origin
            int m_xintersection = m_intersection.x;
            int m_yintersection = m_intersection.y;
            
            int m_xcolliding = m_xintersection - m_outline->x;
            int m_ycolliding = m_yintersection - m_outline->y;

            int xcolliding = m_xintersection - outline->x;
            int ycolliding = m_yintersection - outline->y;

            int width = abs(m_intersection.w);
            int height = abs(m_intersection.h);

            int m_surfaceWidth = m_surface->w;
            int surfaceWidth = sprite->m_surface->w;
            for(int y = 0; y < height; y++){
                for(int x = 0; x < width; x++){
                    int m_xoffset = m_xcolliding + x;
                    int xoffset = xcolliding + x;
                    int m_yoffset = m_ycolliding + y;
                    int yoffset = ycolliding + y;

                    int m_index = m_xoffset + m_surfaceWidth*(m_yoffset);
                    int index = xoffset + surfaceWidth*(yoffset);
                    int m_bitValue = (*m_mask)[m_index];
                    int bitValue = (*sprite->m_mask)[index];

                    if(m_bitValue && bitValue){
                        return true;
                    }
                }
            }
        }
        return isColliding;
    }
    throw(std::out_of_range("The collider index(s) is(are) out of range"));
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
    updateColliderSize(0,w,h);
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

    SDL_LockSurface(m_surface);
    int colourchannels = m_surface->pitch/m_surface->w;
    int surfaceWidth = m_surface->w;
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

void GameEntity::checkPixel(int x, int y){
    SDL_Point point = {x,y};
    
    SDL_Rect* boundary = m_colliderComponents[0]->getCollider();
    bool pointInRect = SDL_PointInRect(&point,boundary);

    if(pointInRect){

        int xrect = boundary->x;
        int yrect = boundary->y;
        
        int xrel = x - xrect;
        int yrel = y - yrect;

        int index = m_w*yrel + xrel;

        std::printf("(%d,%d) is- alpha = %d\n",
        xrel, yrel, (*m_mask)[index]);
    }
}