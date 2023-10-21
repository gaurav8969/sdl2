#include <iostream>
#include <utility>
#include <exception>

#include "SDL2/SDL.h"
#include "GameEntity.hpp"

GameEntity::GameEntity(SDL_Renderer* renderer, std::string spritepath){
    m_sprite = new TexturedRectangle(renderer, spritepath); 
    m_renderer = renderer;
    m_colliderComponent = new Collider2D();
    if(!m_sprite && !m_colliderComponent){
        throw std::bad_alloc();
    }

    if(!m_renderer){
        throw std::invalid_argument("Renderer is not provided.");
    }
    std::pair<int,int> position = m_sprite->getPosition();
    std::pair<int,int> dimensions = m_sprite ->getDimensions();
    m_colliderComponent->setPosition(position);
    m_colliderComponent->setDimensions(dimensions);
}

GameEntity::~GameEntity(){
    delete m_sprite;
    m_sprite = nullptr;
}

void GameEntity::render(){
    SDL_SetRenderDrawColor(m_renderer,255,0,255,255);
    SDL_RenderDrawRect(m_renderer,m_colliderComponent->getCollider());
    m_sprite->render();
}

TexturedRectangle& GameEntity::getRect(){
    return *m_sprite;
}

bool GameEntity::isColliding(GameEntity* sprite){
    bool isColliding = m_colliderComponent->isColliding(sprite->m_colliderComponent);
    return isColliding;
}

void GameEntity::updatePosition(int x, int y){
    std::pair<int,int> position = std::make_pair(x,y);
    m_sprite->setPosition(position);
    m_colliderComponent->setPosition(position);
}

void GameEntity::updateSize(int w, int h){
    std::pair<int,int> size = std::make_pair(w,h);
    m_sprite->setDimensions(size);
    m_colliderComponent->setDimensions(size);
}
