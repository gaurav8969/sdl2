#include "GameEntity.hpp"
#include <iostream>

GameEntity::GameEntity(SDL_Renderer* renderer, std::string spritepath){
    m_sprite = new TexturedRectangle(renderer, spritepath); 
    m_renderer = renderer;
}

GameEntity::~GameEntity(){
    delete m_sprite;
    m_sprite = nullptr;
}

TexturedRectangle& GameEntity::getRect(){
    return *m_sprite;
}

bool GameEntity::isColliding(GameEntity& sprite){
    bool isColliding = m_sprite->isColliding(sprite.getRect());
    return isColliding;
}

void GameEntity::render(){
    //if the allocation failed
    if(m_sprite != nullptr){
        m_sprite->render();
    }else{
        std::cout << "Allocation failed" << std::endl;
    }
}
